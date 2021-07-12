package ui.control.compra;

import java.text.DecimalFormat;

import abonos.Abono;
import evento.Evento;
import evento.Representacion;
import reserva.Reserva;
import teatro.Butaca;
import teatro.Zona;
import ui.view.Ventana;
import ui.view.compra.UICompra;
import usuario.TarjetaBancaria;

/**
 * Clase encargada de guardar los datos de compra
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlCompra {
	private Abono abonoComprar = null; //abono seleccionado si es que quiere comprar un abono
	private Evento evento = null; //evento seleccionado si es que quiere comprar un evento
	private Abono abonoUsar = null; //abono para comprar la entrada
	private Representacion r = null; //representacion a comprar del evento
	private TarjetaBancaria tarjetaSeleccionada=null; //tarjeta seleccionada por el usuario
	private Zona z = null;
	private Butaca butaca = null;
	private UICompra uic;
	private DecimalFormat df = new DecimalFormat("###.##");
	private Reserva reserva = null;
	/**
	 * Constructor de la clase
	 * @param v ventana de la que recoge la vista
	 */
	public ControlCompra(Ventana v) {
		this.uic = v.getUICompra();
	}
	public Reserva getReserva() {
		return this.reserva;
	}
	public void setReserva(Reserva r) {
		this.reserva = r;
	}
	public Abono getAbonoAUsar() {
		return this.abonoUsar;
	}
	public void setAbonoUsar(Abono a) {
		this.abonoUsar = a;
	}
	/**
	 * @return the abonoComprar
	 */
	public Abono getAbonoComprar() {
		return abonoComprar;
	}
	/**
	 * @return the evento
	 */
	public Evento getEvento() {
		return evento;
	}
	/**
	 * @return the r
	 */
	public Representacion getR() {
		return r;
	}
	/**
	 * @return the tarjetaSeleccionada
	 */
	public TarjetaBancaria getTarjetaSeleccionada() {
		return tarjetaSeleccionada;
	}
	/**
	 * @return the z
	 */
	public Zona getZ() {
		return z;
	}
	/**
	 * @return the butaca
	 */
	public Butaca getButaca() {
		return butaca;
	}
	/**
	 * @param abonoComprar the abonoComprar to set
	 */
	public void setAbonoComprar(Abono abonoComprar) {
		this.abonoComprar = abonoComprar;
		uic.setTitulo(this.abonoComprar.getCodigo());
		uic.setPrecio(String.valueOf(df.format(this.abonoComprar.getPrecio())) + " €");
	}
	/**
	 * @param evento the evento to set
	 */
	public void setEvento(Evento evento) {
		this.evento = evento;
		uic.setTitulo(evento.getTitulo());
		uic.setDesc(evento.getDescripcion());
		double val;
		if((val = evento.getValoracion())<0) {
			uic.noValoraciones();
		} else {
			uic.setValoracion(val);
		}
	}
	/**
	 * @param r the r to set
	 */
	public void setR(Representacion r) {
		this.r = r;
	}
	/**
	 * @param tarjetaSeleccionada the tarjetaSeleccionada to set
	 */
	public void setTarjetaSeleccionada(TarjetaBancaria tarjetaSeleccionada) {
		this.tarjetaSeleccionada = tarjetaSeleccionada;
	}
	/**
	 * @param z the z to set
	 */
	public void setZ(Zona z) {
		this.z = z;
		if(this.evento!=null && z!=null) { //si es una zona y evento válidos
			uic.setPrecio(String.valueOf(df.format(this.evento.getPrecio(z))) + " €");
		}
	}
	/**
	 * @param butaca the butaca to set
	 */
	public void setButaca(Butaca butaca) {
		this.butaca = butaca;
	}
	/**
	 * Método para resetear los valores de control compra
	 */
	public void reset() { //reseteo todos los valores para evitar problemas
		abonoComprar = null;
		evento = null;
		r = null;
		tarjetaSeleccionada=null;
		z = null;
		butaca = null;
		this.uic.setPrecio("");
		this.reserva=null;
	}
	
}
