package ui.control.compra;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.AbonoUsuario;
import sistema.Sistema;
import ui.view.Ventana;
import ui.view.compra.UICompra;
/**
 * Clase con el control para seleccionar el boton de abono y mostrar la lista de abonos
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlSeleccionarAbono implements ActionListener{

	private UICompra vista;
	private Ventana v;
	private ControlCompra cc;
	//private ControlSeleccionarAbono2 controlSeleccionarTarjeta2 = null;
	
	/**
	 * Constructor de la clase
	 * @param v ventana de la que obtiene la vista
	 */
	public ControlSeleccionarAbono(Ventana v) {
		super();
		this.vista = v.getUICompra();
		this.v = v;
	}
	
	/**
	 * Método con las instrucciones al presionar abono (mostrará una lista de abonos compatibles para la compra de entrada o reserva de representacion)
	 */
	public void actionPerformed(ActionEvent arg0) {
		this.cc = vista.getControlCompra();
		if(Sistema.getInstancia().getUsuarioEnUso()==null) { /*comprueba si hizó login (no debería ocurrir por los controles anteriores)*/
				JOptionPane.showMessageDialog(vista, "No puede seleccionar abono sin hacer log in ántes", "User Error", JOptionPane.ERROR_MESSAGE);
				return;
		}
		if(vista.getControlCompra().getEvento()==null) { /*si no hay evento seleccionado (no debería ocurrir)*/
			JOptionPane.showMessageDialog(vista, "Error inesperado", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		if(vista.getControlCompra().getR()==null) { /*si no ha seleccionado representacion (debería estar controlado por control next)*/
			JOptionPane.showMessageDialog(vista, "Por favor, seleccione primero la representación", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JFrame ventana = new JFrame("Seleccionar Abono"); /*crea el frame para seleccionar abono*/
		JScrollPane main1 = new JScrollPane();
		ventana.setContentPane(main1);
		JPanel main2 = new JPanel();
		int size = 0;
		/*añade al frame una lista de abonos compatibles para el proposito (compra de entrada/confirmar reserva)*/
		for(AbonoUsuario u : Sistema.getInstancia().getUsuarioEnUso().getAbonos()) {
			if(u.getAbono().comprobarValidez(vista.getControlCompra().getEvento())) { /*se muestran los abonos válidos*/
				if(vista.getMReserva()) {
					if(u.getAbono().getZona().equals(cc.getZ())) {
						size++;
						JButton au = new JButton(u.toString());
						au.addActionListener(new ControlSeleccionarAbono2(this.vista, u, ventana, v));
						main2.add(au);
					}
				}
				else {
					size++;
					JButton au = new JButton(u.toString());
					au.addActionListener(new ControlSeleccionarAbono2(this.vista, u, ventana, v));
					main2.add(au);
				}
			}
		}
		if(size==0) {
			ventana.dispose();
	  		JOptionPane.showMessageDialog(vista, "No dispone de ningún abono que sea válido para el evento seleccionado", "No Abonos", JOptionPane.INFORMATION_MESSAGE);
		}
		main2.setLayout(new GridLayout(size, 1));

		main1.add(main2);
		main2.setVisible(true);
		main1.setViewportView(main2);
		ventana.setVisible(true);
		//ventana.setSize(400, 400);
		ventana.pack();
	}

}
