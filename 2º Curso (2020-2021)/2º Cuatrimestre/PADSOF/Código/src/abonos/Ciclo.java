package abonos;

import java.io.Serializable;
import java.util.List;

import evento.Evento;

/**
 * Clase con el ciclo contenido en los abonos de ciclo
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Ciclo implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -544815439613609412L;
	private List<Evento> eventos; //lista de eventos contenidos en el abono
	private static int last = 0;
	private String cod;
	/**
	 * Constructor de la clase
	 * @param ev lista de eventos a establecer en el abono
	 */
	public Ciclo(List<Evento> ev) {
		eventos = ev;
		cod = String.valueOf(Ciclo.last);
		cod+=ev.toString().substring(0, 3);
	}

	/**
	 * Método para obtener el valor del static, para poder guardarlo en save sistem
	 * @return el valor del entero estático
	 */
	public static int getLast(){
		return last;
	}

	/**
	 * Método para establecer el valor del entero estático (empleado en la carga del sistema)
	 * @param a el entero a establecer
	 */
	public static void setLast(int a){
		last = a;
	}
	/**
	 * Método para obtener la lista de eventos del ciclo
	 * @return lista de eventos contenidos en el ciclo
	 */
	public List<Evento> getEventos() {
		return eventos;
	}
	/**
	 * Método para establecer la lista de eventos del ciclo
	 * @param eventos eventos contenidos en el ciclo
	 */
	public void setEventos(List<Evento> eventos) {
		this.eventos = eventos;
	}
	/**
	 * Método para obtener la valoración de un ciclo
	 * @return decimal con la valoración del ciclo, -1 si no hay votos
	 */
	public double getValoracion() {
		double sum=0;
		int votos = 0;
		for(Evento e : this.eventos) {
			double aux = e.getValoracion(); 
			if(aux>=0) {
				sum+=aux;
				votos++;
			}
		}
		if(votos>0)
			return sum/votos;
		return -1;
	}
	
	/**
	 * Método para obtener el código del ciclo
	 * @return string con el código del ciclo
	 */
	public String getCod() {
		return this.cod;
	}
}
