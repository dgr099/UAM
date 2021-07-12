package pr3.trafico.conductores;

import pr3.trafico.vehiculos.*;
import java.util.*;
/**
 * Clase que contiene los métodos y atributos de propietario
 * 
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class Propietario {
    private String nombre=null;
    private ArrayList<Vehiculo> vehiculos = new ArrayList<>();

	/**
	 * Constructor de la clase propietario
	 * 
	 * @param nombre       nombre del propietario 
	 */
    public Propietario(String nombre) {
		this.nombre = nombre;
    }

	/**
	 * Método para conocer el nombre de un propietario
	 * 
	 * @return nombre del propietario
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Método para establecer el nombre de un propietario
	 * 
	 * @param nombre nombre del propietario a establecer
	 */
	public void setNombre(String nombre) {
		if(nombre==null){
			return;
		}
		this.nombre = nombre;
	}
	
	/**
	 * Método para obtener la lista de vehículos del propietario
	 * 
	 * @return lista de vehículos del propietario
	 */
	public ArrayList<Vehiculo> getVehiculos() {
		return vehiculos;
	}
	
	/**
	 * Método para establecer la lista de vehículos del propietario
	 * 
	 * @param vehiculos lista de vehiculos a establecer en el propietario
	 */
	public void setVehiculos(ArrayList<Vehiculo> vehiculos) {
		this.vehiculos = vehiculos;
    }
	
	/**
	 * Método para añadir un vehículo a la lista del propietario
	 * 
	 * @param v vehículo a añadir en la lista del propietario
	 */
    public void addVehiculo(Vehiculo v) {
    	if(v==null) {
    		return;
    	}
    	if(this.vehiculos.contains(v)) {
    		return;
    	}
    	this.vehiculos.add(v);
    }

	/**
	 * Método para poder imprimir la información relevante de propietario
	 * 
	 * @return string descriptivo del vehículo
	 */
	public String toString() {
		//this.vehiculos.toString().replace("[", "").replace("]", "")
		String info = new String();
		if(this.vehiculos.isEmpty()) {
			return info;
		}
		info+=" propietario de:\n";
		for(Vehiculo v:this.vehiculos) {
			info+=v + "\n";
		}
		return info;
	}
    
    
}
