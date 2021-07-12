package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JOptionPane;

import entrada.Entrada;
import ui.view.Ventana;
import ui.view.VistaPrincipal;
import ui.view.usuario.InfoEntrada;

/**
 * Clase con el control para indicar la valoración del usuario
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlValoracion implements ActionListener{
	Ventana v=null;	
	InfoEntrada vista = null;
	VistaPrincipal vp = null;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlValoracion(Ventana v) {
		this.v = v;
		this.vista = v.getInfoEntrada();
		this.vp = v.getVistaPrincipal();
	}
	
	public  void actionPerformed (ActionEvent e) {
		Entrada entrada = vista.getControlUsuario().getEseleccionada();
		if(Calendar.getInstance().before(entrada.getRepresentacion().getFechaYHora())) {
			JOptionPane.showMessageDialog(vista, "No puede valorar una representación que aún no ha ocurrido.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		int val = 0;
		try{
			val = Integer.parseInt(vista.getValoracion());
		}catch (Exception ex) {
			JOptionPane.showMessageDialog(vista, "Lo sentimos la valoración no es correcta\nPruebe escribiendo un número entero del 1 al 5.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		if(entrada.addValoracion(val)==false) {
			JOptionPane.showMessageDialog(vista, "Lo sentimos la valoración no es correcta\nPruebe escribiendo un número del 1 al 5.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		vp.updateValoracion();
		JOptionPane.showMessageDialog(vista, "La valoración fue añadida satisfactoriamente.", "Valoration", JOptionPane.INFORMATION_MESSAGE);
	}
}
