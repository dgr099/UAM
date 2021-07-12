package ui.control.teatro;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import sistema.Sistema;
import teatro.Zona;
import ui.view.teatro.UILista;
public class ControlQuitarZona implements ActionListener{
	private Zona z=null;
	private JFrame f;
	private UILista p;
	public ControlQuitarZona(Zona z, JFrame f, UILista p){
		if(z==null) {
			return;
		}
		this.z = z;
		this.f=f;
		this.p=p;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(Sistema.getInstancia().getTeatro()!=null)
			Sistema.getInstancia().getTeatro().quitarZona(this.z); //elimina la zona del teatro
		this.f.dispose();
		this.p.update();
	}

}
