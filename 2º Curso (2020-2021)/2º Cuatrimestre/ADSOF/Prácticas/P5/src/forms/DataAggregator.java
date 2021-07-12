package forms;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

/**
 * Clase que sirve para agrupar las respuestas a un formulario
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class DataAggregator {
	Map<String, List<Respuesta<?>>> respuestas;
	
	public DataAggregator() {
		super();
		this.respuestas = new LinkedHashMap<String, List<Respuesta<?>>>();
	}

	/**
	 * Metodo que recopila las respustas, las introduce en el map respuestas y las ordena.
	 * @param map mapa de preguntas y respuestas
	 */
	public void add(Map<String, Respuesta<?>> map) {
		List<Respuesta<?>> l;
		for(Entry<String, Respuesta<?>> p: map.entrySet()) { //iteramos sobre el mapa
			if(this.respuestas.containsKey(p.getKey())) { //si tenemos esa pregunta
				l = this.respuestas.get(p.getKey()); //creamos una lista con lo anterior
				l.add(p.getValue()); //y le añadimos los nuevos datos
				this.respuestas.put(p.getKey(), l);
			}
			else {
				l= new ArrayList<Respuesta<?>>(); //si no estaba creada la lista la creas
				l.add(p.getValue()); 
				this.respuestas.put(p.getKey(), l);
			}
			Collections.sort(this.respuestas.get(p.getKey()));
		}
	}

	@Override
	public String toString() {
		return this.respuestas.toString();
	}
}
