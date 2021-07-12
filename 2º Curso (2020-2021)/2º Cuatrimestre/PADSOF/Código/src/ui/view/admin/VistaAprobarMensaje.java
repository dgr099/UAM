package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import ui.control.ControlBack;
import ui.control.admin.ControlModerarComentario;

public class VistaAprobarMensaje extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 5918214602400910678L;
	private VistaMensaje vistaMensaje = new VistaMensaje();
	private JButton back = new JButton();
	private JButton aceptar = new JButton("aceptar");
	private JButton rechazar = new JButton("rechazar");
	private JButton modificar = new JButton("solicitar cambios");
	
	public VistaMensaje getVistaMensaje() {
		return this.vistaMensaje;
	}
	public void setControlador(ControlBack cb, ControlModerarComentario ca) {
		this.back.addActionListener(cb);
		this.aceptar.addActionListener(ca);
		this.rechazar.addActionListener(ca);
		this.modificar.addActionListener(ca);
	}
	public String getComentario() {
		return this.vistaMensaje.getComentario();
	}
	public VistaAprobarMensaje() {
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		JPanel main = new JPanel();
		JPanel south = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(vistaMensaje, BorderLayout.CENTER);
		main.add(south, BorderLayout.SOUTH);
		south.add(back);
		south.add(aceptar);
		south.add(rechazar);
		south.add(modificar);
		this.add(main);
		main.setPreferredSize(new Dimension(300, 150));
		this.setViewportView(main);
	}
	public static void main (String...args) {
		JFrame ventana = new JFrame("Prueba_Usuario");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		VistaAprobarMensaje vam = new VistaAprobarMensaje();
		//sc.updateString("Esto es un mensaje muy laaaaaargo para probaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaar");
		String text = new String();
		for(int i=0; i!=100; i++) {
			text += i + "Mensaje de prueba para ver que todo va como la seda\n";
		}
		vam.getVistaMensaje().updateString(text);
		c.add(vam);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
	

}
