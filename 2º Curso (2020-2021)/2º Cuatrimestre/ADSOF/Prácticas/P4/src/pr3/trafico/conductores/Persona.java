package pr3.trafico.conductores;

import pr3.trafico.carnet.Carnet;
import pr3.trafico.vehiculos.Vehiculo;

/**
 * Clase que contiene los métodos y atributos de persona
 * 
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Persona extends Propietario{
	private int edad;
	private Carnet carnet = null;
	
	/**
	 * Constructor de la clase persona con su información imprescindible (edad y nombre)
	 * 
	 * @param nombre       nombre de la persona
	 * @param edad		   edad de la persona
	 */
	public Persona(String nombre, int edad) {
		super(nombre);
		this.edad = edad;
	}
	
	/**
	 * Método para obtener el carnet de una persona
	 * 
	 * @return el carnet de la persona
	 */
	public Carnet getCarnet() {
		return this.carnet;
	}
	/**
	 * Método para establecer el carnet de una persona
	 * 
	 * @param carnet carnet que se pretende establecer a la persona
	 * @return true si se pudo establecer el carnet false en caso contrario
	 */
	public boolean setCarnet(Carnet carnet) {
		boolean r;
		if(carnet==null){
			return false;
		}
		if((r=carnet.setPropietario(this))) {
			this.carnet=carnet;
			return r;
		}
		return r;
	}

	/**
	 * Método paraconocer la edad de una persona
	 * 
	 * @return entero con su edad
	 */
	public int getEdad() {
		return edad;
	}
	
	/**
	 * Método para establecer la edad de una persona
	 * 
	 * @param edad edad a establecer en la persona
	 */
	public void setEdad(int edad) {
		if(edad<0){
			this.edad=0;
			return;
		}
		this.edad = edad;
	}
	
	/**
	 * Método para poder imprimir la información de una persona
	 * 
	 * @return string descriptivo de la persona con su información más importante
	 */
	public String toString(){
		return super.getNombre() + super.toString();
	}

	/**
	 * Método para añadir un vehículo a la lista de vehículos de la persona
	 * 
	 */
	public void addVehiculo(Vehiculo v) {
		if(v==null) {
			return;
		}
		super.addVehiculo(v);
		if(this.getCarnet()!=null) { /*si tiene carnet y es de tipo persona*/
			if(this.getCarnet().carnetValido(v)) /*compruebas que sea calidos*/
			v.setConductor(this); /*si lo es, lo asignas como conductor*/
		}
	}
}
