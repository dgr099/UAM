package usuario;

import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.Calendar;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

import abonos.Abono;
import abonos.AbonoUsuario;
import entrada.Entrada;
import entrada.EntradaButaca;
import es.uam.eps.padsof.telecard.FailedInternetConnectionException;
import es.uam.eps.padsof.telecard.InvalidCardNumberException;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import es.uam.eps.padsof.telecard.TeleChargeAndPaySystem;
import evento.Comentario;
import evento.Evento;
import evento.Representacion;
import reserva.Reserva;
import sistema.Sistema;
import teatro.Butaca;

/**
 * Clase Usuario
 * @version 1.0 28 Mar 28
 * @author Jonás Arce García
 * @author David Teófilo Garitagoitia Romero
 * @author Daniel Cerrato Sánchez
 */

public class Usuario implements Serializable{
	private String nombre;
	private String contraseña;
	private static final long serialVersionUID = 8032973568981129903L;
	private List<Notificacion> notificaciones = new ArrayList<Notificacion>();
	//private ArrayList <String> notificaciones = new ArrayList<>();
	private List <TarjetaBancaria> tarjetas = new ArrayList<>();
	private List <Entrada> entradas = new ArrayList<>(); 
	private List <AbonoUsuario> abonos = new ArrayList<>();
	private List <Reserva> reservas = new ArrayList<>();
	private Map<Representacion, Integer> nReservas = new TreeMap<>();
	/**
	 * Constructor de la clase Usuario
	 * @param nom nombre del usuario
	 * @param contra contraseña del usuario
	 * @throws Exception
	 */
	public Usuario(String nom, String contra) throws Exception{
		this.nombre = nom;
		this.contraseña = contra;
	}
	
	/**
	 * Función que obtiene el número de reservas del usario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return el número de reservas del usuario
	 */
	public Map<Representacion, Integer> getNReservas(){
		return this.nReservas;
	}
	
	/**
	 * Función que obtiene las reservas del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return el array de reservas del usuario
	 */
	 public List<Reserva> getReservas() {
		 return this.reservas;
	 }

	/**
	 * Función que devuelve el nombre del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return nombre del usuario
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Función que asigna el nombre del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param nombre nombre del usuario
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Función que obtiene la contraseña del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return contraseña del usuario
	 */
	public String getContraseña() {
		return contraseña;
	}

	/**
	 * Función que asigna la contraseña del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param contraseña contraseña a asignar
	 */
	public void setContraseña(String contraseña) {
		this.contraseña = contraseña;
	}

	/**
	 * Función que obtiene las notificaciones del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return array de notificaciones del usuario
	 */
	public	List<String> getNotificaciones() {
		List<String> mensajes = new ArrayList<String>();
		for(Notificacion n : this.notificaciones) {
			mensajes.add(n.getMensaje());
		}
		return mensajes;
	}
	
	/**
	 * Función que obtiene las notificaciones del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @return array de notificaciones del usuario
	 */
	public	List<Notificacion> getNotificacionesList() {
		return this.notificaciones;
	}
	/**
	 * Método para confirmar una reserva (pagar la entrada de la butaca reservada)
	 * @param codTarjeta cod de la tarjeta con la que pagar la reserva
	 * @return booleano que define si la operación resultó o no exitosa
	 */
	public boolean confirmarReserva(String codTarjeta, Reserva r) {
		if(codTarjeta == null || r == null) {
			return false;
		}
		r.getRepresentacion().getButacasOcupadas().remove(r.getButaca()); /*quitamos la butaca de las butacas ocupadas*/
		try {
			Sistema.getInstancia().comprarEntrada(r.getRepresentacion(), r.getButaca().getZonaButaca(), this.seleccionarTarjeta(codTarjeta), r.getButaca());
		} catch (Exception e) {
			e.printStackTrace();
			r.getRepresentacion().getButacasOcupadas().add(r.getButaca()); /*la volvemos a meter en la reserva en caso de error*/
			return false; /*retornamos false para indicar que no se pudo reservar con éxito*/
		}
		r.getRepresentacion().getButacasOcupadas().add(r.getButaca()); /*la volvemos a poner como ocupada*/
		this.getReservas().remove(r); /*borramos la reserva que se hizo satisfacotriamente*/
		return true;
	}
	
