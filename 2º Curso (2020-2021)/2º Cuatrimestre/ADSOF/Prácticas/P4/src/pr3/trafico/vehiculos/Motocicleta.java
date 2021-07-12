package pr3.trafico.vehiculos;

import java.sql.Date;
import java.util.Calendar;

import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.components.IComponent;
import pr3.trafico.components.InvalidComponentException;
import pr3.trafico.conductores.Propietario;

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
	 * Constructor de la clase
	 * @param maxSpeed máximo de velocidad de la motocicleta
	 */
	public Motocicleta(double maxSpeed) {
		super(maxSpeed, "Motorcycle");
	}
    
    /**
	 * @param mod modelo
	 * @param a anyo de compra
	 * @param matricula matricula de la motocicleta
	 * @param electrica si es electrica
	 * @param p propietario
	 */
	public Motocicleta(String mod, int a, String matricula, boolean electrica, Propietario p) {
		super(mod, a, matricula, p);
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
    /*public String toString() {
        return "Motocicleta" + (this.electrica ? " eléctrica" : "") + ", " + super.toString();
    }*/


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
    
    public boolean vVehiculo(TipoLicencia L){
        return (L == TipoLicencia.A);
    }

    /**
	 * Metodo para obtener el estado de caducidad de la ITV concretamente en una motocicleta (override)
     * 
	 * @return booleano, que será false si no caducó aún, true en caso contrario
	 */
	@Override
	public boolean cadITV() {
		Calendar fechaAct = Calendar.getInstance(); 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
    	//long msYear = 1000 * 60 * 60 * 24 * 365; /*ms de un año*/
		long msYear = 31536000000L; 
    	if(añosDif < 4) { //si no han pasado los 4 años no tiene que tiene que pasar itv
    		return false;
    	}
    	/*si ya han pasado los 4 años y no tiene ninguna ITV*/
   		if(this.getLastITV()==null) {
   			return true;
   		}
   		/*si hay última ITV, calculas la diferencia de tiempo entre la fecha act y la última inspeccion*/
    	long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime(); 
    	double difa = (double)((double)dif * (long)1/msYear); //dif en años
    	if(añosDif<10) { /*si han pasado 4 o + años pero no 10*/
    		if(difa > 2) { /*si han pasado más de dos años de la última inspección*/
    			return true;
    		}
    		return false;
    	}
    	/*si han pasado 10 o + años*/
    	if(difa >1) { /*si ha pasado +1 año de la última inspección*/
    		return true;
    	}
    	return false;
	}
    /**
	 * Método para conocer la fecha de la siguiente itv
	 * @return fecha de la siguiente itv
	 */
	public Date nextITV() {
		Calendar fechaAct = Calendar.getInstance(); 
		long msYear = 31536000000L; 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
		Calendar n = Calendar.getInstance();//el date de retorno
		if(añosDif <4) {
			n.set(n.get(Calendar.YEAR) + añosDif, n.get(Calendar.MONTH), n.get(Calendar.DAY_OF_MONTH), n.get(Calendar.HOUR), n.get(Calendar.MINUTE));
			return (Date) n.getTime();
		}
		if(this.getLastITV()==null) { /*si aun no hizo ninguna itv y ya paso el tiempo*/
			return null;
		}
		long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime(); //diferencia entre hoy y su ultima itv
		if(añosDif<10) { /*si tiene entre 2 y 10 años de antiguedad (sin incluir), se hace cada dos años*/
			return new Date(fechaAct.getTime().getTime() + (2 * msYear) - dif);
		}
		return new Date(fechaAct.getTime().getTime() + (1 * msYear) - dif);
	}

	/**
	 * Método para actualizar la posición de la motocicleta
	 */
	@Override
	public void updatePosition() {
		if(!this.canMove()) {
			return;
		}
		this.setActualPosition(this.getActualPosition() + this.getMaxSpeed());
	}
	/**
	 * Método para comprobar validez de un componente  para la clase
	 * @param c componente del que se quiere saber si es válido para la clase
	 * @return true si es válido, false en caso contrario
	 */
	public boolean comprobarValidez(IComponent c) throws InvalidComponentException {
		if(c.getName().equals("Engine") || c.getName().equals("Wheels")) {
			return true;
		}
		throw new InvalidComponentException("Component " + c.getName() + " is not valid for Vehicle " + this.getName());
	}
}
