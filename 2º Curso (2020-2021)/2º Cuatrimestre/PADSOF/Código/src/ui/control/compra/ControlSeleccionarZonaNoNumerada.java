package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import teatro.Zona;
import ui.view.compra.UICompra;

public class ControlSeleccionarZonaNoNumerada implements ActionListener{
	private Zona z;
	private UICompra uic;
	private JFrame ventana;
	public ControlSeleccionarZonaNoNumerada(Zona z, UICompra uic, JFrame ventana) {
		this.z = z;
		this.uic = uic;
		this.ventana = ventana;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(!uic.getControlCompra().getR().comprobarDisponibilidad(z)) {
			JOptionPane.showMessageDialog(ventana, "Lo sentimos, no quedan huecos para la zona seleccionada ya está completa.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		uic.getControlCompra().setZ(z); //ponemos la zona establecida
		uic.getControlCompra().setButaca(null); //quitamos la butaca si se habia seleccionado antes
		ventana.dispose(); //cerramos la ventana auxiliar
	}
	
}
