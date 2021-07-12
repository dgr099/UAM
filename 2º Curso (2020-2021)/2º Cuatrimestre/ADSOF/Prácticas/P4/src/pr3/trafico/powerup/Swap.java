package pr3.trafico.powerup;

import pr3.trafico.Race.Race;
import pr3.trafico.vehiculos.IVehicle;
import pr3.trafico.vehiculos.Vehiculo;
/**
 * Clase que contiene los datos del powerUp Swap
 *
 * @version 1.0 21 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Swap extends PowerUp {
	
	/**
	 * Constructor del powerUp
	 * @param name nombre del powerUp
	 * @param race Carrera en la que se crea el powerUp
	 */
	public Swap(String name, Race race) {
		super(name, race);
	}

	/**
	 * Método para aplicar el powerUp en el IVehicle pasado
	 * @param v vehículo en el que aplicar el powerUp
	 */
	@Override
	public void applyPowerUp(IVehicle v) {
		
		Vehiculo delante = this.race.getDelante(v);
	
		if(delante != null) {
			double posicionV = v.getActualPosition();
			double posicionDelante = delante.getActualPosition();
			v.setActualPosition(posicionDelante);
			delante.setActualPosition(posicionV);
			System.out.println(v.getName() + " swapped with " + delante.getName());
		} else {
			System.out.println("First cannot swap.");
		}
	}

}
