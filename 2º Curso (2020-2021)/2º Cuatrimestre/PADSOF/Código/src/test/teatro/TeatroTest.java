package test.teatro;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import teatro.Teatro;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;

public class TeatroTest {
	private Teatro t;
	@BeforeEach
	void setUp() {
		try {
			t=new Teatro("TeatroPrueba", 5);
		} catch (Exception e) {
			fail();
		}
	}
	@Test
	void testGetNombre() {
		assertEquals("TeatroPrueba", t.getNombre());
	}

	@Test
	void testSetNombre() {
		assertEquals("TeatroPrueba", t.getNombre());
		t.setNombre("PruebaSet");
		assertNotEquals("TeatroPrueba", t.getNombre());
		assertEquals("PruebaSet", t.getNombre());
	}

	@Test
	void testGetLimitaciones() {
		assertEquals(5, t.getLimitaciones());
	}

	@Test
	void testSetLimitaciones() {
		assertEquals(5, t.getLimitaciones());
		t.setLimitaciones(4);
		assertNotEquals(5, t.getLimitaciones());
		assertEquals(4, t.getLimitaciones());
	}

	@Test
	void testGetZonas() {
		assertEquals(0, t.getZonas().size());
	}

	@Test
	void testAddZona() {
		Zona z=null;
		Zona z1=null;
		try {
			z = new ZonaNoNumerada("Z1", 5);
			z1 = new ZonaNumerada("Z2", 2, 2);
		} catch (Exception e) {
			fail();
		}
		t.addZona(z);
		t.addZona(z1);
		assertEquals(z, t.getZonas().get(0));
		assertEquals(z, t.seleccionarZona(0));
		assertEquals(z1, t.getZonas().get(1));
		assertEquals(z1, t.seleccionarZona(1));
		return;
	}
	@Test
	void testQuitarZona() {
		Zona z=null, z1=null;
		try {
			z = new ZonaNoNumerada("Z1", 5);
			z1 = new ZonaNumerada("Z2", 2, 2);
			
		} catch (Exception e) {
			fail();
		}
		t.addZona(z);
		t.addZona(z1);
		assertEquals(z, t.getZonas().get(0));
		t.quitarZona(z);
		assertEquals(z1, t.seleccionarZona(0));
		assertEquals(false, t.getZonas().contains(z));
		assertEquals(true, t.getZonas().contains(z1));
	}

	@Test
	void testSeleccionarZona() {
		Zona z=null;
		try {
			z = new ZonaNoNumerada("Z1", 10);
		} catch (Exception e) {
			fail();
		}
		t.addZona(z);
		assertEquals(z, t.getZonas().get(0));
	}

}
