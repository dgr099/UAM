package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import sistema.Sistema;
import teatro.ZonaNumerada;
import ui.view.Ventana;
import ui.view.compra.UICompra;

/**
 * Clase para implementar el control del boton de siguiente en la pagina de compra
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlNext implements ActionListener{
	private UICompra vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene la vista del controlador
	 */
	public ControlNext(Ventana v) {
		this.vista = v.getUICompra();
	}
	/**
	 * Método con las instrucciones para poder continuar con la compra (mostrar la parte de selección e introducción de tarjeta)
	 */
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(Sistema.getInstancia().getUsuarioEnUso()==null) {
			JOptionPane.showMessageDialog(vista, "No puede comprar una entrada sin hacer previamente login", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(vista.getControlCompra().getR()==null) { //si no ha seleccionado representación
			JOptionPane.showMessageDialog(vista, "Falta por seleccionar la fecha", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(vista.getControlCompra().getZ()==null) { //si no ha seleccionado zona
			JOptionPane.showMessageDialog(vista, "Falta por seleccionar la zona", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(vista.getControlCompra().getZ() instanceof ZonaNumerada) { //si no ha seleccionado zona
			if(vista.getControlCompra().getButaca()==null) {
				JOptionPane.showMessageDialog(vista, "Falta por seleccionar la butaca de la zona numerada", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			vista.getSouth().ponerReserva();
		}
		else {
			vista.getSouth().quitarReserva();
		}
		vista.getSouth().mostrarPanel("tarjeta"); //pasamos a la siguiente parte (introducir los datos de la tarjeta)
		vista.mostrarAtras();
	}
	
}
