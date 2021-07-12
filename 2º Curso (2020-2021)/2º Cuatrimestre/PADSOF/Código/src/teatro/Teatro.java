package teatro;

import java.io.Serializable;
import java.util.*;

import sistema.Sistema;
import usuario.Usuario;

/** 
 * Clase con métodos y atributos de Teatro
 * @version 1.0 28 Mar 30
 * @author David Teófilo Garitagoitia Romero
 */

public class Teatro implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 6742897171601966458L;
	private String nombre;
	private double limitaciones;
	private List<Zona> zonas = new ArrayList<Zona>();
	public String getNombre() {
		return nombre;
	}
	/**
	 * Función que asigna un nombre al teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre deseado
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	/**
	 * Función que obtiene las limitaciones del teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return limitaciones del teatro
	 */
	public double getLimitaciones() {
		return limitaciones;
	}
	/**
	 * Función que asigna ulas limitaciones del teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param limitaciones limtiaciones a asignar
	 */
	public void setLimitaciones(double limitaciones) {
		for(Usuario u : Sistema.getInstancia().getUsuarios()) { /*solo se puede modificar las limitaciones si no hay ninguna entrada vendida*/
			if(u.getEntradas().size()>0) {
				return;
			}
		}
		if(limitaciones<0 || limitaciones>100) { /*no pueden existir limitaciones negativas ni superiores al 100%*/
			return;
		}
		Zona.setLimitacion(limitaciones);
		this.limitaciones = limitaciones;
	}
	/**
	 * Función que obtiene las zonas del teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return lista de zonas del teatro 
	 */
	public List<Zona> getZonas() {
		return zonas;
	}
	/**
	 * Función que asigna una zona al teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param zonas lista de zonas
	 */
	public void setZonas(List<Zona> zonas) {
		this.zonas = zonas;
	}
	/**
	 * Función que añade una zona al array de zonas
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona a añadir
	 * @return true o false si se ha podido añadir o no
	 */
	public boolean addZona(Zona z) {
		if(z==null || (z.getTeatro()!=this && z.getTeatro()!=null) || this.getZonas().contains(z)) { //si no hay zona o ya está asociada con otro teatro
			return false;
		}
		z.setTeatro(this);
		zonas.add(z);
		z.actLimitaciones();
		return true;
	}
	/**
	 * Funcción que quita una zona del array de zonas
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona
	 */
	public void quitarZona(Zona z) {
		if(zonas.contains(z)==false) {
			return;
		}
		zonas.remove(z);
	}
	/**
	 * Muestra Teatro por pantalla y sus zonas
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarTeatro(){
		int i=0;
		System.out.println(this.nombre);
		for(Zona z : zonas) {
			System.out.print(i + " ");
			z.mostrarZona();
			++i;
		}
	}
	/**
	 * Función que permite seleccionar una zona del array de zonas según su índice pasado como argumento 
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param o entero
	 * @return zona del array de zonas cuyo índice corresponde con (o) o null si ha ocurrido algún error
	 */
	public Zona seleccionarZona(int o) {
		if(o<0) {
			return null;
		}
		if(this.zonas.size()<=o) {
			return null;
		}
		return this.zonas.get(o);
	}
	/**
	 * Constructor de la clase Teatro
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre del teatro
	 * @param limitaciones % de limitación del teatro
	 */
	public Teatro(String nombre, double limitaciones) throws Exception {
		super();
		if(limitaciones<0 || limitaciones>100) { /*si es un % negativo o mayor del 100%*/
			throw new Exception("Parámetros incorrectos");
		}
		Zona.setLimitacion(limitaciones);
		this.nombre = nombre;
		this.limitaciones = limitaciones;
	}
	
}
