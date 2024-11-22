import java.rmi.*;
import java.util.Scanner;

public class Client12 {

public static void main(String[] args) {

Scanner scanner = new Scanner(System.in);
System.out.println("Choose a scientific operation: ");
System.out.println("1. Sine (sin)");
System.out.println("2. Cosine (cos)");
System.out.println("3. Tangent (tan)");
System.out.println("4. Cotangent (cot)");
System.out.println("5. Secant (sec)");
System.out.println("6. Cosecant (cosec)");
int operation = scanner.nextInt();
if (operation < 1 || operation > 6) {

System.out.println("Invalid operation choice.");
scanner.close();
return;
}

System.out.print("Enter angle in radians: ");
double angle = scanner.nextDouble();

try {
ScientificCalculator stub = (ScientificCalculator)
Naming.lookup("rmi://localhost:5000/calculate");
switch (operation) {
case 1:
System.out.println("sin(angle): " + stub.sin(angle));
break;
case 2:
System.out.println("cos(angle): " + stub.cos(angle));break;
case 3:
System.out.println("tan(angle): " + stub.tan(angle));
break;
case 4:
System.out.println("cot(angle): " + stub.cot(angle));
break;
case 5:
System.out.println("sec(angle): " + stub.sec(angle));
break;
case 6:
System.out.println("cosec(angle): " + stub.cosec(angle));
break;
default:
System.out.println("Invalid operation choice.");
break;
}
}
 catch (Exception e) 
 {
System.out.println("Error: " + e.toString());
} 
finally 
{
scanner.close();
}
}
}
