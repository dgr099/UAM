package ui.view;

import java.awt.CardLayout;
import java.util.Stack;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import sistema.Sistema;
import ui.control.Control;
import ui.view.admin.AddAbonoAnual;
import ui.view.admin.AddAbonoCiclo;
import ui.view.admin.AddRepresentacion;
import ui.view.admin.AñadirAbonos;
import ui.view.admin.AñadirEventos;
import ui.view.admin.CambiarRepresentacion;
import ui.view.admin.PaginaAddEventosOAbonos;
import ui.view.admin.PaginaAdmin;
import ui.view.admin.PaginaEliminarAbono;
import ui.view.admin.PaginaEliminarEvento;
import ui.view.admin.StatEvento;
import ui.view.admin.VistaAprobarMensaje;
import ui.view.compra.UICompra;
import ui.view.loginAndRegister.Login;
import ui.view.loginAndRegister.Register;
import ui.view.teatro.ConfTeatro;
import ui.view.usuario.InfoAbono;
import ui.view.usuario.InfoCiclo;
import ui.view.usuario.InfoEntrada;
import ui.view.usuario.PaginaReservas;
import ui.view.usuario.PaginaUsuario;
//clase global con todos los paneles
public class Ventana extends JFrame{
	private static final long serialVersionUID = -3683614603911572174L;
	
	private Login login = null; //panel del login
	private Register register = null; //panel del register
	private ConfTeatro configuracionTeatro = null; //para el control de teatro
	private VistaPrincipal vistaP = null;
	private PaginaAddEventosOAbonos pagEventAdmin = null;
	private UICompra uicompra = null;
	private StatEvento statevento = null;
	private PaginaUsuario paginaUsuario = null;
	private InfoEntrada infoEntrada = null;
	private InfoAbono infoAbono = null;
	private PaginaReservas paginaReservas = null;
	private PaginaAdmin paginaAdmin = null;
	private VistaAprobarMensaje aprobarMensaje = null;
	private AñadirAbonos añadirAbono = null;
	private AddAbonoAnual añadirAbonoAnual = null;
	private AddAbonoCiclo añadirAbonoCiclo = null;
	private AñadirEventos añadirEventos = null;
	private AddRepresentacion addRepresentacion = null;
	private InfoCiclo infoCiclo = null;
	private PaginaEliminarEvento paginaEliminarEvento = null;
	private PaginaEliminarAbono paginaEliminarAbono = null;
	private CambiarRepresentacion cambiarRepresentacion = null;
	private JPanel contentPane=null;
	private Stack<String> lasts = new Stack<String>();
	private String current = null; //panel en uso actual
	
