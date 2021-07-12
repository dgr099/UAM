package ui.control.admin;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import evento.Concierto;
import evento.Evento;
import sistema.Sistema;
import teatro.Zona;
import ui.view.Ventana;
import ui.view.admin.AddConcierto;

/**
 * Clase con el control para poder crear un concierto
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ControlAddConcierto implements ActionListener{
	
	private AddConcierto vista;
	private JFrame ventana;
	private Ventana v;
	private ControlAddPrecioEvento c;
	
	
	/** Constructor de la clase
	 * @param v ventana de la aplicación
	 */
	public ControlAddConcierto(Ventana v) {
		this.v = v;
	}
	/**
	 * Método para establecer el control add precio de evento que actua tambien como modelo
	 * @param cap
	 */
	public void setControlAddPrecioEvento(ControlAddPrecioEvento cap) {
		this.c = cap;
	}
	/**
	 * Clase interna con el control para cuando se presiona el botón de asignar precio por zonas al evento que se desea crear
	 * @author David Teófilo Garitagoitia Romero
	 *
	 */
	public class ControlAddConcierto2 implements ActionListener{ /*el de crear el evento concierto como tal*/
		@Override
		public void actionPerformed(ActionEvent arg0) {
			Sistema sis = Sistema.getInstancia();
			try {
			Evento e = new Concierto(vista.getDescripcion(), Double.parseDouble(vista.getDuracion()), vista.getTitulo(), vista.getAutor(), vista.getOrquesta(), vista.getDirector(), vista.getSolista());
			Map<Zona, Double> precioZonas = new HashMap<Zona, Double>();
			precioZonas.putAll(c.getPrecio());
			e.setPrecioZonas(precioZonas);
			if(sis.addEvento(e)==false) { /*añade el evento*/
				JOptionPane.showMessageDialog(vista, "Error en la creación del evento, no puede haber dos eventos con mismo nombre", "Error nombre", JOptionPane.ERROR_MESSAGE);			
				return;
			}
			ventana.dispose(); /*cierra la ventana*/
			JOptionPane.showMessageDialog(vista, "El evento ha sido creado satisfactoriamente", "Evento Creado", JOptionPane.INFORMATION_MESSAGE);			
			v.getVistaPrincipal().getCartelera().addElement(e);
			v.getPaginaEliminarEvento().addElement(e);
			v.getVistaPrincipal().getStatListaEventos().addElement(e);
			v.getVistaPrincipal().getMejorValoradosUI().getEventosValorados().addElement(e);
			v.getAddAbonoCiclo().getCheckBoxAbono().addElement(e);
			}
			catch (Exception e) {
				e.printStackTrace();
				JOptionPane.showMessageDialog(vista, "Lo sentimos, no ha sido posible crear el evento.\nAsegurate de rellenar todos los campos.\nRecuerde que la duración debe ser un número", "Sistem Error", JOptionPane.ERROR_MESSAGE);
			}
		}
		
	}
	@Override
	public void actionPerformed(ActionEvent arg0) { /*el de dar al botón de crear que abre una ventana para introducir los datos*/
		JFrame nuevoConcierto = new JFrame(); /*crea un frame donde asignar los valores para el evento*/
		this.ventana = nuevoConcierto;
		AddConcierto ac = new AddConcierto();
		this.vista = ac;
		ac.setControlador(new ControlAddConcierto2(), c);
		nuevoConcierto.getContentPane().add(ac);
		nuevoConcierto.setVisible(true);
		nuevoConcierto.setSize(400, 400);
	
	}
	
}
