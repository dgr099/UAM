package ui.view.usuario;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Image;
import java.util.Calendar;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

import entrada.Entrada;
import entrada.EntradaZonaNoNumerada;
import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import teatro.Teatro;
import teatro.ZonaNoNumerada;
import ui.control.ControlBack;
import ui.control.usuario.ControlBorrarComentario;
import ui.control.usuario.ControlComentario;
import ui.control.usuario.ControlUsuario;
import ui.control.usuario.ControlValoracion;

public class InfoEntrada extends JScrollPane{
	JButton back = new JButton();
	private ControlUsuario cu;
	private JPanel principal = new JPanel();
	private JLabel entrada = new JLabel("Entrada:");
	private JLabel zona = new JLabel("-Zona: " + "?");
	private JLabel evento = new JLabel("-Evento: " + "?");
	private JLabel fecha = new JLabel("-Fecha: " + "?"); 
	private JLabel codigo = new JLabel("-Código: " + "?");
	private JLabel precio = new JLabel("-Precio: " + "?");
	private JLabel butaca = new JLabel();
	private JTextField valoracion = new JTextField("Puntue del 1 al 5 el evento");
	private JButton comentario = new JButton("Add Comentario");
	private JButton delComentario = new JButton("Del Comentario");
	JTextArea main_second = new JTextArea("Escriba su comentario, click en add comentario para enviar"); /*para poner los comentarios*/
	JPanel main = new JPanel();
	/**
	 * 
	 */
	private static final long serialVersionUID = -4761272741429800603L;
	
	/**
	 * Método para obtener el text área
	 * @return el text area donde se escribe el comentario
	 */
	public JTextArea getTextArea() {
		return this.main_second;
	}
	public void setControlador(ControlBack cb, ControlUsuario cu, ControlComentario cc, ControlBorrarComentario cbc, ControlValoracion cv) {
		this.back.addActionListener(cb);
		this.cu = cu;
		this.comentario.addActionListener(cc);
		this.delComentario.addActionListener(cbc);
		this.valoracion.addActionListener(cv);
	}
	
	public InfoEntrada(){
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		Entrada e = null;
		if(cu!=null)
			e = cu.getEseleccionada();
		SpringLayout sl = new SpringLayout();
		entrada.setFont(new Font("Serif", Font.BOLD, 15));
		if(e != null) {
			String text = "-Zona: " + e.getZona();
			zona.setText(text);
			text = "-Evento: " + e.getEventName();
			evento.setText(text);
			text = "-Fecha: " + e.getEventDate();
			fecha.setText(text);
			text = "-Código: " + e.getCodigo();
			codigo.setText(text);
			text = "-Precio: " + e.getPrecio();
			precio.setText(text);
			if(e.getButaca() != null) {
				text = "-Butaca: " + e.getButaca();
				butaca.setText(text);
			}
		}

		main.setLayout(sl); 
		main.add(entrada);
		main.add(zona);
		main.add(evento);
		main.add(fecha);
		main.add(codigo);
		main.add(precio);
		main.add(butaca);
		main.add(comentario);
		main.add(valoracion);
		main.add(delComentario);
		
		JLabel val = new JLabel("Estrellas:");
		main.add(val);
		sl.putConstraint(SpringLayout.NORTH, entrada, 5, SpringLayout.NORTH, principal);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, entrada, 0, SpringLayout.HORIZONTAL_CENTER, main);
		
