package pr3.trafico.conductores;

import pr3.trafico.vehiculos.Vehiculo;

/**
 * Clase que contiene los métodos y atributos de sociedad
 * 
 * @version 1.0 11 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Sociedad extends Propietario {
	private Persona responsable = null;



	/**
	 * Constructor de la clase sociedad
	 * 
	 * @param nombre		nombre de la sociedad
	 * @param responsable	persona responsable de la sociedad
	 */
	public Sociedad(String nombre, Persona responsable) {
		super(nombre);
		this.responsable = responsable;
	}

	/**
	 * Método para obtener al responsable de la sociedad
	 * 
	 * @return la persona responsable de la sociedad
	 */
	public Persona getResponsable() {
		return responsable;
	}
	
	/**
	 * Método para establecer a la persona responsable de la sociedad
	 * 
	 * @param responsable persona responsable de la sociedad
	 */
	public void setResponsable(Persona responsable) {
		if(!(responsable==null)){
            this.responsable = responsable;
        }
	}
	
	
	/**
	 * Método para poder imprimir la información de sociedad
	 * 
	 * @return string descriptivo de sociedad
	 */
	public String toString(){
		return super.getNombre() + " (responable: " + this.getResponsable().getNombre() + ")" + super.toString();
	}

	/**
	 * Método para añadir vehículos a sociedad
	 * 
	 * @param v	vehículo que se pretende añadir a la sociedad
	 */
	public void addVehiculo(Vehiculo v) {
		if(v==null) {
			return;
		}
		/*ponemos el propietario*/
		super.addVehiculo(v);
		/*comprobamos si podemos poner el conductor*/
		if(this.getResponsable().getCarnet() != null){
			if(this.getResponsable().getCarnet().carnetValido(v)) {
				v.setConductor(this.getResponsable());
			}
		}
	}
}
