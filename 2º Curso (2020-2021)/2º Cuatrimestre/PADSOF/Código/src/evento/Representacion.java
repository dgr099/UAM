package evento;
import java.io.Serializable;
import java.util.*;

import entrada.Entrada;
import entrada.EntradaButaca;
import reserva.PolíticaDeReseva;
import sistema.Sistema;
import teatro.Butaca;
import teatro.Zona;
import usuario.Usuario;

/**
 * Clase con la información y métodos relativo a las representaciones
 * @version 1.0 31 Mar 21
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Representacion implements Comparable<Representacion>, Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 3224187703207406179L;
	private Calendar fechaYHora; //fecha y hora de la representacion
	private int asistencia = 0; //asistencia de la representación
	private int aforo; //aforo (capacidad máxima de personas de la representacion)
	private Evento evento; //evento asociado a la representacion
	private List<Entrada> entradas = new ArrayList<Entrada>(); /*lista de entradas de la representacion*/
	private List<Butaca> butacasOcupadas = new ArrayList<Butaca>(); /*lista de las butacas ocupadas y por tanto no disponibles*/
	private Map<Zona, Integer> ocupacion = new TreeMap<Zona, Integer>(); /*para comprobar que no se exceda la ocupacion*/
	private PolíticaDeReseva pd = null; //politica de reserva para la representacion
	private List<Usuario> listaDeEspera = new ArrayList<Usuario>(); //usuarios en lista de espera, esperando que se cancelen reservas para tener hueco	
	/**
	 * Función para obtener la lista de usuarios en espera
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return lista de espera de la representacion
	 */
	public List<Usuario> getLista() {
		return this.listaDeEspera;
	}
	/**
	 * Función para añadir a la lista de espera
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param u usuario a añadir a la lista de espera
	 */
	public void addLista(Usuario u) {
		if(u==null) {
			return;
		}
		if(this.listaDeEspera.contains(u)) {
			return;
		}
		this.listaDeEspera.add(u);
		return;
	}
	
	/**
	 * Método para cancelar una representación
	 */
	public void cancelarRepresentacion() {
		this.getEvento().getRepresentaciones().remove(this);
		for(Usuario u : Sistema.getInstancia().getUsuarios()) {
			for(Entrada e : this.getEntradas()) {
				if(u.getEntradas().contains(e)) { /*si el usuario tiene alguna entrada de la representacion*/
					u.addNotificacion("La representación del evento " + this.getEvento().getTitulo() + " en la fecha " + 
				this.getFechaYHora().getTime()+ "\nFue Cancelada\nPase por taquilla para la devolución de su dinero"); /*se le notifica*/
					u.getEntradas().remove(e); /*se elimina esa entrada*/
				}
			}
		}
	}
	
	/**
	 * Método para cambiar la fecha de una representancion y notificar a los usuarios
	 * @param d Nueva fecha para la representacion
	 */
	public void cambiarFecha(Calendar d) {
		if(Calendar.getInstance().getTime().after(d.getTime())) { /*no se puede cambiar la fecha a una pasada*/
			return;
		}
		Calendar aux = this.fechaYHora;
		this.fechaYHora = d;
		for(Usuario u : Sistema.getInstancia().getUsuarios()) {
			for(Entrada e : this.getEntradas()) {
				if(u.getEntradas().contains(e)) { /*si el usuario tiene alguna entrada de la representacion*/
					u.addNotificacion("La representación del evento " + this.getEvento().getTitulo() + " en la fecha " + 
				aux.getTime() + "\nCambio su fecha a " + d.getTime()); /*se le notifica a los usuarios del cambio de fecha*/
				}
			}
		}
	}

	/**
	 * Función para sacar de la lista de espera
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param u usuario a sacar de la lista
	 */
	public void salirLista(Usuario u) {
		if(u==null) {
			return;
		}
		if(this.listaDeEspera.contains(u)) {
			this.listaDeEspera.remove(u);
		}
	}
	/**
	 * Constructor de la clase representación
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param fechaYHora fecha y hora de la representacion
	 * @param aforo entero del aforo
	 */
	public Representacion(Calendar fechaYHora, int aforo) {
		this.fechaYHora = fechaYHora;
		this.aforo = aforo;
	}
	
	/**
	 * Constructor de la clase de representacion
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param fechaYHora tiempo en el que tiene lugar la representación 
	 * @param aforo aforo de la representacion
	 * @param pd politica de reservas de la representación
	 */
	public Representacion(Calendar fechaYHora, int aforo, PolíticaDeReseva pd) {
		this.fechaYHora = fechaYHora;
		this.aforo = aforo;
		this.pd = pd;
	}
	
	/**
	 * Función para obtener la política de reserva de una representación
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return política de reserva de la representación
	 */
	public PolíticaDeReseva getPd() {
		return pd;
	}
	
	/**
	 * Función para establecer los actores de la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param pd política de reserva a establecer
	 */
	public void setPd(PolíticaDeReseva pd) {
		this.pd = pd;
	}
	
	/**
	 * Función para obtener el evento asociado a la representación
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return
	 */
	public Evento getEvento() {
		return evento;
	}

	/**
	 * Función para establecer el evento asociado a una representación
	 * @version 1.0 4 Abr 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param evento evento que se quiere ligar a la representacion
	 */
	public void setEvento(Evento evento) {
		this.evento = evento;
	}

	/**
	 * Función para obtener la lista de entradas de la representación
	 * @version 1.0 4 Abr 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return
	 */
	public List<Entrada> getEntradas() {
		return entradas;
	}

	public void setEntradas(List<Entrada> entradas) {
		this.entradas = entradas;
	}

	public Calendar getFechaYHora() {
		return fechaYHora;
	}
	public void setFechaYHora(Calendar fechaYHora) {
		this.fechaYHora = fechaYHora;
	}
	public int getAsistencia() {
		return asistencia;
	}
	public void setAsistencia(int asistencia) {
		this.asistencia = asistencia;
	}
	public int getAforo() {
		return aforo;
	}
	public void setAforo(int aforo) {
		this.aforo = aforo;
	}
	/**
	 * Método para obtener las estadísticas del evento
	 * @return Un array de double en el que cada posición corresponder a un valor estadístico:
	 * 	la posición 0 para la gente que acudió con entrada comprada sin emplear abono, 
	 * 	la posición 1 para el número total de personas que acudieron al evento
	 * 	la posición 2 para el número total de personas que emplearon un abono
	 * 	la posición 3 para la recaudación total del evento
	 */
	public double[]  getEstadisticas() {
		double estadisticas[] = {0, 0, 0, 0};
		int abonos=0;
		double recaudacion=0;
		estadisticas[0] = entradas.size();
		for(Entrada ent: entradas) {
			if(ent.getAbono()) {
				abonos++;
			}
			else {
				recaudacion+=ent.getPrecio();
			}
		}
		estadisticas[1] = entradas.size(); /*la asistencia total es el número de entradas, los abonos tambien generan entradas, esto es asistencia total*/
		estadisticas[2] = abonos; /*el numero de entradas que provienen de abono*/
		estadisticas[0] = estadisticas[1] - estadisticas[2]; /*gente que fue con entrada*/
		estadisticas[3] = recaudacion; /*la suma de importes de la entrada que no emplearon abono*/
		return estadisticas;
	}
	
	/**
	 * Método para añadir una entrada a una representación
	 * @param e La entrada que se desea añadir
	 * @return True en caso de realizarse con éxito, false en caso contrario
	 */
	public boolean addEntrada(Entrada e) {
		if(e.getRepresentacion()!=null && e.getRepresentacion()!=this) { /*si la entrada es de otra representación*/
			return false;
		}
		if(this.entradas.contains(e)==true) { /*si la entrada ya esta en la lista de entradas*/
			return true;
		}
		try {
			if(comprobarValidezEntrada(e)==false) { /*comprobar validez se encarga de ver si es válida y en caso de serlo actualizar la ocupacion*/
				return false;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			return false; /*si hay alguna excepción devuelve false para que se sepa que no se pudo completar la operación*/
		}
		/**si es la entrada es correcta y no estaba anteriormente */
		this.entradas.add(e); /*añades la entrada a la lista de entrada*/
		if(e.getRepresentacion()==null) { /*si no se había asignado representacion en el constructor*/
			e.setRepresentacion(this); /*se le asigna está representacion a la entrada*/
		}
		/*si todo es correcto incrementas la asistencia*/
		if(this.ocupacion.containsKey(e.getZona())==true) {
			this.ocupacion.put(e.getZona(), this.ocupacion.get(e.getZona()) + 1); /*si la zona ya estaba en el mapa la incrementas*/
		}
		else
			this.ocupacion.put(e.getZona(), 1); /*si no estaba, la inicias a 1*/
		if(e instanceof EntradaButaca) { /*si es de las de butaca añades la butaca a la lista de butacas ocupadas*/
			if(this.butacasOcupadas.contains(((EntradaButaca)e).getButaca())==false) { /*si la butaca que quieres añadir no estaba*/
				this.butacasOcupadas.add(((EntradaButaca)e).getButaca());
			}
		}
		this.asistencia++;
		return true;
	}
	
	/**
	 * Método para debugeo
	 */
	public void mostrarRepresentacion() {
		System.out.print(/*this.evento.getTitulo() + " " + this.evento.getDescripcion() + */"Disponibilidad: " + (this.aforo - this.asistencia) + " Fecha: " + this.getFechaYHora().getTime());
	}
	
	/**
	 * Método para comprobar la validez de una entrada para la representación
	 * @param e Entrada para que se desea conocer la validez
	 * @return true en caso de ser válida, false en caso contrario
	 * @throws Exception
	 */
	public boolean comprobarValidezEntrada(Entrada e) throws Exception {
		if(e==null) { /*si no hay entrada*/
			return false;
		}
		/*si la representacion ya está llena*/
		if(this.asistencia == this.aforo){
			throw new Exception("La representación está llena");
		}
		if(this.evento.getPrecio(e.getZona())==-1) { /*antes de añadir una entrada hay que asegurarse de tener el precio de esa zona para el evento*/
			return false;
		}
		return e.comprobarValidez(this);
	}

	public List<Butaca> getButacasOcupadas() {
		return butacasOcupadas;
	}

	public Map<Zona, Integer> getOcupacion() {
		return ocupacion;
	}
	@Override
	public int compareTo(Representacion arg0) {
		return(this.getFechaYHora().compareTo(arg0.getFechaYHora()));
	}
	
	/**
	 * Método para comprobar la disponibilidad de una zona
	 * @param z Zona en la que se desea comprobar la disponibilidad
	 * @return booleano que define la disponibilidad de la zona
	 */
	public boolean comprobarDisponibilidad(Zona z) {
		double perc = 100 - Zona.getLimitacion();
		int max = -1;
		if(z!=null) {
			max = (int)(z.getMax() * perc/100.0);
		}
		if(this.getAsistencia()==this.getAforo()){ /*si se ha cumplido el tope del representacion*/
			return false;
		}
		/*si la zona está en el mapa*/
		if(z!=null)
			if(this.getOcupacion().containsKey(z)==true){ /*si contiene la zona de la entrada*/
				if(this.getOcupacion().get(z) >=  max) { /*si esa zona ya esta ocupada al máximo contando con las límitaciones*/
					return false;
				}
				return true;
			}
		if(0 == max) { /*si no puede estar nadie en la zona*/
			return false;
		}
		if(this.evento.getPrecio(z)==-1) { //si no está asignado el precio para la zona
			return false;
		}
		return true;
	}
	
}
