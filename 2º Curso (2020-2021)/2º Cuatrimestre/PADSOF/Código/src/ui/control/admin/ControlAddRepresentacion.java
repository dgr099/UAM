package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import evento.Representacion;
import reserva.PolíticaDeReseva;
import ui.view.Ventana;
import ui.view.admin.AddRepresentacion;
import ui.view.admin.StatEvento;

/**
 * Clase con el control para añadir una representacion a un evento
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddRepresentacion implements ActionListener{
	private AddRepresentacion vista;
	private StatEvento sev;
	private JFrame ventana;
	private Ventana v;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas
	 */
	public ControlAddRepresentacion(Ventana v) {
		this.v = v;
		vista = v.getAddRepresentacion();
		sev = v.getStatEvento();
		vista.setControlador(new ControlAddRepresentacion2());
		v.getStatEvento();
	}
	
	/**
	 * Clase interna con el control para aceptar y añadir la representacion
	 * @author David Teófilo Garitagoitia Romero
	 *
	 */
	public class ControlAddRepresentacion2 implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			Date fecha;
			try {
				fecha = new SimpleDateFormat("dd/MM/yyyy").parse(vista.getFecha());
			} catch (ParseException e) {
				JOptionPane.showMessageDialog(vista, "Error, el formato para la fecha es incorrecto.\nEl formato debe ser dd/MM/yyyy.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				e.printStackTrace();
				return;
			}
			if(Calendar.getInstance().getTime().after(fecha)) {
				JOptionPane.showMessageDialog(vista, "Error, no se puede establecer un evento en una fecha pasada.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			Calendar cad = Calendar.getInstance();
			cad.setTime(fecha);
			PolíticaDeReseva pd;
			try {
				pd = new PolíticaDeReseva(Integer.parseInt(vista.getMax()), Integer.parseInt(vista.getLim()), Integer.parseInt(vista.getDur()));
			} catch (NumberFormatException e) {
				e.printStackTrace();
				JOptionPane.showMessageDialog(vista, "Error, recuerde que los valores para la política de reserva deben ser numéricos", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			} catch (Exception e) {
				e.printStackTrace();
				JOptionPane.showMessageDialog(vista, "Lo sentimos ha ocurrido un error con la política de reserva:\n" + e.getMessage(), "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			Representacion r = new Representacion(cad, Integer.parseInt(vista.getAforo()));
			r.setPd(pd);
			sev.getEvento().addRepresentacion(r);
			v.getVistaPrincipal().getCartelera().addElementCartelera(sev.getEvento()); /*añadimos el evento a cartelera por si no estaba antes*/
			v.getStatEvento().getPaginaEventoAdmin().addElement(r);
			v.getPaginaAdmin().addElement(r);
			JOptionPane.showMessageDialog(vista, "Representación añadida con éxito.", "Representación añadida", JOptionPane.INFORMATION_MESSAGE);
			ventana.dispose();
		}
		
	}
	public void actionPerformed(ActionEvent arg0) {
		JFrame nuevaR = new JFrame();
		this.ventana = nuevaR;
		nuevaR.getContentPane().add(this.vista);
		vista.setVisible(true);
		ventana.setVisible(true);
		nuevaR.setSize(400, 400);
		
	}

}
