package pr3.trafico.components;
/**
 * Clase que contiene los datos del componente BananaDispenser
 *
 * @version 1.0 15 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Engine extends Component{

	/**
	 * Constructor de la clase
	 */
	public Engine() {
		super("Engine");
	}

	/**
	 * Método para obtener el número de turnos necesarios para reparar el componente
	 * @return número de turnos necesarios para la reparación
	 */
	@Override
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

