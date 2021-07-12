package ui.view.admin;

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

import ui.control.admin.ControlAddPrecioEvento;
import ui.control.admin.ControlAddObraTeatro.ControlAddObraTeatro2;

// Vista para añadir una obra de teatro
public class AddObraTeatro extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	JButton add = new JButton("Añadir Evento");
	JTextField titulo = new JTextField(10); 
	JTextField descripcion = new JTextField(100); 
	//JTextField precio = new JTextField(10); 
	JTextField duracion = new JTextField(10);
	JTextField autor = new JTextField(10);
	JTextField director = new JTextField(10);
	JTextField compania = new JTextField(10);
	private JButton precio = new JButton("Precio Zonas");
	
	/**
	 * Metodo para obtener el titulo introducido
	 * @return devuelve el titulo
	 */
	public String getTitulo() {
		return this.titulo.getText();
	}
	
	/**
	 * Metodo para obtener la descripcion de la obra introducida
	 * @return devuelve una descripcion
	 */
	public String getDescripcion() {
		return this.descripcion.getText();
	}
	
	/*public String getPrecio() {
		return this.precio.getText();
	}*/
	
	/**
	 * Metodo para obtener la duracion del evento
	 * @return devuelve una duracion
	 */
	public String getDuracion() {
		return this.duracion.getText();
	}
	
	/**
	 * Metodo para obtener el autor introducido
	 * @return devuelve un nombre de autor
	 */
	public String getAutor() {
		return this.autor.getText();
	}
	
	/**
	 * Metodo para obtener el director de la obra introducido
	 * @return devuelve el nombre del director
	 */
	public String getDirector() {
		return this.director.getText();
	}
	
	/**
	 * Metodo para obtener la compañia del evento
	 * @return devuelve el nombre de la compañia
	 */
	public String getCompania() {
		return this.compania.getText();
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cao contiene el controlador para añadir una obra de teatro
	 * @param cpe contiene el controlador para añadir el precio a la obra
	 */
	public void setControlador(ControlAddObraTeatro2 cao, ControlAddPrecioEvento cpe) {
		this.add.addActionListener(cao);
		this.precio.addActionListener(cpe);
	}
	
	// constructor de la vista
	public AddObraTeatro(){ 
		JPanel main = new JPanel();
		JLabel tituloEvento = new JLabel("Titulo: ");
		JLabel descripcionEvento = new JLabel("Descripcion:");
		//JLabel precioEvento = new JLabel("Precio: ");
		JLabel duracionEvento = new JLabel("Duracion: ");
		JLabel autorEvento = new JLabel("Autor: ");
		JLabel directorEvento = new JLabel("Director: ");
		JLabel companiaEvento = new JLabel("Compania: ");
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(7, 2)); 
		
		f.add(tituloEvento);
		f.add(this.titulo);
		
		f.add(descripcionEvento);
		f.add(this.descripcion);
		
		/*f.add(precioEvento);
		f.add(this.precio);*/
		
		f.add(duracionEvento);
		f.add(this.duracion);
		
		f.add(autorEvento);
		f.add(this.autor);
		
		f.add(directorEvento);
		f.add(this.director);
		
		f.add(companiaEvento);
		f.add(this.compania);
		
		f.add(this.add);
		f.add(this.precio);
		main.add(f, BorderLayout.CENTER);
		
		f.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		c.add(new AddObraTeatro());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}