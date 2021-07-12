package pr3.trafico.Race;

import java.io.File;
import java.io.IOException;
import java.util.*;

import pr3.trafico.components.BananaDispenser;
import pr3.trafico.components.Engine;
import pr3.trafico.components.IComponent;
import pr3.trafico.components.InvalidComponentException;
import pr3.trafico.components.Wheels;
import pr3.trafico.components.Window;
import pr3.trafico.vehiculos.*;
/**
 * Clase que contiene los datos y métodos para leer una carrera de un fichero
 *
 * @version 1.0 18 Abr 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class RaceReader {

    /**
     * Constructor de la clase
     * @param fichero nombre del fichero donde está guardada la carrera
     * @return carrera
     * @throws IOException excepcion de input output
     * @throws RaceException excepcion de Race
     */
    static public Race read(String fichero) throws IOException, RaceException{
        File file = new File(fichero);
        Race carrera = null;
        if(fichero==null) {
        	throw new IOException();
        }
        try(Scanner lector = new Scanner(file)) {
            /*primero leemos la longitud*/
        	if(lector.hasNextLine()) {
                try {
					carrera = new Race(Double.parseDouble(lector.nextLine()));
				} catch (Exception e) {
					throw new IOException();
				} /*creamos una carrera pasando la longitud*/
            } else {
                return null;
            }
            
            while(lector.hasNextLine()) { /*mientras queden vehículos por comprobar*/
                StringTokenizer strtok = new StringTokenizer(lector.nextLine(), " "); /*separamos por espacios*/
                int num_v =Integer.parseInt(strtok.nextToken()); /*número de vehículos*/
                String v = strtok.nextToken(); /*tipo de vehículo*/
                double vel = Integer.parseInt(strtok.nextToken()); /*velocidad máxima del vehículo*/
            	List<IComponent> lc = new ArrayList<IComponent>(); /*lista de componentes del vehículo*/
                /*guardas la lista de componentes*/
            	while(strtok.hasMoreElements()) {
            		String comp=strtok.nextToken();
            		if(comp.equals("Wheels")) {
            			lc.add(new Wheels());
            		}
            		else if(comp.equals("Engine")){
            			lc.add(new Engine());
            		}
            		else if(comp.equals("Window")) {
            			lc.add(new Window());
            		}
            		else if(comp.equals("BananaDispenser")) {
            			lc.add(new BananaDispenser());
            		}
            	}
                while((num_v--)!=0) { /*guardas vehículos con esas condiciones el número de veces que digan*/
					RaceReader_aux(carrera, v, vel, lc);
                }  	
            }
        }
        if(carrera.getParticipantes().size()<=2 || carrera.getParticipantes().size()>10) {
        	throw new RaceException("Error en el rango de vehículos");
        }
        return carrera;
    }
    
    /*función auxiliar para generar el vehículo dado los parámetros*/
    /**
     * Funcion auxiliar para generar el vehículo dado los parámetros
     * @param r carrera donde añadir el vehiculo
     * @param type string con el nombre del vehículo
     * @param vel velocidad máxima del vehículo
     * @param lc lista de componentes del vehículo
     * @throws RaceException
     */
    static private void RaceReader_aux(Race r, String type, double vel, List<IComponent> lc) throws RaceException{
    	Vehiculo v;
    	if(type.equals("Car")) {
    		v=new Coche(vel);
    	}
    	else if(type.equals("Truck")) {
			v=new Camion(vel);
    	}
    	else if(type.equals("Motorcycle")) {
    		v = new Motocicleta(vel);
    	}
    	else {
    		throw new RaceException("Tipo de vehículo desconocido");
        }
    	/*añades el vehículo a la carrera*/
    	for(IComponent iC : lc) {
    		try {
				v.addComponent(iC);
			} catch (InvalidComponentException e) {
				System.out.println(e.getMessage());
			}
    	}
    	r.addParticipantes(v);
    }
}
