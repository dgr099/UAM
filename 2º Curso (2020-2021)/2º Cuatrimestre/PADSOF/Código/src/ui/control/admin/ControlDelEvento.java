package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import evento.Evento;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.PaginaEliminarEvento;

public class ControlDelEvento implements ActionListener{
	Ventana v;
	PaginaEliminarEvento vista;
	public ControlDelEvento(Ventana v) {
		this.v = v;
		vista = v.getPaginaEliminarEvento();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String nom = vista.getEventosSelectedValue();
		Evento e = null;
		for(Evento evento : Sistema.getInstancia().getEventos()) {
			if(evento.getTitulo().equals(nom)) {
				e = evento;
				break;
			}
		}
		if(e==null) {
			JOptionPane.showMessageDialog(vista, "No se encontró el evento seleccionado.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		Sistema.getInstancia().removeEvent(e);
		vista.update();
		v.getVistaPrincipal().getCartelera().removeElement(e);
		v.getVistaPrincipal().getMejorValoradosUI().getEventosValorados().removeElement(e);
		v.getVistaPrincipal().getStatListaEventos().removeElement(e);
		JOptionPane.showMessageDialog(vista, "El evento fue eliminado.", "Evento Eliminado", JOptionPane.INFORMATION_MESSAGE);
	}

}
