package pr3.trafico.multas;

public class Multa {
    private String matricula;
    private String tipoMulta;
    private int puntos;

    public Multa(String matricula, String tipoMulta, int puntos) {
        this.matricula = matricula;
        this.tipoMulta = tipoMulta;
        this.puntos = puntos;
    }

	@Override
	public String toString() {
		return "Multa [matricula=" + matricula + ", tipoMulta=" + tipoMulta + ", puntos=" + puntos + "]";
    }
    public String getMatricula(){
        return this.matricula;
    }
    public int getPuntos(){
        return this.puntos;
    }
    public void addITVCad() {
    	++this.puntos;
    }
    public String getTipo() {
    	return this.tipoMulta;
    }

    
}