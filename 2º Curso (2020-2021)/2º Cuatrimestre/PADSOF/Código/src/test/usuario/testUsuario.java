package test.usuario;

import static org.junit.jupiter.api.Assertions.*;


import java.util.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import abonos.Abono;
import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import entrada.Entrada;
import entrada.EntradaZonaNoNumerada;
import evento.Concierto;
import evento.Evento;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import reserva.Reserva;
import teatro.Butaca;
import teatro.Teatro;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import usuario.TarjetaBancaria;
import usuario.Usuario;
public class testUsuario {
	Usuario u = null;

	@BeforeEach
	void setUp() {
		try {
			u = new Usuario("paco", "pswd");
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testgetNReservas()	{
		Map<Representacion, Integer> nReservas = new TreeMap<Representacion, Integer>();
		assertEquals(nReservas, u.getNReservas());
	}
	
	@Test
	void testgetReservas() {
		ArrayList <Reserva> reservas = new ArrayList<>();
		assertEquals(reservas, u.getReservas());
	}
	
	@Test
	void testGetNombre() {
		assertEquals("paco", u.getNombre());
	}

	@Test
	void testSetNombre() {
		u.setNombre("paco");
		assertEquals("paco", u.getNombre());
	}

	@Test
	void testGetContraseña() {
		assertEquals("pswd", u.getContraseña());
	}

	@Test
	void testSetContraseña() {
		u.setContraseña("pswd");
		assertEquals("pswd", u.getContraseña());
	}

	@Test
	void testGetNotificaciones() {
		ArrayList <String> n = new ArrayList<>();
		assertEquals(n, u.getNotificaciones());
	}

	@Test
	void testAddTarjetas() {
		TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);

		try {
			u.addTarjetas(t);
			assertEquals(true, u.getTarjetas().contains(t));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testSeleccionarTarjeta() {
		String o = "1111222233334444";
		TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);
		
		try {
			u.addTarjetas(t);
			assertEquals(u.seleccionarTarjeta(o).getNumTarjeta(), o);
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testAddEntradas() {
		Entrada en = null;
		
		try {
			u.addEntradas(en);
			assertEquals(true, u.getEntradas().contains(en));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testComprarEntrada() {
		try {
			TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);
			Calendar c= Calendar.getInstance();
			c.set(2021, 5, 25, 14, 20, 00);
			Representacion r = new Representacion(c, 50);
			Evento e = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			((Concierto)e).addPieza("Pieza1");
			((Concierto)e).addPieza("Pieza2");
			Teatro teat = new Teatro("Teatro1", 20);
			ZonaNoNumerada z = new ZonaNoNumerada("ZNN1", 30);
			z.setTeatro(teat);
			teat.addZona(z);
			e.addRepresentacion(r);
			e.addPrecioZona(z, 25);
			u.addTarjetas(t);
			Entrada ent = null;
			ent = new EntradaZonaNoNumerada(false, r, z);
			u.comprarEntrada(ent, t);
			assertEquals(true, u.getEntradas().contains(ent));
		} catch(Exception e) {
		fail();
		}
	}

	@Test
	void testAddAbonos() {
		
		try {
			Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
			Evento ev2 = new Concierto("Concierto de prueba2", 15, "C2", "DGRA", "CerraOrquestas", "Germaon", "Wilalyrex");
			Zona z = new ZonaNoNumerada("hola", 50);
			ArrayList<Evento> eventos = new ArrayList<>();
			eventos.add(ev1);
			eventos.add(ev2);
			AbonoUsuario abc = new AbonoUsuario(new AbonoCiclo(50.0, eventos, z));
			u.addAbonos(abc);
			assertEquals(true, u.getAbonos().contains(abc));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testComprarAbono() {
		int num=0;
		TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);
		num=u.getAbonos().size();
		try {
			u.addTarjetas(t);
			ZonaNoNumerada z = new ZonaNoNumerada("zona_prueba", 50);
			double p = 350;
			Abono a = new AbonoAnual(p, z);
			a.setPrecio(p);
			try{
				u.comprarAbono(a, t);
			}catch(Exception e) {
				System.out.println(e);
			}
			assertEquals(num+1, u.getAbonos().size());
		} catch(Exception e) {
			fail();
		}
	}

	@Test
	void testEntrarListaEspera() {
		Calendar c= Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Representacion r = new Representacion(c, 50);
		
		try {
			u.entrarListaEspera(r);
			assertEquals(true, r.getLista().contains(u));
		} catch(Exception e) {
			fail();
		}
	}

	@Test
	void testReservarButaca() {
		Calendar c = Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
		Butaca b = null;

		try {
			PolíticaDeReseva pd = new PolíticaDeReseva(10, 5, 5);
			Representacion r = new Representacion(c, 50, pd);
			ev1.addRepresentacion(r);
			ZonaNumerada z = new ZonaNumerada("Zona_prueba", 2, 2);
			b = new Butaca(0, 0, z);
			u.reservarButaca(r, b);
			assertEquals(true, u.reservarButaca(r, b));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testSeleccionarReserva() {
		Calendar c = Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
		Reserva r = null; 
		Reserva o = null; //LO dejo a null porque solo voy a seleccionar la reserva r
		int num = 0;
		
		try {
			PolíticaDeReseva pd = new PolíticaDeReseva(10, 5, 5);
			Representacion rep = new Representacion(c, 50, pd);
			ev1.addRepresentacion(rep);
			ZonaNumerada z = new ZonaNumerada("Zona_prueba", 2, 2);
			Butaca b = null;
			b = new Butaca(0, 0, z);
			r = new Reserva(rep, b);
			u.getReservas().add(r);
			u.getReservas().add(o);
			u.SeleccionarReserva(num);
			assertEquals(r, u.SeleccionarReserva(num));
		} catch(Exception e) {
			fail();
		}
	}

	@Test
	void testCancelarReserva() {
		Calendar c = Calendar.getInstance();
		c.set(2021, 5, 25, 14, 20, 00);
		Evento ev1 = new Concierto("Concierto de prueba", 15, "C1", "DGR", "CerraOrquesta", "German", "Willyrex");
		Reserva r = null;
		
		try {
			PolíticaDeReseva pd = new PolíticaDeReseva(10, 5, 5);
			Representacion rep = new Representacion(c, 50, pd);
			ev1.addRepresentacion(rep);
			ZonaNumerada z = new ZonaNumerada("Zona_prueba", 2, 2);
			Butaca b = null;
			b = new Butaca(0, 0, z);
			r = new Reserva(rep, b);
			u.getReservas().add(r);
			u.getNReservas().put(rep, 1);
			u.cancelarReserva(r);
		} catch(Exception e) {
			fail();
		}
	}
	
	@Test
	void testEncriptarYDesencriptar() {
		try {
			String claveSecreta = "misterio";
			String contra = u.getContraseña();
			
			String contraEncriptada = u.encriptar(contra, claveSecreta);
			assertNotEquals(contra, contraEncriptada);
			String contraDesencriptada = u.desencriptar(contraEncriptada, claveSecreta);
			assertEquals(contra, contraDesencriptada);
			
		} catch (Exception e) {
			fail();
		}
	}

}