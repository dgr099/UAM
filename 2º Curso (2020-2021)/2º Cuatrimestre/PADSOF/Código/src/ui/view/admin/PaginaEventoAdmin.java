package ui.view.admin;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Calendar;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;

import evento.Comentario;
import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlBack;
import ui.control.admin.ControlCambiarFechaRepresentacion;
import ui.control.admin.ControlCancelarRepresentacion;
import ui.control.admin.ControlVerComentario;
import usuario.Usuario;

/**
 * Similar a página Admin pero especifica para un evento en concreto
 * muestra las representaciones del evento y comentarios pendientes por aprobar
 * además de permitir cancelar representaciones y aprobar/rechazar o solicitar cambio en comentarios
 * @author eps
 *
 */
public class PaginaEventoAdmin extends JScrollPane implements PAdmin{

	private static final long serialVersionUID = 1L;
	JList<String> comentarios, representaciones;
	JScrollPane scrollComentarios,
				scrollRepresentaciones;
	
	JLabel lComentarios = new JLabel("Comentarios por aprobar", SwingConstants.CENTER), 
		   lRepresentaciones = new JLabel("Representaciones", SwingConstants.CENTER);
	
	
	DefaultListModel<String> c = new DefaultListModel<>();
	DefaultListModel<String> r = new DefaultListModel<>();
	
	JButton btnComentarios = new JButton ( "Leer Comentario" );
	JButton btnRepresentacion = new JButton ( "Cancelar Representacion" );
	JButton btnRepresentacion2 = new JButton ( "Cambiar Fecha Representacion" );
	JPanel main = new JPanel();
	int i = 0;
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param ccr contiene el controlador para cancelar una representacion
	 * @param cvc contiene el controlador para ver un comentario
	 * @param cfr contiene el controlador para cambiar la fecha de una representacion
	 */
	public void setControlador(ControlBack cb, ControlCancelarRepresentacion ccr, ControlVerComentario cvc, ControlCambiarFechaRepresentacion cfr) {
		this.btnRepresentacion.addActionListener(ccr);
		this.btnComentarios.addActionListener(cvc);
		this.btnRepresentacion2.addActionListener(cfr);
	}
	
	/**
	 * Metodo para obtener un comentario seleccionado
	 */
	public String getComentarioSelectedValue() {
		return this.comentarios.getSelectedValue();
	}
	
	/**
	 * Metodo para obtener una representacion seleccionada
	 */
	public String getRepresentacionSelectedValue() {
		return this.representaciones.getSelectedValue();
	}
	
	// Constructor de la vista
	public PaginaEventoAdmin() {
		comentarios = new JList<>(c);
		representaciones = new JList<>(r);
		
		comentarios.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		representaciones.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		this.scrollRepresentaciones = new JScrollPane(representaciones);
		this.scrollComentarios = new JScrollPane(comentarios);
		JPanel north = new JPanel();
		JPanel south = new JPanel();
		main.setLayout(new BorderLayout());
		north.setLayout(new GridBagLayout());
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.insets = new Insets(5,5,5,5);
		constraints.gridx = 0;
		constraints.gridy = 0;
		constraints.gridwidth = 2;
		constraints.gridheight = 1;
		north.add(this.lRepresentaciones, constraints);
		constraints.gridx = 2;
		constraints.gridy = 0;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(this.lComentarios, constraints);
		constraints.gridx = 0;
		constraints.gridy = 1;
		constraints.gridwidth = 2;
		constraints.gridheight = 1;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.weighty = 1.0;
		constraints.weightx = 1.0;
		north.add(scrollRepresentaciones, constraints);
		constraints.gridx = 2;
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(scrollComentarios, constraints);
		constraints.fill = GridBagConstraints.NONE;
		constraints.weighty = 0;
		constraints.weightx = 0;
		constraints.gridx = 0;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnRepresentacion, constraints);
		constraints.gridx = 1;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnRepresentacion2, constraints);
		constraints.gridx = 2;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnComentarios, constraints);
		main.add(north, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		
		this.add(main);
		main.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main);
	}
	
	/**
	 * Metodo para actualizar un evento
	 * @param e contiene el evento a actualizar
	 */
	public void updateEvento(Evento e) {
		r.clear();
		c.clear();
		i=0;
		for(Representacion rep : e.getRepresentaciones()) {
			if(rep.getFechaYHora().after(Calendar.getInstance())) { /*si es una representación que aún no ha pasado*/
				r.addElement(i + ") " + rep.getEvento().getTitulo() +"; " + rep.getFechaYHora().getTime());
				i++;
			}
		}
		for(Comentario comentario : e.getComentariosEnEsperaDeAprobación()) {
			c.addElement(comentario.getMensaje() + "\n-" + e.getTitulo() + "; " + comentario.getNum());
		}
		this.validate();
		this.repaint();
		return;
	}
	
	// Main para probar la vista
	public static void main (String...args) {
		try {
			Usuario u = new Usuario("Prueba", "123");
			Sistema.getInstancia().setUsuarioEnUso(u);
			for(int i=0; i!=5; i++) {
				Concierto con = new Concierto("prueba", 45, "titulo", "aut", "orq", "dir", "sol");
				for(int j=0; j!=20; j++) {
					Calendar c = Calendar.getInstance();
					c.add(Calendar.YEAR, 2);
					Representacion r = new Representacion(c, 20);
					con.addRepresentacion(r);
				}
				Sistema.getInstancia().addEvento(con);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		PaginaEventoAdmin pu = new PaginaEventoAdmin();
		JFrame ventana = new JFrame("Prueba_Usuario");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(pu);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	/**
	 * Método para eliminar un comentario de la lista
	 * @param c comentario a eliminar
	 */
	public void removeElementComentario(Comentario c) {
		if(c==null) {
			return;
		}
		String s = c.getMensaje() + "\n-" + c.getE().getRepresentacion().getEvento().getTitulo() + "; " + c.getNum();
		if(this.c.contains(s)){
			this.c.removeElement(s);
		}
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para añadir representacion a la lista de representaciones
	 * @param rep representación a añadir
	 */
	public void addElement(Representacion rep) {
		r.addElement(rep.getEvento().getRepresentaciones().size()-1 + ") " + rep.getEvento().getTitulo() +"; " + rep.getFechaYHora().getTime());
		this.validate();
		this.repaint();
	}
}
