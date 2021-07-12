package test.abono;
import evento.*;
import teatro.*;
import entrada.*;
import abonos.AbonoCiclo;
import abonos.Ciclo;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.*;

public class AbonoCicloTest {
	
	ZonaNoNumerada zona;
	ArrayList<Evento> eventos = new ArrayList<Evento>();
	AbonoCiclo abono;
	Evento eventoIni = new Danza("desc", 10.0, "tit", "au", "dir");
		
	@BeforeEach
	void setUp() {
		try { zona = new ZonaNoNumerada("zona", 50); } catch (Exception e) { e.printStackTrace();}
		Evento evento1 = new Danza("hola", 1.0, "tit", "au", "dir");
		Evento evento2 = new Danza("mundo", 2.0, "ulo", "tor", "ect");
		Evento evento3 = new Danza("desc", 3.0, "gran", "dedi", "or");
		Evento evento4 = new Danza("onocido", 4.0, "dioso", "cado", "azo");
		Map<Zona, Double> precioZona1 = new TreeMap<Zona, Double>(); precioZona1.put(zona, (double)10);
		Map<Zona, Double> precioZona2 = new TreeMap<Zona, Double>(); precioZona2.put(zona, (double)20);
		Map<Zona, Double> precioZona3 = new TreeMap<Zona, Double>(); precioZona3.put(zona, (double)30);
		Map<Zona, Double> precioZona4 = new TreeMap<Zona, Double>(); precioZona4.put(zona, (double)40);
		evento1.setPrecioZonas(precioZona1); eventos.add(evento1);
		evento2.setPrecioZonas(precioZona2); eventos.add(evento2);
		evento3.setPrecioZonas(precioZona3); eventos.add(evento3);
		evento4.setPrecioZonas(precioZona4); eventos.add(evento4);
		
		Map<Zona, Double> precioZonaIni = new TreeMap<Zona, Double>(); precioZonaIni.put(zona, (double)100);
		eventoIni.setPrecioZonas(precioZonaIni); eventos.add(eventoIni);
		
		try { abono = new AbonoCiclo(50.0, eventos, zona); } catch (Exception  exc) { exc.printStackTrace(); }		
		return;
	}
	@Test
	void testGetCiclo() {
		Ciclo c = new Ciclo(eventos);
		assertEquals(c.getCod(), abono.getCiclo().getCod());
	}
	@Test
	void testGetPrecio() {
		assertEquals(100.0, abono.getPrecio());
	}

	@Test
	void testGetEventos() {
		int i;
		List<Evento> evs = abono.getEventos();
		for (i = 0; i < eventos.size() && i < evs.size(); i++){
			assertEquals(eventos.get(i), evs.get(i));
		}
	}

	@Test
	void testDelEventos() {
		List<Evento> evs;
		abono.delEventos(eventoIni);
		evs = abono.getEventos();		
		assertEquals(false, evs.contains(eventoIni));
	}

	@Test
	void testGetDescuento() {
		assertEquals(50.0, abono.getDescuento());
	}

	@Test
	void testSetDescuento() {
		abono.setDescuento(25.0);
		assertEquals(25.0, abono.getDescuento());
		assertEquals(150.0, abono.getPrecio());
	}

	@Test
	void testComprobarValidez() {
		Representacion r = new Representacion(Calendar.getInstance(), 5);	
		eventoIni.addRepresentacion(r);
		try {EntradaZonaNoNumerada e = new EntradaZonaNoNumerada(true, r, zona); 
			assertEquals(true, abono.comprobarValidez(e));		
			r.setEvento(new Danza("desc", 2.0, "tit", "au", "dir"));		
			assertEquals(true, abono.comprobarValidez(e));
		} catch (Exception exc) { exc.printStackTrace(); }
	}
	
	@Test
	void testGetFechaCaducidad() {
		Calendar cad = Calendar.getInstance();
		cad.add(Calendar.YEAR, 3);
		Representacion repre = new Representacion(cad, 5);
		Evento evento = new Danza("descripcion", 10.0, "titulo", "autor", "director");
		evento.addRepresentacion(repre);
		eventos.add(evento);
		try { 
			AbonoCiclo a = new AbonoCiclo(25.0, eventos, zona);
			assertEquals(cad, a.getFechaCaducidad());
		} catch (Exception exc) {exc.printStackTrace(); }
	}
	
	@Test
	void testGenerarCodigo() {
		try { abono = new AbonoCiclo(50.0, eventos, zona); 
		if (abono.getCodigo().compareTo("10ACzon") > 10) fail();
		} catch (Exception  exc) {exc.printStackTrace(); }
	}
}
