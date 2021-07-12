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

import evento.Concierto;
import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import ui.control.admin.ControlAbonoCiclo;
import ui.control.admin.ControlAddAbonoCiclo;
import ui.control.admin.ControlAddEventoCiclo;
import ui.control.admin.ControlCancelAdmin;

// Vista para añadir un abono de ciclo
public class AddAbonoCiclo extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	JButton add = new JButton("Añadir Abono");
	JTextField descuento = new JTextField(10); 
	List<Zona> zonas = Sistema.getInstancia().getTeatro().getZonas();
	Zona[] zonas2 = new Zona[zonas.size()];    
	JComboBox<Zona> cb = new JComboBox<Zona>(zonas.toArray(zonas2));
	CheckBoxAbono cba = new CheckBoxAbono();
	JButton cancelar = new JButton("cancelar");
	private ControlAbonoCiclo controlAbonoCiclo;
	private ControlAddEventoCiclo controlAddEventoCiclo;
	
	/**
	 * Metodo para obtener el descuento introducido
	 * @return devuelve el descuento
	 */
	public String getDescuento() {
		return this.descuento.getText();
	}
	
	/**
	 * Metodo para obtener la zona introducida
	 * @return devuelve la zona
	 */
	public Zona getZona() {
		return (Zona) this.cb.getSelectedItem();
	}
	
	/**
	 * Metodo para obtener el controlador del abono de ciclo
	 * @return devuelve el controlador
	 */
	public ControlAbonoCiclo getControlAbonoCiclo() {
		return this.controlAbonoCiclo;
	}
	
	/**
	 * Metodo para obtener el check box del abono
	 * @return devuelve el check box
	 */
	public CheckBoxAbono getCheckBoxAbono() {
		return this.cba;
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param cca contiene el controlador para cancelar el abono
	 * @param cac contiene el controlador para añadir un abono de ciclo
	 * @param cabciclo contiene el controlador de la vista de abonos de ciclo
	 * @param cadd contiene el controlador para añadir un evento a un ciclo
	 */
	public void setControlador(ControlCancelAdmin cca, ControlAddAbonoCiclo cac, ControlAbonoCiclo cabciclo, ControlAddEventoCiclo cadd) {
		this.cancelar.addActionListener(cca);
		this.add.addActionListener(cac);
		this.controlAbonoCiclo = cabciclo;
		this.setControlAddEventoCiclo(cadd);
		cba.setControlador(cadd);
	}
	
	// Constructor de la vista
	public AddAbonoCiclo(){ 
		JPanel main = new JPanel();
		JLabel descuentoAbono = new JLabel("Descuento: ");
		JLabel elijeEventos = new JLabel("Elija los eventos: ");
		JLabel zonaAbono = new JLabel("Elije una zona: ");
		main.setLayout(new BorderLayout());
		JPanel f = new JPanel();
		f.setLayout(new GridLayout(4, 2)); 
		
		f.add(descuentoAbono);
		f.add(this.descuento);
		
		f.add(elijeEventos);
		f.add(cba);
		
		f.add(zonaAbono);
		f.add(cb); /* Aqui iria el combobox de las zonas */
		
		f.add(this.add);
		f.add(cancelar);
		main.add(f, BorderLayout.CENTER);
		
		f.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(220, 150));
		this.setViewportView(main);
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_abonociclo");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		try {
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba1", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba2", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba3", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba4", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba5", 3));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto1", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto2", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto3", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto4", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto5", "DGR", "CerraOrquesta", "German", "Willyrex"));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new AddAbonoCiclo());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}

	/**
	 * Metodo para obtener el controlador para añadir un evento a un ciclo
	 * @return devuelve el controlador
	 */
	public ControlAddEventoCiclo getControlAddEventoCiclo() {
		return controlAddEventoCiclo;
	}

	/**
	 * Metodo para actualizar el controlador para añadir un evento a un ciclo
	 * @param controlAddEventoCiclo contiene el controlador
	 */
	public void setControlAddEventoCiclo(ControlAddEventoCiclo controlAddEventoCiclo) {
		this.controlAddEventoCiclo = controlAddEventoCiclo;
	}
}

