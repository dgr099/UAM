package test.evento;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Calendar;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import entrada.Entrada;
import entrada.EntradaButaca;
import entrada.EntradaZonaNoNumerada;
import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import teatro.Butaca;
import teatro.Teatro;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;

public class EventoTest {
	private Evento e;
	private Teatro t;
	@BeforeEach
	void setUp() throws Exception {
		Zona z = new ZonaNoNumerada("ZNN1", 30);
		t = new Teatro("Teatro1", 20);
		e = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
		((Concierto)e).addPieza("Pieza1");
		((Concierto)e).addPieza("Pieza2");
		t.addZona(z);
		z= new ZonaNumerada("ZN1", 3, 3);
		/*añado unas cuantas butaquitas a la zona de butacas*/
		try {
			((ZonaNumerada)z).addButaca(new Butaca(0, 0, ((ZonaNumerada)z)));
			((ZonaNumerada)z).addButaca(new Butaca(0, 1, ((ZonaNumerada)z)));
			((ZonaNumerada)z).addButaca(new Butaca(0, 2, ((ZonaNumerada)z)));
			((ZonaNumerada)z).addButaca(new Butaca(2, 0, ((ZonaNumerada)z)));
			((ZonaNumerada)z).addButaca(new Butaca(2, 1, ((ZonaNumerada)z)));
			((ZonaNumerada)z).addButaca(new Butaca(2, 2, ((ZonaNumerada)z)));
		} catch (Exception e1) {
			fail();
		}
		for(int i=0; i!=3; i++) { /*todas las de la última fila a false because yes*/
			((ZonaNumerada)z).getButacas()[2][i].setActiva(false);
		}
		t.addZona(z);
		e.addPrecioZona(t.getZonas().get(0), 25.00); /*el precio de la zona no numerada es de 25.00*/
		e.addPrecioZona(t.getZonas().get(1), 28.20); /*el precio de la zona de butacas es de 28.20*/
		return;
	}
	
	@Test
	void testGetPrecio() {
		Zona z = null;
		if(e.getPrecioZonas().size()==0){
			fail();
		}
		try {
			z=new ZonaNoNumerada("Prueba", 5);
		} catch (Exception e1) {
			fail();
		}
		assertEquals(true, e.addPrecioZona(z, 20));
		assertEquals(25.00, e.getPrecio(t.getZonas().get(0)));
		assertEquals(28.20, e.getPrecio(t.getZonas().get(1)));
		assertEquals(20, e.getPrecio(z));
	}
	
	@Test
	void testAddPrecioZona() {
		Zona z = null;
		assertEquals(false, e.addPrecioZona(z, 0));
		assertEquals(false, e.addPrecioZona(z, 12));
		try {
			z = new ZonaNoNumerada("ZNN2", 40);
		} catch (Exception e1) {
			fail();
		}
		t.addZona(z);
		assertEquals(true, e.addPrecioZona(z, 15.20));
		assertEquals(15.20, e.getPrecio(z));
		assertEquals(false, e.addPrecioZona(z, 0));
		assertEquals(true, e.addPrecioZona(z, 300.1234));
		assertEquals(300.1234, e.getPrecio(z));
		
	}

	@Test
	void testGetDescripcion() {
		assertEquals("Concierto de prueba", e.getDescripcion());
		e.setDescripcion("Prueba_2");
		assertEquals("Prueba_2", e.getDescripcion());
		
	}

	@Test
	void testSetDescripcion() {
		e.setDescripcion("2");
		assertEquals("2", e.getDescripcion());
		e.setDescripcion("Prueba 1 para ver si todo va bien");
		assertEquals("Prueba 1 para ver si todo va bien", e.getDescripcion());
		e.setDescripcion("Prueba 2 para ver si todo va bien");
		assertNotEquals("2", e.getDescripcion());
		assertNotEquals("Prueba 1 para ver si todo va bien", e.getDescripcion());
		assertEquals("Prueba 2 para ver si todo va bien", e.getDescripcion());
		e.setDescripcion("Prueba 3 para ver si todo va bien");
		assertNotEquals("2", e.getDescripcion());
		assertNotEquals("Prueba 1 para ver si todo va bien", e.getDescripcion());
		assertNotEquals("Prueba 2 para ver si todo va bien", e.getDescripcion());
		assertEquals("Prueba 3 para ver si todo va bien", e.getDescripcion());
	}

	@Test
	void testGetDuracion() {
		assertEquals(15, e.getDuracion());
	}

	@Test
	void testSetDuracion() {
		assertEquals(true, e.setDuracion(10));
		assertEquals(10, e.getDuracion());
		assertEquals(true, e.setDuracion(5));
		assertEquals(5, e.getDuracion());
		assertEquals(false, e.setDuracion(0));
		assertEquals(false, e.setDuracion(-100));
	}

	@Test
	void testGetTitulo() {
		assertEquals("C1", e.getTitulo());
	}

	@Test
	void testSetTitulo() {
		e.setTitulo(null);
		assertEquals(null, e.getTitulo());
		e.setTitulo("Eustaqui");
		assertEquals("Eustaqui", e.getTitulo());
		e.setTitulo("AAA");
		assertEquals("AAA", e.getTitulo());
		e.setTitulo("BBB");
		assertEquals("BBB", e.getTitulo());
	}

	@Test
	void testGetAutor() {
		assertEquals("DGR", e.getAutor());
	}

	@Test
	void testSetAutor() {
		e.setAutor(null);
		assertNotEquals("DGR", e.getAutor());
		assertEquals(null, e.getAutor());
		e.setAutor("Bohdan");
		assertNotEquals(null, e.getAutor());
		assertEquals("Bohdan", e.getAutor());
	}

