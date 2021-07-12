package entrada;

import java.io.Serializable;
import java.util.Calendar;

import es.uam.eps.padsof.tickets.ITicketInfo;
import es.uam.eps.padsof.tickets.NonExistentFileException;
import es.uam.eps.padsof.tickets.TicketSystem;
import es.uam.eps.padsof.tickets.UnsupportedImageTypeException;
import evento.Comentario;
import evento.Representacion;
import teatro.Butaca;
import teatro.Zona;
import usuario.Usuario;
/**
 * Clase que contiene los métodos y atributos de la clase entrada
 *
 * @version 1.0 26 Mar 21
 * @author David Teófilo Garitagoitia Romero
 */
public abstract class Entrada implements ITicketInfo, Serializable{
	private static final long serialVersionUID = -915490106496385557L;
	private static int ne=0; //numero global de entradas, para hacer códigos
	private String codigo; //codigo de la entrada (único y que no se repite
	private int cod_num=0; //parte numérica del código
	private boolean abono=false; //para saber si se ha empleado un abono para adquirir la entrada
	private Representacion representacion = null; //representacion asociada a la entrada
	private Comentario comentario; //comentario asociado a la entrada
	private int valoracion = -1; //valoración asociada a la entrada
	private Usuario u = null;
	/**
	 * Constructor de la clase entrada
	 *
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param abono Booleano para saber si se ha empleado abono para adquirir la entrada
	 * @param representacion Representación a la que va asociada la entrada
	 */
	public Entrada(boolean abono, Representacion representacion) {
		this.codigo = Integer.toString(++ne);
		this.cod_num = ne;
		this.abono = abono;
		this.representacion = representacion;
		if(representacion == null) { /*si no está asignada a ninguna representacion*/
			codigo +='?'; /*para identificar entradas que aun no tienen asignadas eventos/errores varios*/
			return;
		}
		else {
			if(this.representacion.getEvento()!=null && this.representacion.getEvento().getTitulo()!=null)
				codigo+=this.getRepresentacion().getEvento().getTitulo().charAt(0); /*le añadimos el 1º caracter del evento*/
		}
		if(representacion.getEntradas().contains(this)){
			return;
		}
	}

	/**
	 * Método para obtener el número de entradas 
	 * (valor estático empleado para la generación del código así que necesario para save y load)
	 * @return entero con el número de entradas
	 */
	public static int getNumeroEntrdas(){
		return ne;
	}

	/**
	 * Método para establecer el número de entradas
	 * @param a entero con el número de entradas
	 */
	public static void setNumeroEntradas(int a){
		Entrada.ne = a;
	}
	
	/**Función para comprobar si la entrada es válida para la representación
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param r Representacion para la que se quiere comprobar si es válida la entrada
	 * @return True si es válida, false en caso contrario
	 */
	public abstract boolean comprobarValidez(Representacion r);
	/**Función para obtener la zona a la que está asociada una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Zona de la entrada
	 */
	public abstract Zona getZona();
	
	/**
	 * Método para obtener un string descriptivo de la posición
	 * @return string descriptivo de la posición
	 */
	public abstract String getPosicion();
	/**
	 * Función para obtener el código de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Cofigo de la entrada
	 */
	public String getCodigo() {
		return codigo;
	}

	/**
	 * Función para establecer el codigo de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param codigo codigo a establecer en la entrada
	 */
	public void setCodigo(String codigo) {
		this.codigo = codigo;
	}

	/**
	 * Función para obtener la representación de la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Representación asociada a la entrada
	 */
	public Representacion getRepresentacion() {
		return representacion;
	}

	/**
	 * Función para establecer la representación de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param representacion Representación que se quiere establecer en la entrada
	 */
	public void setRepresentacion(Representacion representacion) {
		if(this.comprobarValidez(representacion)==false) {
			return;
		}
		this.representacion = representacion;
	}

	/**
	 * Función para conocer si fue empleado un abono para adquirir la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return True en caso de haber empleado abono, false en caso contrario
	 */
	public boolean isAbono() {
		return abono;
	}

	/**
	 * Función para establecer que se empleo o no un abono para aquirir la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param abono booleano que definirá si se empleo o no un abono
	 */
	public void setAbono(boolean abono) {
		this.abono = abono;
	}
	
	/**
	 * Función para obtener si se empleo un abono para la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return booleano que definirá el uso o no de abono
	 */
	public boolean getAbono() {
		return this.abono;
	}
	
	/**
	 * Función para obtener el precio de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return precio de la entrada
	 */
	public double getPrecio() {
		if(this.representacion==null) {
			return -1; /*como control de errores, si no tiene representación asignada devolverá -1*/
		}
		return this.representacion.getEvento().getPrecio(this.getZona());
	}
	
