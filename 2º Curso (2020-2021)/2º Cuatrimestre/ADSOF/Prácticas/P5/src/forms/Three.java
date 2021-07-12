package forms;

/**
 * Clase Three donde se define un trio de elementos cualesquiera
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Three <V, T, Z>{ //pareja 
		V campo;
		T pareja;
		Z valor;

		/**
		 * Constructor de trio de elementos
		 * @param p primer elemento
		 * @param c segundo elemento
		 * @param z tercer elemento
		 */
		Three(V p, T c, Z z){
			this.campo=p;
			this.pareja=c;
			this.valor=z;
		}

		/**
		 * Establecer el valor del tercer elemento
		 * @param object valor tercer elemento
		 */
		public void setThird(Z object) {
			this.valor=object;
		}
		/**
		 * Establecer el valor del primer elemento
		 * @param object valor primer elemento
		 */
		public void setFirst(V v) {
			this.campo=v;
		}

		/**
		 * Establecer el valor del segundo elemento
		 * @param object valor segundo elemento
		 */
		public void setSecond(T t) {
		 this.pareja=t;
		}

		/**
		 * Obtener el valor del primer elemento
		 * @return valor primer elemento
		 */
		public V getFirst(){
			return this.campo;
		}

		/**
		 * Obtener el valor del segundo elemento
		 * @return valor segundo elemento
		 */
		public T getSecond() {
			return this.pareja;
		}
		
		/**
		 * Obtener el valor del tercer elemento
		 * @return valor tercer elemento
		 */
		public Z getThird() {
			return this.valor;
		}
		
		/**
		 * Comprobar si son iguales dos trios de elementos
		 */
		@SuppressWarnings("unchecked")
		@Override //para que no me ponga varias veces el mismo
		public boolean equals(Object p) {
			if(p instanceof Three<?, ?, ?> == false) {
				return false;
			}
			Three <V, T, Z> p2 = ((Three <V, T, Z>) p);
			/*if(this.getThird()!=null && p2.getThird()!=null)
				return (this.getFirst().equals(p2.getFirst()) && this.getSecond().equals(p2.getSecond()) && this.getThird().equals(p2.getThird()));
			*/
			return (this.getFirst().equals(p2.getFirst()) && this.getSecond().equals(p2.getSecond()));
		}
}
