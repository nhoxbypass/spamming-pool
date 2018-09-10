-- MySQL dump 10.13  Distrib 5.6.24, for Win32 (x86)
--
-- Host: 127.0.0.1    Database: bankmanagement
-- ------------------------------------------------------
-- Server version	5.7.19-log

CREATE DATABASE bankmanagement;
USE bankmanagement;

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `account_id` int(11) NOT NULL,
  `pin` int(11) DEFAULT NULL,
  `account_name` varchar(45) DEFAULT NULL,
  `expired_date` date DEFAULT NULL,
  `balance` int(11) DEFAULT NULL,
  `bank_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,123456,'TRAN THI NHA','2017-10-05',13028100,1),(2,123456,'DOAN HIEU TAM','2017-10-05',4130000,1),(3,123456,'DOAN THI PHUONG HUYEN','2017-01-01',920000,2);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bank`
--

DROP TABLE IF EXISTS `bank`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bank` (
  `bank_id` int(11) NOT NULL,
  `bank_name` char(100) DEFAULT NULL,
  PRIMARY KEY (`bank_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank`
--

LOCK TABLES `bank` WRITE;
/*!40000 ALTER TABLE `bank` DISABLE KEYS */;
INSERT INTO `bank` VALUES (1,'ACB Bank'),(2,'Agribank'),(3,'Viettin Bank'),(4,'Dong A Bank'),(5,'TMCP Bank'),(6,'Sacombank'),(7,'BIDV');
/*!40000 ALTER TABLE `bank` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `transaction_id` char(30) NOT NULL,
  `sender_id` int(11) DEFAULT NULL,
  `receiver_id` int(11) DEFAULT NULL,
  `amount` int(11) DEFAULT NULL,
  `time` char(100) DEFAULT NULL,
  `fee` int(11) DEFAULT NULL,
  PRIMARY KEY (`transaction_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES ('1507203212953',1,3,100000,'Thu Oct 05 2017 18:33:32 GMT+0700 (SE Asia Standard Time)',3300),('1507203247189',1,NULL,100000,'Thu Oct 05 2017 18:34:07 GMT+0700 (SE Asia Standard Time)',0),('1507203434149',1,3,100000,'Thu Oct 05 2017 18:37:14 GMT+0700 (SE Asia Standard Time)',11000),('1507203494313',1,NULL,100000,'Thu Oct 05 2017 18:38:14 GMT+0700 (SE Asia Standard Time)',0),('1507208359332',1,NULL,1000000,'Thu Oct 05 2017 19:59:19 GMT+0700 (SE Asia Standard Time)',0),('1507208510828',1,NULL,200000,'Thu Oct 05 2017 20:01:50 GMT+0700 (SE Asia Standard Time)',0),('1507208583640',1,NULL,200000,'Thu Oct 05 2017 20:03:03 GMT+0700 (SE Asia Standard Time)',0),('1507208690899',1,2,200000,'Thu Oct 05 2017 20:04:50 GMT+0700 (SE Asia Standard Time)',11000),('1507208724434',1,2,20000,'Thu Oct 05 2017 20:05:24 GMT+0700 (SE Asia Standard Time)',11000),('1507208730132',1,NULL,1000000,'Thu Oct 05 2017 20:05:30 GMT+0700 (SE Asia Standard Time)',0),('1507208808873',1,2,200000,'Thu Oct 05 2017 20:06:48 GMT+0700 (SE Asia Standard Time)',3300),('1507209025403',2,NULL,1000000,'Thu Oct 05 2017 20:10:25 GMT+0700 (SE Asia Standard Time)',0);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'bankmanagement'
--

--
-- Dumping routines for database 'bankmanagement'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-10-05 20:11:46
