package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import ui.view.Ventana;
import ui.view.admin.PaginaAddEventosOAbonos;

public class ControlPaginaEventosAdmin implements ActionListener {

	private Ventana ventana = null;
	private PaginaAddEventosOAbonos pea = null;
	
	public ControlPaginaEventosAdmin(Ventana v) {
		this.ventana = v;
		this.setPea(v.getPaginaEventosAdmin());
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(((JButton)arg0.getSource()).getText().equals("Crear evento")) {
			ventana.mostrarPanelSinVueltaAtras("AddEvento");
			return;
			
		}
		
		else if(((JButton)arg0.getSource()).getText().equals("Eliminar evento")) {
			ventana.mostrarPanelSinVueltaAtras("PaginaEliminarEvento");
			return;	
		}
		
		else if(((JButton)arg0.getSource()).getText().equals("Añadir abono")) {
			ventana.mostrarPanelSinVueltaAtras("AddAbono");
			return;
		}
		else if(((JButton)arg0.getSource()).getText().equals("Eliminar abono")) {
			ventana.mostrarPanelSinVueltaAtras("PaginaEliminarAbono");
			return;
		}
	}

	public PaginaAddEventosOAbonos getPea() {
		return pea;
	}

	public void setPea(PaginaAddEventosOAbonos pea) {
		this.pea = pea;
	}
	
}
