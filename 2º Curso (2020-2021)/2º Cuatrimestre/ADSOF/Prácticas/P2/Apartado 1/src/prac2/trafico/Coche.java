package prac2.trafico;

/**
 * Clase que contiene los datos de un coche (si es diesel más la información de
 * la clase vehículo de la que hereda) con métodos para obtener su número de
 * ruedas, su índice de contaminación y para imprimir su información
 *
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Coche extends Vehiculo {
	private boolean diesel; // Booleano que recoge si el coche es diesel o no

	/**
	 * Constructor de la clase coche, con el modelo, el anyo de compra y la
	 * mátricula (necesarios para el constructor del super, vehículo), y el booleano
	 * que definirá si es diesel
	 * 
	 * @param mod       modelo del coche
	 * @param a         anyo de compra del coche
	 * @param matricula matrícula del coche
	 * @param diesel    booleano para saber si es o no diesel
	 */
	public Coche(String mod, int a, String matricula, boolean diesel) {
		super(mod, a, matricula);
		this.diesel = diesel;
	}

	/**
	 * Método para obtener el número de ruedas del coche
	 * 
	 * @return el número de ruedas del coche
	 */
	public int numeroRuedas() {
		return 4;
	}

	/**
	 * Método para imprimir la clase coche (si se trata de un coche diesesl junto
	 * con los datos de la clase de la que hereda)
	 * 
	 * @return String descriptivo del coche
	 */
	public String toString() {
		return "Coche " + (this.diesel ? "diesel" : "gasolina") + ", " + super.toString();
	}

	/**
	 * Método para conocer el índice de contaminación del coche
	 * 
	 * @return el índice de contaminación del coche
	 */
	public IndiceContaminacion getIndiceContaminacion() {
		if (this.diesel){
			return IndiceContaminacion.C;
		}
		return super.getIndiceContaminacion();
	}

	/**
	 * Método para obtener el booleano que define si la coche es diesel
	 * 
	 * @return true si es diesel, false en el caso contrario
	 */
	public boolean getDiesel() {
		return this.diesel;
	}
}
