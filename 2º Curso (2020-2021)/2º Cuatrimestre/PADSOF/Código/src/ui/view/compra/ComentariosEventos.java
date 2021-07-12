package ui.view.compra;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Calendar;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import evento.Concierto;
import evento.Representacion;
import sistema.Sistema;
import ui.control.ControlEvento;
import ui.control.compra.ControlCompra;

public class ComentariosEventos extends JScrollPane {

	private static final long serialVersionUID = 1L;
	private JPanel main = new JPanel();
	private JList<String> comentariosJLista;
	private JList<String> eventosJLista;
	private JLabel titulo = new JLabel("Comentarios: ");
	DefaultListModel<String> comentariosLista = new DefaultListModel<>();
	DefaultListModel<String> eventosLista = new DefaultListModel<>();
	
	ControlCompra cc = null;
	CardLayout cl = new CardLayout();
	public void setControl(ControlCompra cc, ControlEvento ce) {
		this.cc = cc;
		this.eventosJLista.addMouseListener(ce);
	}
	
	public ComentariosEventos() {
		eventosJLista = new JList<>(eventosLista);
		comentariosJLista = new JList<>(comentariosLista);
		comentariosJLista.addMouseListener(new MouseListener() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				
			}
			
			@Override
			public void mousePressed(MouseEvent arg0) {
				
			}
			
			@Override
			public void mouseExited(MouseEvent arg0) {
				
			}
			
			@Override
			public void mouseEntered(MouseEvent arg0) {
				
			}
			
			@Override
			public void mouseClicked(MouseEvent arg0) {
				if(comentariosJLista.getSelectedValue().equals(null)) {
					return;
				}
				JOptionPane.showMessageDialog(main, comentariosJLista.getSelectedValue(), "Comentario", JOptionPane.INFORMATION_MESSAGE);	
			}
		});
		JPanel main2 = new JPanel();
		main2.setLayout(new BorderLayout());
		main2.add(titulo, BorderLayout.NORTH);
		main2.add(main, BorderLayout.CENTER);
		main.setLayout(cl);
		main.add(comentariosJLista, "Comentarios");
		main.add(eventosJLista, "Eventos");
		main2.setVisible(true);
		this.add(main2);
		this.setViewportView(main2);
	}

	public void actualizarComentarios() {
		this.comentariosLista.clear();
		this.titulo.setText("Comentarios: ");
		if(cc.getEvento()!=null && cc.getEvento().getComentariosVisibles()!=null)
			cc.getEvento().getComentariosVisibles().stream().forEach(c -> this.comentariosLista.addElement(c.toStringUsuario()));
		main.setPreferredSize(comentariosJLista.getPreferredSize());
		this.validate();
		this.repaint();
	}
	
	public void actualizarEventos() {
		if(cc==null) {
			return;
		}
		this.eventosLista.clear();
		this.titulo.setText("Eventos: ");
		if(cc.getAbonoComprar()!=null) {
			if(cc.getAbonoComprar().getEventos()==null)
				titulo.setText("El abono anual incluye todos los eventos del año");
			else
				cc.getAbonoComprar().getEventos().forEach(e -> this.eventosLista.addElement(e.getTitulo()));
		}
		main.setPreferredSize(eventosJLista.getPreferredSize());
		this.validate();
		this.repaint();
	}
	
	public void mostrarEventos() {
		cl.show(main, "Eventos");
		this.validate();
		this.repaint();
	}

	public void mostrarComentarios() {
		cl.show(main, "Comentarios");
		this.validate();
		this.repaint();
	}
	
	public static void main (String...args) {
		JFrame ventana = new JFrame("Prueba_Main");
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
		c.add(new ComentariosEventos());
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	
}
