package teatro;

import entrada.Entrada;
import entrada.EntradaZonaNoNumerada;
import ui.control.compra.ControlCompra;

/** 
 * Clase con métodos y atributos de una zona no numerada
 * @version 1.0 28 Mar 30
 * @author David Teófilo Garitagoitia Romero
 */

public class ZonaNoNumerada extends Zona{
	/**
	 * 
	 */
	private static final long serialVersionUID = 4023236231823854653L;
	private int aforo;
	@Override
	/**
	 * Función que muestra la zona por pantalla
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarZona() {
		System.out.println(super.getNombre() + " Aforo: " + this.getAforo());

	}
	/**
	 * Función que devuelve el aforo de la zona no numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return aforo de la zona
	 */
	public int getAforo() {
		return aforo;
	}
	/**
	 * Función que asigna el aforo de la zona no numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param aforo aforo
	 */
	public void setAforo(int aforo) {
		if(aforo<0) { //no puede tener aforo negativo
			return;
		}
		this.aforo = aforo;
	}
	/**
	 * Constructor de la clase ZonaNoNumerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre de la zona
	 * @param aforo aforo de la zona
	 */
	public ZonaNoNumerada(String nombre, int aforo) throws Exception {
		super(nombre);
		if(aforo<0) {
			throw new Exception("Error de parámetros");
		}
		this.aforo = aforo;
	}
	/**
	 * Función que compara la zona pasada por argumento con la zona actual
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona a comparar
	 */
	public int compareTo(Zona z) {
		return super.comparteTo(z);
	}
	@Override
	public int getMax() {
		return this.aforo;
	}
	@Override
	public Entrada factoryEntrada(ControlCompra cc) {
		EntradaZonaNoNumerada e = null;
		try {
			e = new EntradaZonaNoNumerada(true, cc.getR(), this);
		} catch (Exception e2) {
			e2.printStackTrace();
		}
		if(!cc.getAbonoAUsar().comprobarValidez(e)) {
			return null;
		}
		return e;
	}
	
	@Override
	public String toString() {
		return "Zona No Numerada: " + super.toString();
	}
	@Override
	public void actLimitaciones() {
		return;
	}
}
