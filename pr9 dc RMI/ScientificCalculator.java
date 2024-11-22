import java.rmi.*;

public interface ScientificCalculator extends Remote {

double sin(double angle) throws RemoteException;
double cos(double angle) throws RemoteException;
double tan(double angle) throws RemoteException;
double cot(double angle) throws RemoteException;
double sec(double angle) throws RemoteException;
double cosec(double angle) throws RemoteException;
}



