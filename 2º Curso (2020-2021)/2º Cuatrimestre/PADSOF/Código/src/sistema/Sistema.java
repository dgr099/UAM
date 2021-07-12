package sistema;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import abonos.Abono;
import abonos.AbonoAnual;
import abonos.AbonoCiclo;
import abonos.AbonoUsuario;
import abonos.Ciclo;
import entrada.Entrada;
import entrada.EntradaButaca;
import entrada.EntradaZonaNoNumerada;
import es.uam.eps.padsof.telecard.FailedInternetConnectionException;
import es.uam.eps.padsof.telecard.InvalidCardNumberException;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import evento.Comentario;
import evento.Concierto;
import evento.Danza;
import evento.Evento;
import evento.ObraTeatro;
import evento.Representacion;
import reserva.Reserva;
import teatro.Butaca;
import teatro.Teatro;
import teatro.Zona;
import teatro.ZonaNoNumerada;
import teatro.ZonaNumerada;
import usuario.TarjetaBancaria;
import usuario.Usuario;

/**
 * Métodos y atributos de sistema
 * @version 1.0 4 Abr 21
 * @author David Teófilo Garitagoitia Romero
 */
public class Sistema implements Serializable{
	private static Sistema instanciacion = null;
	/**
	 * 
	 */
	private static final long serialVersionUID = -92762827344452326L;
	private Teatro teatro = null; //teatro de la aplicación
	private Usuario usuarioEnUso = null; //usuario de la aplicación
	private Usuario admin = null; //administrador
	private List<Abono> abonos = new ArrayList<Abono>(); //lista de abonos
	private List<Usuario> usuarios = new ArrayList<Usuario>(); //lista de usuarios
	private List<Evento> eventos = new ArrayList<Evento>(); //lista de eventos
	private List<Ciclo> ciclos = new ArrayList<Ciclo>();
	
	/**
	 * Añade un evento a la lista de eventos del sistema
	 * @param e Evento a añadir
	 * @return booleano para saber si la acción se realizó con éxito
	 */
	public boolean addEvento(Evento e) {
		if(e==null) {
			return false;
		}
		if(eventos.contains(e) || !this.validEvent(e)) {
			return false;
		}
		eventos.add(e);
		return true;
	}

	/**
	 * Método para obtener la instancia del singleton
	 * @return objeto de la clase Sistema
	 */
	public static Sistema getInstancia(){
		if(instanciacion==null){
			instanciacion = new Sistema(25, "Teatro", "123", "123");
		}
		return instanciacion;
	}

