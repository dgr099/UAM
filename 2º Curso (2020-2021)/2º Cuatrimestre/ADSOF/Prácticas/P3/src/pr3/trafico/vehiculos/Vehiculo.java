package pr3.trafico.vehiculos;

import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.conductores.*;
import pr3.trafico.itv.ITV;

import java.util.List;
import java.util.Date;
import java.util.ArrayList;
import java.util.Calendar;

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
	private Propietario propietario = null;
	private Persona conductor = null;
	private List<ITV> ITVs = new ArrayList<ITV>(); 

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
	
	public String getModelo() {
		return modelo;
	}

	public int getAnyoCompra() {
		return anyoCompra;
	}

	public List<ITV> getITVs() {
		return ITVs;
	}
	public ITV getLastITV() {
		/*retorna la última ITV*/
		if(this.ITVs.size()==0) { //si no tiene ninguna itv
			return null;
		}
		return this.ITVs.get(this.ITVs.size()-1);
	}

	public void setMatricula(String matricula) {
		this.matricula = matricula;
	}

	public Persona getConductor() {
		return this.conductor;
	}
	
	public Propietario getPropietario() {
		return this.propietario;
	}
	
	public Vehiculo(String mod, int a, String matricula, Propietario p) {
		this.modelo = mod;
		this.anyoCompra = a;
		this.matricula = matricula;
		this.setPropietario(p);
	}

	/**
	 * Método para imprimir la clase vehículo (modelo, matricula, año, ruedas e
	 * índice de contaminación)
	 * 
	 * @return String descriprivo del vehículo
	 */
	public String toString() {
		return "modelo " + this.modelo + ", " + "matrícula: " + this.getMatricula() + ", fecha compra "
		+ this.anyoCompra + ", con " + this.numeroRuedas() + " ruedas, índice:" + this.getIndiceContaminacion() + " propietario: " + (this.propietario!=null ? (this.propietario.getNombre()) : "no registrado") + " conductor: " + (this.conductor!=null ? this.conductor.getNombre() : "no registrado");
	}
	
	public void addITV(ITV itv) {
		if(itv==null) {
			return;
		}
		if(this.getITVs().size()==0) { /*si no tiene itvs, comprueba con la fecha de matr*/
			if(this.anyoCompra>=itv.getFecha().get(Calendar.YEAR)) {
				return;
			}
			this.getITVs().add(itv);
			itv.getTaller().addVehiculo(this);
			return;
		}
		if(this.getLastITV().getFecha().compareTo(itv.getFecha())>0) { /*si queremos añadir una ITV que sucedio antes*/
			return;
		}
		/*si la itv no es nula y es posterior a la última, se añade a la lista de itvs*/
		this.getITVs().add(itv);
		itv.getTaller().addVehiculo(this);
		return;
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

	public void setPropietario(Propietario propietario) {
		if(propietario==null) {
			return;
		}
		this.propietario=propietario;
		propietario.addVehiculo(this);
		
	}

	public boolean setConductor(Persona conductor) {
		if(conductor==null){
			return false;
		}
		if (conductor.getEdad() < 18) {
			return false;
		} else {
			this.conductor = conductor;
			return true;
		}
	}
	public abstract boolean vVehiculo(TipoLicencia L);
	public abstract boolean cadITV();
	public abstract Date nextITV();
}
