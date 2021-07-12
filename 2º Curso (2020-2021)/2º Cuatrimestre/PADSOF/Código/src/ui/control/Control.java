package ui.control;

import ui.control.abonos.ControlAbonos;
import ui.control.admin.ControlAbonoCiclo;
import ui.control.admin.ControlModerarComentario;
import ui.control.admin.ControlAddAbonoAnual;
import ui.control.admin.ControlAddAbonoCiclo;
import ui.control.admin.ControlAddConcierto;
import ui.control.admin.ControlAddDanza;
import ui.control.admin.ControlAddEventoCiclo;
import ui.control.admin.ControlAddObraTeatro;
import ui.control.admin.ControlAddPrecioEvento;
import ui.control.admin.ControlAddRepresentacion;
import ui.control.admin.ControlAñadirAbono;
import ui.control.admin.ControlCancelAdmin;
import ui.control.admin.ControlCancelarRepresentacion;
import ui.control.admin.ControlDelAbono;
import ui.control.admin.ControlDelEvento;
import ui.control.admin.ControlPaginaEventosAdmin;
import ui.control.admin.ControlStatListaEventos;
import ui.control.admin.ControlVerComentario;
import ui.control.compra.ControlAñadirListaEspera;
import ui.control.compra.ControlBackCompra;
import ui.control.compra.ControlCompra;
import ui.control.compra.ControlLiberarReserva;
import ui.control.compra.ControlNext;
import ui.control.compra.ControlProceder;
import ui.control.compra.ControlReserva;
import ui.control.compra.ControlSeleccionarAbono;
import ui.control.compra.ControlSeleccionarRepresentacion;
import ui.control.compra.ControlSeleccionarTarjeta;
import ui.control.compra.ControlSeleccionarZona;
import ui.control.registerAndLogin.ControlLogin;
import ui.control.registerAndLogin.ControlRegister;
import ui.control.teatro.ControlAñadirZona;
import ui.control.teatro.ControlLimitaciones;
import ui.control.teatro.ControlListaZonaNoNumerada;
import ui.control.teatro.ControlListaZonaNumerada;
import ui.control.usuario.ControlBorrarComentario;
import ui.control.usuario.ControlComentario;
import ui.control.usuario.ControlReservaUsuario;
import ui.control.usuario.ControlSeleccionAbono;
import ui.control.usuario.ControlSeleccionEntrada;
import ui.control.usuario.ControlSeleccionarCiclo;
import ui.control.usuario.ControlSeleccionarReserva;
import ui.control.usuario.ControlUsuario;
import ui.control.usuario.ControlValoracion;
import ui.control.admin.ControlCambiarFechaRepresentacion;
import ui.view.Ventana;

