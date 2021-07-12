package pr3.trafico.components;

import pr3.trafico.vehiculos.IVehicle;
/**
 * Interfaz a implementar en los componentes
 *
 * @version 1.0 14 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public interface IComponent {
	public boolean isDamaged(); //método para saber si está dañado
	public void setDamaged(boolean damage); //método para establecer el daño del vehículo
	public String getName(); //método para obtener el nombre del vehículo
	public int costRepair(); //método para conocer el costo de reparación
	public IVehicle getVehicle(); //método para conocer el IVehicle asociado al componente
	public void setVehicle(IVehicle v); //método para establecer el IVehicle asociado al componente
	public boolean isCritical(); //método para saber si el componente es crítico (fundamental para el movimiento)
	public void repair(); //método para reparar el componente
	public boolean canAttack(); //método para conocer si el componente puede atacar a otros vehículos
}
