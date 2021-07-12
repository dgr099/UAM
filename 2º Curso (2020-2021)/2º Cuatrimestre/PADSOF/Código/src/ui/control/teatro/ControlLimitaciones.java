package ui.control.teatro;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import sistema.Sistema;
import teatro.Zona;
import ui.view.Ventana;
import ui.view.teatro.TeatroHeader;
import usuario.Usuario;
public class ControlLimitaciones implements ActionListener{
	private TeatroHeader vista=null;
	
	public ControlLimitaciones(Ventana v) {
		super();
		this.vista = v.getConfTeatro().getHeader();
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		for(Usuario u : Sistema.getInstancia().getUsuarios()) {
			if(u.getEntradas().size()>0) {
				JOptionPane.showMessageDialog(vista, "No puede cambiar las limitaciones del teatro si ya se han vendido entradas", "INFO", JOptionPane.INFORMATION_MESSAGE);
			}
		}
		double limitaciones = Double.parseDouble(this.vista.getLimitaciones());
		System.out.println(limitaciones); //debug
		if(Sistema.getInstancia().getTeatro()!=null)
			Sistema.getInstancia().getTeatro().setLimitaciones(limitaciones);
		for(Zona z : Sistema.getInstancia().getTeatro().getZonas()) { /*act las limitaciones de cada zona*/
			z.actLimitaciones();
		}
	}

}