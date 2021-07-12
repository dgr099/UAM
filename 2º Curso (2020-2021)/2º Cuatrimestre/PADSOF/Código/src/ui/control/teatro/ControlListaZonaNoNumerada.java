package ui.control.teatro;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import ui.view.Ventana;
import ui.view.teatro.UITeatroListaZonasNoNumeradas;
import ui.view.teatro.UIZonaNoNumerada;
public class ControlListaZonaNoNumerada implements MouseListener{
	private UITeatroListaZonasNoNumeradas vista;
	public ControlListaZonaNoNumerada(Ventana v){
		this.vista = v.getConfTeatro().getListaZonaNoNumerada();
	}
		@Override
		public void mouseClicked(MouseEvent arg0) {
			String zona = vista.getSelectedValue();
			Zona z = null;
			for(Zona z1 : Sistema.getInstancia().getTeatro().getZonas()) {
				if(zona.equals(z1.getNombre())) {
					z = z1;
					break;
				}
			}
			if(z == null) {
				return;
			}
			JFrame uiZN =new JFrame();
			uiZN.getContentPane().add(new UIZonaNoNumerada((ZonaNoNumerada) z, uiZN, vista));
			uiZN.setVisible(true);
			uiZN.setSize(400, 400);
			
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
