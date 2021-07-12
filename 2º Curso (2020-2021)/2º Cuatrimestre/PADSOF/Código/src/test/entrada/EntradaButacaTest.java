package test.entrada;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Calendar;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import entrada.EntradaButaca;
import es.uam.eps.padsof.tickets.NonExistentFileException;
import es.uam.eps.padsof.tickets.UnsupportedImageTypeException;
import evento.Representacion;
import teatro.*;
import evento.Evento;
import evento.Concierto;

public class EntradaButacaTest {
	EntradaButaca e = null;
	Butaca b = null;
	private Teatro t;
	@BeforeEach
	void setUp() {
		try {
			b=new Butaca(0, 0, null);
		} catch (Exception e) {
			e.printStackTrace();
			fail();
		}
		try {
			e = new EntradaButaca(false, null, b);
		} catch (Exception e) {
			e.printStackTrace();
			fail();
		}
	}
	@Test
	void testComprobarValidez() {
		Representacion r = new Representacion(Calendar.getInstance(), 50);
		r.getButacasOcupadas().add(b); /*suponiendo que la butaca ya esté ocupada*/
		assertEquals(false, e.comprobarValidez(r)); 
		assertEquals(true, e.comprobarValidez(null)); 
		r.getButacasOcupadas().remove(b);
		assertEquals(true, e.comprobarValidez(r)); 
	}

	@Test
	void testGetZona() {
		ZonaNumerada z = null;
		try {
			z = new ZonaNumerada("Prueba", 1, 1);
		} catch (Exception e1) {
			e1.printStackTrace();
			fail();
		} 
		assertEquals(null, e.getZona());
		assertEquals(true, b.setZonaButaca(z));
		assertEquals(z, e.getZona());
		
	}

	@Test
	void testGetButaca() {
		assertEquals(b, e.getButaca());
	}
	
	@Test
	void testGenerarPDF() throws NonExistentFileException, UnsupportedImageTypeException {
		EntradaButaca e2 = null;
		Teatro t = null;
		Representacion r = new Representacion(Calendar.getInstance(), 20);
		Evento ev = new Concierto("desc", 20, "Concierto super bonico", "peter", "pan", "perry el ornitorrinco", "yo xd");
		ev.addRepresentacion(r);
		try {
			t = new Teatro("Nombre_prueba", 5);
		} catch (Exception e1) {
			e1.printStackTrace();
			fail();
		}
		
		try {
			ZonaNumerada z = new ZonaNumerada("Zona 1", 5, 5);
			t.addZona(z);
			r.getEvento().addPrecioZona(z, 15);
			e2 = new EntradaButaca(false, r, new Butaca(0, 0, z));
		} catch (Exception e1) {
			e1.printStackTrace();
			fail();
		}
		e.generarPDF();
		e2.generarPDF();		
	}
	
	@Test
	public void testGetSetValoracion() {
		assertEquals(false, e.addValoracion(5));
		Representacion r = new Representacion(Calendar.getInstance(), 20);
		try {
			t = new Teatro("nombre", 10);
			Evento ev = new Concierto("desc", 20, "Concierto super bonico", "peter", "pan", "perry el ornitorrinco", "yo xd");
			ev.addRepresentacion(r);
			ZonaNumerada z = new ZonaNumerada("Zona 1", 5, 5);
			t.addZona(z);
			r.getEvento().addPrecioZona(z, 15);
			e = new EntradaButaca(false, r, new Butaca(0, 0, z));
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
