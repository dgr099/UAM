package ui.control.registerAndLogin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import sistema.Sistema;
import ui.view.Ventana;
import ui.view.VistaPrincipal;
import ui.view.VistaPrincipal_North;
import ui.view.VistaPrincipal_south;
import ui.view.loginAndRegister.Login;
public class ControlLogin implements ActionListener{
	private Login vista=null;
	private VistaPrincipal_south vs;
	private VistaPrincipal_North vn;
	private Ventana v;
	private VistaPrincipal vp;
	public ControlLogin(Ventana v){
		if(v==null) {
			return;
		}
		this.vista = v.getLogin();
		this.vs = v.getVistaPrincipal().getSouth();
		this.vn = v.getVistaPrincipal().getNorth();
		this.vp = v.getVistaPrincipal();
		this.v = v;
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
		if(Sistema.getInstancia().login(nombre, contr)==false) { //si no ha podido hacer el login
			JOptionPane.showMessageDialog(vista, "Usuario o contraseña incorrectos.", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		else {
			this.vs.mostrarPanel("iniciado");
			v.mostrarPanel("VistaPrincipal");
			vs.getUser().setText(nombre);
			if(Sistema.getInstancia().getUsuarioEnUso().getNombre().equals(Sistema.getInstancia().getAdmin().getNombre())) {
				vn.mostrarPanel("admin");
				vp.mostrarStats();
				v.getVistaPrincipal().getStatListaEventos().update(); /*update la páina de stats del admin*/
				v.getPaginaAdmin().update(); /*actualizamos la pagina de admin*/
			}
			else {
				v.getPaginaUsuario().update(); /*actualizamos para que se vean los valores del usuario*/
				v.getPaginaReservas().getListaReservas().actualizasValores();
			}
		}
	}

}
