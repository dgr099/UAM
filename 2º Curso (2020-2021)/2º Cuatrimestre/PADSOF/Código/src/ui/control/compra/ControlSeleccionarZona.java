package ui.control.compra;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import ui.view.Ventana;
import ui.view.compra.UICompra;
import ui.view.teatro.UITeatroListaZonasNoNumeradas;
import ui.view.teatro.UITeatroListaZonasNumeradas;

public class ControlSeleccionarZona implements ActionListener{
	private UICompra uic;
	public ControlSeleccionarZona(Ventana c) {
		this.uic = c.getUICompra();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(uic.getControlCompra().getR()==null) { //si no ha seleccionado la fecha
			JOptionPane.showMessageDialog(uic, "Para seleccionar la zona primero debe seleccionar la fecha.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JFrame uiZN =new JFrame();
		JPanel content = new JPanel();
		content.setLayout(new GridLayout(1, 2));
		uiZN.setContentPane(content);
		/*crea un panel con vistas para zonas no numeradas y numeradas*/
		content.add(new UITeatroListaZonasNoNumeradas(uic.getControlCompra().getR(), uiZN, this.uic));
		content.add(new UITeatroListaZonasNumeradas(uic.getControlCompra().getR(), uic, uiZN));
		uiZN.setVisible(true);
		uiZN.pack();
	}

}
