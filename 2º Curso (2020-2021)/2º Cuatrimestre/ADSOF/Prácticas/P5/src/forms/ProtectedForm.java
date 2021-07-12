package forms;

import java.util.Map;
import java.util.Scanner;

/**
 * Clase que sirve como Proxy implementando la protección
 * @version 1.0 6 Mayo 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public class ProtectedForm extends AbstractForm{
	Form formulario; //verdadero recurso
	String contraseña; //contraseña para el test
	String usuario; //contraseña del usuario
	int intentos=3; //intentos para guardar en usuario la contraseña del test
	
	/**
	 * Constructor de la clase
	 * @param formulario recurso para asignar al proxy
	 * @param contraseña contraseña del test
	 */
	public ProtectedForm(Form formulario, String contraseña) {
		super();
		this.formulario = formulario;
		this.contraseña = contraseña;
		this.usuario = new String();
	}

	/**
	 * Metodo que sobreescribe el de Form ya que en este caso se pide un password, en caso
	 * de acertar se llama al metodo exec de Form y si se falla 3 veces se bloquea y devuelve null
	 * 
	 * @return llamada al metodo exec de Form, no de ProtectedForm 
	 */
	@Override
	public Map<String, Respuesta<?>> exec() {
		if(this.formulario==null) { //si no hay formulario
			System.out.println("Error no formulario");
			return null;
		}
		@SuppressWarnings("resource")
		Scanner scan = new Scanner(System.in);
		if(usuario.equals(contraseña)) {
			return this.formulario.exec();
		}
		while(intentos>0) {
			System.out.print("Enter password: ");
			usuario = scan.nextLine();
			if(usuario.equals(contraseña)) { //si ya está puesta la contraseña
				break;
			}
			else {
				this.intentos--;
				System.out.println("Invalid password (" + this.intentos + " remaining attempts)");
			}		
		}
		if(intentos==0) {
			System.out.println("Has pasado el número de intentos, cuestionario bloqueado");
			return null;
		}
		return this.formulario.exec();
	}

	/**
	 * Metodo de add de protected form a llamar al de form
	 * @param question pregunta
	 * @param campo formato de respuesta
	 * @return llamada a add de form
	 */
	@Override
	public Form add(String question, Field<?> campo) {
		if(this.formulario==null) {
			System.out.println("Error no formulario");
			return null;
		}
		return this.formulario.add(question, campo);
	}

	/**
	 * Esté método devuelve una instanciación de la clase llamando al constructor con los parámetros introducidos
	 * @version 1.0 6 Mayo 21
	 * @author David Teófilo Garitagoitia Romero
	 * @author Javier Fernandez de Alarcon Gervas
	 * @param enrollForm formulario a proteger
	 * @param string contrasela a introducir en el protected form
	 * @return un objeto de esta clase con la contraseña y formulario introducidos
	 */
	public static AbstractForm protect(Form enrollForm, String string) {
		ProtectedForm pf = new ProtectedForm(enrollForm, string); //construimos un ProtectedForm
		return pf;
	}
		
}
