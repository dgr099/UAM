package evento;
import java.util.ArrayList;
import java.util.List;
/**
 * Clase que contiene los métodos y atributos de la clase danza
 * @version 1.0 28 Mar 21
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Danza extends Evento{
	/**
	 * 
	 */
	private static final long serialVersionUID = 5661898527689869637L;
	private List<String> bailarines; //lista de bailarines de la danza
	private String director; //director de la obra
	
	/**
	 * Constructor de la clase danza
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param descripcion decripcion del evento de danza
	 * @param duracion duracion en minutos del evento
	 * @param titulo titulo del evento
	 * @param autor autor del evento
	 * @param director director de la danza
	 */
	public Danza(String descripcion, double duracion, String titulo, String autor,
			String director) {
		super(descripcion, duracion, titulo, autor);
		this.director = director;
		this.bailarines=new ArrayList<String>();
	}
	
	/**
	 * Función para obtener los bailarines del evento de danza
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return lista de bailarines del evento de danza
	 */
	public List<String> getBailarines() {
		return bailarines;
	}
	
	/**
	 * Función para establecer los bailarines de un evento
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param bailarines lista de bailarines de un evento
	 */
	public void setBailarines(List<String> bailarines) {
		this.bailarines = bailarines;
	}
	
	/**
	 * Función para añadir bailarines a la lista de bailarines del evento
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param b nombre del nuevo bailarin
	 * @return
	 */
	public boolean addBailarin(String b) {
		if(this.bailarines.contains(b)) {
			return false;
		}
		this.bailarines.add(b);
		return true;
	}
	
	/**
	 * Función para obtener el director del evento de danza
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre del director
	 */
	public String getDirector() {
		return director;
	}
	
	/**
	 * Función para establecer el director del evento de danza
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param director director a establecer en el evento
	 */
	public void setDirector(String director) {
		this.director = director;
	}
	/**
	 * Función auxiliar para debugear
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarEvento(){
		super.mostrarEventoAux();
		System.out.print(" Bailarines: " + this.getBailarines().toString());
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
		if(!(o instanceof Danza)) {
			return false;
		}
		Danza d = (Danza)o;
		return d.getAutor().equals(d.getAutor()) && d.getBailarines().equals(this.getBailarines()) && d.getDescripcion().equals(this.getDescripcion())
				&& d.getDirector().equals(this.getDirector()) && d.getTitulo().equals(this.getTitulo());
	}

}
