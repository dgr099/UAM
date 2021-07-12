package test;

import java.io.IOException;

import pr3.trafico.Race.Race;
import pr3.trafico.Race.RaceException;
import pr3.trafico.Race.RaceReader;
import pr3.trafico.vehiculos.Vehiculo;

public class testerRace {
	public static void main(String [] args) {
		Race r;
		try {
			r = RaceReader.read("p2.txt");
			for(Vehiculo v : r.getParticipantes()) {
				System.out.println(v.getName());
				System.out.println(v.getComponents());
			}
		} catch (IOException e) {
			System.out.println("Error reading the file");
		} catch (RaceException e) {
			System.out.println(e);
		}
	}
}
