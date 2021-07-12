package ui.view.usuario;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.Abono;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import evento.Concierto;
import evento.Evento;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import ui.control.ControlBack;
import ui.control.usuario.ControlUsuario;
import usuario.Usuario;

public class InfoAbono extends JScrollPane{

	/**
	 * 
	 */
	private static final long serialVersionUID = -4761272741429800603L;
	private JPanel principal = new JPanel();
	private JLabel nombre = new JLabel("Abono:");
	private JLabel codigo = new JLabel("-Código: ?");
	private JLabel caducidad = new JLabel("-Caducidad: ?");
	private JLabel zona = new JLabel("-Zona");
	private JLabel tipo = new JLabel("-Tipo: ?");
	private JLabel descuento = new JLabel("");
	private JLabel evento = new JLabel("");
	
	JPanel main_second = new JPanel();
	JScrollPane second = new JScrollPane();
	private ControlUsuario cu;
	private JButton back = new JButton();
	private Abono aux;
	
	public JLabel getZona() {
		return this.zona;
	}
	
	public JLabel getTipo() {
		return this.tipo;
	}
	public JLabel getCodigo() {
		return codigo;
	}

	public JLabel getCaducidad() {
		return caducidad;
	}

	public JLabel getDescuento() {
		return descuento;
	}

	public JLabel getEvento() {
		return evento;
	}

	public JPanel getMain_second() {
		return main_second;
	}

	public void setControlador(ControlBack cb, ControlUsuario cu) {
		this.back.addActionListener(cb);
		this.cu = cu;
	}
	
	public InfoAbono(){ 
		JPanel main = new JPanel();
		nombre.setFont(new Font("Serif", Font.BOLD, 15));
		nombre.setHorizontalAlignment(JLabel.CENTER);
		caducidad.setHorizontalAlignment(JLabel.CENTER);
		codigo.setHorizontalAlignment(JLabel.CENTER);
		tipo.setHorizontalAlignment(JLabel.CENTER);
		zona.setHorizontalAlignment(JLabel.CENTER);
		descuento.setHorizontalAlignment(JLabel.CENTER);
		evento.setHorizontalAlignment(JLabel.CENTER);
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		AbonoUsuario abono=null;
		
		if(cu!=null) {
			abono = cu.getAseleccionado();
			setAux(abono.getAbono());
		}
			
		principal.setLayout(new BorderLayout());
		
		main.setLayout(new GridLayout(7, 1));
		main.add(nombre);
		main.add(codigo);
		main.add(caducidad);
		main.add(tipo);
		main.add(zona);
		main.add(descuento);
		main.add(evento);
		
		principal.add(second, BorderLayout.CENTER);
		second.add(main_second);
		second.setViewportView(main_second);
		main_second.setVisible(true);
		principal.add(main, BorderLayout.NORTH);
		principal.add(back, BorderLayout.SOUTH);
		principal.setVisible(true);
		this.add(principal);
		main.setPreferredSize(new Dimension(600, 300));
		if(abono!=null) {
			abono.dataAbonoUI(this);
		}
		this.setViewportView(principal);
	}
	
	public void update() {
		AbonoUsuario abono=null;
		if(cu!=null)
			abono = cu.getAseleccionado();
		if(abono!=null) {
			abono.dataAbonoUI(this);
		}
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_InfoAbono");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			Usuario u = new Usuario("paco", "pswd");
			Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			Evento ev2 = new Concierto("Concierto de prueba2", 15, "C2", "DGRA", "CerraOrquestas", "Germaon", "Wilalyrex");
			Zona z = new ZonaNoNumerada("hola", 50);
			ArrayList<Evento> eventos = new ArrayList<>();
			eventos.add(ev1);
			eventos.add(ev2);
			for(int i=0; i!=100; i++) {
				Evento evento = new Concierto("Concierto de prueba " + i, 15, "C " + i+3, "DGR", "CerraOrquesta", "German", "Willyrex");
				eventos.add(evento);
			}
			AbonoUsuario abc = new AbonoUsuario(new AbonoCiclo(50.0, eventos, z));
			u.addAbonos(abc);
			c.add(new InfoAbono()); 
		} catch (Exception e) {
			System.out.println(e);
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}

	public Abono getAux() {
		return aux;
	}

	public void setAux(Abono aux) {
		this.aux = aux;
	}
}