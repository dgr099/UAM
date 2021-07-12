package ui.view.compra;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import ui.control.compra.ControlAñadirListaEspera;
import ui.control.compra.ControlLiberarReserva;
import ui.control.compra.ControlNext;
import ui.control.compra.ControlProceder;
import ui.control.compra.ControlReserva;
import ui.control.compra.ControlSeleccionarAbono;
import ui.control.compra.ControlSeleccionarRepresentacion;
import ui.control.compra.ControlSeleccionarTarjeta;
import ui.control.compra.ControlSeleccionarZona;

public class UICompra_south extends JScrollPane{
	
	CardLayout l = new CardLayout();
	JPanel int_tarjeta = new JPanel(); //para introducir la trajeta y comprar
	JPanel selec_datos = new JPanel(); //para seleccionar datos (zona, fecha y usar abono)
	JPanel reserva = new JPanel(); /*JPanel exclusivo para aceptar o rechazar reservas*/
	boolean mReserva = false; /*modo reserva para saber de donde sacar el texto*/
	/*botones necesarios para el panel de intr tarjeta*/
	private JTextField cvv = new JTextField(10); //para poner el cvv
	private JTextField nTarjeta = new JTextField(10); //para poner el nTarjeta
	private JTextField fCaducidad = new JTextField(10); //para intr la fecha de caducidad
	private JButton sTarjeta = new JButton("Tarjetas"); //para seleccionar una de las tarjetas
	private JButton proceder = new JButton("Proceder"); //para proceder
	private JButton reservar = new JButton("Reservar");
	
	/*botones necesarios para seleccionar los datos del evento*/
	private JButton abono = new JButton("Abono");
	private JButton fecha = new JButton("Seleccionar fecha");
	private JButton zona = new JButton("Seleccionar Zona");
	private JButton next = new JButton("continuar"); //para pasar a int tarjeta
	private JButton addLista = new JButton("L. Espera"); //para añadir a la lista de espera
	private JPanel main;
	private UICompra ui;
	
	/*copia de botones para reserva*/
	private JButton abono_2 = new JButton("Abono");
	private JTextField cvv_2 = new JTextField(10); //para poner el cvv
	private JTextField nTarjeta_2 = new JTextField(10); //para poner el nTarjeta
	private JTextField fCaducidad_2 = new JTextField(10); //para intr la fecha de caducidad
	private JButton sTarjeta_2 = new JButton("Tarjetas"); //para seleccionar una de las tarjetas
	private JButton proceder_2 = new JButton("Proceder"); //para proceder
	private JButton liberar = new JButton("Liberar Reserva"); //para liberar la reserva
	/**
	 * 
	 */
	public boolean getMReserva() {
		return this.mReserva;
	}
	public UICompra_south(UICompra ui) {
		this.setUi(ui);
	}
	
	public String getFechaCaducidad() {
		if(mReserva){
			return this.fCaducidad_2.getText();
		}
		return this.fCaducidad.getText();
	}
	public String getCVV() {
		if(mReserva) {
			return this.fCaducidad_2.getText();
		}
		return this.cvv.getText();
	}
	public String getnTarjeta() {
		if(mReserva) {
			return this.nTarjeta_2.getText();
		}
		return this.nTarjeta.getText();
	}

	
	public void setControlador(ControlSeleccionarTarjeta controlSTarejta, ControlSeleccionarZona zona, ControlSeleccionarRepresentacion rep, ControlSeleccionarAbono cab, ControlNext cn, ControlAñadirListaEspera cAE, ControlProceder cp, ControlReserva cres, ControlLiberarReserva clr) {
		this.sTarjeta.addActionListener(controlSTarejta);
		this.sTarjeta_2.addActionListener(controlSTarejta);
		this.zona.addActionListener(zona);
		this.fecha.addActionListener(rep);
		this.abono.addActionListener(cab);
		this.abono_2.addActionListener(cab);
		this.next.addActionListener(cn);
		this.addLista.addActionListener(cAE);
		this.proceder.addActionListener(cp);
		this.proceder_2.addActionListener(cp);
		this.reservar.addActionListener(cres);
		this.liberar.addActionListener(clr);
	}
	
