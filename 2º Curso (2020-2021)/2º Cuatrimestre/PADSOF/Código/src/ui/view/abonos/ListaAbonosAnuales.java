package ui.view.abonos;
import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.Abono;
import abonos.AbonoAnual;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.abonos.ControlAbonos;
import ui.view.teatro.UILista;

/* Vista de una lista de abonos anuales */
public class ListaAbonosAnuales extends JScrollPane implements UILista{	
	
	private static final long serialVersionUID = 650385903029733333L;
	private JPanel main;
	private JLabel titulo = new JLabel("Abonos Anuales:");
	private JList<String> abonosAnualesJList;
	private DefaultListModel<String> abonosAnualesList = new DefaultListModel<>();

	/**
	 * Metodo para actualizar el controlador de la lista
	 * @param ca Controlador de la lista de abonos
	 */
	public void setControlador(ControlAbonos ca) {
		this.abonosAnualesJList.addMouseListener(ca);
	}
	
	/**
	 * Metodo para obtener el abono anual seleccionado
	 * @return Devuelve el abono seleccionado
	 */
	public String getAbonoAnualSelected() {
		return this.abonosAnualesJList.getSelectedValue();
	}
	
	/*constructor para utilizar cuando quiere comprar una entrada*/
	public ListaAbonosAnuales(){ /*constructor*/
		abonosAnualesJList = new JList<String>(abonosAnualesList);
		main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		main.add(abonosAnualesJList, BorderLayout.CENTER);
		this.update();
		this.add(main);
		main.setVisible(true);
		this.setViewportView(main);
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
			e1.printStackTrace();
		}
		try {
			c.add(new ListaAbonosAnuales());
		} catch (Exception e) {
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	/**
	 * Método para añadir un abono a la lista
	 * @param a abono a añadir
	 */
	public void addElement(Abono a) {
		if(a==null) {
			return;
		}
		if(this.abonosAnualesList.contains(a.getCodigo())){
			return;
		}
		this.abonosAnualesList.addElement(a.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Método para quitar un abono a la lista
	 * @param a abono a eliminar
	 */
	public void removeElement(Abono a) {
		if(a==null || !this.abonosAnualesList.contains(a.getCodigo())) {
			return;
		}
		this.abonosAnualesList.removeElement(a.getCodigo());
		this.validate();
		this.repaint();
	}
	
	/**
	 * Metodo para actualizar la lista de abonos anuales cuando sea necesario
	 */
	@Override
	public void update() {
		if(Sistema.getInstancia().getTeatro()!=null && Sistema.getInstancia().getAbonos()!=null) {
			abonosAnualesList.clear();
			Sistema.getInstancia().getAbonos().stream().filter(a -> a instanceof AbonoAnual).forEach(a -> this.abonosAnualesList.addElement(a.getCodigo()));
		}
		this.validate();
		this.repaint();
		this.revalidate();
	}
}
