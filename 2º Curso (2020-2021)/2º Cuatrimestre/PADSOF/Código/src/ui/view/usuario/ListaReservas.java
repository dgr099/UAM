package ui.view.usuario;

import java.awt.BorderLayout;
import java.awt.Container;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import reserva.Reserva;
import sistema.Sistema;
import teatro.Teatro;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.usuario.ControlSeleccionarReserva;
import usuario.Usuario;

public class ListaReservas extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 4068805395119889928L;
	private DefaultListModel<String> reservasLista = new DefaultListModel<>();
	private JList<String> reservasJList = new JList<String>(reservasLista);
	public ListaReservas() {
	JPanel main = new JPanel();
	main.setLayout(new BorderLayout());
	main.add(reservasJList, BorderLayout.CENTER);
	this.actualizasValores();
	main.setVisible(true);
	this.add(main);
	this.setViewportView(main);
	}
	public void setControlador(ControlSeleccionarReserva csr) {
		this.reservasJList.addMouseListener(csr);
	}
	/**
	 * Método para obtener la reserva seleccionada de la lista
	 * @return string descriptivo de la reserva
	 */
	public String getSelected() {
		return this.reservasJList.getSelectedValue();
	}
	public void actualizasValores() {
		reservasLista.clear();
		Usuario u = Sistema.getInstancia().getUsuarioEnUso();
		if(u==null) {
			return;
		}
		for(Reserva r : u.getReservas()) {
			this.reservasLista.addElement(r.getCodigo() + "; " + r.getRepresentacion().getEvento().getTitulo() + " " + r.getRepresentacion().getFechaYHora().getTime());
		}
		this.validate();
		this.repaint();
	}
	/**
	 * Método para añadir una reserva a la lista
	 * @param r reserva que se desea añadir
	 */
	public void addElement(Reserva r) {
		if(r==null || this.reservasLista.contains(r.getCodigo() + "; " + r.getRepresentacion().getEvento().getTitulo() + " " + r.getRepresentacion().getFechaYHora().getTime()))	
			return;
		this.reservasLista.addElement(r.getCodigo() + "; " + r.getRepresentacion().getEvento().getTitulo() + " " + r.getRepresentacion().getFechaYHora().getTime());
		this.validate();
		this.repaint();
	}
	
	public void removeElement(Reserva r) {
		if(r==null || !this.reservasLista.contains(r.getCodigo() + "; " + r.getRepresentacion().getEvento().getTitulo() + " " + r.getRepresentacion().getFechaYHora().getTime()))	
			return;
		this.reservasLista.removeElement(r.getCodigo() + "; " + r.getRepresentacion().getEvento().getTitulo() + " " + r.getRepresentacion().getFechaYHora().getTime());
		this.validate();
		this.repaint();
	}
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_InfoEntrada");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		try {
			Calendar cal= Calendar.getInstance();
			cal.set(2021, 5, 25, 14, 20, 00);
			Representacion r = new Representacion(cal, 50);
			Evento e = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			((Concierto)e).addPieza("Pieza1");
			((Concierto)e).addPieza("Pieza2");
			Teatro teat = new Teatro("Teatro1", 20);
			ZonaNoNumerada z = new ZonaNoNumerada("ZNN1", 30);
			List<ZonaNumerada> zn = new ArrayList<ZonaNumerada>();
			z.setTeatro(teat);
			teat.addZona(z);
			e.addRepresentacion(r);
			e.addPrecioZona(z, 25);
			Sistema.getInstancia().registro("abc", "abc");
			r.setPd(new PolíticaDeReseva(20, 2, 3));
			for(int i=0; i!=50; i++) {
				zn.add(new ZonaNumerada("zonita", 20, 20));
				zn.get(i).setTeatro(teat);
				e.addPrecioZona(zn.get(i), 30);
				Sistema.getInstancia().getUsuarioEnUso().reservarButaca(r, zn.get(i).searchButaca(0, 0));
			}

			c.add(new ListaReservas());
		} catch(Exception e) {
			System.out.println(e);
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		return;
	}
}
