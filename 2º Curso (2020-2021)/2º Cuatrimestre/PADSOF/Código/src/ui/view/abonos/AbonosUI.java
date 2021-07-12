package ui.view.abonos;

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
import ui.control.abonos.ControlAbonos;

/* vista para ver las distintas listas de abonos */
public class AbonosUI extends JScrollPane {
	
	private static final long serialVersionUID = 1L;
	private ListaAbonosCiclo listaAC = new ListaAbonosCiclo();
	private ListaAbonosAnuales listaAA = new ListaAbonosAnuales();
	
	/**
	 * Metodo para actualizar los controladores de la vista
	 * @param ca Controlador de lista de abonos
	 */
	public void setControlador(ControlAbonos ca) {
		listaAA.setControlador(ca);
		listaAC.setControlador(ca);
	}
	
	/**
	 * Metodo para actualizar las lista cuando sea necesario
	 */
	public void update() {
		this.listaAA.update();
		this.listaAC.update();
	}
	
	/**
	 * Metodo para obtener la lista de abonos anuales
	 * @return Retorna la vista de la lista de abonos anuales
	 */
	public ListaAbonosAnuales getListaAbonosAnuales() {
		return this.listaAA;
	}
	
	/**
	 * Metodo para obtener la lista de abonos de ciclo
	 * @return Retorna la vista de la lista de abonos de ciclo
	 */
	public ListaAbonosCiclo getListaAbonosCiclo() {
		return this.listaAC;
	}
	
	public AbonosUI(){ /*constructor*/
		JPanel main = new JPanel();
		BorderLayout bL = new BorderLayout();
		main.setLayout(bL);
		JPanel center = new JPanel();
		center.setLayout(new GridLayout(1, 2));
		center.add(listaAA);
		center.add(listaAC);
		main.add(center, BorderLayout.CENTER); //ponemos la lista de zonas
		main.setVisible(true);
		this.add(main);
		this.setViewportView(main);
		main.setPreferredSize(new Dimension(200, 240));
	}
	
	/* main para ver el panel */
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
			c.add(new AbonosUI());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
}
