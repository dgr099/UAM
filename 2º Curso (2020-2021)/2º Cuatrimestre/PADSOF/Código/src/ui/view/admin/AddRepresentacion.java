package ui.view.admin;

import static org.junit.jupiter.api.Assertions.fail;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import evento.Concierto;
import evento.Evento;
import ui.control.admin.ControlAddRepresentacion.ControlAddRepresentacion2;

// Vista para añadir una representacion 
public class AddRepresentacion extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = -6086343697095300896L;
	private JButton add = new JButton("Add");
	private JTextField fecha = new JTextField();
	private JTextField aforo = new JTextField();
	private JTextField max = new JTextField();
	private JTextField lim = new JTextField();
	private JTextField dur = new JTextField();
	private static Evento ev1;
	
	// Constructor de la vista
	public AddRepresentacion() {
		JPanel main = new JPanel();
		JPanel center = new JPanel();
		center.add(new JLabel("Fecha:"));
		center.add(fecha);
		center.add(new JLabel("Aforo: "));
		center.add(aforo);
		center.add(new JLabel("Max Reserva: "));
		center.add(max);
		center.add(new JLabel("Lim tiempo Reserva: "));
		center.add(lim);
		center.add(new JLabel("Dur Reserva: "));
		center.add(dur);
		center.setLayout(new GridLayout(5, 2));
		main.setLayout(new BorderLayout());
		main.add(center, BorderLayout.CENTER);
		main.add(add, BorderLayout.SOUTH);
		this.add(main);
		this.setViewportView(main);
	}
	
	/**
	 * Metodo para obtener la fecha introducida
	 * @return devuelve una fecha
	 */
	public String getFecha() {
		return this.fecha.getText();
	}
	
	/**
	 * Metodo para obtener el limite de tiempo introducido
	 * @return Devuelve un limite
	 */
	public String getLim() {
		return this.lim.getText();
	}
	
	/**
	 * Metodo para obtener la duracion introducida
	 * @return Devuelve una duracion
	 */
	public String getDur() {
		return this.dur.getText();
	}
	
	/**
	 * Metodo para obtener el maximo de aforo introducido
	 * @return Devuelve un maximo
	 */
	public String getMax() {
		return this.max.getText();
	}
	/**
	 * Metodo para obtener el aforo introducido
	 * @return Devuelve el aforo
	 */
	public String getAforo() {
		return this.aforo.getText();
	}
	
	//Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_StatEvento");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			setEv1(new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex"));
			c.add(new AddRepresentacion()); 
		} catch (Exception e) {
			fail();
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param controlAddRepresentacion2 contiene el controlador para añadir una representacion
	 */
	public void setControlador(ControlAddRepresentacion2 controlAddRepresentacion2) {
		this.add.addActionListener(controlAddRepresentacion2);
	}
	
	/**
	 * Metodo para obtener el evento de la representacion
	 * @return devuelve un evento
	 */
	public static Evento getEv1() {
		return ev1;
	}
	
	/**
	 * Metodo para actualizar el evento de una representacion
	 * @param ev1 contiene el nuevo evento
	 */
	public static void setEv1(Evento ev1) {
		AddRepresentacion.ev1 = ev1;
	}
}
