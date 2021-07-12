package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

import ui.control.admin.ControlCambiarFechaRepresentacion.ControlCambiarFechaRepresentacion2;

/* Vista para modificar una representacion */
public class CambiarRepresentacion extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 2968676464753291936L;
	private JButton aceptar = new JButton("Guardar Cambios");
	private JTextField fecha = new JTextField();
	
	/**
	 * Metodo para conseguir la fecha introducida
	 * @return Devuelve una fecha
	 */
	public String getFecha() {
		return this.fecha.getText();
	}
	
	/**
	 * Metodo para actualizar el controlador de la vista
	 * @param cfr contiene el controlador para modificar la fecha de la representacion
	 */
	public void setControlador(ControlCambiarFechaRepresentacion2 cfr) {
		this.aceptar.addActionListener(cfr);
	}
	
	// Constructor de la vista
	public CambiarRepresentacion() {
		JPanel main = new JPanel();
		SpringLayout sl = new SpringLayout();
		main.setLayout(sl);
		JLabel lfecha = new JLabel("Introducir Fecha:");
		main.add(lfecha);
		main.add(fecha);
		main.add(aceptar);
		sl.putConstraint(SpringLayout.NORTH, lfecha, 10, SpringLayout.NORTH, main);
		sl.putConstraint(SpringLayout.NORTH, fecha, 10, SpringLayout.NORTH, main);
		sl.putConstraint(SpringLayout.SOUTH, fecha, -10, SpringLayout.NORTH, aceptar);
		sl.putConstraint(SpringLayout.SOUTH, lfecha, -10, SpringLayout.NORTH, aceptar);
		
		sl.putConstraint(SpringLayout.WEST, lfecha, 10, SpringLayout.WEST, main);
		sl.putConstraint(SpringLayout.WEST, fecha, 10, SpringLayout.EAST, lfecha);
		sl.putConstraint(SpringLayout.EAST, fecha, -10, SpringLayout.EAST, main);
		

		sl.putConstraint(SpringLayout.WEST, aceptar, 10, SpringLayout.WEST, main);
		sl.putConstraint(SpringLayout.EAST, aceptar, -10, SpringLayout.EAST, main);
		sl.putConstraint(SpringLayout.SOUTH, aceptar, -10, SpringLayout.SOUTH, main);
		main.setPreferredSize(new Dimension(250, 80));
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new CambiarRepresentacion());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
		return;
	}

}
