package test.ui;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import entrada.EntradaZonaNoNumerada;
import evento.Concierto;
import evento.Danza;
import evento.Evento;
import evento.ObraTeatro;
import evento.Representacion;
import reserva.PolíticaDeReseva;
import sistema.Sistema;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import ui.control.Control;
import ui.view.Ventana;
import usuario.TarjetaBancaria;
import usuario.Usuario;

/**
 * Aplicación del sistema de gestión de tetaro
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class UITest {
	public static void main(String... args) {
		Sistema sis = Sistema.getInstancia();
		Concierto conc = new Concierto("Concierto de la aclamadísima filarmónica de Viena que se representa una vez al año como bienvenida al nueva año", 145, "Concierto de Año Nuevo", "Bethoven", "Filarmónica de Viena", "Mozart", "Alfonso II");
		try {
		Zona z[] = {new ZonaNoNumerada("n1", 35),
				new ZonaNumerada("PruebaZN1", 0, 3),
				new ZonaNumerada("PruebaZN2", 3, 3),
				new ZonaNumerada("PruebaZN3", 3, 3),
				new ZonaNumerada("PruebaZN4", 3, 3),
				new ZonaNumerada("PruebaZN5", 3, 3),
				new ZonaNumerada("PruebaZN6", 3, 3),
				new ZonaNumerada("PruebaZN7", 3, 3),
				new ZonaNumerada("PruebaZN8", 3, 3),
				new ZonaNumerada("PruebaZN9", 3, 3),
				new ZonaNoNumerada("PruebaZNN1", 0),
				new ZonaNoNumerada("PruebaZNN2", 4),
				new ZonaNoNumerada("PruebaZNN3", 4),
				new ZonaNoNumerada("PruebaZNN4", 4),
				new ZonaNoNumerada("PruebaZNN5", 4),
				new ZonaNoNumerada("PruebaZNN6", 4),
				new ZonaNoNumerada("PruebaZNN7", 4),
				new ZonaNoNumerada("PruebaZNN8", 4),
				new ZonaNoNumerada("PruebaZNN9", 4),
				new ZonaNoNumerada("PruebaZNN10", 4),
				new ZonaNoNumerada("PruebaZNN11", 4),
				new ZonaNoNumerada("PruebaZNN12", 4),
				new ZonaNoNumerada("PruebaZNN13", 4),
				new ZonaNoNumerada("PruebaZNN14", 4),
				new ZonaNoNumerada("PruebaZNN15", 4),};
			Representacion rep = new Representacion(Calendar.getInstance(), 100);
			conc.addRepresentacion(rep);
			PolíticaDeReseva pd = new PolíticaDeReseva(3, 2, 4);
			rep.setPd(pd);
			for(int i=0; i!=25; i++) { //añadimos las zonas y les ponemos precio para la prueba
				sis.getTeatro().addZona(z[i]);
				conc.addPrecioZona(z[i], i+10);
				if(i>0 && i<=5) {
					((ZonaNumerada)z[i]).addButaca(0, 0);
					((ZonaNumerada)z[i]).addButaca(0, 1);
					((ZonaNumerada)z[i]).addButaca(2, 0);
				}
			}
			rep.getFechaYHora().set(2022, 2, 5);
			sis.addEvento(conc);
			Representacion pasada =  new Representacion(Calendar.getInstance(), 20);
			conc.addRepresentacion(pasada);
			Calendar c = Calendar.getInstance();
			c.add(Calendar.MONTH, -12);
			c.add(Calendar.MINUTE, -10);
			Representacion pasada_mas_12_meses =  new Representacion(c, 20);
			conc.addRepresentacion(pasada);
			conc.addRepresentacion(pasada_mas_12_meses);
			Usuario u = new Usuario("abc", "abc");
			u.addTarjetas(new TarjetaBancaria("1111222233334444", new Date(12-21), 666));
			u.addAbonos(new AbonoUsuario(new  AbonoAnual(15, z[3])));
			u.addAbonos(new AbonoUsuario(new  AbonoAnual(15, z[2])));
			for(int i=0; i!=10; i++)
				u.addEntradas(new EntradaZonaNoNumerada(false, pasada, (ZonaNoNumerada)z[0]));
			u.addEntradas(new EntradaZonaNoNumerada(false, pasada_mas_12_meses, (ZonaNoNumerada)z[0]));
			sis.addUsuario(u);
			ArrayList<Evento> ev = new ArrayList<Evento>();
			ev.add(conc);
			for(int i=0; i!=100; i++) {
				Concierto conc2 = new Concierto("descripcion", 120, "Concierto " + i, "yo", "tu", "el", "ellos");;
				for(int j=0; j!=30; j++) {
					Representacion rep2 = new Representacion(Calendar.getInstance(), 100);
					rep2.getFechaYHora().set(2022, 2, 5);
					rep2.setPd(pd);
					//System.out.println(rep.getFechaYHora().getTime());
					conc2.addRepresentacion(rep2);
					sis.addEvento(conc2);
					for(int b=0; b!=25; b++) { //añadimos las zonas y les ponemos precio para la prueba
						conc2.addPrecioZona(z[b], b+Math.random() + 5);
					}
				}
			}
			for(int i=0; i!=20; i++) {
				Danza conc2 = new Danza("descripcion danza", 12, "Danza " + i, ":-(", "m quiero morir");
				Representacion rep2 = new Representacion(Calendar.getInstance(), 100);
				rep2.getFechaYHora().set(2022, 2, 5);
				//System.out.println(rep.getFechaYHora().getTime());
				conc2.addRepresentacion(rep2);
				sis.addEvento(conc2);
				ev.add(conc2);
				for(int b=0; b!=25; b++) { //añadimos las zonas y les ponemos precio para la prueba
					conc2.addPrecioZona(z[b], b+Math.random() + 5);
				}
			}
			
			for(int i=0; i!=5; i++) {
				ObraTeatro conc2 = new ObraTeatro("descripcion teatro", 12, "Teatro " + i, ":-(", "m quiero morir", "comp");
				Representacion rep2 = new Representacion(Calendar.getInstance(), 100);
				rep2.getFechaYHora().set(2022, 2, 5);
				//System.out.println(rep.getFechaYHora().getTime());
				conc2.addRepresentacion(rep2);
				sis.addEvento(conc2);
				for(int b=0; b!=25; b++) { //añadimos las zonas y les ponemos precio para la prueba
					conc2.addPrecioZona(z[b], b+Math.random() + 5);
				}
			}
			for(int i=0; i!=30; i++) {
				sis.addAbono(new AbonoAnual(20, z[0]));
				sis.addAbono(new AbonoCiclo(30, ev, z[2]));
			}
			Representacion rep2 = new Representacion(Calendar.getInstance(), 100);
			rep2.getFechaYHora().set(2020, 2, 5); //una repr ya pasada para poder opinar jeje
			conc.addRepresentacion(rep2);
			//u.addEntradas(new EntradaZonaNoNumerada(false, rep2, (ZonaNoNumerada)z[0]));
			Sistema.getInstancia().login("123", "123");
			Sistema.getInstancia().cerrarSesion();
		}	catch(Exception e1) {
				e1.printStackTrace();
				return;
		}
		Ventana v = new Ventana();
		Control c = new Control(v);
		v.setControlador(c);
		//v.getUICompra().getControlCompra().setEvento(conc);
		v.setVisible(true);
	}
}
