package test;
import java.util.Calendar;
import pr3.trafico.itv.ITV;
import pr3.trafico.itv.Taller;
import pr3.trafico.vehiculos.Camion;
import pr3.trafico.vehiculos.Coche;
import pr3.trafico.vehiculos.Motocicleta;
import pr3.trafico.vehiculos.Vehiculo;
public class TesterITV {
	public static void cocheMotoPrueba() {
		Calendar c= Calendar.getInstance();
		c.set(2005, 4, 10, 2, 0);
		ITV itv = new ITV(c, new Taller("Taller_1", "Calle prueba", "Provincia prueba"), "Todo bien, todo correcto y yo que me alegro");
		Vehiculo v1 = new Coche("Seat", Calendar.getInstance().get(Calendar.YEAR), "matPrueba", false);
		if(ITV.cadITV(v1)==true) { /*el coche es de este año, no necesita tener ITV*/
			System.out.println("ERROR l16");
			return;
		}
		v1 = new Coche("Seat", Calendar.getInstance().get(Calendar.YEAR)-3, "matPrueba", false);
		if(ITV.cadITV(v1)==true) { /*el coche tiene menos de 4 años, aun no tiene que pasar la ITV*/
			System.out.println("ERROR l20");
			return;
		}
		v1 = new Coche("Seat", Calendar.getInstance().get(Calendar.YEAR)-4, "matPrueba", false); /*el coche tiene 4 años, debería tener alguna itv (no es el caso)*/
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l25");
			return;
		}
		v1.addITV(itv); /*añades la itv de 2005 (que no debería añadirse al ser posterior a la matriculación)*/
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l31");
			return;
		}
		if(v1.getITVs().size()!=0) {
			System.out.println("ERROR l35");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR), 4, 10, 2, 0);
		v1.addITV(itv); /*ahora si que se añade y al ser de esta fecha no debería tener problemas*/
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l41");
			return;
		}
		c.set(2017, 4, 10, 2, 0); /*prueba a cambiar la fecha de la itv*/
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l46");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR) - 2, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + 5, Calendar.getInstance().get(Calendar.HOUR), Calendar.getInstance().get(Calendar.MINUTE), Calendar.getInstance().get(Calendar.SECOND)); /*itv justo hace 2 años (un poco más)*/
		//System.out.println(Calendar.getInstance().getTime());
		//System.out.println(c.getTime());
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l53");
			return;
		}
		v1 = new Coche("Seat", 2011, "matPrueba", false); //Coche con 10 años
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, 4, 5, 2, 0);
		v1.addITV(itv);
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l60");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + 2, Calendar.getInstance().get(Calendar.HOUR), Calendar.getInstance().get(Calendar.MINUTE)); /*tiene una itv de hace un año y un poco menos por lo que pasa*/
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l65");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH) - 2, Calendar.getInstance().get(Calendar.HOUR), Calendar.getInstance().get(Calendar.SECOND)); /*tiene una itv de más de un año (caducada)*/
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l70");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR), 4, 10, 2, 0);
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l75");
			return;
		}
		v1 = new Coche("Seat", 2001, "matPrueba", false); //Coche con 10 años
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + 1, Calendar.getInstance().get(Calendar.HOUR), Calendar.getInstance().get(Calendar.SECOND));
		v1.addITV(itv);
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l81");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-2, 4, 5, 2, 0);
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l86");
			return;
		}
		v1 = new Motocicleta("Kawa", 2001, "matPrueba", true);
		v1.addITV(itv);
		if(ITV.cadITV(v1)==false) {
			System.out.println("ERROR l86");
			return;
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + 1, Calendar.getInstance().get(Calendar.HOUR), Calendar.getInstance().get(Calendar.SECOND));
		if(ITV.cadITV(v1)==true) {
			System.out.println("ERROR l81");
			return;
		}		
	}

	public static void camionPrueba() {
		Vehiculo v = new Camion("NoSe", 2000, "MatPrueba", 2); /*10 años, semestral*/
		Calendar c = Calendar.getInstance();
		ITV itv = new ITV(c, new Taller("tall", "Dir", "Prov"), "El tubo de escape mejorable");
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l109");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-5, 4);
		v.addITV(itv);
		if(ITV.cadITV(v) == true) {
			System.out.println("Error l111");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-7, 4);
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l115");
		}
		v = new Camion("NoSe", Calendar.getInstance().get(Calendar.YEAR)-2, "MatPrueba", 2);
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l119");
		}
		v = new Camion("NoSe", Calendar.getInstance().get(Calendar.YEAR)-3, "MatPrueba", 2);
		v.addITV(itv);
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-7, 4);
		if(ITV.cadITV(v) == true) {
			System.out.println("Error l125");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH)+2);
		if(ITV.cadITV(v) == true) {
			System.out.println("Error l129");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-2, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH)-1);
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l133");
		}
		v = new Camion("NoSe", Calendar.getInstance().get(Calendar.YEAR)-7, "MatPrueba", 2);
		c.set(Calendar.getInstance().get(Calendar.YEAR)-2, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH)-1);
		v.addITV(itv);
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l138");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH)+1);
		if(ITV.cadITV(v) == true) {
			System.out.println("Error l142");
		}
		v = new Camion("NoSe", Calendar.getInstance().get(Calendar.YEAR)-11, "MatPrueba", 2);
		v.addITV(itv);
		if(ITV.cadITV(v) == false) {
			System.out.println("Error l149");
		}
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-6, Calendar.getInstance().get(Calendar.DAY_OF_MONTH)+1);
		if(ITV.cadITV(v) == true) {
			System.out.println("Error l149");
		}
		
	}
	public static void testNextITV() {
		Calendar c = Calendar.getInstance();
		ITV itv = new ITV(c, new Taller("tall", "Dir", "Prov"), "El tubo de escape mejorable");
		Vehiculo v = new Camion("NoSe", 2000, "MatPrueba", 2); /*10 años, semestral*/
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*null porque ya la debió de pasar ya*/
		//c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
		v.addITV(itv);
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*acaba de hacer la itv, en 6 meses la siguiente*/
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-2, Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*hizo la itv hace 2 meses, le quedan 4 para la siguiente*/
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-7, Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*hizo la itv hace 7 meses, retorna null porque te pasaste*/
		v=new Coche("Seat", Calendar.getInstance().get(Calendar.YEAR)-1, "mat", true); /*menos de 4 años, luego la itv la pasará cuando pasen los 3 años que le quedan*/
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV());
		v=new Coche("Seat", Calendar.getInstance().get(Calendar.YEAR)-4, "mat", true); /*este ya tiene 4 años*/
		v.addITV(itv);
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*tiene una itv recién pasada, le quedan 2 años para la siguiente*/
		c.set(Calendar.getInstance().get(Calendar.YEAR)-1, Calendar.getInstance().get(Calendar.MONTH), Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*tiene una itv hace 1 año, le queda otro año porque es cada 2 años entre los 4 y 10 años de antiguedad*/
		c.set(Calendar.getInstance().get(Calendar.YEAR), Calendar.getInstance().get(Calendar.MONTH)-6, Calendar.getInstance().get(Calendar.DAY_OF_MONTH));
		System.out.println(v.getAnyoCompra());
		System.out.println(v.nextITV()); /*tiene una itv hace 6 meses, le queda otro año y 6 meses*/

	}
	public static void main(String[] args){
		cocheMotoPrueba();
		camionPrueba();
		testNextITV();
	}
}
