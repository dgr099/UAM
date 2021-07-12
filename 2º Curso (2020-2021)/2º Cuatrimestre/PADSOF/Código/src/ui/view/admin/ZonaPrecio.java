package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.admin.JTextAux;

// Vista para cambiar el precio de una zona
public class ZonaPrecio extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 8217949711147335344L;
	private JPanel main = new JPanel();
	private Map<JTextAux, Zona> zonas = new TreeMap<JTextAux, Zona>(); /*A cada zona le asigno un precio*/

	private List<JTextAux> precios = new ArrayList<JTextAux>();
	
	/**
	 * Metodo para obtener una lista de precios
	 * @return devuelve una lista
	 */
	public List<JTextAux> getPrecios(){
		return this.precios;
	}
	
	/**
	 * Metodo para obtener la zona 
	 * @param a texto introducido
	 * @return devuelve la zona asociada
	 */
	public Zona getZona(JTextAux a) {
		return zonas.get(a);
	}
	
	// Constructor de la vista
	public ZonaPrecio() {
		zonas.clear();
		main.setLayout(new GridLayout(Sistema.getInstancia().getTeatro().getZonas().size(), 2));
		for(Zona z : Sistema.getInstancia().getTeatro().getZonas()) {
			main.add(new JLabel(z.getNombre()));
			JTextField zona = new JTextField();
			JTextAux aux = new JTextAux(zona);
			zonas.put(aux, z);
			main.add(zona);
			precios.add(aux);
		}
		this.add(main);
		this.setViewportView(main);
		main.setVisible(true);
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario
	 */
	public void update() {
		precios.clear();
		zonas.clear();
		main.removeAll();
		main.setLayout(new GridLayout(Sistema.getInstancia().getTeatro().getZonas().size(), 2));
		for(Zona z : Sistema.getInstancia().getTeatro().getZonas()) {
			main.add(new JLabel(z.getNombre()));
			JTextField zona = new JTextField();
			JTextAux aux = new JTextAux(zona);
			zonas.put(aux, z);
			main.add(zona);
			precios.add(aux);
		}
	}
	
	// Main para probar la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_InfoAbono");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			for(int i=0; i!=100; i++) {
				Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("prueba ZNN " + i, i+10));
			}
			for(int i=0; i!=50; i++) {
				Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("prueba ZN " + i, i+10, i+20));
			}
			
		} catch (Exception e) {
			System.out.println(e);
		}
		c.add(new ZonaPrecio());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
