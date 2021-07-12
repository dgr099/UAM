package ui.control;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import ui.view.Ventana;

/**
 * Clase con los controles para la parte sur de la vista de usuario ántes de hacer el registro o log
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlVista_South_sin_iniciar implements ActionListener{
	private Ventana v = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la cual obtiene las vistas en las que actuará el control
	 */
	public ControlVista_South_sin_iniciar(Ventana v) {
		super();
		v.getVistaPrincipal().getSouth();
		this.v  = v;
	}

	/**
	 * Acción a ejecitar al pulsar sobre los botones de la vista sur
	 * 1º Se identifica el botón pulsado
	 * 2º Se muestra el panel correspondiente al botón pulsado
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(((JButton)arg0.getSource()).getText()!=null) {
			if(((JButton)arg0.getSource()).getText().equals("Register")) {
				v.mostrarPanel("Register"); //si se presionó el botón de register se muestra la pantalla de registro
			}
			else if (((JButton)arg0.getSource()).getText().equals("Login")){
				v.mostrarPanel("Login"); //si se presionó el botón de login se muestra la pantalla de login
			}
			else {
				return; //este debería pasar a mostrar la info del usuario
			}
		}
	}

}
