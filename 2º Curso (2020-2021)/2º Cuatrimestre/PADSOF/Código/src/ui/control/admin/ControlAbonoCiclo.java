package ui.control.admin;

import java.util.LinkedHashSet;
import java.util.Set;

import evento.Evento;

/**
 * Clase que actua como modelo para la creacion de un abono de ciclo
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAbonoCiclo {
	private Set<Evento> eventos = new LinkedHashSet<Evento>();
	public void reset() {
		eventos.clear();
	}
	public void addEvento(Evento e) {
		eventos.add(e);
	}
	public void remEvento(Evento e) {
		eventos.remove(e);
	}
	public Set<Evento> getEventos(){
		return this.eventos;
	}
}
