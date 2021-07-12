package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase para el control del botón de añadir a la lista de espera
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAñadirListaEspera implements ActionListener{
	public UICompra vista;
	/**
	 * Constructor de la clase
	 * @param v recibe la ventana para poder obtener la vista
	 */
	public ControlAñadirListaEspera(Ventana v) {
		this.vista = v.getUICompra();
	}
	/**
	 *Método con las instrucciones a realizar cuando se presiona el botón de lista de espera
	 *para añadir o quitar a un usuario de la lista de espera de una representacion
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		/*se añade el usuario a la lista*/
		if(vista.getControlCompra().getR()==null) { /*primero se comprueba si se seleccionó una representación*/
			JOptionPane.showMessageDialog(vista, "Debe seleccionar la representación a la que se desea añadirse a la lista de espera", "User Error", JOptionPane.ERROR_MESSAGE); /*en caso de no seleccionarse ninguna representación se le notifica que debe hacerlo para añadirse a una lista de espera*/
			return;
		}
		/*si se ha seleccionado una representacion, el siguiente paso es comprobar si ya estaba con anterioridad en ella*/
		if(!vista.getControlCompra().getR().getLista().contains(Sistema.getInstancia().getUsuarioEnUso())) { /*en caso de no estar*/
			vista.getControlCompra().getR().addLista(Sistema.getInstancia().getUsuarioEnUso()); /*se le añade a la lista*/ 
			JOptionPane.showMessageDialog(vista, "Se añadió el usuario a la lista de espera de la representacion " + vista.getControlCompra().getR().getFechaYHora().getTime() + " del evento " + vista.getControlCompra().getEvento().getTitulo(), "INFO", JOptionPane.INFORMATION_MESSAGE); /*se notifica que se añadió a la lista*/	
			return;
		}
		else {
			/*en caso de estar en la lista con anterioridad*/
			vista.getControlCompra().getR().salirLista(Sistema.getInstancia().getUsuarioEnUso()); /*se saca al usuario de la lista de espera*/
			JOptionPane.showMessageDialog(vista, "El usuario ha salido de la lista de espera de la representacion " + vista.getControlCompra().getR().getFechaYHora().getTime() + " del evento " + vista.getControlCompra().getEvento().getTitulo(), "INFO", JOptionPane.INFORMATION_MESSAGE); /*se notifica al usuario que se salió exitosamente de la lista*/
		}
		return;
		
	}

}
