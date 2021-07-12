package forms;

/**
 * Clase para trabajar con la respuesta de la pregunta
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Respuesta<T extends Comparable<T>> implements Comparable<Respuesta<T>>{
	T valor;

	/**
	 * Establecer el valor de la respuesta
	 * @param o Valor de la respuesta en el que se hace casting
	 */
	@SuppressWarnings("unchecked")
	public void setValor(Object o) {
		this.valor = (T)o;
		return;
	}

	/**
	 * Metodo toString
	 */
	@Override
	public String toString() {
		return valor.toString();
	}

	/**
	 * Metodo para comparar respuestas
	 * @param arg0 respuesta con la que comparar
	 */
	@Override
	public int compareTo(Respuesta<T> arg0) {
		return this.valor.compareTo(arg0.getValor());
	}

	/**
	 * Obtener el valor de la respuesta
	 * @return valor
	 */
	public T getValor() {
		return this.valor;
	}

}
