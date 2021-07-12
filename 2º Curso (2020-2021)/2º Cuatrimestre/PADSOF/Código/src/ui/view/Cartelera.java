package ui.view;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Container;
import java.util.Calendar;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Danza;
import evento.Evento;
import evento.ObraTeatro;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlEvento;

public class Cartelera extends JScrollPane {

	private static final long serialVersionUID = 1L;
	Calendar now = Calendar.getInstance();
	private DefaultListModel<String> eventosCarteleraList = new DefaultListModel<>();
	private JList<String> eventosCartelera = new JList<String>(eventosCarteleraList);
	private DefaultListModel<String> eventosDanzaList = new DefaultListModel<>();
	private JList<String> eventosDanza = new JList<String>(eventosDanzaList);
	private DefaultListModel<String> eventosMusicaList = new DefaultListModel<>();
	private JList<String> eventosMusica = new JList<String>(eventosMusicaList);
	private DefaultListModel<String> eventosTeatroList = new DefaultListModel<>();
	private JList<String> eventosTeatro = new JList<String>(eventosTeatroList);
	JPanel Cartelera = new JPanel();
	CardLayout cl = new CardLayout();
	public void setControl(ControlEvento ce) {
		this.eventosCartelera.addMouseListener(ce);
		this.eventosDanza.addMouseListener(ce);
		this.eventosTeatro.addMouseListener(ce);
		this.eventosMusica.addMouseListener(ce);
	}
	public Cartelera() {
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(Cartelera, BorderLayout.CENTER);
		Cartelera.setLayout(cl);
		Cartelera.add(eventosCartelera, "cartelera");
		Cartelera.add(eventosDanza, "danza");
		Cartelera.add(eventosMusica, "musica");
		Cartelera.add(eventosTeatro, "teatro");
		this.actualizarValores();
		this.mostrarCartelera();
		main.setVisible(true);
		this.add(main);
		this.setViewportView(main);
	}
	
	public void mostrarCartelera() {
		cl.show(Cartelera, "cartelera");
		this.Cartelera.setPreferredSize(this.eventosCartelera.getPreferredSize());
		this.validate();
		this.repaint();
	}
	
	public void actualizarValores() {
		this.eventosCartelera.removeAll(); //quitamos todos los botones de cartelera
		this.eventosDanza.removeAll(); //quitamos todos los botones de danza
		this.eventosTeatro.removeAll(); //quitamos todos los botones de teatro
		this.eventosMusica.removeAll(); //quitamos todos los botones de musica
		
	
		for(Evento e: Sistema.getInstancia().getEventos()) {
			Calendar today = Calendar.getInstance();
			List<Representacion> rlist = e.getRepresentaciones();
			boolean flag = false;
			for(Representacion r : rlist) {
				if(!today.after(r.getFechaYHora())) {
					flag = true;
					break;
				}
			}
			if(flag==true) {
				this.eventosCarteleraList.addElement(e.getTitulo());
			}
			if(e instanceof Danza) {
				this.eventosDanzaList.addElement(e.getTitulo());
			}
			else if(e instanceof Concierto) {
				this.eventosMusicaList.addElement(e.getTitulo());
			}
			else if(e instanceof ObraTeatro) {
				this.eventosTeatroList.addElement(e.getTitulo());
			}
			
		}
		this.validate();
		this.repaint();
	}
	
	public void filtrarDanza() {
		cl.show(Cartelera, "danza");
		this.Cartelera.setPreferredSize(this.eventosDanza.getPreferredSize());
		this.validate();
		this.repaint();
	}
	
	public void filtrarMusica() {
		cl.show(Cartelera, "musica");
		this.Cartelera.setPreferredSize(this.eventosMusica.getPreferredSize());
		this.validate();
		this.repaint();
	}
	
	public void filtrarTeatro() {
		cl.show(Cartelera, "teatro");
		this.Cartelera.setPreferredSize(this.eventosTeatro.getPreferredSize());
		this.validate();
		this.repaint();
	}
	public void removeElement(Evento e) {
		if(e==null)	return;
		if(this.eventosCarteleraList.contains(e.getTitulo())) {
			this.eventosCarteleraList.removeElement(e.getTitulo());
		}
		if(e instanceof Danza) {
			this.eventosDanzaList.removeElement(e.getTitulo());
		}
		else if(e instanceof Concierto) {
			this.eventosMusicaList.removeElement(e.getTitulo());
		}
		else if(e instanceof ObraTeatro) {
			this.eventosTeatroList.removeElement(e.getTitulo());
		}
	}
	/**
	 * Añade un evento a su lista correspondiente en función del tipo de evento
	 * @param e Evento a añadir
	 */
	public void addElement(Evento e) {
		if(e instanceof Danza) {
			if(this.eventosDanzaList.contains(e.getTitulo()))	return;
			this.eventosDanzaList.addElement(e.getTitulo());
		}
		else if(e instanceof Concierto) {
			if(this.eventosMusicaList.contains(e.getTitulo()))	return;
			this.eventosMusicaList.addElement(e.getTitulo());
		}
		else if(e instanceof ObraTeatro) {
			if(this.eventosTeatroList.contains(e.getTitulo()))	return;
			this.eventosTeatroList.addElement(e.getTitulo());
		}
		this.revalidate();
		this.repaint();
	}
	
	/**
	 * Se añade un evento a la cartelera (primero se comprueba que efectivamente tiene alguna representacion futura)
	 * @param e Evento a añadir a la cartelera
	 */
	public void addElementCartelera(Evento e) {
		if(e==null || eventosCarteleraList.contains(e.getTitulo()))	return; 
		Calendar today = Calendar.getInstance();
		List<Representacion> rlist = e.getRepresentaciones();
		boolean flag = false;
		for(Representacion r : rlist) {
			if(!today.after(r.getFechaYHora())) {
				flag = true;
				break;
			}
		}
		if(flag==true) {
			this.eventosCarteleraList.addElement(e.getTitulo());
		}
		this.validate();
		this.repaint();
	}
	
	/**
	 * Comprobar si se mantiene elemento después de quitar una representación
	 * @param e Evento a comprobar
	 */
	public void compElemento(Evento e) {
		if(e==null || !eventosCarteleraList.contains(e.getTitulo()))	return; 
		Calendar today = Calendar.getInstance();
		List<Representacion> rlist = e.getRepresentaciones();
		boolean flag = false;
		for(Representacion r : rlist) {
			if(!today.after(r.getFechaYHora())) {
				flag = true;
				break;
			}
		}
		if(flag==false) { /*si después de quitar la representacion ya no hay ninguna válida*/
			this.eventosCarteleraList.removeElement(e.getTitulo());
			this.validate();
			this.repaint();
		}
	}
	
	public static void main (String...args) {
		JFrame ventana = new JFrame("Prueba_Cartelera");
		Sistema sis = Sistema.getInstancia();
		for(int i=0; i!=101; i++) {
			Concierto conc = new Concierto("descripcion", 120, "Concierto " + i, "yo", "tu", "el", "ellos");;
			Representacion rep = new Representacion(Calendar.getInstance(), 100);
			rep.getFechaYHora().set(2022, 2, 5);
			conc.addRepresentacion(rep);
			sis.addEvento(conc);
		}
		
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new Cartelera());
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	
}
