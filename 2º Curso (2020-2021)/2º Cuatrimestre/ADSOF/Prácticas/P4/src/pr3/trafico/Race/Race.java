package pr3.trafico.Race;

import pr3.trafico.components.IComponent;
import pr3.trafico.powerup.AttackAll;
import pr3.trafico.powerup.PowerUp;
import pr3.trafico.powerup.AutoHealthAll;
import pr3.trafico.powerup.Swap;
import pr3.trafico.vehiculos.*;


import java.util.ArrayList;
import java.util.List;



/**
 * Clase que contiene los datos de una carrera
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Race {
    private double longitud; //longitud de la carrera
    private List<Vehiculo> participantes = new ArrayList<Vehiculo>(); //lista de participantes de la carrera
    private Boolean attacks = false; //booleano que define si los ataques están activados
    private Boolean powerUps = false; //booleano que define si los powerUps están activados

    /**
     * Constructor de la carrera
     * @param l longitud de la carrera
     * @throws Exception excepcion de Race
     */
    public Race(double l) throws Exception {
    	if(l<0) //no puede tener longitud negativa
    		throw new RaceException("Parámetros fuera de rango");
    	this.longitud = l;
    }
    
    /**
     * Método para conocer si los ataques están activados en la carrera
     * @return booleano que define si están o no permitidos los ataques
     */
    public Boolean getAttacks() {
    	return this.attacks;
    }
    
    /**
     * Método que establece si los ataques están o no permitidos
     * @param b booleano que define si están permitidos los ataques
     */
    public void allowAttacks(Boolean b) {
    	this.attacks=b;
    }
    
    /**
     * Método para obtener un string descriptivo de la carrera
     * @return string descriptivo de la misma
     */
    public String toString() {
    	String fin = new String();
		fin+="Race with maximum length: " + Double.toString(this.getLongitud());
		for(Vehiculo v : this.participantes){
			fin+="\n";
			fin+=this.toStringAux(v);
			fin+=this.toStringAux2(v);
		}
		return fin;
    }

    /**
     * Método auxiliar para obtener la información relevante de un vehículo en la carrera
     * @param v vehiculo del que se desea conocer la información
     * @return string descriptivo de la situación del vehiculo
     */
    public String toStringAux(Vehiculo v) {
    	String f = new String();
		//f += "    " + v.toString();
    	f+=v.toString();
    	if(this.attacks==true) { /*si los ataques están habilitados*/
    		for(IComponent c: v.getComponents()) { //muestra el estado de los componentes
    			f+="\n ->" + c.getName() + ". Is damaged: "+ c.isDamaged() + ". Is critical: " + c.isCritical();
    		}
    		
    	}
		return f;
    }
    
    /**
     * Método auxiliar para conocer la situacion relativa del vehículo con respecto al resto en la carrera
     * @param v vehículo del que se desea conocer su posición con respeto del resto
     * @return string de la situacion relativa
     */
    public String toStringAux2(Vehiculo v) {
    	String f = new String();
    	for(Vehiculo v1 : this.getParticipantes()){
			if(v1 != v){
				f+="\n";
				f+= " " + v.getName() + " distance to " + v1.getName() + " " + Math.abs(v.distanceTo(v1)); 

			}
		}
    	return f;
    	
    }
    
	/**
	 * Método para conocer la longitud de la carrera
	 * @return longitud de la carrera
	 */
	public double getLongitud() {
		return longitud;
	}


	/**
	 * Método para obtener los participantes de la carrera
	 * @return lista de vehículos de la carrera
	 */
	public List<Vehiculo> getParticipantes() {
		return participantes;
	}
	
	/**
	 * Método para establecer la lista de participantes del vehículo
	 * @param participantes lista de vehiculos a establecer como participantes
	 */
	public void setParticipantes(List<Vehiculo> participantes) {
		this.participantes = participantes;
	}
	
	/**
	 * Método para añadir participantes
	 * @param p vehiculo a añadir en la carrera
	 * @throws RaceException excepcion de race
	 */
	public void addParticipantes(Vehiculo p) throws RaceException {
		if(this.participantes.contains(p)==true) {
			return;
		}
		if(p.getMaxSpeed()>=this.getLongitud()) {
			throw new RaceException("Carrera demasiado corta");
		}
		this.participantes.add(p);
	}
	
	/**
	 * Método para simular la carrera
	 */
	public void simulate() {
		Vehiculo w=null;
		int t=1; //turno
		boolean attacked = false;
		
		if(this.participantes.size()==0 || this.longitud<0) {
			return;
		}
		for(t=1; w == null; t++) { /*si hay ganador se deja de actualizar la carrera*/
			System.out.println("---------\nStarting Turn: " + t);
			System.out.println(this); //muestra el estado de la carrera
			System.out.println();
			/*fase de ataque*/
			if(this.attacks==true){ //si están activados los ataques
				if(t%3!=0) {//si no es turno de atacar
					System.out.println("Not attacking turn");
					if(this.powerUps == true) { //si ya se atacó y los powerUps están activados
						if(attacked == true) {
							this.PowerUpPhase();
						}
						else {
							System.out.println("Turn with no power ups");
						}
						
					}
				} else if(t%3 == 0){ //si es turno de atacar
					System.out.println("Start attack phase");
					this.attackPhase();
					attacked = true;
					System.out.println("End attack phase");
				}
			}
			
			
			/*fase de raparación*/
			this.repairPhase();
			/*Actualizar posiciones y guardamos el ganador en w*/
			w=this.movePhase();
			//System.out.println("------------" +  w  + "------------");
			System.out.println("Ending Turn: "+ t +"\n---------");
		}
		//ultimo turno en el que ya hay ganador
		System.out.println("---------\nStarting Turn: " + t);
		System.out.println(this); //muestra el estado de la carrera
		System.out.println();
		/*fase de ataque*/
		if(this.attacks==true){ //si están activados los ataques
			if(t%3!=0) {//si no es turno de atacar
				System.out.println("Not attacking turn");
				if(this.powerUps == true) { //si ya se atacó y los powerUps están activados
					if(attacked == true) {
						this.PowerUpPhase();
					}
					else {
						System.out.println("Turn with no power ups");
					}
					
				}
			} else if(t%3 == 0){ //si es turno de atacar
				System.out.println("Start attack phase");
				this.attackPhase();
				attacked = true;
				System.out.println("End attack phase");
			}
		}
		/*fase de raparación*/
		this.repairPhase();
		//System.out.println("------------" +  w  + "------------");
		System.out.println("Ending Turn: "+ t +"\n---------");
		//imprime al ganador
		if(this.attacks)
			System.out.println(this.toStringAux(w));
		else {
			System.out.println(w); //imprime el ganador
		}
		System.out.println("has won the race");
		return;
	}
	
	/**
	 * Método para realizar la fase de movimiento
	 * @return si no hay ganador aún retorna null, en caso contrario retorna el ganador
	 */
	public Vehiculo movePhase() { //retorna null si no hay ganador, w si lo hay
		Vehiculo w=null; //winner
		for(Vehiculo v : this.getParticipantes()){
			v.updatePosition();
			if(w==null && v.getActualPosition()>=this.getLongitud()){ //si no hay un ganador previo y ha terminado la carrera
				w=v;
			}
		}
		return w;
	}

	/**
	 * Método para llevar acabo la fase de ataque
	 */
	public void attackPhase() {
		Vehiculo delante = null;
		//recorrer vehiculos en el orden que se introdujeron
		for(Vehiculo v : this.participantes) {
			//comprobar si el vehiculo puede atacar
			if(v.canAttack()) {
				delante = getDelante(v);
				if(delante != null) {
					double distance = delante.getActualPosition() - v.getActualPosition();
					if(distance < 30) {
						this.attack(v, delante);
					}
					else {
						System.out.println(v.getName() + " can not attack, next vehicle too far away");
					}
				}
				else {
					System.out.println(v.getName() + " can not attack, no vehicles ahead");
				}
			} else {
				System.out.println(v.getName() + " can not attack");
			}
		}
	}
	
	/**
	 * Método para obtener la distancia entre dos IVehicles
	 * @param v1 vehiculo 1
	 * @param v2 vehículo 2
	 * @return distancia entre vehiculo 1 y vehiculo 2
	 */
	public double distanceBetween(IVehicle v1, IVehicle v2) {
		return (v1.getActualPosition() - v2.getActualPosition());
		//return Math.abs(v.getActualPosition() - this.getActualPosition());
	}
	
	/**
	 * Método para conocer el Vehiculo que tenemos delantes del IVehicle pasado
	 * @param vehiculo IVehicle del que se quiere conocer quien está delante
	 * @return null si no tiene vehículo delante o el vehículo que tiene delante
	 */
	public Vehiculo getDelante(IVehicle vehiculo) {
		Vehiculo delante = null;
		double distancia;
		double auxdistancia = -1;
		
		//iterar sobre todos los vehiculos para obtener el mas cercano que este por delante
		for(Vehiculo v : this.participantes) {
			distancia = this.distanceBetween(v, vehiculo);
			//que este por delnate
			if((distancia > 0)) {
				if(distancia < auxdistancia || auxdistancia==-1) {
					auxdistancia = distancia;
					delante = v;
				}
			}
		}
		return delante;
	}
	
	
	/**
	 * Método para atacar desde un vehiculo hasta un objetivo
	 * @param vehiculo IVehicle desde el que se inicia el ataque
	 * @param objetivo Vehiculo al que va destinado el ataque
	 */
	public void attack(IVehicle vehiculo, Vehiculo objetivo) {
		if(objetivo==null){
			System.out.println(vehiculo.getName() + " has no one in front.");
			return;
		}

		if(Math.round(Math.random()) == 1) { 
			//(int)(Math.random()*(HASTA-DESDE+1)+DESDE)
			if(objetivo.getComponents()==null || objetivo.getComponents().size()<=0){
				return;
			}
			
			int pos = (int) (Math.random() * (objetivo.getComponents().size() -1));
			IComponent componente = objetivo.getComponents().get(pos);
			componente.setDamaged(true);
			
			if(componente.isCritical()){
				objetivo.setCanMove(false);
			}
			System.out.println(vehiculo.getName() + " attacks " + objetivo.getName() + " " + componente.getName());
		}	
		else{
			System.out.println(vehiculo.getName() + " fails attack to " + objetivo.getName());
		}
	}
	
	/**
	 * Método para llevar a acabo la fase de raparación de la carrera
	 */
	public void repairPhase() {
		/*todos los vehiculos reparan lo que necesiten*/
		for(Vehiculo v : this.getParticipantes()){
			Boolean dam = false; //bandera para saber si tiene algo crítico dañado
			for(IComponent ic : v.getComponents()){
				ic.repair();
				if(ic.isCritical()==true && ic.isDamaged()==true){ //si tiene algo dañado crítico no se mueve
					dam=true;
				}
			}
			if(!dam){ //si no tiene nada crítico dañado se puede seguir moviendo
				v.setCanMove(true);
			}
		}
					
	}
	
	/**
	 * Método para activar los powerUps
	 */
	public void activatePowerUp() {
		int pu;
		PowerUp swap = new Swap("Swap", this);
		PowerUp attackAll = new AttackAll("AttackAll", this);
		PowerUp autoHealthAll = new AutoHealthAll("AutoHealthAll", this);
		
		for(IVehicle v : this.getParticipantes()) {
			
			pu = (int) Math.round(Math.random() * 3);
			
			switch(pu) {
				case 0:
					System.out.println(v.getName() + " applying powerup: Swap");
					swap.applyPowerUp(v); 
					break;
				case 1:
					System.out.println(v.getName() + " applying powerup: AttackAll");
					attackAll.applyPowerUp(v); 
					break;	
				case 2:
					System.out.println(v.getName() + " applying powerup: AutoHealthAll"); 
					autoHealthAll.applyPowerUp(v);
					break;
			}
		}
	}
	
	/**
	 * Método para llevar a cabo la fase de powerUps de la carrera
	 */
	public void PowerUpPhase() {
		//this.activatePowerUp();
		if((double) Math.random() < 0.1) {
			System.out.println("Turn with power ups");
			this.activatePowerUp();
			System.out.println("End PowerUp phase");
		} else {
			System.out.println("Turn with no power ups");
		}
	}

	/**
	 * Método para establecer si están permitidos los powerUps
	 * @param b booleano para definir si están permitidos o no los PowerUps
	 */
	public void allowPowerUps(boolean b) {
		this.powerUps = b;
	}

}
