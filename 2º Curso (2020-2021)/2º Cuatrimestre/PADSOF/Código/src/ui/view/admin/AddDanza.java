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

import ui.control.admin.ControlAddDanza.ControlAddDanza2;
import ui.control.admin.ControlAddPrecioEvento;

public class AddDanza extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	JButton add = new JButton("Añadir Evento");
	JTextField titulo = new JTextField(10); 
	JTextField descripcion = new JTextField(100); 
	//JTextField precio = new JTextField(10); 
	JTextField duracion = new JTextField(10);
	JTextField autor = new JTextField(10);
	JTextField director = new JTextField(10);
	private JButton precio = new JButton("Precio Zonas");
	
	public void setControlador(ControlAddDanza2 cad, ControlAddPrecioEvento cpe) {
		this.add.addActionListener(cad);
		this.precio.addActionListener(cpe);
	}
	public String getTitulo() {
		return this.titulo.getText();
	}
	
	public String getDescripcion() {
		return this.descripcion.getText();
	}
	
	public String getDuracion() {
		return this.duracion.getText();
	}
	
	public String getAutor() {
		return this.autor.getText();
	}
	
	public String getDirector() {
		return this.director.getText();
	}
	
	public AddDanza(){ 
		JPanel main = new JPanel();
		JLabel tituloEvento = new JLabel("Titulo: ");
		JLabel descripcionEvento = new JLabel("Descripcion:");
		//JLabel precioEvento = new JLabel("Precio: ");
		JLabel duracionEvento = new JLabel("Duracion: ");
		JLabel autorEvento = new JLabel("Autor: ");
		JLabel directorEvento = new JLabel("Director: ");
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(6, 2)); 
		
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
		
		f.add(this.add);
		f.add(this.precio);
		
		main.add(f, BorderLayout.CENTER);
		
		f.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_danza");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		c.add(new AddDanza());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
