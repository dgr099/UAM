package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import abonos.AbonoUsuario;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.usuario.PaginaUsuario;

/**
 * Clase con el control para la selección de un abono
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionAbono implements ActionListener{
	Ventana v=null;	
	PaginaUsuario vista = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlSeleccionAbono(Ventana v) {
		this.v = v;
		this.vista = v.getPaginaUsuario();
	}
	
	public  void actionPerformed (ActionEvent e) {
		AbonoUsuario au = null;
	    if(vista.getAbonoSelected() == null) {
	  		JOptionPane.showMessageDialog(null, "No se ha seleccionado abono", "Sistem Error", JOptionPane.ERROR_MESSAGE);
	  		return;
	    }	else {
	    		 String cod = vista.getAbonoSelected();
	    		 for(AbonoUsuario abonoUsuario : Sistema.getInstancia().getUsuarioEnUso().getAbonos()) {
	    			 if(abonoUsuario.getCodigo().equals(cod)) {
	    				 au=abonoUsuario;
	    				 break;
	    			  }
	    		  }
	    	if(au==null) {
	    		JOptionPane.showMessageDialog(null, "No se ha seleccionado correctamente abono", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			  	return;
	    	}
	    	vista.getControlUsuario().setAseleccionado(au);;
	    	v.mostrarPanelSinVueltaAtras("InfoAbono");
	    }
	}
}
