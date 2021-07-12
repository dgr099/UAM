package abonos;
import java.io.Serializable;
import java.util.Calendar;

import ui.view.usuario.InfoAbono;

/**
 * Clase que contiene la información general de un abono perteneciente a un usuario
 * 
 * @version		1.0 13 Abr 2021
 * @author 		Daniel Cerrato (daniel.cerrato@estudiante.uam.es)
 *
 */
public class AbonoUsuario implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = -6572814363868808446L;

	/* Entero estatico que guarda el ultimo codigo usado y el numero de abonos creados */
	
	/* Variable que contiene la fecha de caducidad del abono */
	private Calendar caducidad;
	/* Variable que contiene los datos del tipo de abono comprado */
	private Abono abono = null;
	/* Variable que contiene el codigo del abono */
	private String codigo = new String();
	/**
	 * Constructor de la clase AbonoUsuario
	 * 
	 * @param "a" contiene el tipo de abono comprado como clase Abono
	 */
	public AbonoUsuario(Abono a){
		this.abono = a;
		this.setCaducidad();
		codigo=Integer.toUnsignedString( (Abono.getCodigoLast() + 1))  + " " + a.getCodigo();
		Abono.setCodigoLast(Abono.getCodigoLast());
	}

	
	/** 
	 * Metodo para conocer la fecha de caducidad del abono
	 * 
	 * @return Devuelve una fecha de caducidad como Calendar
	 */
	public Calendar getCaducidad(){
		return this.caducidad;
	}
	
	/**
	 * Metodo para poner la fecha de caducidad al abono dependiendo del tipo de abono comprado
	 */
	public void setCaducidad(){
		Calendar c = Calendar.getInstance();
		if(this.abono instanceof AbonoCiclo) {
			this.caducidad = ((AbonoCiclo) abono).getFechaCaducidad();
		}
		else {
			c.add(Calendar.YEAR, 1);
			this.caducidad = c;
		}
	}
	
	/**
	 * Metodo para conseguir el tipo de abono comprado
	 * 
	 * @return Devuelve el tipo de abono comprado como Abono
	 */
	public Abono getAbono(){
		return this.abono;
	}
	
	/**
	 * Metodo para cambiar el abono comprado
	 * 
	 * @param "a" contiene el nuevo abono comprado
	 */
	public void setAbono(Abono a){
		this.abono = a;
		this.setCaducidad();
	}
	
	/**
	 * Metodo para conseguir el codigo del abono
	 * 
	 * @return Devuelve el codigo como String
	 */
	public String getCodigo(){
		return this.codigo;
	}
	
	/**
	 * Metodo para cambiar el codigo del abono
	 * 
	 * @param "c" contiene el nuevo codigo como String
	 */
	public void setCodigo(String c){
		this.codigo = c;
	}
	
	/**
	 * Metodo para comprobar la caducidad del abono
	 * 
	 * @return Devuelve true si no esta caducado; si esta caducado, devuelve false
	 */
	public boolean comprobarCaducidad(){
		Calendar cad = Calendar.getInstance();
		if(cad.after(this.caducidad)) return false;
		return true;
	}
	
	/**
	 * Metodo para mostrar los datos del abono (Para debuggear)
	 */
	public void mostrarAbono(){
		System.out.println("Codigo: " + this.codigo + "\nFecha de caducidad: " + this.caducidad.getTime());
		this.abono.mostrarAbono();
	}
	
	/**
	 * Método para obtener un string descriptivo del abono
	 * @return string descriptivo del abono
	 */
	public String toString() {
		return "Codigo: " + this.codigo + "\nFecha de caducidad: " + this.caducidad.getTime();
		
	}
	
	public void dataAbonoUI(InfoAbono a) {
		a.getCodigo().setText("-Código: " + this.getCodigo());
		a.getCaducidad().setText("-Fecha de caducidad: " + this.getCaducidad().getTime());
		this.abono.dataAbonoUI(a);
	}
	
}
