package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

import sistema.Sistema;
import ui.view.compra.UICompra;

public class ControlSeleccionarTarjeta2 implements ActionListener{
	private UICompra uic;
	private JFrame ventana;
	
	public ControlSeleccionarTarjeta2(UICompra uic, JFrame ventana) {
		super();
		this.uic = uic;
		this.ventana = ventana;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String numT = ((JButton)arg0.getSource()).getText();
		try { //intenta seleccionar en la compra la tarjeta establecida
			uic.getControlCompra().setTarjetaSeleccionada(Sistema.getInstancia().getUsuarioEnUso().seleccionarTarjeta(numT));
			ventana.dispose();
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}

}
