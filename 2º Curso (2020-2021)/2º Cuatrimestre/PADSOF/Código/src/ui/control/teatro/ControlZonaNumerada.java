package ui.control.teatro;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JPanel;

import teatro.Butaca;
import teatro.ZonaNumerada;
import ui.view.teatro.UIZonaNumerada;
public class ControlZonaNumerada implements ActionListener{
	private UIZonaNumerada vista=null;
	private ZonaNumerada z=null;
	
	public ControlZonaNumerada(UIZonaNumerada v){
		if(v==null) {
			return;
		}
		this.vista=v;
		this.z=v.getZona();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		ActionListener AButacas = new ControlButaca(this.z);
		//System.out.println(this.vista.getButacas().size() + "Filas: " + vista.getZona().getFilas());
		ArrayList<JButton> butacas = (ArrayList<JButton>) vista.getButacas();
		Butaca[][] matriz;
		//actualizamos en función de lo que recibimos
		switch (((JButton)arg0.getSource()).getText()) {
		case "Add Row": /*en función de la instrucción recibida hace una u otra acción*/
			z.addFila(); //añaimos una fila a la zona
			break;
		case "Add Col":
			z.addColumna();
			break;
		case "Del Row":
			z.quitarFila();
			break;
		case "Del Col":
			z.quitarColumna();
			break;
		default:
			return;
		}
		
		//actualizamos la vista
		int filas=this.z.getFilas();
		int columnas=this.z.getColumnas();
		matriz=this.z.getButacas();
		String maxText = new String();
		//obtienes el panel principal
		//obtienes su layout
		BorderLayout Bl = (BorderLayout) vista.getMain().getLayout();
		//obtienes el elemento del centro
		JPanel center = (JPanel) Bl.getLayoutComponent(BorderLayout.CENTER);
		butacas.clear();
		center.setLayout(new GridLayout(filas, columnas)); //hacemos un grid layout con todas las filas y columnas de la zona
		center.removeAll();
		for(int i=0; i!=filas; i++) { //vas poniendoles de nombre su posición (fila y columna)
			for(int j=0; j!=columnas; j++) {
				JButton butaca = new JButton(i + ":" + j);
				if(butaca.getText().length()>maxText.length()) {
					maxText = butaca.getText();
				}
				butaca.setFont(new Font("Arial", Font.PLAIN, 10));
					if(matriz[i][j]!=null) {
					if(matriz[i][j].isActiva()==false) {
						butaca.setBackground(Color.RED); //Red si no está activa
					}else {
						butaca.setBackground(Color.GREEN); //Green si está activa
					}
				}
					else {
						butaca.setBackground(Color.GRAY); //Gray si no hay butaca
					}
				butaca.addActionListener(AButacas);
				center.add(butaca);
				butacas.add(butaca);
			}
		}
		//se actualiza la impresión
		this.vista.validate();
		this.vista.repaint();
		if(butacas.size()!=0)
			this.vista.getMain().setPreferredSize(new Dimension(Math.max(columnas*maxText.length()*16, this.z.getNombre().length()*16 + 150), filas*40));
		else this.vista.getMain().setPreferredSize(new Dimension(Math.max(270, this.z.getNombre().length()*16 + 45), 100));
		this.vista.setViewportView(this.vista.getMain());
		//this.vista.setSize(new Dimension(100, 200));
	}
}
