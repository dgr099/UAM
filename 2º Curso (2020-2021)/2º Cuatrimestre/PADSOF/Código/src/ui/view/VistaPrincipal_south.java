package ui.view;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import ui.control.ControlVista_South_iniciado;
import ui.control.ControlVista_South_sin_iniciar;

public class VistaPrincipal_south extends JPanel{
	JButton login = new JButton("Login");
	JButton register = new JButton("Register");
	JButton user = new JButton("user");
	JButton logout = new JButton("log out");
	CardLayout l = new CardLayout();
	JPanel sin_iniciar = new JPanel();
	JPanel iniciado = new JPanel();
	/**
	 * 
	 */
	public JButton getUser() {
		return this.user;
	}
	public void setControlador(ControlVista_South_sin_iniciar control, ControlVista_South_iniciado control2) {
		this.login.addActionListener(control);
		this.register.addActionListener(control);
		this.user.addActionListener(control2);
		this.logout.addActionListener(control2);
	}
	private static final long serialVersionUID = -4391841094348300046L;
	public VistaPrincipal_south() {
		this.setLayout(l); /*estableces el cardLayout*/
		SpringLayout sl = new SpringLayout();
		sin_iniciar.setLayout(sl);
		sin_iniciar.add(login);
		sin_iniciar.add(register);
		sl.putConstraint(SpringLayout.EAST, register, -10, SpringLayout.EAST, this.sin_iniciar);
		sl.putConstraint(SpringLayout.EAST, login, -10, SpringLayout.WEST, register);
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, login, 0, SpringLayout.VERTICAL_CENTER, sin_iniciar);
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, register, 0, SpringLayout.VERTICAL_CENTER, sin_iniciar);
		iniciado.setLayout(new BorderLayout());
		JPanel aux = new JPanel();
		logout.setBackground(Color.red);
		aux.add(logout);	aux.add(user);
		iniciado.add(aux, BorderLayout.EAST);
		user.setIcon(new ImageIcon(new ImageIcon("./asserts/user.png").getImage().getScaledInstance(40, 40, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		user.setOpaque(false);
		user.setContentAreaFilled(false);
		user.setBorderPainted(false);
		user.setSize(10, 10);
		this.add(iniciado, "iniciado");
		this.add(sin_iniciar, "sin_iniciar");
		this.mostrarPanel("sin_iniciar"); //comienza sin iniciar
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new VistaPrincipal_south());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.setPreferredSize(new Dimension(200, 200));
		//dimensiones mínimas para el login
		ventana.pack();
		return;
	}
	public void mostrarPanel(String nombre) {
		this.l.show(this, nombre);
	}
	
}
