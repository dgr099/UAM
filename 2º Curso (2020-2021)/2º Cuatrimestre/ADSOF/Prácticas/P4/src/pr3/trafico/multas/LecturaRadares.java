package pr3.trafico.multas;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;


/**
 * Clase que contiene los métodos y atributos de la lectura de radares
 * 
 * @version 1.0 30 Mar 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public abstract class LecturaRadares {
	/**
	 * Método para leer las multas a traves de una base de datos
	 * @param fichero nombre del fichero con las multas
	 * @return lista de multas
	 */
	static public ArrayList<Multa> leer(String fichero) {
		List<Multa> multas = new ArrayList<Multa>();
		Multa aux;
		File file = new File(fichero); /*vamos a trafico, luego a pr3 luego a src y finalmente al directorio*/
		//System.out.println(file.exists());
		//System.out.println(file.getAbsolutePath());
		try (Scanner lector = new Scanner(file)) {
			while (lector.hasNextLine()) { /*mientras queden multas por leer*/
				String leido = lector.nextLine(); /*lee la siguiente linea*/
				if((aux=LecturaRadares.generarMulta(leido))==null) { /*comprueba que no hubo error al generar la multa*/
					multas=null; /*si hubo error libera el array de multas*/
					return null; /*retorna null para el control de errores del padre*/
				}
				multas.add(aux);
			}
		} catch (FileNotFoundException e) { /*si hay algún error en la lectura del .txt*/
			return null;
		}
		return (ArrayList<Multa>) multas;

	}
	
	/**
	 * Método para generar una multa a traves de una entrada de una base de datos
	 * @param data string con los diferentes datos de la multa
	 * @return la multa 
	 */
	static private Multa generarMulta(String data) {
		if(data==null){
			return null;
		}
		String matricula = new String();
		String tipoMulta = new String();
		int puntos = 0;
		StringTokenizer strtok = new StringTokenizer(data, ";");
		if(strtok.hasMoreElements()) {
			matricula = strtok.nextToken();
		}else return null;
		
		if(strtok.hasMoreElements()) {
			tipoMulta = strtok.nextToken();
		}else return null;
		
		if(strtok.hasMoreElements()) {
			puntos = Integer.valueOf(strtok.nextToken());
		}else return null;
		Multa m=new Multa(matricula, tipoMulta, puntos);
		return m;
	}
}
