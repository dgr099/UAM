package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import ui.control.ControlBack;
import ui.control.admin.ControlPaginaEventosAdmin;

/* Vista de la pagina para añadir eventos o abonos */
public class PaginaAddEventosOAbonos extends JScrollPane {

	private static final long serialVersionUID = 1L;
	JButton crearEvento = new JButton("Crear evento");
	JButton eliminarEvento = new JButton("Eliminar evento");
	JButton añadirAbono = new JButton("Añadir abono");
	JButton eliminarAbono = new JButton("Eliminar abono");
	JButton back = new JButton();
	JPanel PaginaEventosAdmin = new JPanel();	
	
	/**
	 * Metodo para actualizar los controladores para los elementos de la vista
	 * @param c contiene el controlador de la pagina de eventos
	 * @param cb contiene el controlador del boton de back
	 */
	public void setControlador(ControlPaginaEventosAdmin c, ControlBack cb) {
		crearEvento.addActionListener(c);
		eliminarEvento.addActionListener(c);
		añadirAbono.addActionListener(c);
		eliminarAbono.addActionListener(c);
		back.addActionListener(cb);
	}
	
	// Constructor de la vista
	public PaginaAddEventosOAbonos() {
		JPanel main = new JPanel();
		main.setLayout(new GridLayout(0,1));
		main.add(PaginaEventosAdmin);
		main.add(back);
		PaginaEventosAdmin.setLayout(new GridLayout(2,2));
		/*main.setPreferredSize(new Dimension(400, 400));*/
		crearEvento.setText("Crear evento");
		eliminarEvento.setText("Eliminar evento");
		añadirAbono.setText("Añadir abono");
		eliminarAbono.setText("Eliminar abono");
		PaginaEventosAdmin.add(crearEvento);
		PaginaEventosAdmin.add(eliminarEvento);
		PaginaEventosAdmin.add(añadirAbono);
		PaginaEventosAdmin.add(eliminarAbono);
		
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main (String...args) {
		JFrame ventana = new JFrame("Pagina eventos admin");
		PaginaAddEventosOAbonos pea = new PaginaAddEventosOAbonos();
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(pea);
		ventana.setSize(400, 400);
		ventana.setVisible(true);
		ventana.pack();
		return;
	}
}
