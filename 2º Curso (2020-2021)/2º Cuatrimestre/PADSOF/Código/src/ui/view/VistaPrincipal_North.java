package ui.view;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import ui.control.ControlVista_North;
import ui.control.ControlVista_North_admin;

public class VistaPrincipal_North extends JScrollPane{
	private JButton abonos = new JButton("Abonos");
	private JButton cartelera = new JButton("Cartelera");
	private JButton danza = new JButton("Danza");
	private JButton musica = new JButton("Música");
	private JButton teatro = new JButton("Teatro");
	private JButton mejorValorados = new JButton("Más Valorados");
	
	private JButton eventos = new JButton("Añadir Eventos o Abonos");
	private JButton configuracion = new JButton("Configuracion Teatro");
	private JButton estadisticas = new JButton("Eventos");
	private CardLayout l = new CardLayout();
	private JPanel user = new JPanel();
	private JPanel admin = new JPanel();
	private JButton last;
	private JPanel main = new JPanel();
	/**
	 * @return the abonos
	 */
	public JButton getAbonos() {
		return abonos;
	}
	/**
	 * @return the cartelera
	 */
	public JButton getCartelera() {
		return cartelera;
	}
	/**
	 * @return the danza
	 */
	public JButton getDanza() {
		return danza;
	}
	/**
	 * @return the musica
	 */
	public JButton getMusica() {
		return musica;
	}
	/**
	 * @return the teatro
	 */
	public JButton getTeatro() {
		return teatro;
	}
	/**
	 * @return the eventos
	 */
	public JButton getEventos() {
		return eventos;
	}
	/**
	 * @return the configuracion
	 */
	public JButton getConfiguracion() {
		return configuracion;
	}
	/**
	 * @return the estadisticas
	 */
	public JButton getEstadisticas() {
		return estadisticas;
	}
	/**
	 * @return the user
	 */
	public JPanel getUser() {
		return user;
	}
	/**
	 * @return the admin
	 */
	public JPanel getAdmin() {
		return admin;
	}
	/**
	 * @return the main
	 */
	public JPanel getMain() {
		return main;
	}
	/**
	 * 
	 */
	public JButton getLast() {
		return this.last;
	}
	public void setLast(JButton newlast) {
		this.last = newlast;
	}
	public void setControlador(ControlVista_North control, ControlVista_North_admin controlAdmin) {
		abonos.addActionListener(control);
		musica.addActionListener(control);
		danza.addActionListener(control);
		cartelera.addActionListener(control);
		teatro.addActionListener(control);
		mejorValorados.addActionListener(control);
		eventos.addActionListener(controlAdmin);
		configuracion.addActionListener(controlAdmin);
		estadisticas.addActionListener(controlAdmin);
		
	}
	
	private static final long serialVersionUID = -4391841094348300046L;
	public VistaPrincipal_North() {
		main = new JPanel();
		main.setLayout(l);
		user.setLayout(new GridLayout(1, 6));
		user.add(abonos).setForeground(Color.gray);
		abonos.setFont(new Font("Arial", Font.PLAIN, 12));
		user.add(cartelera).setForeground(Color.gray);
		cartelera.setFont(new Font("Arial", Font.PLAIN, 12));
		user.add(danza).setForeground(Color.gray);
		danza.setFont(new Font("Arial", Font.PLAIN, 12));
		user.add(musica).setForeground(Color.gray);
		musica.setFont(new Font("Arial", Font.PLAIN, 12));
		user.add(teatro).setForeground(Color.gray);
		teatro.setFont(new Font("Arial", Font.PLAIN, 12));
		user.add(mejorValorados).setForeground(Color.gray);
		mejorValorados.setFont(new Font("Arial", Font.PLAIN, 12));
		main.add(user, "user");
		admin.setLayout(new GridLayout(1, 3));
		admin.add(eventos).setForeground(Color.gray);
		eventos.setFont(new Font("Arial", Font.PLAIN, 12));
		admin.add(configuracion).setForeground(Color.gray);
		configuracion.setFont(new Font("Arial", Font.PLAIN, 12));
		admin.add(estadisticas).setForeground(Color.gray);
		estadisticas.setFont(new Font("Arial", Font.PLAIN, 12));
		main.add(admin, "admin");
		this.mostrarPanel("user");
		main.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(600, 30));
		this.setViewportView(main);
		last=this.cartelera;
		last.setForeground(Color.BLUE);
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new VistaPrincipal_North());
		ventana.setVisible(true);
		ventana.pack();
		return;
	}
	public void mostrarPanel(String nombre) {
		this.l.show(main, nombre);
		if(nombre.equals("user")) {
			last = this.cartelera;
		}
		else {
			last = this.estadisticas;
		}
		abonos.setForeground(Color.GRAY);
		danza.setForeground(Color.GRAY);
		musica.setForeground(Color.GRAY);
		teatro.setForeground(Color.GRAY);
		mejorValorados.setForeground(Color.GRAY);
		eventos.setForeground(Color.GRAY);
		configuracion.setForeground(Color.GRAY);
		last.setForeground(Color.BLUE);
	}
	
}
