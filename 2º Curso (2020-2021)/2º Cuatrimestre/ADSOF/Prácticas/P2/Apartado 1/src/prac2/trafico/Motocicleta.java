package prac2.trafico;

/**
 * Clase que contiene los datos de una motocicleta (si es eléctrica más la
 * información de la clase motocicleta ) con métodos para obtener su número de
 * ruedas, su índice de contaminación y para imprimir su información
 *
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Motocicleta extends Vehiculo {
    private boolean electrica; // Booleano que contiene si la motocicleta es o no eléctrica

    /**
     * Constructor de la clase motocicleta, con el modelo, el anyo de compra y la
     * mátricula (necesarios para el constructor del super, vehículo), y el booleano
     * que definirá si es eléctrica
     * 
     * @param mod       modelo de la motocicleta
     * @param a         anyo de compra de la motocicleta
     * @param matricula matrícula de la motocicleta
     * @param electrica booleano para saber si es o no electrica
     */
    public Motocicleta(String mod, int a, String matricula, boolean electrica) {
        super(mod, a, matricula);
        this.electrica = electrica;
    }

    /**
     * Método para obtener el número de ruedas de la motocicleta
     * 
     * @return el número de ruedas de la motocicleta
     */
    public int numeroRuedas() {
        return 2;
    }

    /**
     * Método para imprimir la clase motocicleta (si es electrica junto con los
     * datos de la clase de la que hereda)
     * 
     * @return String descriprivo de la motocicleta
     */
    public String toString() {
        return "Motocicleta" + (this.electrica ? " eléctrica" : "") + ", " + super.toString();
    }

    /**
     * Método para conocer el índice de contaminación de la motocicleta
     * 
     * @return el índice de contaminación de la moto
     */
    public IndiceContaminacion getIndiceContaminacion() {
        if (this.electrica) {
            return IndiceContaminacion.A;
        } else {
            return super.getIndiceContaminacion();
        }
    }

    /**
     * Método para obtener el booleano que define si la motocicleta es eléctrica
     * 
     * @return true si es eléctrica, false en el caso contrario
     */
    public boolean getElectrica() {
        return this.electrica;
    }
}