	public Ventana() {
		//this.setExtendedState(this.getExtendedState() | JFrame.MAXIMIZED_BOTH); //para que inicie maximizado
		this.setBounds(0, 0, 640, 480); //dimensiones para el panel
		contentPane = new JPanel();//creamos el panel
		this.setContentPane(contentPane); //lo establecemos
		contentPane.setLayout(new CardLayout()); //le ponemos un card Layout
		try {
			this.login = new Login(); //creamos el panel del login
			this.register = new Register(); //creamos el panel del register
			this.configuracionTeatro = new ConfTeatro(); //creamos la conf de teatro
			this.vistaP = new VistaPrincipal();
			this.uicompra = new UICompra();
			this.paginaUsuario = new PaginaUsuario();
			this.pagEventAdmin = new PaginaAddEventosOAbonos();
			this.infoEntrada = new InfoEntrada();
			this.infoAbono = new InfoAbono();
			this.paginaReservas = new PaginaReservas();
			this.paginaAdmin = new PaginaAdmin();
			this.statevento = new StatEvento();
			this.aprobarMensaje = new VistaAprobarMensaje();
			this.añadirAbono = new AñadirAbonos();
			this.añadirAbonoAnual = new AddAbonoAnual();
			this.añadirAbonoCiclo = new AddAbonoCiclo();
			this.añadirEventos = new AñadirEventos();
			this.infoCiclo = new InfoCiclo();
			this.paginaEliminarEvento = new PaginaEliminarEvento();
			this.paginaEliminarAbono = new PaginaEliminarAbono();
			this.addRepresentacion = new AddRepresentacion();
			this.cambiarRepresentacion = new CambiarRepresentacion();
		} catch (Exception e) {
			e.printStackTrace();
			return;
		} //creamos la conf de teatro
		contentPane.add(this.login, "Login"); //añadimos el login
		contentPane.add(this.register, "Register"); //añadimos el login
		contentPane.add(this.configuracionTeatro, "Conf Teatro"); //añademos la conf de teatro
		contentPane.add(this.vistaP, "VistaPrincipal");
		contentPane.add(this.uicompra, "UICompra");
		contentPane.add(this.statevento, "Stat");
		contentPane.add(this.paginaUsuario, "Pagina usuario");
		contentPane.add(this.pagEventAdmin, "PaginaEventosAdmin");
		contentPane.add(this.infoEntrada, "InfoEntrada");
		contentPane.add(this.infoAbono, "InfoAbono");
		contentPane.add(this.paginaReservas, "Reservas");
		contentPane.add(this.paginaAdmin, "PaginaAdmin");
		contentPane.add(this.aprobarMensaje, "AprobarMensaje");
		contentPane.add(this.añadirAbono, "AddAbono");
		contentPane.add(this.añadirAbonoAnual, "AddAbonoAnual");
		contentPane.add(this.añadirAbonoCiclo, "AddAbonoCiclo");
		contentPane.add(this.añadirEventos, "AddEvento");
		contentPane.add(this.infoCiclo, "InfoCiclo");
		contentPane.add(this.paginaEliminarEvento, "PaginaEliminarEvento");
		contentPane.add(this.paginaEliminarAbono, "PaginaEliminarAbono");
		this.current = "VistaPrincipal";
		mostrarPanel("VistaPrincipal"); //se inicia con la vista principal que inicia mostrando el sin usuario
		this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE); //para que no pueda cerrar sin confirmar
		this.addWindowListener(new java.awt.event.WindowAdapter() {
		    @Override
		    public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				if (JOptionPane.showConfirmDialog(contentPane, 
		            "Are you sure you want to close this window?", "Close Window?", 
		            JOptionPane.YES_NO_OPTION,
		            JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION){
					Sistema.getInstancia().saveSistema(); //guarda todos los cambios antes de salir
		            System.exit(0);
		        }
		    }
		});
	}
	
	public String getLast() {
		if(!this.lasts.isEmpty())
			return this.lasts.pop();
		return null;
	}
	
	public void addLast(String last) {
		this.lasts.push(last);
	}
	
	public String getCurrent() {
		return this.current;
	}
	
	public void setCurrent(String current) {
		this.current = current;
	}
	public VistaPrincipal getVistaPrincipal() {
		return this.vistaP;
	}
	public Login getLogin() {
		return this.login;
	}
	
	public Register getRegister() {
		return this.register;
	}
	
	public ConfTeatro getConfTeatro() {
		return this.configuracionTeatro;
	}
	public PaginaAddEventosOAbonos getPaginaEventosAdmin() {
		return this.pagEventAdmin;
	}
	
	public void setControlador(Control c) {
		if(c==null) {
			return;
		}
		this.login.setControlador(c.getControlLogin(), c.getControlBack());
		this.register.setControlador(c.getControlRegister(), c.getControlBack());
		this.configuracionTeatro.setControlador(c.getControlLimitaciones(), c.getControlAñadirZona(), c.getControlBack(), c.getControlListaZonaNoNumerada(), c.getControlListaZonaNumerada());
		this.vistaP.setControlador(c.getControlVistaSouthSinIniciar(), c.getControlVistaSouthIniciado(), c.getControlVistaNorth(), c.getControlVistaNorthAdmin(), c.getControlEvento(), c.getControlAbonos(), c.getControlStatListaEventos(), c.getControlSeleccionarCiclo());
		this.uicompra.setControlador(c.getControlEvento(), c.getControlBackCompra(), c.getControlCancel(), c.getControlCompra(), c.getControlSeleccionarTarjeta(), c.getControlSeleccionarZona(), c.getControlSeleccionarRepresentacion(), c.getControlSeleccionarAbono(), c.getControlNext(), c.getControlAñadirListaDeEspera(), c.getControlProceder(), c.getControlReserva(), c.getControlLiberarReserva());
		this.statevento.setControlador(c.getControlCancelAdmin(), c.getControlAddRepresentacion(), c.getControlBack(), c.getControlCancelarRepresentacion(), c.getControlVerComentario(), c.getControlCambiarFechaRepresentacion());
		this.paginaUsuario.setControlador(c.getControlBack(), c.getControlUsuario(), c.getControlSeleccionEntrada(), c.getControlSeleccionAbono(), c.getControlReservaUsuario());
		this.pagEventAdmin.setControlador(c.getControlPaginaEventosAdmin(), c.getControlBack());
		this.infoEntrada.setControlador(c.getControlBack(), c.getControlUsuario(), c.getControlComentario(), c.getControlBorrarComentario(), c.getControlValoracion());
		this.infoAbono.setControlador(c.getControlBack(), c.getControlUsuario());
		this.paginaReservas.setControlador(c.getControlBack(), c.getControlCompra(), c.getControlSeleccionarReserva());
		this.paginaAdmin.setControlador(c.getControlBack(), c.getControlCancelarRepresentacion(), c.getControlVerComentario(), c.getControlCambiarFechaRepresentacion());
		this.aprobarMensaje.setControlador(c.getControlBack(), c.getControlAceptarComentario());
		this.añadirAbono.setControlador(c.getControlBack(), c.getControlAñadirAbono());
		this.añadirAbonoAnual.setControlador(c.getControlCancelAdmin(), c.getControlAddAbonoAnual());
		this.añadirAbonoCiclo.setControlador(c.getControlCancelAdmin(), c.getControlAddAbonoCiclo(), c.getControlAbonoCiclo(), c.getControlAddEventoCiclo());
		this.añadirEventos.setControlador(c.getControlBack(), c.getControlAddConcierto(), c.getControlAddDanza(), c.getControlAddObraTeatro(), c.getControlAddPrecioEvento());
		this.infoCiclo.setControlador(c.getControlAbonos(), c.getControlBack());
		this.paginaEliminarEvento.setControlador(c.getControlBack(), c.getControlDelEvento());
		this.paginaEliminarAbono.setControlador(c.getControlBack(), c.getControlDelAbono());
	}
	
	public void mostrarPanel(String carta) {
		CardLayout l = (CardLayout)contentPane.getLayout();
		l.show(contentPane, carta); //muestra el panel del string recibido
		this.lasts.push(this.current); //la ultima es la que estaba antes
		this.current = carta; //la nueva es la que se pasa por argumento
	}
	
	/*para que no haga push*/
	public void mostrarPanelSinVueltaAtras(String carta) {
		CardLayout l = (CardLayout)contentPane.getLayout();
		l.show(contentPane, carta); //muestra el panel del string recibido
		this.lasts.push(this.current); //la ultima es la que estaba antes
		this.setCurrent("VistaPrincipal");
	}
	
	/**
	 * Método para ir a la anterior ventana
	 */
	public void goBack() {
		String last = this.getLast();
		if(last!=null) { //si hay pantalla anterior
			this.mostrarPanel(last); //muestra la pantalla anterior
		}
	}
	
	public UICompra getUICompra() {
		return this.uicompra;
	}
	
	public StatEvento getStatEvento() {
		return this.statevento;
	}
	
	public PaginaUsuario getPaginaUsuario() {
		return this.paginaUsuario;
	}
	
	public InfoEntrada getInfoEntrada() {
		return this.infoEntrada;
	}
	
	public InfoAbono getInfoAbono() {
		return this.infoAbono;
	}

	public PaginaReservas getPaginaReservas() {
		return paginaReservas;
	}
	public PaginaAdmin getPaginaAdmin() {
		return this.paginaAdmin;
	}
	public VistaAprobarMensaje getVistaAprobarMensaje() {
		return this.aprobarMensaje;
	}
	public AñadirAbonos getAñadirAbono() {
		return this.añadirAbono;
	}
	public AddAbonoAnual getAddAbonoAnual() {
		return this.añadirAbonoAnual;
	}
	public AddAbonoCiclo getAddAbonoCiclo() {
		return this.añadirAbonoCiclo;
	}
	public InfoCiclo getInfoCiclo() {
		return this.infoCiclo;
	}
	public PaginaEliminarEvento getPaginaEliminarEvento() {
		return this.paginaEliminarEvento;
	}
	public PaginaEliminarAbono getPaginaEliminarAbono() {
		return this.paginaEliminarAbono;
	}
	public AddRepresentacion getAddRepresentacion() {
		return this.addRepresentacion;
	}
	public CambiarRepresentacion getCambiarRepresentacion() {
		return this.cambiarRepresentacion;
	}
}