	/**
	 * Función para confirmar una reserva mediante un abono
	 * @param a Abono de usuario a usar para confirmar la reserva
	 * @param r Reserva a confirmar
	 * @return
	 */
	public boolean confirmarReserva(AbonoUsuario a, Reserva r) {
		if(a == null || r == null || a.getAbono() == null) {
			return false;
		}
		Entrada ent;
		r.getRepresentacion().getButacasOcupadas().remove(r.getButaca()); /*quitamos la butaca de las butacas ocupadas*/
		try {
			ent = new EntradaButaca(true, r.getRepresentacion(), r.getButaca());
			ent.setUsuario(this);
			if(Sistema.getInstancia().usarAbono(ent, a)==false) {
				return false;
			}
		} catch (Exception e) {
			e.printStackTrace();
			r.getRepresentacion().getButacasOcupadas().add(r.getButaca()); /*la volvemos a meter en la reserva en caso de error*/
			return false; /*retornamos false para indicar que no se pudo reservar con éxito*/
		}
		r.getRepresentacion().getButacasOcupadas().add(r.getButaca()); /*la volvemos a poner como ocupada*/
		this.getReservas().remove(r); /*borramos la reserva que se hizo satisfacotriamente*/
		this.addEntradas(ent);
		ent.setUsuario(this);
		return true;
	}

	
	/**
	 * Función que añade una tarjeta al array de tarjetas del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param t	tarjeta tipo TarjetaBancaria
	 * @throws Exception
	 */
	public void addTarjetas(TarjetaBancaria t) throws Exception{
		if(this.tarjetas.contains(t)) { /*si ya contiene esa tarjeta*/
			new Exception("Ya contiene esa tarjeta");
		} else {
		this.tarjetas.add(t);
		}
	}
	
	/**
	 * Función que selecciona una tarjeta del array de tarjetas del usuario si existe una que 
	 * coincida con el número de tarjeta introducido
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param numTarjeta número de la tarjeta que quieres seleccionar
	 * @return tarjeta del array de tarjetas cuyo número corresponde al numTarjeta pasado por
	 * argumento, en caso de error null
	 * @throws Exception
	 */
	public TarjetaBancaria seleccionarTarjeta(String numTarjeta) throws Exception{
		for(int i=0; i<tarjetas.size(); i++) {
			if(tarjetas.get(i).getNumTarjeta() == numTarjeta) {
				return tarjetas.get(i);
			} 
		}
		throw new Exception("No existe ninguna tarjeta con ese número entre sus tarjetas");
	}
	
	/**
	 * Función que añade una entrada al array de entradas del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param e entrada que se desea añadir
	 */
	public void addEntradas(Entrada e) {
		if(this.entradas.contains(e)) { /*si ya contiene esa entrada*/
			new Exception("Ya contiene esa entrada");
		} else {
		this.entradas.add(e);
		e.setUsuario(this);
		}
	}
	
	/**
	 * Método para añadir comentario a una entrada
	 * @param e entrada a la que añadir el comentario
	 * @param c string con el mensaje del comentario
	 */
	public void añadirComentario(Entrada e, String c) {
		if(e==null || c==null) {
			return;
		}
		e.setComentario(c);
		return;
	}
	
