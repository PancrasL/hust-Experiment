package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;


public class Main extends Application {
	@Override
	public void start(Stage primaryStage) {
		try {
            // Read file fxml and draw interface.
			
            Parent root = FXMLLoader.load(getClass().getResource("/application/Login.fxml"));
            root.getStylesheets().add( 
            		getClass().getResource("application.css") 
            		.toExternalForm()); 
            primaryStage.setTitle("医院挂号管理系统");
            primaryStage.setScene(new Scene(root));
            primaryStage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
