package ui.control.admin;

import javax.swing.JTextField;

/**
 * Clase empleada para poder tener un mapa que una a un jtext con la zona para 
 * facilitar la tarea en el precio por zonas
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class JTextAux implements Comparable<JTextAux>{
	private int i=0;
	private static int ni=0;
	private JTextField text;
	/**
	 * Contructor de la clase, obtiene un jtextfield, le asigna una i estática y por ende distinta para todos
	 * para que de esa forma sea posible diferenciarlos en el comparable
	 * @param text JTextField a incluir en la clase
	 */
	public JTextAux(JTextField text) {
		this.text = text;
		i = ++ni;
	}
	/**
	 * método para obtener su identificador (para el compare to)
	 * @return
	 */
	public int getI() {
		return this.i;
	}
	/**
	 * Compare to necesario para el mapa
	 */
	@Override
	public int compareTo(JTextAux arg0) {
		return this.i - arg0.getI();
	}
	
	/**
	 * Método para obtener el JTextField incluido en la clase
	 * @return
	 */
	public JTextField getTextField() {
		return this.text;
	}
}
