package application;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.sun.javafx.robot.impl.FXRobotHelper;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class PatientController {
	public static String userName;
	public static String userId;
	@FXML
	ChoiceBox<String> departmentName, registerType, registerName, doctorName;
	@FXML
	Button exitButton;
	@FXML
	TextField shouldPay, registerNumber, charge, pay;
	@FXML
	Label infomation;

	@FXML
	public void initialize() {
		showRegisterId();
		showDepartmentName();
		showDoctorName();
		showRegisterType();
		showRegisterName();
		showRegisterId();
	}

	private void showRegisterId() {
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			registerNumber.setText(DataBase.getRegisterId());
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void showDepartmentName() {
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getWholeTable("t_ksxx");
			departmentName.getItems().clear();
			int i = 1;
			while (result.next()) {
				departmentName.getItems().add(result.getString("KSBH") + " " + result.getString("KSMC"));
			}
			DataBase.disconnectDataBase();
		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void showDoctorName() {
		if (departmentName.getSelectionModel().isEmpty())// 没有选择任何项
			return;
		String KSBH = departmentName.getSelectionModel().getSelectedItem();
		KSBH = KSBH.substring(0, KSBH.indexOf(' '));
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getDoctorName(KSBH);
			doctorName.getItems().clear();
			while (result.next()) {
				doctorName.getItems().add(result.getString("YSBH") + " " + result.getString("YSMC"));
			}
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void showRegisterType() {
		if (doctorName.getSelectionModel().isEmpty())
			return;
		String YSBH = doctorName.getSelectionModel().getSelectedItem();
		YSBH = YSBH.substring(0, YSBH.indexOf(' '));
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			boolean isExpert = DataBase.getDoctorType(YSBH);
			registerType.getItems().clear();
			if (isExpert) {
				registerType.getItems().addAll("普通", "专家");
			} else {
				registerType.getItems().addAll("普通");
			}
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void showRegisterName() {
		if (departmentName.getSelectionModel().isEmpty())
			return;
		String KSBH = departmentName.getSelectionModel().getSelectedItem();
		KSBH = KSBH.substring(0, KSBH.indexOf(' '));
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getRegisteredName(KSBH);
			registerName.getItems().clear();
			while (result.next()) {
				registerName.getItems().add(result.getString("HZBH") + " " + result.getString("HZMC"));
			}
			if (registerType.getSelectionModel().getSelectedIndex() == 0)
				shouldPay.setText("20");
			else
				shouldPay.setText("40");
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void confirm() {
		if (charge.getText().startsWith("ERROR")) {
			infomation.setText("找零错误");
			infomation.setStyle("-fx-text-fill: red;");
			return;
		}
		if (departmentName.getSelectionModel().isEmpty() || registerType.getSelectionModel().isEmpty()
				|| registerName.getSelectionModel().isEmpty() || doctorName.getSelectionModel().isEmpty()) {
			infomation.setText("请选择完所有选项");
			infomation.setStyle("-fx-text-fill: red;");
			return;
		}
		String GHBH = null, BRBH = null, GHRC = null, THBZ = null, GHFY = null, RQSJ = null;
		DBConnector DataBase = new DBConnector();
		String HZBH = registerName.getSelectionModel().getSelectedItem();
		HZBH = HZBH.substring(0, HZBH.indexOf(' '));

		String YSBH = doctorName.getSelectionModel().getSelectedItem();
		YSBH = YSBH.substring(0, YSBH.indexOf(' '));
		BRBH = userId;
		THBZ = "0";
		GHFY = shouldPay.getText();
		RQSJ = getCurrentDateTime();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			GHBH = DataBase.getRegisterId();
			GHRC = DataBase.getRegisteredPersons(HZBH);
			DataBase.insertRecord(GHBH, HZBH, YSBH, BRBH, GHRC, THBZ, GHFY, RQSJ);
			infomation.setText("您的挂号编号为" + GHBH);
			infomation.setStyle("-fx-text-fill: red;");

			DataBase.disconnectDataBase();
		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	@FXML
	void clear() throws IOException {
		Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Patient.fxml")));
		scene.getStylesheets().add( 
        		getClass().getResource("application.css") 
        		.toExternalForm()); 
		FXRobotHelper.getStages().get(0).setScene(scene);
	}

	@FXML
	void getCharge() {
		int shallPay, realPay;
		if (shouldPay.getText().length() != 0 && pay.getText().length() != 0) {
			shallPay = Integer.valueOf(shouldPay.getText());
			realPay = Integer.valueOf(pay.getText());
			if (realPay >= shallPay) {
				charge.setText(String.valueOf(realPay - shallPay));
			} else
				charge.setText("ERROR");
		} else
			charge.setText("");
	}

	@FXML
	void exit() throws IOException {
		Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Login.fxml")));
		scene.getStylesheets().add( 
        		getClass().getResource("application.css") 
        		.toExternalForm()); 
		FXRobotHelper.getStages().get(0).setScene(scene);
	}

	private String getCurrentDateTime() {
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");// 设置日期格式
		return df.format(new Date());
	}

}
