package pr3.trafico.multas;

/**
 * Clase que contiene los métodos y atributos de las multas
 * 
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Multa {
    private String matricula;
    private String tipoMulta;
    private int puntos;

    /**
	 * Constructor de la clase Multa
	 * @param matricula	matricula del vehiculo que tiene la multa
	 * @param tipoMulta tipo de multa
	 * @param puntos puntos que suponen la sancion
	 */
    public Multa(String matricula, String tipoMulta, int puntos) {
        this.matricula = matricula;
        this.tipoMulta = tipoMulta;
        this.puntos = puntos;
    }

	@Override
	public String toString() {
		return "Multa [matricula=" + matricula + ", tipoMulta=" + tipoMulta + ", puntos=" + puntos + "]";
    }

    /**
	 * Método para obtener la matricula
	 * @return matricula
	 */
    public String getMatricula(){
        return this.matricula;
    }

     /**
	 * Método para obtener los puntos
	 * @return puntos
	 */
    public int getPuntos(){
        return this.puntos;
    }

     /**
	 * Método para anyadir puntos por ITV caducada
	 */
    public void addITVCad() {
    	++this.puntos;
    }

     /**
	 * Método para obtener el tipo de multa
	 * @return tipo de multa
	 */
    public String getTipo() {
    	return this.tipoMulta;
    }

    
}