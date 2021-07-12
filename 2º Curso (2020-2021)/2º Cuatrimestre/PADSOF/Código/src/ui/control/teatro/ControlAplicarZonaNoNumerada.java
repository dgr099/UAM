package ui.control.teatro;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import teatro.ZonaNoNumerada;
import ui.view.teatro.UIZonaNoNumerada;

public class ControlAplicarZonaNoNumerada implements ActionListener{
	public ControlAplicarZonaNoNumerada(ZonaNoNumerada z, UIZonaNoNumerada uz) {
		super();
		this.z = z;
		this.uz = uz;
	}

	private ZonaNoNumerada z;
	private UIZonaNoNumerada uz;
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(!uz.getAforo().equals(""))
			z.setAforo(Integer.parseInt(uz.getAforo()));
	}

}
