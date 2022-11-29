/* COP3331
 * IGLI DURO
 * U33766202 */
 
 /* In this lab, you will create a GUI application.  
  * This application starts with a window containing 7 buttons with 1-7 stars on them (* to *******), 
  * in a horizontal line and in random order.  The random order should be different each time the program runs.  
  * Initially, only the * button should be enabled (setDisable(false)), but clicking that button should disable it (setDisable(true)) and enable the ** button.  
  * Likewise, ** disables itself and enables ***, and so forth, with ******* enabling nothing. */

import java.util.ArrayList;
import java.util.Collections;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Orientation;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.TilePane;
import javafx.stage.Stage;

public class example extends Application {
        public static void main(String[] args) {
                launch(args);
        }

        @Override
        public void start(Stage s) {
                s.setTitle("Star buttons"); 
                Button b1 = new Button("*");
                Button b2 = new Button("**");
                Button b3 = new Button("***");
                Button b4 = new Button("****");
                Button b5 = new Button("*****");
                Button b6 = new Button("******");
                Button b7 = new Button("*******");
                b2.setDisable(true);
                b3.setDisable(true);
                b4.setDisable(true);
                b5.setDisable(true);
                b6.setDisable(true);
                b7.setDisable(true);
                EventHandler<ActionEvent> event = new EventHandler<ActionEvent>() {
                        public void handle(ActionEvent e) {
                                String text = ((Button) e.getSource()).getText();
                                if (text.equals("*")) {
                                        b1.setDisable(true);
                                        b2.setDisable(false);
                                } else if (text.equals("**")) {
                                        b2.setDisable(true);
                                        b3.setDisable(false);
                                } else if (text.equals("***")) {
                                        b3.setDisable(true);
                                        b4.setDisable(false);
                                } else if (text.equals("****")) {
                                        b4.setDisable(true);
                                        b5.setDisable(false);
                                } else if (text.equals("*****")) {
                                        b5.setDisable(true);
                                        b6.setDisable(false);
                                } else if (text.equals("******")) {
                                        b6.setDisable(true);
                                        b7.setDisable(false);
                                } else if (text.equals("*******")) {
                                        b7.setDisable(true);
                                }
                        }
                };
                b1.setOnAction(event);
                b2.setOnAction(event);
                b3.setOnAction(event);
                b4.setOnAction(event);
                b5.setOnAction(event);
                b6.setOnAction(event);
                b7.setOnAction(event);
                ArrayList<Button> buttons = new ArrayList<>();
                buttons.add(b1);
                buttons.add(b2);
                buttons.add(b3);
                buttons.add(b4);
                buttons.add(b5);
                buttons.add(b6);
                buttons.add(b7);
                Collections.shuffle(buttons);
                TilePane tileButtons = new TilePane(Orientation.HORIZONTAL);
                tileButtons.getChildren().addAll(buttons);
                Scene sc = new Scene(tileButtons, 400, 50);
                s.setScene(sc);
                s.show();
        }
}
Output