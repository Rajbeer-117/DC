import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ScientificCalculatorServer {

public static void main(String[] args) {

try {

ScientificCalculator calculator = new ScientificCalculatorImpl();
Registry registry = LocateRegistry.createRegistry(5000);
registry.rebind("calculate", calculator);
System.out.println("Scientific Calculator Server is ready.");

} 

catch (Exception e) {
System.err.println("Server exception: " + e.toString());
e.printStackTrace();
}
}
}

