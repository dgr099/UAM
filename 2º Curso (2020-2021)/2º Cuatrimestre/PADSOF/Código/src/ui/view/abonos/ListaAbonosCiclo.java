package ui.view.abonos;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.Abono;
import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.abonos.ControlAbonos;
import ui.view.teatro.UILista;

/* Vista de la lista de abonos de ciclo */
public class ListaAbonosCiclo extends JScrollPane implements UILista{	
	private static final long serialVersionUID = 650385903029733333L;
	private JPanel main;
	private JLabel titulo = new JLabel("Abonos Ciclo:");
	private JList<String> abonosCicloJList;
	private DefaultListModel<String> abonosCicloList = new DefaultListModel<>();

	/*constructor para utilizar cuando quiere comprar una entrada*/
	public void setControlador(ControlAbonos ca) {
		this.abonosCicloJList.addMouseListener(ca);
	}
	
	/**
	 * Metodo para obtener el abono de ciclo seleccionado
	 * @return Devuelve el abono de ciclo seleccionado
	 */
	public String getAbonoCicloSelectedValue() {
		return this.abonosCicloJList.getSelectedValue();
	}
	
	/*constructor de la vista*/
	public ListaAbonosCiclo(){ 

		main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		abonosCicloJList = new JList<String>(abonosCicloList);
		main.add(abonosCicloJList, BorderLayout.CENTER);
		this.update();
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
		this.setMaximumSize(new Dimension(200, 400));
	}
	
	//main para ver la vista
	public static void main(String... args) {
		JFrame ventana = new JFrame("Pruebas_login");
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		try {
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new ListaAbonosCiclo());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	
	/**
	 * Metodo para añadir un abono a la lista de abonos de ciclo
	 * @param a contiene el abono a introducir
	 */
	public void addElement(Abono a) {
		if(a==null)	return;
		if(this.abonosCicloList.contains(a.getCodigo()))	return;
		this.abonosCicloList.addElement(a.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Metodo para borrar un abono de la lista de abonos de ciclo
	 * @param a contiene el abono a eliminar
	 */
	public void removeElement(Abono a) {
		if(a==null)	return;
		if(this.abonosCicloList.contains(a.getCodigo())) {
			this.abonosCicloList.removeElement(a.getCodigo());
		}
		this.validate();
		this.repaint();
	}
	
	/**
	 * Metodo para actualizar la lista de abonos de ciclo cuando sea necesario
	 */
	@Override
	public void update() {
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getAbonos()!=null) {
			abonosCicloList.clear();
			Sistema.getInstancia().getAbonos().stream().filter(a -> a instanceof AbonoCiclo).forEach(a -> this.abonosCicloList.addElement(a.getCodigo()));
		}
		this.validate();
		this.repaint();
		this.revalidate();
	}
}
