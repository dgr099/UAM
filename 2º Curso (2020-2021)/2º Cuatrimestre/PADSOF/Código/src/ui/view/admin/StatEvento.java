package ui.view.admin;

import static org.junit.jupiter.api.Assertions.fail;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Font;
import java.awt.Image;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Evento;
import ui.control.ControlBack;
import ui.control.admin.ControlAddRepresentacion;
import ui.control.admin.ControlCambiarFechaRepresentacion;
import ui.control.admin.ControlCancelAdmin;
import ui.control.admin.ControlCancelarRepresentacion;
import ui.control.admin.ControlVerComentario;

// Vista para las estadisticas de un evento
public class StatEvento extends JScrollPane{

	/**
	 * 
	 */
	private static final long serialVersionUID = -4761272741429800603L;
	private JButton back = new JButton();
	private JLabel descripcion = new JLabel();
	private JLabel nombre = new JLabel();
	private JLabel ingresos = new JLabel("-Ingresos: "/* + est_evento[3]*/);
	private JLabel ocupacion = new JLabel("-Ocupacion: "/* + est_evento[1]*/);
	private JLabel abonos = new JLabel("-Abonos: "/* + est_evento[2]*/);
	private JLabel estrellas = new JLabel("-Estrellas: ");
	private JButton representacion = new JButton("Add Representacion");
	private boolean enUso = false;
	private PaginaEventoAdmin padmin;
	private Evento e = null;
	private static Evento ev1;
	
	/**
	 * Metodo para obtener un evento
	 * @return devuelve el evento
	 */
	public Evento getEvento() {
		return this.e;
	}
	/**
	 * Metodo para obtener la vista de la pagina de eventos del administrador
	 * @return devuelve la vista
	 */
	public PaginaEventoAdmin getPaginaEventoAdmin() {
		return this.padmin;
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cvp contiene el controlador para cancelar del admin
	 * @param car contiene el controlador para añadir una representacion
	 * @param cb contiene el controlador del boton de back
	 * @param ccr contiene el controlador para cancelar una representacion
	 * @param cvc contiene el controlador para ver un comentario
	 * @param cfr contiene el controlador para cambiar la fecha de una representacion
	 */
	public void setControlador(ControlCancelAdmin cvp, ControlAddRepresentacion car, ControlBack cb , ControlCancelarRepresentacion ccr, ControlVerComentario cvc, ControlCambiarFechaRepresentacion cfr) {
		this.back.addActionListener(cvp);
		this.representacion.addActionListener(car);
		this.padmin.setControlador(cb, ccr, cvc, cfr);
	}
	
	/**
	 * Metodo para obtener el nombre
	 * @return devuelve el nombre
	 */
	public String getNombre() {
		return this.nombre.getText();
	}
	
	// Constructor de la vista
	public StatEvento(){
		this.padmin = new PaginaEventoAdmin();
		JPanel main = new JPanel();
		nombre.setFont(new Font("Serif", Font.BOLD, 15));
		nombre.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		descripcion.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		
		double est_evento[] = {0, 0, 0, 0, 0};
		
		ingresos = new JLabel("-Ingresos: " + est_evento[3]);
		ocupacion = new JLabel("-Ocupacion: " + est_evento[1]);
		abonos = new JLabel("-Abonos: " + est_evento[2]);
		if(est_evento[4]>=0)
			estrellas = new JLabel("-Estrellas: " + est_evento[4]);
		else {
			estrellas = new JLabel("-Estrellas: " + "Sin Valoraciones");
		}
		JPanel main_2 = new JPanel();
		JPanel south = new JPanel();
		JPanel north = new JPanel();
		north.setLayout(new BoxLayout(north, BoxLayout.Y_AXIS));
		
		main_2.setLayout(new BorderLayout());
		main_2.add(this.padmin, BorderLayout.CENTER);
		main_2.add(south, BorderLayout.SOUTH);
		main_2.add(north, BorderLayout.NORTH);
		north.add(nombre);
		north.add(descripcion);
		main.add(ingresos);
		north.add(main);
		main.add(ocupacion);
		main.add(abonos);
		main.add(estrellas);
		main.add(representacion);
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
		south.add(back);
		south.add(representacion);
		
		south.setVisible(true);
		main.setVisible(true);
		main_2.setVisible(true);
		this.add(main_2);
		//main_2.setPreferredSize(new Dimension(600, 300));
		this.setViewportView(main_2);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		Evento evento = new Concierto("123", 123, "123", "123", "123", "123", "123");
		JFrame ventana = new JFrame("Pruebas_StatEvento");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			setEv1(new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex"));
			StatEvento vista = new StatEvento(); 
			c.add(vista);
			vista.setEvento(evento);
		} catch (Exception e) {
			fail();
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
	
	/**
	 * Metodo para actualizar el evento
	 * @param e contiene el evento
	 */
	public void setEvento(Evento e) {
		if(e==null) {
			return;
		}
		this.e = e;
		double est_evento[] = e.getEstadisticas();
		this.nombre.setText(e.getTitulo());
		this.descripcion.setText(e.getDescripcion());
		this.ingresos.setText("-Ingresos: " + est_evento[3]);
		this.ocupacion.setText("-Ocupacion: " + est_evento[1]);
		this.abonos.setText("-Abonos: " + est_evento[2]);
		if(est_evento[4]>=0) {
			this.estrellas.setText("-Estrellas: " + est_evento[4]);
		}else {
			this.estrellas.setText("-Estrellas: " + "Sin Valoraciones");
		}
		this.padmin.updateEvento(e);
	}
	
	/**
	 * Metodo para obtener el evento
	 * @return devuelve el evento
	 */
	public static Evento getEv1() {
		return ev1;
	}
	
	/**
	 * Metodo para cambiar de evento
	 * @param ev1 contiene el nuevo evento
	 */
	public static void setEv1(Evento ev1) {
		StatEvento.ev1 = ev1;
	}
	
	/**
	 * Metodo para comprobar si esta en uso la vista
	 * @return devuelve un booleano
	 */
	public Boolean getEnUso() {
		return this.enUso;
	}
	
	/**
	 * Metodo para cambiar si esta en uso la vista o no 
	 * @param b contiene el booleano con el estado
	 */
	public void setEnUso(Boolean b) {
		this.enUso = b;
	}
}
