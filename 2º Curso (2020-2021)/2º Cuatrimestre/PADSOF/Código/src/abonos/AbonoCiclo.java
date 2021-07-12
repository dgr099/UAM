package abonos;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import javax.swing.JLabel;

import entrada.Entrada;
import evento.*;
import sistema.Sistema;
import teatro.Zona;
import ui.view.usuario.InfoAbono;

/**
 * Clase que contiene la información general de un abono de ciclo
 * 
 * @version		1.0 13 Abr 2021
 * @author 		Daniel Cerrato (daniel.cerrato@estudiante.uam.es)
 *
 */
public class AbonoCiclo extends Abono{

	/* Entero estatico que contiene la version de la serializacion */
	private static final long serialVersionUID = 1L;
	/* Macro de valor real que contiene el precio inicial del abono como 0 */
	public static final double PRECIO_INI = 0.0;
	/* String estatica que contiene una cadena base para el codigo del abono */
	public static final String CODIGO_INI = "code";
	/* Entero que contiene el numero de abonos de ciclo generados */
	private static int numAbonos = 0;

	private Ciclo ciclo;
	/* Valor real que contiene el descuento (%) aplicado en el abono */
	public double descuento; 
	/* Lista de eventos a los que se puede asistir con el abono */
	public List<Evento> eventos = new ArrayList<Evento>();
	
	/**
	 * Constructor de la clase AbonoCiclo
	 * 
	 * @param "d" contiene el descuento (%) a aplicar en el abono como Double
	 * @param "e" contiene la lista de eventos a los que se puede asistir con el abono como ArrayList
	 * @param "z" contiene la zona elegida para usar el abono
	 * 
	 * @throws Exception si la lista de eventos esta vacia
	 */
	public AbonoCiclo(double d, ArrayList<Evento> e, Zona z) throws Exception {
		super(CODIGO_INI, PRECIO_INI,z); 
		super.setCodigo(this.generarCodigo());
		this.descuento = d;
		if(e.isEmpty() || z == null) throw new Exception("No hay eventos en la lista");
		this.eventos = e;
		boolean flag = false;
		for(Ciclo c : Sistema.getInstancia().getCiclos()) {
			if(c.getEventos().equals(e)) {
				this.ciclo = c;
				flag = true;
				break;
			}
		}
		if(!flag) {
			this.ciclo = new Ciclo(e);
			Sistema.getInstancia().addCiclo(this.ciclo);	
		}
		super.setPrecio(this.calcularPrecio(d,e,z));
		super.setCodigo(this.generarCodigo());
	}
	
	/**
	 * Constructor de la clase AbonoCiclo
	 * 
	 * @param "d" contiene el descuento (%) a aplicar en el abono como Double
	 * @param "c" contiene el ciclo del abono
	 * @param "z" contiene la zona elegida para usar el abono
	 * 
	 * @throws Exception si la lista de eventos esta vacia
	 */
	public AbonoCiclo(double d, Ciclo c, Zona z) throws Exception {
		super(CODIGO_INI, PRECIO_INI,z); 
		super.setCodigo(this.generarCodigo());
		this.descuento = d;
		if(c==null || c.getEventos().size()==0 || z == null) throw new Exception("No hay eventos en la lista");
		this.ciclo = c;
		this.eventos =  c.getEventos();
		super.setPrecio(this.calcularPrecio(d, c.getEventos(),z));
		super.setCodigo(this.generarCodigo());
	}
	
	/**
	 * Metodo para calcular el precio del abono
	 * 
	 * @param "d" contiene el descuento (%) a aplicar en el abono como Double
	 * @param "e" contiene la lista de eventos a los que se puede asistir con el abono como ArrayList
	 * @param "z" contiene la zona elegida para usar el abono
	 * 
	 * @return Devuelve el precio obtenido en el calculo al aplicar el descuento como Double
	 */
	private double calcularPrecio(double d, List<Evento> e, Zona z) {
		double p = 0.0; 
		if(e.isEmpty()) return PRECIO_INI;
		for (Evento ev: e) p += Math.max(ev.getPrecio(z), 0);
		p = p * (1.0-(d/100.0));
		return p;
	}
	
