package ui.view.usuario;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Image;
import java.util.ArrayList;
import java.util.Arrays;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.Abono;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import abonos.Ciclo;
import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import ui.control.ControlBack;
import ui.control.abonos.ControlAbonos;
import usuario.Usuario;

public class InfoCiclo extends JScrollPane{
	/**
	 * 
	 */
	private static final long serialVersionUID = -1221564170513510104L;
	private JLabel titulo = new JLabel("Ciclo: ");
	private JLabel cod = new JLabel("?");
	private DefaultListModel<String> listaAbonosCiclo = new DefaultListModel<>();
	private JList<String> lista = new JList<String>(listaAbonosCiclo);
	private JButton back = new JButton();

	public void setControlador(ControlAbonos csa, ControlBack cb) {
		this.lista.addMouseListener(csa);
		this.back.addActionListener(cb);
	}
	public InfoCiclo() {
		back.setIcon(new ImageIcon(new ImageIcon("./asserts/back.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		back.setOpaque(false);
		back.setContentAreaFilled(false);
		back.setBorderPainted(false);
		back.setSize(10, 10);
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		JPanel north = new JPanel();
		north.setLayout(new BoxLayout(north, BoxLayout.Y_AXIS));
		north.add(titulo);
		JLabel codigo = new JLabel("Codigo:");
		codigo.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		cod.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		titulo.setAlignmentX(JLabel.CENTER_ALIGNMENT);
		north.add(codigo);
		north.add(cod);
		JScrollPane center = new JScrollPane();
		center.add(lista);
		center.setViewportView(lista);
		main.add(north, BorderLayout.NORTH);
		main.add(center, BorderLayout.CENTER);
		center.setPreferredSize(new Dimension(200, 250));
		main.add(back, BorderLayout.SOUTH);
		this.add(main);
		this.setViewportView(main);
	}
	
	public void update(Ciclo c) {
		if(c==null) {
			return;
		}
		this.listaAbonosCiclo.clear();
		for(Abono a : Sistema.getInstancia().getAbonos()) {
			if(a.getCiclo()!=null) {
				if(a.getCiclo().getCod().equals(c.getCod())) {
					listaAbonosCiclo.addElement(a.getCodigo());;
				}
			}
		}
		this.cod.setText(c.getCod());
		this.revalidate();
		this.repaint();
	}
	
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_InfoAbono");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		InfoCiclo ic;
		try {
			Usuario u = new Usuario("paco", "pswd");
			Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			Evento ev2 = new Concierto("Concierto de prueba2", 15, "C2", "DGRA", "CerraOrquestas", "Germaon", "Wilalyrex");
			Ciclo ciclo = new Ciclo(Arrays.asList(ev1, ev2));
			Sistema.getInstancia().addCiclo(ciclo);
			Sistema.getInstancia().addAbono(new AbonoCiclo(15, ciclo, new ZonaNoNumerada("prueba", 2)));
			Zona z = new ZonaNoNumerada("hola", 50);
			ArrayList<Evento> eventos = new ArrayList<>();
			eventos.add(ev1);
			eventos.add(ev2);
			for(int i=0; i!=100; i++) {
				Evento evento = new Concierto("Concierto de prueba " + i, 15, "C " + i+3, "DGR", "CerraOrquesta", "German", "Willyrex");
				eventos.add(evento);
			}
			for(int i=0; i!=50; i++) {
				AbonoUsuario abc = new AbonoUsuario(new AbonoCiclo(50.0, ciclo, z));
				u.addAbonos(abc);
				Sistema.getInstancia().addAbono(abc.getAbono());
			}
			ic = new InfoCiclo();
			ic.update(ciclo);
			c.add(ic); 
		} catch (Exception e) {
			System.out.println(e);
		}
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		ventana.pack();
		return;
	}
}
