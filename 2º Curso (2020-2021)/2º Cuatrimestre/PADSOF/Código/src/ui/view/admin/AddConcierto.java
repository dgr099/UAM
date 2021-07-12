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

import ui.control.admin.ControlAddConcierto.ControlAddConcierto2;
import ui.control.admin.ControlAddPrecioEvento;

// Vista para añadir un concierto
public class AddConcierto extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	private JButton add = new JButton("Añadir Evento");
	private JTextField titulo = new JTextField(10); 
	private JTextField descripcion = new JTextField(100); 
	//JTextField precio = new JTextField(10); 
	private JTextField duracion = new JTextField(10);
	private JTextField autor = new JTextField(10);
	private JTextField director = new JTextField(10);
	private JTextField orquesta = new JTextField(10);
	private JTextField solista = new JTextField(10);
	private JButton precio = new JButton("Precio Zonas");
	
	/**
	 * Metodo para obtener el titulo introducido
	 * @return devuelve el titulo
	 */
	public String getTitulo() {
		return this.titulo.getText();
	}

	/**
	 * Metodo para obtener la descripcion introducida
	 * @return devuelve la descripcion
	 */
	public String getDescripcion() {
		return this.descripcion.getText();
	}
	
	/*public String getPrecio() {
		return this.precio.getText();
	}*/
	
	/**
	 * Metodo para obtener la duracion introducida
	 * @return devuelve la duracion
	 */
	public String getDuracion() {
		return this.duracion.getText();
	}
	
	/**
	 * Metodo para obtener el autor introducido
	 * @return devuelve el autor
	 */
	public String getAutor() {
		return this.autor.getText();
	}
	
	/**
	 * Metodo para obtener el director introducido
	 * @return devuelve el director
	 */
	public String getDirector() {
		return this.director.getText();
	}
	
	/**
	 * Metodo para obtener la orquesta introducida
	 * @return devuelve la orquesta
	 */
	public String getOrquesta() {
		return this.orquesta.getText();
	}
	
	/**
	 * Metodo para obtener el solista introducido
	 * @return devuelve el solista
	 */
	public String getSolista() {
		return this.solista.getText();
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param controlAddConcierto2 contiene el controlador para añadir un concierto
	 * @param cpe contiene el controlador para añadir un precio al concierto
	 */
	public void setControlador(ControlAddConcierto2 controlAddConcierto2, ControlAddPrecioEvento cpe) {
		this.add.addActionListener(controlAddConcierto2);
		this.precio.addActionListener(cpe);
	}
	
	// Constructor de la vista
	public AddConcierto(){ 
		JPanel main = new JPanel();
		JLabel tituloEvento = new JLabel("Titulo: ");
		JLabel descripcionEvento = new JLabel("Descripcion:");
		//JLabel precioEvento = new JLabel("Precio: ");
		JLabel duracionEvento = new JLabel("Duracion: ");
		JLabel autorEvento = new JLabel("Autor: ");
		JLabel directorEvento = new JLabel("Director: ");
		JLabel orquestaEvento = new JLabel("Orquesta: ");
		JLabel solistaEvento = new JLabel("Solista: ");
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(8, 2)); 
		
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
		
		f.add(orquestaEvento);
		f.add(this.orquesta);
		
		f.add(solistaEvento);
		f.add(this.solista);
		
		f.add(this.add);
		f.add(this.precio);
		
		main.add(f, BorderLayout.CENTER);
		
		f.setVisible(true);
		//add.addActionListener(new ControlAddConcierto(ventana, this)); /* al pulsar el boton lleva a este control que deberia añadir el evento a la lista y volver a la anterior vista (esta pocho)*/
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_concierto");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		c.add(new AddConcierto());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
