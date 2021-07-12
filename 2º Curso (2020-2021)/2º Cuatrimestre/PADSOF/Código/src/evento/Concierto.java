package evento;
import java.util.ArrayList;
import	java.util.List;

/*
 * Clase con métodos y atributos del concierto
 * @version 1.0 28 Mar 21
 * @author David Teófilo Garitagoitia Romero
 */
public class Concierto extends Evento{
	/**
	 * 
	 */
	private static final long serialVersionUID = 7287249982666128106L;
	private String orquesta; //orquesta del concierto
	private String director; //directo del concierto
	private String solista; //solista del concierto
	private List<String> piezas; //lista de piezas a tocar en el concierto
	
	/**
	 * Constructor de la clase concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param descripcion descripcion del cocierto
	 * @param duracion duración en minutos del concierto
	 * @param titulo titulo del evento
	 * @param autor autor de la obra
	 * @param orquesta orquesta del concierto
	 * @param director director de la orquesta
	 * @param solista solistas del cocnierto
	 */
	public Concierto(String descripcion, double duracion, String titulo, String autor, String orquesta, String director,
			String solista) {
		super(descripcion, duracion, titulo, autor);
		this.orquesta = orquesta;
		this.director = director;
		this.solista = solista;
		this.piezas = new ArrayList<String>();
	}
	/**
	 * Función para añadir piezas a las piezas del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param p nombre de la pieza a añadir
	 */
	public void addPieza(String p) {
		if(this.piezas.contains(p)) {
			return;
		}
		this.piezas.add(p);
	}
	
	/**
	 * Función para obtener la orquesta del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre de la orquesta
	 */
	public String getOrquesta() {
		return orquesta;
	}
	
	/**
	 * Función para establecer la orquesta del evento
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param orquesta
	 */
	public void setOrquesta(String orquesta) {
		this.orquesta = orquesta;
	}
	
	/**
	 * Función para obtener el director del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre del director de la orquesta
	 */
	public String getDirector() {
		return director;
	}
	
	/**
	 * Función para establecer el director del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param director nuevo director del concierto
	 */
	public void setDirector(String director) {
		this.director = director;
	}
	
	/**
	 * Función para obtener el solista del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre del solista del concierto
	 */
	public String getSolista() {
		return solista;
	}
	
	/**
	 * Función para establecer el solista del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param solista nuevo solista del concierto
	 */
	public void setSolista(String solista) {
		this.solista = solista;
	}
	
	/**
	 * Función para obtener las piezas del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return lista de piezas del concierto
	 */
	public List<String> getPiezas() {
		return piezas;
	}
	
	/**
	 * Función para establecer las piezas del concierto
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param piezas lista de piezas del concierto
	 */
	public void setPiezas(List<String> piezas) {
		this.piezas = piezas;
	}
	//@override
	/**
	 * Función auxiliar para debugear
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarEvento() {
		super.mostrarEventoAux();
		System.out.print(" Director: " + this.getDirector());
	}
	@Override
	public String getStatString() {
		double[] est_evento = this.getEstadisticas();
		if(est_evento[4]>=0) {
			return this.getTitulo() + "; Director: " + this.getDirector() + " Duracion: " + this.getDuracion() + " Ingresos: " + est_evento[3] + " Estrellas: " + est_evento[4];
		}
		return this.getTitulo() + "; Director: " + this.getDirector() + " Duracion: " + this.getDuracion() + " Ingresos: " + est_evento[3] + " Estrellas: " + "Sin Valoraciones";

	}
	@Override
	public boolean equals(Object o) {
		if(!(o instanceof Concierto)) {
			return false;
		}
		Concierto c = (Concierto)o;
		return c.director.equals(this.director) && c.orquesta.equals(this.orquesta) && c.piezas.equals(this.piezas) 
				&& c.solista.equals(this.solista) && c.getDuracion()==this.getDuracion() && c.getAutor().equals(this.getAutor())
				&& c.getDescripcion().equals(this.getDescripcion()) && c.getTitulo().equals(this.getTitulo());
	}
	
}
