package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;

import evento.Comentario;
import evento.Evento;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.VistaAprobarMensaje;

/**
 * Clase con el control para poder aceptar comentarios de eventos
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlModerarComentario implements ActionListener{
	private Ventana v;
	private VistaAprobarMensaje vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene la vista sobre la que actua el control
	 */
	public ControlModerarComentario(Ventana v) {
		this.v = v;
		this.vista = v.getVistaAprobarMensaje();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String mensaje = vista.getComentario();
		int index = 0;
		int index_2 = 0;
		for(index = mensaje.length()-1; index>=0; index--) {
			if(mensaje.charAt(index)=='-') { /*buscamos hasta donde llega el título (mas el num id de comentario)*/
				break;
			}
			if(mensaje.charAt(index) == ';') {
				index_2 = index; /*guardamos hasta donde llega el id de comentario*/
			}
		}
		String cod = mensaje.substring(index_2 + 2); /*codigo del comentario*/ 
		String eventName = mensaje.substring(index+1, index_2);
		Evento evento = null;
		for(Evento e : Sistema.getInstancia().getEventos()) {
			if(e.getTitulo().equals(eventName)) {
				evento = e;
				break;
			}
		}/*si no encontramos el evento*/
		if(evento==null) {
			JOptionPane.showMessageDialog(vista, "Lo sentimos, no se pudo encontrar el evento al que referencia el comentario", "No event", JOptionPane.ERROR_MESSAGE);
			return;
		}
		mensaje = mensaje.substring(0, index-1); /*mensaje sin incluir el nombre del evento*/
		/*si se presionó el botón de aceptar*/
		Comentario comentario = null;
		for(Comentario c : evento.getComentariosEnEsperaDeAprobación()) {
			if(c.getNum() == Integer.parseInt(cod)) {
				comentario = c;
				break;
			}
		}
		if(comentario == null) {
			JOptionPane.showMessageDialog(vista, "No se encontró el comentario", "Comentario Desconocido", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		if(((JButton)arg0.getSource()).getText().equals("aceptar")) {
			Sistema.getInstancia().getUsuarioEnUso().aprobarComentario(comentario, evento);
			JOptionPane.showMessageDialog(vista, "Se aprobó el comentario, estará visible los siguiente 12 meses a la representación comentada", "Comentario Aceptado", JOptionPane.INFORMATION_MESSAGE);
			v.getPaginaAdmin().removeElement(comentario); /*se quita el comentario de la lista de comentarios del evento*/
			v.getStatEvento().getPaginaEventoAdmin().removeElementComentario(comentario); /*quitamos el comentario de la lista después de aceptarlo*/
			v.goBack();
			return;
		}
		/*si lo que se presionó fue el botón de rechazar*/
		else if(((JButton)arg0.getSource()).getText().equals("rechazar")){
			evento.borrarComentario(comentario);
			comentario.getU().addNotificacion("El comentario: \n" + comentario.getMensaje() + "\n del evento " + comentario.getE().getRepresentacion().getEvento().getTitulo() + "\nHa sido rechazado por el administrador");
			JOptionPane.showMessageDialog(vista, "El comentario fue borrado", "Comentario Rechazado", JOptionPane.INFORMATION_MESSAGE);
			v.getPaginaAdmin().removeElement(comentario); /*se quita el comentario de la lista de comentarios del evento*/
			v.getStatEvento().getPaginaEventoAdmin().removeElementComentario(comentario);
			comentario.rechazarComentario(); /*se pone en modo rechazado*/
			v.goBack();
			return;
			}
		else {
			Sistema.getInstancia().getUsuarioEnUso().solicitarCambio(comentario);
			JOptionPane.showMessageDialog(vista, "Se ha mandado una notificación al usuario para que modifique su comentario", "Solicitado cambios", JOptionPane.INFORMATION_MESSAGE);
		}
		
	}
}
