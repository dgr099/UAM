package test.usuario;

import static org.junit.jupiter.api.Assertions.*;

import java.util.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import usuario.TarjetaBancaria;
/**
 * Tester de la clase TarjetaBancaria
 * @author Jonás Arce García
 *
 */
public class testTarjeta {
	private TarjetaBancaria t;

	@BeforeEach
	void setUp(){
		try {
		t = new TarjetaBancaria("1111222233334444", new Date(12-21), 666);
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testGetNumTarjeta() {
		assertEquals("1111222233334444", t.getNumTarjeta());
	}

	@Test
	void testSetNumTarjeta() {
		t.setNumTarjeta("1111222233334444");
		assertEquals("1111222233334444", t.getNumTarjeta());
	}

	@Test
	void testGetFechaCad() {
		assertEquals(new Date(12-21), t.getFechaCad());
	}

	@Test
	void testSetFechaCad() {
		t.setFechaCad(new Date(12-21));
		assertEquals(new Date(12-21), t.getFechaCad());
	}

	@Test
	void testGetCodigo() {
		assertEquals(666, t.getCodigo());
	}

	@Test
	void testSetCodigo() {
		t.setCodigo(666);
		assertEquals(666, t.getCodigo());
	}

}
