package forms;

import java.util.Map;

/**
 * Clase abstracta que sirve como interfaz para el Form de verdad y el ProtectedForm correspondiente
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class AbstractForm {
	public abstract Map<String, Respuesta<?>> exec();
	public abstract Form add(String question, Field<?> campo);
	
}
