package test;

import pr3.trafico.carnet.Carnet;
import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.conductores.Persona;
import pr3.trafico.conductores.Sociedad;
import pr3.trafico.vehiculos.Camion;
import pr3.trafico.vehiculos.Coche;
import pr3.trafico.vehiculos.Motocicleta;
import pr3.trafico.vehiculos.Vehiculo;
import pr3.trafico.multas.*;

import java.util.*;

public class TesterMultas {
	public static void main(String[] args) {
		Persona ana = new Persona("Ana Soler", 30);		 // Ana 			
		Persona andres = new Persona("Andres Molina", 27);
		Sociedad edsa = new Sociedad("Entregas a Domicilio S.A.", ana);	// Ana es responsable de EDSA
		
		ana.setCarnet(new Carnet(TipoLicencia.B, TipoLicencia.C1));
		andres.setCarnet(new Carnet(TipoLicencia.A));
		
		Vehiculo parque[] = { 
				new Coche("Fiat 500x", 2019, "1245 HYN", true, ana), // Coche de Ana, que lo conduce	
				new Camion("IvecoDaily", 2010, "5643 KOI", 2, edsa), // Coche de EDSA
				new Motocicleta("Harley Davidson", 2003, "0987 ETG", false, andres),
				new Coche("Volvo XC90", 2018, "1234 XYZ", false, null),
		};
		
		ProcesadorMultas pm = new ProcesadorMultas(Arrays.asList(parque));			
		pm.procesar(LecturaRadares.leer("multas_radar1.txt"));
	}
}
