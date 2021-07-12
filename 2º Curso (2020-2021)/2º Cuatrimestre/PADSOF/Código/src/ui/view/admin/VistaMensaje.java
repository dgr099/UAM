package ui.view.admin;

import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class VistaMensaje extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = 7647591732819938659L;
	JTextArea main = new JTextArea();
	public VistaMensaje() {
		this.add(main);
		this.setViewportView(main);
		main.setVisible(true);
	}
	
	public String getComentario() {
		return this.main.getText();
	}
	
	public void updateString(String s) {
		main.setText(s);
		main.setEditable(false);
		this.revalidate();
		this.repaint();
	}
	public static void main (String...args) {
		JFrame ventana = new JFrame("Prueba_Usuario");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		VistaMensaje sc = new VistaMensaje(); 
		//sc.updateString("Esto es un mensaje muy laaaaaargo para probaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaar");
		String text = new String();
		for(int i=0; i!=100; i++) {
			text += i + "Mensaje de prueba para ver que todo va como la seda\n";
		}
		sc.updateString(text);
		c.add(sc);
		ventana.setVisible(true);
		ventana.setSize(600, 400);
		return;
	}
}
