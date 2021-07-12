package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import teatro.Zona;
import ui.view.admin.AddPrecioEvento;

/**
 * Clase con el control para poder asinar el precio de las zonas del teatro para un evento
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddPrecioEvento implements ActionListener{
	private JFrame ventana;
	private AddPrecioEvento vista;
	private Map<Zona, Double> precioZonas = new TreeMap<Zona, Double>(); /*A cada zona le asigno un precio*/
	private ControlAddPrecioEvento2 cev = new ControlAddPrecioEvento2();
	public Map<Zona, Double> getPrecio(){
		return precioZonas;
	}
	/**
	 * Clase interna para poder aceptar los cambios
	 * @author David Teófilo Garitagoitia Romero
	 *
	 */
	public class ControlAddPrecioEvento2 implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			precioZonas.clear();
			for(JTextAux tf : vista.getPrecios()) {
				Zona x = vista.getZona(tf);
				if(x==null) {
					JOptionPane.showMessageDialog(vista, "Error, no se encontró en sistema la zona", "Sistem Error", JOptionPane.ERROR_MESSAGE);
					return;
				}
				if(!tf.getTextField().getText().equals("")) {
					try{
						Double precio = Double.parseDouble(tf.getTextField().getText());
						precioZonas.put(x,  precio);
					} catch (Exception e) {
						e.printStackTrace();
						JOptionPane.showMessageDialog(vista, "Error, recuerde que los precios deben ser números\n" + tf.getTextField().getText() + " no es un número", "Sistem Error", JOptionPane.ERROR_MESSAGE);
						return;
						
					}
				}
				
			}
			JOptionPane.showMessageDialog(vista, "Se estableció correctamente el precio", "Precio Establecido", JOptionPane.INFORMATION_MESSAGE);
			ventana.dispose();
			
		}
		
	}
	@Override
	public void actionPerformed(ActionEvent arg0) { /*el de dar al botón de crear que abre una ventana para introducir los datos*/
		JFrame precio = new JFrame();
		this.ventana = precio;
		this.vista = new AddPrecioEvento();
		this.vista.setControlador(this.cev);
		precio.getContentPane().add(this.vista);
		precio.setVisible(true);
		precio.setSize(400, 400);
	
	}

}
