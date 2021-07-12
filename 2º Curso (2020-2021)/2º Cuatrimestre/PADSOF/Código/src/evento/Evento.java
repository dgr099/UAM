package evento;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import evento.Comentario;
import teatro.Zona;
/**
 * Clase que contiene la información y métodos de evento
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 *
 */
public abstract class Evento implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -1312263816916875171L;
	private String descripcion;
	private double duracion;
	private String titulo;
	private String autor;
	private Map<Zona, Double> precioZonas = new TreeMap<Zona, Double>(); /*A cada zona le asigno un precio*/
	private List<Representacion> representaciones = new ArrayList<Representacion>();
	private Set<Comentario> comentariosNoVisibles = new HashSet<Comentario>(); /*comentarios que ya han pasado su periodo de vigencia*/
	private Set<Comentario> comentariosEnEsperaDeAprobación = new HashSet<Comentario>(); /*comentarios en espera de que el admin los apruebe*/
	private Set<Comentario> comentariosVisibles = new HashSet<Comentario>(); /*comentarios Visibles*/
	private List<Integer> puntuaciones = new ArrayList<Integer>(); /*lista de puntuaciones recibidas*/
	private int sumPuntuaciones = 0; /*para que sea más facil sacar la media*/
	
	/**
	 * Constructor de la clase evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param descripcion descripción del evento
	 * @param duracion duración en minutos del evento
	 * @param titulo título del evento
	 * @param autor autor del evento
	 */
	public Evento(String descripcion, double duracion, String titulo, String autor) {
		super();
		this.descripcion = descripcion;
		this.duracion = duracion;
		this.titulo = titulo;
		this.autor = autor;
	}
	/**
	 * Método para añadir comentarios a un evento (se añaden a la lista de comentarios a aprobar por el admin)
	 * @param c comentario a añadir
	 */
	public void addComentario(Comentario c) {
		if(c!=null && !this.comentariosNoVisibles.contains(c) && !this.comentariosVisibles.contains(c)) {
			comentariosEnEsperaDeAprobación.add(c); /*se añade a los comentarios en espera de aprobación para que el admin los apruebe*/
		}
	}

	/**
	 * Método para añadir una valoración al evento
	 * @param n numero de estrellas a añadir
	 * @return booleano que define si se ejecutó correctamente
	 */
	public boolean addValoracion(int n) {
		if(n<0 || n>5) { /*no pueden tener valoraciones negativas o de más de 5 estrellas*/
			return false;
		}
		puntuaciones.add(n);
		this.sumPuntuaciones += n; /*se añade la valoración a la suma total*/
		return true;
	}
	
	/**
	 * Método para obtener la valoración de un evento
	 * @return número con decimales ce estrellas para la valoración
	 */
	public double getValoracion() {
		if(this.puntuaciones.size()<=0) {
			return -1;
		}
		return (this.sumPuntuaciones*1.0)/this.puntuaciones.size();
	}
	
	/**
	 * String con la valoración
	 * @return string que describe la valoración
	 */
	public String getValorString() {
		double aux = this.getValoracion();
		if(aux==-1) {
			return "Sin Valoracion";
		}
		return String.valueOf(aux);
	}
	/**
	 * Método para quitar los comentarios que lleven más del tiempo debido en visibles
	 */
	public void updateComentariosVisibles() {
		Set<Comentario> comentariosPasados = new HashSet<Comentario>();
		for(Comentario c : this.comentariosVisibles) {
			Representacion r = c.getE().getRepresentacion();
			Calendar limit = Calendar.getInstance();
			limit.setTime(r.getFechaYHora().getTime());
			limit.add(Calendar.MONTH, 12);
			if (Calendar.getInstance().after(limit)) {
				comentariosPasados.add(c);
			}
		}
		this.comentariosVisibles.removeAll(comentariosPasados); /*todos los comentarios pasados los quitamos de visibles*/
		this.comentariosNoVisibles.addAll(comentariosPasados); /*los movemos a pasados*/
	}
	/**
	 * Función para obtener el mapa que relaciona las zonas con su precio
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Mapa que relaciona la zona con su precio
	 */
	public Map<Zona, Double> getPrecioZonas() {
		return precioZonas;
	}
	/**
	 * Función para obtener el precio de una zona
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona de la que se desea conocer el precio
	 * @return precio de la zona en cuestión
	 */
	public double getPrecio(Zona z) {
		if(z==null) {
			return -1;
		}
		if(precioZonas.containsKey(z)){
			return precioZonas.get(z);
		}
		return -1; /*si no tiene esa zona retornará -1 como error*/
	}
	
	/**
	 * Función para establecer el mapa que relaciona el precio y las zonas
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param precioZonas mapa a establecer en el evento
	 */
	public void setPrecioZonas(Map<Zona, Double> precioZonas) {
		this.precioZonas = precioZonas;
	}
	
	/**
	 * Función para mostrar evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * Función auxiliar para mostrar el evento (debugeo)
	 */
	public void mostrarEventoAux() {
		System.out.print(this.titulo + " " + "Duración: " + this.getDuracion());
	}
	
	/**
	 * Función para obtener la descripción del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return String descriptivo del evento
	 */
	public String getDescripcion() {
		return descripcion;
	}
	
	/**
	 * Función para establecer la descripción del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param descripcion descripción a establecer en el evento
	 */
	public void setDescripcion(String descripcion) {
		this.descripcion = descripcion;
	}
	
	/**
	 * Función para obtener la duración del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return duración en minutos del evento
	 */
	public double getDuracion() {
		return duracion;
	}
	
	/**
	 * Método para establecer la duración del evento
	 * @param duracion número con decimales para indicar la duración del evento
	 * @return booleano para indicar si se pudo realizar correctamente la operación
	 */
	public boolean setDuracion(double duracion) {
		if(duracion<=0) { /*comprobación para que siempre la duración se positiva y mayor que 0*/
			return false;
		}
		this.duracion = duracion;
		return true;
	}
	
	/**
	 * Función para obtener el titulo del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return título del evento
	 */
	public String getTitulo() {
		return titulo;
	}
	
	/**
	 * Función para establecer el titulo del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param titulo título a establecer en el evento
	 */
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	
	/**
	 * Función para obtener el autor de un evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre del autor del evento
	 */
	public String getAutor() {
		return autor;
	}
	
	/**
	 * Función para establecer el autor de un evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param autor autor a establecer en el evento
	 */
	public void setAutor(String autor) {
		this.autor = autor;
	}
	
	/**
	 * Función para obtener las representaciones del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return
	 */
	public List<Representacion> getRepresentaciones() {
		return representaciones;
	}
	
	/**
	 * Función para establecer las representaciones de un evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param representaciones representaciones del evento que se pretenden establecer
	 */
	public void setRepresentaciones(List<Representacion> representaciones) {
		this.representaciones = representaciones;
	}
	
	/**
	 * Función para añadir una representación a un evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param r representación añadir en el evento
	 * @return
	 */
	public boolean addRepresentacion(Representacion r) {
		if(this.representaciones.contains(r)) { /*si ya contiene esa representacion*/
			return false;
		}
		this.representaciones.add(r);
		r.setEvento(this);
		return true;
	}
	
	/**
	 * Función mostrar evento (debug)
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero 
	 */
	public abstract void mostrarEvento();
	
	/**
	 * Función para mostrar la pantalla de compra (Debugeo)
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarPantallaCompra() {
		System.out.print(this.getTitulo() + " " + this.getDescripcion());
	}
	
	/**
	 * Función para obtener las estadísticas del evento
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return en el 0 del double se guarda la gente que empleo entradas,
	 * 		   en el 1 la asistencia total, 
	 * 		   en el 2 los abonos empleados
	 * 		   en el 3 se guardan los beneficios netos de las entradas
	 * 		   en el 4 se guarda la valoración del evento
	 */
	public double[] getEstadisticas() {
		double est_evento[] = new double[5];
		double est_repr[];
		if(this.representaciones.size()<=0) {
			est_evento[4] = -1;
		}
		for(Representacion r : this.representaciones) {
			est_repr=r.getEstadisticas();
			for(int i=0; i!=4; i++) {
				est_evento[i] += est_repr[i];
			}
			est_evento[4] = this.getValoracion();
		}
		return est_evento;
	}
	
	/**
	 * Función para mostrar la pantalla del admin (debug)
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarPantallaAdmin() {
		double est[] = this.getEstadisticas();
		System.out.print(this.getTitulo() + " Estadísticas ->"+ " Asistencia: " + est[1] + " Abonos: " + est[2] + " Recaudación: " + est[3]);
	}
	
	/**
	 * Función para establecer el precio de una zona
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona en la que se quiere establecer un precio
	 * @param d precio a establecer en la zona
	 * @return booleano para indicar si la acción se realizó o no con éxito
	 */
	public boolean addPrecioZona(Zona z, double d) {
		if(d<=0) {
			return false;
		}
		if(z==null) {
			return false;
		}
		this.precioZonas.put(z, d);
		return true;
	}
	
	/**
	 * Función de debugeo para mostrar las representaciones
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarRepresentaciones() {
		mostrarEvento();
		int i=1;
		System.out.println("Representaciones: ");
		for(Representacion r : this.representaciones) {
			System.out.print(i + ") ");
			r.mostrarRepresentacion();
			System.out.println("");
			++i;
		}
	}
	
	/**
	 * Método para obtener un string descriptivo del evento
	 * @return String descriptivo del evento
	 */
	public String toString() {
		return this.titulo;
	}
	/*métodos get and set*/
	public Set<Comentario> getComentariosVisibles() {
		return this.comentariosVisibles;
	}

	public Set<Comentario> getComentariosEnEsperaDeAprobación() {
		return comentariosEnEsperaDeAprobación;
	}
	
	public List<Integer> getPuntuaciones() {
		return puntuaciones;
	}
	public int getSumPuntuaciones() {
		return sumPuntuaciones;
	}

	public void setPuntuaciones(List<Integer> puntuaciones) {
		this.puntuaciones = puntuaciones;
	}
	public void setSumPuntuaciones(int sumPuntuaciones) {
		this.sumPuntuaciones = sumPuntuaciones;
	}
	/**
	 * Método para borrar un comentario escrito con anterioridad
	 * @param s comentario que se desea borrar
	 */
	public void borrarComentario(Comentario s) {
		if(this.comentariosEnEsperaDeAprobación.contains(s)) {
			this.comentariosEnEsperaDeAprobación.remove(s);
			return;
		}
		if(this.comentariosNoVisibles.contains(s)) {
			this.comentariosNoVisibles.remove(s);
			return; 
		}
		if(this.comentariosVisibles.contains(s)) {
			this.comentariosVisibles.remove(s);
		}
	}
	
	/**
	 * Método para obtener un string descriptivo de las estadísticas del evento
	 * @return String descriptivo de las estadísticas
	 */
	public abstract String getStatString();
	
	/**
	 * Método para indicar si el objeto es equivalente al evento
	 */
	public abstract boolean equals(Object o);
	
	public Set<Comentario> getComentariosNoVisibles(){
		return this.comentariosNoVisibles;
	}
}
