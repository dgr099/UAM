package sistema;

import ui.control.Control;
import ui.view.Ventana;

/**
 * Clase con el main para ejecutar la aplicación
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Main {
	public static void main(String... args) {
		Sistema sis = Sistema.getInstancia(); /*inicias el sistema*/
		sis.loadSistema(); /*recuperas lo guardado*/
		Ventana v = new Ventana();
		Control c = new Control(v);
		v.setControlador(c);
		v.setVisible(true);
	}

}
