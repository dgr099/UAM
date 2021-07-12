package sistema;

import evento.Evento;

/**
 * Clase para actualizar periodicamente las notificaciones y comentarios visibles
 * @author David Teófilo Garitagoitia Romero
 *
 */
public class ActSistema implements Runnable{

	@Override
	public void run() {
		int time = 1000*60*60;
		while(true) { /*bucle para actualizar las notificaciones del usuario*/
			try {
				Sistema.getInstancia().notificarUsuarios();
				for(Evento e : Sistema.getInstancia().getEventos()){ /*actualiza los comentarios visibles de todos los eventos*/
					e.updateComentariosVisibles(); /*los eventos que ya ha pasado su tiempo se borran*/
				}
				Thread.sleep(time); /*espera una hora para volver a notificar*/	
			} 
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
	}

}
