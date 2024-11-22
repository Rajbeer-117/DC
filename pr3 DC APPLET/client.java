import java.io.*;
import java.net.*;

public class client {
    private static final String SERVER_ADDRESS = "10.70.3.208";
    private static final int PORT = 8080;

    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
             BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

            String serverResponse;
            while (true) {
                System.out.print("Enter your guess (1-100): ");
                String guess = userInput.readLine();
                out.println(guess);

                serverResponse = in.readLine();
                System.out.println(serverResponse);

                if (serverResponse.contains("Congratulations")) {
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
