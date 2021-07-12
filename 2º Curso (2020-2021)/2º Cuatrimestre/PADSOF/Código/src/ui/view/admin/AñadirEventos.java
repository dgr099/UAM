package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.AbonoAnual;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.ControlBack;
import ui.control.admin.ControlAddConcierto;
import ui.control.admin.ControlAddDanza;
import ui.control.admin.ControlAddObraTeatro;
import ui.control.admin.ControlAddPrecioEvento;

/* Vista para añadir eventos */
public class AñadirEventos extends JScrollPane{

	private static final long serialVersionUID = 1L;
	JButton añadirObra = new JButton("Añadir obra");
	JButton añadirDanza = new JButton("Añadir danza");
	JButton añadirConcierto = new JButton("Añadir concierto");
	JButton back = new JButton();
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param cac contiene el controlador para añadir un concierto
	 * @param cad contiene el controlador para añadir una danza
	 * @param cao contiene el controlador para añadir una obra de teatro
	 * @param cap contiene el controlador para añadir un precio a un evento
	 */
	public void setControlador(ControlBack cb, ControlAddConcierto cac, ControlAddDanza cad, ControlAddObraTeatro cao, ControlAddPrecioEvento cap) {
		this.back.addActionListener(cb);
		this.añadirConcierto.addActionListener(cac);
		this.añadirDanza.addActionListener(cad);
		this.añadirObra.addActionListener(cao);
		cad.setControlAddPrecioEvento(cap);
		cac.setControlAddPrecioEvento(cap);
		cao.setControlAddPrecioEvento(cap);
	}
	
	// Constructor de la vista
	public AñadirEventos () {
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		JPanel center = new JPanel();
		center.add(añadirObra);
		center.add(añadirDanza);
		center.add(añadirConcierto);
		
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
		main.add(center, BorderLayout.CENTER);
		main.add(this.back, BorderLayout.SOUTH);
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		/*añadirObra.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFrame nuevaObra = new JFrame();
				AddObraTeatro aot = new AddObraTeatro(nuevaObra);
				nuevaObra.getContentPane().add(aot);
				nuevaObra.setVisible(true);
				nuevaObra.setSize(400, 400);
			}
		});
		
		añadirDanza.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFrame nuevaDanza = new JFrame();
				AddDanza ad = new AddDanza(nuevaDanza);
				nuevaDanza.getContentPane().add(ad);
				nuevaDanza.setVisible(true);
				nuevaDanza.setSize(400, 400);
			}
		});
		
		añadirConcierto.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFrame nuevoConcierto = new JFrame();
				AddConcierto ac = new AddConcierto(nuevoConcierto);
				nuevoConcierto.getContentPane().add(ac);
				nuevoConcierto.setVisible(true);
				nuevoConcierto.setSize(400, 400);
			}
		});*/
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		try {
			c.add(new AñadirEventos());
		} catch (Exception e) {
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	
}
