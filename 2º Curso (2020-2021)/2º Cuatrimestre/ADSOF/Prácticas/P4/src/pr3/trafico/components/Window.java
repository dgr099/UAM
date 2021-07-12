package pr3.trafico.components;
/**
 * Clase que contiene los datos del componente window
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Window extends Component{

	/**
	 * Constructor del componente
	 */
	public Window() {
		super("Window");
	}
	
	/**
	 * Método para obtener el número de turnos necesarios para reparar el componente
	 * @return número de turnos necesarios para la reparación
	 */
	@Override
	public int costRepair() {
		return 2;
	}
	
	/**
	 * Método para saber si el componente es fundamental para el movimiento (crítico)
	 * @return booleano que define si el componente es crítico
	 */
	@Override
	public boolean isCritical() {
		return false;
	}

}
