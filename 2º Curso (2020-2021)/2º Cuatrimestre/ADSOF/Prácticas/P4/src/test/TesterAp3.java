package test;

import pr3.trafico.carnet.Carnet;
import pr3.trafico.carnet.TipoLicencia;
import pr3.trafico.conductores.Persona;
import pr3.trafico.vehiculos.Coche;

public class TesterAp3 {
	private void testMenorDe18NoPuedeTenerCarnetA() {
		Persona ana = new Persona("Ana Soler", 17);
		Carnet c = new Carnet(TipoLicencia.A);
		System.out.println("Test: MenorDe18NoPuedeTenerCarnetA");
		System.out.println(c);
		System.out.println(ana.setCarnet(c));		// debe devolver false, porque Ana no tiene 18		
	}
	
	private void testMenorDe23NoPuedeTenerCarnetC1() {
		Persona ana = new Persona("Ana Soler", 19);
		Carnet c = new Carnet(TipoLicencia.A, TipoLicencia.C1);
		System.out.println("=================\nTest: MenorDe18NoPuedeTenerCarnetC1");
		System.out.println(c);			
		System.out.println(ana.setCarnet(c));		// debe devolver false, porque Ana no tiene 23
	}
	
	private void testCarnetParaCategoria() {
		Persona ana = new Persona("Ana Soler", 24);
		ana.setCarnet(new Carnet(TipoLicencia.A, TipoLicencia.C1));
		Coche c = new Coche("Fiat 500x", 2019, "1245 HYN", true, ana);
		System.out.println("=================\nTest: CarnetParaCategoria");
		System.out.println(c);		// ana no es el conductor, porque tiene carnet de moto y cami�n
		ana.getCarnet().addLicencia(TipoLicencia.B);
		c.setConductor(ana);
		System.out.println(c);		// ahora s�
		System.out.println(ana.getCarnet());		// carnet
	}
	
	public static void main(String[] args) {
		TesterAp3 tap3 = new TesterAp3();
		/*tap3.testMenorDe18NoPuedeTenerCarnetA();
		tap3.testMenorDe23NoPuedeTenerCarnetC1();
		tap3.testCarnetParaCategoria();*/
		tap3.testCarnetCoche();
	}
	
	public void testCarnetCoche() {
		Persona ana = new Persona("Ana", 20);
		ana.setCarnet(new Carnet(TipoLicencia.A));
		Coche c = new Coche("Fiat 500x", 2019, "1245 HYN", true, ana);
		c.setConductor(ana);
		System.out.println(c);
		return;
	}
}
