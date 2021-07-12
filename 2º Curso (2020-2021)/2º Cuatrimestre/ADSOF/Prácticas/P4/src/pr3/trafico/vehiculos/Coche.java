package pr3.trafico.vehiculos;

import java.util.Date;
import java.util.Calendar;

import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.conductores.Propietario;

/**
 * Clase que contiene los datos de un coche (si es diesel más la información de
 * la clase vehículo de la que hereda) con métodos para obtener su número de
 * ruedas, su índice de contaminación y para imprimir su información
 *
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Coche extends Vehiculo{
	private boolean diesel; // Booleano que recoge si el coche es diesel o no

	/**
	 * Constructor de la clase coche, con el modelo, el anyo de compra y la
	 * mátricula (necesarios para el constructor del super, vehículo), y el booleano
	 * que definirá si es diesel
	 * 
	 * @param mod       modelo del coche
	 * @param a         anyo de compra del coche
	 * @param matricula matrícula del coche
	 * @param diesel    booleano para saber si es o no diesel
	 */
	public Coche(String mod, int a, String matricula, boolean diesel) {
		super(mod, a, matricula);
		this.diesel = diesel;
	}
	
	/**
	 * Constructor de la clase coche pasando su velocidad máxima
	 * @param maxSpeed velocidad maxima del coche
	 */
	public Coche(double maxSpeed) {
		super(maxSpeed, "Car");
		
	}
	/**
	 * Constructor de la clase coche, con el modelo, el anyo de compra y la
	 * mátricula (necesarios para el constructor del super, vehículo), y el booleano
	 * que definirá si es diesel además del propietario del coche
	 * 
	 * @param mod       modelo del coche
	 * @param a         anyo de compra del coche
	 * @param matricula matrícula del coche
	 * @param diesel    booleano para saber si es o no diesel
	 * @param p			propietario del vehículo
	 */
	public Coche(String mod, int a, String matricula, boolean diesel, Propietario p) {
		super(mod, a, matricula, p);
		this.diesel = diesel;
	}

	/**
	 * Método para obtener el número de ruedas del coche
	 * 
	 * @return el número de ruedas del coche
	 */
	public int numeroRuedas() {
		return 4;
	}

	/**
	 * Método para imprimir la clase coche (si se trata de un coche diesesl junto
	 * con los datos de la clase de la que hereda)
	 * 
	 * @return String descriptivo del coche
	 */
	/*public String toString() {
		return "Coche " + (this.diesel ? "diesel" : "gasolina") + ", " + super.toString();
	}*/

	/**
	 * Método para conocer el índice de contaminación del coche
	 * 
	 * @return el índice de contaminación del coche
	 */
	public IndiceContaminacion getIndiceContaminacion() {
		if (this.diesel){
			return IndiceContaminacion.C;
		}
		return super.getIndiceContaminacion();
	}

	/**
	 * Método para obtener el booleano que define si la coche es diesel
	 * 
	 * @return true si es diesel, false en el caso contrario
	 */
	public boolean getDiesel() {
		return this.diesel;
	}

	public boolean vVehiculo(TipoLicencia L){
        return (L == TipoLicencia.B);
    }
	/**
	 * Metodo para obtener el estado de caducidad de la ITV en un coche
	 * 
	 * @return booleano, que será false si no caducó aún, true en caso contrario
	 */
	public boolean cadITV() {
		Calendar fechaAct = Calendar.getInstance(); 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
    	//long msYear = 1000 * 60 * 60 * 24 * 365; /*ms de un año*/
		long msYear = 31536000000L; 
    	if(añosDif < 4) { //si no han pasado los 4 años no tiene que tiene que pasar itv
    		return false;
    	}
    	/*si ya han pasado los 4 años y no tiene ninguna ITV*/
   		if(this.getLastITV()==null) {
   			return true;
   		}
   		/*si hay última ITV, calculas la diferencia de tiempo entre la fecha act y la última inspeccion*/
    	long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime(); 
    	double difa = (double)((double)dif * (long)1/msYear); //dif en años
    	if(añosDif<10) { /*si han pasado 4 o + años pero no 10*/
    		if(difa > 2) { /*si han pasado más de dos años de la última inspección*/
    			return true;
    		}
    		return false;
    	}
    	/*si han pasado 10 o + años*/
    	if(difa >1) { /*si ha pasado +1 año de la última inspección*/
    		return true;
    	}
    	return false;
    }
	
	/**
	 * Metodo para obtener la fecha de la siguiente ITV
	 * 
	 * @return la fecha determinada
	 */
	public Date nextITV() {
		Calendar fechaAct = Calendar.getInstance(); 
		long msYear = 31536000000L; 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
		Calendar n = Calendar.getInstance();//el date de retorno
		if(añosDif <4) {
			n.set(this.getAnyoCompra() + 4, n.get(Calendar.MONTH), n.get(Calendar.DAY_OF_MONTH), n.get(Calendar.HOUR), n.get(Calendar.MINUTE));
			return n.getTime();
		}
		if(this.getLastITV()==null) { /*si aun no hizo ninguna itv y ya paso el tiempo*/
			return null;
		}
		long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime(); //diferencia entre hoy y su ultima itv
		if(añosDif<10) { /*si tiene entre 2 y 10 años de antiguedad (sin incluir), se hace cada dos años*/
			return new Date(fechaAct.getTime().getTime() + (2 * msYear) - dif);
		}
		return new Date(fechaAct.getTime().getTime() + (1 * msYear) - dif);
	}

	/**
	 * Método para actualizar la posición del coche
	 */
	@Override
	public void updatePosition() {
		double i=Math.random()*9;
		if(this.canMove() == false) { //si no se puede mover
			return;
		}
		if(i<=8) { //si sale un numero del 0 al 8 (9 de 10 opcs, 90%) se mueve a max vel
			this.setActualPosition(this.getActualPosition() + this.getMaxSpeed());
		}	else { //en caso contrario se mueve al 90% de su max vel
			this.setActualPosition(this.getActualPosition() + this.getMaxSpeed() * 90/100);
		}
		return;
	}
}
