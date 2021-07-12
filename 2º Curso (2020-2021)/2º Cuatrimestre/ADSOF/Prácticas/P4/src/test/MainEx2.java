package test;

import java.io.IOException;

import pr3.trafico.Race.Race;
import pr3.trafico.Race.RaceException;
import pr3.trafico.Race.RaceReader;

public class MainEx2 {
	public static void main(String [] args) {
		Race r;
		try {
			r = RaceReader.read(args[0]);
			r.simulate();
		} catch (IOException e) {
			System.out.println("Error reading the file");
		} catch (RaceException e) {
			System.out.println(e);
		}
	}
}