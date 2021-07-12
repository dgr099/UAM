package ui.view.teatro;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import sistema.Sistema;

import java.util.List;

import teatro.ZonaNumerada;
import ui.control.compra.ControlSeleccionarButaca;
import ui.control.teatro.ControlButaca;
import ui.control.teatro.ControlQuitarZona;
import ui.control.teatro.ControlZonaNumerada;
import ui.view.compra.UICompra;

import java.awt.Container;

/**
 * Clase con la vista para mostrar la información de una zona numerada
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class UIZonaNumerada extends JScrollPane{

	private static final long serialVersionUID = 4256175980103227849L;
	List<JButton> butacas = new ArrayList<JButton>();
	JButton addRow=new JButton("Add Row");
	JButton addCol = new JButton("Add Col");
	JButton delRow=new JButton("Del Row");
	JButton delCol = new JButton("Del Col");
	JButton delZona = new JButton("Remove");
	UILista padre;
	ZonaNumerada z=null;
	JPanel main=null; //lo guardo para cuando toque repintar
	
	public JPanel getMain() {
		return this.main;
	}
	
	public List<JButton> getButacas(){
		return this.butacas;
	}
	
	public ZonaNumerada getZona() {
		return this.z;
	}
	public UIZonaNumerada(ZonaNumerada z, JFrame frame, UITeatroListaZonasNumeradas p){ /*constructor*/
		if(z==null) {
			return;
		}
		String maxText = new String();
		this.padre = p;
		/*se recoge la información de la zona para la impresión*/
		this.z=z;
		int filas=z.getFilas();
		int columnas=z.getColumnas();
		/*controladores para los botones*/
		ActionListener Abotones = new ControlZonaNumerada(this);
		ActionListener Abutacas = new ControlButaca(this.z);
		/*se establece el action del botón addRow delRow...*/
		this.addRow.addActionListener(Abotones);
		this.delRow.addActionListener(Abotones);
		this.addCol.addActionListener(Abotones);
		this.delCol.addActionListener(Abotones);
		/*se crea el botón de info y se pone bonito*/
		JButton info = new JButton();
		info.setIcon(new ImageIcon(new ImageIcon("./asserts/info.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT))); //ponemos el back con la imagen
		info.setOpaque(false);
		info.setContentAreaFilled(false);
		info.setBorderPainted(false);
		info.setSize(10, 10);
		info.setHorizontalAlignment(JLabel.RIGHT);
		/*se le pone su acción para que se muestre un tutoria de como usar*/
		info.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JOptionPane.showMessageDialog(null, "Verde->buataca activa\nRojo->Butaca inhabilitada\nGris->No hay butaca\nPulsa sobre una butaca para cambiar su estado\nPara respetar limitaciones, algunas butacas solo pasan de inhabilitado o no hay butaca\nAbajo del todo están los botones para añadir o quitar filas y columnas\nLimitaciones actuales: " + Sistema.getInstancia().getTeatro().getLimitaciones(), "INFO", JOptionPane.INFORMATION_MESSAGE);
				//JOptionPane.showMessageDialog(null, "Verde->buataca activa\nRojo->Butaca inhabilitada\nGris->No hay butaca\nPulsa sobre una butaca para cambiar su estado");
			}
		});
		/*el titulo de la zona*/
		JLabel nZona = new JLabel(z.getNombre());
		nZona.setFont(new Font("Serif", Font.PLAIN, 25));
		nZona.setHorizontalAlignment(JLabel.CENTER);
		
		/*panel principal que sera borderLayout y luego se envolverá en un scroll panel*/
		this.main = new JPanel();
		BorderLayout Bl = new BorderLayout();
		main.setLayout(Bl);
		/*definicion del norte donde irá el nombre de la zona y el botón de información*/
		JPanel north = new JPanel();
		//north.setLayout(new SpringLayout());
		north.add(nZona);
		north.add(info);
		north.add(this.delZona);
		this.delZona.addActionListener(new ControlQuitarZona(this.z, frame, this.padre));
		main.add(north, BorderLayout.NORTH);
		/*el centro donde estarán las butacas*/
		JPanel center = new JPanel();
		main.add(center, BorderLayout.CENTER); //otro jpanel con gridLayout en el medio
		//creas todos los botones de las butacas
		center.setLayout(new GridLayout(filas, columnas)); //hacemos un grid layout con todas las filas y columnas de la zona
		for(int i=0; i!=filas; i++) { //vas poniendoles de nombre su posición (fila y columna)
			for(int j=0; j!=columnas; j++) {
				JButton butaca = new JButton(i + ":" + j);
				if(butaca.getText().length()>maxText.length()) {
					maxText=butaca.getText();
				}
				butaca.setFont(new Font("Arial", Font.PLAIN, 10));
					if(this.z.getButacas()[i][j]!=null) {
					if(this.z.getButacas()[i][j].isActiva()==false) {
						butaca.setBackground(Color.RED); //Red si no está activa
					}else {
						butaca.setBackground(Color.GREEN); //Green si está activa
					}
				}
					else {
						butaca.setBackground(Color.GRAY); //Gray si no hay butaca
					}
				butaca.addActionListener(Abutacas);
				this.butacas.add(butaca);
				center.add(butaca);
			}
		}
		JPanel south = new JPanel();
		south.setLayout(new GridLayout(2, 2));
		south.add(addRow);
		south.add(delRow);
		south.add(addCol);
		south.add(delCol);
		main.add(south, BorderLayout.SOUTH);
		main.setVisible(true);
		this.add(main);
		if(butacas.size()!=0)
			//maximo entre el tamaño para que se vean las columnas y el tamaño para que se vea el nombre y el info
			main.setPreferredSize(new Dimension(Math.max(columnas*maxText.length()*16, this.z.getNombre().length()*16 + 150), filas*40));
		else this.main.setPreferredSize(new Dimension(Math.max(270, this.z.getNombre().length()*16 + 150), 100));
		this.setViewportView(main);
		this.setSize(new Dimension(100, 200));
	}
	
	/*a emplear en la compra*/
	public UIZonaNumerada(ZonaNumerada z, UICompra uic, JFrame frame, JFrame frame2){ /*constructor*/
		if(z==null) {
			return;
		}
		String maxText = new String();
		/*se recoge la información de la zona para la impresión*/
		this.z=z;
		int filas=z.getFilas();
		int columnas=z.getColumnas();
		/*controladores para los botones*/
		ActionListener Abutacas = new ControlSeleccionarButaca(uic, frame, frame2);
		/*se establece el action del botón addRow delRow...*/
		/*el titulo de la zona*/
		JLabel nZona = new JLabel(z.getNombre());
		nZona.setFont(new Font("Serif", Font.PLAIN, 25));
		nZona.setHorizontalAlignment(JLabel.CENTER);
		
		/*panel principal que sera borderLayout y luego se envolverá en un scroll panel*/
		this.main = new JPanel();
		BorderLayout Bl = new BorderLayout();
		main.setLayout(Bl);
		/*definicion del norte donde irá el nombre de la zona y el botón de información*/
		JPanel north = new JPanel();
		//north.setLayout(new SpringLayout());
		north.add(nZona);
		main.add(north, BorderLayout.NORTH);
		/*el centro donde estarán las butacas*/
		JPanel center = new JPanel();
		main.add(center, BorderLayout.CENTER); //otro jpanel con gridLayout en el medio
		//creas todos los botones de las butacas
		center.setLayout(new GridLayout(filas, columnas)); //hacemos un grid layout con todas las filas y columnas de la zona
		for(int i=0; i!=filas; i++) { //vas poniendoles de nombre su posición (fila y columna)
			for(int j=0; j!=columnas; j++) {
				JButton butaca = new JButton(i + ":" + j);
				if(butaca.getText().length()>maxText.length()) {
					maxText=butaca.getText();
				}
				butaca.setFont(new Font("Arial", Font.PLAIN, 10));
					if(this.z.getButacas()[i][j]!=null) {
					if(this.z.getButacas()[i][j].isActiva()==false || uic.getControlCompra().getR().getButacasOcupadas().contains(this.z.getButacas()[i][j])) {
						butaca.setBackground(Color.RED); //Red si no está activa
					}else {
						butaca.setBackground(Color.GREEN); //Green si está activa
					}
				}
					else {
						butaca.setBackground(Color.GRAY); //Gray si no hay butaca
					}
				butaca.addActionListener(Abutacas);
				this.butacas.add(butaca);
				center.add(butaca);
			}
		}
		main.setVisible(true);
		this.add(main);
		if(butacas.size()!=0)
			//maximo entre el tamaño para que se vean las columnas y el tamaño para que se vea el nombre y el info
			main.setPreferredSize(new Dimension(Math.max(columnas*maxText.length()*16, this.z.getNombre().length()*16 + 150), filas*40));
		else this.main.setPreferredSize(new Dimension(Math.max(270, this.z.getNombre().length()*16 + 150), 100));
		this.setViewportView(main);
		this.setSize(new Dimension(100, 200));
	}
	
	//main para ver la vista
	public static void main(String... args) throws Exception {
		JFrame ventana = new JFrame("Pruebas_ZonaNumerada");
		ZonaNumerada z = new ZonaNumerada("Zona de Arriba", 5, 5);
		Container c = ventana.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(new UIZonaNumerada(z, ventana, null));
		ventana.setVisible(true);
		ventana.setSize(400, 400);
		//dimensiones mínimas para el login
		//ventana.setMinimumSize(new Dimension(200, 240));
		ventana.pack();
		return;
	}
}
