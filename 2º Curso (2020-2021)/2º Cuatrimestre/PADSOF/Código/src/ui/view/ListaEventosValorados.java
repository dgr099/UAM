package ui.view;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.AbonoAnual;
import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.ControlEvento;
import ui.view.teatro.UILista;

public class ListaEventosValorados extends JScrollPane implements UILista{	
	private static final long serialVersionUID = 650385903029733333L;
	private List<Evento> eventosMejorValorados = new ArrayList<Evento>();
	private DefaultListModel<String> eventosName = new DefaultListModel<>();
	private JList<String> eventosJList = new JList<String>(eventosName);
	private JPanel main;
	private JLabel titulo = new JLabel("Eventos:");

	public void setControlador(ControlEvento cev) {
		eventosJList.addMouseListener(cev);
	}
	/*constructor para utilizar cuando quiere comprar una entrada*/
	public ListaEventosValorados(){ /*constructor*/
		main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		main.add(eventosJList, BorderLayout.CENTER);
		if(Sistema.getInstancia().getEventos()==null) {
			return;
		}
		this.update();
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			for(int i=0; i!=5; i++) {
				Concierto con = new Concierto("des", 20, "prueba" + i, "aut", "orq", "abc", "def");
				con.addValoracion(i);
				Sistema.getInstancia().addEvento(con);
			}
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new ListaEventosValorados());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	
	@Override
	public void update() {
		if(Sistema.getInstancia().getEventos()==null) {
			return;
		}
		this.eventosName.clear();
		eventosMejorValorados.clear();
		eventosMejorValorados.addAll(Sistema.getInstancia().getEventos());
		Collections.sort(eventosMejorValorados, new Comparator<Evento>() {
				@Override
				public int compare(Evento arg0, Evento arg1) {
					if(arg0.getValoracion() - arg1.getValoracion()>0) {
						return -1;
					}
					return 1;
				}
			});
		eventosMejorValorados.stream().forEach(e -> this.eventosName.addElement(e.getTitulo() + "; " + e.getValorString()));
		this.validate();
		this.repaint();
		this.revalidate();
	}
	
	/**
	 * Método para añadir eventos a la listta
	 * @param e Evento que se desea añadir
	 */
	public void addElement(Evento e) {
		if(e==null)	return;
		if(eventosMejorValorados.contains(e))	return;
		this.eventosName.addElement(e.getTitulo() + "; " + e.getValorString());
		this.validate();
		this.repaint();
	}
	/**
	 * Método para quitar eventos de la lista
	 * @param e Evento que se desea quitar
	 */
	public void removeElement(Evento e) {
		if(e==null)	return;
		if(eventosMejorValorados.contains(e))	return;
		for(int i=0; i!=this.eventosName.getSize(); i++) {
			if(eventosName.getElementAt(i).contains(e.getTitulo())) {
				this.eventosName.remove(i);
				this.eventosMejorValorados.remove(e);
				return;
			}
		}
		this.validate();
		this.repaint();
	}
}
