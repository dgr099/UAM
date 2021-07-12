package evento;

import java.io.Serializable;
import java.util.Calendar;

import entrada.Entrada;
import usuario.Usuario;

public class Comentario implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -4889022982187130734L;
	private String mensaje;
	private Usuario u;
	private Entrada e;
	private Calendar fecha;
	private int num;
	private static int num_t = 0;
	private int mode = 0; /*<- 0 indica que está a espera de aprobarse
	 							1 que se aprobó
	 							2 que fue rechazado
	 							3 solicitó modificacion
	 							4 fue aceptado pero ya no está visible*/
	public Comentario(String m, Usuario u, Entrada e) {
		this.mensaje = m;
		this.u = u;
		this.e = e;
		this.setNum(num_t++);
		this.setFecha(Calendar.getInstance());
	}
	public String getMensaje() {
		return mensaje;
	}
	public void setMensaje(String mensaje) {
		this.mensaje = mensaje;
	}
	public Usuario getU() {
		return u;
	}
	public void setU(Usuario u) {
		this.u = u;
	}
	public Entrada getE() {
		return e;
	}
	public void setE(Entrada e) {
		this.e = e;
	}
	public Calendar getFecha() {
		return fecha;
	}
	public void setFecha(Calendar fecha) {
		this.fecha = fecha;
	}
	public int getNum() {
		return num;
	}
	public void setNum(int num) {
		this.num = num;
	}
	public static int getNumT() {
		return num_t;
	}
	public static void setNumT(int num) {
		num_t = num;
	}
	 @Override
	    public boolean equals(Object o) {
		 if(!(o instanceof Comentario)) {
			 return false;
		 }
		 Comentario c = (Comentario)o;
		 return this.getNum() == c.getNum();
	 }
	 
	 /**
	  * Método para obtener un string descriptivo para el usuario no admin del comentario
	 * @return String descriptivo del comentario
	 */
	public String toStringUsuario() {
		 return this.getMensaje() + " : " + this.getFecha().getTime();
	 }
	
	/**
	 * Método para obtener el modo en el que se encuentra el comentario
	 * @return modo del comentario
	 */
	public int getMode() {
		return this.mode;
	}
	 /*<- 0 indica que está a espera de aprobarse
		1 que se aprobó
		2 que fue rechazado
		3 solicitó modificacion
		4 fue aceptado pero ya no está visible*/
	
	/**
	 * Método para cambiar el modo para indicar que el comentario fue modificado y volver al modo de esperar aprobación
	 */
	public void modificarComentario() {
		this.mode = 0; 
	}
	
	/**
	 * Método para cambiar el modo para ponerlo en modo aceptar comentario
	 */
	public void aprobarComentario() {
		this.mode = 1;
	}
	
	/**
	 * Método para indicar que el comentario fue rechazado y ponerlo en modo 2
	 */
	public void rechazarComentario() {
		this.mode = 2;
	}
	
	/**
	 * Método para establecer el modo en solicitar modificación
	 */
	public void solicitarModificacion() {
		this.mode = 3;
	}
	
	/**
	 * Método para establecer en modo no visible
	 */
	public void setNotVisible() {
		this.mode = 4;
	}
}
