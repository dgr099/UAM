package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.StringTokenizer;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import evento.Evento;
import evento.Representacion;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.admin.CambiarRepresentacion;
import ui.view.admin.PAdmin;
import ui.view.admin.PaginaAdmin;
import ui.view.admin.StatEvento;

public class ControlCambiarFechaRepresentacion implements ActionListener{
	private JFrame ventana;
	private CambiarRepresentacion vista1;
	private Ventana v;
	private PaginaAdmin vista2;
	private StatEvento vista3;
	private PAdmin vista;
	
	
	public class ControlCambiarFechaRepresentacion2 implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			String cod = vista.getRepresentacionSelectedValue();
			if(cod == null) {
				JOptionPane.showMessageDialog(vista1, "Error, no se seleccionó ninguna representacion.", "Error No Value Selected", JOptionPane.ERROR_MESSAGE);
				return;
			}
			Date fecha;
			/*obtenemos la fecha*/
			try {
				fecha = new SimpleDateFormat("dd/MM/yyyy").parse(vista1.getFecha());
			} catch (ParseException e) {
				JOptionPane.showMessageDialog(vista1, "Error, el formato para la fecha es incorrecto.\nEl formato debe ser dd/MM/yyyy.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				e.printStackTrace();
				return;
			}
			if(Calendar.getInstance().getTime().after(fecha)) {
				JOptionPane.showMessageDialog(vista1, "Error, no se puede establecer un evento en una fecha pasada.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			/*buscamos la representación seleccionada*/
			int num;
			Evento evento = null;
			StringTokenizer tokens=new StringTokenizer(cod);
			num = Integer.parseInt((String) tokens.nextToken(")"));
			String name = tokens.nextToken(";");
			name = name.substring(2);
			//name += tokens.nextToken(";");
			for(Evento e : Sistema.getInstancia().getEventos()) {
				if(e.getTitulo().equals(name)) {
					evento = e;
					break;
				}
			}
			if(evento == null) {
				JOptionPane.showMessageDialog(vista1, "Error, no se encontró el evento.", "Error Evento", JOptionPane.ERROR_MESSAGE);
				return;
			}
			Representacion r = evento.getRepresentaciones().get(num);
			if(r == null) {
				JOptionPane.showMessageDialog(vista1, "Error, no se encontró la representación.", "Error Representacion", JOptionPane.ERROR_MESSAGE);
				return;
			}
			Calendar nFecha = Calendar.getInstance();
			nFecha.setTime(fecha);
			r.cambiarFecha(nFecha); /*si todo salió correctamente se cambia la fecha de ña representacion*/
			vista2.update();
			vista3.setEvento(evento);
			v.getPaginaUsuario().update();
			JOptionPane.showMessageDialog(vista1, "La fecha de la representación fue modificada.", "Representación modificada", JOptionPane.INFORMATION_MESSAGE);
			ventana.dispose();
		}
		
	}
	
	public ControlCambiarFechaRepresentacion(Ventana v) {
		this.v = v;
		vista1 = v.getCambiarRepresentacion();
		vista2 = v.getPaginaAdmin();
		vista1.setControlador(new ControlCambiarFechaRepresentacion2());
		this.vista3 = v.getStatEvento();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) { /*el de dar al botón de crear que abre una ventana para introducir los datos*/
		if(vista3.getEnUso()) {
			vista = vista3.getPaginaEventoAdmin();
		}
		else {
			vista = vista2;
		}
		String cod = vista.getRepresentacionSelectedValue();
		if(cod == null) {
			JOptionPane.showMessageDialog(vista1, "Error, no se seleccionó ninguna representacion.", "Error No Value Selected", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JFrame nuevaR = new JFrame();
		this.ventana = nuevaR;
		nuevaR.getContentPane().add(this.vista1);
		vista1.setVisible(true);
		ventana.setVisible(true);
		nuevaR.setSize(400, 400);
		
	
	}

}
