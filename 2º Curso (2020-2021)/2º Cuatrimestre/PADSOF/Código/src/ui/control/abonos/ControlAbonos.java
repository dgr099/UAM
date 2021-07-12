package ui.control.abonos;

import java.awt.event.MouseEvent;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.event.MouseInputListener;

import abonos.Abono;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal;
import ui.view.compra.UICompra;

/**
 * Clase con el control al seleccionar un abono
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAbonos implements MouseInputListener{
	private Ventana v;
	private VistaPrincipal vista;
	private UICompra uic;
	/**
	 * Constructor de la clase
	 * @param v ventana de la cual recoge las vistas en las que actua el controlador
	 */
	public ControlAbonos(Ventana v) {
		this.v =v;
		this.uic = v.getUICompra();
		this.vista = v.getVistaPrincipal();
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		@SuppressWarnings("unchecked")
		String nombre = ((JList<String>)arg0.getSource()).getSelectedValue();
		Abono abono = null;
		for(Abono a : Sistema.getInstancia().getAbonos()) { /*se busca el abono correspondiente*/
			if(a.getCodigo().equals(nombre)) {
				abono = a;
				break;
			}
		}
		if(abono == null) {
			JOptionPane.showMessageDialog(vista, "Error inesperado en la selección de abono", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		uic.prepararCompraAbono(abono); /*si se encontró exitosamente el abono seleccionado se prepará la pantalla para la compra del mismo*/
		v.mostrarPanel("UICompra"); /*se muestra la pantalla de compra tras ser preparada para la compra del abono seleccionado*/
	}
	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
