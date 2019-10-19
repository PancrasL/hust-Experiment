package application;

import java.sql.*;

public class DBConnector {
	private Connection connection;
	private Statement statement;

	public void connectDataBase(String url) throws ClassNotFoundException, SQLException {
		// ������������
		Class.forName(SQLConfig.DRIVER);

		// ��������
		connection = DriverManager.getConnection(SQLConfig.URL, SQLConfig.USERNAME, SQLConfig.PASSWORD);

		// �������
		statement = connection.createStatement();

	}

	public void disconnectDataBase() throws SQLException {// �ر�����
		statement.close();
		connection.close();
	}

	public ResultSet getWholeTable(String tableName) {// ��ȡ���ű������
		try {
			return statement.executeQuery("select * from " + tableName);
		} catch (SQLException e) {
			return null;
		}
	}

	public ResultSet getPatientInfo(String number) {// ��ȡ����number����Ϣ
		try {
			return statement.executeQuery("select * from " + "t_brxx" + " where " + "BRBH" + "=" + number);
		} catch (SQLException e) {
			return null;
		}
	}

	public ResultSet getDoctorInfo(String number) {// ��ȡҽ��number����Ϣ
		try {
			return statement.executeQuery("select * from " + "t_ksys" + " where " + "YSBH" + "=" + number);
		} catch (SQLException e) {
			return null;
		}
	}

	public ResultSet getRegisterForDoctor(String docNumber) {// ��ȡҽ���ĹҺ���Ϣ��
		try {
			String sql = "SELECT GHBH,BRMC,RQSJ,HZMC FROM t_ghxx,t_brxx,t_hzxx \r\n" + "WHERE t_ghxx.YSBH = "
					+ docNumber + " AND t_ghxx.BRBH = t_brxx.BRBH AND t_ghxx.HZBH = t_hzxx.HZBH;";
			return statement.executeQuery(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	public ResultSet getDoctorWageInfo(String beginDateTime, String endDateTime) {// ��ȡҽ��������Ϣ
		try {
			String sql = "SELECT KSMC,YSBH,YSMC,SFZJ,COUNT(GHRC) as PERNUM,SUM(GHFY) as TOTALWAGE FROM\r\n"
					+ "(SELECT KSMC,YSBH,YSMC,SFZJ,GHRC,GHFY,RQSJ FROM\r\n"
					+ "(SELECT t_ksxx.KSMC,t_ghxx.YSBH,t_ksys.YSMC,t_ksys.SFZJ,t_ghxx.GHRC,t_ghxx.GHFY,RQSJ FROM t_ksxx,t_ghxx,t_ksys,t_hzxx\r\n"
					+ "WHERE t_ghxx.YSBH=t_ksys.YSBH AND t_ksxx.KSBH=t_ksys.KSBH AND t_ghxx.HZBH=t_hzxx.HZBH) temp WHERE RQSJ BETWEEN \""
					+ beginDateTime + "\" AND \"" + endDateTime + "\") temp1 GROUP BY YSBH,KSMC;";
			return statement.executeQuery(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	public void updatePatientLoginTime(String patientId, String time) {// ���»��ߵ�½����
		try {
			statement.executeUpdate("update t_brxx set DLRQ = '" + time + "' where BRBH = '" + patientId + "'");
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
	}

	public void updateDoctorLoginTime(String doctorId, String time) {// ����ҽ����½����
		try {
			statement.executeUpdate("update t_ksys set DLRQ = '" + time + "' where YSBH = '" + doctorId + "'");
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
	}

	public String getRegisterId() {
		try {
			String sql = "SELECT MAX(GHBH) FROM t_ghxx;";
			String s = new String();
			ResultSet result = statement.executeQuery(sql);
			result.next();
			return String.format("%06d", result.getInt(1) + 1);
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	public void insertRecord(String GHBH, String HZBH, String YSBH, String BRBH, String GHRC, String THBZ, String GHFY,
			String RQSJ) {
		String s = String.format("('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", GHBH, HZBH, YSBH, BRBH, GHRC, THBZ,
				GHFY, RQSJ);
		String sql = "INSERT INTO `t_ghxx` (`GHBH`, `HZBH`, `YSBH`, `BRBH`, `GHRC`, `THBZ`, `GHFY`, `RQSJ`) VALUES "
				+ s;
		try {
			statement.execute(sql);

		} catch (SQLException e) {
			// e.printStackTrace();
		}

	}

	public ResultSet getDoctorName(String KSBH) {
		try {
			String sql = "SELECT t_ksys.YSBH,t_ksys.YSMC FROM t_ksys\r\n" + "WHERE t_ksys.KSBH = \"" + KSBH + "\";";
			String s = new String();
			ResultSet result = statement.executeQuery(sql);
			return result;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	public boolean getDoctorType(String YSBH) {
		try {
			String sql = "SELECT t_ksys.SFZJ FROM t_ksys\r\n" + "WHERE t_ksys.YSBH = \"" + YSBH + "\";";
			String s = new String();
			ResultSet result = statement.executeQuery(sql);
			result.next();
			return result.getBoolean("SFZJ");
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}

	public String getRegisteredPersons(String HZBH) {// ��ȡ�Һ��˴�
		try {
			String sql = "SELECT MAX(GHRC) FROM t_ghxx \r\n" + "WHERE t_ghxx.HZBH=\"" + HZBH + "\";";
			String s = new String();
			ResultSet result = statement.executeQuery(sql);
			result.next();
			return String.format("%d", result.getInt(1) + 1);
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public ResultSet getRegisteredName(String KSBH) {
		try {
			String sql = "SELECT HZBH,HZMC FROM t_hzxx\r\n" + 
					"		WHERE KSBH=\""+KSBH+"\";";
			String s = new String();
			ResultSet result = statement.executeQuery(sql);
			return result;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
}
