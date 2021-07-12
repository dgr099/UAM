package forms;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;


/**
 * Clase Field donde se define el formato de las respuestas, no las respuestas
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Field<T extends java.lang.Comparable<T>>{ //T es el valor de respuesta esperado y debe tener implementada la interfaz comparable
	Function<? super String,? extends T> f; //la función para pasar de string a int
	List<Pair<Predicate<T>, Exception>> validations = new ArrayList<Pair<Predicate<T>,Exception>>();
	//cualquier función que permita pasar de un superior de String a un valor igual o más profundo que t nos vale
	Field(Function<? super String,? extends T> f){ //el constructor recibe una función que le permite pasar de string a integer
		this.f = f; 
	}

	/**
	 * Metodo que anyade un nuevo tipo de caracteristicas que tiene que tener una respuesta
	 * @param t la expresion lambda que se tiene que cumplir en la respuesta
	 * @param string mensaje de excepcion que se devuelve en dicho caso
	 * @return el propio Field ya que se usa para concatenar validaciones en el main
	 */
	public Field<T> addValidation(Predicate<T> t, String string) {
		this.validations.add(new Pair<Predicate<T>, Exception>(t, new Exception(string)));
		return this;
	}

	/** 
	 * Metodo para crear un nuevo tipo de respuesta
	 * @return el nuevo tipo
	 */
	public Respuesta<T> createRespuesta(){
		return new Respuesta<T>();
	}

	/**
	 * Metodo para establecer el valor dado a la respuesta, teniendo en cuenta las posibles excepciones
	 * @param v respuesta dada
	 */
	public T setValue(String v) throws Exception {
		if(v==null) {
			throw new Exception("null value");
		}
		T value = this.f.apply(v);
		for(Pair<Predicate<T>, Exception> p : this.validations) {
			if(p.getFirst().test(value)==false)
				throw p.getSecond();	
		}
		return value;
	}
	
	@Override //para que no me ponga varias veces el mismo campo
	public boolean equals(Object p) {
		if(p instanceof Field<?> == false) {
			return false;
		}
		@SuppressWarnings("unchecked")
		Field<T> r = (Field<T>)p; 
		return (this.f.equals(r.f) && this.validations.equals(r.validations));
	}

}
