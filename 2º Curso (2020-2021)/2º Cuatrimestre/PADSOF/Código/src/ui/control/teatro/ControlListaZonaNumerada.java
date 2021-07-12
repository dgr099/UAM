package ui.control.teatro;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;

import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNumerada;
import ui.view.Ventana;
import ui.view.teatro.UITeatroListaZonasNumeradas;
import ui.view.teatro.UIZonaNumerada;
public class ControlListaZonaNumerada implements MouseListener{
	private UITeatroListaZonasNumeradas vista;
	public ControlListaZonaNumerada(Ventana v){
		this.vista = v.getConfTeatro().getListaZonaNumerada();
	}

		@Override
		public void mouseClicked(MouseEvent arg0) {
			JFrame uiZN =new JFrame();
			String zona = vista.getSelected();
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
			uiZN.getContentPane().add(new UIZonaNumerada((ZonaNumerada) z, uiZN, vista));
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
