package ui.control.usuario;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.StringTokenizer;

import javax.swing.JOptionPane;

import abonos.Ciclo;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal;

/**
 * Clase con el control para seleccionar un ciclo por el usuario
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionarCiclo implements MouseListener{
	Ventana v;
	VistaPrincipal vista;

	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene las vistas sobre las que actua
	 */
	public ControlSeleccionarCiclo(Ventana v) {
		this.v = v;
		vista = v.getVistaPrincipal();
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		String s = String.copyValueOf(vista.getMejorValoradosUI().getCiclosValorados().getCicloSelectedValue().toCharArray());
		StringTokenizer tokens = new StringTokenizer(s);
		String nombre = tokens.nextToken(";");
		Ciclo ciclo = null;
		for(Ciclo c : Sistema.getInstancia().getCiclos()) {
			if(c.getCod().equals(nombre)) {
				ciclo = c;
				break;
			}
		}
		if(ciclo==null) {
			JOptionPane.showMessageDialog(vista, "El ciclo seleccionado no se ha encontrado.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
		}
		tokens = null;
		v.getInfoCiclo().update(ciclo);
		v.mostrarPanel("InfoCiclo");
		return;
		
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
	
	/*public void valueChanged(ListSelectionEvent arg0) {
		if(vista.getMejorValoradosUI().getCiclosValorados().getCicloSelectedValue()==null) {
			return;
		}
		String s = String.copyValueOf(vista.getMejorValoradosUI().getCiclosValorados().getCicloSelectedValue().toCharArray());
		StringTokenizer tokens = new StringTokenizer(s);
		String nombre = tokens.nextToken(";");
		Ciclo ciclo = null;
		for(Ciclo c : Sistema.getInstancia().getCiclos()) {
			if(c.getCod().equals(nombre)) {
				ciclo = c;
				break;
			}
		}
		if(ciclo==null) {
			JOptionPane.showMessageDialog(vista, "El ciclo seleccionado no se ha encontrado.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
		}
		tokens = null;
		this.vista.getMejorValoradosUI().getCiclosValorados().getCiclosJList().clearSelection();
		v.getInfoCiclo().update(ciclo);
		v.mostrarPanel("InfoCiclo");
		return;
	}*/
}