	/**
	 * Función para obtener el id (codigo numérico) de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return codigo numérico de la entrada
	 */
	public int getIdTicket () { 
		return this.cod_num; 
	}
	
	/**
	 * Función para obtener el nombre del teatro al que está asociada la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Nombre del teatro
	 */
	public String getTheaterName () {
		if(this.getZona()==null){
			return "Sin zona ni teatro asignado";
		}
		if(this.getZona().getTeatro()==null) {
			return "No teatro";
		}
		if(this.getZona().getTeatro().getNombre()==null) {
			return "No hay nombre de teatro";
		}
		return this.getZona().getTeatro().getNombre();
	}
	

	/**
	 *Función para obtener el nombre del evento al que está asociada la entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Nombre del evento de la entrada
	 */
	public String getEventName () {
		if(this.representacion==null){
			return "No evento ni representacion";
		}
    	if(this.representacion.getEvento() == null) {
    		return "No evento";
    	}
    	return this.representacion.getEvento().getTitulo(); 
    }
    
    /**
     *Función para obtener la fecha de la representacion de una entrada
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return String descriptivo de la fecha de la representacion de la entrada
     */
    public String getEventDate () {
    	if(this.representacion==null || this.representacion.getFechaYHora()==null) {
    		return "No evento";
    	}
    	return this.representacion.getFechaYHora().getTime().toString(); 
    }
    
	/**
	 * Función para imprimir la entrada en formato pdf
	 * @version 1.0 26 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @throws NonExistentFileException
	 * @throws UnsupportedImageTypeException
	 */
	public void generarPDF() throws NonExistentFileException, UnsupportedImageTypeException{
		TicketSystem.createTicket(this, "./tickets/");
	}
	
	/**
	 * Función que retorna la butaca a la que está asociada una entrada, por defecto ninguna
	 * @return Butaca butaca a la que está asociada la entrada
	 */
	public Butaca getButaca() {
		return null;
	}

	/**
	 * Método para obtener el comentario asociado a la entrada
	 * @return  comentario
	 */
	public Comentario getComentario() {
		return comentario;
	}

	/**
	 * Método para establecer el comentario de la entrada
	 * @param comentario string con el comentario de la entrada
	 */
	public void setComentario(String comentario) {
		if(this.getRepresentacion().getFechaYHora().after(Calendar.getInstance())) { /*si aún no ha tenido lugar el evento no se permite añadir comentarios*/
			return;
		}
		if(comentario==null) {
			return;
		}
		if(this.comentario!=null) { /*si ya había un comentario antes, primero se borra el anterior*/
			this.borrarComentario();
		}
		this.comentario = new Comentario(comentario, this.getUsuario(), this);
		this.comentario.modificarComentario(); /*se pone en estado de modificado*/
		this.representacion.getEvento().addComentario(this.comentario);
	}
	
	/**
	 * Método para borrar el comentario asociado a una entrada y por tanto del evento de la misma
	 */
	public void borrarComentario() {
		if(this.comentario==null) {
			return;
		}
		this.representacion.getEvento().borrarComentario(this.comentario);
		this.comentario=null;
	}

	/**
	 * Método para obtener la valoración de la entrada (que se asignará como valoración del evento de la entrada)
	 * @return int con la valoración
	 */
	public int getValoracion() {
		return valoracion;
	}

	/**
	 * Método para añadir valoración a la entrada
	 * @param n entero con válores del 0 al 5 para definir la valoración
	 * @return booleano para indicar si la operación se realizó correctamente
	 */
	public boolean addValoracion(int n) {
		if(this.getRepresentacion()==null) {
			return false;
		}
		int aux = this.getValoracion();
		if(aux==-1) {
			if(this.getRepresentacion().getEvento().addValoracion(n)==false) {
				return false;
			}
		}
		// a la suma de puntuaciones le restamos la anterior
		else{
			this.getRepresentacion().getEvento().setSumPuntuaciones(this.getRepresentacion().getEvento().getSumPuntuaciones() - aux);
			this.getRepresentacion().getEvento().getPuntuaciones().remove(this.getRepresentacion().getEvento().getPuntuaciones().indexOf(aux)); //quitamos el valor de la lista
			if(this.getRepresentacion().getEvento().addValoracion(n) == false) { //si no somos capaces de añadir la valoración pasada por argumento
				this.getRepresentacion().getEvento().addValoracion(aux); //volvemos a poner la anterior 
				return false; //retornamos false para que se sepa que ha ocurrido un error
			}
		}
		/*si en cambio se pudo añadir bien se cambia el valor actual de la valoración*/
		this.valoracion = n;
		return true;
	}
	public void setUsuario(Usuario u) {
		this.u = u;
	}
	public Usuario getUsuario() {
		return this.u;
	}
	
}
