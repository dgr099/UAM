package ui.view.teatro;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import teatro.ZonaNoNumerada;
import ui.control.teatro.ControlAplicarZonaNoNumerada;
import ui.control.teatro.ControlQuitarZona;

/**
 * Clase con la vista ppara mostrar una zona no numerada
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class UIZonaNoNumerada extends JScrollPane{
	private ZonaNoNumerada z;
	private JFrame frame;
	private JButton aplicar = new JButton("Aplicar");
	private JButton rem = new JButton("Remove");
	private static final long serialVersionUID = 4256175980103227849L;
	JTextField aforo = new JTextField(4);
	
	/**
	 * Método para obtener el aforo escrito en la vista
	 * @return
	 */
	public String getAforo() {
		return this.aforo.getText();
	}

	/**
	 * Constructor de la clase
	 * @param zonaNoNumerada zona no numerada que se quiere mostrar
	 * @param frame ventana
	 * @param p
	 */
	public UIZonaNoNumerada(ZonaNoNumerada zonaNoNumerada, JFrame frame, UITeatroListaZonasNoNumeradas p){ /*constructor*/
		JPanel main = new JPanel();
		JLabel nombreZona = new JLabel("Nombre Zona: ");
		JLabel nombre = new JLabel(zonaNoNumerada.getNombre());
		JLabel aforoZona = new JLabel("Aforo Zona:");
		main.setLayout(new GridLayout(3, 2));
		main.add(nombreZona);
		main.add(nombre);
		main.add(aforoZona);
		main.add(aforo);
		main.add(aplicar);
		aplicar.addActionListener(new ControlAplicarZonaNoNumerada(zonaNoNumerada, this));
		main.add(rem);
		rem.addActionListener(new ControlQuitarZona(zonaNoNumerada, frame, p));
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	//main para ver la vista
	public static void main(String... args) throws Exception {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new UIZonaNoNumerada(new ZonaNoNumerada("prueba", 10), ventana, null));
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
		return;
	}

	public JFrame getFrame() {
		return frame;
	}

	public void setFrame(JFrame frame) {
		this.frame = frame;
	}


	public ZonaNoNumerada getZ() {
		return z;
	}

	public void setZ(ZonaNoNumerada z) {
		this.z = z;
	}
}