package pr3.trafico.multas;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

import pr3.trafico.vehiculos.Vehiculo;
import pr3.trafico.conductores.*;

public class ProcesadorMultas {
    List<Vehiculo> vehiculos;

    public ProcesadorMultas(List<Vehiculo> vehiculos) {
        this.vehiculos = vehiculos;
    }

    public void procesar(List<Multa> multas) {
        Persona conductor = null;
        Vehiculo veh = null;
        for (Multa m : multas) { /*para cada una de las multas*/
            for (Vehiculo v : this.vehiculos) { /*buca el vehículo asociado a esa multa*/
                if (v.getMatricula().equals(m.getMatricula())) { /*si lo encuentra*/
                	veh = v;
                    if((conductor = v.getConductor())==null){ /*si no tiene dueño se toman acciones legales*/
                      System.out.println("No hay ningun conductor asociado. La DGT tomara acciones legales.");  
                    }
                    break;
                }
            }
            if(conductor!=null){
            	if(veh.cadITV()==false) { /*si no está caducada la itv*/
            		System.out.println("El conductor " + conductor.getNombre() + " pierde " + m.getPuntos());
            	}
            	else { /*si está caducada la itv*/
            		System.out.println("El conductor " + conductor.getNombre() + " pierde " + m.getPuntos() + " más otro punto por itv caducada");
            		//System.out.println("El conductor " + conductor.getNombre() + " pierde " + m.getPuntos());
            		m.addITVCad(); //se añade el punto por itv caducada
            		this.infrITVCad(m);
            		
            	}
                System.out.println("El conductor " + conductor.getNombre() + " pierde " + m.getPuntos());
                if(conductor.getCarnet().getPuntos()==0){
                    conductor.getCarnet().setSuspendido();
                    System.out.println("Queda suspendido el carnet del conductor "+ conductor.getNombre());
                    continue;
                }
                conductor.getCarnet().setPuntos(Math.max(conductor.getCarnet().getPuntos() - m.getPuntos(), 0)); //no puede tener puntos negativos
                if(conductor.getCarnet().getPuntos()==0){
                    System.out.println("El conductor " + conductor.getNombre() + " queda " + conductor.getCarnet().getPuntos());
                }
            }
        }
    }
    private void infrITVCad(Multa m) {
    	String esc = new String();
    	esc = m.getMatricula() + ";" + m.getTipo() + ";" + m.getPuntos() + '\n'; 
    	try {
			FileWriter w = new FileWriter("ITV_caducada.txt", true); /*modo append por si ya existe*/
			w.write(esc); /*escribimos la multa con el mismo formato que se nos da en multas*/
			w.close(); /*cerramos el fichero de texto*/
		} catch (IOException e) {
			System.out.println("ERROR" + e.getMessage());
			return;
		}
    	
    }
}