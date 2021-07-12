package test.teatro;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import teatro.Butaca;
import teatro.Zona;
import teatro.ZonaNumerada;

public class ZonaNumeradaTest {
	ZonaNumerada z;
	@BeforeEach
	void setUp() {
		try {
			z=new ZonaNumerada("Zona_prueba", 2, 2);
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testaddButacaIntInt() throws Exception {
		assertEquals(true, z.addButaca(0, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(0, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(true, z.addButaca(1, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(-1, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(2, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(1, 0), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(0, -1), "Error añadiendo butaca por fila y columna");
		assertEquals(false, z.addButaca(0, 2), "Error añadiendo butaca por fila y columna");
		assertEquals(true, z.addButaca(1, 1), "Error añadiendo butaca por fila y columna");
		assertEquals(true, z.addButaca(0, 1), "Error añadiendo butaca por fila y columna");
		
	}

	@Test
	void testaddButacaButaca() throws Exception {
		assertEquals(true, z.addButaca(new Butaca(0, 0, z)), "Error añadiendo butaca pasando la butaca");
		try{
			z.addButaca(new Butaca(0, 0, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
		assertEquals(true, z.addButaca(new Butaca(1, 0, z)), "Error añadiendo butaca pasando la butaca");
		try{
			z.addButaca(new Butaca(-1, 0, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
		try{
			z.addButaca(new Butaca(2, 0, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
		try{
			z.addButaca(new Butaca(0, 2, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
		assertEquals(true, z.addButaca(new Butaca(1, 1, z)), "Error añadiendo butaca pasando la butaca");
		assertEquals(true, z.addButaca(new Butaca(0, 1, z)), "Error añadiendo butaca pasando la butaca");
		try{
			z.addButaca(new Butaca(0, -1, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
		try{
			z.addButaca(new Butaca(1, 1, z));
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error añadiendo butaca pasando la butaca");
		}
	}

	@Test
	void testAddFila() {
		try {
			z.addButaca(0, 1);
			z.addButaca(1, 0);
		} catch (Exception e) {
			fail();
		}
		z.addFila();
		assertEquals(3, z.getFilas(), "Error en addFila");
		assertEquals(2, z.getColumnas(), "Error en addFilas");
		assertEquals(3, z.getButacas().length);
		assertEquals(2, z.getButacas()[1].length);
		assertNotEquals(null, z.getButacas()[0][1]);
		assertNotEquals(null, z.getButacas()[1][0]);
		try {
			z.addButaca(2, 1);
			z.addButaca(2, 0);
		} catch (Exception e) {
			fail();
		}
		try {
			z.addButaca(2, 1);
		} catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca", "Error en addFilas");
		}
		assertEquals(null, z.getButacas()[0][0]);
	}

	@Test
	void testQuitarFila() {
		try {
			z.addButaca(0, 1);
			z.addButaca(1, 0);
		} catch (Exception e) {
			fail();
		}
		z.quitarFila();
		assertEquals(1, z.getButacas().length); /*solo debería quedar una fila*/
		assertEquals(2, z.getButacas()[0].length); /*la fila debe mantener dos columnas*/
		assertNotEquals(null, z.getButacas()[0][1]); /*se mantiene la butaca de la fila 0*/
	}

	@Test
	void testAddColumna() {
		try {
			z.addButaca(0, 0);
			z.addButaca(1, 1);
		} catch (Exception e) {
			fail();
		}
		z.addColumna();
		assertEquals(3, z.getColumnas());
		assertEquals(3, z.getButacas()[0].length);
		assertEquals(null, z.getButacas()[0][1]);
		assertNotEquals(null, z.getButacas()[0][0]);
		assertNotEquals(null, z.getButacas()[1][1]);
		try {
			z.addButaca(0, 2);
			z.addButaca(1, 2);
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testQuitarColumna() {
		try {
			z.addButaca(0, 0);
			z.addButaca(0, 1);
		}
		catch (Exception e) {
			fail();
		}
		z.quitarColumna();
		assertEquals(null, z.getButacas()[1][0]);
		assertEquals(1, z.getColumnas());
		assertEquals(1, z.getButacas()[0].length);
		assertEquals(2, z.getButacas().length);
		try {
			z.addButaca(0, 1);
		}
		catch (Exception e) {
			assertEquals(e.getMessage(), "Error atributos new Butaca");
		}
	}

	@Test
	void testQuitarButaca() {
		try {
			z.addButaca(0, 0);
			z.addButaca(1, 1);
		}
		catch (Exception e) {
			fail();
		}
		assertEquals(true, z.quitarButaca(0, 0));
		assertEquals(false, z.quitarButaca(-1, 0));
		assertEquals(false, z.quitarButaca(3, 0));
		assertEquals(null, z.getButacas()[0][0]);
		assertEquals(null, z.searchButaca(0, 0));
		assertNotEquals(null, z.searchButaca(1, 1));
	}

	@Test
	void testSearchButaca() {
		try {
			z.addButaca(0, 0);
			z.addButaca(1, 0);
		}
		catch (Exception e) {
			fail();
		}
		assertEquals(null, z.searchButaca(1, 1));
		assertEquals(null, z.searchButaca(2, 2));
		assertEquals(null, z.searchButaca(-1, 0));
		assertEquals(null, z.searchButaca(3, 0));
		assertNotEquals(null, z.searchButaca(0, 0));
		assertNotEquals(null, z.searchButaca(1, 0));
	}
	
	@Test
	void testLimitaciones() {
		Zona.setLimitacion(5);
	}

}
