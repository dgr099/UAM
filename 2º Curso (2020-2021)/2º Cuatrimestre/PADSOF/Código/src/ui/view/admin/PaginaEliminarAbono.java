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

import abonos.Abono;
import evento.Concierto;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlBack;
import ui.control.admin.ControlDelAbono;
import usuario.Usuario;

/* Vista para eliminar un abono */
public class PaginaEliminarAbono extends JScrollPane{

	private static final long serialVersionUID = 1L;
	JList<String> abonos;
	JScrollPane scrollAbono;
	
	JLabel labono = new JLabel("Abono", SwingConstants.CENTER);
	
	
	DefaultListModel<String> a = new DefaultListModel<>();
	
	JButton bntAbono = new JButton ( "Borrar Abono" );
	JButton back = new JButton();
	JPanel main = new JPanel();

	/**
	 * Metodo para acutalizar los controladores de los elementos de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param cda contiene el controlador para borrar un abono
	 */
	public void setControlador(ControlBack cb, ControlDelAbono cda) {
		this.back.addActionListener(cb);
		this.bntAbono.addActionListener(cda);
	}
	
	/**
	 * Metodo para obtener el abono seleccionado
	 * @return Devuelve el abono seleccionado
	 */
	public String getAbonoSelectedValue() {
		return this.abonos.getSelectedValue();
	}
	
	/**
	 * Método para eliminar un abono de la lista
	 * @param a Abono a eliminar
	 */
	public void removeElement(Abono a) {
		if(a==null)	return;
		if(this.a.contains(a.getCodigo())) {
			this.a.removeElement(a.getCodigo());
			this.validate();
			this.repaint();
		}
		
	}
	
	/**
	 * Método para añadir elemento a la lista
	 * @param a Abono a añadir
	 */
	public void addElement(Abono a) {
		if(a==null)	return;
		if(this.a.contains(a.getCodigo())) {
			return;
		}
		this.a.addElement(a.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/* Constructor de la vista */
	public PaginaEliminarAbono() {
		/*se crean las listas de abonos, entradas y notificaciones que tiene el usuario*/
		for(Abono a : Sistema.getInstancia().getAbonos()) { /*añades la representaciones a la lista*/
			this.a.addElement(a.getCodigo());
		}
		
		abonos = new JList<>(a);
		
		abonos.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		this.scrollAbono = new JScrollPane(abonos);

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
		north.add(this.labono, constraints);
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.weighty = 1.0;
		constraints.weightx = 1.0;
		north.add(this.scrollAbono, constraints);
		constraints.fill = GridBagConstraints.NONE;
		constraints.weighty = 0;
		constraints.weightx = 0;
		constraints.gridx = 0;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(bntAbono, constraints);
		south.add(this.back);
		main.add(north, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		
		this.add(main);
		main.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main);
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario
	 */
	public void update() {
		a.clear();
		for(Abono a : Sistema.getInstancia().getAbonos()) { /*añades la representaciones a la lista*/
			this.a.addElement(a.getCodigo());
		}
		this.validate();
		this.repaint();
		return;
	}
	
	// main para probar la vista del panel
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
		PaginaEliminarAbono pu = new PaginaEliminarAbono();
		JFrame ventana = new JFrame("Prueba_Usuario");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		//pu.update();
		c.add(pu);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
}
