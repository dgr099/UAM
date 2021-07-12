package pr3.trafico.multas;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public abstract class LecturaRadares {
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
