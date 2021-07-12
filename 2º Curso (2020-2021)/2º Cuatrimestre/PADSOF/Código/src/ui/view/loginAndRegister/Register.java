package ui.view.loginAndRegister;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Image;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

/*jpanell con el login*/
public class Register extends JScrollPane{

	/**
	 * 
	 */
	private static final long serialVersionUID = 3027277943433894178L;
	JTextField utxt = new JTextField(12); //nombre del usuario (u texto)
	JPasswordField ctxt = new JPasswordField(12); //contraseña del usuario (c texto)
	JPasswordField c2txt = new JPasswordField(12); //contraseña del usuario método de confirmación (c2 texto)
	JButton reg = new JButton("Registrarse");
	JButton back = new JButton();

	public String getNombreUsuario() {
		return this.utxt.getText();
	}
	
	public String getContraseña() {
		return new String(this.ctxt.getPassword());
	}
	
	public String getConfirmaciónContraseña() {
		return new String(this.c2txt.getPassword());
	}
	
	public void setControlador(ActionListener reg, ActionListener back) {
		this.reg.addActionListener(reg);
		this.back.addActionListener(back);
	}
	
	public Register(){ /*constructor*/
		JPanel main = new JPanel();
		SpringLayout sl = new SpringLayout();
		JLabel titulo = new JLabel("Eventual");
		titulo.setFont(new Font("Serif", Font.PLAIN, 35)); //ponemos el nombre de la app en grande
		JLabel user = new JLabel("Usuario:");
		
		JLabel contraseñas[] = new JLabel[2];
		contraseñas[0] = new JLabel("Contraseña:");
		contraseñas[1] = new JLabel("Confirmar Contraseña:");
		reg.setFont(new Font("Dialog", Font.PLAIN, 10));
		
		/*ponemos el back bien bonico*/
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		
		main.setLayout(sl); //pones el layout
		/*ponemos el nombre de la app*/
		main.add(titulo);
		/*ponemos en el panel donde poner el nombre de usuario*/
		main.add(user);
		main.add(utxt);
		/*ponemos en el panel donde poner la contraseña*/
		main.add(ctxt);
		main.add(contraseñas[0]);
		main.add(c2txt);
		main.add(contraseñas[1]);
		/*ponemos el botón de registro*/
		main.add(reg);
		/*ponemos el botón de volver a atras*/
		main.add(back);
		/*Alineas el Título*/
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, titulo, 0, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.SOUTH, titulo, -25, SpringLayout.NORTH, user);
		/*Alineas la primera pareja de valores (el label de user y donde escribir usuario)*/
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, user, -35, SpringLayout.VERTICAL_CENTER, main);
		sl.putConstraint(SpringLayout.NORTH, utxt, 5, SpringLayout.SOUTH, user);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, utxt, 0, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, user, 0, SpringLayout.HORIZONTAL_CENTER, main);
		/*ponemos el campo de contraseña*/
		sl.putConstraint(SpringLayout.NORTH, contraseñas[0], 10, SpringLayout.SOUTH, utxt);
		sl.putConstraint(SpringLayout.NORTH, ctxt, 5, SpringLayout.SOUTH, contraseñas[0]);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, ctxt, 0, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, contraseñas[0], 0, SpringLayout.HORIZONTAL_CENTER, main);
		/*ponemos el campo de confirmar contraseña*/
		sl.putConstraint(SpringLayout.NORTH, contraseñas[1], 10, SpringLayout.SOUTH, ctxt);
		sl.putConstraint(SpringLayout.NORTH, c2txt, 5, SpringLayout.SOUTH, contraseñas[1]);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, c2txt, 0, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, contraseñas[1], 0, SpringLayout.HORIZONTAL_CENTER, main);
		
		/*Alienas el back*/
		sl.putConstraint(SpringLayout.EAST, back, -25, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.VERTICAL_CENTER, back, 0, SpringLayout.VERTICAL_CENTER, reg);
		/*ponemos el botón de login*/
		sl.putConstraint(SpringLayout.WEST, reg, -10, SpringLayout.EAST, back);
		sl.putConstraint(SpringLayout.NORTH, reg, 15, SpringLayout.SOUTH, c2txt);
		main.setVisible(true);
		this.add(main);
		main.setPreferredSize(new Dimension(160, 300));
		this.setViewportView(main);
	}
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_reg");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new Register());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		return;
	}
}