	/**
	 * Función que compra una entrada y la carga en la tarjeta del usuario cuyo número se le
	 * pide con un scan para seleccionar una de sus tarjetas usando el método
	 * seleccionarTarjeta(), si cualquier cosa de estas falla se devuelve false
	 * en caso contrario se devuelve true y se añade esa entrada al array de
	 * entradas del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
 	 * @author David Teófilo Garitagoitia
	 * @param e entrada que se desea comprar
	 * @return true o false dependiendo de si se realiza correectamente la compra
	 * @throws Exception
	 * @throws InvalidCardNumberException
	 * @throws FailedInternetConnectionException
	 * @throws OrderRejectedException
	 */
	public boolean comprarEntrada(Entrada e, TarjetaBancaria t) throws Exception, InvalidCardNumberException, FailedInternetConnectionException, OrderRejectedException {
		if(seleccionarTarjeta(t.getNumTarjeta()) != null) {
		if(TeleChargeAndPaySystem.isValidCardNumber(t.getNumTarjeta()) == true) {
			TeleChargeAndPaySystem.charge(t.getNumTarjeta(), "Entrada,", e.getPrecio(), true);
			addEntradas(e);
			e.setUsuario(this);
			e.generarPDF();
			return true;
		} else { new Exception("Error en el pago con tarjeta");
			return false; }
		} else { new Exception("No dispones de una tarjeta con ese número");
			return false; }
	}
	
	/**
	 * Función que añade un abono usuario al array de abonos de usuarios
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param a abono usuario que se desea añadir
	 * @throws Exception
	 */
	public void addAbonos(AbonoUsuario a) throws Exception{
		if(this.abonos.contains(a)) { /*si ya contiene esa abono*/
			new Exception("Ya contiene ese abono");
		} else {
		this.abonos.add(a);
		}
	}
	
	/**
	 * Función que compra un abono y lo carga en la tarjeta del usuario cuyo número se le
	 * pide con un scan para seleccionar una de sus tarjetas usando el método
	 * seleccionarTarjeta(), si cualquier cosa de estas falla se devuelve false
	 * en caso contrario se devuelve true y se añade esa abono al array de
	 * abonos del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param a abono a añadir
	 * @param t tarjeta bancaria con la que se va a realizar el pago
	 * @return true o false
	 * @throws Exception
	 * @throws InvalidCardNumberException
	 * @throws FailedInternetConnectionException
	 * @throws OrderRejectedException
	 */
	public boolean comprarAbono(Abono a, TarjetaBancaria t) throws Exception, InvalidCardNumberException, FailedInternetConnectionException, OrderRejectedException {
		if(seleccionarTarjeta(t.getNumTarjeta()) != null) {
		if(TeleChargeAndPaySystem.isValidCardNumber(t.getNumTarjeta()) == true) {
			AbonoUsuario abono = new AbonoUsuario(a);
			this.addAbonos(abono);
			return true;
		} else { throw new Exception("Error en el pago con tarjeta");
		}
		} else { throw new Exception("No dispones de una tarjeta con ese número");
		}
	}

	/**
	 * Función que añade al usuario en el array de usuarios listaDeEspera de representacion,
	 * si no se puede acceder a la lista de espera se devuelve false, en caso
	 * contrario true
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param r (Representacion)
	 * @return true o false
	 * @throws Exception
	 */
	public boolean entrarListaEspera(Representacion r) throws Exception {
		if(r==null) {
			new Exception("No se pudo acceder a la lista de espera");
			return false;
		}
		r.addLista(this);	
		return true;
	}
	
