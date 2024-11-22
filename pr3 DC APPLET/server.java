import java.io.*;
import java.net.*;
import java.util.Random;

public class server {
    private static final int PORT = 8080;
    private static final String[] MESSAGES = {
        "Too low. Try again!",
        "Too high. Try again!",
        "Congratulations! You guessed the number."
    };

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is listening on port " + PORT);
            Socket socket = serverSocket.accept();
            System.out.println("Client connected");

            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

                Random random = new Random();
                int randomNumber = random.nextInt(100) + 1;
                System.out.println("Random number generated: " + randomNumber);

                String guess;
                while ((guess = in.readLine()) != null) {
                    int guessNumber = Integer.parseInt(guess.trim());
                    if (guessNumber < randomNumber) {
                        out.println(MESSAGES[0]);
                    } else if (guessNumber > randomNumber) {
                        out.println(MESSAGES[1]);
                    } else {
                        out.println(MESSAGES[2]);
                        break;
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
