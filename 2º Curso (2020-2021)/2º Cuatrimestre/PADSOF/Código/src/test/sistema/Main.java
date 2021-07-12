package test.sistema;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;
import test.abono.*;
import test.entrada.*;
import test.evento.*;
import test.reserva.*;
import test.teatro.*;
import test.usuario.*;

@RunWith(Suite.class)
@SuiteClasses({
    AbonoAnualTest.class,
    AbonoCicloTest.class,
    AbonoUsuarioTest.class,
    EntradaButacaTest.class,
    EntradaZonaNoNumeradaTest.class,
    EventoTest.class,
    ReservaTest.class,
    SistemaTest.class,
    ButacaTest.class,
    TeatroTest.class,
    ZonaNumeradaTest.class,
    testTarjeta.class,
    testUsuario.class
})


public class Main {
    
}