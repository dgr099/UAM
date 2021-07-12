package ui.control.registerAndLogin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal_south;
import ui.view.loginAndRegister.Register;
public class ControlRegister implements ActionListener{
	private Register vista=null;
	private Ventana v;
	private VistaPrincipal_south vs;
	public ControlRegister(Ventana v){
		if(v==null) {
			return;
		}
		this.v = v;
		this.vs = v.getVistaPrincipal().getSouth();
		this.vista = v.getRegister();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String nombre = vista.getNombreUsuario();
		if(nombre==null || nombre.equals("")) {
			JOptionPane.showMessageDialog(vista, "Debe introducir un nombre.", "User Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		String contr = vista.getContraseña();
		if(contr==null || contr.equals("")) {
			JOptionPane.showMessageDialog(vista, "Debe introducir una contraseña.", "Password Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		String contr2 = vista.getConfirmaciónContraseña();
		if(contr2==null || contr2.equals("")) {
			JOptionPane.showMessageDialog(vista, "Debe introducir la confirmación de contraseña.", "Password Confirmation Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		if(!contr.equals(contr2)) {
			JOptionPane.showMessageDialog(vista, "La contraseña y la confirmación no coinciden.", "Password Validation Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		//DEBUG
		//System.out.println(nombre + " " +contr);
		if(Sistema.getInstancia().registro(nombre, contr)==false) { //si no ha podido hacer el login
			JOptionPane.showMessageDialog(vista, "Error en el registro, usuario ya existente", "Sistem Error", JOptionPane.ERROR_MESSAGE);
		}
		else {
			v.mostrarPanel("VistaPrincipal");
			vs.mostrarPanel("iniciado");
			vs.getUser().setText(nombre);
		}
	}

}
