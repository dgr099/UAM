package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;

import ui.view.Ventana;
import ui.view.admin.PaginaAdmin;
import ui.view.admin.StatEvento;
import ui.view.admin.VistaAprobarMensaje;

public class ControlVerComentario implements ActionListener{
	private VistaAprobarMensaje vista;
	private Ventana v;
	private PaginaAdmin vista3;
	private StatEvento vista2;
	private JScrollPane vista_;
	public ControlVerComentario(Ventana v) {
		this.v = v;
		vista = v.getVistaAprobarMensaje();
		vista2 = v.getStatEvento();
		vista3 = v.getPaginaAdmin();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String value;
		if(vista2.getEnUso()) {
			vista_ = vista2;
			value = vista2.getPaginaEventoAdmin().getComentarioSelectedValue();
		}
		else {
			value = vista3.getComentarioSelectedValue();
			vista_ = vista3;
		}
		
		
		if(value==null) {
			JOptionPane.showMessageDialog(vista_, "Error, no se seleccionó ningún comentario.", "Error No Value Selected", JOptionPane.ERROR_MESSAGE);
			return;
		}
		vista.getVistaMensaje().updateString(value); /*actualizas con el comentario a mostrar*/
		v.mostrarPanelSinVueltaAtras("AprobarMensaje"); /*pasas a mostrar la pagina de aprobar mensajes*/
	}

}
