package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.admin.ControlAddPrecioEvento.ControlAddPrecioEvento2;
import ui.control.admin.JTextAux;

public class AddPrecioEvento extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 6167820548158012759L;
	private JButton confirmar = new JButton("Confirmar");
	private ZonaPrecio zonaPrecio = new ZonaPrecio();
	public void update() {
		this.zonaPrecio.update();
	}
	public Zona getZona(JTextAux a) {
		return this.zonaPrecio.getZona(a);
	}
	public void setControlador(ControlAddPrecioEvento2 cad) {
		this.confirmar.addActionListener(cad);
	}
	public List<JTextAux> getPrecios(){
		return this.zonaPrecio.getPrecios();
	}
	public AddPrecioEvento(){
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(zonaPrecio, BorderLayout.CENTER);
		main.add(confirmar, BorderLayout.SOUTH);
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		main.setPreferredSize(new Dimension(200, 200));
	}
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
		c.add(new AddPrecioEvento());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
