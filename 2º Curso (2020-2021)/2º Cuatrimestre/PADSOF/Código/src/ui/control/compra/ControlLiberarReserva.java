package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JOptionPane;

import reserva.Reserva;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Control para liberar una reserva
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlLiberarReserva implements ActionListener{
	private UICompra ui;
	private Ventana v;

	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene la vista
	 */
	public ControlLiberarReserva(Ventana v) {
		this.v = v;
		ui = v.getUICompra();
	}
	
	/**
	 * Método para cuando se presiona en liberar reserva
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(Sistema.getInstancia().getUsuarioEnUso()==null || !ui.getMReserva()) {
			JOptionPane.showMessageDialog(ui, "Unexpected Error", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		Reserva r = this.ui.getControlCompra().getReserva();
		if(Sistema.getInstancia().getUsuarioEnUso().cancelarReserva(r)==false) {
			JOptionPane.showMessageDialog(ui, "Lo sentimos, ha ocurrido un error durante la cancelación", "User Error", JOptionPane.ERROR_MESSAGE);
		}
		Sistema.getInstancia().getUsuarioEnUso().addNotificacion("Has Liberado la reserva de la butaca: " + r.getButaca().toString() + "\nDe la representación: " + r.getRepresentacion().getFechaYHora().getTime() + "\nDel evento " + r.getRepresentacion().getEvento().getTitulo());
		v.getPaginaUsuario().addElement(Sistema.getInstancia().getUsuarioEnUso().getNotificacionesList().get(Sistema.getInstancia().getUsuarioEnUso().getNotificaciones().size() - 1));
		if(r.getRepresentacion().getLista().contains(Sistema.getInstancia().getUsuarioEnUso())) {
			v.getPaginaUsuario().addElement(Sistema.getInstancia().getUsuarioEnUso().getNotificacionesList().get(Sistema.getInstancia().getUsuarioEnUso().getNotificaciones().size() - 2));
		}
		v.getPaginaReservas().getListaReservas().removeElement(r);
		ui.getControlCompra().reset(); //reinicias los datos para la siguiente compra
		JOptionPane.showMessageDialog(ui, "La reserva fue cancelada satisfactoriamente", "Reserva Cancelada", JOptionPane.PLAIN_MESSAGE);
		v.mostrarPanel("VistaPrincipal"); //si termina con éxito vuelves al panel principal
	}
}
