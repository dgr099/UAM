package ui.control.usuario;

import abonos.AbonoUsuario;
import entrada.Entrada;
import ui.view.Ventana;
import ui.view.usuario.InfoAbono;
import ui.view.usuario.InfoEntrada;

/**
 * Clase que actua como modelo y controlador para el usuario
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlUsuario {
	private Entrada Eseleccionada = null;
	private AbonoUsuario Aseleccionado = null;
	private InfoEntrada vista1 = null;
	private InfoAbono vista2 = null;
	public ControlUsuario(Ventana v) {
		this.vista1 = v.getInfoEntrada();
		this.vista2 = v.getInfoAbono();
	}
	
	/**
	 * Método para obtener la entrada seleccionada
	 * @return entrada seleccionada
	 */
	public Entrada getEseleccionada() {
		return Eseleccionada;
	}
	/**
	 * Método para establecer la entrada seleccionada
	 * @param eseleccionada entrada a establecer como seleccionada
	 */
	public void setEseleccionada(Entrada eseleccionada) {
		Eseleccionada = eseleccionada;
		vista1.update();
	}
	/**
	 * Clase para obtener el abono seleccionado
	 * @return Abono seleccionado por el usuario
	 */
	public AbonoUsuario getAseleccionado() {
		return Aseleccionado;
	}
	/**
	 * Método para establecer el abono seleccionado por el usuario
	 * @param aseleccionado Abono a establecer como seleccionado
	 */
	public void setAseleccionado(AbonoUsuario aseleccionado) {
		Aseleccionado = aseleccionado;
		vista2.update();
	}
}
