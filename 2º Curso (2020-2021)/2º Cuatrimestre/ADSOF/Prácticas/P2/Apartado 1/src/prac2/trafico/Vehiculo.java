package prac2.trafico;

/**
 * Clase que contiene los datos de un vehiculo con métodos para obtener su
 * número de ruedas (método abstracto), su índice de contaminación y para
 * imprimir su información
 *
 * @version 1.0 25 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class Vehiculo {
	private String modelo; // String que guarda el nombre del modelo del vehículo
	private int anyoCompra; // Entero que contiene el año en el que fue adquirido el vehículo
	private String matricula; // String que contiene la mátricula del vehículo

	/**
	 * Constructor de la clase vehículo, con el modelo, el anyo de compra y la
	 * mátricula
	 * 
	 * @param mod       modelo del vehículo
	 * @param a         anyo de compra del vehículo
	 * @param matricula matrícula del vehículp
	 */
	public Vehiculo(String mod, int a, String matricula) {
		this.modelo = mod;
		this.anyoCompra = a;
		this.matricula = matricula;
	}

	/**
	 * Método para imprimir la clase vehículo (modelo, matricula, año, ruedas e
	 * índice de contaminación)
	 * 
	 * @return String descriprivo del vehículo
	 */
	public String toString() {
		return "modelo " + this.modelo + ", " + "matrícula: " + this.getMatricula() + ", fecha compra "
				+ this.anyoCompra + ", con " + this.numeroRuedas() + " ruedas, índice:" + this.getIndiceContaminacion();
	}

	/**
	 * Método para conocer la matrícula del vehículo
	 * 
	 * @return el string con la matrícula del vehículo
	 */
	public String getMatricula() {
		return this.matricula;
	}

	/**
	 * Método abstracto para obtener el número de ruedas del vehículo
	 * 
	 * @return el número de ruedas del vehículo
	 */
	public abstract int numeroRuedas();

	/**
	 * Método para conocer el índice de contaminación del vehículo
	 * 
	 * @return el índice de contaminación del vehículo
	 */
	public IndiceContaminacion getIndiceContaminacion() {
		return IndiceContaminacion.getIndiceContaminacion(this.anyoCompra);
	}
}
