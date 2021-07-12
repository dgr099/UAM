package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import ui.view.Ventana;

/**
 * Clase con el control para la reserva de un usuario
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlReservaUsuario implements ActionListener{
	private Ventana v;
	/**
	 * Constructor de la clase
	 * @param v ventana de las que obtiene las vistas sobre las que actua
	 */
	public ControlReservaUsuario(Ventana v) {
		this.v=v;
		v.getPaginaReservas();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		//vista.getListaReservas().actualizasValores(); /*actualizamos los valores de la lista de reservas*/
		v.mostrarPanelSinVueltaAtras("Reservas"); /*mostramos la paguna de reservas*/
	}
	
}
