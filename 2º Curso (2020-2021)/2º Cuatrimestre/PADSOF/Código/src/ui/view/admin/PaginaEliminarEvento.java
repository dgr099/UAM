package ui.view.admin;
import java.awt.BorderLayout;
import java.awt.Container;
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

import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlBack;
import ui.control.admin.ControlDelEvento;
import usuario.Usuario;

// Vista para eliminar un evento
public class PaginaEliminarEvento extends JScrollPane{

	private static final long serialVersionUID = 1L;
	JList<String> eventos;
	JScrollPane scrollEventos;
	
	JLabel leventos = new JLabel("Eventos", SwingConstants.CENTER);
	
	
	DefaultListModel<String> e = new DefaultListModel<>();
	
	JButton btnEvento = new JButton ( "Borrar Evento" );
	JButton back = new JButton();
	JPanel main = new JPanel();
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param cev contiene el controlador para eliminar un evento
	 */
	public void setControlador(ControlBack cb, ControlDelEvento cev) {
		this.back.addActionListener(cb);
		this.btnEvento.addActionListener(cev);
	}
	
	
	/**
	 * Metodo para obtener el evento seleccionado
	 * @return devuelve un evento
	 */
	public String getEventosSelectedValue() {
		return this.eventos.getSelectedValue();
	}
	
	// Constructor de la vista
	public PaginaEliminarEvento() {
		
		eventos = new JList<>(e);
		
		eventos.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		this.scrollEventos = new JScrollPane(eventos);

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
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(this.leventos, constraints);
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.weighty = 1.0;
		constraints.weightx = 1.0;
		north.add(this.scrollEventos, constraints);
		constraints.fill = GridBagConstraints.NONE;
		constraints.weighty = 0;
		constraints.weightx = 0;
		constraints.gridx = 0;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnEvento, constraints);
		south.add(this.back);
		main.add(north, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		this.update();
		this.add(main);
		main.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main);
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario
	 */
	public void update() {
		e.clear();
		for(Evento e : Sistema.getInstancia().getEventos()) { /*añades la representaciones a la lista*/
			this.e.addElement(e.getTitulo());
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
		PaginaEliminarEvento pu = new PaginaEliminarEvento();
		JFrame ventana = new JFrame("Prueba_Usuario");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		//pu.update();
		c.add(pu);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	
	
	/**
	 * Método para añadir evento a la lista
	 * @param e Evento a añadir
	 */
	public void addElement(Evento e) {
		if(e==null || this.e.contains(e.getTitulo())) {
			return;
		}
		this.e.addElement(e.getTitulo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para eliminar un evento de la lista
	 * @param e Evento a borrar de la lista
	 */
	public void removeElement(Evento e) {
		if(e==null || !this.e.contains(e.getTitulo())) {
			return;
		}
		this.e.removeElement(e.getTitulo());
		this.validate();
		this.repaint();
	}
}
