package pr3.trafico.carnet;

import pr3.trafico.conductores.Persona;
import pr3.trafico.vehiculos.*;
/**
 * Enumeración que contiene los tipos de licencia de los carnets
 *
 * @version 1.0 2 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public enum TipoLicencia {
	A, B, C1; //diferentes tipos de licencia
	/**
	 * Método para conocer si una persona puede tener esa licencia
	 * 
	 * @param p persona a la que se quiere comprobar si puede obtener la licencia
	 * @param L licencia a comprobar para la persona
	 */
	public static boolean validoPersona(Persona p, TipoLicencia L) {
		if(p==null || L ==null){
			return false;
		}
		if(p.getEdad()>=18 && (L==A || L==B)) {
			return true;
		}
		if(p.getEdad()>=23 && L==C1) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método para conocer el si un tipo de licencia es válido para un determinado vehículo
	 * 
	 * @param anyo anyo de compra del objeto del que se desea conocer el índice de
	 *             contaminación
	 */
	public static boolean validoVehiculo(Vehiculo v, TipoLicencia L) {
		if(v == null || L == null){
			return false;
		}
		return v.vVehiculo(L); //llama a la funcion de válido vehículo del propio vehículo para esa licencia
	}

}
