package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.util.Calendar;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
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

/* Vista de la pagina principal del administrador */
public class PaginaAdmin extends JScrollPane implements PAdmin{

	private static final long serialVersionUID = 1L;
	private JList<String> comentarios, representaciones;
	private JScrollPane scrollComentarios,
				scrollRepresentaciones;
	private int i;
	private JLabel lComentarios = new JLabel("Comentarios por aprobar", SwingConstants.CENTER), 
		   lRepresentaciones = new JLabel("Representaciones", SwingConstants.CENTER);
	
	
	private DefaultListModel<String> c = new DefaultListModel<>();
	private DefaultListModel<String> r = new DefaultListModel<>();
	
	private JButton btnComentarios = new JButton ( "Leer Comentario" );
	private JButton btnRepresentacion = new JButton ( "Cancelar Representacion" );
	private JButton btnRepresentacion2 = new JButton ( "Cambiar Fecha Representacion" );
	private JButton back = new JButton();
	private JPanel main = new JPanel();
	
	/**
	 * Metodo para actualizar los controladores de los elementos de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param ccr contiene el controlador para cancelar una representacion
	 * @param cvc contiene el controlador para ver comentarios
	 * @param cfr contiene el controlador para cambiar de fecha una representacion 
	 */
	public void setControlador(ControlBack cb, ControlCancelarRepresentacion ccr, ControlVerComentario cvc, ControlCambiarFechaRepresentacion cfr) {
		this.back.addActionListener(cb);
		this.btnRepresentacion.addActionListener(ccr);
		this.btnComentarios.addActionListener(cvc);
		this.btnRepresentacion2.addActionListener(cfr);
	}
	
	/**
	 * Metodo para obtener el comentario seleccionado
	 */
	public String getComentarioSelectedValue() {
		return this.comentarios.getSelectedValue();
	}
	
	/**
	 * Metodo para obtener la representacion seleccionada
	 */
	public String getRepresentacionSelectedValue() {
		return this.representaciones.getSelectedValue();
	}
	
	// Constructor de la vista
	public PaginaAdmin() {
		
		comentarios = new JList<>(c);
		representaciones = new JList<>(r);
		
		comentarios.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		representaciones.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		this.scrollRepresentaciones = new JScrollPane(representaciones);
		this.scrollComentarios = new JScrollPane(comentarios);

		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
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
		south.add(this.back);
		main.add(north, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		this.add(main);
		this.update();
		main.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main);
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario
	 */
	public void update() {;
		r.clear();
		c.clear();
		for(Evento e : Sistema.getInstancia().getEventos()) { /*añades la representaciones a la lista*/
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
		}
		
		this.validate();
		this.repaint();
		return;
	}
	
	/**
	 * Método para añadir un comentario a la lista
	 * @param comentario comentario que se desea añadir
	 */
	public void addElement(Comentario comentario){
		if(comentario==null)	return;
		this.c.addElement(comentario.getMensaje() + "\n-" + comentario.getE().getRepresentacion().getEvento().getTitulo() + "; " + comentario.getNum());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para añadir una representación
	 * @param comentario comentario que se desea añadir
	 */
	public void addElement(Representacion r){
		if(r==null)	return;
		this.r.addElement(r.getEvento().getRepresentaciones().size()-1 + ") " + r.getEvento().getTitulo() +"; " + r.getFechaYHora().getTime());
		this.validate();
		this.repaint();
	}

	/**
	 * Método para eliminar un comentario de la lista
	 * @param comentario comentario a eliminar
	 */
	public void removeElement(Comentario comentario){
		if(comentario==null)	return;
		String s = comentario.getMensaje() + "\n-" + comentario.getE().getRepresentacion().getEvento().getTitulo() + "; " + comentario.getNum();
		if(c.contains(s)){
			c.removeElement(s);
			this.validate();
			this.repaint();
		}
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
		PaginaAdmin pu = new PaginaAdmin();
		JFrame ventana = new JFrame("Prueba_Usuario");
		ventana.getContentPane().setLayout(new BorderLayout());
		ventana.getContentPane().add(pu);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
}
