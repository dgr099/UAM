package test.sistema;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Calendar;
import java.util.Date;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import evento.Evento;
import evento.ObraTeatro;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import sistema.Sistema;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import usuario.TarjetaBancaria;
import usuario.Usuario;
import abonos.AbonoAnual;
import abonos.Abono;


public class SistemaTest {
	Sistema sistem = null;
	@BeforeEach
	void setUp() {
		sistem = Sistema.getInstancia(); /*creas un sistem con un teatro con limitaciones del 5% y nombre prueba*/
		try {
			sistem.addUsuario(new Usuario("User_prueba", "123"));
			sistem.addUsuario(new Usuario("User_prueba_3", "123"));
		} catch (Exception e) {
			fail();
		}
		try {
			sistem.getTeatro().addZona(new ZonaNoNumerada("ZNN1", 20));
			sistem.getTeatro().addZona(new ZonaNoNumerada("ZNN2", 20));
			sistem.getTeatro().addZona(new ZonaNumerada("ZN1", 3, 3));
		} catch (Exception e) {
			fail();
		}
		for(int i=0; i!=3; i++){ /*rellenamos las butacas*/
			for(int j=0; j!=3; j++){
				try {
					((ZonaNumerada)sistem.getTeatro().getZonas().get(2)).addButaca(i, j);
				} catch (Exception e) {
					fail();
				}
			}
		}
		
		((ZonaNumerada)sistem.getTeatro().getZonas().get(2)).getButacas()[0][0].setActiva(false); /*ponemos que 1 no esté activa*/
		((ZonaNumerada)sistem.getTeatro().getZonas().get(2)).quitarButaca(1, 1); /*quitamos una butaca*/
		sistem.addEvento(new ObraTeatro("teat_des", 20, "OT_prueba", "autor", "director", "compania"));
		sistem.getEventos().get(0).addRepresentacion(new Representacion(Calendar.getInstance(), 30));
		sistem.getEventos().get(0).getRepresentaciones().get(0).getFechaYHora().set(Calendar.MONTH, sistem.getEventos().get(0).getRepresentaciones().get(0).getFechaYHora().get(Calendar.MONTH)+3); /*representacion que tiene lugar en tres meses*/
		sistem.getEventos().get(0).addPrecioZona(sistem.getTeatro().getZonas().get(0), 5); /*el precio de la zona para poder crear entradas*/
		sistem.getEventos().get(0).addPrecioZona(sistem.getTeatro().getZonas().get(1), 15); /*el precio de la zona para poder crear entradas*/
		sistem.getEventos().get(0).addPrecioZona(sistem.getTeatro().getZonas().get(2), 25); /*el precio de la zona para poder crear entradas*/
		
	}

	@Test
	void testLogin() {
		Usuario u = null;
		try {
			u = new Usuario("User_prueba_2", "12345");
		} catch (Exception e) {
			fail();
		}
		assertEquals(null, sistem.getUsuarioEnUso()); //no hay usuarios al inicio
		sistem.addUsuario(u);
		sistem.login(u.getNombre(), u.getContraseña());
		assertNotEquals(null, sistem.getUsuarioEnUso());
		assertEquals(u.getNombre(), sistem.getUsuarioEnUso().getNombre());
		assertEquals(u.getContraseña(), sistem.getUsuarioEnUso().getContraseña());
	}

	@Test
	void testRegistro() {
		int user=0;
		user=sistem.getUsuarios().size();
		sistem.registro("User_prueba", "1234");
		assertNotEquals(user+1, sistem.getUsuarios().size()); /*debería no incrementarse el nombre de usuarios*/
		sistem.registro("User_prueba_4", "1234");
		assertEquals(user+1, sistem.getUsuarios().size()); /*debería incrementarse el nº de usuarios*/
	}

	@Test
	void testCerrarSesion() {
		try {
			sistem.setUsuarioEnUso(new Usuario("prueba", "123"));
		} catch (Exception e) {
			fail();
		}
		assertNotEquals(null, sistem.getUsuarioEnUso());
		sistem.cerrarSesion();
		assertEquals(null, sistem.getUsuarioEnUso());
	}

	@Test
	void testSeleccionarEvento() {
		Evento e = sistem.getEventos().get(0);
		System.out.println("testSeleccionarEvento");
		assertEquals(e.getTitulo(), sistem.seleccionarEvento(1).getTitulo());
		assertEquals(null, sistem.seleccionarEvento(-1));
		assertEquals(null, sistem.seleccionarEvento(0));
		assertEquals(null, sistem.seleccionarEvento(5));
		
	}

	@Test
	void testBusqueda() {
		assertEquals(0, sistem.busqueda("nope").size());
		assertEquals(1, sistem.busqueda("e").size());
		System.out.println(sistem.busqueda("e"));
	}

	@Test
	void testFiltrarEvento() {
		assertEquals(null, sistem.filtrarEvento(-1));
		assertEquals(null, sistem.filtrarEvento(4));
		assertEquals(1, sistem.filtrarEvento(3).size());
	}

