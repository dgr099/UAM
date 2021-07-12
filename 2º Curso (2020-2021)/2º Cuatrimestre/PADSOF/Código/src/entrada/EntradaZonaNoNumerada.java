package entrada;

import evento.Representacion;
import teatro.Zona;
import teatro.ZonaNoNumerada;

/**
 * Clase con métodos y atributos de las entradas de zona no numerada
 * @version 1.0 28 Mar 21
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class EntradaZonaNoNumerada extends Entrada{
	private static final long serialVersionUID = -5997383565193143240L;
	private ZonaNoNumerada zonaNoNumerada; //Zona no numerada asignada a la entrada
	
	/**
	 * Constructor de la clase EntradaZonaNoNumerada
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param abono booleano para definir si se empleo un abono para adquirir la entrada
	 * @param representacion representación a la que está asignada la entrada
	 * @param zonaNoNumerada zona vinculada con la butaca
	 * @throws Exception
	 */
	public EntradaZonaNoNumerada(boolean abono, Representacion representacion, ZonaNoNumerada zonaNoNumerada) throws Exception {
		super(abono, representacion);
		/*si no la puedes crear por estar llena*/
		this.zonaNoNumerada = zonaNoNumerada; /*le asignas la zona*/
		if(representacion!=null){ /*si tiene asignada una representacion*/
			if(representacion.addEntrada(this)==false){ /*se comprueba si se puede añadir la entrada*/
				throw new Exception("Entrada no válida");
			}
		}
		super.setCodigo(super.getCodigo() + "ZNN"); /*le concatenamos ZNN para indicar que es una zona no numerada*/ 
		
	}

	/**
	 * Función para obtener la Zona vinculada a la entrada de zona no numerada
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @return Zona vinculada a la entrada
	 */
	public ZonaNoNumerada getZonaNoNumerada() {
		return zonaNoNumerada;
	}

	/**
	 * Función para asignar la zona no numerada de una entrada 
	 * @version 1.0 28 Mar 21
	 * @author David Teófilo Garitagoitia Romero
	 * @param zonaNoNumerada zona que se pretende asignar a la entrada
	 */
	public void setZonaNoNumerada(ZonaNoNumerada zonaNoNumerada) {
		this.zonaNoNumerada = zonaNoNumerada;
	}

	@Override
	public boolean comprobarValidez(Representacion r) {
		double perc = 100 - Zona.getLimitacion();
		int max = -1;
		if(this.getZonaNoNumerada()!=null) {
			max = (int)(this.getZonaNoNumerada().getAforo() * perc/100.0);
		}
		if(r==null) { //comprobar argumentos de entrada
			return true;
		}
		if(r.getAsistencia()==r.getAforo()){ /*si se ha cumplido el tope del representacion*/
			return false;
		}
		/*si la zona está en el mapa*/
		if(this.getZonaNoNumerada()!=null)
			if(r.getOcupacion().containsKey(this.getZonaNoNumerada())==true){ /*si contiene la zona de la entrada*/
				if(r.getOcupacion().get(this.getZonaNoNumerada()) >=  max) { /*si esa zona ya esta ocupada al máximo contando con las límitaciones*/
					return false;
				}
				return true;
			}
		if(0 == max) { /*si no puede estar nadie en la zona*/
			return false;
		}
		return true;
	}

	@Override
	public Zona getZona() {
		return this.zonaNoNumerada;
	}
    /**
     * Método para obtener el string descriptivo de la posición de la entrada
     */
    public String getSeatNumber () {
		if(this.getZona()==null || this.getZona().getNombre()==null){
			return "Sin localización";
		}
    	return this.getZona().getNombre();
    }

	@Override
	public String getPosicion() {
		return this.getZona().toString();
	}

}
