package pr3.trafico.vehiculos;

import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.components.IComponent;
import pr3.trafico.components.InvalidComponentException;
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
 * @version 1.3 25 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class Vehiculo implements IVehicle{
	private String modelo = null; // String que guarda el nombre del modelo del vehículo
	private int anyoCompra = 0; // Entero que contiene el año en el que fue adquirido el vehículo
	private String matricula = null; // String que contiene la mátricula del vehículo
	private Propietario propietario = null; // Propietario asignado al vehiculo
	private Persona conductor = null; // Conductor asignado al vehiculo
	private List<ITV> ITVs = new ArrayList<ITV>();
	/*nuevo*/
	private double posicion=0;
	private double maxSpeed=0;
	static private int num = 1;
	private boolean mov=true;
	private String name = new String();
	private List<IComponent> componentes = new ArrayList<IComponent>(); //lista de componentes del vehículo

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
	
	public Vehiculo(double maxSpeed, String name) {
		this.maxSpeed = maxSpeed;
		this.name=name + '(' + Vehiculo.num++ + ')';
	}
	
	/**
	 * Método para obtener el modelo del vehículo
	 * 
	 * @return el string con el modelo del vehículo
	 */
	public String getModelo() {
		return modelo;
	}
	
	/**
	 * Método para actualizar la posición de un vehículo
	 */
	public abstract void updatePosition();
	
	public void setActualPosition(double newPosition) {
		if(newPosition<0) { //no puede haber posiciones nehativas
			return;
		}
		this.posicion = newPosition;
	}
	
	public double getActualPosition(){
		return this.posicion;
	}
	
	public boolean canMove() {
		/*for(IComponent ic : this.componentes) {
			si tiene un componente crítico dañado no se mueve
			if(ic.isDamaged() && ic.isCritical()) {
				return false;
			}
		}
		return true;*/
		return this.mov;
	}
	
	public void setCanMove(boolean newMovement) {
		this.mov=newMovement;
	}
	public double getMaxSpeed() {
		return this.maxSpeed;
	}
	
	public String getName() {
		return this.name;
	}
	
	/**
	 * Método para obtener el anyo de compra del vehículo
	 * 
	 * @return anyo de compra del vehículo
	 */
	public int getAnyoCompra() {
		return anyoCompra;
	}

	/**
	 * Método para obtener la lista de ITVs del vehículo
	 * 
	 * @return lista con ITVs del vehículo
	 */
	public List<ITV> getITVs() {
		return ITVs;
	}

	/**
	 * Método para obtener la ultima ITV del vehículo
	 * 
	 * @return la ultima ITV del vehículo
	 */
	public ITV getLastITV() {
		/*retorna la última ITV*/
		if(this.ITVs.size()==0) { //si no tiene ninguna itv
			return null;
		}
		return this.ITVs.get(this.ITVs.size()-1);
	}

	/**
	 * Método para establecer la matricula del vehículo
	 * 
	 * @param matricula matricula a establecer al vehiculo
	 */
	public void setMatricula(String matricula) {
		this.matricula = matricula;
	}

	/**
	 * Método para obtener el conductor del vehículo
	 * 
	 * @return la persona que hace de conductor del vehículo
	 */
	public Persona getConductor() {
		return this.conductor;
	}
	
	/**
	 * Método para obtener el propietario del vehículo
	 * 
	 * @return la persona que hace de propietario del vehículo
	 */
	public Propietario getPropietario() {
		return this.propietario;
	}
	
	/**
	 * Constructor de la clase vehículo anyadiendo aparte el propietario
	 * 
	 * @param mod       modelo del vehículo
	 * @param a         anyo de compra del vehículo
	 * @param matricula matrícula del vehículo
	 * @param p 		propietario del vehiculo
	 */
	public Vehiculo(String mod, int a, String matricula, Propietario p) {
		this.modelo = mod;
		this.anyoCompra = a;
		this.matricula = matricula;
		this.setPropietario(p);
	}

	/**
	 * Método para conocer si un vehículo puede atacar
	 * @return booleano que define si puede o no atacar
	 */
	public boolean canAttack(){
		for(IComponent ic : this.getComponents()){
			if(ic.canAttack()==true){
				return true;
			}
		}
		return false;
	}
	/**
	 * Método para imprimir la clase vehículo (modelo, matricula, año, ruedas e
	 * índice de contaminación)
	 * 
	 * @return String descriprivo del vehículo
	 */
	/*public String toString() {
		return "modelo " + this.modelo + ", " + "matrícula: " + this.getMatricula() + ", fecha compra "
		+ this.anyoCompra + ", con " + this.numeroRuedas() + " ruedas, índice:" + this.getIndiceContaminacion() + " propietario: " + (this.propietario!=null ? (this.propietario.getNombre()) : "no registrado") + " conductor: " + (this.conductor!=null ? this.conductor.getNombre() : "no registrado");
	}*/
	
	public String toString() {
		return this.getName() + ". Speed " + this.maxSpeed + ". Actual position: " + this.posicion;
	}
	
	/**
	 * Método para obtener la distancia de un vehículo
	 * @param v vehículo del que se desea conocer la distancia
	 * @return distancia entre este vehículo y el pasado por argumento
	 */
	public double distanceTo(Vehiculo v) {
		if(v==null) {
			return -1;
		}
		return (v.getActualPosition() - this.getActualPosition());
		//return Math.abs(v.getActualPosition() - this.getActualPosition());
	}
	
	/**
	 * Método para establecer la ultima ITV a un vehiculo
	 * 
	 * @param itv ultima ITV a anyadir
	 * 
	 */
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

	/**
	 * Método para establecer un propietario a un vehiculo
	 * 
	 * @param propietario Propietario a establecer
	 */
	public void setPropietario(Propietario propietario) {
		if(propietario==null) {
			return;
		}
		this.propietario=propietario;
		propietario.addVehiculo(this);
		
	}

	/**
	 * Método para establecer un conductor a un vehiculo
	 * 
	 * @param conductor Propietario a establecer
	 * 
	 * @return true si es valido, false si no
	 */
	public boolean setConductor(Persona conductor) {
		if(conductor==null){
			return false;
		}
		if (conductor.getEdad() < 18) {
			return false;
		} else {
			if(conductor.getCarnet().carnetValido(this)==true) {
				this.conductor = conductor;
				return true;
			}
		}
		return false;
	}

	/**
	 * Método abstracto que se usa para hacer uso del metodo validoVehiculo() que hereda
	 * 
	 * @param L TipoLicencia para el vehiculo
	 * 
	 * @return abstract method 
	 */
	public abstract boolean vVehiculo(TipoLicencia L);
	/**
	 * Método abstracto para obtener la caducidad de cada vehiculo
	 * 
	 * @return abstract method
	 */
	public abstract boolean cadITV();
	/**
	 * Método abstracto para obtener la fecha de la siguiente ITV de cada vehiculo
	 * 
	 * @return abstract method
	 */
	public abstract Date nextITV();
	
	/**
	 * Método para añadir componentes al vehículo
	 * @param c componente a añadir
	 */
	public void addComponent(IComponent c) throws InvalidComponentException {
		if(c==null) {
			return;
		}
		if(!this.comprobarValidez(c) && this.componentes.contains(c)) {
			return;
		}
		this.componentes.add(c);
		c.setVehicle(this);
	}
	
	/**
	 * Método para comprobar si un componente es válida
	 * @param c componente del que se desea conocer si es válido para el vehículo
	 * @return booleano que define si es válido el componente para el vehículo
	 * @throws InvalidComponentException si no es compatible el componente hay excepcion
	 */
	public boolean comprobarValidez(IComponent c) throws InvalidComponentException {
		for(IComponent c1 : this.componentes) {
			if(c1.getName().equals(c.getName())) {
				return false;
			}
		}
		return true;
	}
	
	/**
	 * Método para conocer la lista de componentes
	 * @return lista de componentes del vehículo
	 */
	@Override
	public List<IComponent> getComponents() {
		return this.componentes;
	}
}