	@Test
	void testSeleccionarZona() {
		assertNotEquals(null, sistem.seleccionarZona("ZNN1"));
		assertEquals(null, sistem.seleccionarZona("Zona que no existe"));
		assertEquals(null, sistem.seleccionarZona(null));
		assertNotEquals(null, sistem.seleccionarZona("ZNN2"));
		assertNotEquals(null, sistem.seleccionarZona("ZN1"));
		
	}

	@Test
	void testComprarEntrada() {
		TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);
		Usuario u = null;
		try {
			u = new Usuario("prueba_compra", "123");
		} catch (Exception e) {
			fail();
		}
		sistem.setUsuarioEnUso(u);
		try {
			u.addTarjetas(t);
		} catch (Exception e) {
			fail();
		}
		try {
			assertEquals(true, sistem.comprarEntrada(sistem.getEventos().get(0).getRepresentaciones().get(0), sistem.getTeatro().getZonas().get(0), sistem.getUsuarioEnUso().seleccionarTarjeta(t.getNumTarjeta())));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testSeleccionarAbono() {
		try { 
			Abono abono = new AbonoAnual(50.0,new ZonaNoNumerada("zona", 100));
			sistem.addAbono(abono);
			assertEquals(abono, sistem.seleccionarAbono(abono.getCodigo()));
		} catch (Exception e) {
			fail();
		}
	}

	@Test
	void testComprarAbono() {
		try { 
			Abono abono1 = new AbonoAnual(50.0,new ZonaNoNumerada("zona", 100));
			Abono abono2 = new AbonoAnual(50.0,new ZonaNoNumerada("zona", 100));
			TarjetaBancaria t = new TarjetaBancaria("1111222233334444", new Date(12 - 21), 666);
			sistem.getUsuarioEnUso().addTarjetas(t);
			assertEquals(true, sistem.comprarAbono(abono1, "1111222233334444"));
			assertEquals(false, sistem.comprarAbono(abono2, "0000000000000000"));
		} catch (Exception e) {
			assertEquals("No existe ninguna tarjeta con ese número entre sus tarjetas", e.getMessage());
		}
	}

	@Test
	void testNotificarUsuarios() {
		try {
			sistem.getEventos().get(0).getRepresentaciones().get(0).setPd(new PolíticaDeReseva(3, 3, 3));
		} catch (Exception e) {
			fail();
		}
		/*se reserva una butaca*/
		try {
			sistem.getUsuarios().get(1).reservarButaca(sistem.getEventos().get(0).getRepresentaciones().get(0), ((ZonaNumerada)sistem.getTeatro().getZonas().get(2)).searchButaca(0, 1));
		} catch (Exception e) {
			fail();
		}
		try {
			sistem.getUsuarios().get(0).entrarListaEspera(sistem.getEventos().get(0).getRepresentaciones().get(0));
		} catch (Exception e) {
			fail();
		}
		sistem.notificarUsuarios();
		assertEquals(0, sistem.getUsuarios().get(0).getNotificaciones().size());
		sistem.getUsuarios().get(1).cancelarReserva(sistem.getUsuarios().get(1).getReservas().get(0));
		/*al cancelar reserva se notifica al usuario 0*/
		assertEquals(1, sistem.getUsuarios().get(0).getNotificaciones().size());
		String mensaje = sistem.getUsuarios().get(0).getNotificaciones().get(0); 
		assertEquals(true, mensaje.contains("tiene entrada disponibles"));
	}

	@Test
	void testLoadAndSavesistem() {
		int nZonas=0;
		int nEv=0;
		int nUs=0;
		Usuario usA = sistem.getUsuarios().get(0);
		Usuario usP = sistem.getUsuarios().get(1);
		assertEquals(true, sistem.saveSistema());
		nZonas = sistem.getTeatro().getZonas().size();
		nEv = sistem.getEventos().size();
		sistem.getTeatro().quitarZona(sistem.getTeatro().getZonas().get(0)); /*eliminamos una zona*/
		sistem.getEventos().clear();
		assertNotEquals(nZonas, sistem.getTeatro().getZonas());
		assertNotEquals(nEv, sistem.getEventos());
		nUs = sistem.getUsuarios().size();		
		sistem.getUsuarios().clear();
		sistem.loadSistema();
		sistem = Sistema.getInstancia();
		assertEquals(nEv, sistem.getEventos().size());
		assertEquals("OT_prueba", sistem.getEventos().get(0).getTitulo());
		assertEquals(nZonas, sistem.getTeatro().getZonas().size());
		assertEquals(nUs, sistem.getUsuarios().size());
		assertEquals(usP.getNombre(), sistem.getUsuarios().get(1).getNombre());
		assertEquals(usP.getContraseña(), sistem.getUsuarios().get(1).getContraseña());
		assertEquals(usA.getNombre(), sistem.getUsuarios().get(0).getNombre());
		assertEquals(usA.getContraseña(), sistem.getUsuarios().get(0).getContraseña());
		assertEquals(30, sistem.getEventos().get(0).getRepresentaciones().get(0).getAforo());
	}

}
