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

import ui.control.teatro.ControlAñadirZona2;

/*Vista para añadir zona*/
public class AñadirZona extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	JButton add = new JButton("Añadir"); //botón de añadir
	JTextField name = new JTextField(10); //para poner el nombre
	JTextField rows = new JTextField(4); //para poner las filas
	JTextField col = new JTextField(4); //para poner las columnas
	JTextField aforo = new JTextField(4);
	
	/**
	 * Método para obtener las filas escritas
	 * @return string con lo escrito en el recuadro para las filas
	 */
	public String getFilas() {
		return this.rows.getText();
	}
	
	/**
	 * Método para obtener las columnas escritas
	 * @return string con lo escrito en el recuadro para las columnas
	 */
	public String getColumnas() {
		return this.col.getText();
	}
	
	/**
	 * Método para obtener el nombre de la zona a añadir
	 * @return string con el nombre escrito en el recuadro para el nombre
	 */
	public String getNombre() {
		return this.name.getText();
	}
	
	/**
	 * Método para obtener el aforo de la zona
	 * @return string con lo escrito en el recuadro para escribir el aforo
	 */
	public String getAforo() {
		return this.aforo.getText();
	}
	
	/**
	 * Método para establecer el controlador de añadir zona
	 * @param add controla para añadir zona
	 */
	public void setControlador(ControlAñadirZona2 add) {
		this.add.addActionListener(add);
	}

	public AñadirZona(){ /*constructor*/
		JPanel main = new JPanel();
		JLabel nombreZona = new JLabel("Nombre Zona: ");
		JLabel aforoZona = new JLabel("Aforo Zona:");
		JLabel filas = new JLabel("Filas: ");
		JLabel columnas = new JLabel("Columnas: ");
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(4, 2)); //pones el layout
		f.add(nombreZona);
		f.add(this.name);
		
		f.add(aforoZona);
		f.add(this.aforo);
		
		f.add(filas);
		f.add(this.rows);
		
		f.add(columnas);
		f.add(this.col);
		main.add(f, BorderLayout.CENTER);
		main.add(this.add, BorderLayout.SOUTH);
		f.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new AñadirZona());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
		return;
	}
}