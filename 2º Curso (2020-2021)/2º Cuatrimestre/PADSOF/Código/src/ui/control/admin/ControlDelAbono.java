package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import abonos.Abono;
import abonos.AbonoAnual;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.PaginaEliminarAbono;

/**
 * Control para eliminar un abono del sistema
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlDelAbono implements ActionListener{
	Ventana v;
	PaginaEliminarAbono vista;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlDelAbono(Ventana v) {
		this.v = v;
		vista = v.getPaginaEliminarAbono();
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String nom = vista.getAbonoSelectedValue();
		Abono a = null;
		for(Abono abono : Sistema.getInstancia().getAbonos()) {
			if(abono.getCodigo().equals(nom)) {
				a = abono;
				break;
			}
		}
		if(a==null) {
			JOptionPane.showMessageDialog(vista, "No se encontró el abono seleccionado.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		Sistema.getInstancia().removeAbono(a);
		vista.removeElement(a);
		if(a instanceof AbonoAnual) {
			v.getVistaPrincipal().getAbonosUI().getListaAbonosAnuales().removeElement(a);
		}else {
			v.getVistaPrincipal().getAbonosUI().getListaAbonosCiclo().removeElement(a);
		}
		JOptionPane.showMessageDialog(vista, "El abono fue eliminado.", "Abono Eliminado", JOptionPane.INFORMATION_MESSAGE);
	}

}
