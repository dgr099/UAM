package reserva;

import java.io.Serializable;

/**
 * Clase que guarda atributos y métodos para la política de reserva
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class PolíticaDeReseva implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 4203345393647569034L;
	private int max; //máximo de reservas por usuario
	private int dur; //días en los que está activa la reserva
	private int lim; //limite para la reserva, ej 3 días antes
	public PolíticaDeReseva(int max, int lim, int dur) throws Exception {
		if(max<0 || lim<0 || dur<0) {
			throw new Exception("Error en Politica de reserva");
		}
		this.dur=dur;
		this.max = max;
		this.lim = lim;
	}
	
	public int getDur() {
		return dur;
	}

	public void setDur(int dur) {
		this.dur = dur;
	}

	public int getMax() {
		return max;
	}
	public void setMax(int max) {
		this.max = max;
	}
	public int getLim() {
		return lim;
	}
	public void setLim(int lim) {
		this.lim = lim;
	}
	
}