	/**
	 * Función que reserva una butaca pasándole su respectiva representacion y la butaca en sí,
	 * si ya se tenía alguna reserva para dicha representación o bien se han cumplido
	 * el máximo de reservas se devuelve false en caso contrario true
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param r (Representacion)
	 * @param b	(Butaca)
	 * @return true o false
	 * @throws Exception
	 */
	public boolean reservarButaca(Representacion r, Butaca b) throws Exception {
		if (r.getButacasOcupadas().contains(b) == false) { 
			if (this.getNReservas().containsKey(r) == true) { 
				if (this.getNReservas().get(r) == r.getPd()
						.getMax()) { 
					return false;
				}
			}
			try {
				reservas.add(new Reserva(r, b));
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
		}
		if(this.getNReservas().containsKey(r))
			this.getNReservas().put(r, this.getNReservas().get(r)+1);
		else
			this.getNReservas().put(r, 1);
		return true;
	}
	
	/**
	 * Funciión que coge los abonos del array de abonos del usuario
	 * @version 1.0 28 Mar 28
 	 * @author Daniel Cerrato Sánchez
	 * @return abonos
	 */
	public List<AbonoUsuario> getAbonos(){
		return this.abonos;
	}
	
	/**
	 * Compra una entrada y la carga en el abono del usuario cuyo número se le
	 * pide con un scan para seleccionar una de sus abonos usando el método
	 * seleccionarAbono(), si cualquier cosa de estas falla se devuelve false
	 * en caso contrario se devuelve true y se añade esa entrada al array de
	 * entradas del usuario.
	 * @param e (Entrada)
	 * @param a (AbonoUsuario)
	 * @return true o false
	 * @throws Exception
	 * @throws InvalidCardNumberException
	 * @throws FailedInternetConnectionException
	 * @throws OrderRejectedException
	 */
	public boolean comprarEntrada(Entrada e, AbonoUsuario a) throws Exception{
		if(a == null || !this.abonos.contains(a) || !Sistema.getInstancia().usarAbono(e, a)) { 
			new Exception("Error en el abono");
			return false;
		}
		return true;
	}
	
	/**
	 * Muestra por pantalla las reservas del arraylist de reservas del usuario (para debuggear)
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 */
	public void mostrarReservas(){
		if(reservas.size() == 0) {
			System.out.print("No dispones de ninguna reserva actualmente");
		}else System.out.print("Estas son tus reservas: " + reservas);
	}
	
	/**
	 * Devuelve una reserva del array de reservas del usuario cuya posición se
	 * pasa como argumento o null en caso de que no exista una reserva con ese número
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param o (int)
	 * @return reservas.get(o) (Reserva) o null
	 */
	public Reserva SeleccionarReserva(int o) {
		if(o > reservas.size() || o < 0) {
			System.out.print("No existe una reserva con ese número");
			return null;
		} else return reservas.get(o);
	}
	
	/**
	 * Cancela una reserva pasada por argumento, es decir la quita del array
	 * de reservas del usuario, además libera su respectiva butaca y decrementa
	 * el número de reservas de la representación
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param r
	 * @return true o false
	 */
	public boolean cancelarReserva(Reserva r) {
		if(r==null) {
			return false;
		}
		r.liberarButaca();
		this.getNReservas().put(r.getRepresentacion(), this.getNReservas().get(r.getRepresentacion())-1); 
		this.getReservas().remove(r);
		Sistema.getInstancia().notificarUsuarios();
		return true;
	}
	
	/**
	 * Saca al usuario del array de usuarios listaDeEspera de la clase Representacion
	 * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
	 * @param r (Representacion)
	 */
	public void salirLista(Representacion r) {
		if(r==null) {
			return;
		}
		r.salirLista(this);
		return;
	}
	
	/**
     * Crea la clave de encriptacion usada internamente
     * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
     * @param clave Clave que se usara para encriptar
     * @return Clave de encriptacion
     * @throws UnsupportedEncodingException
     * @throws NoSuchAlgorithmException 
     */
    private SecretKeySpec crearClave(String clave) throws UnsupportedEncodingException, NoSuchAlgorithmException {
        byte[] claveEncriptacion = clave.getBytes("UTF-8");
        
        MessageDigest sha = MessageDigest.getInstance("SHA-1");
        
        claveEncriptacion = sha.digest(claveEncriptacion);
        claveEncriptacion = Arrays.copyOf(claveEncriptacion, 16);
        
        SecretKeySpec secretKey = new SecretKeySpec(claveEncriptacion, "AES");

        return secretKey;
    }
    
    /**
     * Aplica la encriptacion AES a la cadena de texto usando la clave indicada
     * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
     * @param contra (contrasenia) a encriptar
     * @param claveSecreta Clave para encriptar
     * @return Información encriptada
     * @throws UnsupportedEncodingException
     * @throws NoSuchAlgorithmException
     * @throws InvalidKeyException
     * @throws NoSuchPaddingException
     * @throws IllegalBlockSizeException
     * @throws BadPaddingException 
     */
    public String encriptar(String contra, String claveSecreta) throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        SecretKeySpec secretKey = this.crearClave(claveSecreta);
        
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");        
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);

