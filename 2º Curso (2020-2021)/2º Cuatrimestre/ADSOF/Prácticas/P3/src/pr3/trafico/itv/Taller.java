package pr3.trafico.itv;

import java.util.ArrayList;
import java.util.List;

import pr3.trafico.vehiculos.Vehiculo;

public class Taller {
    private String nombre;
    private String direccion;
    private String provincia;
    private List<Vehiculo> vehiculosTaller = new ArrayList<Vehiculo>();
    
    public List<Vehiculo> getVehiculosTaller() {
		return vehiculosTaller;
	}
    public void addVehiculo(Vehiculo v) {
    	if(this.vehiculosTaller.contains(v)==true) {
    		return;
    	}
    	this.vehiculosTaller.add(v);
    }
	public Taller(String nombre, String direccion, String provincia) {
        this.nombre = nombre;
        this.direccion = direccion;
        this.provincia = provincia;
    }

	public String getNombre() {
		return nombre;
	}

	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	public String getDireccion() {
		return direccion;
	}

	public void setDireccion(String direccion) {
		this.direccion = direccion;
	}

	public String getProvincia() {
		return provincia;
	}

	public void setProvincia(String provincia) {
		this.provincia = provincia;
	}
    
}