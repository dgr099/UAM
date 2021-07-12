package prac2.trafico;
public class prueba2 {
    public static void main(String[] args) {
   Coche fiat500x = new Coche("Fiat 500x", 2019, "1245 HYN", true);
   Motocicleta moto1 = new Motocicleta("Harley Davidson", 2003, "0987 ETG", false);
   Motocicleta moto2 = new Motocicleta("Torrot Muvi", 2015, "9023 MCV", true);
   Camion camion1 = new Camion("MAN TGA410", 2000, "M-3456-JZ", 3);
   Camion camion2 = new Camion("Iveco Daily", 2010, "5643 KOI", 2);
   Vehiculo [] vehiculos = { fiat500x, moto1, moto2, camion1, camion2 };
   for (Vehiculo v : vehiculos )
   System.out.println(v);
    }
   }