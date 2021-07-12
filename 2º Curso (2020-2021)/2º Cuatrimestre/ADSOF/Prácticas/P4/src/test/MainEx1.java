package test;

import java.io.IOException;

import pr3.trafico.Race.Race;
import pr3.trafico.Race.RaceException;
import pr3.trafico.Race.RaceReader;

public class MainEx1 {
	public static void main(String [] args) {
		Race r;
		try {
			r = RaceReader.read(args[0]);
			System.out.println(r);
		} catch (IOException e) {
			System.out.println("Error reading the file");
		} catch (RaceException e) {
			System.out.println(e);
		}
	}
}