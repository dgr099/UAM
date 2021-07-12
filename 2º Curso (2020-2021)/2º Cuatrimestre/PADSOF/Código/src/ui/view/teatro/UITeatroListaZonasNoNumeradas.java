package ui.view.teatro;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Representacion;
import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import ui.control.compra.ControlSeleccionarZonaNoNumerada;
import ui.control.teatro.ControlListaZonaNoNumerada;
import ui.view.compra.UICompra;

/**
 * Clase con el panel de la lista de zonas no numeradas
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class UITeatroListaZonasNoNumeradas extends JScrollPane implements UILista{	
	private static final long serialVersionUID = 650385903029733333L;
	private DefaultListModel<String> zonasNoNumeradasLista = new DefaultListModel<>();
	private JList<String> zonasNoNumeradasJList = new JList<String>(zonasNoNumeradasLista);
	private JLabel titulo = new JLabel("Zonas No Numeradas:");
	private JPanel main = new JPanel();
	
	public void setControlador(ControlListaZonaNoNumerada c) {
		this.zonasNoNumeradasJList.addMouseListener(c);
	}
	/** constructor para utilizar cuando quiere comprar una entrada
	 * @param r representacion de la entrada a comprar
	 * @param ventana frame
	 * @param uic interfaz de compra
	 */
	public UITeatroListaZonasNoNumeradas(Representacion r, JFrame ventana, UICompra uic){ /*constructor cuando se pretenden mostrar las opciones para una representacion*/
		main.add(titulo, BorderLayout.NORTH);
		titulo.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		JPanel main_2 = new JPanel();
		main.add(main_2, BorderLayout.CENTER);
		List<Zona> zonasNoNumeradas = new ArrayList<Zona>(); 
		main.setLayout(new BoxLayout(main, BoxLayout.Y_AXIS));
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getTeatro().getZonas()!=null)
			zonasNoNumeradas = (Sistema.getInstancia().getTeatro().getZonas().stream().filter(z -> z instanceof ZonaNoNumerada).collect(Collectors.toList()));;
		if(zonasNoNumeradas!=null) {
			main_2.setLayout(new GridLayout(zonasNoNumeradas.size(), 1));
			for(Zona z : zonasNoNumeradas) {
				JButton zona = new JButton(z.getNombre()); //crea un nuevo botón para la zona
				if(!r.comprobarDisponibilidad(z)) { //si la zona no está disponible lo pones en color rojo
					zona.setBackground(Color.red);
				}
				main_2.add(zona);
				zona.addActionListener(new ControlSeleccionarZonaNoNumerada(z, uic, ventana));
			}
		}
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	
	public String getSelectedValue() {
		return this.zonasNoNumeradasJList.getSelectedValue();
	}
	
	public UITeatroListaZonasNoNumeradas(){ /*constructor*/
		main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		main.add(zonasNoNumeradasJList, BorderLayout.CENTER);
		this.add(main);
		this.update();
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba1", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba2", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba3", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba4", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba5", 3));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new UITeatroListaZonasNoNumeradas());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	@Override
	public void update() {
		this.zonasNoNumeradasLista.clear();
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getTeatro().getZonas()!=null) {
			Sistema.getInstancia().getTeatro().getZonas().stream().filter(z -> z instanceof ZonaNoNumerada).forEach(z -> zonasNoNumeradasLista.addElement(z.getNombre()));
		}
		this.validate();
		this.repaint();
		this.revalidate();
	}
}