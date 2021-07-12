package ui.view.teatro;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.util.List;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.ControlBack;
import ui.control.teatro.ControlAñadirZona;
import ui.control.teatro.ControlLimitaciones;
import ui.control.teatro.ControlListaZonaNoNumerada;
import ui.control.teatro.ControlListaZonaNumerada;

/**
 * Clase con la vista para la conf de teatro
 * @author David Teófilo Garitagoitia Romero
 */
public class ConfTeatro extends JScrollPane{
	private static final long serialVersionUID = -288671273664752206L;
	private List<Zona> ZonasNumeradas = null; //lista de zonas numeradas
	private List<Zona> ZonasNoNumeradas = null; //lista de zonas no numeradas
	private TeatroHeader Header = new TeatroHeader(); //header del teatro
	private UITeatroListaZonasNoNumeradas listaZNN = new UITeatroListaZonasNoNumeradas();
	private UITeatroListaZonasNumeradas listaZN = new UITeatroListaZonasNumeradas();
	private JButton back = new JButton("Back");
	
	/**
	 * Método para obtener el header
	 * @return header de configuracion de teatro
	 */
	public TeatroHeader getHeader() {
		return this.Header;
	}
	
	/**
	 * Método para establecer el controlador
	 * @param cl control para las limitaciones
	 * @param ca control para añadir zona
	 * @param cb control para ir al panel anterior
	 */
	public void setControlador(ControlLimitaciones cl, ControlAñadirZona ca, ControlBack cb, ControlListaZonaNoNumerada cznn, ControlListaZonaNumerada czn) {
		this.Header.setControlador(cl, ca);
		this.back.addActionListener(cb);
		this.listaZNN.setControlador(cznn);
		this.listaZN.setControlador(czn);
	}
	/**
	 * Método para obtener la lista gráfica de zona numeradas
	 * @return
	 */
	public UITeatroListaZonasNumeradas getListaZonaNumerada() {
		return this.listaZN;
	}
	/**
	 * Método para obtener la lista gráfica de zona no numeradas
	 * @return
	 */
	public UITeatroListaZonasNoNumeradas getListaZonaNoNumerada() {
		return this.listaZNN;
	}
	public ConfTeatro() throws Exception{ /*constructor*/
		JPanel main = new JPanel();
		/*configuramos el back*/
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		BorderLayout bL = new BorderLayout();
		main.setLayout(bL);
		main.add(this.Header, BorderLayout.NORTH); //añades el header
		JPanel center = new JPanel();
		center.setLayout(new GridLayout(1, 2));
		center.add(listaZNN);
		center.add(listaZN);
		main.add(center, BorderLayout.CENTER); //ponemos la lista de zonas
		main.add(back, BorderLayout.SOUTH);
		main.setVisible(true);
		this.add(main);
		this.setViewportView(main);
		main.setPreferredSize(new Dimension(200, 240));
	}
	
	//main para ver la vista
	public static void main(String... args) throws Exception {
		JFrame ventana = new JFrame("Pruebas_conf_Teatro");
		try {
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba1", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba2", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba3", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba4", 3, 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada("Prueba5", 3, 3));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba6", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba7", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba8", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba9", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba10", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba11", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba17", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba18", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba19", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba20", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba21", 3));
			Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada("Prueba22", 3));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		Container c = ventana.getContentPane();
		c.add(new ConfTeatro());
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}

	public List<Zona> getZonasNoNumeradas() {
		return ZonasNoNumeradas;
	}

	public void setZonasNoNumeradas(List<Zona> zonasNoNumeradas) {
		ZonasNoNumeradas = zonasNoNumeradas;
	}

	public List<Zona> getZonasNumeradas() {
		return ZonasNumeradas;
	}

	public void setZonasNumeradas(List<Zona> zonasNumeradas) {
		ZonasNumeradas = zonasNumeradas;
	}
}