//controlLoginase global con los controladores
/**
 * Clase que agrupa los controles de la vista de la aplicación
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class Control {
	private Ventana ventana = null; //ventana de la app
	private ControlLogin controlLogin = null; //control para el panel de login
	private ControlRegister controlRegister = null; //control para el registro
	private ControlBack controlBack = null; //control para el botón de atras
	private ControlLimitaciones controlLimitaciones = null; //control para establecer las limitaciones
	private ControlAñadirZona controlAñadirZona = null; //control para añadir zonas
	private ControlVista_South_sin_iniciar controlVistaSouth = null;
	private ControlVista_South_iniciado controlVistaSouthIniciado = null;
	private ControlVista_North controlVistaNorth = null;
	private ControlVista_North_admin controlVistaNorthAdmin = null;
	private ControlCompra controlCompra = null;
	private ControlSeleccionarZona controlSeleccionarZona = null;
	private ControlSeleccionarTarjeta controlSeleccionarTarjeta = null;
	private ControlSeleccionarRepresentacion controlSeleccionarRepresentacion = null;
	private ControlSeleccionarAbono controlSeleccionarAbono = null;
	private ControlNext controlNext = null;
	private ControlAñadirListaEspera controlAñadirListaDeEspera = null;
	private ControlProceder controlProceder = null;
	private ControlReserva controlReserva = null;
	private ControlBackCompra controlBackCompra = null;
	private ControlEvento controlEvento = null;
	private ControlCancel controlCancel = null;
	private ControlAbonos controlAbonos = null;
	private ControlStatListaEventos controlStatListaEventos = null;
	private ControlPaginaEventosAdmin controlPaginaEventosAdmin = null;
	private ControlUsuario controlUsuario = null;
	private ControlSeleccionEntrada controlSeleccionEntrada = null;
	private ControlSeleccionAbono controlSeleccionAbono = null;
	private ControlComentario controlComentario = null;
	private ControlBorrarComentario controlBorrarComentario = null;
	private ControlValoracion controlValoracion = null;
	private ControlReservaUsuario controlReservaUsuario = null;
	private ControlSeleccionarReserva controlSeleccionarReserva = null;
	private ControlLiberarReserva controlLiberarReserva = null;
	private ControlCancelarRepresentacion controlCanecelarRepresentacion = null;
	private ControlVerComentario controlVerComentario = null;
	private ControlModerarComentario controlAceptarComentario = null;
	private ControlAñadirAbono controlAddAbono = null;
	private ControlCancelAdmin controlCancelAdmin = null;
	private ControlAddAbonoAnual controlAddAbonoAnual = null;
	private ControlAddAbonoCiclo controlAddAbonoCiclo = null;
	private ControlAbonoCiclo controlAbonoCiclo = null;
	private ControlAddEventoCiclo controlAddEventoCiclo = null;
	private ControlAddConcierto controlAddConcierto = null;
	private ControlAddObraTeatro controlAddObraTeatro = null;
	private ControlAddDanza controlAddDanza = null;
	private ControlSeleccionarCiclo controlSeleccionarCiclo = null;
	private ControlDelEvento controlDelEvento = null;
	private ControlDelAbono controlDelAbono = null;
	private ControlAddRepresentacion controlAddRepresentacion = null;
	private ControlAddPrecioEvento controlAddPrecioEvento = null;
	private ControlCambiarFechaRepresentacion controlCambiarFechaRepresentacion = null;
	private ControlListaZonaNoNumerada controlListaZonaNoNumerada = null;
	private ControlListaZonaNumerada controlListaZonaNumerada = null;
	/**
	 * Constructor de la clase (inicializa los controles para que funcionen para la ventana pasada por arg)
	 * @param ventana clase que contiene todas las vistas de la aplicación
	 */
	public Control(Ventana ventana) {
		this.ventana = ventana;
		this.controlLogin = new ControlLogin(this.ventana);
		this.controlBack = new ControlBack(this.ventana);
		this.controlRegister = new ControlRegister(this.ventana);
		this.controlLimitaciones = new ControlLimitaciones(this.ventana);
		this.controlAñadirZona = new ControlAñadirZona(this.ventana);
		this.controlVistaSouth = new ControlVista_South_sin_iniciar(this.ventana);
		this.controlVistaSouthIniciado = new ControlVista_South_iniciado(this.ventana);
		this.controlVistaNorth = new ControlVista_North(this.ventana);
		this.controlVistaNorthAdmin = new ControlVista_North_admin(this.ventana);
		this.controlCompra = new ControlCompra(this.ventana);
		this.controlSeleccionarZona = new ControlSeleccionarZona(this.ventana);
		this.controlSeleccionarTarjeta = new ControlSeleccionarTarjeta(this.ventana);
		this.controlSeleccionarRepresentacion = new ControlSeleccionarRepresentacion(this.ventana);
		this.controlSeleccionarAbono = new ControlSeleccionarAbono(this.ventana);
		this.controlNext = new ControlNext(this.ventana);
		this.controlAñadirListaDeEspera = new ControlAñadirListaEspera(this.ventana);
		this.controlProceder = new ControlProceder(this.ventana);
		this.controlReserva = new ControlReserva(this.ventana);
		this.controlBackCompra = new ControlBackCompra(this.ventana);
		this.controlEvento = new ControlEvento(this.ventana);
		this.controlCancel = new ControlCancel(this.ventana);
		this.controlAbonos = new ControlAbonos(this.ventana);
		this.controlStatListaEventos = new ControlStatListaEventos(this.ventana);
		this.controlPaginaEventosAdmin = new ControlPaginaEventosAdmin(this.ventana);
		this.controlUsuario = new ControlUsuario(this.ventana);
		this.controlSeleccionEntrada = new ControlSeleccionEntrada(this.ventana);
		this.controlSeleccionAbono = new ControlSeleccionAbono(this.ventana);
		this.controlComentario = new ControlComentario(this.ventana);
		this.controlBorrarComentario = new ControlBorrarComentario(this.ventana);
		this.controlValoracion = new ControlValoracion(this.ventana);
		this.controlReservaUsuario = new ControlReservaUsuario(this.ventana);
		this.controlSeleccionarReserva = new ControlSeleccionarReserva(this.ventana);
		this.controlLiberarReserva = new ControlLiberarReserva(this.ventana);
		this.controlCanecelarRepresentacion = new ControlCancelarRepresentacion(this.ventana);
		this.controlVerComentario = new ControlVerComentario(this.ventana);
		this.controlAceptarComentario = new ControlModerarComentario(this.ventana);
		this.controlAddAbono = new ControlAñadirAbono(this.ventana);
		this.controlCancelAdmin = new ControlCancelAdmin(this.ventana);
		this.controlAddAbonoAnual = new ControlAddAbonoAnual(this.ventana);
		this.controlAddAbonoCiclo = new ControlAddAbonoCiclo(this.ventana);
		this.controlAbonoCiclo = new ControlAbonoCiclo();
		this.controlAddEventoCiclo = new ControlAddEventoCiclo(this.ventana);
		this.controlAddConcierto = new ControlAddConcierto(this.ventana);
		this.controlAddDanza = new ControlAddDanza(this.ventana);
		this.controlAddObraTeatro = new ControlAddObraTeatro(this.ventana);
		this.controlSeleccionarCiclo = new ControlSeleccionarCiclo(this.ventana);
		this.controlDelEvento = new ControlDelEvento(this.ventana);
		this.controlDelAbono = new ControlDelAbono(this.ventana);
		this.controlAddRepresentacion = new ControlAddRepresentacion(this.ventana);
		this.controlCambiarFechaRepresentacion = new ControlCambiarFechaRepresentacion(this.ventana);
		this.controlListaZonaNoNumerada = new ControlListaZonaNoNumerada(this.ventana);
		this.controlListaZonaNumerada = new ControlListaZonaNumerada(this.ventana);
		this.controlAddPrecioEvento = new ControlAddPrecioEvento();
	}
	/*getters de los controles*/
	public Ventana getView() {
		return this.ventana;
	}
	public ControlVista_North_admin getControlVistaNorthAdmin() {
		return this.controlVistaNorthAdmin;
	}
	
	public ControlAñadirZona getControlAñadirZona() {
		return this.controlAñadirZona;
	}
	
	public ControlLogin getControlLogin() {
		return this.controlLogin;
	}
	
	public ControlBack getControlBack() {
		return this.controlBack;
	}
	
	public ControlRegister getControlRegister() {
		return this.controlRegister;
	}
	
	public ControlLimitaciones getControlLimitaciones() {
		return this.controlLimitaciones;
	}
	
	public ControlVista_South_sin_iniciar getControlVistaSouthSinIniciar() {
		return this.controlVistaSouth;
	}
	public ControlVista_South_iniciado getControlVistaSouthIniciado() {
		return this.controlVistaSouthIniciado;
	}
	public ControlVista_North getControlVistaNorth() {
		return this.controlVistaNorth;
	}
	public ControlCompra getControlCompra() {
		return this.controlCompra;
	}
	public ControlSeleccionarZona getControlSeleccionarZona() {
		return this.controlSeleccionarZona;
	}
	public ControlSeleccionarTarjeta getControlSeleccionarTarjeta() {
		return this.controlSeleccionarTarjeta;
	}
	public ControlSeleccionarRepresentacion getControlSeleccionarRepresentacion() {
		return this.controlSeleccionarRepresentacion;
	}
	public ControlSeleccionarAbono getControlSeleccionarAbono() {
		return this.controlSeleccionarAbono;
	}
	public ControlNext getControlNext() {
		return this.controlNext;
	}
	public ControlAñadirListaEspera getControlAñadirListaDeEspera() {
		return this.controlAñadirListaDeEspera;
	}
	public ControlProceder getControlProceder() {
		return this.controlProceder;
	}
	public ControlReserva getControlReserva() {
		return this.controlReserva;
	}
	public ControlBackCompra getControlBackCompra() {
		return this.controlBackCompra;
	}
	public ControlEvento getControlEvento() {
		return this.controlEvento;
	}
	public ControlCancel getControlCancel() {
		return this.controlCancel;
	}
	public ControlAbonos getControlAbonos() {
		return this.controlAbonos;
	}
	public ControlStatListaEventos getControlStatListaEventos() {
		return this.controlStatListaEventos;
	}
	public ControlPaginaEventosAdmin getControlPaginaEventosAdmin() {
		return this.controlPaginaEventosAdmin;
	}
	public ControlUsuario getControlUsuario() {
		return this.controlUsuario;
	}
	public ControlSeleccionEntrada getControlSeleccionEntrada() {
		return this.controlSeleccionEntrada;
	}
	public ControlSeleccionAbono getControlSeleccionAbono() {
		return this.controlSeleccionAbono;
	}
	public ControlBorrarComentario getControlBorrarComentario() {
		return this.controlBorrarComentario;
	}
	public ControlComentario getControlComentario() {
		return this.controlComentario;
	}
	public ControlValoracion getControlValoracion() {
		return this.controlValoracion;
	}
	public ControlReservaUsuario getControlReservaUsuario() {
		return this.controlReservaUsuario;
	}
	public ControlSeleccionarReserva getControlSeleccionarReserva() {
		return this.controlSeleccionarReserva;
	}
	public ControlLiberarReserva getControlLiberarReserva() {
		return this.controlLiberarReserva;
	}
	public ControlCancelarRepresentacion getControlCancelarRepresentacion() {
		return this.controlCanecelarRepresentacion;
	}
	public ControlVerComentario getControlVerComentario() {
		return this.controlVerComentario;
	}
	public ControlModerarComentario getControlAceptarComentario() {
		return this.controlAceptarComentario;
	}
	public ControlAñadirAbono getControlAñadirAbono() {
		return this.controlAddAbono;
	}
	public ControlCancelAdmin getControlCancelAdmin() {
		return this.controlCancelAdmin;
	}
	public ControlAddAbonoAnual getControlAddAbonoAnual() {
		return this.controlAddAbonoAnual;
	}
	public ControlAddAbonoCiclo getControlAddAbonoCiclo() {
		return this.controlAddAbonoCiclo;
	}
	public ControlAddEventoCiclo getControlAddEventoCiclo() {
		return this.controlAddEventoCiclo;
	}
	public ControlAbonoCiclo getControlAbonoCiclo() {
		return this.controlAbonoCiclo;
	}
	public ControlAddConcierto getControlAddConcierto() {
		return this.controlAddConcierto;
	}
	public ControlAddDanza getControlAddDanza() {
		return this.controlAddDanza;
	}
	public ControlAddObraTeatro getControlAddObraTeatro() {
		return this.controlAddObraTeatro;
	}
	public ControlSeleccionarCiclo getControlSeleccionarCiclo() {
		return this.controlSeleccionarCiclo;
	}
	public ControlDelEvento getControlDelEvento() {
		return this.controlDelEvento;
	}
	public ControlDelAbono getControlDelAbono() {
		return this.controlDelAbono;
	}
	public ControlAddRepresentacion getControlAddRepresentacion() {
		return this.controlAddRepresentacion;
	}
	public ControlAddPrecioEvento getControlAddPrecioEvento() {
		return this.controlAddPrecioEvento;
	}
	public ControlCambiarFechaRepresentacion getControlCambiarFechaRepresentacion() {
		return this.controlCambiarFechaRepresentacion;
	}
	public ControlListaZonaNoNumerada getControlListaZonaNoNumerada() {
		return this.controlListaZonaNoNumerada;
	}
	public ControlListaZonaNumerada getControlListaZonaNumerada() {
		return this.controlListaZonaNumerada;
	}
}
