package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.admin.ControlAddEventoCiclo;

/* vista para la check box de abonos */
public class CheckBoxAbono extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 5035748829531033580L;
	private int ancho = 100;
	private int largo = 100;
	private ControlAddEventoCiclo control;
	private JPanel main = new JPanel();
	private List<JCheckBox> lista = new ArrayList<JCheckBox>();
	private int i=0;
	public CheckBoxAbono() {
		main.setLayout(new BoxLayout(main, BoxLayout.Y_AXIS));
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
	}
	
	/**
	 * Método para añadir un evento al checkbox
	 * @param e Evento a añadir
	 */
	public void addElement(Evento e) {
		if(e==null)	return;
		for(int i=0; i!=lista.size(); i++) {
			if(lista.get(i).getText().equals(e.getTitulo())) { /*si ya lo contiene no hace nada*/
				return;
			}
		}
		JCheckBox check = new JCheckBox(e.getTitulo()); /*si no lo contiene lo añade*/
		check.setBounds(0 ,i*largo,ancho,largo);
		lista.add(check);
		if(control != null) {
			check.addActionListener(control);
		}
		main.add(check);
		i++;
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para eliminar un evento del check Box
	 * @param e Evento a eliminar
	 */
	public void removeElement(Evento e) {
		if(e==null)	return;
		for(int i=0; i!=lista.size(); i++) {
			if(lista.get(i).getText().equals(e.getTitulo())) { /*si ya lo contiene no hace nada*/
				main.remove(lista.get(i));
				lista.remove(lista.get(i));
				this.validate();
				this.repaint();
				i--;
				return;
			}
		}
	}
	
	/**
	 * Metodo para actualizar los controladores de la vista 
	 * @param cac contiene el controlador para añadir un evento de ciclo
	 */
	public void setControlador(ControlAddEventoCiclo cac) {
		this.control = cac;
		this.update();
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario 
	 */
	public void update() {
		lista.clear();
		List<Evento> eventos = Sistema.getInstancia().getEventos();
		main.removeAll();
		i=0;
		for(Evento e : eventos) {
			JCheckBox check = new JCheckBox(e.getTitulo()); 
			check.setBounds(0 ,i*largo,ancho,largo);
			lista.add(check);
			if(control != null) {
				check.addActionListener(control);
			}
			main.add(check);
			i++;
		}
		main.setVisible(true);
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
			c.add(new CheckBoxAbono());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
