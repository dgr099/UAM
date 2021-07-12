package pr3.trafico.itv;

import java.util.ArrayList;
import java.util.List;

import pr3.trafico.vehiculos.Vehiculo;


/**
 * Clase que contiene los métodos y atributos de taller
 * 
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Taller {
    private String nombre; /* nombre del taller */
    private String direccion; /* nombre de la direccion del taller */
    private String provincia; /* nombre de la provincia en la que se ubica el taller */
    private List<Vehiculo> vehiculosTaller = new ArrayList<Vehiculo>(); /* vehiculos que han pasado la itv en este taller */
    

	/**
	 * Método para obtener los vehiculos del taller
	 * @return lista de vehiculos
	 */
    public List<Vehiculo> getVehiculosTaller() {
		return vehiculosTaller;
	}

	/**
	 * Metodo para anyadir un vehiculo al taller
	 * @param v vehiculo a anyadir
	 */
    public void addVehiculo(Vehiculo v) {
    	if(this.vehiculosTaller.contains(v)==true) {
    		return;
    	}
    	this.vehiculosTaller.add(v);
    }

	/**
	 * Constructor de la clase Taller
	 * @param nombre nombre asignado al taller
	 * @param direccion direccion asignada al taller
	 * @param provincia nombre de la provincia del taller
	 */
	public Taller(String nombre, String direccion, String provincia) {
        this.nombre = nombre;
        this.direccion = direccion;
        this.provincia = provincia;
    }

	/**
	 * Método para obtener el nombre del taller
	 * @return nombre del taller
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Método para establecer el nombre del taller
	 * @param nombre nombre a asignar
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Método para obtener la direccion del taller
	 * @return direccion del taller
	 */
	public String getDireccion() {
		return direccion;
	}

	/**
	 * Método para establecer la direccion del taller
	 * @param direccion direccion del taller
	 */
	public void setDireccion(String direccion) {
		this.direccion = direccion;
	}

	/**
	 * Método para obtener la provincia del taller
	 * @return provincia del taller
	 */
	public String getProvincia() {
		return provincia;
	}

	/**
	 * Método para establecer la provincia del taller
	 * @param provincia provincia del taller
	 */
	public void setProvincia(String provincia) {
		this.provincia = provincia;
	}
    
}