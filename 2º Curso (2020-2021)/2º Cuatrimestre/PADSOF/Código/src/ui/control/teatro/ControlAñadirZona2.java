package ui.control.teatro;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import sistema.Sistema;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.view.teatro.AñadirZona;
import ui.view.teatro.ConfTeatro;

public class ControlAñadirZona2 implements ActionListener{
	private AñadirZona az=null;
	private JFrame v=null;
	private ConfTeatro cf=null;
	
	public ControlAñadirZona2(AñadirZona z, JFrame v, ConfTeatro cf) {
		super();
		this.az = z;
		this.v = v;
		this.cf=cf;
	}

	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String nombre = az.getNombre();
		int col = 0;
		int fil = 0;
		int aforo = 0;
		String aux = az.getAforo();
		if(!aux.equals("") )
			aforo = Integer.parseInt(aux);
		aux=az.getColumnas();
		if(!aux.equals("") )
			col = Integer.parseInt(aux);
		aux=az.getFilas();
		if(!aux.equals("") )
			fil = Integer.parseInt(aux);
		if((col!=0 || fil!=0) && aforo!=0) {
			JOptionPane.showMessageDialog(v, "Debe decidir si crear zona numerada (filas y columnas) o no numerada (aforo).", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(col!=0 && fil!=0) {
			try {
				if(Sistema.getInstancia().getTeatro().addZona(new ZonaNumerada(nombre, fil, col))==false) {
					JOptionPane.showMessageDialog(v, "Ya existe una zona con ese nombre", "User Error", JOptionPane.ERROR_MESSAGE);
					return;
				}
			} catch (Exception e) {
				JOptionPane.showMessageDialog(v, "Error en la creación de la zona.", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			cf.getListaZonaNumerada().update();
		}
		else if (aforo!=0){
			try {
				if(Sistema.getInstancia().getTeatro().addZona(new ZonaNoNumerada(nombre, aforo))==false) {
					JOptionPane.showMessageDialog(v, "Ya existe una zona con ese nombre", "User Error", JOptionPane.ERROR_MESSAGE);
					return;
				}
			} catch (Exception e) {
				JOptionPane.showMessageDialog(v, "Error en la creación de la zona.", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			this.cf.getListaZonaNoNumerada().update();
		}
		else {
			JOptionPane.showMessageDialog(v, "Error en la creación de la zona, faltan valores por poner.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
	}

}
