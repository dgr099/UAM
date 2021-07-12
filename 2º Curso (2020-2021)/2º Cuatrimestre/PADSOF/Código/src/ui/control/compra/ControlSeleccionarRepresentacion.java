package ui.control.compra;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Representacion;
import ui.view.Ventana;
import ui.view.compra.UICompra;

public class ControlSeleccionarRepresentacion implements ActionListener{
	private UICompra uic;
	public ControlSeleccionarRepresentacion(Ventana v) {
		this.uic = v.getUICompra();
	}
	public void actionPerformed(ActionEvent arg0) {
		//al pulsar se crea una nueva pestaña con lo de añadir zona
		if(uic.getControlCompra().getEvento()==null) {
			JOptionPane.showMessageDialog(uic, "Error inesperado", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JFrame ventana = new JFrame("Seleccionar Fecha");
		JScrollPane main1 = new JScrollPane();
		ventana.setContentPane(main1);
		JPanel main2 = new JPanel();
		int num=0;
		for(Representacion r : uic.getControlCompra().getEvento().getRepresentaciones()) {
			if(Calendar.getInstance().getTime().before(r.getFechaYHora().getTime())) { /*no se debería poder comprar entradas para una representación pasada*/
				JButton tbb = new JButton(r.getFechaYHora().getTime().toString());
				tbb.addActionListener(new ControlSeleccionarRepresentacion2(this.uic, r, ventana));
				main2.add(tbb);
				num++;
			}
		}
		if(num<=0) {
			JOptionPane.showMessageDialog(uic, "Lo sentimos, actualmente el evento no tiene ninguna representación que no haya pasado ya", "Sin fechas", JOptionPane.INFORMATION_MESSAGE);
			return;
		}
		main2.setLayout(new GridLayout(num, 1));
		main1.add(main2);;
		main2.setVisible(true);
		main1.setViewportView(main2);
		ventana.setVisible(true);
		//ventana.setSize(400, 400);
		ventana.pack();
	}
}
