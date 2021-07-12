package test.teatro;

import teatro.Butaca;
import teatro.ZonaNumerada;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class ButacaTest {
	private Butaca b;
	@BeforeEach
	void setUp() throws Exception{
		/*inicializamos los valores de la butaca*/
		b=new Butaca(0, 0, new ZonaNumerada("ZonaPrueba", 2, 2));
	}

	@Test
	void testIsActiva() {
		assertEquals(true, b.isActiva(), "Error en el isActiva");
		b.mostrarButaca(); /*está activa, debería imprimirla en verde*/
		System.out.println(); /*salto de linea*/
		b.setActiva(false);
		assertEquals(false, b.isActiva(), "Error en el isActiva");
		b.mostrarButaca(); /*ahora no está activa, debería imprimirla en rojo*/
	}

	@Test
	void testSetActiva() {
		b.setActiva(true);
		assertEquals(true, b.isActiva(), "Error en set Activa");
		b.setActiva(false);
		assertEquals(false, b.isActiva(), "Error en set Activa");
	}

	@Test
	void testGetFila() {
		assertEquals(0, b.getFila(), "Error en el get filas");
		Butaca b2=null;
		try {
			ZonaNumerada z2 = new ZonaNumerada("Zona_prueba", 3, 3);
			b2 = new Butaca(2, 2, z2);
		} catch (Exception e) {
			fail();
		}
		if(b2==null) {
			fail();
		}
	}

	@Test
	void testSetFila() throws Exception {
		assertEquals(true ,b.setFila(1), "Error en el set fila");
		assertEquals(1, b.getFila(), "Error en el set fila");
		assertEquals(false, b.setFila(-1), "Error en el set fila");
		assertEquals(false, b.setFila(2), "Error en el set fila");
		b.setFila(0);
		b.setColumna(0);
		Butaca b2=new Butaca(1, b.getColumna(), b.getZonaButaca());
		b.getZonaButaca().addButaca(b2);
		assertEquals(false, b.setFila(1), "Error en el set fila");
	}

	@Test
	void testGetColumna() {
		assertEquals(0, b.getFila(), "Error en el get columna");
	}

	@Test
	void testSetColumna() throws Exception {
		assertEquals(true, b.setColumna(1), "Error en el set columnas");
		assertEquals(1, b.getColumna());
		assertEquals(false, b.setColumna(-1), "Error en el set columnas");
		b.setFila(0);
		b.setColumna(0);
		Butaca b2=new Butaca(b.getFila(), 1, b.getZonaButaca());
		b.getZonaButaca().addButaca(b2);
		assertEquals(false, b.setColumna(1), "Error en el set columna");
	}

	@Test
	void testGetZonaButaca() {
		ZonaNumerada z;
		z=b.getZonaButaca();
		assertNotEquals(null, z, "Zona no existente");
		assertEquals("ZonaPrueba", z.getNombre(), "No es la zona esperada");
		assertEquals(2, z.getFilas(), "No es la zona esperada");
		assertEquals(2, z.getColumnas(), "No es la zona esperada");
	}

	@Test
	void testSetZonaButaca() throws Exception {
		ZonaNumerada z = new ZonaNumerada("Prueba_1", 2, 2);
		z.addButaca(0, 0);
		b.setFila(0);
		b.setColumna(0);
		assertEquals(false, b.setZonaButaca(z));
	}

}
