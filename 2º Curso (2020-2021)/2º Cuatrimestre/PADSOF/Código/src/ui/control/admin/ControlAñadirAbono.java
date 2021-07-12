package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import ui.view.Ventana;

/**
 * Método con el control para añadir un abono
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAñadirAbono implements ActionListener{
	private Ventana v;
	/**
	 * Constructor de la clase
	 * @param v
	 */
	public ControlAñadirAbono(Ventana v) {
		this.v = v;
	}
	/**
	 * 1º identifica que botón fue presionado y después se encarga de mostrar el panel 
	 * correspondiente para introducir los datos en función del botón presionado
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(((JButton)arg0.getSource()).getText().equals("Añadir abono anual")) {
			v.mostrarPanelSinVueltaAtras("AddAbonoAnual");
			return;
		}
		else {
			v.mostrarPanelSinVueltaAtras("AddAbonoCiclo");
			v.getAddAbonoCiclo().getControlAbonoCiclo().reset(); /*reseteamos los datos de interacciones pasadas*/
			return;
		}
		
	}

}
