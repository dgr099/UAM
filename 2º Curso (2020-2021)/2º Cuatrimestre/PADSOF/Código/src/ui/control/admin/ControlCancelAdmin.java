package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import ui.view.Ventana;

/**
 * Control para cancelar cuando el usuario es un admin
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlCancelAdmin implements ActionListener{
	Ventana v;
	/**
	 * Constructor de la clase
	 * @param v ventana de la aplicación
	 */
	public ControlCancelAdmin(Ventana v) {
		this.v = v;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		v.mostrarPanel("VistaPrincipal");
		v.getStatEvento().setEnUso(false);
	}

}
