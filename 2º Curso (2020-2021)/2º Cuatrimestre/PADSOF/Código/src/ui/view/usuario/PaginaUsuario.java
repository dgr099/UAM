package ui.view.usuario;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;

import abonos.AbonoAnual;
import abonos.AbonoUsuario;
import entrada.Entrada;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.ControlBack;
import ui.control.usuario.ControlReservaUsuario;
import ui.control.usuario.ControlSeleccionAbono;
import ui.control.usuario.ControlSeleccionEntrada;
import ui.control.usuario.ControlUsuario;
import usuario.Notificacion;
import usuario.Usuario;

public class PaginaUsuario extends JScrollPane{

	private static final long serialVersionUID = 1L;
	private JList<String> entradas, abonos, mensajes;
	private JScrollPane scrollEntradas,
				scrollAbonos,
				scrollMensajes;
	
	private JLabel misEntradas = new JLabel("Mis entradas", SwingConstants.CENTER), 
		   misAbonos = new JLabel("Mis abonos", SwingConstants.CENTER),
		   misMensajes = new JLabel("Mis mensajes", SwingConstants.CENTER);
	
	
	private DefaultListModel<String> e = new DefaultListModel<>();
	private DefaultListModel<String> a = new DefaultListModel<>();
	private DefaultListModel<String> m = new DefaultListModel<>();
	
	private JButton btnEntradas = new JButton ( "Comprobar entrada" );
	private JButton btnAbonos = new JButton ( "Comprobar abono" );
	private JButton btnMensajes = new JButton ( "Comprobar mensaje" );
	private JButton back = new JButton();
	private JButton btnReservas = new JButton("Reservas");
	private JPanel main = new JPanel();
	private ControlUsuario cu;
	
	public ControlUsuario getControlUsuario() {
		return this.cu;
	}
	public void setControlador(ControlBack cb, ControlUsuario cu, ControlSeleccionEntrada ce, ControlSeleccionAbono ca, ControlReservaUsuario cr) {
		this.back.addActionListener(cb);
		this.cu = cu;
		this.btnEntradas.addActionListener(ce);
		this.btnAbonos.addActionListener(ca);
		this.btnReservas.addActionListener(cr);
	}
	
	public String getEntradaSeleccionada() {
		return this.entradas.getSelectedValue();
	}
	
	public String getAbonoSelected() {
		return this.abonos.getSelectedValue();
	}
	
	public String getMensaje() {
		return this.mensajes.getSelectedValue();
	}
	
	/**
	 * Método para añadir un abono de usuario a la lista de abonos de usuario
	 * @param a
	 */
	public void addElement(AbonoUsuario a) {
		if(a==null || this.a.contains(a.getCodigo()))	return;
		this.a.addElement(a.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para añadir una entrada a la lista de entradas de usuario
	 * @param e
	 */
	public void addElement(Entrada e) {
		if(e==null || this.e.contains(e.getCodigo()))	return;
		this.e.addElement(e.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para añadir notificaciones a la lista
	 * @param n notificación a añadir
	 */
	public void addElement(Notificacion n) {
		if(n==null)	return;
		this.m.addElement(n.getMensaje() + "\n-" + n.getFecha().getTime());
		this.validate();
		this.repaint();
	}
	public PaginaUsuario() {

		Usuario user = Sistema.getInstancia().getUsuarioEnUso();
		/*se crean las listas de abonos, entradas y notificaciones que tiene el usuario*/
		
		if(user!=null) {
			if(!user.getAbonos().isEmpty()) {
				for(AbonoUsuario abono: user.getAbonos())
					a.addElement(abono.getCodigo());
			}
			
			if(!user.getEntradas().isEmpty()) {
				for(Entrada entrada: user.getEntradas())
					e.addElement(entrada.getCodigo());
			}
			
			if(!user.getMensajes().isEmpty()) {
				for(Notificacion n : user.getMensajes()) {
					m.addElement(n.getMensaje() + "\n-" + n.getFecha().getTime());
				}
			}
			
		}
		
		entradas = new JList<>(e);
		abonos = new JList<>(a);
		mensajes = new JList<>(m);
		
		entradas.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		abonos.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		mensajes.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		this.scrollEntradas = new JScrollPane(entradas);
		this.scrollAbonos = new JScrollPane(abonos);
		this.scrollMensajes = new JScrollPane(mensajes);

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
		north.add(this.misEntradas, constraints);
		constraints.gridx = 1;
		constraints.gridy = 0;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(this.misAbonos, constraints);
		constraints.gridx = 2;
		constraints.gridy = 0;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(this.misMensajes, constraints);
		constraints.gridx = 0;
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.weighty = 1.0;
		constraints.weightx = 1.0;
		north.add(scrollEntradas, constraints);
		constraints.gridx = 1;
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(scrollAbonos, constraints);
		constraints.gridx = 2;
		constraints.gridy = 1;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(scrollMensajes, constraints);
		constraints.fill = GridBagConstraints.NONE;
		constraints.weighty = 0;
		constraints.weightx = 0;
		constraints.gridx = 0;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnEntradas, constraints);
		constraints.gridx = 1;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnAbonos, constraints);
		constraints.gridx = 2;
		constraints.gridy = 2;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		north.add(btnMensajes, constraints);
		south.add(this.back);
		south.add(this.btnReservas);
		main.add(north, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		
		this.btnMensajes.addActionListener ( new ActionListener () {
			@Override
			public  void actionPerformed (ActionEvent e) {
				if(mensajes.getSelectedValue() == null)
		  			JOptionPane.showMessageDialog(null, "No se ha seleccionado ningún mensaje", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				else
		  			JOptionPane.showMessageDialog(null, mensajes.getSelectedValue(), "Mensaje", JOptionPane.INFORMATION_MESSAGE);
			}
	    });
		
		this.add(main);
		main.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main);
	}
	
	public void update() {
		Usuario user = Sistema.getInstancia().getUsuarioEnUso();
		if(user!=null) {
			e.clear();
			a.clear();
			m.clear();
			if(!user.getAbonos().isEmpty()) {
				for(AbonoUsuario abono: user.getAbonos())
					a.addElement(abono.getCodigo());
			}
			
			if(!user.getEntradas().isEmpty()) {
				for(Entrada entrada: user.getEntradas())
					e.addElement(entrada.getCodigo());
			}
			if(!user.getMensajes().isEmpty()) {
				for(Notificacion n : user.getMensajes()) {
					m.addElement(n.getMensaje() + "\n-" + n.getFecha().getTime());
				}
			}		
		}
		
		this.validate();
		this.repaint();
		return;
	}
	public static void main (String...args) {
		try {
			Usuario u = new Usuario("Prueba", "123");
			Sistema.getInstancia().setUsuarioEnUso(u);
			for(int i=0; i!=100; i++)
				u.addAbonos(new AbonoUsuario(new AbonoAnual(30, new ZonaNoNumerada("Prueba", 20))));
			u.getNotificaciones().add("Prueba");
			u.addNotificacion("prueba");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		PaginaUsuario pu = new PaginaUsuario();
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
