package ui.control;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import ui.view.Ventana;
/**
 * Controlador para implementar la función de vuelta atrás
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlBack implements ActionListener{
	private Ventana vista=null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana para poder pasar a mostrar el panel anterior al actual
	 */
	public ControlBack(Ventana v){
		if(v==null) {
			return;
		}
		this.vista = v;
	}
	/**
	 * Se pasa a mostrar la anterior pantalla 
	 *
	 */ 
	@Override
	public void actionPerformed(ActionEvent arg0) {
			vista.goBack();
	}
	
}
