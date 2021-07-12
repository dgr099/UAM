package ui.control.usuario;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import entrada.Entrada;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.usuario.PaginaUsuario;

/**
 * Clase con el control para seleccionar una entrada
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionEntrada implements ActionListener{
	Ventana v=null;	
	PaginaUsuario vista = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlSeleccionEntrada(Ventana v) {
		this.v = v;
		this.vista = v.getPaginaUsuario();
	}
	
	public  void actionPerformed (ActionEvent e) {
		Entrada entrada = null;
	    if(vista.getEntradaSeleccionada() == null) {
	  		JOptionPane.showMessageDialog(null, "No se ha seleccionado entrada", "Sistem Error", JOptionPane.ERROR_MESSAGE);
	  		return;
	    }	else {
	    		 String cod = vista.getEntradaSeleccionada();
	    		 for(Entrada entrada2 : Sistema.getInstancia().getUsuarioEnUso().getEntradas()) {
	    			 if(entrada2.getCodigo().equals(cod)) {
	    				 entrada=entrada2;
	    				 break;
	    			  }
	    		  }
	    	if(entrada==null) {
	    		JOptionPane.showMessageDialog(null, "No se ha seleccionado correctamente entrada", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			  	return;
	    	}
	    	vista.getControlUsuario().setEseleccionada(entrada);
	    	v.mostrarPanelSinVueltaAtras("InfoEntrada");
	    }
	}
}
