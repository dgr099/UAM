package ui.control.compra;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;
import usuario.TarjetaBancaria;

public class ControlSeleccionarTarjeta implements ActionListener{

	private UICompra uic;
	private ControlSeleccionarTarjeta2 controlSeleccionarTarjeta2 = null;
	
	public ControlSeleccionarTarjeta(Ventana v) {
		super();
		this.uic = v.getUICompra();
	}
	
	public void actionPerformed(ActionEvent arg0) {
		//al pulsar se crea una nueva pestaña con lo de añadir zona
		if(Sistema.getInstancia().getUsuarioEnUso()==null) {
			JOptionPane.showMessageDialog(uic, "Para seleccionar tarjeta primero debe hacer login", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JFrame ventana = new JFrame("Seleccionar Tarjeta");
		JScrollPane main1 = new JScrollPane();
		ventana.setContentPane(main1);
		JPanel main2 = new JPanel();
		main2.setLayout(new GridLayout(Sistema.getInstancia().getUsuarioEnUso().getTarjetas().size(), 1));
		for(TarjetaBancaria tb : Sistema.getInstancia().getUsuarioEnUso().getTarjetas()) {
			JButton tbancaria = new JButton(tb.getNumTarjeta());
			tbancaria.addActionListener(new ControlSeleccionarTarjeta2(uic, ventana));
			main2.add(tbancaria);
		}
		main1.add(main2);;
		main2.setVisible(true);
		main1.setViewportView(main2);
		ventana.setVisible(true);
		//ventana.setSize(400, 400);
		ventana.pack();
	}

	public ControlSeleccionarTarjeta2 getControlSeleccionarTarjeta2() {
		return controlSeleccionarTarjeta2;
	}

	public void setControlSeleccionarTarjeta2(ControlSeleccionarTarjeta2 controlSeleccionarTarjeta2) {
		this.controlSeleccionarTarjeta2 = controlSeleccionarTarjeta2;
	}

}