        byte[] datosEncriptar = contra.getBytes("UTF-8");
        byte[] bytesEncriptados = cipher.doFinal(datosEncriptar);
        String encriptado = Base64.getEncoder().encodeToString(bytesEncriptados);

        return encriptado;
    }
    
    /**
     * Desencripta la cadena de texto indicada usando la clave de encriptacion
     * @version 1.0 28 Mar 28
 	 * @author Jonás Arce García
     * @param Contrasenia encriptada
     * @param claveSecreta Clave de encriptacion
     * @return Contrasenia desencriptada
     * @throws UnsupportedEncodingException
     * @throws NoSuchAlgorithmException
     * @throws InvalidKeyException
     * @throws NoSuchPaddingException
     * @throws IllegalBlockSizeException
     * @throws BadPaddingException 
     */
    public String desencriptar(String contraEncriptada, String claveSecreta) throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        SecretKeySpec secretKey = this.crearClave(claveSecreta);

        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5PADDING");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        
        byte[] bytesEncriptados = Base64.getDecoder().decode(contraEncriptada);
        byte[] datosDesencriptados = cipher.doFinal(bytesEncriptados);
        String datos = new String(datosDesencriptados);
        
        return datos;
    }
    
    /**
     * Función para obtener la lista de tarjetas del usuario
     * @return
     */
    public List<TarjetaBancaria> getTarjetas(){
    	return this.tarjetas;
    }
    
    public List<Entrada> getEntradas(){
    	return this.entradas;
    }
    
	/**
	 * Método para aprobar un comentario, comprueba si el usuario en uso es un admin, y en ese caso,
	 * le permite aprobar el comentario con índice pasado por argumento
	 * @param Comentario a aprobar
	 * @param e Evento del que se quiere aprobar el comentario i
	 */
	public void aprobarComentario(Comentario c, Evento e) {
		if(!this.equals(Sistema.getInstancia().getAdmin()) || c==null || e==null) {
			return;
		}
		if(!e.getComentariosEnEsperaDeAprobación().contains(c)) {
			return;
		}
		e.getComentariosEnEsperaDeAprobación().remove(c);
		Calendar cal = Calendar.getInstance();
		cal.setTime(c.getE().getRepresentacion().getFechaYHora().getTime());
		cal.add(Calendar.MONTH, 12);
		if(Calendar.getInstance().after(cal)) { /*si ya pasaron los 12 meses de visibilidad*/
			e.getComentariosNoVisibles().add(c);
			c.setNotVisible(); /*se pone el comentario en modo no visible*/
		}
		else {
			e.getComentariosVisibles().add(c);
			c.aprobarComentario(); /*modo visible y aprobado*/
		}
		return;
	}
	
	/**
	 * Método para obtener las notificaciones
	 * @return lista de notificaciones
	 */
	public List<Notificacion> getMensajes(){
		return this.notificaciones;
	}
	
	/**
	 * Método para añadir una nueva notificación
	 * @param m mensaje de la notificación a añadir
	 */
	public void addNotificacion(String m) {
		this.notificaciones.add(new Notificacion(m));
	}
	
	/**
	 * Método para solicitar a un usuario cambios en su comentario
	 * @param c comentario del que se solicitan cambios
	 */
	public void solicitarCambio(Comentario c) {
		if(c==null) {
			return;
		}
		if(!(Sistema.getInstancia().getUsuarioEnUso().getNombre().equals(this.nombre) && Sistema.getInstancia().getUsuarioEnUso().getContraseña().equals(this.contraseña))) {
			return;
		}
		else {
			c.getU().addNotificacion("El administrados ha solicitado cambios en su comentario:\n" + c.getMensaje() + "\n del evento: " + c.getE().getRepresentacion().getEvento() + "del día " + c.getE().getRepresentacion().getFechaYHora().getTime());
			c.solicitarModificacion(); /*se pone el comentario en modo solicitar revision*/
			return;
		}
	}
}
