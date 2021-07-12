package abonos;

import entrada.Entrada;
import evento.Evento;
import teatro.*;
import ui.view.usuario.InfoAbono;

import java.io.Serializable;

import java.util.List;

/**
 * Clase abstracta que contiene la información general de un abono
 * 
 * @version		1.0 13 Abr 2021
 * @author 		Daniel Cerrato (daniel.cerrato@estudiante.uam.es)
 *
 */
public abstract class Abono implements Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 8132645912028391529L;
	/* String que contiene el codigo del abono */
	private String codigo;
	/* Valor real que contiene el precio del abono */
	private double precio;
	/* Zona en la que se podra usar el abono */
	public Zona zona;

	private static int codigo_last=0;

	public static int getCodigoLast(){
		return codigo_last;
	}

	public static void setCodigoLast(int a){
		codigo_last = a;
	}
	
	/**
	 * Constructor de la clase Abono
	 * 
	 * @param "c" contiene el codigo del abono como String
	 * @param "p" contiene el precio del abono como Double
	 * @param "z" contiene la zona en la que se podra usar el abono
	 * 
	 * @throws Exception si la zona obtenida es nula
	 */
	public Abono(String c, double p, Zona z) throws Exception {
		if(z == null) throw new Exception("Zona nula");
		this.precio = p;
		this.zona = z;
		this.codigo = c;
	}

	/**
	 * Metodo abstracto para comprobar la validez del abono a la hora de comprar una entrada
	 * 
	 * @param "e" contiene la entrada que se quiere comprar
	 * 
	 * @return Devuelve true si es posible comprar la entrada, sino devuelve false
	 */
	public abstract boolean comprobarValidez(Entrada e);
	
	/**
	 * Metodo abstracto para comprobar la validez del abono para un evento
	 * 
	 * @param "e" evento del que se quiere comprobar la validez
	 * 
	 * @return Devuelve true si es posible comprar entrada para el vento, sino devuelve false
	 */
	public abstract boolean comprobarValidez(Evento e);
	
	/**
	 * Metodo abstracto para generar un codigo para el abono
	 * 
	 * @return Devuelve un codigo como String
	 */
	public abstract String generarCodigo();
	
	/**
	 * Metodo para obtener el codigo del abono
	 * 
	 * @return Devuelve el codigo del abono como String
	 */
	public String getCodigo(){
		return this.codigo;
	}
	
	/**
	 * Metodo para cambiar el codigo del abono
	 * 
	 * @param "c" contiene el nuevo codigo del abono
	 */
	public void setCodigo(String c){
		this.codigo = c;
	}
	
	/**
	 * Metodo para obtener el precio del abono
	 * 
	 * @return Devuelve el precio del abono como Double
	 */
	public double getPrecio(){
		return this.precio;
	}
	
	/**
	 * Metodo para cambiar el precio del abono
	 * 
	 * @param "p" contiene el nuevo precio del abono
	 */
	public void setPrecio(double p){
		this.precio = p;
	}
	
	/**
	 * Metodo para obtener la zona donde se podra usar el abono
	 * 
	 * @return Devuelve la zona como Zona
	 */
	public Zona getZona(){
		return this.zona;
	}
	
	/**
	 * Metodo para cambiar la zona donde se podra usar el abono
	 * 
	 * @param "z" contiene la nueva zona como Zona
	 */
	public void setZona(Zona z){
		this.zona = z;
	}

	/**
	 * Metodo para mostrar la informacion del abono (Para debuggear)
	 */
	public void mostrarAbono(){
		System.out.println("Codigo: " + this.codigo + ", Precio: " + this.precio);
		this.zona.mostrarZona(); 
	}
	
	/**
	 * @author David Teófilo Garitagoitia Romero
	 * @param a InfoAbono (panel gráfico en el cual realizar los cambios)
	 */
	public abstract void dataAbonoUI(InfoAbono a);
	
	/**
	 * Método para obtener la lista de eventos del abono
	 * @return lista de eventos, si es un abono anual se retorna null
	 */
	public abstract List<Evento> getEventos();
	/**
	 * Método para obtener la valoración de un abono
	 * @return -2 si se trata de un abono anual y -1 no tiene valoracion, en caso contrario retorna la valoracion del abono
	 */
	public abstract double getValoracion();
	
	/**
	 * Método para obtener el ciclo de un ciclo
	 * @return Ciclo del abono, null si no hay ciclo
	 */
	public Ciclo getCiclo() {
		return null;
	}
}
