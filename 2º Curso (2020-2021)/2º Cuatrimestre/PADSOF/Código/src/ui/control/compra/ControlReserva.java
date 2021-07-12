package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JOptionPane;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase para implementar el control de reserva
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlReserva implements ActionListener{
	private UICompra vista;
	private Ventana v;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas a modificar
	 */
	public ControlReserva(Ventana v) {
		vista = v.getUICompra();
		this.v = v;
	}
	/**
	 * Método para cuando se presiones el botón de reserva
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(vista.getControlCompra().getButaca()==null) { /*primero comprueba si se selecciono una butaca*/
			JOptionPane.showMessageDialog(vista, "No puede reservar en una zona no numerada, solo puede reservar butacas", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		try {
			if(Sistema.getInstancia().getUsuarioEnUso().reservarButaca(vista.getControlCompra().getR(), vista.getControlCompra().getButaca())==false) { /*intenta reservar dicha butaca*/
				Calendar fecha_limit = vista.getControlCompra().getR().getFechaYHora();
				fecha_limit.add(Calendar.DAY_OF_MONTH, vista.getControlCompra().getR().getPd().getLim());
				/*si ocurre algún problema con la reserva, le notifica la situacion del usuario con respecto a la política de reserva de la representacion*/
				JOptionPane.showMessageDialog(vista, "Error, lo lamentamos pero no se pudo reservar la butaca\nVerifique si cumple la política de reservas:\n" + "Reservas del usuario para la representación: " + Sistema.getInstancia().getUsuarioEnUso().getNReservas().get(vista.getControlCompra().getR()) + "/" + vista.getControlCompra().getR().getPd().getMax() + "\nFecha límite para reservar: " + fecha_limit.getTime(), "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(vista, "Error, lo lamentamos pero no se pudo reservar la butaca", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			e.printStackTrace();
			return;
		}
		//vista.getControlCompra().getR().addLista(Sistema.getInstancia().getUsuarioEnUso());
		JOptionPane.showMessageDialog(vista, "Se ha reservado la butaca " + vista.getControlCompra().getButaca().getFila() + " : " + vista.getControlCompra().getButaca().getColumna() + " del evento " + vista.getControlCompra().getEvento().getTitulo() + " para el dia " + vista.getControlCompra().getR().getFechaYHora().getTime() + " con éxito.", "INFO", JOptionPane.INFORMATION_MESSAGE);
		v.mostrarPanel("VistaPrincipal");
		//añades la ultima reserva de la lista de reservas del usuario a la pagina de reservas
		v.getPaginaReservas().getListaReservas().addElement(Sistema.getInstancia().getUsuarioEnUso().getReservas().get(Sistema.getInstancia().getUsuarioEnUso().getReservas().size()-1));
		return;
	}

}
