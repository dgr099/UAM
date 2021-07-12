package ui.control.admin;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.StringTokenizer;

import javax.swing.JOptionPane;

import evento.Evento;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal;
import ui.view.admin.StatEvento;
import ui.view.admin.StatListaEventos;

public class ControlStatListaEventos implements MouseListener{
	
	private Evento e = null;
	private Ventana v = null;
	private VistaPrincipal vista = null;
	private StatEvento stat = null;
	private StatListaEventos vista1 = null;
	public ControlStatListaEventos(Ventana v){
		this.v = v;
		this.vista = v.getVistaPrincipal();
		this.stat = v.getStatEvento();
		this.vista1 = v.getVistaPrincipal().getStatListaEventos();
	}
		@Override
		public void mouseClicked(MouseEvent arg0) {
			StringTokenizer tokenizer = new StringTokenizer(this.vista1.getEventoSelected(), ";");
			if(!tokenizer.hasMoreElements()) {
				JOptionPane.showMessageDialog(vista, "Error inesperado.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			String nombre = tokenizer.nextToken();
			for(Evento e : Sistema.getInstancia().getEventos()) {
				if(e.getTitulo().equals(nombre)) {
					this.e=e;
					break;
				}
			}
			if(e==null) {
				JOptionPane.showMessageDialog(vista, "Error, no se ha encontrado el evento.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			this.stat.setEvento(e); //le pones el evento a mostrar
			v.mostrarPanel("Stat"); //pasa a mostrar stat
			stat.setEnUso(true); //para que los controladores sepan de donde sacar la info
			
		}
		@Override
		public void mouseEntered(MouseEvent arg0) {
			// TODO Auto-generated method stub
			
		}
		@Override
		public void mouseExited(MouseEvent arg0) {
			// TODO Auto-generated method stub
			
		}
		@Override
		public void mousePressed(MouseEvent arg0) {
			// TODO Auto-generated method stub
			
		}
		@Override
		public void mouseReleased(MouseEvent arg0) {
			// TODO Auto-generated method stub
			
		}
}
