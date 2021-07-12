package test.reserva;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Calendar;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import reserva.Reserva;
import teatro.Butaca;
import teatro.ZonaNumerada;

public class ReservaTest {
	Reserva r=null; 
	@BeforeEach
	void setUp(){
		try {
			r = new Reserva(null, null);
			//System.out.println(r.getCodigo());
		} catch (Exception e) {
			fail();
		} 
	}
	@Test
	void testLiberarButaca() {
		Evento ev = null;
		Representacion re = null;
		Calendar c = Calendar.getInstance();
		c.add(Calendar.MONTH, 1);
		Butaca b=null;
		try {
			ev = new Concierto(null, 0, null, null, null, null, null);
			re = new Representacion(c, 10, new PolíticaDeReseva(5, 1, 1));
			ev.addRepresentacion(re);
			b = new Butaca(3, 1, new ZonaNumerada("Zona butaca", 4, 2));
			r = new Reserva(re, b); /*reservamos la butaca b*/
		} catch (Exception e) {
			fail();
		}
		assertEquals(true, re.getButacasOcupadas().contains(b)); /*comprobamos que este ocupada*/
		r.liberarButaca();
		assertEquals(false, re.getButacasOcupadas().contains(b));
	}
	@Test
	void testGetCodigo() {
		assertEquals("3", r.getCodigo()); /*2 porque se ejecuta ántes el test de liberar butaca*/
		Evento ev = null;
		Representacion re = null;
		Calendar c = Calendar.getInstance();
		c.add(Calendar.DAY_OF_MONTH, 3);
		try {
			ev = new Concierto(null, 0, null, null, null, null, null);
			re = new Representacion(c, 10, new PolíticaDeReseva(5, 1, 1));
			ev.addRepresentacion(re);
			r = new Reserva(re, new Butaca(0, 0, null));
		} catch (Exception e) {
			fail();
		}
		assertEquals("4?R", r.getCodigo());
		ev.setTitulo("Prueba");
		try {
			r = new Reserva(re, new Butaca(0, 0, null));
		} catch (Exception e) {
			assertEquals("Butaca ya ocupada", e.getMessage());
		}
		r.liberarButaca();
		try {
			r = new Reserva(null, new Butaca(0, 0, null));
		} catch (Exception e) {
			fail();
		}
		assertEquals("6", r.getCodigo());
		try {
			re.setFechaYHora(Calendar.getInstance());
			r = new Reserva(re, new Butaca(0, 0, null));
		} catch (Exception e) {
			assertEquals("Representación pasada", e.getMessage());
		}
		try {
			re.setFechaYHora(Calendar.getInstance());
			re.getFechaYHora().add(Calendar.DAY_OF_MONTH, -2);
			r = new Reserva(re, new Butaca(0, 0, null));
		} catch (Exception e) {
			assertEquals("Representación pasada", e.getMessage());
		}
		try {
			re.setFechaYHora(Calendar.getInstance());
			re.getFechaYHora().add(Calendar.DAY_OF_MONTH, +1);
			re.getPd().setLim(2);
			r = new Reserva(re, new Butaca(0, 0, null));
		} catch (Exception e) {
			assertEquals("Límite pasado", e.getMessage());
		}
		return;
	}

}
