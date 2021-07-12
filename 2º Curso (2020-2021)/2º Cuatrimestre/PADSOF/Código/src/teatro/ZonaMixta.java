package teatro;

import java.util.ArrayList;
import java.util.List;

import entrada.Entrada;
import ui.control.compra.ControlCompra;

/**
 * Zona que puede contener a su vez otras zonas
 * implementa el composite
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ZonaMixta extends Zona{
	private static final long serialVersionUID = 5427917738359411928L;
	private List<Zona> composite;
	public ZonaMixta(String nombre) {
		super(nombre);
		this.setComposite(new ArrayList<Zona>());
	}

	@Override
	public int compareTo(Zona arg0) {
		return super.comparteTo(arg0);
	}

	@Override
	public int getMax() {
		int max = 0;
		for(Zona z : this.composite) {
			max+=z.getMax();
		}
		return max;
	}

	@Override
	public void mostrarZona() {
		System.out.println(this.getNombre());
		for(Zona z : this.composite) {
			z.mostrarZona();
		}
		
	}

	@Override
	public Entrada factoryEntrada(ControlCompra cc) throws Exception {
		return null;
	}

	@Override
	public void actLimitaciones() {
		/*actualizamos las limitaciones de todas las zonas que están dentro de zona mixta*/
		for(Zona z : this.composite) {
			z.actLimitaciones();
		}
		
	}

	public List<Zona> getComposite() {
		return composite;
	}

	public void setComposite(List<Zona> composite) {
		this.composite = composite;
	}
	
	/**
	 * Método para añadir zonas al composite
	 * @param z zona a añadir en la zona mixta
	 */
	public void addZona(Zona z) {
		if(z==null)	return;
		if(this.composite.contains(z)) {
			return;
		}
		this.composite.add(z);
	}
	
	/**
	 * Método para borrar zonas de la zona mixta
	 * @param z
	 */
	public void removeZonas(Zona z) {
		if(z==null)	return;
		if(!this.composite.contains(z)) {
			return;
		}
		this.composite.remove(z);
	}

}
