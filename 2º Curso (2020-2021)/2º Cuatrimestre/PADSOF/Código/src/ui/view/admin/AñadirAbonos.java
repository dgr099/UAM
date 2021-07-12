package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import sistema.Sistema;
import ui.control.ControlBack;
import ui.control.admin.ControlAñadirAbono;

// Vista para añadir abonos
public class AñadirAbonos extends JScrollPane {

	private static final long serialVersionUID = 1L;
	JButton añadirCiclo = new JButton("Añadir abono ciclo");
	JButton añadirAnual = new JButton("Añadir abono anual");
	JButton back = new JButton();
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cb contiene el controlador del boton de back
	 * @param caa contiene el controlador para añadir un abono
	 */
	public void setControlador(ControlBack cb, ControlAñadirAbono caa) {
		back.addActionListener(cb);
		this.añadirAnual.addActionListener(caa);
		this.añadirCiclo.addActionListener(caa);
	}
	
	// Constructor de la vista
	public AñadirAbonos () {
		JPanel main = new JPanel();
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
		main.setLayout(new BorderLayout());
		JPanel north = new JPanel();
		north.add(añadirCiclo);
		north.add(añadirAnual);
		main.add(north, BorderLayout.NORTH);
		JPanel south = new JPanel();
		main.add(south, BorderLayout.SOUTH);
		south.add(this.back);
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_Add_Abono");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto1", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto2", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto3", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto4", "DGR", "CerraOrquesta", "German", "Willyrex"));		} catch (Exception e1) {
			e1.printStackTrace();
		}
		try {
			c.add(new AñadirAbonos());
		} catch (Exception e) {
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	
}
