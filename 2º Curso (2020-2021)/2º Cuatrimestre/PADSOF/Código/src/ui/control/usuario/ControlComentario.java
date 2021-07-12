package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JOptionPane;

import entrada.Entrada;
import ui.view.Ventana;
import ui.view.usuario.InfoEntrada;

/**
 * Clase con el control para poder comentar en un evento
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlComentario implements ActionListener{
	Ventana v=null;	
	InfoEntrada vista = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de las que obtiene las vistas sobre las que actua
	 */
	public ControlComentario(Ventana v) {
		this.v = v;
		this.vista = v.getInfoEntrada();
	}
	
	public  void actionPerformed (ActionEvent e) {
		Entrada entrada = vista.getControlUsuario().getEseleccionada();
		if(Calendar.getInstance().before(entrada.getRepresentacion().getFechaYHora())) {
			JOptionPane.showMessageDialog(vista, "No puede comentar una representación que aún no ha ocurrido.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		String comen = vista.getComentario();
		entrada.setComentario(comen);
		JOptionPane.showMessageDialog(vista, "El comentario fue enviado exitosamente.", "Valoration", JOptionPane.INFORMATION_MESSAGE);
	}
}
