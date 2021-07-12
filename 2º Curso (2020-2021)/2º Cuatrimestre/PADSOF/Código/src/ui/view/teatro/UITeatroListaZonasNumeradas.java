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
import teatro.ZonaNumerada;
import ui.control.compra.ControlSeleccionarZonaNumerada;
import ui.control.teatro.ControlListaZonaNumerada;
import ui.view.compra.UICompra;

/**
 * Clase con el panel de la lista de zonas no numeradas
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class UITeatroListaZonasNumeradas extends JScrollPane implements UILista{	
	private static final long serialVersionUID = 650385903029733333L;
	private DefaultListModel<String> zonasNumeradasLista = new DefaultListModel<>();
	private JList<String> zonasNumeradasJList = new JList<String>(zonasNumeradasLista);
	JPanel main = new JPanel();
	JLabel titulo = new JLabel("Zonas Numeradas:");
	/**
	 * Constructor de la clase para mostrar las zonas del teatro
	 */
	public UITeatroListaZonasNumeradas(){ /*constructor*/
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		main.add(zonasNumeradasJList, BorderLayout.CENTER);
		this.update();
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	public void setControlador(ControlListaZonaNumerada cl) {
		this.zonasNumeradasJList.addMouseListener(cl);
	}
	public String getSelected() {
		return this.zonasNumeradasJList.getSelectedValue();
	}
	/**
	 * constructor para utilizar en compra de entrada
	 * @param r representacion para que mostrar las zonas
	 * @param uic vista de compra
	 * @param frame ventana
	 */
	public UITeatroListaZonasNumeradas(Representacion r, UICompra uic, JFrame ventana){ /*constructor*/
		main.add(titulo, BorderLayout.NORTH);
		titulo.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		JPanel main_2 = new JPanel();
		main.add(main_2, BorderLayout.CENTER);
		List<Zona> zonasNumeradas = new ArrayList<Zona>(); 
		main.setLayout(new BoxLayout(main, BoxLayout.Y_AXIS));
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getTeatro().getZonas()!=null)
			zonasNumeradas = (Sistema.getInstancia().getTeatro().getZonas().stream().filter(z -> z instanceof ZonaNumerada).collect(Collectors.toList()));;
		if(zonasNumeradas!=null) {
			main_2.setLayout(new GridLayout(zonasNumeradas.size(), 1));
			for(Zona z : zonasNumeradas) {
				JButton zona = new JButton(z.getNombre()); //crea un nuevo botón para la zona
				if(!r.comprobarDisponibilidad(z)) { //si la zona no está disponible lo pones en color rojo
					zona.setBackground(Color.red);
				}
				main_2.add(zona);
				zona.addActionListener(new ControlSeleccionarZonaNumerada(z, ventana, uic));
			}
		}
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	
	public void update() {
		zonasNumeradasLista.clear();
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getTeatro().getZonas()!=null) {
			Sistema.getInstancia().getTeatro().getZonas().stream().filter(z -> z instanceof ZonaNumerada).forEach(z -> zonasNumeradasLista.addElement(z.getNombre()));
		}
		this.validate();
		this.repaint();
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		Sistema.getInstancia();
		try {
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba1", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba2", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba3", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba4", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba5", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba6", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba7", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba8", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba9", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba10", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba11", 3, 3));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new UITeatroListaZonasNumeradas());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(100, 100);
		return;
	}
}