	/**
	 * Constructor de sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param limitaciones limitaciones del teatro
	 * @param nombre nombre del teatro
	 * @param nam nombre del usuarios admin
	 * @param contr contraseña del usuario admin
	 */
	private Sistema(int limitaciones, String nombre, String nam, String contr) {
		if(!(nam==null && contr==null)) {
			Usuario admin;
			try {
				admin = new Usuario(nam, contr);
			} catch (Exception e) {
				e.printStackTrace();
				return;
			}
			this.getUsuarios().add(admin);
			this.admin=admin;
		}
		try {
			teatro = new Teatro(nombre, limitaciones);
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		Thread hilo = new Thread(new ActSistema()); /*se crea un hilo para act el sistema*/
		hilo.start(); /*se inicia la ejecución del hilo*/
	}
	
	/**
	 * Función para añadir un usuario al sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param u usuario que se pretende añadir
	 */
	public void addUsuario(Usuario u) {
		if(u==null) {
			return;
		}
		if(this.usuarios.contains(u)==true || !this.validUser(u)) {
			return;
		}
		this.usuarios.add(u);
	}
	
	/**
	 * Función para obtener el teatro
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return teatro del sistema
	 */
	public Teatro getTeatro() {
		return teatro;
	}

	/**
	 * Función para obtener el teatro
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param teatro teatro a establecer en el sistema
	 */
	public void setTeatro(Teatro teatro) {
		this.teatro = teatro;
	}

	/**
	 * Función para obtener el usuario en uso
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return usuario en uso
	 */
	public Usuario getUsuarioEnUso() {
		return usuarioEnUso;
	}

	/**
	 * Función para establecer el usuario en uso
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param usuarioEnUso
	 */
	public void setUsuarioEnUso(Usuario usuarioEnUso) {
		this.usuarioEnUso = usuarioEnUso;
	}

	/**
	 * Función para obtener el administrador del sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return usuario administrador del sistema
	 */
	public Usuario getAdmin() {
		return admin;
	}

	/**
	 * Función para obtener los abonos del sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return lista de abonos del sistema
	 */
	public List<Abono> getAbonos() {
		return abonos;
	}

	/**
	 * Función para establecer la lista de abonos del sistema
	 * @author David Teófilo Garitagoitia Romero
	 * @param abonos
	 */
	public void setAbonos(List<Abono> abonos) {
		this.abonos = abonos;
	}
	
	/**
	 * Función para añadir abonos al sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param a abono que se desea añadir
	 */
	public void addAbono(Abono a) {
		if(a==null || this.abonos.contains(a)) {
			return;
		}
		this.abonos.add(a);
		return;
	}
	
	/**
	 * Función para obtener los usuarios del sistema
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return lista de usuarios del sistema
	 */
	public List<Usuario> getUsuarios() {
		return usuarios;
	}

	/**
	 * Establecer lista de usuarios
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param usuarios usuarios a establecer
	 */
	public void setUsuarios(List<Usuario> usuarios) {
		this.usuarios = usuarios;
	}

	/**
	 * @return lista de eventos
	 */
	public List<Evento> getEventos() {
		return eventos;
	}

	/**
	 * @param eventos lista de eventos a establecer
	 */
	public void setEventos(List<Evento> eventos) {
		this.eventos = eventos;
	}

	/**
	 * Función para hacer login y cambiar el usuario en uso por otro ya registrado
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param nombre
	 * @param contr
	 * @return
	 */
	public boolean login(String nombre, String contr) {
		if(nombre==null || contr==null) {
			return false;
		}
		//System.out.println("Esto he leido, nombre: " + nombre + " contraseña: " + contr);
		for(Usuario u : this.usuarios) {
			if(u.getNombre().equals(nombre) && u.getContraseña().equals(contr)) {
				this.usuarioEnUso=u;
				return true;
			}
		}
		//scan.close();
		return false; //si no está, no se puede hacer login correctamente
	}
	
	/**
	 * Función para registrar un nuevo usuario
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param nombre nombre del usuario
	 * @param contr contraseña del usuario
	 * @return
	 */
	public boolean registro(String nombre, String contr) {
		if(nombre==null || contr==null) {
			return false;
		}
		Usuario newUser = null;
		try {
			newUser = new Usuario(nombre, contr);
		} catch (Exception e) {
			e.printStackTrace();
			//scan.close();
			return false;
		}
		if(this.validUser(newUser)==false) {
			//scan.close();
			return false;
		}
		this.usuarios.add(newUser); //si es valido el usuario, se añade a la lista de usuarios
		this.usuarioEnUso = newUser; //Se coloca al usuario activo
		//scan.close();
		return true;
		
	}
	/*
	 * comprueba que no haya dos usuarios con mismo nombre
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param u usuario a comprobar
	 * @return
	 */
	private boolean validUser (Usuario u) {
		if(u==null) {
			return false;
		}
		for(Usuario user : usuarios) {
			if(user.getNombre().equals(u.getNombre())) { /*si ya hay alguien con ese nombre*/
				return false;
			}
		}
		return true;
	}
	/**
	 * comprueba que no haya dos eventos con mismo nombre
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param e
	 * @return
	 */
	private boolean validEvent(Evento e) {
		if(e==null || e.getTitulo().contains(";")) { /*no puede contener el ; ya que se usa para el string tokenizer*/
			return false;
		}
		for(Evento e1 : this.getEventos()) {
			if(e.getTitulo().equals(e1.getTitulo())) {
				return false;
			}
		}
		return true;
	}
	/**
	 * Función para cerrar sesión, eliminar usuario activo
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 */
	public void cerrarSesion() {
		this.usuarioEnUso=null;
	}
	
	/**
	 * comprueba si el usuario en uso es el admin
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @return true en caso de estar con el admin
	 */
	public boolean comprobarAdmin() {
		if(this.usuarioEnUso==this.admin && admin!=null) {
			return true;
		}
		return false;
	}
	
	/**
	 * Función de debug para mostrar cartelera
	 */
	public void mostrarCartelera() {
		int i=1;
		if(this.comprobarAdmin()==false) //si no es el admin
			for(Evento e : this.eventos) {
				System.out.print(i + ") ");
				e.mostrarEvento();
				System.out.println(""); //para que muestre su número de opción (para seleccionar)
				++i;
			}
		else //si en cambio es el admin
			for(Evento e : this.eventos) {
				System.out.print(i + ") ");
				e.mostrarPantallaAdmin();
				System.out.println(""); //para que muestre su número de opción (para seleccionar)	
				++i;
			}
	}
	
	/**
	 * Función para seleccionar evento
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param i index del evento
	 * @return Evento seleccionado
	 */
	public Evento seleccionarEvento(int i) {
		if(i>this.eventos.size() || i<=0) {
			return null;
		}
		return this.eventos.get(i-1);
	}
	
	/**
	 * Función para obtener los eventos que contenga unas letras
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param s cadena de caracteres a contener
	 * @return lista de eventos con esa string
	 */
	public List<Evento> busqueda(String s) {
		List<Evento> ev = new ArrayList<Evento>();
		if(s==null) {
			return null;
		}
		for(Evento e : this.eventos) {
			if(e.getTitulo().contains(s)) {
				ev.add(e);
			}
		}
		return ev;
	}
	
	/**
	 * Función para filtrar eventos por tipo
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param tipo tipo de evento 1->conciero 2->danza 3->teatro 
	 * @return lista de eventos del tipo
	 */
	public List<Evento> filtrarEvento(int tipo){
		Evento ev = null;
		List<Evento> eventos = new ArrayList<Evento>();
		switch (tipo) {
		case 1:
			ev = new Concierto(null, 0, null, null, null, null, null);
			break;
		case 2:
			ev = new Danza(null, 0, null, null, null);
			break;
		case 3:
			ev = new ObraTeatro(null, 0, null, null, null, null);
			break;
		default:
			return null;
		}
		
		for(Evento e : this.eventos) {
			if(e.getClass()==ev.getClass()) {
				eventos.add(e);
			}
		}
		return eventos;
	}
	/**
	 * Función para seleccionar zona
	 * @param nombre nombre de la zona a seleccionar
	 * @return zona con el nombre pasado por argumento
	 */
	public Zona seleccionarZona(String nombre) {
		for(Zona z : this.teatro.getZonas()) {
			if(z.getNombre().equals(nombre)) {
				return z;
			}
		}
		return null;
	}
	
	/**
	 * Función para comprar entrada
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param r representacion donde comprar entrada
	 * @param z zona donde comprar entrada
	 * @return booleano en función del resultado
	 */
	public boolean comprarEntrada(Representacion r, Zona z, TarjetaBancaria tb) {
		//con los datos introducidos se genera la entrada y después se llama al método comprar entrada de la clase usuario
		Entrada e = null;
		if(z==null || r==null)	return false;
		if(z instanceof ZonaNoNumerada) {
			try {
				e = new EntradaZonaNoNumerada(false, r, (ZonaNoNumerada)z);
			} catch (Exception e1) {
				e1.printStackTrace();
				return false;
			}
		}
		else { 
			return false;
		}
		try {
			return this.usuarioEnUso.comprarEntrada(e, tb);
		} catch (Exception e1) {
			e1.printStackTrace();
			return false;
		}
	}
	
	/**
	 * Función para comprar entrada de zona de butacas
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param r representacion
	 * @param z zona
	 * @param tb tarjeta bancaria
	 * @param f fila
	 * @param c columna 
	 * @return booleano para saber si se realizo correctamente
	 */
	public boolean comprarEntrada(Representacion r, ZonaNumerada z, TarjetaBancaria tb, int f, int c) {
		//con los datos introducidos se genera la entrada y después se llama al método comprar entrada de la clase usuario
		Entrada e = null;
		if(z==null || r==null)	return false;
		else { 
			try {
				e = new EntradaButaca(false, r, z.searchButaca(f, c));
			} catch (Exception e1) {
				e1.printStackTrace();
				return false;
			}
		}
		try {
			return this.usuarioEnUso.comprarEntrada(e, tb);
		} catch (Exception e1) {
			e1.printStackTrace();
			return false;
		}
	}
	/**
	 * Función para comprar entrada de zona de butacas
     * @version 1.0 3 Jun 21
     * @author David Teófilo Garitagoitia Romero
	 * @param r representacion
	 * @param z zona
	 * @param tb tarjeta bancaria
	 * @param b butaca para la que se desea comprar la entrada
	 * @return booleano para saber si se realizo correctamente
	 */
	public boolean comprarEntrada(Representacion r, ZonaNumerada zonaNumerada, TarjetaBancaria tarjetaSeleccionada,
			Butaca butaca) {
		if(butaca==null) {
			return false;
		}
		int f = butaca.getFila();
		int c = butaca.getColumna();
		return comprarEntrada(r, zonaNumerada, tarjetaSeleccionada, f, c);
	}
	/**
	 * función auxiliar para mostrar butacas disponibles
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param r representacion
	 * @param z zona
	 */
	public void mostrarButacasDisponibles(Representacion r, Zona z) {
		if(r==null || z==null) {
			return;
		}
		for(Butaca[] b : ((ZonaNumerada)z).getButacas()) {
			for(int i=0; i!=((ZonaNumerada)z).getColumnas(); i++) {
				if(b[i]!=null && !r.getButacasOcupadas().contains(b[i]) && b[i].isActiva()) { /*si hay butaca, no está ocupada y está activa*/
					b[i].mostrarButaca();
				}
				System.out.print("\t");
			}
			System.out.println("");
		}
	}
	
	/**
	 * Función auxiliar para debugear
	 */
	public void mostrarAbonos() {
		for(Abono a : this.abonos) {
			a.mostrarAbono();
		}
	}
	
	/**
	 * Función para seleccionar abono
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 * @param cod
	 * @return
	 */
	public Abono seleccionarAbono(String cod) {
		for(Abono a : this.abonos) {
			if(a.getCodigo()==cod) {
				return a;
			}
		}
		return null;
	}
	
	/**
	 * Metodo para comprar un abono
	 * @param a contiene el abono a comprar
	 * @param numTarjeta contiene el codigo de la tarjeta bancaria a usar
	 * @return true si se ha comprado correctamente, sino false
	 * @throws Exception 
	 * @throws OrderRejectedException 
	 * @throws FailedInternetConnectionException 
	 * @throws InvalidCardNumberException 
	 */
	public boolean comprarAbono(Abono a, String numTarjeta) throws InvalidCardNumberException, FailedInternetConnectionException, OrderRejectedException, Exception {
		return this.usuarioEnUso.comprarAbono(a, this.usuarioEnUso.seleccionarTarjeta(numTarjeta));
	}
	
	/**
	 * Metodo para usar un abono a la hora de comprar una entrada
	 * @param e entrada a comprar
	 * @param a abono a usar
	 * @return true si se ha usado correctamente el abono, sino false
	 */
	public boolean usarAbono(Entrada e, AbonoUsuario a) {
		Abono abono = a.getAbono();
		if(!a.comprobarCaducidad() || !abono.comprobarValidez(e)) {
			return false; }
		if(abono instanceof AbonoCiclo) {
			((AbonoCiclo)abono).delEventos(e.getRepresentacion().getEvento());
			return true;
		}
		else if(abono instanceof AbonoAnual) {
			((AbonoAnual)abono).addEntradas(e);
			return true;
		}
		return false;
	}
	
	/*comprueba si se han caducado las reservas*/
	/**
	 * Función para notificar a los usuarios
     * @version 1.0 4 Abr 21
     * @author David Teófilo Garitagoitia Romero
	 */
	public void notificarUsuarios() { /*cuando haya nuevo hueco manda una notificación a los usuarios*/
		Map<Representacion, List<String>> res = new LinkedHashMap<Representacion, List<String>>();
		/*primero se comprueba que reservas están caducadas y se hace una lista de representaciones con reservas caducadas*/
		for(Usuario u : this.usuarios) {
			List<Reserva> caducadas = new ArrayList<Reserva>();
			for(Reserva r : u.getReservas()) {
				if(Calendar.getInstance().getTime().after(r.getCad().getTime())) { /*si ya pasó el tiempo para la reserva*/
					r.liberarButaca2(); /*liberamos la butaca*/
					caducadas.add(r);
					List<String> newList = new ArrayList<String>();
					if(res.containsKey(r.getRepresentacion())) {
						newList = res.get(r.getRepresentacion());
						newList.add(r.getButaca().toString());
						res.put(r.getRepresentacion(), newList);
					}
					newList.add(r.getButaca().toString());
					res.put(r.getRepresentacion(), newList); /*añadimos la representacion de la reserva a la lista de reservas*/
				}
			}
			u.getReservas().removeAll(caducadas); /*borramos de las reservas las que estén caducadas*/
		}
		/*después se avisa a todos los usuarios en lista de espera de las representacion con reservas canceladas*/
		for(Entry<Representacion, List<String>> entry : res.entrySet()) {
			Representacion rp = entry.getKey();
			for(Usuario u : rp.getLista()) {
				/*en caso de estar en la lista de espera se le envía una notificación*/
				u.addNotificacion(rp.getEvento().getTitulo() + "; con fecha " + rp.getFechaYHora().getTime() + " tiene entrada disponibles en:\n" + entry.getValue().toString());
			}
		}
	}
	
		/**
		 * Función para guardar el estado del sistema
		 * @version 1.0 4 Abr 21
		 * @author David Teófilo Garitagoitia Romero
		 * @return
		 */
	public boolean saveSistema(){
		ObjectOutputStream o = null;
		try {
			
			/*guardamos uno a uno los campos*/
			Sistema s = Sistema.instanciacion;
			
			o = new ObjectOutputStream(new FileOutputStream("./files/sistema.dat"));
			o.writeObject(s);
			o.close();
			
			/*los datos estáticos*/
			/*primero el de butaca*/
			o = new ObjectOutputStream(new FileOutputStream("./files/butaca_id_last.dat"));
			o.writeObject(Butaca.getIdLast());
			o.close();
			/*para abonos*/
			o = new ObjectOutputStream(new FileOutputStream("./files/abono_last.dat"));
			o.writeObject(Abono.getCodigoLast());
			o.close();
			/*para ciclos*/
			o = new ObjectOutputStream(new FileOutputStream("./files/ciclo_last.dat"));
			o.writeObject(Ciclo.getLast());
			o.close();
			/*para entradas*/
			o = new ObjectOutputStream(new FileOutputStream("./files/entrada_last.dat"));
			o.writeObject(Entrada.getNumeroEntrdas());
			o.close();
			/*para reserva*/
			o = new ObjectOutputStream(new FileOutputStream("./files/reserva_last.dat"));
			o.writeObject(Reserva.getNumeroReservas());
			o.close();
			/*para comentario*/
			o = new ObjectOutputStream(new FileOutputStream("./files/comentario_last.dat"));
			o.writeObject(Comentario.getNumT());
			o.close();
			
		}catch(Exception e){
			e.printStackTrace();
			return false;
		}
		return true;
	}

		/**
		 * Función para cargar el sistema
		 * @version 1.0 4 Abr 21
		 * @author David Teófilo Garitagoitia Romero
		 * @return
		 */
	public boolean loadSistema() {
		ObjectInputStream entrada = null;
		try {
			entrada = new ObjectInputStream(new FileInputStream("./files/sistema.dat"));
			Sistema s = (Sistema) entrada.readObject();
			entrada.close();
			Sistema.instanciacion = s;
			
			entrada = new ObjectInputStream(new FileInputStream("./files/butaca_id_last.dat"));
			long butaca_last = (long) entrada.readObject();
			Butaca.setIdLast(butaca_last);
			entrada.close();
			
			entrada = new ObjectInputStream(new FileInputStream("./files/abono_last.dat"));
			int abono_last = (int) entrada.readObject();
			Abono.setCodigoLast(abono_last);
			entrada.close();
			
			entrada = new ObjectInputStream(new FileInputStream("./files/ciclo_last.dat"));
			int ciclo_last = (int) entrada.readObject();
			Ciclo.setLast(ciclo_last);
			entrada.close();
			
			entrada = new ObjectInputStream(new FileInputStream("./files/entrada_last.dat"));
			int entrada_last = (int) entrada.readObject();
			Entrada.setNumeroEntradas(entrada_last);;
			entrada.close();
			
			entrada = new ObjectInputStream(new FileInputStream("./files/reserva_last.dat"));
			int reservas_last = (int) entrada.readObject();
			Reserva.setNumeroReservas(reservas_last);
			entrada.close();
			
			entrada = new ObjectInputStream(new FileInputStream("./files/comentario_last.dat"));
			int comentario_last = (int) entrada.readObject();
			Comentario.setNumT(comentario_last);
			entrada.close();
		    
		}catch(Exception e){ /*si no se puede cargar devolvemos false (error)*/
			e.printStackTrace();
			return false;
		}
		return true;
	}
		
		/**
		 * Función para eliminar un evento del sistema
		 * @param e Evento que se desea borrar
		 */
		public void removeEvent(Evento e) {
			this.eventos.remove(e);
		}
		
		/**
		 * Función para eliminar un abono del sistema
		 * @param a Abono que se desea borrar
		 */
		public void removeAbono(Abono a) {
            this.abonos.remove(a);
        }
		
		/**
		 * Método para añadir ciclos al sistema
		 * @param c ciclo que se desea añadir
		 */
		public void addCiclo(Ciclo c) {
			if(this.ciclos.contains(c)) {
				return;
			}
			this.ciclos.add(c);
		}
		
		/**
		 * Método para obtener los ciclos del sistema
		 * @return
		 */
		public List<Ciclo> getCiclos(){
			return this.ciclos;
		}
	}
