package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import ui.control.admin.ControlStatListaEventos;

// Vista para ver las estadisticas de una lista de eventos
public class StatListaEventos extends JScrollPane{

	/**
	 * 
	 */
	private static final long serialVersionUID = -4761272741429800603L;
	private DefaultListModel<String> eventosLista = new DefaultListModel<>();
	private JList<String> eventosJList = new JList<String>(eventosLista);
	
	/** 
	 * Metodo para actualizar los controladores de la vista
	 * @param ce contiene el controlador de la vista
	 */
	public void setControlador (ControlStatListaEventos ce) {
		this.eventosJList.addMouseListener(ce);
	}
	
	/**
	 * Metodo para obtener el evento seleccionado
	 * @return devuelve un evento
	 */
	public String getEventoSelected() {
		return this.eventosJList.getSelectedValue();
	}
	
	/**
	 * Metodo para actualizar la vista cuando sea necesario
	 */
	public void update() {
		eventosLista.removeAllElements();
		Sistema.getInstancia().getEventos().stream().forEach(e -> eventosLista.addElement(e.getStatString()));
		this.repaint();
		this.validate();
	}
	/**
	 * Método para añadir un evento a la lista de stat
	 * @param e Evento a añadir
	 */
	public void addElement(Evento e) {
		if(e==null)	return;
		eventosLista.addElement(e.getStatString());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para quitar un evento de la lista
	 * @param e Evento que se desea quitar
	 */
	public void removeElement(Evento e) {
		if(e==null)	return;
		for(int i=0; i!=eventosLista.getSize(); i++) {
			if(eventosLista.getElementAt(i).contains(e.getTitulo())) {
				eventosLista.removeElementAt(i);
				this.validate();
				this.repaint();
				break;
			}
		}
	}
	
	public StatListaEventos(){ /*constructor*/
		this.add(eventosJList);
		this.update();
		eventosJList.setVisible(true);
		this.setViewportView(eventosJList);
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_StatListaEventos");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		Sistema.getInstancia();
		try {
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto1", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto2", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto3", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto4", "DGR", "CerraOrquesta", "German", "Willyrex"));
			Sistema.getInstancia().addEvento(new Concierto("Concierto de prueba", 15, "Concierto5", "DGR", "CerraOrquesta", "German", "Willyrex"));
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		try {
			c.add(new StatListaEventos());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}