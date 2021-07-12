package test.abono;
import entrada.*;
import evento.*;
import teatro.*;
import abonos.AbonoAnual;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.*;

public class AbonoAnualTest {
		
	AbonoAnual abono;
	ZonaNoNumerada zona;
	Representacion repre;
	EntradaZonaNoNumerada entradaIni;
	Evento evento;
	
	@BeforeEach
	void setUp() {
		try { zona = new ZonaNoNumerada("zona", 50); 
		evento = new Danza("hola", 1.0, "tit", "au", "dir");
		Map<Zona, Double> precioZona = new TreeMap<Zona, Double>(); 
		precioZona.put(zona, (double)10);
		evento.setPrecioZonas(precioZona);
		repre = new Representacion(Calendar.getInstance(), 5);
		evento.addRepresentacion(repre);
		entradaIni = new EntradaZonaNoNumerada(true, repre, zona);
		abono = new AbonoAnual(200.0, zona);
		abono.addEntradas(entradaIni);
		} catch (Exception e) { e.printStackTrace(); }

	}
	@Test
	void testGetEntradas() {
		assertEquals(true, abono.getEntradas().contains(entradaIni));
	}

	@Test
	void testAddEntradas() {
		assertEquals(false, abono.addEntradas(entradaIni));
		evento = new Danza("desc", 2.0, "tit", "au", "dir");
		Map<Zona, Double> precioZona = new TreeMap<Zona, Double>(); 
		precioZona.put(zona, (double)10);
		evento.setPrecioZonas(precioZona);
		repre = new Representacion(Calendar.getInstance(), 1);
		evento.addRepresentacion(repre);
		try { entradaIni = new EntradaZonaNoNumerada(true, repre, zona);
		assertEquals(true, abono.addEntradas(entradaIni));
		assertEquals(true, abono.getEntradas().contains(entradaIni));
		} catch (Exception e) { e.printStackTrace(); }
	}

	@Test
	void testComprobarValidez() {
		assertEquals(false, abono.comprobarValidez(entradaIni));
		evento = new Danza("bien", 3.0, "tit", "au", "dir");
		Map<Zona, Double> precioZona = new TreeMap<Zona, Double>(); 
		precioZona.put(zona, (double)10);
		evento.setPrecioZonas(precioZona);
		repre = new Representacion(Calendar.getInstance(), 2);
		evento.addRepresentacion(repre);
		try { entradaIni = new EntradaZonaNoNumerada(true, repre, zona); 
		assertEquals(true, abono.comprobarValidez(entradaIni));
		} catch (Exception e) { e.printStackTrace(); }
	}
	
	@Test
	void testGetValoracion() {
		assertEquals(-2, abono.getValoracion());
	}
}
