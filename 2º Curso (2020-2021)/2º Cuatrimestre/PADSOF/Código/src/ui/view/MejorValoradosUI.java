package ui.view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.ControlEvento;
import ui.control.usuario.ControlSeleccionarCiclo;
import ui.view.ListaCiclosValorados;

public class MejorValoradosUI extends JScrollPane {
		/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
		private ListaEventosValorados listaEV = new ListaEventosValorados();
		private ListaCiclosValorados listaCV = new ListaCiclosValorados();
		
		public void setControlador(ControlEvento cev, ControlSeleccionarCiclo csc) {
			listaEV.setControlador(cev);
			listaCV.setControlador(csc);
		}
		
		public ListaCiclosValorados getCiclosValorados() {
			return this.listaCV;
		}
		
		public ListaEventosValorados getEventosValorados() {
			return this.listaEV;
		}
		
		public MejorValoradosUI(){ /*constructor*/
			JPanel main = new JPanel();
			BorderLayout bL = new BorderLayout();
			main.setLayout(bL);
			JPanel center = new JPanel();
			center.setLayout(new GridLayout(1, 2));
			center.add(listaEV);
			center.add(listaCV);
			main.add(center, BorderLayout.CENTER); //ponemos la lista de zonas
			main.setVisible(true);
			this.add(main);
			this.setViewportView(main);
			main.setPreferredSize(new Dimension(200, 240));
		}
		
	public void update() {
		this.listaCV.update();
		this.listaEV.update();
	}
	public static void main (String...args) {
		JFrame ventana = new JFrame("Prueba_Cartelera");
		for(int i=0; i!=101; i++) {
			try {
				Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		for(int i=0; i!=101; i++) {
			try {
				ArrayList<Evento> ev = new ArrayList<Evento>();
				ev.add(new Concierto("ojala me muera", 120, "titulo", "jo", "lines", "pe", "pa"));
				Sistema.getInstancia().addAbono(new AbonoCiclo(20, ev, new ZonaNoNumerada("Prueba", 5)));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			c.add(new MejorValoradosUI());
		} catch (Exception e) {
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	
}