	/**
	 * Metodo para obtener la lista de eventos a los que se puede asistir con el abono
	 * 
	 * @return Devuelve la lista de eventos como ArrayList
	 */
	public List<Evento> getEventos(){
		return this.eventos;
	}
	
	/**
	 * Método para obtener el ciclo del evento
	 * @return ciclo del abono
	 */
	public Ciclo getCiclo() {
		return this.ciclo;
	}
	
	/**
	 * Metodo para borrar un evento de la lista una vez usado el abono en una representacion del mismo
	 * 
	 * @param "e" contiene el evento al que se va a asistir como Evento 
	 */
	public void delEventos(Evento e){
		this.eventos.remove(e);
	}
	
	/**
	 * Metodo para obtener el descuento aplicado en el abono
	 * 
	 * @return Devuelve el descuento aplicado como Double
	 */
	public double getDescuento(){
		return this.descuento;
	}
	
	/**
	 * Metodo para cambiar el descuento aplicado en el abono 
	 * 
	 * @param "d" contiene el nuevo descuento a aplicar como Double
	 */
	public void setDescuento(double d){
		this.descuento = d;
		super.setPrecio(this.calcularPrecio(d, this.getEventos(), super.getZona()));
	}

	/**
	 * Metodo para comprobar la validez del abono a la hora de comprar una entrada
	 * 
	 * @param "e" contiene la entrada que se quiere comprar
	 * 
	 * @return Devuelve true si no se ha usado el abono en una representacion del evento de la entrada,
	 * 		   y la zona del abono y de la entrada coinciden, sino devuelve false
	 */
	@Override
	public boolean comprobarValidez(Entrada e){
		Evento evento = e.getRepresentacion().getEvento();
		Zona zona = e.getZona();
		if(this.eventos.contains(evento) && zona.equals(this.zona)) return true; 
		return false;
	}
	
	/**
	 *	Método para saber si el abono es válido para un evento
	 *	@param e Evento para el que se desea comprobar su validez
	 *	@return booleano que define su validez
	 */
	public boolean comprobarValidez(Evento e) {
		if(this.eventos.contains(e)) return true; 
		return false;
	}
	/**
	 * Metodo para mostrar la informacion del abono (Para debuggear)
	 */
	@Override
	public void mostrarAbono(){
		super.mostrarAbono();
		System.out.println("Descuento: " + this.descuento + "\nSe puede asistir aun a estos eventos:");
		for(Evento e: eventos) e.mostrarEvento();
	}
	
	/**
	 * Metodo para obtener una fecha de caducidad
	 * 
	 * @return Devuelve la fecha de la ultima representacion de entre todos los eventos a los que se puede asistir
	 * 		   con el abono como Calendar
	 */
	public Calendar getFechaCaducidad() {
		Calendar date = Calendar.getInstance();
		List<Representacion> repres;
		for(Evento e: this.eventos) {
			repres= e.getRepresentaciones();
			if(!repres.isEmpty()) {
				for(Representacion r: repres) {
					if(r.getFechaYHora().after(date)) date = r.getFechaYHora();
				}
			}
		}
		return date;
	}
	
	/**
	 * Metodo para generar un codigo en base a la zona y el tipo de abono
	 * 
	 * @return Devuelve un codigo como String
	 */
	@Override
	public String generarCodigo() {
		String n = Integer.toString(++numAbonos);
		String nombre = super.getZona().getNombre();
		n += "ACz:" + nombre;
		return n;
	}

	@Override
	public void dataAbonoUI(InfoAbono a) {
		a.getZona().setText("-" + this.getZona().toString()); //recogemos la zona
		a.getTipo().setText("-Tipo: Abono De Ciclo"); //lo ponemos como abono anual
		a.getDescuento().setText(""); //le quitamos el descuento ya que tienen precio fijo
		a.getEvento().setText(""); //le quitamos el label de eventos ya que incluye todos durante el año
		a.getMain_second().removeAll(); //vaciamos la lista de elementos para rellenarla con los del abono
		for(Evento e : this.getEventos()) {
			a.getMain_second().add(new JLabel(e.getTitulo())); //la rellenamos con los eventos contenidos en el ciclo
		}
		a.getMain_second().setPreferredSize(new Dimension(500, (this.getEventos().size() * 10)));
	}

	@Override
	public double getValoracion() {
		return this.ciclo.getValoracion();
	}
}
