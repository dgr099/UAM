package reserva;

import java.io.Serializable;
import java.util.Calendar;

import evento.Representacion;
import sistema.Sistema;
import teatro.Butaca;

/**
 * Clase que contiene la informacion de una reserva
 * 
 * @version 	14 Abr 2021
 * @author		David Teófilo Garitagoitia Romero
 */
public class Reserva implements Serializable{

	/* Entero estatico que contiene la version para la serializacion */
	private static final long serialVersionUID = -5078177152515566443L;

	/* String que contiene el codigo de la reserva */
	private String cod = null;
	/* */
	static int num = 0;
	static long msDay = (1000*60*60*24); //86,400,000
	private Calendar cad = null;
	private Butaca butaca = null;
	private Representacion reserva = null;
	
	/**
	 * Constructor de la clase
	 * @param r representación que se desea reservar
	 * @param b butaca de la representación que se desea reservar
	 * @throws Exception
	 */
	public Reserva(Representacion r, Butaca b) throws Exception {
		this.cod = new String();
		this.cod+=Integer.toString(++num);
		if(r==null) {
			return;
		}
		if(r.getPd()==null){
			throw new Exception("No existe política de reserva");
		}
		//System.out.println(r.getFechaYHora().getTime());
		//System.out.println(Calendar.getInstance().getTime());
		long msres = r.getFechaYHora().getTimeInMillis() - Calendar.getInstance().getTimeInMillis();
		double diasRestantes = (1.0/msDay*(msres));
		
		if(diasRestantes<=0) {/*si no quedan días o ya paso la reunión*/
			throw new Exception("Representación pasada");
		}
		if(r.getPd().getLim() > diasRestantes) {/*si los días de diferencia entre la fecha de la repre y hoy son menos que el limite*/
			throw new Exception("Límite pasado");
		}

		if(b!=null) { /*si le pasas correctamente la butaca*/
			if(r.getButacasOcupadas().contains(b)==true) {  /*si ya está siendo ocupada por alguien*/
				throw new Exception("Butaca ya ocupada");
			}
			r.getButacasOcupadas().add(b); /*añades la butaca a la lista de butacas ocupadas*/
		}
		this.reserva = r;
		if(r.getEvento().getTitulo()!=null){
			this.cod += r.getEvento().getTitulo().charAt(0);
		}
		else this.cod += "?";
		this.cod += "R";
		this.butaca=b;
		this.cad = Calendar.getInstance();
		this.cad.set(this.cad.get(Calendar.YEAR), this.cad.get(Calendar.MONTH), this.cad.get(Calendar.DAY_OF_MONTH) + r.getPd().getDur());
	}
	public static int getNumeroReservas(){
		return num;
	}
	public static void setNumeroReservas(int a){
		num = a;
	}
	public String getCodigo() {
		return this.cod;
	}
	
	/**
	 * Método para liberar una bútaca reservada
	 * @return booleano que describe si la operación ha sido realizada con o sin éxito
	 */
	public boolean liberarButaca() {
		if(this.butaca==null) {
			return true;
		}
		if(this.reserva.getButacasOcupadas().contains(this.butaca)==false) {
			return true;
		}
		this.reserva.getButacasOcupadas().remove(this.butaca);
		this.cad=Calendar.getInstance();
		this.cad.set(Calendar.YEAR, 0); /*se pone como caducada para avisar al resto de usuarios en notificacion, en notificación se elimina la reserva etc*/
		Sistema.getInstancia().notificarUsuarios();
		return true;
		
	}
	
	/**
	 * Método para liberar una bútaca reservada solo que sin llamar a notificar para evitar recursividad
	 * @return booleano que describe si la operación ha sido realizada con o sin éxito
	 */
	public boolean liberarButaca2() {
		if(this.butaca==null) {
			return true;
		}
		if(this.reserva.getButacasOcupadas().contains(this.butaca)==false) {
			return true;
		}
		this.reserva.getButacasOcupadas().remove(this.butaca);
		this.cad=Calendar.getInstance();
		this.cad.set(Calendar.YEAR, 0); /*se pone como caducada para avisar al resto de usuarios en notificacion, en notificación se elimina la reserva etc*/
		return true;
		
	}
	/**
	 * Método para establecer la butaca de una reserva
	 * @param b buttaca a reservar
	 * @return
	 */
	public boolean setButaca(Butaca b) {
		if(b==null) {
			return true;
		}
		if(this.reserva==null) {
			this.butaca=b;
			return true;
		}
		if(this.reserva.getButacasOcupadas().contains(b)==true) {
			return false;
		}
		if(this.butaca!=null) { //si tenía antes asignada una butaca, la liberas
			this.liberarButaca();
		}
		this.butaca=b;
		this.reserva.getButacasOcupadas().add(b);
		return true;
	}
	public Calendar getCad() {
		return this.cad;
	}
	public Representacion getRepresentacion() {
		return this.reserva;
	}
	public Butaca getButaca() {
		return this.butaca;
	}
}
