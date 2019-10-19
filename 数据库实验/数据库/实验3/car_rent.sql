/*
Navicat MySQL Data Transfer

Source Server         : test
Source Server Version : 80015
Source Host           : localhost:3306
Source Database       : car_rent

Target Server Type    : MYSQL
Target Server Version : 80015
File Encoding         : 65001

Date: 2019-06-19 00:48:11
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `broken`
-- ----------------------------
DROP TABLE IF EXISTS `broken`;
CREATE TABLE `broken` (
  `B_ID` char(20) NOT NULL,
  `C_ID` char(8) NOT NULL,
  `U_ID` char(18) NOT NULL,
  `B_TIME` datetime NOT NULL,
  `B_SITUATION` varchar(128) NOT NULL,
  `B_DEGREE` char(4) DEFAULT NULL,
  `B_REPAIRED` char(2) NOT NULL,
  `B_PRICE` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`B_ID`),
  KEY `broken_ibfk_1` (`C_ID`),
  KEY `broken_ibfk_2` (`U_ID`),
  CONSTRAINT `broken_ibfk_1` FOREIGN KEY (`C_ID`) REFERENCES `cars` (`C_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `broken_ibfk_2` FOREIGN KEY (`U_ID`) REFERENCES `users` (`U_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of broken
-- ----------------------------
INSERT INTO `broken` VALUES ('2019061119451207202', '京TF3321', '412702199503200021', '2019-06-11 19:44:00', '123', '轻微', '是', '100.00');
INSERT INTO `broken` VALUES ('2019061214444477802', '京TFS351', '412702199503200021', '2019-06-12 14:43:00', '轮胎漏气', '轻微', '是', '100.00');
INSERT INTO `broken` VALUES ('2019061216585201302', '京TF3321', '412702199710200016', '2019-06-12 16:58:00', '车胎漏气', '轻微', '是', '100.00');

-- ----------------------------
-- Table structure for `cars`
-- ----------------------------
DROP TABLE IF EXISTS `cars`;
CREATE TABLE `cars` (
  `C_ID` char(8) NOT NULL,
  `C_TYPE` char(32) NOT NULL,
  `C_BRAND` char(32) NOT NULL,
  `C_BUYTIME` datetime NOT NULL,
  `C_DEPOSIT` decimal(10,2) NOT NULL,
  `C_PRICE` decimal(10,2) NOT NULL,
  `C_TIMEOUT_PRICE` decimal(10,2) NOT NULL,
  `C_STATUS` char(8) DEFAULT NULL,
  PRIMARY KEY (`C_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of cars
-- ----------------------------
INSERT INTO `cars` VALUES ('京TF3321', '微型客车', '奥迪', '2011-01-01 00:00:00', '2500.00', '150.00', '150.00', '空闲');
INSERT INTO `cars` VALUES ('京TFS351', '中型客车', '奥迪', '2011-01-01 00:00:00', '2500.00', '150.00', '150.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3223', '二座轿车', '大众', '2011-01-01 00:00:00', '1500.00', '100.00', '150.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3233', '二座轿车', '本田', '2011-01-01 00:00:00', '1500.00', '100.00', '250.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3234', '四座跑车', '奔驰', '2011-01-01 00:00:00', '4000.00', '300.00', '250.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3243', '二座轿车', '大众', '2011-01-01 00:00:00', '1500.00', '100.00', '250.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3321', '二座跑车', '奥迪', '2011-01-01 00:00:00', '2500.00', '150.00', '250.00', '空闲');
INSERT INTO `cars` VALUES ('京TY3432', '二座跑车', '奥迪', '2011-01-01 00:00:00', '2500.00', '150.00', '250.00', '空闲');
INSERT INTO `cars` VALUES ('京YT3243', '七座轿车', '大众', '2010-01-01 00:00:00', '2000.00', '100.00', '200.00', '空闲');
INSERT INTO `cars` VALUES ('陕AHE234', '二座跑车', '奥迪', '2010-01-01 00:00:00', '3000.00', '200.00', '300.00', '空闲');
INSERT INTO `cars` VALUES ('豫ASH301', '四座轿车', '宝马', '2009-02-26 19:07:30', '2000.00', '120.00', '150.00', '空闲');
INSERT INTO `cars` VALUES ('豫SAH323', '二座跑车', '丰田', '2000-01-01 00:00:00', '1000.00', '100.00', '150.00', '空闲');

-- ----------------------------
-- Table structure for `employees`
-- ----------------------------
DROP TABLE IF EXISTS `employees`;
CREATE TABLE `employees` (
  `E_ID` char(8) NOT NULL,
  `E_PASSWORD` varchar(32) NOT NULL,
  `E_NAME` char(32) NOT NULL,
  `E_SEX` char(2) DEFAULT NULL,
  `E_PHONE_NUM` char(11) NOT NULL,
  `E_ENTRYDATE` date NOT NULL,
  `E_TYPE` char(8) DEFAULT NULL,
  PRIMARY KEY (`E_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of employees
-- ----------------------------
INSERT INTO `employees` VALUES ('E0000001', '123', '吗妥', '男', '11111111111', '2000-01-01', '普通');
INSERT INTO `employees` VALUES ('E0000002', '123', '章三', '男', '15624320593', '2019-05-08', '高级');
INSERT INTO `employees` VALUES ('E0000003', '456', '鸿山华', '男', '11111111111', '2000-01-01', '高级');
INSERT INTO `employees` VALUES ('E0000004', '123', '洪山', '男', '13432456849', '2000-01-01', '高级');
INSERT INTO `employees` VALUES ('E0000005', '123', '王信义', '女', '13143234567', '2019-05-08', '普通');
INSERT INTO `employees` VALUES ('E0000006', '123', '番茄', '男', '13432435422', '2010-01-01', '普通');

-- ----------------------------
-- Table structure for `record`
-- ----------------------------
DROP TABLE IF EXISTS `record`;
CREATE TABLE `record` (
  `R_ID` char(20) NOT NULL,
  `U_ID` char(18) NOT NULL,
  `R_SITUATION` varchar(128) NOT NULL,
  `R_FINE` int(11) NOT NULL,
  `R_TIME` datetime NOT NULL,
  PRIMARY KEY (`R_ID`),
  KEY `record_ibfk_1` (`U_ID`),
  CONSTRAINT `record_ibfk_1` FOREIGN KEY (`U_ID`) REFERENCES `users` (`U_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of record
-- ----------------------------
INSERT INTO `record` VALUES ('000001', '412702199503200032', '闯红灯', '200', '2019-05-02 19:10:39');
INSERT INTO `record` VALUES ('2019061119224150703', '412702199503200021', '超速', '50', '2019-06-11 19:22:00');
INSERT INTO `record` VALUES ('2019061214432350003', '412702199503200021', '闯红灯', '50', '2019-06-12 14:43:00');
INSERT INTO `record` VALUES ('2019061812560415003', '412702199503200021', '追尾', '80', '2019-06-18 12:55:00');

-- ----------------------------
-- Table structure for `rent`
-- ----------------------------
DROP TABLE IF EXISTS `rent`;
CREATE TABLE `rent` (
  `RT_ID` char(20) NOT NULL,
  `U_ID` char(18) NOT NULL,
  `E_ID` char(8) DEFAULT NULL,
  `C_ID` char(8) NOT NULL,
  `RT_TIME` datetime NOT NULL,
  `OUT_TIME` datetime DEFAULT NULL,
  `BACK_TIME` datetime DEFAULT NULL,
  `EXPENSE` decimal(10,2) NOT NULL,
  `DEPOSIT` decimal(10,2) NOT NULL,
  `PROGRESS` char(10) DEFAULT NULL,
  `RENTAL_TIME` int(11) NOT NULL,
  PRIMARY KEY (`RT_ID`),
  KEY `rent_ibfk_1` (`U_ID`),
  KEY `rent_ibfk_2` (`E_ID`),
  KEY `rent_ibfk_3` (`C_ID`),
  CONSTRAINT `rent_ibfk_1` FOREIGN KEY (`U_ID`) REFERENCES `users` (`U_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `rent_ibfk_2` FOREIGN KEY (`E_ID`) REFERENCES `employees` (`E_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `rent_ibfk_3` FOREIGN KEY (`C_ID`) REFERENCES `cars` (`C_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of rent
-- ----------------------------
INSERT INTO `rent` VALUES ('2019061119305934001', '123', 'E0000002', '豫ASH301', '2019-05-01 00:00:00', '2019-05-03 19:11:22', '2019-05-10 19:11:34', '1002.00', '1200.00', '已完成', '8');
INSERT INTO `rent` VALUES ('2019061119305984001', '412702199503200021', 'E0000001', '京TY3223', '2019-06-11 19:30:59', '2019-06-11 19:31:00', '2019-06-11 19:33:00', '85.00', '600.00', '已完成', '1');
INSERT INTO `rent` VALUES ('2019061119383952501', '412702199503200021', 'E0000001', '京TY3243', '2019-06-11 19:38:39', '2019-06-01 00:00:00', '2019-06-11 19:44:00', '935.00', '600.00', '已完成', '11');
INSERT INTO `rent` VALUES ('2019061119383953201', '412702199503200021', 'E0000002', '豫SAH323', '2018-07-10 21:49:44', '2018-07-11 21:49:51', '2018-08-01 21:50:05', '3000.00', '800.00', '已完成', '30');
INSERT INTO `rent` VALUES ('2019061120030641401', '412702199503200021', 'E0000001', '京TF3321', '2019-03-11 20:03:06', '2019-03-11 20:03:06', '2019-03-11 20:03:06', '510.00', '1000.00', '已完成', '4');
INSERT INTO `rent` VALUES ('2019061120031236001', '412702199503200021', 'E0000001', '京TY3223', '2019-04-11 20:03:12', '2019-04-11 20:04:06', '2019-04-16 20:04:06', '425.00', '600.00', '已完成', '5');
INSERT INTO `rent` VALUES ('2019061120031766401', '412702199503200021', 'E0000001', '豫ASH301', '2019-05-11 20:03:17', '2019-05-11 20:04:06', '2019-05-14 20:04:06', '306.00', '800.00', '已完成', '3');
INSERT INTO `rent` VALUES ('2019061209552580701', '412702199503200021', 'E0000001', '京TFS351', '2019-06-12 09:55:25', '2019-06-12 09:55:00', null, '382.50', '1000.00', '已取消', '3');
INSERT INTO `rent` VALUES ('2019061209561134601', '412702199503200021', 'E0000001', '京TFS351', '2019-03-12 09:56:11', '2019-03-12 09:55:00', '2019-06-12 09:56:00', '127.50', '1000.00', '已完成', '1');
INSERT INTO `rent` VALUES ('2019061209580544401', '412702199503200021', 'E0000001', '京TY3243', '2019-03-12 09:58:05', '2019-03-12 09:58:00', null, '340.00', '600.00', '已取消', '4');
INSERT INTO `rent` VALUES ('2019061209584275401', '412702199503200021', 'E0000001', '京TY3243', '2019-01-12 09:58:42', '2019-01-12 09:58:00', '2019-01-12 09:58:00', '85.00', '600.00', '已完成', '1');
INSERT INTO `rent` VALUES ('2019061210214697201', '412702199503200021', 'E0000001', '豫SAH323', '2019-06-03 10:21:46', '2019-06-03 14:00:00', '2019-06-08 10:23:00', '275.00', '400.00', '已完成', '6');
INSERT INTO `rent` VALUES ('2019061210215058401', '412702199503200021', 'E0000001', '陕AHE234', '2019-01-12 10:21:50', '2019-01-12 14:00:00', '2019-01-16 10:26:00', '380.00', '1200.00', '已完成', '5');
INSERT INTO `rent` VALUES ('2019061210215557901', '412702199503200021', 'E0000001', '京YT3243', '2018-06-12 10:21:55', '2018-06-12 14:00:00', '2019-06-12 10:26:00', '85.00', '800.00', '已完成', '1');
INSERT INTO `rent` VALUES ('2019061210445769901', '123', 'E0000001', '京TFS351', '2019-03-12 10:44:57', '2019-03-12 10:45:00', '2019-03-15 10:46:00', '555.00', '1500.00', '已完成', '4');
INSERT INTO `rent` VALUES ('2019061210450108601', '123', 'E0000001', '京TY3233', '2019-02-12 10:45:01', '2019-02-12 10:45:00', '2019-02-14 10:46:00', '270.00', '900.00', '已完成', '3');
INSERT INTO `rent` VALUES ('2019061210451795001', '123', 'E0000001', '京TY3243', '2019-06-12 10:45:17', '2019-06-12 10:45:00', '2019-06-15 10:46:00', '520.00', '900.00', '已完成', '4');
INSERT INTO `rent` VALUES ('2019061215072704101', '412702199503200021', 'E0000002', '京TF3321', '2019-06-12 15:07:27', '2019-06-12 15:07:00', null, '637.50', '1000.00', '已取消', '5');
INSERT INTO `rent` VALUES ('2019061215081952301', '412702199503200021', 'E0000002', '京TF3321', '2019-06-12 15:08:19', '2019-06-12 15:08:00', '2019-06-13 15:08:00', '255.00', '1000.00', '已完成', '2');
INSERT INTO `rent` VALUES ('2019061216544203401', '412702199710200016', 'E0000001', '京TY3233', '2019-06-12 16:54:42', '2019-06-12 16:55:00', null, '300.00', '1500.00', '已取消', '3');
INSERT INTO `rent` VALUES ('2019061216564378601', '412702199710200016', 'E0000001', '京TF3321', '2019-06-12 16:56:43', '2019-06-12 16:55:00', '2019-06-12 16:57:00', '150.00', '2500.00', '已完成', '1');
INSERT INTO `rent` VALUES ('2019061812481367301', '123', 'E0000001', '京TFS351', '2019-06-18 12:48:13', '2019-06-12 14:00:00', '2019-06-24 12:48:00', '1935.00', '1500.00', '已完成', '13');
INSERT INTO `rent` VALUES ('2019061812504646301', '123', 'E0000001', '京TFS351', '2019-06-18 12:50:46', '2019-06-18 12:51:00', '2019-06-18 12:51:00', '135.00', '1500.00', '已完成', '1');

-- ----------------------------
-- Table structure for `users`
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `U_ID` char(18) NOT NULL,
  `U_PASSWORD` varchar(32) NOT NULL,
  `U_PHONE_NUM` char(11) NOT NULL,
  `U_NAME` char(32) NOT NULL,
  `U_SEX` char(2) DEFAULT NULL,
  `U_BIRTHDAY` date NOT NULL,
  `U_VIP` int(11) NOT NULL,
  `U_CREDIT` int(11) NOT NULL,
  `U_BALANCE` decimal(10,2) NOT NULL,
  `U_REGISTDATE` datetime NOT NULL,
  `U_SECRET_QUESTION` varchar(64) NOT NULL,
  `U_SECRET_ANSWER` varchar(64) NOT NULL,
  PRIMARY KEY (`U_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of users
-- ----------------------------
INSERT INTO `users` VALUES ('123', '123', '18932345432', '张超', '男', '2004-02-27', '2', '78', '2930.00', '2019-03-27 19:05:12', '我住在哪里？', '地球');
INSERT INTO `users` VALUES ('412702199503200021', '123', '11111111111', 'test', 'X', '2019-05-09', '5', '91', '20000.00', '2019-05-27 21:27:16', '1', '1');
INSERT INTO `users` VALUES ('412702199503200032', '123', '15623437960', '吕智慧', '男', '2000-06-14', '2', '90', '5000.00', '2019-05-01 19:03:23', '我的出生日期是什么？', '1月1日');
INSERT INTO `users` VALUES ('412702199710200016', '123', '15623437960', '吕鹏泽', '男', '1997-10-20', '1', '91', '4850.00', '2019-06-12 16:52:23', '我喜欢什么？', '旅游');
INSERT INTO `users` VALUES ('432503197505028800', '123', '13411111112', '佘彪', '男', '1975-05-02', '0', '90', '0.00', '2019-06-17 20:57:55', '我喜欢什么？', '旅游');
INSERT INTO `users` VALUES ('432503197505028819', '123', '15623437960', '佘彪', '男', '1975-05-02', '2', '90', '3095.00', '2019-05-28 20:13:02', '我喜欢什么？', '旅游');
DROP TRIGGER IF EXISTS `become_vip`;
DELIMITER ;;
CREATE TRIGGER `become_vip` BEFORE UPDATE ON `users` FOR EACH ROW BEGIN
	if new.U_BALANCE >= 20000 and new.U_VIP < 5 THEN
		set new.U_VIP = 5;
	elseif new.U_BALANCE >=15000 and new.U_VIP < 4 THEN
		set new.U_VIP = 4;
	elseif(new.U_BALANCE >=10000) and new.U_VIP < 3 THEN
		set new.U_VIP = 3;
	elseif(new.U_BALANCE >=5000) and new.U_VIP < 2 THEN
		set new.U_VIP = 2;
	elseif(new.U_BALANCE >=2000) and new.U_VIP < 1 THEN
		set new.U_VIP = 1;
	end if;
END
;;
DELIMITER ;
DROP TRIGGER IF EXISTS `reduce_vip`;
DELIMITER ;;
CREATE TRIGGER `reduce_vip` BEFORE UPDATE ON `users` FOR EACH ROW BEGIN
	if new.U_CREDIT<60 THEN
		set new.U_VIP = 0;
	end if;
END
;;
DELIMITER ;
