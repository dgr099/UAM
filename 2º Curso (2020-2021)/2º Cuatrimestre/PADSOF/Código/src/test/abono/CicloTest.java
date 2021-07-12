package test.abono;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import abonos.Ciclo;
import evento.Concierto;
import evento.Evento;;

class CicloTest {
	List<Evento> eventos = Arrays.asList(
			new Concierto("desc", 123, "123", "123", "123", "123", "123"), 
			new Concierto("desc2", 1234, "1234", "1234", "1234", "1234", "1234"),
			new Concierto("desc3", 1234, "12345", "12345", "12345", "12345", "12345"));
	Ciclo c = new Ciclo(eventos);
	

	@Test
	void testGetEventos() {
		List<Evento> eventos1 = c.getEventos();
		assertEquals(eventos1, eventos);
	}

	@Test
	void testGetValoracion() {
		double val=0;
		eventos.get(0).addValoracion(5);
		val = 5;
		assertEquals(val, c.getValoracion());
		eventos.get(1).addValoracion(7);
		assertEquals(val, c.getValoracion());
		eventos.get(1).addValoracion(3);
		val = (5+3)/2.0;
		assertEquals(val, c.getValoracion());
		eventos.get(1).addValoracion(4);
		eventos.get(1).addValoracion(3);
		val = ((5) + (3+4+3)/3.0)/2.0;
		assertEquals(val, c.getValoracion());
		
	}

}
