package ui.control;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import ui.view.Ventana;

/**
 * Clase para implementar la función de cancelar y volver a la vista principal
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlCancel implements ActionListener{
	Ventana v;
	/**
	 * Constructor de la clase
	 * @param v ventana para pedirle que pase a mostrar la vista principal al hacer click en ella
	 */
	public ControlCancel(Ventana v) {
		this.v = v;
	}
	/**
	 * Se cancelan las acciones y se vuelve a la vista principal
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		v.mostrarPanel("VistaPrincipal");
		
	}
}
