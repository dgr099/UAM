package pr3.trafico.powerup;

import pr3.trafico.Race.Race;
import pr3.trafico.vehiculos.IVehicle;
import pr3.trafico.vehiculos.Vehiculo;
/**
 * Clase que contiene los datos del powerUp AttackAll
 *
 * @version 1.0 21 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class AttackAll extends PowerUp {

	/** Constructor del powerUp
	 * @param name nombre del powerUp
	 * @param race carrera en la que se aplica el powerUp
	 */
	public AttackAll(String name, Race race) {
		super(name, race);
	}

	/**
	 * Método para aplicar el powerUp en el IVehicle pasado
	 * @param v vehículo en el que aplicar el powerUp
	 */
	@Override
	public void applyPowerUp(IVehicle v) {
		for(Vehiculo vehiculo : race.getParticipantes()) {
			if(vehiculo != v) {
				race.attack(v, vehiculo);
			}
		}
	}

}