	private static final long serialVersionUID = -4391841094348300046L;
	public UICompra_south() {
		main=new JPanel();
		main.setLayout(l); /*estableces el cardLayout*/
		main.add(int_tarjeta, "tarjeta");
		int_tarjeta.setLayout(new GridLayout(2, 5));
		JLabel seleccionarT = new JLabel("Seleccionar Tarjeta");
		seleccionarT.setHorizontalAlignment(JLabel.CENTER);
		int_tarjeta.add(seleccionarT);
		JLabel CVV = new JLabel("CVV");
		CVV.setHorizontalAlignment(JLabel.CENTER);
		int_tarjeta.add(CVV);
		JLabel ntarjeta = new JLabel("Nº Tarjeta");
		ntarjeta.setHorizontalAlignment(JLabel.CENTER);
		int_tarjeta.add(ntarjeta);
		JLabel fcaducidad = new JLabel("Fecha de Caducidad");
		fcaducidad.setHorizontalAlignment(JLabel.CENTER);
		int_tarjeta.add(fcaducidad);
		int_tarjeta.add(reservar);
		int_tarjeta.add(sTarjeta);
		int_tarjeta.add(cvv);
		int_tarjeta.add(nTarjeta);
		int_tarjeta.add(fCaducidad);
		int_tarjeta.add(proceder);
		
		selec_datos.setLayout(new GridLayout(1, 4));
		selec_datos.add(abono);
		selec_datos.add(fecha);
		selec_datos.add(zona);
		selec_datos.add(addLista);
		selec_datos.add(next);
		
		main.add(selec_datos, "Seleccionar datos");
		main.setVisible(true);
		this.mostrarPanel("Seleccionar datos");
		this.add(main);
		main.setPreferredSize(new Dimension(570, 55));
		this.setViewportView(main);
		
		
		reserva.setLayout(new GridLayout(2, 6));
		main.add(reserva, "reserva");
		JLabel seleccionarT_2 = new JLabel("Seleccionar Tarjeta");
		seleccionarT_2.setHorizontalAlignment(JLabel.CENTER);
		reserva.add(seleccionarT_2);
		JLabel CVV_2 = new JLabel("CVV");
		CVV_2.setHorizontalAlignment(JLabel.CENTER);
		reserva.add(CVV_2);
		JLabel ntarjeta_2 = new JLabel("Nº Tarjeta");
		ntarjeta_2.setHorizontalAlignment(JLabel.CENTER);
		reserva.add(ntarjeta_2);
		JLabel fcaducidad_2 = new JLabel("Fecha de Caducidad");
		fcaducidad.setHorizontalAlignment(JLabel.CENTER);
		reserva.add(fcaducidad_2);
		reserva.add(new JLabel());
		reserva.add(liberar);
		reserva.add(sTarjeta_2);
		reserva.add(cvv_2);
		reserva.add(nTarjeta_2);
		reserva.add(fCaducidad_2);
		reserva.add(abono_2);
		reserva.add(proceder_2);
		this.mostrarPanel("reserva");
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new UICompra_south());
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.setPreferredSize(new Dimension(200, 200));
		//dimensiones mínimas para el login
		ventana.pack();
		return;
	}
	public void mostrarPanel(String nombre) {
		this.l.show(main, nombre);
	}
	public void quitarReserva() {
		this.reservar.setVisible(false);
	}
	public void ponerReserva() {
		this.reservar.setVisible(true);
	}
	public void prepararCompraAbono() {
		this.mReserva = false;
		this.mostrarPanel("tarjeta");
		this.quitarReserva(); //no existe la opción de reservar en un abono
	}
	public void prepararCompraEntrada() {
		this.mReserva = false;
		this.mostrarPanel("Seleccionar datos");
		this.ponerReserva();
	}
	public void prepararCompraReserva() {
		this.mReserva = true;
		this.mostrarPanel("reserva");
	}
	public UICompra getUi() {
		return ui;
	}
	public void setUi(UICompra ui) {
		this.ui = ui;
	}
	
}
