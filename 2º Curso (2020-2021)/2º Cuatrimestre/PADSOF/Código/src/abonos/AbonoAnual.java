package abonos;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.List;


import entrada.Entrada;
import evento.Evento;
import teatro.Zona;
import ui.view.usuario.InfoAbono;

/**
 * Clase que contiene la información general de un abono anual
 * 
 * @version		1.0 13 Abr 2021
 * @author 		Daniel Cerrato (daniel.cerrato@estudiante.uam.es)
 *
 */
public class AbonoAnual extends Abono{

	/* Entero estatico que contiene la version de la serializacion */
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -1374267355586436846L;

	/* String estatica que contiene una cadena base para el codigo del abono */
	public static final String CODIGO_INI = "code";
	
	/* Lista de entradas compradas con el abono */
	ArrayList<Entrada> entradas = new ArrayList<Entrada>();

	/**
	 * Constructor de la clase AbonoAnual
	 * 
	 * @param "p" contiene el precio del abono
	 * @param "z" contiene la zona donde se podra usar el abono
	 */
	public AbonoAnual(double p, Zona z) throws Exception {
		super(CODIGO_INI, p, z);
		super.setCodigo(this.generarCodigo());
	};
	
	/**
	 * Metodo para obtener la lista de entradas compradas con el abono
	 * 
	 * @return Devuelve la lista de entradas como ArrayList
	 */
	public ArrayList<Entrada> getEntradas(){
		return this.entradas;
	}
	
	/**
	 * Metodo para añadir una entrada comprada con el abono a la lista de entradas compradas
	 * 
	 * @param "e" contiene la entrada comprada como Entrada
	 * 
	 * @return Devuelve true si la entrada ha sido añadida correctamente, sino devuelve false
	 */
	public boolean addEntradas(Entrada e){
		if(this.comprobarValidez(e)) {
			this.entradas.add(e);
			return true;
		}
		return false;
	}
	
	/**
	 * Metodo para comprobar la validez del abono a la hora de comprar una entrada
	 * 
	 * @param "e" contiene la entrada que se quiere comprar
	 * 
	 * @return Devuelve true si no se ha comprado ninguna entrada para la misma representacion de la entrada
	 * 		   y la zona coincide con la del abono, sino devuelve false
	 */
	@Override
	public boolean comprobarValidez(Entrada e){
		Evento evento = e.getRepresentacion().getEvento();
		if(!e.getZona().equals(this.zona)) return false;
		for(Entrada entrada: this.entradas) {
			if(entrada.getRepresentacion().getEvento().equals(evento)) return false;
		}
		return true;
	}
	
	/**
	 * Método para comprobar la validez del abono
	 * @param e Evento del que se quiere comprobar la validez
	 * @return booleano que será true si es válido
	 */
	public boolean comprobarValidez(Evento e){
		Evento evento = e;
		for(Entrada entrada: this.entradas) {
			if(entrada.getRepresentacion().getEvento().equals(evento)) return false;
		}
		return true;
	}
	
	/**
	 * Metodo para generar un codigo en base a la zona y el tipo de abono
	 * 
	 * @return Devuelve un codigo como String
	 */
	@Override
	public String generarCodigo() {
		String n = Integer.toString(Abono.getCodigoLast() + 1);
		Abono.setCodigoLast(Abono.getCodigoLast() + 1);
		String nombre = super.getZona().getNombre();
		n += "AAz:" + nombre;
		return n;
	}

	/** 
	 * Metodo para mostrar la informacion del abono (Para debuggear)
	 */
	@Override
	public void mostrarAbono(){
		super.mostrarAbono();
	}

	/**
	 * Método para reescribir los cambios gráficos conforme al abono seleccionado
	 */
	@Override
	public void dataAbonoUI(InfoAbono a) {
		a.getZona().setText("-" + this.getZona().toString()); //recogemos la zona
		a.getTipo().setText("-Tipo: Abono Anual"); //lo ponemos como abono anual
		a.getDescuento().setText(""); //le quitamos el descuento ya que tienen precio fijo
		a.getEvento().setText(""); //le quitamos el label de eventos ya que incluye todos durante el año
		a.getMain_second().removeAll(); //vaciamos la lista de elementos 
		a.getMain_second().setPreferredSize(new Dimension(0, 0));
		
	}

	/**
	 * Método para obtener la lista de eventos, como es para abono anual retorna null
	 */
	@Override
	public List<Evento> getEventos() {
		return null;
	}

	/**
	 * Como el abono anual no tiene eventos, el retorno es -2 para identificar el tipo de abono
	 */
	@Override
	public double getValoracion() {
		return -2;
	}

}
