package pr3.trafico.powerup;

import pr3.trafico.Race.Race;
import pr3.trafico.components.IComponent;
import pr3.trafico.vehiculos.IVehicle;
/**
 * Clase que contiene los datos del powerUp AutoHealthAll
 *
 * @version 1.0 21 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class AutoHealthAll extends PowerUp {

	/**
	 * Constructor del powerUp
	 * @param name nombre del powerUp
	 * @param race Carrera en la que se crea el powerUp
	 */
	public AutoHealthAll(String name, Race race) {
		super(name, race);
	}

	/**
	 * Método para aplicar el powerUp en el IVehicle pasado
	 * @param v vehículo en el que aplicar el powerUp
	 */
	@Override
	public void applyPowerUp(IVehicle v) {
		for(IComponent ic : v.getComponents()) {
			while(ic.isDamaged()) {
				ic.repair(); //mientras esté dañado se va reparando
			}
		}
	}

}
