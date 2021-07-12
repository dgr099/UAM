package teatro;

import java.io.Serializable;

import entrada.Entrada;
import ui.control.compra.ControlCompra;

/** 
 * Clase abstracta Zona con sus respectivos métodos y atributos
 * @version 1.0 28 Mar 30
 * @author David Teófilo Garitagoitia Romero
 */

public abstract class Zona implements Comparable<Zona>, Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 4704407797887708345L;
	private String nombre;
	static private double limitacion = 0;
	private Teatro t=null;
	
	/**
	 * Método para conocer el máximo número de personas que pueden estar en la zona sin limitaciones
	 * @return maximo numero de personas
	 */
	public abstract int getMax();
	/**
	 * Función que obtiene el teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return t Teatro
	 */
	public Teatro getTeatro() {
		return this.t;
	}
	/**
	 * Función que asigna el teatro
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param t Teatro
	 */
	public void setTeatro(Teatro t) {
		this.t=t;
	}
	/**
	 * Función que obtiene el nombre del teatro
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return getNombre (String)
	 */
	public String getNombre() {
		return nombre;
	}
	/**
	 * Función que asigna el nombre del teatro
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param t nombre a asignar
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	/**
	 * Constructor de la clase Zona
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre de la zona
	 */
	public Zona(String nombre) {
		this.nombre = nombre;
	}
	/**
	 * Muestra por pantalla la zona del teatro
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public abstract void mostrarZona();
	/**
	 * Función que compara la zona pasada por argumento con la zona actual
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona a comparar
	 */
	public int comparteTo(Zona z) {
		return this.nombre.compareTo(z.nombre);
	}
	@Override
	public boolean equals(Object o) {
		if(o==null) {
			return false;
		}
		if(o instanceof Zona) {
			Zona aux = (Zona)o;
			return this.getNombre().equals(aux.getNombre());
		}
		return false;
	}
	/**
	 * Función que compara la zona pasada por argumento con la zona actual
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param l limitacion (double)
	 */
	public static void setLimitacion(double l) {
		Zona.limitacion=l;
	}
	/**
	 * Función que obtiene el porcentaje de limitacion de la zona
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return La limitación (double)
	 */
	public static double getLimitacion() {
		return Zona.limitacion;
	}
	
	/**
	 * Método para obtener un string descriptivo de la zona
	 * @return String descriptivo de la zona
	 */
	public String toString() {
		return this.nombre;
	}
	
	/**
	 * Factory method para zona, dependiendo de si es zona numerada o no, genera una u otra entrada para la compra
	 * @return Entrada
	 * @throws Exception 
	 */
	public abstract Entrada factoryEntrada(ControlCompra cc) throws Exception;
	
	/**
	 * Método para actualizar las limitaciones
	 */
	public abstract void actLimitaciones();
}
