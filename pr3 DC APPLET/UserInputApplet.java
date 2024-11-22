import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.TextField;
import java.awt.Button;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserInputApplet extends Applet {
    private TextField usernameField;
    private TextField passwordField;
    private Button submitButton;
    private String displayText = "";

    @Override
    public void init() {
       
        add(new Label("Username:"));
        usernameField = new TextField(20);
        add(usernameField);

        add(new Label("Password:"));
        passwordField = new TextField(20);
        passwordField.setEchoChar('*'); // Mask the password input
        add(passwordField);

        submitButton = new Button("Submit");
        add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = passwordField.getText();
                displayText = "Username: " + username + ", Password: " + password;
                repaint(); // Refresh the applet to show the new text
            }
        });
    }

    @Override
    public void paint(Graphics g) {
        g.drawString(displayText, 20, 100);
    }
}

