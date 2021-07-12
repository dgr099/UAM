package usuario;

import java.io.Serializable;
import java.util.Date;

/**
 * Clase TarjetaBancaria
 * @author Jonás Arce García
 */


public class TarjetaBancaria implements Serializable{
	private static final long serialVersionUID = 8032973568981129903L;
	private String numTarjeta;
	private Date FechaCad;
	private int codigo;

	/**
	 * Constructor de la clase TarjetaBancaria
	 * @param numT	número de la tarjeta
	 * @param Fecha	fecha de caducidad
	 * @param cod	código CVS 
	 */
	public TarjetaBancaria(String numT, Date Fecha, int cod) {
		this.numTarjeta = numT;
		this.FechaCad = Fecha;
		this.codigo = cod;
	}

	/**
	 * 
	 *  @return numTarjeta
	 */
	public String getNumTarjeta() {
		return numTarjeta;
	}

	/**
	 * 
	 * @param numTarjeta 
	 */
	public void setNumTarjeta(String numTarjeta) {
		this.numTarjeta = numTarjeta;
	}

	/**
	 * 
	 * @return FechaCad
	 */
	public Date getFechaCad() {
		return FechaCad;
	}

	/**
	 * 
	 * @param fechaCad
	 */
	public void setFechaCad(Date fechaCad) {
		FechaCad = fechaCad;
	}

	/**
	 * 
	 * @return codigo
	 */
	public int getCodigo() {
		return codigo;
	}

	/**
	 * 
	 * @param codigo
	 */
	public void setCodigo(int codigo) {
		this.codigo = codigo;
	}
	
}
