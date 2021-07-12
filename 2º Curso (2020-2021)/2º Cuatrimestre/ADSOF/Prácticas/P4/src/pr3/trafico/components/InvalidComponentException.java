package pr3.trafico.components;
/**
 * Clase para la excepción cuando un componente no es válido
 *
 * @version 1.0 15 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class InvalidComponentException extends Exception {
	private static final long serialVersionUID = -6951294429811887586L;
	
	/**
	 * Constructor de la excepción
	 * @param msg mensaje mostrado al haber excepcion de componente
	 */
	public InvalidComponentException(String msg) {
		super(msg);
	}
}
