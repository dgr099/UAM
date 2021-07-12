package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import abonos.AbonoUsuario;
import entrada.Entrada;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase que implementa el control para la seleccion de abono dentro de la lista de abonos compatibles
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionarAbono2 implements ActionListener{
	private UICompra uic;
	private AbonoUsuario u;
	private JFrame ventana;
	private Ventana v;
	/**
	 * Constructor de la clase
	 * @param uic
	 * @param u
	 * @param ventana
	 * @param v
	 */
	public ControlSeleccionarAbono2(UICompra uic, AbonoUsuario u, JFrame ventana, Ventana v) {
		this.ventana = ventana;
		this.u = u;
		this.uic = uic;
		this.v=v;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		uic.getControlCompra().setAbonoUsar(u.getAbono()); //estableces que este es el abono a usar
		Entrada e = null;
		if(uic.getMReserva()) { /*si está en modo reserva*/
			if(Sistema.getInstancia().getUsuarioEnUso().confirmarReserva(u, uic.getControlCompra().getReserva())==false) {
				JOptionPane.showMessageDialog(ventana, "No se ha podido confirmar la reserva con el abono seleccionado", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			JOptionPane.showMessageDialog(ventana, "Reserva confirmada satisfactoriamente", "Reserva Confirmada", JOptionPane.INFORMATION_MESSAGE);
			ventana.dispose();
			v.mostrarPanel("VistaPrincipal");
			return;
		}
		try {
			e = u.getAbono().getZona().factoryEntrada(uic.getControlCompra());
		} catch (Exception e1) {
			JOptionPane.showMessageDialog(ventana, "Lo sentimos, el abono o las condiciones en que fue usado no son válidas: " + e1.getMessage(), "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		} //pruebas a generar una entrada
		if(e==null) {
			JOptionPane.showMessageDialog(ventana, "Si el abono está asociado a una zona numerada debe seleccionar la butaca para continuar.\n " + u.getAbono().getZona(), "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(Sistema.getInstancia().usarAbono(e, u)==false) {
			JOptionPane.showMessageDialog(ventana, "Lo sentimos, ha ocurrido un error con el abono", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		/*si todo sale correctamente se añade la entrada al usuario*/
		Sistema.getInstancia().getUsuarioEnUso().addEntradas(e);
		uic.prepararCompraEntrada(uic.getControlCompra().getEvento()); //reinicio valores
		JOptionPane.showMessageDialog(ventana, "Se ha añadido la entrada a su lista de entradas", "OK", JOptionPane.INFORMATION_MESSAGE);
		ventana.dispose();
		//v.mostrarPanel("VistaPrincipal"); //volvemos a la vista principal
	}
		

}
