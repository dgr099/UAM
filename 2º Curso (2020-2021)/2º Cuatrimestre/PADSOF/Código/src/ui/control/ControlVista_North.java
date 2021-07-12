package ui.control;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import ui.view.Ventana;
import ui.view.VistaPrincipal;
import ui.view.VistaPrincipal_North;

/**
 * Clase que implementa los controles para la parte norte de la vista principal para usuarios no admins
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlVista_North implements ActionListener{
	private VistaPrincipal_North vn = null;
	private VistaPrincipal vp = null;
	
	/**
	 * Constructor de la clase
	 * @param v objeto con las distintas vistas de la aplicación para obtener las vistas a modificar
	 */
	public ControlVista_North(Ventana v) {
		super();
		this.vn = v.getVistaPrincipal().getNorth();
		this.vp = v.getVistaPrincipal();
	}

	/**
	 * Similar al funcionamiento para la vista norte del admin
	 * 1º Se detecta el botón que se está pulsando
	 * 2º Una vez detectado el botón se cambia el panel en función del botón que se presionó
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		((JButton)arg0.getSource()).setForeground(Color.blue); //pones el seleccionado en azul
		//haces lo que tengas que hacer
		if(((JButton)arg0.getSource()).getText().equals("Danza")) {
			this.vp.viewDanza();
		}
		else if(((JButton)arg0.getSource()).getText().equals("Cartelera")) {
			this.vp.viewCartelera();
		}
		else if(((JButton)arg0.getSource()).getText().equals("Música")) {
			this.vp.viewMusica();
		}
		else if(((JButton)arg0.getSource()).getText().equals("Teatro")) {
			this.vp.viewTeatro();
		}
		else if(((JButton)arg0.getSource()).getText().equals("Abonos")) {
			this.vp.mostrarAbonos();
		}
		else if(((JButton)arg0.getSource()).getText().equals("Más Valorados")) {
			this.vp.mostrarMasValorados();
		}
		this.vn.getLast().setForeground(Color.gray); //pones el otro en gris
		this.vn.setLast(((JButton)arg0.getSource()));
	}

}
