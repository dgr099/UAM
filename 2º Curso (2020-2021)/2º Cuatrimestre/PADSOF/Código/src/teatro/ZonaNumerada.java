package teatro;

import entrada.Entrada;
import entrada.EntradaButaca;
import ui.control.compra.ControlCompra;

/** 
 * Clase con métodos y atributos de una zona numerada
 * @version 1.0 28 Mar 30
 * @author David Teófilo Garitagoitia Romero
 */

public class ZonaNumerada extends Zona{
	/**
	 * 
	 */
	private static final long serialVersionUID = 434353291818625884L;
	private int filas=0;
	private int columnas=0;
	private Butaca butacas[][] = {null};
	private int nButacas=0;
	private int distButacas=0; /*se obtiene apartir de las limitaciones*/
	/**
	 * Constructor de la clase ZonaNumerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre de la zona numerada
	 * @param filas filas de la zona numerada
	 * @param columnas columnas de la zona numerada
	 */
	public ZonaNumerada(String nombre, int filas, int columnas) throws Exception{
		super(nombre);
		if(filas<0 || columnas<0) {
			throw new Exception("Parámetros incorrectos");
		}
		this.filas = filas;
		this.columnas = columnas;
		this.butacas = new Butaca[filas][columnas];
		/*ponemos inactivas las butacas necesarias para poder cumplir las limitaciones*/
		this.actLimitaciones();
		/**/
	}
	/**
	 * Función que devuelve el número de butacas
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return El número de las butacas de la zona
	 */
	public int getNButacas() { /*obtener el número de butacas de la zona (como el aforo)*/
		return this.nButacas;
	}
	/**
	 * Función que asigna el número de butacas
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param nButacas número de butacas (int)
	 */
	public void setNButacas(int nButacas) { /*obtener el número de butacas de la zona (como el aforo)*/
		if(nButacas<0)	return;
		this.nButacas = nButacas;
		return;
	}
	/**
	 * Función que añade una butaca al array de butacas según su fila y su columna
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param f filas
	 * @param c columnas
	 * @return true si se pudo añadir la butaca correctamente o false en caso contrario
	 */
	public Boolean addButaca(int f, int c) throws Exception {
		Butaca b = null;
		if(f<0 || c<0) {
			return false;
		}
		if(f>=this.filas || c>=this.columnas) {
			return false;
		}
		
		if(this.butacas[f][c]!=null) {
			return false;
		}
		
		b=new Butaca(f, c, this);
		this.nButacas++;
		this.butacas[f][c]=b;
		this.actLimitaciones();
		return true;
		
	}
	/**
	 * Función que añade una butaca al array de butacas según el objeto Butaca
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param b Butaca
	 * @return true si se pudo añadir la butaca correctamente o false en caso contrario
	 */
	public Boolean addButaca(Butaca b) {
		if(b==null) {
			return false;
		}
		
		if(b.getFila()>=this.filas || b.getColumna()>=this.columnas) { //si la fila o columna no existen
			return false;
		}
		
		if(this.butacas[b.getFila()][b.getColumna()]==b) { //si ya esta la butaca que quieres añadir
			return true;
		}
		
		if(this.butacas[b.getFila()][b.getColumna()]!=null) {
			return false;
		}
		this.nButacas++;
		this.butacas[b.getFila()][b.getColumna()]=b;
		this.actLimitaciones();
		return true;
	}
	/**
	 * Función que actualiza las dimensiones del teatro tanto por filas como por columnas
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param f fila
	 * @param c columna
	 */
	private void actDimensiones(int f, int c) {
		if(f<0 || c<0) { /*no puede tener dimensiones negativas*/
			return;
		}
		Butaca nb[][] = new Butaca[f][c]; /*creas un nuevo array con el nuevo tamaño*/
		if(f==this.filas && c==this.filas) { /*si no hay nada que actualizar*/
			return; 
		}
		if(f!=this.filas) { /*si queremos actualizar las filas*/
			/*copiamos en el nuevo array lo que había en el original*/
			System.arraycopy(this.butacas, 0, nb, 0, f-this.filas > 0 ? this.filas : f);
		}
		else if(c!=this.columnas) { /*si lo que queremos actualizar son las columnas*/
			for(int i=0; i!=this.filas; i++) {
				/*la comparación es por si quieres quitar para que no copie los ultimos valores*/
				System.arraycopy(this.butacas[i], 0, nb[i], 0, c-this.columnas > 0 ? this.columnas : c);
			}
		}
		this.filas=f;
		this.columnas=c;
		this.butacas=nb;
		this.actLimitaciones();
		return;	
	}
	/**
	 * Función que añade una fila a la zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void addFila() {
		int nf=this.filas+1;
		actDimensiones(nf, this.columnas);
		return;
	}
	/**
	 * Función que quita una fila a la zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void quitarFila() {
		if(this.filas==0) {
			return;
		}
		int nf=this.filas-1;
		for(int i=0; i!=this.getColumnas();i++) { /*actualizamos el numero de butacas*/
			if(this.butacas[this.getFilas()-1][i]!=null) {
				this.nButacas--;
			}
		}
		actDimensiones(nf, this.columnas);
		return;
	}
	/**
	 * Función que añade una columna a la zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void addColumna() {
		int nc=this.columnas+1;
		actDimensiones(this.filas, nc);
		return;
	}
	/**
	 * Función que quita una columna a la zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void quitarColumna() {
		int nc=this.columnas-1;
		if(this.columnas==0) {
			return;
		}
		for(int i=0; i!=this.getFilas();i++) { /*actualizamos el numero de butacas*/
			if(this.butacas[i][this.getColumnas()-1]!=null) {
				this.nButacas--;
			}
		}
		actDimensiones(this.filas, nc);
		return;
	}
	/**
	 * Función que quita una butaca a la zona numerada según su fila y columna
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param f fila
	 * @param c	columna
	 * @return true si la butaca fue eliminada correctamente o false en caso contrario
	 */
	public Boolean quitarButaca(int f, int c) {
		if(f<0 || c<0) {
			return false;
		}
		if(f>=this.filas || c>=this.columnas) {
			return false;
		}
		this.butacas[f][c]=null; /*la butaca de esa posición la eliminamos (aunque el hueco sigue para la separación)*/
		this.nButacas--;
		return true;
	}
	/**
	 * Función que muestra por pantalla las butacas
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	public void mostrarButacas() {
		for(int i=0; i!=this.filas; i++) {
			for(int j=0; j!=this.columnas-1; j++) {
				mostrarButacasAux(i, j);
				System.out.print(" "); /*separador entre butacas*/
			}
			mostrarButacasAux(i, this.columnas-1); /*el último no tiene separación*/
			System.out.println();
			
		}
	}
	/**
	 * Muestra por pantalla una butaca según su fila y su columna
	 * @param f (int)
	 * @param c (int)
	 */
	private void mostrarButacasAux(int f, int c) {
		if(this.butacas[f][c]!=null) { //si hay butaca
			this.butacas[f][c].mostrarButaca();
		}
		else { /*si no hay butaca en esa posicion*/
			System.out.print("_");
		}
	}
	/**
	 * Función que busca una butaca según su fila y su columna
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param f fila
	 * @param c columna
	 * @return la butaca correspondiente a la fila y columna pasada como argumento en el caso correcto, en caso de error null
	 */
	public Butaca searchButaca(int f, int c) {
		if(f<0 || c<0) {
			return null;
		}
		if(f>=this.filas || c>=this.columnas) {
			return null;
		}
		return this.butacas[f][c];
	}
	/**
	 * Función que obtiene las filas de una zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return filas de la zona numerada
	 */
	public int getFilas() {
		return filas;
	}
	/**
	 * Función que obtiene las filas de una zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return columnas de la zona numerada
	 */
	public int getColumnas() {
		return columnas;
	}
	/**
	 * Función que obtiene las butacas de una zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @return butacas de la zona numerada
	 */
	public Butaca[][] getButacas() {
		return butacas;
	}

	/**
	 * Función que muestra las butacas de la zona numerada
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 */
	@Override
	public void mostrarZona() {
		System.out.println(super.getNombre());
		this.mostrarButacas();
		
	}
	/**
	 * Función que compara la zona pasada por argumento con la zona actual
	 * @version 1.0 28 Mar 30
 	 * @author David Teófilo Garitagoitia Romero
	 * @param z zona a comparar
	 */
	@Override
	public int compareTo(Zona z) {
		return super.comparteTo(z);
	}
	@Override
	public int getMax() {
		return this.nButacas;
	}
	@Override
	public Entrada factoryEntrada(ControlCompra cc) throws Exception {
		if(cc.getButaca() == null)
			return null;
		EntradaButaca e = null;
		e = new EntradaButaca(true, cc.getR(), cc.getButaca());
		if(!cc.getAbonoAUsar().comprobarValidez(e)) {
			return null;
		}
		return e;
	}
	
	@Override
	public String toString() {
		return "Zona Numerada: " + super.toString();
	}
	
	/**
	 * Método para actualizar las butacas que deben estar como no disponibles por las limitaciones
	 */
	public void actLimitaciones() {
		double a = 0;
		if(this.getTeatro()!=null)
			a = 1.0/(1-(this.getTeatro().getLimitaciones()/100));
			distButacas = (int) Math.ceil(a);
		for(int f = 0; f!=this.filas; f++) {
			for(int c = 0; c!=this.columnas; c++) {
				Butaca b = this.butacas[f][c];
				if(b==null) {
					continue;
				}
				if(distButacas==0 || c%distButacas == 0) {
					b.setActiva(true);
				}else {
					b.setActiva(false);
				}
			}
		}
	}
}
