package forms;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;


/**
 * Clase Form donde se define el formato de la pregunta
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class Form extends AbstractForm{
	private List< Three<String, Field<?>, Respuesta<?>> > campos; //tres campos, el string de la pregunta, el field y el valor
	//constructor de la clase
	private Map<String, Respuesta<?>> resultados;
	public Form() {
		super();
		this.campos = new ArrayList<Three<String,Field<?>, Respuesta<?>>>();
		this.resultados = new LinkedHashMap<String, Respuesta<?>>();
	}

	/**
	 * Metodo para procesar la pregunta e insertar la respuesta comprobando el formato correcto
	 * @return el resultado del procesamiento
	 */
	public Map<String, Respuesta<?>> exec() {
		@SuppressWarnings("resource")
		Scanner scan = new Scanner(System.in);
		Field<?> campo;
		Boolean succes = false;
		String valor;
		for(Three<String, Field<?>, Respuesta<?>> p : this.campos) {
			succes=false;
			while(succes==false) { //mientrás no ppueda leer el dato correctamente
				System.out.print(p.getFirst() + " > "); //imprime la pregunta
				campo=p.getSecond(); //obtienes el field
				valor = scan.nextLine(); //lees el valor escrito por teclado
				try {//si lanza alguna excepción saltas al catch
					Object o = campo.setValue(valor);
					p.setThird(campo.createRespuesta()); //creamos la respuesta
					p.getThird().setValor(o);
					this.resultados.put(p.getFirst(), p.getThird());	
					succes=true; //si lo consiguio leer
				} catch (Exception e) {
					System.out.println("\nInvalid value: " + valor);
					System.out.println("\t" + e.getMessage()); //imprimes el mensaje de la excepción
				}
			}
		}
		return this.resultados;
	}
	
	/**
	 * Metodo toString
	 */
	public String toString() {
		String f = new String();
		f+="{";
		int i, z;
		for(i=0, z=this.campos.size(); i!=z; i++) {
			Three<String, Field<?>, Respuesta<?>> p = this.campos.get(i);
			f+=p.getFirst()+"="+p.getThird(); //guarda pregunta y resultado
			if(i!=z-1) {
				f+=", ";
			}
		}
		f+="}";
		return f;
		
	}


	/**
	 * Metodo para anyadir la pregunta a la lista
	 * @param question pregunta
	 * @param campo respuesta
	 * @return el propio Form para poder concatenar
	 */
	public Form add(String question, Field<?> campo) {
		Three<String, Field<?>, Respuesta<?>> TrioNuevo = new Three<String, Field<?>, Respuesta<?>>(question, campo, null);
		//Three<String, Field<?>, ?> TrioNuevo = new Three<String, Field<?>, ?>(question, campo, new String());
		if(!this.campos.contains(TrioNuevo)) //si no contiene ya la pregunta
			this.campos.add(TrioNuevo); //añade la nueva pareja a la lista
		return this; //se retorna a si mismo para poder añadir en cadena
	}
}
