package usuario;

import java.io.Serializable;
import java.util.Calendar;

/**
 * Clase para trabajar con las notificaciones
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Notificacion implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 6919020040779045181L;
	private String mensaje;
	private Calendar fecha;
	public Notificacion(String m) {
		this.mensaje = m;
		this.fecha = Calendar.getInstance();
	}
	public String getMensaje() {
		return mensaje;
	}
	public void setMensaje(String mensaje) {
		this.mensaje = mensaje;
	}
	public Calendar getFecha() {
		return fecha;
	}
	public void setFecha(Calendar fecha) {
		this.fecha = fecha;
	}
	
}
