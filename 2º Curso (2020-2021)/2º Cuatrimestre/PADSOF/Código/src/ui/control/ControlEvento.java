package ui.control;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.StringTokenizer;

import javax.swing.JList;

import evento.Evento;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase con el control al presionar sobre el botón de algún eventos 
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlEvento implements MouseListener{
	private UICompra uic;
	private Ventana v;
	/**
	 * Constructor de la clase para el control de evento
	 * @param v ventana con las diferentes pantallas del evento
	 */
	public ControlEvento(Ventana v) {
		uic = v.getUICompra();
		v.getVistaPrincipal().getCartelera();
		this.v = v;
		v.getVistaPrincipal();
	}
	/**
	 * Acción al pulsar sobre un evento
	 * Se obtiene el evento al que se refiere el botón,
	 * y se pasa a mostrar la pantalla de compra del evento en cuestión
	 */
	
	@Override
	public void mouseClicked(MouseEvent arg0) {
		@SuppressWarnings("unchecked")
		StringTokenizer tokens=  new StringTokenizer(((JList<String>)arg0.getSource()).getSelectedValue());
		String nombre = tokens.nextToken(";");
		Evento evento = null;
		/*se pasa a buscar el evento con ese nombre*/
		for(Evento e : Sistema.getInstancia().getEventos()) {
			if(e.getTitulo().equals(nombre)) {
				evento = e;
				break;
			}
		}
		if(evento!=null) { /*si el evento seleccionado existe*/
			uic.prepararCompraEntrada(evento); /*se prepara para mostrar el evento*/
			v.mostrarPanel("UICompra"); /*se muestra el panel de compra de evento*/
		}
		
	}
	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	
	

}
