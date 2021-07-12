import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Clase que contiene dos sets (uno de numero pares y otro de impares), y cuenta
 * con métodos para añadir números y obtener los sets y las sumas de ellos
 *
 * @version 1.0 17 Feb 20
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class OrdenaYSuma {
	private SortedSet<Integer> pares = new TreeSet<>(); // Set que contiene los números pares
	private SortedSet<Integer> impares = new TreeSet<>(); // Set que contiene los números impares

	/**
	 * Constructor, con los array de cadenas
	 * 
	 * @param cadenas a insertar, tras convertir a números
	 */
	public OrdenaYSuma(String... cadenas) {
		for (String s : cadenas) { // recorremos el array
			int n = Integer.parseInt(s); // convertimos a entero
			this.anyade(n);
		}
	}

	/**
	 * Método para obtener el set de los números pares
	 * 
	 * @return la colección de números pares
	 */
	public SortedSet<Integer> getNumerosPares() {
		return this.pares;
	}

	/**
	 * Método para obtener los números impares
	 * 
	 * @return la colección de números impares
	 */
	public SortedSet<Integer> getNumerosImpares() {
		return impares;
	}

	/**
	 * Método para obtener la suma de los números pares
	 * 
	 * @return la suma de los elementos de la coleccion de números pares
	 */
	public Integer getSumaPares() {
		return Suma(1);
	}

	/**
	 * Método para obtener la suma de los números impares
	 * 
	 * @return la suma de los elementos de la coleccion de números impares
	 */
	public Integer getSumaImpares() {
		return Suma(0);
	}

	private Integer Suma(int opc){
		SortedSet<Integer> conj;
		int suma=0;
		if(opc==1){
			conj=pares;
		}
		else{
			conj=impares;
		}
		for(int i : conj){
			suma+=i;
		}
		return suma;
	}

	/**
	 * Método para añadir números a la clase
	 * 
	 * @param n numero a insertar en la coleccion
	 */
	public void anyade(Integer n) {
		if (n % 2 == 0) {
			pares.add(n); // añadimos al conjunto de pares si es par
		} else {
			impares.add(n); // añadimos al conjunto de impares en caso contrario
		}
	}

	/**
	 * Método para imprimir la clase (conjunto de pares y su suma, conjunto de impares y su suma)
	 * 
	 * @return Conjunto y suma
	 */
	public String toString() {
		return "Números pares " + this.pares.toString() + " (suma: " + this.getSumaPares() + ")" + "\n"
				+ "Números impares " + this.impares.toString() + " (suma: " + this.getSumaImpares() + ")\n";
				//termina con salto de línea para que el output sea lo más similar posible al ejemplo
	}

	public static void main(String... args) {
		if (args.length < 2) {
			System.out.println("Se espera al menos dos números como parámetros");
			System.out.println("Devuelve los números pares e impares ordenados, sin repetidos, y su suma");
		} else {
			OrdenaYSuma c = new OrdenaYSuma(args);
			System.out.println(c); // Imprimimos los conjuntos ordenados y su suma, por salida estándar
			c.anyade(30); // Añade el 30
			c.anyade(33); // Añade el 33
			System.out.println(c); // Imprimimos los conjuntos ordenados y su suma
			System.out.println("Suma pares: " + c.getSumaPares()); // Imprimimos la suma de los pares
			System.out.println("Suma impares: " + c.getSumaImpares()); // Imprimimos la suma de los impares
			System.out.println("Suma total: " + (c.getSumaPares() + c.getSumaImpares())); // suma total
		}
	}
}
