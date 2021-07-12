package ui.control.compra;

import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;

import javax.swing.JOptionPane;

import es.uam.eps.padsof.telecard.FailedInternetConnectionException;
import es.uam.eps.padsof.telecard.InvalidCardNumberException;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import reserva.Reserva;
import sistema.Sistema;
import teatro.ZonaNumerada;
import ui.view.Ventana;
import ui.view.compra.UICompra;
import usuario.TarjetaBancaria;

/**
 * Clase que implementa el control para el control de proceder con el pago en la compra de entrada u abono
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlProceder implements ActionListener{
	private UICompra ui;
	private Ventana v;

	/**
	 * Constructor de la clase
	 * @param v ventana de la que recibe las vistas sobre las que actua el controlador
	 */
	public ControlProceder(Ventana v) {
		this.v = v;
		ui = v.getUICompra();
	}
	
	/**
	 * Método para implementar el control de proceder
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(Sistema.getInstancia().getUsuarioEnUso()==null) { //si no se hizo login previamente (en teoría esto no debería ocurrir por el control de next)
			JOptionPane.showMessageDialog(ui, "Para seleccionar una tarjeta primero debe hacer login", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		TarjetaBancaria tb = ui.getControlCompra().getTarjetaSeleccionada();
		if(tb==null) { /*si no tenia ninguna tarjeta guardada antes*/
			try { /*intenta crear una nueva con los datos introducidos en los otros campos*/
				tb = new TarjetaBancaria(ui.getSouth().getnTarjeta(), new SimpleDateFormat("dd/MM/yyyy").parse(ui.getSouth().getFechaCaducidad()), Integer.parseInt(ui.getSouth().getCVV()));
				try {
					Sistema.getInstancia().getUsuarioEnUso().addTarjetas(tb);
				} catch (Exception e) {
					e.printStackTrace();
				} //le añades la tarjeta 
			} catch (NumberFormatException | ParseException e) {
				e.printStackTrace();
			}
		}
		/*si por alguna razón fue incapaz de crear la tarjeta con los datos introducidos*/
		if(tb==null) {
			JOptionPane.showMessageDialog(ui, "Debe seleccionar o introducir una tarjeta, recuerde introducir la fecha con el formato dd/MM/yyyy", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		/*comprobamos si estamos en modo reserva*/
		if(ui.getMReserva()) {
			Reserva r = this.ui.getControlCompra().getReserva();
			if(Sistema.getInstancia().getUsuarioEnUso().confirmarReserva(tb.getNumTarjeta(), r)==false) {
				JOptionPane.showMessageDialog(ui, "Lo sentimos, ha ocurrido un error durante la operación", "User Error", JOptionPane.ERROR_MESSAGE);
			}
			v.getPaginaReservas().getListaReservas().removeElement(r); /*quitamos la reserva de la lista de reservas*/
			JOptionPane.showMessageDialog(ui, "Operación realizada con éxito", "Transacción finalizada", JOptionPane.PLAIN_MESSAGE);
			String last = v.getLast();
			if(last!=null) { //si hay pantalla anterior
				v.mostrarPanel(last); //muestra la pantalla anterior
			}
			return;
		}
		/*primera parte es para obtener la tarjeta a usar*/
		if(ui.getControlCompra().getButaca()!=null) { //si ha seleccionado una butaca
			if(Sistema.getInstancia().comprarEntrada(ui.getControlCompra().getR(), ((ZonaNumerada)(ui.getControlCompra().getZ())), ui.getControlCompra().getTarjetaSeleccionada(), ui.getControlCompra().getButaca())==false) {
				JOptionPane.showMessageDialog(ui, "No se ha podido completar la operación para comprar la entrada de butaca", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
		}
		else if (ui.getControlCompra().getZ()!=null){ //si quiere comprar una entrada en una zona
				if(Sistema.getInstancia().comprarEntrada(ui.getControlCompra().getR(), ui.getControlCompra().getZ(), tb)==false) {
					JOptionPane.showMessageDialog(ui, "No se ha podido completar la operación para la compra de entrada", "User Error", JOptionPane.ERROR_MESSAGE);
					return;
				}		
			}
		if(ui.getControlCompra().getAbonoComprar()!=null) {
				try {
					if(Sistema.getInstancia().getUsuarioEnUso().comprarAbono(ui.getControlCompra().getAbonoComprar(), tb)==false) {
						JOptionPane.showMessageDialog(ui, "No se ha podido completar la operación para la compra de entrada", "User Error", JOptionPane.ERROR_MESSAGE);
						return;
					}
				} catch (HeadlessException e) {
					JOptionPane.showMessageDialog(ui, "Error Headless Exception", "User Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				} catch (InvalidCardNumberException e) {
					JOptionPane.showMessageDialog(ui, "Número de tarjeta inválido", "User Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				} catch (FailedInternetConnectionException e) {
					JOptionPane.showMessageDialog(ui, "Error, no se ha podido conectar a iternet", "User Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				} catch (OrderRejectedException e) {
					JOptionPane.showMessageDialog(ui, "Operación rechazada", "User Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				} catch (Exception e) {
					JOptionPane.showMessageDialog(ui, "Se ha producido una Excepción", "User Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				}
			}
		/*añadimos el abono o la entrada a la vista de la página de usuario*/
		if(ui.getControlCompra().getAbonoComprar()!=null) {
			v.getPaginaUsuario().addElement(Sistema.getInstancia().getUsuarioEnUso().getAbonos().get(Sistema.getInstancia().getUsuarioEnUso().getAbonos().size() - 1));
		}
		else {
			v.getPaginaUsuario().addElement(Sistema.getInstancia().getUsuarioEnUso().getEntradas().get(Sistema.getInstancia().getUsuarioEnUso().getEntradas().size() - 1));
		}
		JOptionPane.showMessageDialog(ui, "Operación realizada con éxito", "Transacción finalizada", JOptionPane.PLAIN_MESSAGE);
		ui.getControlCompra().reset(); //reinicias los datos para la siguiente compra
		v.mostrarPanel("VistaPrincipal"); //si termina con éxito vuelves al panel principal
		
	}

}
