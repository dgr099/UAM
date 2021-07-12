package prac2.trafico;

/**
 * Clase que contiene los datos de un camión (el número de ejes más la
 * información de la clase vehículo ) con métodos para obtener su número de
 * ruedas, su índice de contaminación y para imprimir su información
 *
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Camion extends Vehiculo {
    private int numEjes; // entero que guuarda el número de ejes del camión

    /**
     * Constructor de la clase camión, con el modelo, el anyo de compra y la
     * mátricula (necesarios para el constructor del super, vehículo), y el entero
     * que definirá el número de ejes del camión
     * 
     * @param mod       modelo del camión
     * @param a         anyo de compra del camión
     * @param matricula matrícula del camión
     * @param ejes      entero que guarda los ejes del camión
     */
    public Camion(String mod, int a, String matricula, int ejes) {
        super(mod, a, matricula);
        this.numEjes = ejes;
    }

    /**
     * Método para obtener el número de ruedas del camión
     * 
     * @return el número de ruedas del camión
     */
    public int numeroRuedas() {
        return 2 * this.numEjes;
    }

    /**
     * Método para conocer el índice de contaminación del camión
     * 
     * @return el índice de contaminación del camión
     */
    public IndiceContaminacion getIndiceContaminacion() {
        if (this.numEjes > 2) {
            return IndiceContaminacion.C;
        } else {
            return super.getIndiceContaminacion();
        }
    }

    /**
     * Método para imprimir la clase camión (el número de ejes junto con los datos
     * de la clase de la que hereda)
     * 
     * @return String descriprivo del camión
     */
    public String toString() {
        return "Camión de " + this.numEjes + " ejes, " + super.toString();
    }

    /**
     * Método para obtener el número de ejes del camión
     * 
     * @return el número de ejes del camión
     */
    public int getNumEjes() {
        return this.numEjes;
    }

}
