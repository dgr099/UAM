package forms;

/**
 * Clase Pair donde se define una pareja de elementos cualesquiera
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Pair <V, T>{ //pareja 
		V campo;
		T pareja;

		/**
		 * Constructor pareja
		 * @param p primer valor
		 * @param c segundo valor
		 */
		Pair(V p, T c){
			this.campo=p;
			this.pareja=c;
		}
		
		/**
		 * Obtener el primer valor
		 * @return primer valor
		 */
		public V getFirst(){
			return this.campo;
		}
		
		/**
		 * Obtener el segundo valor
		 * @return segundo valor
		 */
		public T getSecond() {
			return this.pareja;
		}
		
		/**
		 * Comprobar si la pareja es igual a otra pareja
		 */
		@Override //para que no me ponga varias veces el mismo
		public boolean equals(Object p) {
			if(p instanceof Pair<?, ?> == false) {
				return false;
			}
			@SuppressWarnings("unchecked")
			Pair <V, T> p2 = (Pair <V, T>) p;
			return (this.getFirst().equals(p2.getFirst()) && this.getSecond().equals(p2.getSecond()));
		}
}
