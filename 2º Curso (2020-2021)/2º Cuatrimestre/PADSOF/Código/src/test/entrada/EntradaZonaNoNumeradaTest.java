package test.entrada;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Calendar;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import entrada.EntradaZonaNoNumerada;
import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import teatro.Teatro;
import teatro.Zona;
import teatro.ZonaNoNumerada;

public class EntradaZonaNoNumeradaTest {
	private ZonaNoNumerada z = null;
	private EntradaZonaNoNumerada e = null;
	@BeforeEach
	void setUp() throws Exception{
		Zona.setLimitacion(5); /*las limitaciones de todas las zonas son el 5%*/
		z = new ZonaNoNumerada("Prueba", 30); /*creamos una zona con aforo para 30 personas*/
		e = new EntradaZonaNoNumerada(false, null, z);
		
	}
	@Test
	void testComprobarValidez() {
		Representacion r = new Representacion(Calendar.getInstance(), 15);
		Evento ev = new Concierto("Conc", 15, "Prueba", "Me quiero morir", "La maravillosa orquesta del alcohol", ":-(", "Peter Pan");
		ev.addRepresentacion(r);
		assertEquals(true, e.comprobarValidez(null)); /*para ninguna representación siempre estará ok*/
		assertEquals(true, e.comprobarValidez(r)); /*válido porq no hay ninguna ocupación y pueden estar hasta 30*95%=28*/
		Zona.setLimitacion(100);
		assertEquals(false, e.comprobarValidez(r)); /*la limitación es del 100%, nadie puede entrar*/
		r.getOcupacion().put(e.getZona(), 28); /*el evento ya está ocupado al 100%*/
		assertEquals(false, e.comprobarValidez(r));
		Zona.setLimitacion(5); /*volvemos al 95%, sigue ocupado completamente%*/
		assertEquals(false, e.comprobarValidez(r));
		Zona.setLimitacion(4); /*con el96% sigue ocupado completamente*/
		assertEquals(false, e.comprobarValidez(r));
		Zona.setLimitacion(3); /*ya con el 97%, el máximo sube a 29*/
		assertEquals(true, e.comprobarValidez(r));
	}

	@Test
	void testGetPrecio() {
		assertEquals(-1, e.getPrecio());
		Representacion r = new Representacion(Calendar.getInstance(), 15);
		Evento ev = new Concierto("Conc", 15, "Prueba", "Me quiero morir", "La maravillosa orquesta del alcohol", ":-(", "Peter Pan");
		ev.addRepresentacion(r);
		assertEquals(true, ev.addPrecioZona(e.getZona(), 10));
		assertEquals(-1, e.getPrecio());
		e.setRepresentacion(r);
		assertEquals(10, e.getPrecio());
		assertEquals(false, ev.addPrecioZona(e.getZona(), -1));
		assertEquals(10, e.getPrecio());
	}

	@Test
	void testGetZonaNoNumerada() {
		assertEquals(z, e.getZona());
		assertEquals(z, e.getZonaNoNumerada());
		e.setZonaNoNumerada(null);
		assertEquals(null, e.getZona());
	}

	@Test
	void testSetZonaNoNumerada() {
		e.setZonaNoNumerada(null);
		assertEquals(null, e.getZona());
		e.setZonaNoNumerada(z);
		assertEquals(z, e.getZona());
	}
	
	@Test
	public void testGetSetValoracion() {
		assertEquals(false, e.addValoracion(5));
		Representacion r = new Representacion(Calendar.getInstance(), 20);
		try {
			Teatro t = new Teatro("nombre", 10);
			Evento ev = new Concierto("desc", 20, "Concierto super bonico", "peter", "pan", "perry el ornitorrinco", "yo xd");
			ev.addRepresentacion(r);
			ZonaNoNumerada z = new ZonaNoNumerada("nombre", 20);
			t.addZona(z);
			r.getEvento().addPrecioZona(z, 15);
			e = new EntradaZonaNoNumerada(false, r, z);
		}
		catch (Exception e) {
			e.printStackTrace();
			fail();
			return;
		}
		assertEquals(true, e.addValoracion(5));
		assertEquals(5, e.getValoracion());
		assertEquals(false, e.addValoracion(-2));
		assertEquals(5, e.getValoracion());
		assertEquals(true, e.addValoracion(3));
		assertEquals(3, e.getValoracion());
		assertEquals(false, e.addValoracion(6));
		assertEquals(3, e.getValoracion());
	}

}
