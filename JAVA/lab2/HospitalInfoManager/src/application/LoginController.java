package application;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.javafx.robot.impl.FXRobotHelper;
import com.sun.media.jfxmedia.events.NewFrameEvent;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import java.text.SimpleDateFormat;
import java.util.Date;

public class LoginController {
	@FXML
	TextField inputUsername;
	@FXML
	PasswordField inputPassword;
	@FXML
	Button doctorLoginButton;
	@FXML
	Button patientLoginButton;
	@FXML
	Label loginInfo;

	void initialize() {

	}

	@FXML
	void doctorLogin() throws IOException {
		if (!validateUserNameAndPassword())
			return;
		DBConnector DataBase = new DBConnector();
		String userId = null, userName = null;
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getDoctorInfo(inputUsername.getText().trim());
			if (result == null) {
				loginInfo.setText("��ȡ���ݿ��������ϵ����Ա��");
				loginInfo.setStyle("-fx-text-fill: red;");
			}
			if (!result.next()) {
				loginInfo.setText("�û�������");
				loginInfo.setStyle("-fx-text-fill: red;");
				return;
			} else if (!result.getString("DLKL").equals(inputPassword.getText())) {
				loginInfo.setText("�������");
				loginInfo.setStyle("-fx-text-fill: red;");
				return;
			}
			userId=result.getString("YSBH");
			userName=result.getString("YSMC");
			DataBase.updateDoctorLoginTime(userId, getCurrentDateTime());
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
		DoctorController.userName = userName;
		DoctorController.userId = userId;
		Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Doctor.fxml")));
		scene.getStylesheets().add( 
        		getClass().getResource("application.css") 
        		.toExternalForm()); 
		FXRobotHelper.getStages().get(0).setScene(scene);
	}

	@FXML
	void patientLogin() throws IOException {
		if (!validateUserNameAndPassword())
			return;
		String userId = null, userName = null;
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getPatientInfo(inputUsername.getText().trim());
			if (result == null) {
				loginInfo.setText("��ȡ���ݿ��������ϵ����Ա��");
				loginInfo.setStyle("-fx-text-fill: red;");
			}
			if (!result.next()) {
				loginInfo.setText("�û�������");
				loginInfo.setStyle("-fx-text-fill: red;");
				return;
			} else if (!result.getString("DLKL").equals(inputPassword.getText())) {
				loginInfo.setText("�������");
				loginInfo.setStyle("-fx-text-fill: red;");
				return;
			}
			userId=result.getString("BRBH");
			userName=result.getString("BRMC");
			DataBase.updatePatientLoginTime(userId, getCurrentDateTime());
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
		PatientController.userName = userName;
		PatientController.userId = userId;
		Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Patient.fxml")));
		scene.getStylesheets().add( 
        		getClass().getResource("application.css") 
        		.toExternalForm()); 
		FXRobotHelper.getStages().get(0).setScene(scene);
	}

	private boolean validateUserNameAndPassword() {
		if (inputUsername.getText().isEmpty()) {
			inputUsername.setStyle("-fx-background-color: pink;");
			loginInfo.setText("�������û���");
			return false;
		}
		if (inputPassword.getText().isEmpty()) {
			inputUsername.setStyle("-fx-background-color: pink;");
			loginInfo.setText("����������");
			return false;
		}
		return true;
	}
	
	private String getCurrentDateTime() {
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//�������ڸ�ʽ
		return df.format(new Date());
	}
}
