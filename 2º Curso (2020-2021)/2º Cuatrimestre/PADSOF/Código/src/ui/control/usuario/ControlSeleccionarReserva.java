package ui.control.usuario;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.StringTokenizer;

import javax.swing.JOptionPane;

import reserva.Reserva;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;
import ui.view.usuario.PaginaReservas;

/**
 * Clase con el control para seleccionar la reserva
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionarReserva implements MouseListener{
	private Ventana v;
	private UICompra uic;
	private PaginaReservas vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de las que obtiene las vistas sobre las que actua
	 */
	public ControlSeleccionarReserva(Ventana v) {
		this.v = v;
		this.uic = v.getUICompra();
		this.vista = v.getPaginaReservas();
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		Reserva r = null;
		StringTokenizer tokens=new StringTokenizer(vista.getListaReservas().getSelected(), ";");
		String cod = tokens.nextToken(); /*codigo de la reserva*/
		for(Reserva r2 : Sistema.getInstancia().getUsuarioEnUso().getReservas()) {
			if(r2.getCodigo().equals(cod)) {
				r=r2;
				break;
			}
		}
		if(r==null) {
			JOptionPane.showMessageDialog(vista, "Error en la selección de reserva.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		uic.prepararCompraReserva(r);
		v.mostrarPanel("UICompra");
		
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

}
