package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JOptionPane;

import entrada.Entrada;
import ui.view.Ventana;
import ui.view.usuario.InfoEntrada;

/**
 * Método con el control para poder borrar un comebtario del sistema
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlBorrarComentario implements ActionListener{
	Ventana v=null;	
	InfoEntrada vista = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlBorrarComentario(Ventana v) {
		this.v = v;
		this.vista = v.getInfoEntrada();
	}
	
	public  void actionPerformed (ActionEvent e) {
		Entrada entrada = vista.getControlUsuario().getEseleccionada();
		if(Calendar.getInstance().before(entrada.getRepresentacion().getFechaYHora())) {
			JOptionPane.showMessageDialog(vista, "No puede comentar una representación que aún no ha ocurrido.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		entrada.borrarComentario();
		JOptionPane.showMessageDialog(vista, "El comentario ha sido borrado.", "User Error", JOptionPane.INFORMATION_MESSAGE);
		vista.getTextArea().setText("Escriba su comentario, click en add comentario para enviar");
		vista.getTextArea().setEditable(true);
		vista.getComentarioButton().setVisible(true);
		vista.revalidate();
		vista.repaint();
	}
}
