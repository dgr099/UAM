package ui.control.compra;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import teatro.Butaca;
import teatro.ZonaNumerada;
import ui.view.compra.UICompra;

public class ControlSeleccionarButaca implements ActionListener{
	UICompra vista;
	JFrame v;
	JFrame v2;
	public ControlSeleccionarButaca(UICompra uic, JFrame v, JFrame v2) {
		this.vista=uic;
		this.v = v;
		this.v2 = v2;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String pos[] = ((JButton)arg0.getSource()).getText().split(":"); //obtiene el nombre del botón fila:columna
		int fila = Integer.parseInt(pos[0]); 
		int columna = Integer.parseInt(pos[1]); 
		Butaca b = ((ZonaNumerada)vista.getControlCompra().getZ()).getButacas()[fila][columna];
		if(b==null) {
			JOptionPane.showMessageDialog(v, "Lo sentimos, la butaca seleccionada no se encuentra actualmente", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(!b.isActiva()) {
			JOptionPane.showMessageDialog(v, "Lo sentimos, la butaca no está activa, ha sido reservada, ocupada o se encuentra en reparación", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(vista.getControlCompra().getR().getButacasOcupadas().contains(b)) {
			JOptionPane.showMessageDialog(v, "Lo sentimos, la butaca ya está ocupada o reservada", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		vista.getControlCompra().setButaca(b);
		v.dispose();
		v2.dispose();
	}

}
