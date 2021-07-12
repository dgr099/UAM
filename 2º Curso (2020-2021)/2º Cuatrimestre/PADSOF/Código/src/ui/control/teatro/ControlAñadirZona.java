package ui.control.teatro;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;

import ui.view.Ventana;
import ui.view.teatro.AñadirZona;
import ui.view.teatro.ConfTeatro;

public class ControlAñadirZona implements ActionListener{
	ConfTeatro conf = null;
	
	
	public ControlAñadirZona(Ventana vista) {
		super();
		this.conf = vista.getConfTeatro();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		//al pulsar se crea una nueva pestaña con lo de añadir zona
		JFrame ventana = new JFrame("Añadir Zona");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		AñadirZona panel = new AñadirZona();
		panel.setControlador(new ControlAñadirZona2(panel, ventana, conf));
		c.add(panel);
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
	}

}
