package test;
import org.junit.platform.runner.JUnitPlatform;
import org.junit.platform.suite.api.SelectPackages;
import org.junit.runner.RunWith;
@RunWith(JUnitPlatform.class)
@SelectPackages({"test.abono", "test.entrada", "test.usuario", "test.evento", "test.reserva", "test.sistema", "test.teatro"}) 

public class AllTests {
	
}