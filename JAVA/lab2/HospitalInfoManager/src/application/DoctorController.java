package application;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.Date;

import com.sun.javafx.robot.impl.FXRobotHelper;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class DoctorController {
	String beginTime,endTime;
	/*状态栏*/
	public static String userId;
	public static String userName;
	@FXML
	private Button exitButton;
	@FXML
	private Label showTime;
	@FXML
	private Label name;
	@FXML
	private Button confirmDate;
	@FXML
	private DatePicker selectBeginDate;
	@FXML
	private DatePicker selectEndDate;
	@FXML
	void selectDate() {
		beginTime=selectBeginDate.getValue().toString();
		endTime=selectEndDate.getValue().toString();
		showWageInfo();
	}
	/*挂号列表*/
	@FXML
	private TableColumn registerID;
	@FXML
	private TableColumn patientName;
	@FXML
	private TableColumn registerDate;
	@FXML
	private TableColumn registerType;
	@FXML
	TableView<registerInfo> registerInfoTable;
	
	/*收入列表*/
	@FXML
	TableView<wageInfo> wageInfoTable;
	@FXML
	private TableColumn departmentNameCol;
	@FXML
	private TableColumn doctorIdCol;
	@FXML
	private TableColumn doctorNameCol;
	@FXML
	private TableColumn isExpertCol;
	@FXML
	private TableColumn registerPersonCol;
	@FXML
	private TableColumn totalWageCol;

	@FXML
	public void initialize() {
		selectBeginDate.setValue(LocalDate.of(1000, 1, 1));
		selectEndDate.setValue(LocalDate.of(3000, 1, 1));
		showLoginInfo();// 显示登陆信息
		showRegisterList();// 显示挂号列表
		showWageInfo();//显示收入信息
	}

	@FXML
	void exit() throws IOException {
		Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Login.fxml")));
		scene.getStylesheets().add( 
        		getClass().getResource("application.css") 
        		.toExternalForm()); 
		FXRobotHelper.getStages().get(0).setScene(scene);
	}

	private void showLoginInfo() {
		/* 显示登陆日期 */
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		showTime.setText(df.format(new Date()));
		name.setText(userName);
	}

	private void showRegisterList() {
		ObservableList<registerInfo> list = FXCollections.observableArrayList();
		registerID.setCellValueFactory(new PropertyValueFactory("registerID"));
		patientName.setCellValueFactory(new PropertyValueFactory("patientName"));
		registerDate.setCellValueFactory(new PropertyValueFactory("registerDate"));
		registerType.setCellValueFactory(new PropertyValueFactory("registerType"));

		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getRegisterForDoctor(userId);
			while (result.next()) {
				registerInfo item = new registerInfo();
				item.setRegisterID(result.getString("GHBH"));
				item.setPatientName(result.getString("BRMC"));
				item.setRegisterDate(result.getString("RQSJ"));
				item.setRegisterType(result.getString("HZMC"));
				list.add(item);
			}
			registerInfoTable.setItems(list);
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	private void showWageInfo() {
		ObservableList<wageInfo> list = FXCollections.observableArrayList();
		departmentNameCol.setCellValueFactory(new PropertyValueFactory("departmentName"));
		doctorIdCol.setCellValueFactory(new PropertyValueFactory("doctorId"));
		doctorNameCol.setCellValueFactory(new PropertyValueFactory("doctorName"));
		isExpertCol.setCellValueFactory(new PropertyValueFactory("isExpert"));
		registerPersonCol.setCellValueFactory(new PropertyValueFactory("registerPersons"));
		totalWageCol.setCellValueFactory(new PropertyValueFactory("totalWage"));
		
		DBConnector DataBase = new DBConnector();
		try {
			DataBase.connectDataBase(SQLConfig.URL);
			ResultSet result = DataBase.getDoctorWageInfo(beginTime, endTime);
			while (result.next()) {
				wageInfo item = new wageInfo();
				item.setDepartmentName(result.getString("KSMC"));
				item.setDoctorId(result.getString("YSBH"));
				item.setDoctorName(result.getString("YSMC"));
				int isExpert=result.getInt("SFZJ");
				if(isExpert==1) item.setIsExpert("专家");
				else item.setIsExpert("普通");
				item.setRegisterPersons(result.getString("PERNUM"));
				item.setTotalWage(result.getDouble("TOTALWAGE"));
				list.add(item);
			}
			wageInfoTable.setItems(list);
			DataBase.disconnectDataBase();

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}

	public class registerInfo {
		private String registerID;
		private String patientName;
		private String registerDate;
		private String registerType;

		public registerInfo() {
			// TODO 自动生成的构造函数存根
		}

		public String getRegisterID() {
			return registerID;
		}

		public void setRegisterID(String registerID) {
			this.registerID = registerID;
		}

		public String getPatientName() {
			return patientName;
		}

		public void setPatientName(String patientName) {
			this.patientName = patientName;
		}

		public String getRegisterDate() {
			return registerDate;
		}

		public void setRegisterDate(String registerDate) {
			this.registerDate = registerDate;
		}

		public String getRegisterType() {
			return registerType;
		}

		public void setRegisterType(String registerType) {
			this.registerType = registerType;
		}
	}

	public class wageInfo {// 收入信息
		String departmentName;
		String doctorId;
		String doctorName;
		String isExpert;
		String registerPersons;
		double totalWage;

		public wageInfo() {
			// TODO 自动生成的构造函数存根
		}

		public String getDepartmentName() {
			return departmentName;
		}

		public void setDepartmentName(String departmentName) {
			this.departmentName = departmentName;
		}

		public String getDoctorId() {
			return doctorId;
		}

		public void setDoctorId(String doctorId) {
			this.doctorId = doctorId;
		}

		public String getDoctorName() {
			return doctorName;
		}

		public void setDoctorName(String doctorName) {
			this.doctorName = doctorName;
		}

		public String getIsExpert() {
			return isExpert;
		}

		public void setIsExpert(String isExpert) {
			this.isExpert = isExpert;
		}

		public String getRegisterPersons() {
			return registerPersons;
		}

		public void setRegisterPersons(String registerPersons) {
			this.registerPersons = registerPersons;
		}

		public double getTotalWage() {
			return totalWage;
		}

		public void setTotalWage(double totalWage) {
			this.totalWage = totalWage;
		}
	}
}
