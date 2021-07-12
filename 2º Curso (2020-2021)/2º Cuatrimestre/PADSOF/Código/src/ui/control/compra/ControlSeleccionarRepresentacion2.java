package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;

import evento.Representacion;
import ui.view.compra.UICompra;

public class ControlSeleccionarRepresentacion2 implements ActionListener{
	private UICompra uic;
	private Representacion r;
	private JFrame ventana;
	public ControlSeleccionarRepresentacion2(UICompra uic, Representacion r, JFrame ventana) {
		super();
		this.uic = uic;
		this.r = r;
		this.ventana = ventana;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		try { //intenta seleccionar en la compra la tarjeta establecida
			uic.getControlCompra().setR(r);
			uic.getControlCompra().setZ(null); /*reestablecemos el resto de valores*/
			uic.getControlCompra().setButaca(null);
			ventana.dispose(); //cierras la ventana
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}

}