	@Test
	void testGetAddRepresentaciones() {
		Calendar c= Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Representacion r = new Representacion(c, 50);
		assertEquals(0, e.getRepresentaciones().size());
		e.addRepresentacion(r);
		assertEquals(1, e.getRepresentaciones().size());
		assertEquals(true, e.getRepresentaciones().contains(r));
		assertEquals(r, e.getRepresentaciones().get(0));
		//System.out.print(c.getTime()); Debug
		assertEquals(2021, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.YEAR));
		assertEquals(5, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.MONTH));
		assertEquals(25, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.DAY_OF_MONTH));
		assertEquals(14, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.HOUR_OF_DAY));
		assertEquals(20, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.MINUTE));
		e.getRepresentaciones().remove(0);
		assertEquals(0, e.getRepresentaciones().size());
		c.set(2020, 5, 25, 14, 20, 00);
		r = new Representacion(c, 50);
		e.addRepresentacion(r);
		c = Calendar.getInstance();
		c.set(2019, 4, 24, 13, 19, 00);
		r = new Representacion(c, 50);
		e.addRepresentacion(r);
		assertEquals(2, e.getRepresentaciones().size());
		assertEquals(r, e.getRepresentaciones().get(1));
		assertEquals(2020, e.getRepresentaciones().get(0).getFechaYHora().get(Calendar.YEAR));
		assertEquals(2019, e.getRepresentaciones().get(1).getFechaYHora().get(Calendar.YEAR));
		
	}

	@Test
	void testGetEstadisticas() {
		for(int i=0; i!=4; i++) {
			assertEquals(0, e.getEstadisticas()[i]);
		}
		/*creo una nueva representacion y añado una entrada a esta*/
		Calendar c= Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Representacion r = new Representacion(c, 50);
		e.addRepresentacion(r);
		Entrada ent = null;
		/*por si esta llena*/
		try {
			ent = new EntradaZonaNoNumerada(false, r, ((ZonaNoNumerada)t.getZonas().get(0)));
		} catch (Exception e2) {
			fail();
		} /*entrada para la zona no numerada*/
		if(ent==null) {
			fail();
		}
		assertEquals(1, e.getEstadisticas()[0]); /*total de entradas sin usar abono*/
		assertEquals(1, e.getEstadisticas()[1]); /*asistencias*/
		assertEquals(0, e.getEstadisticas()[2]); /*abonos empleados*/
		assertEquals(e.getPrecio(t.getZonas().get(0)), e.getEstadisticas()[3]); /*dinero generado, debería ser igual al precio de la entrada porque no hay más jaja*/
		/*probamos a crear la entrada mediante el add entrada*/
		/*ademas esta entrada utiliza el abono*/
		try {
			e.getRepresentaciones().get(0).addEntrada(new EntradaButaca(true, null, ((ZonaNumerada)(t.getZonas().get(1))).searchButaca(0, 0)));
		} catch (Exception e1) {
			fail();
		}
		assertEquals(1, e.getEstadisticas()[2]); /*abonos empleados*/
		/*por si la zona esta llena*/
		try {
			ent = new EntradaZonaNoNumerada(false, r, ((ZonaNoNumerada)t.getZonas().get(0)));
		} catch (Exception e1) {
			fail();
		}
		assertEquals(e.getPrecio(t.getZonas().get(0))*2, e.getEstadisticas()[3]);
	}
	@Test
	void testLimitaciones() {
		Calendar c= Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Representacion r = new Representacion(c, 5); /*solo 5 personas pueden ir a la repre (cumpliendo con aforo y limitaciones de zona)*/
		e.addRepresentacion(r);
		for(int i=0; i!=5; i++) { /*añadimos 5 entradas en la zona no numerada, que no debería haber ningún problema*/
			try {
				assertEquals(true, r.addEntrada(new EntradaZonaNoNumerada(false, r, (ZonaNoNumerada)(t.getZonas().get(0)))));
			} catch (Exception e1) {
				fail();
			}
		}
		/*la 6 entrada ya excede el aforo de la representacion*/
		/*al pasarle null por parámetro, la entrada se crea correctamente pero luego el add da error*/
		try {
			assertEquals(false, r.addEntrada(new EntradaZonaNoNumerada(false, null, (ZonaNoNumerada)(t.getZonas().get(0)))));
		} catch (Exception e1) {
			e1.printStackTrace();
			fail();
		}
		/**en la zona no numerada cabían 30, las limitaciones son del 20%, por lo que realmente solo pueden entrar  24*/
		r = new Representacion(c, 30);
		e.addRepresentacion(r); /**añadimos la representación */
		for(int i=0; i!=24; i++) { /*añadimos 24 entradas en la zona no numerada, que no debería haber ningún problema*/
			try {
				assertEquals(true, r.addEntrada(new EntradaZonaNoNumerada(false, r, (ZonaNoNumerada)(t.getZonas().get(0)))));
			} catch (Exception e1) {
				fail();
			}
		}
		/*la 25 entrada ya excede las limitaciones de la zona*/
		/**esta vez si le pasamos la representacion por lo que el constructor llama a addEntrada y al recibir error lanza una excepción*/
		try {
			assertEquals(false, r.addEntrada(new EntradaZonaNoNumerada(false, r, (ZonaNoNumerada)(t.getZonas().get(0)))));
		} catch (Exception e1) {
			assertEquals("Entrada no válida", e1.getMessage());
		}
	}

}
