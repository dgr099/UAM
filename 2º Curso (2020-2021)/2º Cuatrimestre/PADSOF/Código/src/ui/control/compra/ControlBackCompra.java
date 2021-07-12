package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase encargada del control del back de compra
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlBackCompra implements ActionListener{
	private UICompra vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que recoge la vista
	 */
	public ControlBackCompra(Ventana v) {
		this.vista = v.getUICompra();
	}
	/**
	 * Método con las instrucciones ha realizar al pulsar el back de compra
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		vista.getSouth().mostrarPanel("Seleccionar datos");
		vista.ocultarAtras();
	}

}
