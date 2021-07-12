package teatro;

import java.io.Serializable;

/** 
 * Clase con métodos y atributos de Butaca
 * @version 1.0 28 Mar 30
 * @author David Teófilo Garitagoitia Romero
 */

public class Butaca implements Serializable{
    /**
	 * 
	 */
	private static final long serialVersionUID = 4507349805542034606L;
	//public static final String red = "\u001B[31m";     // codigo para el color rojo
	//public static final String green = "\u001B[32m";   // codigo para el color verde
	//public static final String white = "\u001B[37m";   // codigo para el blanco
	private static long id_last=0;
	private long id;
	private boolean activa=true;
	private int fila;
	private int columna;
	private ZonaNumerada zonaButaca; 
	
	/**
	 * Método para obtener el ida_last (empleado principalmente para el guardado y carga del sistema)
	 * @return el di_last
	 */
	public static long getIdLast(){
		return id_last;
	}

	/**
	 * Para establecer el id_last (se emplea principalmente en la carga)
	 * @param i id_last a establecer
	 */
	public static void setIdLast(long i) {
		Butaca.id_last = i;
	}
	/**
	 * Función para obtener el id
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return id de la butaca
	 */
	public long getId() {
		return id;
	}
	/**
	 * Función para saber si la butaca está activa
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return true o false
	 */
	public boolean isActiva() {
		return activa;
	}
	/**
	 * Función que pone una butaca a activa o a no activa, dependiendo de su estado anterior
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param activa booleano que indica la disponibilidad de la butaca
	 */
	public void setActiva(boolean activa) {
		if(activa==true && !this.isActiva()) { //si pasa de estar no activa a estar activa
			this.getZonaButaca().setNButacas(this.getZonaButaca().getNButacas() + 1);
		} else if(activa==false && this.isActiva()) { //si pasa de no estar activa a activarse
			this.getZonaButaca().setNButacas(this.getZonaButaca().getNButacas() - 1);
		}
		this.activa = activa;
	}
	/**
	 * Función para obtener una fila
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return fila de la butaca
	 */
	public int getFila() {
		return fila;
	}
	/**
	 * Función para asignar una fila
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param fila fila a colocar
	 */
	public boolean setFila(int fila) {
		if(fila<0) {
			return false; /*sin importar la zona, no hay filas negativas*/
		}
		if(this.zonaButaca==null) { /*si no tiene asignada zona*/
			this.fila=fila; /*simplemente le ponemos la fila*/
			return true;
		}
		if(this.zonaButaca.getFilas()<=fila) { /*comprueba si se le puede asignar la fila*/
			return false;
		}
		if(this.zonaButaca.searchButaca(fila, this.columna)!=null) { /*si ya existe una butaca en esa fila*/
			return false;
		}
		this.zonaButaca.getButacas()[this.fila][this.columna]=null; /*cambio de posición la butaca*/
		this.fila = fila; /*si no, entonces si que se asigna la nueva fila*/
		this.zonaButaca.getButacas()[this.fila][this.columna]=this;
		return true;
	}
	
	/**
	 * Función para obtener una columna
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return la columna 
	 */
	public int getColumna() {
		return columna;
	}
	/**
	 * Funcion para asignar una columna
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param columna 
	 * @return true o false dependiendo de si se ha podido colocar
	 */
	public boolean setColumna(int columna) {
		if(columna<0) { /*sin importar la zona, si es una columna negativa no se puede asignar*/
			return false;
		}
		if(this.zonaButaca==null) { /*si no tiene asignada zona*/
			this.columna=columna;
		}
		if(this.zonaButaca.getColumnas()<=columna){ /*si la nueva columna no vale*/
			return false;
		}
		if(this.zonaButaca.searchButaca(this.fila, columna)!=null) { /*si en esa posicion no hay una butaca*/
			return false;
		}
		this.zonaButaca.getButacas()[this.fila][this.columna]=null;
		this.columna = columna;
		this.zonaButaca.getButacas()[this.fila][this.columna]=this;
		return true;
	}
	/**
	 * Funcion para obtener la zona numerada donde se encuentra la butaca
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @return la zona de la butaca
	 */
	public ZonaNumerada getZonaButaca() {
		return zonaButaca;
	}
	/**
	 * Funcion para cambiar la zona numerada donde se encuentra la butaca
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param zonaButaca la zona donde se encuentra la butaca
	 * @return true o false dependiendo de si se ha colocado
	 */
	public boolean setZonaButaca(ZonaNumerada zonaButaca) {
		if(zonaButaca==null) { /*si no le pasas zona*/
			return true;
		}
		if(this.fila<0 || this.columna<0) { /*comprueba que los atributos de columna y de fila están bien*/
			return false; /*esta comprobación sirve para la creación de butacas*/
		}
		/*compruba comparando con las filas y columnas nueva posicion*/
		if(zonaButaca.getFilas()<=this.fila || zonaButaca.getColumnas()<=this.columna) {
			return false;
		}
		/*comprueba que no haya nadie en esa posición*/
		if(zonaButaca.searchButaca(this.fila, this.columna)!=null) {
			return false;
		}
		/*si se puede asignar a esa zona se borra de la anterior*/
		/*primero quitas la butaca de la anterior zona*/
		if(this.zonaButaca!=null) {
			this.zonaButaca.getButacas()[this.fila][this.columna]=null;
		}
		/*le asignas la nueva zona*/
		this.zonaButaca = zonaButaca;
		this.zonaButaca.addButaca(this);
		this.getZonaButaca().setNButacas(this.getZonaButaca().getNButacas() + 1);
		return true;
	}
	/**
	 * Constructor de la clase Butaca
	 * @version 1.0 28 Mar 30
	 * @author David Teófilo Garitagoitia Romero
	 * @param fila fila de la butaca
	 * @param columna columna de la butaca
	 * @param zonaButaca zona de la butaca
	 */
	public Butaca(int fila, int columna, ZonaNumerada zonaButaca) throws Exception {
		this.fila=fila;
		this.columna=columna;
		if(this.setZonaButaca(zonaButaca)==false) {
			throw new Exception("Error atributos new Butaca");
		}
		this.id =++Butaca.id_last; /*si funciona correctamente, estableces su id*/
	}
	/**
	 * Muestra la butaca por pantalla, tanto si está activa o no como su posición
	 */
	public void mostrarButaca() {
		String a = new String();
		if(this.isActiva()) {
			a = "A"; /*A de activa*/
		}
		else {
			a = "N";
		}
		System.out.print(a + this.fila + ":" + this.columna );
	}
	@Override
	public boolean equals(Object o) {
		if(o instanceof Butaca) {
			Butaca aux = (Butaca)o;
			if(aux.getZonaButaca()!=null)
				return aux.getZonaButaca().equals(this.getZonaButaca()) && aux.getFila() == this.getFila() && this.getColumna() == aux.getColumna();
			if(this.getZonaButaca()!=null)	return false;
			return aux.getFila() == this.getFila() && this.getColumna() == aux.getColumna();
		}
		return false;
	}
	
	/**
	 * Método para obtener un string descriptivo de la butaca
	 */
	public String toString() {
		return this.zonaButaca.toString() + "; Fila: " + this.fila + " Columna: " + this.columna;
	}
	
	
}
