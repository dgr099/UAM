package pr3.trafico.carnet;

import java.util.ArrayList;


import pr3.trafico.conductores.Persona;
import pr3.trafico.vehiculos.Vehiculo;
/**
 * Clase que contiene los datos del carnet, propietario, puntos, id
 * lista de licencias y si se encuentra o no suspendido
 *
 * @version 1.0 2 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Carnet {
	private Persona propietario;
	private int puntos;
	static private long id = 0;
	private long mi_id;
	private ArrayList<TipoLicencia> licencias = new ArrayList<TipoLicencia>();
	private boolean suspendido = false;
	
	/**
	 * Constructor de la clase carnet
	 * @param licencias	conjunto de licencias del carnet
	 */
	public Carnet(TipoLicencia...licencias) {
		this.puntos = 12;
		for(TipoLicencia licencia:licencias) {
			this.addLicencia(licencia);
		}
		this.mi_id=id++; //le asignamos su id
	}
	
	/**
	 * Método para conocer si el carnet está o no suspendido
	 * 
	 * @return booleano que define si el carnet está suspendido
	 */
	public boolean isSuspendido(){
		return this.suspendido;
	}
	
	/**
	 * Método para poner el carnet como suspendido
	 * 
	 */
	public void setSuspendido(){
		this.suspendido=true;
	}
	
	/**
	 * Método para conocer el propietario del carnet
	 * 
	 * @return propietario del carnet
	 */
	public Persona getPropietario() {
		return propietario;
	}
	
	/**
	 * Método para establecer el propietario del carnet. se tendrá en cuenta si es valida
	 * 
	 * @param propietario propietario que se pretende establecer al carnet
	 * @return true en caso de poder asignar dicho propietario y false en caso contrario
	 */
	public boolean setPropietario(Persona propietario) {
		if(propietario == null){
			return false;
		}
		for(TipoLicencia L : this.licencias) {
			if(!TipoLicencia.validoPersona(propietario, L)) {
				return false;
			}
		}
		this.propietario=propietario;
		return true;
	}
	
	/**
	 * Método para conocer los puntos del carnet
	 * 
	 * @return puntos del carnet
	 */
	public int getPuntos() {
		return puntos;
	}
	
	/**
	 * Método para establecer los puntos del carnet
	 * @param puntos puntos a establecer en el carnet
	 * 
	 */
	public void setPuntos(int puntos) {
		if(puntos<0){
			this.puntos=0;
			return;
		}
		this.puntos = puntos;
	}
	
	/**
	 * Método para conocer el id del carnet
	 * 
	 * @return id del carnet
	 */
	public static long getId() {
		return id;
	}
	
	/**
	 * Método para conocer la lista de licencias del carnet
	 * 
	 * @return lista de licencias del carnet
	 */
	public ArrayList<TipoLicencia> getTl() {
		return licencias;
	}
	
	/**
	 * Método para establecer la lista de licencias del carnet
	 * @param licencias lista de licencias a establecer en el carnet
	 */
	public void setTl(ArrayList<TipoLicencia> licencias) {
		this.licencias = licencias;
	}
	
	/**
	 * Método para imprimir la clase carnet, con su id, licencias puntos...
	 * 
	 * @return String descriptivo del carnet
	 */
	public String toString() {
		return "Carnet [id=" + mi_id + ", licencias=" + licencias + ", puntos=" + puntos +"]";
	}
	
	/**
	 * Método para añadir una licencia a la lista de licencias del carnet
	 * 
	 * @param b tipo de licencia a añadir en el carnet
	 */
	public void addLicencia(TipoLicencia b) {
		if(b==null) {
			return;
		}
		if(this.licencias.contains(b)) {
			return;
		}
		this.licencias.add(b);
		return;
	}
	
	/**
	 * Método para comprobar si el carnet es válido para un determinado vehículo
	 * 
	 * @param v vehículo para el que se quiere comprobar si el carnet es válidos
	 * @return String descriptivo del coche
	 */
	public boolean carnetValido(Vehiculo v) {
		if(v == null){
			return false;
		}
		for(TipoLicencia tl:this.licencias) {
			if(TipoLicencia.validoVehiculo(v, tl)) {
				return true;
			}
		}
		return false;
	}
	
}
