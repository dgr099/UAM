package pr3.trafico.vehiculos;

import java.util.Date;
import java.util.Calendar;

import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.conductores.Propietario;

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
	 * @param mod
	 * @param a
	 * @param matricula
	 * @param p
	 * @param numEjes
	 */
	public Camion(String mod, int a, String matricula, int numEjes, Propietario p) {
		super(mod, a, matricula, p);
		this.numEjes = numEjes;
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
    public boolean vVehiculo(TipoLicencia L){
        if(L == TipoLicencia.C1){
            return true;
        }
        return false;
    }





	@Override
	public boolean cadITV() {
		Calendar fechaAct = Calendar.getInstance(); 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
    	//long msYear = 1000 * 60 * 60 * 24 * 365; /*ms de un año*/
		long msYear = 31536000000L; 
		if(añosDif<2) {
			return false;
		}
		/*si han pasado dos años y aún no tiene ninguna ITV*/
		if(this.getLastITV()==null) {
			return true;
		}
		/*si tiene alguna inspeccion calculamos la dif con la fecha actual*/
		long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime();
		double difa = (double)((double)dif * (long)1/msYear); //dif en años
		if(añosDif<6) {
			if(difa > 2) {
				return true;
			}
			return false;
		}
		if(añosDif<10) {
			if(difa > 1) {
				return true;
			}
			return false;
		}
		/*cualquier otro caso es que ya tiene 10 o + años*/
		if((difa * 12/1) > 6) {
			return true;	/*si han pasado más de 6 meses de la última revisión*/
		}
		return false;
	}
	public Date nextITV() {
		Calendar fechaAct = Calendar.getInstance(); 
		long msYear = 31536000000L; 
    	int añosDif = fechaAct.get(Calendar.YEAR) - this.getAnyoCompra();
		Calendar n = Calendar.getInstance();//el date de retorno
		if(añosDif <2) {
			n.set(this.getAnyoCompra() + 2, n.get(Calendar.MONTH), n.get(Calendar.DAY_OF_MONTH), n.get(Calendar.HOUR), n.get(Calendar.MINUTE));
			return (Date) n.getTime();
		}
		if(this.getLastITV()==null) { /*si aun no hizo ninguna itv y ya paso el tiempo*/
			return null;
		}
		long dif=fechaAct.getTime().getTime() - this.getLastITV().getFecha().getTime().getTime(); //diferencia entre hoy y su ultima itv
		if(añosDif<6) { /*si tiene entre 2 y 6 años de antiguedad (sin incluir), se hace cada dos años*/
			return new Date(fechaAct.getTime().getTime() + (2 * msYear) - dif);
		}
		if(añosDif<10) { /*entre 6 y 10 es cada año*/
			return new Date(fechaAct.getTime().getTime() + (1 * msYear) - dif);
		} /*más antiguos es cada 6 meses*/
		return new Date(fechaAct.getTime().getTime() + (long)((double)1/2 * (double)msYear)-dif);
	}
}