		sl.putConstraint(SpringLayout.NORTH, zona, 5, SpringLayout.SOUTH, entrada);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, zona, 0, SpringLayout.HORIZONTAL_CENTER, main);
	
		sl.putConstraint(SpringLayout.NORTH, evento, 5, SpringLayout.SOUTH, zona);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, evento, 0, SpringLayout.HORIZONTAL_CENTER, main);

		sl.putConstraint(SpringLayout.NORTH, fecha, 5, SpringLayout.SOUTH, evento);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, fecha, 0, SpringLayout.HORIZONTAL_CENTER, main);
		
		sl.putConstraint(SpringLayout.NORTH, codigo, 5, SpringLayout.SOUTH, fecha);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, codigo, 0, SpringLayout.HORIZONTAL_CENTER, main);
		
		sl.putConstraint(SpringLayout.NORTH, precio, 5, SpringLayout.SOUTH, codigo);
		sl.putConstraint(SpringLayout.HORIZONTAL_CENTER, precio, 0, SpringLayout.HORIZONTAL_CENTER, main);
		
		sl.putConstraint(SpringLayout.NORTH, valoracion, 5, SpringLayout.SOUTH, precio);
		sl.putConstraint(SpringLayout.WEST, valoracion, 5, SpringLayout.EAST, val);
		sl.putConstraint(SpringLayout.SOUTH, valoracion, -5, SpringLayout.SOUTH, main);
		sl.putConstraint(SpringLayout.EAST, valoracion, -5, SpringLayout.EAST, main);

		sl.putConstraint(SpringLayout.NORTH, val, 5, SpringLayout.SOUTH, precio);
		sl.putConstraint(SpringLayout.WEST, val, 5, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.SOUTH, val, -5, SpringLayout.SOUTH, main);
		
		sl.putConstraint(SpringLayout.NORTH, comentario, 0, SpringLayout.NORTH, valoracion);
		sl.putConstraint(SpringLayout.EAST, comentario, -5, SpringLayout.HORIZONTAL_CENTER, main);
		sl.putConstraint(SpringLayout.SOUTH, comentario, -5, SpringLayout.SOUTH, main);
		
		sl.putConstraint(SpringLayout.NORTH, delComentario, 0, SpringLayout.NORTH, valoracion);
		sl.putConstraint(SpringLayout.EAST, delComentario, -5, SpringLayout.WEST, comentario);
		sl.putConstraint(SpringLayout.SOUTH, delComentario, -5, SpringLayout.SOUTH, main);
		sl.putConstraint(SpringLayout.WEST, delComentario, 5, SpringLayout.WEST, main);

		principal.setLayout(new BorderLayout());
		principal.add(main, BorderLayout.NORTH);
		principal.add(main_second, BorderLayout.CENTER);
		principal.add(back, BorderLayout.SOUTH);
		main.setPreferredSize(new Dimension(500, 150));
		this.add(principal);
		this.setViewportView(principal);
		this.revalidate();
		this.update();
	}
	public void update() {
		Entrada e = null;
		if(cu!=null)
			e = cu.getEseleccionada();
		if(e != null) {
			String text = "-Posición: " + e.getPosicion();
			zona.setText(text);
			text = "-Evento: " + e.getEventName();
			evento.setText(text);
			text = "-Fecha: " + e.getEventDate();
			fecha.setText(text);
			text = "-Código: " + e.getCodigo();
			codigo.setText(text);
			text = "-Precio: " + e.getPrecio();
			precio.setText(text);
			if(e.getComentario()!=null) {
				if(e.getComentario().getMode()==1 || e.getComentario().getMode()==4) { /*si el comentario es ya lo han puesto válido 
					   no se permite volver a mandar otro comentario hasta borrar*/
					this.comentario.setVisible(false);
					this.main_second.setEditable(false);
				}
				else {
					this.comentario.setVisible(true);
					main_second.setEditable(true);
				}
				main_second.setText(e.getComentario().getMensaje());
			}
			else {
				this.comentario.setVisible(true);
				main_second.setText("Escriba su comentario, click en add comentario para enviar");
				main_second.setEditable(true);
			}
			if(e.getValoracion()>=0) {
				valoracion.setText(String.valueOf(e.getValoracion()));
			}
			else {
				valoracion.setText("Puntue del 1 al 5 el evento");
			}
			if(e.getButaca() != null) {
				text = "-Butaca: " + e.getButaca();
				butaca.setText(text);
			}
			butaca.setText("");
		}
	}
	
	public String getValoracion() {
		return this.valoracion.getText();
	}
	
	public String getComentario() {
		return this.main_second.getText();
	}
	
	public ControlUsuario getControlUsuario() {
		return this.cu;
	}
	
	public void resetText() {
		this.main_second.setText("Escriba su comentario, click en add comentario para enviar");
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_InfoEntrada");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		
		try {
			Calendar cal= Calendar.getInstance();
			cal.set(2021, 5, 25, 14, 20, 00);
			Representacion r = new Representacion(cal, 50);
			Evento e = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			((Concierto)e).addPieza("Pieza1");
			((Concierto)e).addPieza("Pieza2");
			Teatro teat = new Teatro("Teatro1", 20);
			ZonaNoNumerada z = new ZonaNoNumerada("ZNN1", 30);
			z.setTeatro(teat);
			teat.addZona(z);
			e.addRepresentacion(r);
			e.addPrecioZona(z, 25);
			Entrada ent = null;
			ent = new EntradaZonaNoNumerada(false, r, z);
			ent.setComentario("Todo mu bonito");
			c.add(new InfoEntrada());
		} catch(Exception e) {
			System.out.println(e);
		}
		
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		return;
	}
	
	public JButton	getComentarioButton() {
		return this.comentario;
	}
}