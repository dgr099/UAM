package ui.view;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import abonos.AbonoAnual;
import abonos.Ciclo;
import evento.Concierto;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import ui.control.usuario.ControlSeleccionarCiclo;
import ui.view.teatro.UILista;
/*TODO*/
public class ListaCiclosValorados extends JScrollPane implements UILista{	
	private static final long serialVersionUID = 650385903029733333L;
	private List<Ciclo> ciclosMejorValorados = new ArrayList<Ciclo>(); //lista de los ciclos mejor valorados
	private DefaultListModel<String> ciclosName = new DefaultListModel<>();
	private JPanel main;
	private JLabel titulo = new JLabel("Ciclos:");
	private JList<String> ciclosJList;
	
	public JList<String> getCiclosJList(){
		return this.ciclosJList;
	}
	public void resetSelection() {
		this.ciclosJList.clearSelection();
	}
	public void setControlador(ControlSeleccionarCiclo csc) {
		this.ciclosJList.addMouseListener(csc);
		//this.ciclosJList.addListSelectionListener(csc);
		this.update();
	}
	public String getCicloSelectedValue() {
		return this.ciclosJList.getSelectedValue();
	}
	/*constructor para utilizar cuando quiere comprar una entrada*/
	public ListaCiclosValorados(){ /*constructor*/
		main = new JPanel();
		main.setLayout(new BorderLayout());
		main.add(titulo, BorderLayout.NORTH);
		ciclosJList = new JList<>(ciclosName);
		if(Sistema.getInstancia().getEventos()==null) {
			return;
		}
		main.add(ciclosJList, BorderLayout.CENTER);
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
			for(int i=0; i!=5; i++) {
				Concierto con = new Concierto("des", 20, "prueba" + i, "aut", "orq", "abc", "def");
				con.addValoracion(i);
				Sistema.getInstancia().addEvento(con);
			}
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
			Sistema.getInstancia().addAbono(new AbonoAnual(30, new ZonaNoNumerada("prueba", 30)));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			c.add(new ListaCiclosValorados());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ventana.setVisible(true);
		ventana.setSize(600, 600);
		return;
	}
	
	@Override
	public void update() {
		ciclosName.clear();
		if(Sistema.getInstancia().getEventos()==null) {
			return;
		}
		/*actualizamos la lista de ciclos mejor valorados*/
		ciclosMejorValorados.clear();
		ciclosMejorValorados.addAll(Sistema.getInstancia().getCiclos());
		Collections.sort(ciclosMejorValorados, new Comparator<Ciclo>() {
				@Override
				public int compare(Ciclo arg0, Ciclo arg1) {
					if(arg0.getValoracion() - arg1.getValoracion()>0) {
						return -1;
					}
					return 1;
				}
			}
		);
		/*lo pasamos a la jlist*/
		for(Ciclo c : this.ciclosMejorValorados) {
			double aux;
			if((aux =  c.getValoracion())<0) {
				ciclosName.addElement(c.getCod() + "; " + "Sin Valoraciones");
			}else {
				ciclosName.addElement(c.getCod() + "; " + aux);
			}
		}
		this.validate();
		this.repaint();
		this.revalidate();
	}
	
	/**
	 * Método para añadir elementos a la lista de ciclos
	 * @param c ciclo a añadir
	 */
	public void addElement(Ciclo c) {
		if(c==null || this.ciclosMejorValorados.contains(c)) {
			return;
		}
		double aux;
		if((aux =  c.getValoracion())<0) {
			ciclosName.addElement(c.getCod() + "; " + "Sin Valoraciones");
		}else {
			ciclosName.addElement(c.getCod() + "; " + aux);
		}
		this.validate();
		this.repaint();
		
	}
	
	/**
	 * Método para quitar un ciclo de la lista
	 * @param c Ciclo a quitar
	 */
	public void removeElement(Ciclo c) {
		if(c==null || !this.ciclosMejorValorados.contains(c)) {
			return;
		}
		for(int i=0; i!=this.ciclosName.size(); i++) {
			if(this.ciclosName.getElementAt(i).contains(c.getCod())) {
				this.ciclosName.removeElementAt(i);
				break;
			}
		}
		this.ciclosMejorValorados.remove(c);
		this.validate();
		this.repaint();
	}
}
