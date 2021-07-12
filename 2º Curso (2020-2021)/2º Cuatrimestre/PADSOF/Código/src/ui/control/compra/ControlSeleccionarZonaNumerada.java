package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import teatro.Zona;
import teatro.ZonaNumerada;
import ui.view.compra.UICompra;
import ui.view.teatro.UIZonaNumerada;

public class ControlSeleccionarZonaNumerada implements ActionListener{
	private Zona z=null;
	private UICompra vista;
	JFrame ventana;
	public ControlSeleccionarZonaNumerada(Zona z, JFrame v1, UICompra v){
		if(z==null) {
			return;
		}
		this.z = z;
		this.vista = v;
		this.ventana = v1;
	}
		public void actionPerformed(ActionEvent arg0) {
			if(!vista.getControlCompra().getR().comprobarDisponibilidad(z)) {
				JOptionPane.showMessageDialog(ventana, "Lo sentimos, no quedan huecos para la zona seleccionada ya está completa.", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			vista.getControlCompra().setZ(z);
			vista.getControlCompra().setButaca(null);
			JFrame uiZN =new JFrame();
			uiZN.getContentPane().add(new UIZonaNumerada((ZonaNumerada)z, vista, uiZN, ventana));
			uiZN.setVisible(true);
			uiZN.setSize(400, 400);
		}
	
}
