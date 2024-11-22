import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class ScientificCalculatorImpl extends UnicastRemoteObject implements ScientificCalculator 
{
protected ScientificCalculatorImpl() throws RemoteException {
super();
}
@Override
public double sin(double angle) throws RemoteException {
return Math.sin(angle); // angle in radians
}
@Override
public double cos(double angle) throws RemoteException {
return Math.cos(angle); // angle in radians
}
@Override
public double tan(double angle) throws RemoteException {
return Math.tan(angle); // angle in radians
}
@Override
public double cot(double angle) throws RemoteException {
return 1.0 / Math.tan(angle); // Cotangent is reciprocal of tangent
}
@Override
public double sec(double angle) throws RemoteException {
return 1.0 / Math.cos(angle); // Secant is reciprocal of cosine
}
@Override
public double cosec(double angle) throws RemoteException {
return 1.0 / Math.sin(angle); // Cosecant is reciprocal of sine }
}
}
