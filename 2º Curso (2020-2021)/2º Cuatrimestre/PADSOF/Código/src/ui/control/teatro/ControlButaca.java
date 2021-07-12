package ui.control.teatro;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import teatro.ZonaNumerada;
public class ControlButaca implements ActionListener{
	private ZonaNumerada z=null;
	public ControlButaca(ZonaNumerada z){
		if(z==null) {
			return;
		}
		this.z = z;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String pos[] = ((JButton)arg0.getSource()).getText().split(":"); //obtiene el nombre del botón fila:columna
		int fila = Integer.parseInt(pos[0]); 
		int columna = Integer.parseInt(pos[1]); 
		if(z.getButacas()[fila][columna]==null) {
			try {
				z.addButaca(fila, columna); //añadimos butaca
				if(z.searchButaca(fila, columna).isActiva())
					((JButton)arg0.getSource()).setBackground(Color.GREEN); //le cambiamos el color al botón
				else {
					((JButton)arg0.getSource()).setBackground(Color.RED);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		else if(z.getButacas()[fila][columna].isActiva()) {
			z.getButacas()[fila][columna].setActiva(false);
			((JButton)arg0.getSource()).setBackground(Color.RED);
		}	
		else {
			z.getButacas()[fila][columna]=null;
			((JButton)arg0.getSource()).setBackground(Color.GRAY);
		}
	}

}
