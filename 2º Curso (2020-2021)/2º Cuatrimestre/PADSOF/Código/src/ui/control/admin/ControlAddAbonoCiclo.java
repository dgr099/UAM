package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JOptionPane;

import abonos.AbonoCiclo;
import evento.Evento;
import sistema.Sistema;
import teatro.Zona;
import ui.view.Ventana;
import ui.view.admin.AddAbonoCiclo;

/**
 * Clase con el control para añadir abonos de ciclo
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddAbonoCiclo implements ActionListener{
	AddAbonoCiclo vista;
	Ventana v;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlAddAbonoCiclo(Ventana v) {
		this.v = v;
		vista = v.getAddAbonoCiclo();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		double desc;
		try { /*intentamos obtener el descuento*/
			desc = Double.parseDouble(vista.getDescuento());
		}
		catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(vista, "Lo sentimos, no se ha podido convertir el descuento a su valor numérico", "User Error", JOptionPane.ERROR_MESSAGE); /*en caso de no seleccionarse ninguna representación se le notifica que debe hacerlo para añadirse a una lista de espera*/
			return;
		}
		Zona z = vista.getZona(); /*obtenemos la zona*/
		ArrayList<Evento> ev = new ArrayList<Evento>(vista.getControlAbonoCiclo().getEventos()); /*obtenemos la lista de eventos*/
		AbonoCiclo ac;
		try {
			ac = new AbonoCiclo(desc, ev, z); /*creamos el abono con las datos recibidos de la vista introducidos por el admin*/
		} catch (Exception e) {
			JOptionPane.showMessageDialog(vista, "Ha ocurrido un error al crear el abono, recuerde que el ciclo no puede estar vacío", "User Error", JOptionPane.ERROR_MESSAGE); /*en caso de no seleccionarse ninguna representación se le notifica que debe hacerlo para añadirse a una lista de espera*/
			e.printStackTrace();
			return;
		}
		Sistema.getInstancia().addAbono(ac);
		v.getPaginaEliminarAbono().addElement(ac); /*update en la pagina de abonos a eliminar*/
		v.getVistaPrincipal().getAbonosUI().getListaAbonosCiclo().addElement(ac); /*update los abonos de la ui para usuario no administrador*/
		v.getVistaPrincipal().getMejorValoradosUI().getCiclosValorados().addElement(ac.getCiclo());
		JOptionPane.showMessageDialog(vista, "Se ha creado el abono exitosamente", "User Error", JOptionPane.INFORMATION_MESSAGE);

	}
}

