package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import abonos.Abono;
import abonos.AbonoAnual;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.AddAbonoAnual;

/**
 * Clase para el control de añadir abono anual
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddAbonoAnual implements ActionListener{
	Ventana v;
	AddAbonoAnual vista;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlAddAbonoAnual(Ventana v) {		 
		this.v = v;
		vista = v.getAddAbonoAnual();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		try { /*intenta crear y añadir el abono con los datos introducidos*/
			Abono a = new AbonoAnual(Double.parseDouble(vista.getPrecio()), vista.getZona());
			Sistema.getInstancia().addAbono(a);
			JOptionPane.showMessageDialog(vista, "Se ha añadido el abono anual satisfactoriamente.", "Abono añadido", JOptionPane.INFORMATION_MESSAGE);
			v.getPaginaEliminarAbono().addElement(a); /*update en la pagina de abonos a eliminar*/
			v.getVistaPrincipal().getAbonosUI().getListaAbonosAnuales().addElement(a); /*update los abonos de la ui para usuario no administrador*/

		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(vista, "Lo sentimos, ha ocurrido un error y no se ha podido añadir el abono.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
		}
	}
}
