package ui.control;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal_North;
import ui.view.VistaPrincipal_south;

/**
 * Clase con los controles para la parte sur de la vista principal tras hacer login o registro
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlVista_South_iniciado implements ActionListener{
	private VistaPrincipal_south vs = null;
	private VistaPrincipal_North vn = null;
	private Ventana v = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana con todas las vistas de la aplicación y de la que obtiene las vistas en las que actua el controlador
	 */
	public ControlVista_South_iniciado(Ventana v) {
		super();
		this.vs = v.getVistaPrincipal().getSouth();
		this.vn = v.getVistaPrincipal().getNorth();
		this.v  = v;
	}

	/**
	 * Similar a la parte norte, identifica el botón seleccionado para saber que instrucciones realizar
	 * Tras ello pasa a mostrar en la vista sur el panel de iniciado o sin iniciar
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(((JButton)arg0.getSource()).getText()!=null) {
			if(((JButton)arg0.getSource()).getText().equals("log out")) {
				Sistema.getInstancia().cerrarSesion();
				vs.mostrarPanel("sin_iniciar");
				vn.mostrarPanel("user");
				v.mostrarPanel("VistaPrincipal");
				v.getVistaPrincipal().viewCartelera();
			}
			else {
				if(Sistema.getInstancia().getUsuarioEnUso().equals(Sistema.getInstancia().getAdmin())) {
					v.mostrarPanel("PaginaAdmin");
					return;
				}
				else {
					v.mostrarPanel("Pagina usuario");
					return;
				}
			}
		}
	}

}
