/* COP3331
 * IGLI DURO
 * U33766202 */
 
/* In this lab, you will create a GUI application.  
 * This application starts with a window containing 7 buttons with 1-7 stars on them (* to *******), 
 * in a horizontal line and in random order.  The random order should be different each time the program runs.  
 * Initially, only the * button should be enabled (setDisable(false)), but clicking that button should disable it (setDisable(true)) and enable the ** button.  
 * Likewise, ** disables itself and enables ***, and so forth, with ******* enabling nothing. */

/* JavaFX error add "C:\Users\duroi\Documents\lib\javafx-sdk-11.0.2\lib "


/* Create 7 buttons, labeled * to *******
 * Disable all except first
 * Write event for on button click disable current button and enable next
 * Add buttons to list
 * Shuffle buttons randomly
 * Display buttons horizontally on scene in random order
 * Show stage

*/

  
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.control.Button; //Gives acccess to Button class
import javafx.event.ActionEvent;
import java.util.ArrayList; //Gives capability to create ArrayLists (similar to vectors)
import java.util.Collections; //Gives access to the Collections class and shuffle method
import javafx.stage.Stage; //
import javafx.scene.Scene;
import javafx.scene.layout.TilePane;
import javafx.geometry.Orientation; //enum type used for displaying objects horizontally or vertically



public class App extends Application 
{
        public static void main(String[] args) 
        {
                launch(args);
        }
  
        @Override
        public void start(Stage stage) 
        {
                //Create 7 objects of class button. Modifying the string changes the label. 
                Button button1 = new Button("*");
                Button button2 = new Button("**");
                Button button3 = new Button("***");
                Button button4 = new Button("****");
                Button button5 = new Button("*****");
                Button button6 = new Button("******");
                Button button7 = new Button("*******");

                //Disable all buttons except button1.
                button1.setDisable(false);
                button2.setDisable(true);
                button3.setDisable(true);
                button4.setDisable(true);
                button5.setDisable(true);
                button6.setDisable(true);
                button7.setDisable(true);

                //Create event handler for an ActionEvent. When a button is clicked a ActionEvent is sent.
                EventHandler<ActionEvent> clickEvent = new EventHandler<ActionEvent>() 
                {
                        public void handle(ActionEvent click) 
                        {
                                //When an ActionEvent occurs, returns the object on which the event occured and gets the label on the object.
                                String text = ((Button) click.getSource()).getText();
                                
                                //Switch statement with 7 cases, one for each button label.
                                //When * is hit, disable * and enable **
                                //When ** is hit, disable ** and enable **
                                //...When ******* is hit, disable *******.
                                switch(text) 
                                {
                                        case "*":
                                                button1.setDisable(true);
                                                button2.setDisable(false);
                                                break;

                                        case "**":
                                                button2.setDisable(true);
                                                button3.setDisable(false);
                                                break;

                                        case "***":
                                                button3.setDisable(true);
                                                button4.setDisable(false);
                                                break;

                                        case "****":
                                                button4.setDisable(true);
                                                button5.setDisable(false);
                                                break;

                                        case "*****":
                                                button5.setDisable(true);
                                                button6.setDisable(false);
                                                break;

                                        case "******":
                                                button6.setDisable(true);
                                                button7.setDisable(false);
                                                break;
                                        case "*******":
                                                button7.setDisable(true);
                                                
                                                break;
                                }
                        }
                };
                
                //Set values defined in clickEvent whenever an ActionEvent occurs for respective button.
                button1.setOnAction(clickEvent);
                button2.setOnAction(clickEvent);
                button3.setOnAction(clickEvent);
                button4.setOnAction(clickEvent);
                button5.setOnAction(clickEvent);
                button6.setOnAction(clickEvent);
                button7.setOnAction(clickEvent);

                //Create an ArrayList of Buttons and add buttons1-7 to buttons.
                ArrayList<Button> buttons = new ArrayList<>();
                buttons.add(button1);
                buttons.add(button2);
                buttons.add(button3);
                buttons.add(button4);
                buttons.add(button5);
                buttons.add(button6);
                buttons.add(button7);
                
                //Collections.shuffle will randomly permute the list of buttons. 
                Collections.shuffle(buttons);

                //Creates a TilePane object display buttons in a uniform grid. Can be configured to HORIZONTAL or VERTICAL with orientation enum.
                TilePane tileButtons = new TilePane(Orientation.HORIZONTAL);
                tileButtons.getChildren().addAll(buttons);

                //Create scene displaying buttons in a 500x50 window.
                Scene scene = new Scene(tileButtons, 500, 50);

                //Set title for stage.
                stage.setTitle("Click the boxes in order");
                //Set scene to stage
                stage.setScene(scene);
                //Show stage.
                stage.show();
          }
  }