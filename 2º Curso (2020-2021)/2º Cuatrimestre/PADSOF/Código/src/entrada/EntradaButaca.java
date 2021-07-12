package entrada;

import evento.Representacion;
import teatro.Butaca;
import teatro.Zona;
import teatro.ZonaNumerada;

/**
 * Clase con métodos y atributos de la entradas asociadas a butacas
 * @version 1.0 26 Mar 21
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class EntradaButaca extends Entrada{
	/**
	 * 
	 */
	private static final long serialVersionUID = 2447489169160683743L;
	private Butaca butaca; //butaca con la que está ligada la entrada
	
	/**
	 * Constructor de la clase entrada de butaca
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param abono Booleano para indicar si se empleo o no abono
	 * @param representacion Representacion a la que está asociada la entrada
	 * @param butaca Butaca a la que está asociada la entrada
	 * @throws Exception
	 */
	public EntradaButaca(boolean abono, Representacion representacion, Butaca butaca) throws Exception {
		super(abono, representacion);
		if(butaca == null) {
			throw new Exception("Es necesario asignar una butaca");
		}
		if(butaca.isActiva()==false) { /*si esa butaca no está activa*/
			throw new Exception("Error la butaca no está activa y por tanto no se puede usar");
		}
		this.butaca = butaca;
		if(representacion!=null) {
			if(representacion.addEntrada(this)==false) {
				throw new Exception("Entrada no válida");
			}
		}
		super.setCodigo(super.getCodigo() + "ZN"); /*le concatenamos ZN en el código para indicar zona numerada*/ 
	}
	
	/**
	 * Función para obtener la butaca a la que está asociada una entrada
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Butaca a la que está asociada una entrada de butaca
	 */
	public Butaca getButaca() {
		return this.butaca;
	}

	@Override
	public boolean comprobarValidez(Representacion r) {
		double perc = 100 - Zona.getLimitacion();
		int max=-1;
		if(this.getZona()!=null){
			max = (int)(((ZonaNumerada)this.getZona()).getNButacas() * perc/100.0);
		}
		if(r==null) {
			return true;
		}
		if(r.getAsistencia()==r.getAforo()){ /*si se ha cumplido el tope*/
			return false;
		}
		if(r.getButacasOcupadas().contains(this.getButaca())==true) { /*si está cya ocupada la butaca*/
			return false;
		}
		//comprobar limitaciones
		if(this.getZona()!=null)
			if(r.getOcupacion().containsKey(this.getZona())==true){ /*si contiene la zona de la entrada*/
				if(r.getOcupacion().get(this.getZona())>=max) { /*si esa zona ya esta ocupada al máximo contando con las límitaciones*/
					return false;
				}
				return true;
			}
		if(max==0) {
			return false;
		}
		return true;
	}

	/**
	 * Función para obtener la zona de la entrada de butacas
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Zona de la entrada
	 */
	public Zona getZona() {
		return (Zona)(this.butaca.getZonaButaca());
	}
    /**
     * Función para obtener la posición de la butaca de la entrada
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return String descriptivo de la posición de la butaca de la entrada
     */
    public String getSeatNumber () {
		if(this.getZona()==null || this.getButaca()==null){
			return "Sin zona ni butaca";
		}
    	return this.getZona().getNombre() + " Fila: " + this.getButaca().getFila() + " Columna: " + this.getButaca().getColumna(); 
    }

	@Override
	public String getPosicion() {
		return this.butaca.toString();
	}
}
