package pr3.trafico.vehiculos;

import java.util.List;

import pr3.trafico.components.IComponent;
import pr3.trafico.components.InvalidComponentException;
/**
 * Interfaz con los métodos a establecer en los vehículos
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public interface IVehicle {
	public double getActualPosition(); //método para obtener la posición del vehículo
	public void setActualPosition(double newPosition); //método para establecer la posición del vehículo
	public boolean canMove(); //método para saber si el vehículo se puede mover
	public void setCanMove(boolean newMovement); //método para establecer si se puede mover el vehículo
	public double getMaxSpeed(); //método para obtener la velocidad máxima del vehículo
	public String getName(); //método para obtener el nombre del vehículo
	//Para el apartado 3
	public void addComponent(IComponent c) throws InvalidComponentException; //método para añadir un componente a un vehículo
	public List<IComponent> getComponents(); //método para obtener la lista de componentes de un vehículo
}