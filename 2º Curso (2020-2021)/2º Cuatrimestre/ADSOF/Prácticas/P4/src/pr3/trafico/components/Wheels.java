package pr3.trafico.components;
/**
 * Clase que contiene los datos del componente wheels
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Wheels extends Component{
	/**
	 * Constructor de la clase
	 */
	public Wheels() {
		super("Wheels");
	}
	
	/**
	 * Método para obtener el número de turnos necesarios para reparar el componente
	 * @return número de turnos necesarios para la reparación
	 */
	public int costRepair() {
		return 3;
	}
	
	/**
	 * Método para saber si el componente es fundamental para el movimiento (crítico)
	 * @return booleano que define si el componente es crítico
	 */
	@Override
	public boolean isCritical() {
		return true;
	}
}
