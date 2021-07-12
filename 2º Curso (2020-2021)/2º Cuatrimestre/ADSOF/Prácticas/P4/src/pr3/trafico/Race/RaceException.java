package pr3.trafico.Race;
/**
 * Clase que contiene los datos de la excepcion de carrera
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class RaceException extends Exception {
	private static final long serialVersionUID = -7805421077723720800L;
	/**
	 * Constructor de la excepción
	 * @param msg mensaje a establecer en la excepción
	 */
	public RaceException(String msg) {
		super(msg);
	}
}
