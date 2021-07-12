package ui.view;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.util.Calendar;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlEvento;
import ui.control.ControlVista_North;
import ui.control.ControlVista_North_admin;
import ui.control.ControlVista_South_iniciado;
import ui.control.ControlVista_South_sin_iniciar;
import ui.control.abonos.ControlAbonos;
import ui.control.admin.ControlStatListaEventos;
import ui.control.usuario.ControlSeleccionarCiclo;
import ui.view.abonos.AbonosUI;
import ui.view.admin.StatListaEventos;
public class VistaPrincipal extends JScrollPane{
	private static final long serialVersionUID = -7817790186240223662L;
	private VistaPrincipal_south vistaPrincipalSouth;
	private VistaPrincipal_North vistaPrincipalNorth;
	private JPanel center = new JPanel();
	private Cartelera c;
	private AbonosUI abonosui;
	private StatListaEventos stat;
	private MejorValoradosUI mValorados;
	
	CardLayout cl = new CardLayout();
	public StatListaEventos getStatListaEventos() {
		return this.stat;
	}
	
	public MejorValoradosUI getMejorValoradosUI() {
		return this.mValorados;
	}
	
	public AbonosUI getAbonosUI() {
		return this.abonosui;
	}

	public void setControlador(ControlVista_South_sin_iniciar sur, ControlVista_South_iniciado sur_2, ControlVista_North nort, ControlVista_North_admin nortAdmin, ControlEvento ce, ControlAbonos ca, ControlStatListaEventos cstat, ControlSeleccionarCiclo csc) {
		this.vistaPrincipalSouth.setControlador(sur, sur_2);
		this.vistaPrincipalNorth.setControlador(nort, nortAdmin);
		this.c.setControl(ce);
		this.c.actualizarValores();
		this.abonosui.setControlador(ca);
		this.stat.setControlador(cstat);
		this.mValorados.setControlador(ce, csc);
	}
	public void updateValoracion() {
		this.mValorados.update();
	}
	public void updateAbonos() {
		this.abonosui.update();
	}
	public VistaPrincipal_south getSouth() {
		return this.vistaPrincipalSouth;
	}
	public VistaPrincipal_North getNorth() {
		return this.vistaPrincipalNorth;
	}
	public Cartelera getCartelera() {
		return this.c;
	}
	public void viewDanza() {
		this.mostrarCartelera();
		this.c.filtrarDanza();
	}
	public void viewMusica() {
		this.mostrarCartelera();
		this.c.filtrarMusica();
	}
	public void viewTeatro() {
		this.mostrarCartelera();
		this.c.filtrarTeatro();
	}
	public void viewCartelera() {
		this.mostrarCartelera();
		this.c.mostrarCartelera();
	}
	public VistaPrincipal(){ /*constructor*/
		JPanel main = new JPanel();
		center.setLayout(cl);
		main.setLayout(new BorderLayout());
		this.vistaPrincipalSouth=new VistaPrincipal_south();
		main.add(this.vistaPrincipalSouth, BorderLayout.SOUTH);
		this.vistaPrincipalNorth = new VistaPrincipal_North();
		main.add(this.vistaPrincipalNorth, BorderLayout.NORTH);
		c = new Cartelera();
		abonosui = new AbonosUI();
		center.add(c, "Cartelera");
		center.add(abonosui, "Abonos");
		stat = new StatListaEventos();
		center.add(stat, "Stats");
		mValorados = new MejorValoradosUI();
		center.add(mValorados, "Mas Valorados");
		cl.show(center, "Cartelera");
		main.add(center, BorderLayout.CENTER);
		this.vistaPrincipalSouth.setVisible(true);
		this.vistaPrincipalSouth.setSize(new Dimension(100, 10));
		this.vistaPrincipalSouth.mostrarPanel("Sin Iniciar");
		main.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(200, 240));
		this.setViewportView(main);
	}
	public void mostrarAbonos() {
		cl.show(center, "Abonos");
	}
	public void mostrarCartelera() {
		cl.show(center, "Cartelera");
	}
	public void mostrarStats() {
		cl.show(center, "Stats");
	}
	public void mostrarMasValorados() {
		cl.show(center, "Mas Valorados");
	}
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		Sistema sis = Sistema.getInstancia();
		for(int i=0; i!=100; i++) {
			Concierto conc = new Concierto("descripcion", 120, "Concierto " + i, "yo", "tu", "el", "ellos");;
			Representacion rep = new Representacion(Calendar.getInstance(), 100);
			rep.getFechaYHora().set(Calendar.YEAR, 2022);
			conc.addRepresentacion(rep);
			sis.addEvento(conc);
		}
		c.setLayout(new BorderLayout());
		c.add(new VistaPrincipal());
		ventana.setVisible(true);
		ventana.setSize(500, 500);
		ventana.pack();
		return;
	}
}
