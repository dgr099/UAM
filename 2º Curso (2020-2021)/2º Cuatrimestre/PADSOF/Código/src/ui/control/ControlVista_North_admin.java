package ui.control;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import ui.view.Ventana;
import ui.view.VistaPrincipal_North;

/**
 * Clase con el control de la parte norte de la vista principal para cuando iniciamos sesión como admin
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlVista_North_admin implements ActionListener{
	private VistaPrincipal_North vn = null;
	private Ventana v = null;
	
	/**
	 * Contstructor de la clase para el control de la vista norte
	 * @param v objeto que contiene las partes de las vistas de la aplicación para poder obtener la vista norte
	 */
	public ControlVista_North_admin(Ventana v) {
		super();
		this.vn = v.getVistaPrincipal().getNorth();
		this.v  = v;
	}

	/**
	 * Método con las instrucciones para cuando se presiona sobre el botón
	 * 1º se identifica el botón presionado
	 * 2º en función del botón seleccionado se mostrará un panel u otro en la vista principal
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		this.vn.setLast(((JButton)arg0.getSource()));
		if(((JButton)arg0.getSource()).getText().equals("Configuracion Teatro")) {
			v.mostrarPanel("Conf Teatro"); //muestra la conf de teatro
			return;
		}
		if(((JButton)arg0.getSource()).getText().equals("Eventos")) {
			v.mostrarPanel("VistaPrincipal");
		}
		if(((JButton)arg0.getSource()).getText().equals("Añadir Eventos o Abonos")) {
			v.mostrarPanel("PaginaEventosAdmin");
		}
		((JButton)arg0.getSource()).setForeground(Color.blue); //pones el seleccionado en azul
		this.vn.getLast().setForeground(Color.gray); //pones el otro en gris
	}

}
