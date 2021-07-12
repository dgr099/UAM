package test.abono;

import teatro.ZonaNoNumerada;
import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import evento.Danza;
import evento.Evento;
import evento.Representacion;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Calendar;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class AbonoUsuarioTest {

	AbonoUsuario abono;
	AbonoAnual anual;
	ZonaNoNumerada zona;
	
	@BeforeEach
	void setUp() {
		try { zona = new ZonaNoNumerada("zona", 50);
		anual = new AbonoAnual(200.0, zona);
		abono = new AbonoUsuario(anual);
		} catch (Exception e) { System.out.println(e); }
		
	}
	
	@Test
	void testSetCodigo() {
		abono.setCodigo("1");
		assertEquals(1, Integer.parseInt(abono.getCodigo()));
	}
	
	@Test
	void testGetCaducidad() {
		Calendar caducidad = Calendar.getInstance();
		if(caducidad.after(abono.getCaducidad())) fail();
		caducidad.add(Calendar.YEAR, 1);
		if(caducidad.before(abono.getCaducidad())) fail();
	}
	
	
	@Test
	void testSetCaducidad() {
		abono.setCaducidad();
		Calendar caducidad = Calendar.getInstance();
		if(caducidad.after(abono.getCaducidad())) fail();
		caducidad.add(Calendar.YEAR, 1);
		if(caducidad.before(abono.getCaducidad())) fail();	
		Calendar cad = Calendar.getInstance();
		Representacion repre = new Representacion(cad, 5);
		Evento evento = new Danza("descripcion", 10.0, "titulo", "autor", "director");
		evento.addRepresentacion(repre);
		ArrayList<Evento> eventos = new ArrayList<Evento>();
		eventos.add(evento);
		try { AbonoCiclo ciclo = new AbonoCiclo(25.0, eventos, zona);
		AbonoUsuario a = new AbonoUsuario(ciclo);
		caducidad.add(Calendar.YEAR, -1);
		if(caducidad.after(a.getCaducidad())) fail();
		caducidad.add(Calendar.YEAR, 1);
		if(caducidad.before(a.getCaducidad())) fail();
		} catch (Exception exc) { exc.printStackTrace(); }
	}
	
	@Test
	void testGetAbono() {
		assertEquals(anual, abono.getAbono());
	}
	
	@Test
	void testSetAbono() {
		try{
			AbonoAnual a = new AbonoAnual(100.0, zona);
			abono.setAbono(a);
			assertEquals(a, abono.getAbono());
		} catch (Exception exc) { exc.printStackTrace(); }
	}
	
	@Test
	void testComprobarCaducidad() {
		assertEquals(true, abono.comprobarCaducidad());
		Calendar cad = Calendar.getInstance();
		cad.add(Calendar.YEAR, 1);
		Representacion repre = new Representacion(cad, 5);
		Evento evento = new Danza("descripcion", 10.0, "titulo", "autor", "director");
		evento.addRepresentacion(repre);
		ArrayList<Evento> eventos = new ArrayList<Evento>();
		eventos.add(evento);
		try {
		AbonoCiclo ciclo = new AbonoCiclo(25.0, eventos, zona);
		AbonoUsuario a = new AbonoUsuario(ciclo);
		assertEquals(true, a.comprobarCaducidad());
		} catch (Exception exc) { exc.printStackTrace(); }
	}

}
