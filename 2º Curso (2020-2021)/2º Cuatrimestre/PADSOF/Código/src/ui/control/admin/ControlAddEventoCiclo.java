package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JCheckBox;
import javax.swing.JOptionPane;

import evento.Evento;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.AddAbonoCiclo;

/**
 * Clase con el control para añadir un evento al ciclo de un abono
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddEventoCiclo implements ActionListener{
	AddAbonoCiclo vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de la aplicación
	 */
	public ControlAddEventoCiclo(Ventana v) {
		this.vista = v.getAddAbonoCiclo();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		JCheckBox check = ((JCheckBox)(arg0.getSource()));
		String nombre = check.getText();
		Evento e = null;
		for(Evento ev : Sistema.getInstancia().getEventos()) {
			if(ev.getTitulo().equals(nombre)) {
				e = ev;
				break;
			}
		}
		if(e==null) {
			JOptionPane.showMessageDialog(vista, "No se ha podido encontrar el evento", "User Error", JOptionPane.ERROR_MESSAGE);
		}
		if(check.isSelected()){
			vista.getControlAbonoCiclo().addEvento(e);
		}else {
			vista.getControlAbonoCiclo().remEvento(e);
		}
		
	}
}
