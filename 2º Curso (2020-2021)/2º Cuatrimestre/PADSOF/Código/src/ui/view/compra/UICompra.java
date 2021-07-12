package ui.view.compra;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Image;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SpringLayout;

import abonos.Abono;
import evento.Evento;
import reserva.Reserva;
import ui.control.ControlCancel;
import ui.control.ControlEvento;
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

/*jthisl con el login*/
public class UICompra extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	private JPanel north = new JPanel();
	private JLabel titulo = new JLabel("titulo");
	private JLabel desc = new JLabel("descripcion");
	private JLabel precio = new JLabel();
	private JPanel val = new JPanel();
	private JLabel valoraciones = new JLabel();
	private UICompra_south south = new UICompra_south();
	private JButton back = new JButton("Cancelar");
	private JButton back2 = new JButton();
	private ControlCompra cc = null;
	private ComentariosEventos comentariosEventos = new ComentariosEventos();
	private SpringLayout s2;
	private JLabel cvv;
	private JLabel numeroTarjeta;
	private JLabel fechaCaducidad;
	
	public boolean getMReserva() {
		return this.south.getMReserva();
	}
	public void setValoracion(double n) {
		this.valoraciones.setText(n + "/5");
	}
	public void noValoraciones() {
		this.valoraciones.setText("Sin valoraciones");
	}
	public void setControlador(ControlEvento ce, ControlBackCompra cbc, ControlCancel cb, ControlCompra c, ControlSeleccionarTarjeta ct, ControlSeleccionarZona cz, ControlSeleccionarRepresentacion cr, ControlSeleccionarAbono ca, ControlNext cn, ControlAñadirListaEspera cAL, ControlProceder cp, ControlReserva creserva, ControlLiberarReserva clr) {
		this.cc = c;
		this.comentariosEventos.setControl(cc, ce);
		this.back2.addActionListener(cbc);
		south.setControlador(ct, cz, cr, ca, cn, cAL, cp, creserva, clr);
		this.back.addActionListener(cb);
	}
	public ControlCompra getControlCompra() {
		return this.cc;
	}
	
	public UICompra_south getSouth() {
		return this.south;
	}
	
	public void setTitulo(String s) {
		if(s!=null) {
			titulo.setText(s);
		}
		this.repaint();
	}
	
	public void setDesc(String s) {
		if(s!=null) {
			desc.setText(s);
		}
		this.repaint();
	}
	
	public void setPrecio(String s) {
		if(s!=null) {
			precio.setText(s);
		}
		this.repaint();
	}

	public UICompra(){ /*constructor*/
		JPanel main = new JPanel();
		SpringLayout sl = new SpringLayout();
		setS2(new SpringLayout());
		setCvv(new JLabel("CVV"));
		setNumeroTarjeta(new JLabel("Nº Tarjeta"));
		setFechaCaducidad(new JLabel("Fecha de caducidad"));
		JLabel estrella = new JLabel();
		estrella.setIcon(new ImageIcon(new ImageIcon("./asserts/star.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); 
		val.add(estrella);
		val.add(valoraciones);
		main.setLayout(new BorderLayout());
		JPanel main_second = new JPanel();
		JScrollPane second = new JScrollPane();
		/*ponemos el back bien bonico*/
		back2.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back2.setOpaque(false);
		back2.setContentAreaFilled(false);
		back2.setBorderPainted(false);
		back2.setSize(10, 10);
		back2.setVisible(false);
		north = new JPanel();
		north.setLayout(sl);
		north.add(titulo);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, titulo, 0, SpringLayout.HORIZONTAL_CENTER, north);
		north.add(desc);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, desc, 0, SpringLayout.HORIZONTAL_CENTER, north);
		sl.putConstraint(SpringLayout.NORTH, desc, 10, SpringLayout.SOUTH, titulo);
		
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, val, 0, SpringLayout.HORIZONTAL_CENTER, north);
		sl.putConstraint(SpringLayout.NORTH, val, 10, SpringLayout.SOUTH, desc);
		north.add(precio);
		north.add(back);
		north.add(back2);
		north.add(val);
		precio.setFont(new Font("Arial", Font.PLAIN, 35));
		
		sl.putConstraint(SpringLayout.NORTH, precio, 10, SpringLayout.SOUTH, val);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, precio, 0, SpringLayout.HORIZONTAL_CENTER, north);
		sl.putConstraint(SpringLayout.WEST, back, 10, SpringLayout.WEST, north);
		sl.putConstraint(SpringLayout.SOUTH, back, 0, SpringLayout.SOUTH, val);
		sl.putConstraint(SpringLayout.WEST, back2, 10, SpringLayout.WEST, north);
		sl.putConstraint(SpringLayout.SOUTH, back2, -10, SpringLayout.NORTH, back);
		
		main_second.setLayout(new BoxLayout(main_second, BoxLayout.Y_AXIS));
		main_second.add(north);
		north.setPreferredSize(new Dimension(200, 380));
		main_second.add(comentariosEventos);
		main_second.setPreferredSize(new Dimension(300, 310));
		second.add(main_second);
		second.setViewportView(main_second);

		main.add(second, BorderLayout.CENTER);
		main.setVisible(true);
		main.add(south, BorderLayout.SOUTH);
		this.add(main);
		//main.setPreferredSize(new Dimension(570, 200));
		this.setViewportView(main);
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		UICompra uicompra = new UICompra();
		c.add(uicompra);
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
		return;
	}
	public void mostrarAtras() {
		this.back2.setVisible(true);
	}
	public void ocultarAtras() {
		this.back2.setVisible(false);
	}
	public void prepararCompraEntrada(Evento e) {
		this.getControlCompra().reset();
		this.getControlCompra().setEvento(e);
		this.getSouth().prepararCompraEntrada();
		this.val.setVisible(true);
		this.desc.setVisible(true);
		this.ocultarAtras();
		this.comentariosEventos.actualizarComentarios();
		this.comentariosEventos.mostrarComentarios();
	}
	public void prepararCompraAbono(Abono a) {
		this.getControlCompra().reset();
		this.getControlCompra().setAbonoComprar(a);
		this.getSouth().prepararCompraAbono();
		this.ocultarAtras();
		double aux;
		if((aux = a.getValoracion())>=-1) {
			this.val.setVisible(true);
			if(aux>=0)
				this.valoraciones.setText(String.valueOf(aux));
			else {
				this.valoraciones.setText("Sin Valoraciones");
			}
		}	else
				this.val.setVisible(false);
		this.comentariosEventos.actualizarEventos();
		this.comentariosEventos.mostrarEventos();
		this.desc.setVisible(false);
	}
	public void prepararCompraReserva(Reserva r) {
		this.getControlCompra().reset();
		this.getControlCompra().setReserva(r);
		this.getControlCompra().setR(r.getRepresentacion());
		this.getControlCompra().setEvento(r.getRepresentacion().getEvento());
		this.getControlCompra().setZ(r.getButaca().getZonaButaca());
		this.getControlCompra().setButaca(r.getButaca());
		this.ocultarAtras();
		this.getSouth().prepararCompraReserva();
		this.val.setVisible(true);
		this.desc.setVisible(true);
		this.comentariosEventos.actualizarComentarios();
		this.comentariosEventos.mostrarComentarios();
	}
	public SpringLayout getS2() {
		return s2;
	}
	public void setS2(SpringLayout s2) {
		this.s2 = s2;
	}
	public JLabel getCvv() {
		return cvv;
	}
	public void setCvv(JLabel cvv) {
		this.cvv = cvv;
	}
	public JLabel getNumeroTarjeta() {
		return numeroTarjeta;
	}
	public void setNumeroTarjeta(JLabel numeroTarjeta) {
		this.numeroTarjeta = numeroTarjeta;
	}
	public JLabel getFechaCaducidad() {
		return fechaCaducidad;
	}
	public void setFechaCaducidad(JLabel fechaCaducidad) {
		this.fechaCaducidad = fechaCaducidad;
	}
}
