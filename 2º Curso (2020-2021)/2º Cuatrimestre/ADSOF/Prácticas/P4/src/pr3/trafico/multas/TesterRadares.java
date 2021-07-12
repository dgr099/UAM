package pr3.trafico.multas;
import java.util.List;

public class TesterRadares {
	public static void main(String[] args) {
		List<Multa> multas = LecturaRadares.leer("multas_radar1.txt");
		
		for (Multa m : multas) 
			System.out.println(m+"\n------------");		
	}
}
