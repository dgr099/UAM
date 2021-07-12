package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.admin.ControlAddAbonoAnual;
import ui.control.admin.ControlCancelAdmin;

/* Vista para añadir un abono anual */
public class AddAbonoAnual extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	JButton add = new JButton("Añadir Abono");
	JTextField precio = new JTextField(10); 
	List<Zona> zonas = Sistema.getInstancia().getTeatro().getZonas();
	Zona[] zonas2 = new Zona[zonas.size()];    
	JComboBox<Zona> cb = new JComboBox<Zona>(zonas.toArray(zonas2));
	JButton cancelar = new JButton("Cancelar");
	private Sistema sis;
	private static Sistema sis2;
	
	/**
	 * Metodo para conseguir el precio escrito en el campo de texto
	 * @return Devuelve el precio obtenido
	 */
	public String getPrecio() {
		return this.precio.getText();
	}
	
	/**
	 * Metodo para conseguir la zona seleccionada en la combo box
	 * @return Devuelve la zona seleccionada
	 */
	public Zona getZona() {
		return (Zona) this.cb.getSelectedItem();
	}
	
	/**
	 * Metodo para actualizar los controladores correspondientes
	 * @param cca contiene el controlador de cancelacion
	 * @param caa contiene el controlador para añadir abonos
	 */
	public void setControlador(ControlCancelAdmin cca, ControlAddAbonoAnual caa) {
		this.cancelar.addActionListener(cca);
		this.add.addActionListener(caa);
	}
	
	/* Constructor de la vista */
	public AddAbonoAnual(){ 
		JPanel main = new JPanel();
		JLabel precioAbono = new JLabel("Precio: ");
		JLabel zonaAbono = new JLabel("Elije una zona: ");
		setSis(Sistema.getInstancia());
		    
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(3, 2)); 
		
		f.add(precioAbono);
		f.add(this.precio);
		
		f.add(zonaAbono);
		
		f.add(cb);
		
		f.add(this.add);
		
		f.add(cancelar);
		main.add(f, BorderLayout.CENTER);
		
		f.setVisible(true);
		//add.addActionListener(new ControlAddAbonoAnual(ventana, this)); /* al pulsar el boton lleva a este control que deberia añadir el evento a la lista y volver a la anterior vista (esta pocho)*/
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	/* Main para generar la vista del panel */
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_abonoanual");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		setSis2(Sistema.getInstancia());
		try {
			for(int i=0; i!=100; i++) {
				Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba_" + i, 3));	
			}
			for(int i=0; i!=500; i++) {
				Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba2_" + i, 3, 3));
			}
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		c.add(new AddAbonoAnual());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}

	/**
	 * Metodo para conseguir la instancia del sistema 
	 * @return Devuelve una instancia de sistema
	 */
	public Sistema getSis() {
		return sis;
	}

	/**
	 * Metodo para actualizar la instancia del sistema
	 * @param sis contiene la instancia del sistema
	 */
	public void setSis(Sistema sis) {
		this.sis = sis;
	}

	/**
	 * Metodo para conseguir una segunda instancia del sistema
	 * @return Devuelve una instancia del sistema
	 */
	public static Sistema getSis2() {
		return sis2;
	}

	/**
	 * Metodo para actualizar la segunda instancia del sistema
	 * @param sis contiene la instancia del sistema
	 */
	public static void setSis2(Sistema sis2) {
		AddAbonoAnual.sis2 = sis2;
	}
}
