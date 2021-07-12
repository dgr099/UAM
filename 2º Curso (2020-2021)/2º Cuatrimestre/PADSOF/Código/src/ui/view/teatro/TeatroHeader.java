package ui.view.teatro;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

import ui.control.teatro.ControlAñadirZona;
import ui.control.teatro.ControlLimitaciones;

/**
 * Clase con el header para el teatro
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class TeatroHeader extends JPanel{	
	/**
	 * 
	 */
	private static final long serialVersionUID = 650385903029733333L;
	private JButton añadirZona = new JButton("Añadir Zona");
	private JTextField limitaciones = new JTextField(3);
	public void setControl(ControlLimitaciones cl) {
		this.limitaciones.addActionListener(cl);
	}
	
	/**
	 * Método para obtener limitaciones
	 * @return string con las limitaciones escritas en el recuadro de limitaciones
	 */
	public String getLimitaciones() {
		return this.limitaciones.getText();
	}
	
	/**
	 * Método para establecer el header de teatro
	 * @param lim control para las limitaciones
	 * @param add control para añadir zonas al teatro
	 */
	public void setControlador(ControlLimitaciones lim, ControlAñadirZona add) {
		this.limitaciones.addActionListener(lim);
		this.añadirZona.addActionListener(add);
	}
	
	public TeatroHeader(){ /*constructor*/
		SpringLayout sl = new SpringLayout();
		this.setLayout(sl);
		JLabel tL = new JLabel("Limitaciones: ");
		this.add(tL);
		this.add(limitaciones);
		this.add(añadirZona);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, limitaciones, -100, SpringLayout.HORIZONTAL_CENTER, this);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, añadirZona, 100, SpringLayout.HORIZONTAL_CENTER, this);
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, limitaciones, 0, SpringLayout.VERTICAL_CENTER, añadirZona);
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, tL, 0, SpringLayout.VERTICAL_CENTER, añadirZona);
		sl.putConstraint(SpringLayout.EAST, tL, 0, SpringLayout.WEST, limitaciones);
		this.setPreferredSize(new Dimension(110, 25));
		this.setVisible(true);
	}
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new TeatroHeader());
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
}
