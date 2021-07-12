package pr3.trafico.vehiculos;

/**
 * Enumeración que contiene los tipos de índice de contaminación junto con los
 * métodos necesarios para conocer el índice de contaminacion dado el año de
 * compra
 *
 * @version 1.0 26 Feb 21
 * @author David Teófilo Garitagoitia Romero
 * @author Javier Fernandez de Alarcon Gervas
 */
public enum IndiceContaminacion {
	A, B, C; //Posibles índices de contaminación

	private static final int FECHAA = 2018; //fecha mínima indice A
	private static final int FECHAB = 2010;	//fecha mínima índice B

	/**
	 * Método para conocer el indíce de contaminación de un objeto
	 * 
	 * @param anyo anyo de compra del objeto del que se desea conocer el índice de
	 *             contaminación
	 */
	public static IndiceContaminacion getIndiceContaminacion(int anyo) {
		if (anyo >= FECHAA)
			return A;
		if (anyo >= FECHAB)
			return B;
		return C;
	}
}
