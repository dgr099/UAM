package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.StringTokenizer;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;

import evento.Evento;
import evento.Representacion;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.PaginaAdmin;
import ui.view.admin.StatEvento;

/**
 * Método con el control para cancelar una representación
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlCancelarRepresentacion implements ActionListener{
	private PaginaAdmin vista;
	private Ventana v;
	private StatEvento vista2;
	private JScrollPane enUso;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlCancelarRepresentacion(Ventana v) {
		this.vista = v.getPaginaAdmin();
		this.v = v;
		this.vista2 = v.getStatEvento();		
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String cod;
		if(vista2.getEnUso()) {
			cod = vista2.getPaginaEventoAdmin().getRepresentacionSelectedValue();
			enUso = vista2;
		}
		else {
			cod = vista.getRepresentacionSelectedValue();
			enUso = vista;
		}
			
		if(cod == null) {
			JOptionPane.showMessageDialog(enUso, "Error, no se seleccionó ninguna representacion.", "Error No Value Selected", JOptionPane.ERROR_MESSAGE);
			return;
		}
		int num;
		Evento evento = null;
		StringTokenizer tokens=new StringTokenizer(cod);
		num = Integer.parseInt((String) tokens.nextToken(")"));
		String name = tokens.nextToken(";");
		name = name.substring(2);
		//name += tokens.nextToken(";");
		for(Evento e : Sistema.getInstancia().getEventos()) {
			if(e.getTitulo().equals(name)) {
				evento = e;
				break;
			}
		}
		if(evento == null) {
			JOptionPane.showMessageDialog(enUso, "Error, no se encontró el evento.", "Error Evento", JOptionPane.ERROR_MESSAGE);
			return;
		}
		Representacion r = evento.getRepresentaciones().get(num);
		if(r == null) {
			JOptionPane.showMessageDialog(enUso, "Error, no se encontró la representación.", "Error Representacion", JOptionPane.ERROR_MESSAGE);
			return;
		}
		r.cancelarRepresentacion();
		vista.update(); /*actualizamos la vista general de admin*/
		vista2.setEvento(evento); /*actualizamos la vista de esa pagina de evento para admin, hacemos el set para actualizar índices*/
		v.getVistaPrincipal().getCartelera().compElemento(evento); /*comprobamos por si hay que quitar el evento de cartelera*/
		JOptionPane.showMessageDialog(enUso, "La representación fue cancelada con éxito", "Representacion cancelada", JOptionPane.INFORMATION_MESSAGE);

	}
}
