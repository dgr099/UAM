package pr3.trafico.powerup;

import pr3.trafico.vehiculos.IVehicle;

/**
 * Interfaz a implementar el los powerUps
 *
 * @version 1.0 21 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public interface IPowerUp {
	public void applyPowerUp(IVehicle v); //método para aplicar el powerUp en el IVehicle
	public String namePowerUp(); //nombre del powerUp
}