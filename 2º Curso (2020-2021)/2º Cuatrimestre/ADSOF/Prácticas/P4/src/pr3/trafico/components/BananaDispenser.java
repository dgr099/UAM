package pr3.trafico.components;
/**
 * Clase que contiene los datos del componente BananaDispenser
 *
 * @version 1.0 26 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class BananaDispenser extends Component{
	
	/**
	 * Constructor de la clase
	 */
	public BananaDispenser() {
		super("BananaDispenser");
	}
	
	/**
	 * Método para obtener el número de turnos necesarios para reparar el componente
	 * @return número de turnos necesarios para la reparación
	 */
	@Override
	public int costRepair() {
		return 4;
	}

	/**
	 * Método para saber si el componente es fundamental para el movimiento (crítico)
	 * @return booleano que define si el componente es crítico
	 */
	@Override
	public boolean isCritical() {
		return false;
	}

	/**
	 * Método para saber si el componente puede atacar a otro vehículo
	 * @return booleano que define si puede o no atacar
	 */
	public boolean canAttack(){
		return !(this.isDamaged()); //si está dañado no puede atacar en caso contrario si puede
	}

}
