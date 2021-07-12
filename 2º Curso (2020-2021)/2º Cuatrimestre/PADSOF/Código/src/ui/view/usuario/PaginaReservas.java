package ui.view.usuario;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Image;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import sistema.Sistema;
import teatro.Teatro;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.ControlBack;
import ui.control.compra.ControlCompra;
import ui.control.usuario.ControlSeleccionarReserva;

public class PaginaReservas extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = -2520628370078986934L;
	private JButton back = new JButton();
	private ListaReservas reservas= new ListaReservas();
	private ControlCompra cc;
	public void setControlador(ControlBack cb, ControlCompra cc, ControlSeleccionarReserva csr) {
		this.back.addActionListener(cb);
		this.cc = cc;
		this.reservas.setControlador(csr);
	}
	
	public ControlCompra getControlCompra() {
		return this.cc;
	}
	
	public ListaReservas getListaReservas() {
		return this.reservas;
	}
	
	public PaginaReservas() {
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		main.add(back, BorderLayout.SOUTH);
		main.add(this.reservas, BorderLayout.CENTER);
		main.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(50, 50));
		this.setViewportView(main);
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

			c.add(new PaginaReservas());
		} catch(Exception e) {
			System.out.println(e);
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		return;
	}
}
