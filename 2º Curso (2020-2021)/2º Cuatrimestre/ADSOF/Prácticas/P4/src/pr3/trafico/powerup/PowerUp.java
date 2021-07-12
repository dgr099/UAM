package pr3.trafico.powerup;

import pr3.trafico.Race.Race;
/**
 * Clase que contiene los datos de powerUp
 *
 * @version 1.0 21 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class PowerUp implements IPowerUp {
	private String name; //nombre del powerUp
	protected Race race; //carrera en la que se aplica el powerUp
	
	/**
	 * Constructor de la clase
	 * @param name nombre del powerUp
	 * @param race carrera en la que se crea el powerUp
	 */
	public PowerUp(String name, Race race) {
		this.name = name;
		this.race = race;
	}
	
	
	/**
	 * Método para obtener el nombre del powerUp
	 * @return nombre del PowerUp
	 */
	@Override
	public String namePowerUp() {
		return this.name;
	}

}
