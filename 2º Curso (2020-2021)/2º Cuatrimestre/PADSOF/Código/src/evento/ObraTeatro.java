package evento;
import java.util.ArrayList;
import java.util.List;
/**
 * Clase que contiene la información y métodos respectivos a las
 * obras de teatro
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 */
public class ObraTeatro extends Evento{
	/**
	 * 
	 */
	private static final long serialVersionUID = -460624282953593436L;
	private List<String> actores; //lista de actores de las obras de teatro
	private String director; //director de la obra
	private String compania; //compañia que lleva la obra
	
	/**
	 * Constructor de la clase obra de teatro
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param descripcion descripción de la obra
	 * @param duracion duración en minutos de la obra
	 * @param titulo titulo de la obra
	 * @param autor autor de la obra de teatro
	 * @param director director de la obra de teatro
	 * @param compania compañia de la obra de teatro
	 */
	public ObraTeatro(String descripcion, double duracion, String titulo, String autor, String director,
			String compania) {
		super(descripcion, duracion, titulo, autor);
		this.director = director;
		this.compania = compania;
		this.actores = new ArrayList<String>();
	}
	/**
	 * Función para obtener los autores de la obra de teatro
	 * @version 1.0 30 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return lista de actores de la obra
	 */
	public List<String> getActores() {
		return actores;
	}
	/**
	 * Función para establecer los actores de la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param actores lista de los actores de la obra
	 */
	public void setActores(List<String> actores) {
		this.actores = actores;
	}
	
	/**
	 * Función para añadir un actor a la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param act nombre del actor que se pretende añadir
	 * @return booleano que define el éxito o no de la operación
	 */
	public boolean addActor(String act) {
		if(this.actores.contains(act)) {
			return false;
		}
		this.actores.add(act);
		return true;
	}
	
	/**
	 * Función para obtener el director de la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return nombre del director de la obra
	 */
	public String getDirector() {
		return director;
	}
	
	/**
	 * Función para establecer la compañia de la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param compania nombre de la compañia de teatro a establecer
	 */
	public void setCompania(String compania){
		this.compania = compania;
	}
	
	/**
	 * Función para obtener la compañia de una obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return string nombre de la compañia
	 */
	public String getCompania(){
		return this.compania;
	}
	
	/**
	 * Función para establecer el director de la obra
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param director nombre del director de la obra
	 */
	public void setDirector(String director) {
		this.director = director;
	}
	
	/**
	 * Función para imprimir el evento (debug)
	 * @version 1.0 31 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarEvento(){
		super.mostrarEventoAux();
		System.out.print(" Actores: " + this.getActores().toString());
	}
	@Override
	public String getStatString() {
		double[] est_evento = this.getEstadisticas();
		if(est_evento[4]>=0) {
			return this.getTitulo() + "; Actores: " + this.getDirector() + " Duracion: " + this.getDuracion() + " Ingresos: " + est_evento[3] + " Estrellas: " + est_evento[4];
		}
		return this.getTitulo() + "; Actores: " + this.getDirector() + " Duracion: " + this.getDuracion() + " Ingresos: " + est_evento[3] + " Estrellas: " + "Sin Valoraciones";
	}
	@Override
	public boolean equals(Object o) {
		if(!(o instanceof ObraTeatro)) {
			return false;
		}
		ObraTeatro t = (ObraTeatro)o;
		return this.getActores().equals(t.getActores()) && this.getAutor().equals(t.getAutor()) && this.getCompania().equals(t.getCompania())
				&& this.getDescripcion().equals(t.getDescripcion()) && this.getDirector().equals(t.getDirector()) && this.getDuracion() == t.getDuracion() && this.getTitulo().contentEquals(t.getTitulo());
	}

}
