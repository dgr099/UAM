package pr3.trafico.components;

import pr3.trafico.vehiculos.IVehicle;
/**
 * Clase que contiene los datos de los componentes de un vehículo
 *
 * @version 1.0 25 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class Component implements IComponent{
	private int tD = 0; //turnos que lleva dañado el componente
	private Boolean damage = false;  //si está actualmente dañado
	private String name = new String(); //nombre del componente
	private IVehicle v; //vehiculo del coche
	
	/**
	 * Método para establecer el vehículo 
	 * 
	 * @param v vehiculo a establecer en el componente
	 */
	public void setVehicle(IVehicle v){
		this.v = v;
	}
	
	/**
	 * Constructor de la clase componente
	 * @param nombre string con el nombre a establecer en el componente
	 */
	public Component(String nombre) {
		this.name=nombre;
	}

	/**
	 * Método para conocer si el componente es capaz de atacar a otros vehículos
	 * @return booleano que define si puede o no atacar el objeto
	 */
	public boolean canAttack(){
		return false;
	}

	/**
	 * Método para saber si el componente está o no dañado
	 * @return booleano con la información del daño del componente
	 */
	public boolean isDamaged() {
		return damage;
	}

	/**
	 * Método para establecer si el componente está o no dañado
	 * @param damage booleano para establecer el daño del componente
	 */
	public void setDamaged(boolean damage) {
		if(damage==true){
			this.tD=0; //reinicia el contador de turnos dañado
		}
		this.damage=damage; //le pone como dañado
	}

	/**
	 * Método para obtener el nombre del componente
	 * @return nombre del componente
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * Método para obtener el número de turnos que lleva dañado el componente
	 * @return entero con el número de turnos que lleva dañado
	 */
	public int getTD(){ //obtener los turnos que lleva dañado
		return this.tD;
	}

	/**
	 * Método para reparar parcial o totalmente un componente
	 * Aumenta en uno el número de turnos dañado, si con ese aumento
	 * se alcanza el número de turnos necesarios, se repara completamente
	 */
	public void repair() {
		if(this.isDamaged()==false){ //si no está dañado
			return;
		}
		this.tD++; //sumas 1 a los turnos que pasan reparando
		System.out.println(this.getVehicle().getName() + " " + this.getName() + " is being repaired " + this.tD + "/" + this.costRepair());
		if(this.tD==this.costRepair()){
			this.damage=false; //si lo reparas le quitas el daño
			this.tD=0; //reinicias el contador de turnos para reparar
		}
		//this.damage=true;
	}
	/**
	 * Método para obtener el objeto que implemente la interfaz IVehicle asociado al componente
	 * @return IVehicle asociado al objeto
	 */
	public IVehicle getVehicle() {
		return this.v;
	}
	
}
