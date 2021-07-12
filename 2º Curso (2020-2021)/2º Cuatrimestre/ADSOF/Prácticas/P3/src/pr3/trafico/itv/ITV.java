package pr3.trafico.itv;

import pr3.trafico.vehiculos.*;
import java.util.*;

/**
 * Clase que contiene los métodos y atributos de itv
 * 
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class ITV {
	private Vehiculo vehiculo = null; /* vehículo de la itv */
	private Calendar fecha; /* fecha en la que tiene lugar la itv */
	private Taller taller; /* taller en el que se realiza */
	private String comentarios; /* comentarios al respecto */

	/**
	 * Constructor de la clase itv
	 * @param fecha	fecha en la que se realiza la itv
	 * @param taller taller en el que tiene lugar
	 * @param comentarios comentarios al respecto de la itv
	 */
	public ITV(Calendar fecha, Taller taller, String comentarios) {
		this.fecha = fecha;
		this.taller = taller;
		this.comentarios = comentarios;
	}
	
	/**
	 * Constructor de la clase itv pasandole el vehíclo al que se hace la itv
	 * @param fecha	fecha en la que se realiza la itv
	 * @param taller taller en el que tiene lugar
	 * @param comentarios comentarios al respecto de la itv
	 * @param v vehículo de la itv
	 */
	public ITV(Calendar fecha, Taller taller, String comentarios, Vehiculo v) {
		this.fecha = fecha;
		this.taller = taller;
		this.comentarios = comentarios;
		this.vehiculo = v;
		if(v!=null) {
			v.addITV(this); //se añade la itv a la lista de itvs del vehíclo, que se encargará de añadir el vehiculo
							// a la lista del taller
		}
	}

	/**
	 * Método para obtener la fecha de la itv
	 * @return fecha de la itv
	 */
	public Calendar getFecha() {
		return this.fecha;
	}

	/**
	 * Método para obtener el vehículo de la itv
	 * @return vehículo de la itv
	 */
	public Vehiculo getVehiculo() {
		return vehiculo;
	}

	/**
	 * Método para establecer el vehículo de la itv
	 * @param vehiculo al que se le quiere establecer la itv
	 */
	public void setVehiculo(Vehiculo vehiculo) {
		if(vehiculo==null) {
			return;
		}
		this.vehiculo = vehiculo;
	}

	/**
	 * Método para conocer el taller de un coche
	 * @return taller en el que tiene lugar la itv
	 */
	public Taller getTaller() {
		return taller;
	}

	/**
	 * Método par establecer el taller de la itv
	 * @param taller taller que se quiere establecer a la itv
	 */
	public void setTaller(Taller taller) {
		this.taller = taller;
	}

	/**
	 * Método para obtener los comentarios de la itv
	 * @return comentarios de la última itv
	 */
	public String getComentarios() {
		return comentarios;
	}

	/**
	 * Método para establecer los comentarios de la itv
	 * @param comentarios comentarios de la itv
	 */
	public void setComentarios(String comentarios) {
		this.comentarios = comentarios;
	}

	/**
	 * Método para establecer la fehca en la que tiene lugar la itv
	 * @param fecha fecha en la que tiene lugar la itv
	 */
	public void setFecha(Calendar fecha) {
		this.fecha = fecha;
	}

	
	/**
	 * @param v vehiculo del que comprobar si caduca su itv
	 * @return booleano, que será false si no caducó aún, true en caso contrario
	 */
	static public boolean cadITV(Vehiculo v) {
		return v.cadITV();

	}

	/**
	 * Método para conocer la fecha de la siguiente itv
	 * @param v vehículo del que se quiere conocer la fecha de la itv próxima
	 * @return fecha de la siguiente itv
	 */
	public Date nextITV(Vehiculo v) {
		return v.nextITV();
	}

}