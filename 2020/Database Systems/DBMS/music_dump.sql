-- MariaDB dump 10.18  Distrib 10.5.8-MariaDB, for osx10.15 (x86_64)
--
-- Host: localhost    Database: music
-- ------------------------------------------------------
-- Server version	10.5.8-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `music`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `music` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;

USE `music`;

--
-- Table structure for table `ARTIST`
--

DROP TABLE IF EXISTS `ARTIST`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ARTIST` (
  `Name` varchar(15) NOT NULL,
  `Number` int(11) NOT NULL,
  `Debut` date DEFAULT NULL,
  `MgrSsn` varchar(15) NOT NULL,
  PRIMARY KEY (`Number`),
  KEY `MgrSsn` (`MgrSsn`),
  CONSTRAINT `artist_ibfk_1` FOREIGN KEY (`MgrSsn`) REFERENCES `MANAGER` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ARTIST`
--

LOCK TABLES `ARTIST` WRITE;
/*!40000 ALTER TABLE `ARTIST` DISABLE KEYS */;
INSERT INTO `ARTIST` VALUES ('Mariah Carey',1,'1990-06-12','384920394'),('Ariana Grande',2,'2012-08-31','384920394'),('Haven Gillespie',3,NULL,'384920394'),('Frederick Coots',4,NULL,'384920394'),('jiwon',5,'2000-03-28','283940174'),('Blackpink',6,'2016-08-08','123456789'),('Maroon',7,'2004-03-19','283940174'),('Maroon',8,'2004-03-19','283940174');
/*!40000 ALTER TABLE `ARTIST` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `COMPOSE`
--

DROP TABLE IF EXISTS `COMPOSE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `COMPOSE` (
  `SNum` int(11) NOT NULL,
  `ArtNum` int(11) NOT NULL,
  PRIMARY KEY (`SNum`,`ArtNum`),
  KEY `ArtNum` (`ArtNum`),
  CONSTRAINT `compose_ibfk_1` FOREIGN KEY (`SNum`) REFERENCES `SONG` (`Number`),
  CONSTRAINT `compose_ibfk_2` FOREIGN KEY (`ArtNum`) REFERENCES `ARTIST` (`Number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `COMPOSE`
--

LOCK TABLES `COMPOSE` WRITE;
/*!40000 ALTER TABLE `COMPOSE` DISABLE KEYS */;
INSERT INTO `COMPOSE` VALUES (1,1),(2,2),(3,4),(5,7);
/*!40000 ALTER TABLE `COMPOSE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CONTAIN`
--

DROP TABLE IF EXISTS `CONTAIN`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CONTAIN` (
  `SNum` int(11) NOT NULL,
  `PNum` int(11) NOT NULL,
  `SubSsn` varchar(9) NOT NULL,
  PRIMARY KEY (`SNum`,`PNum`),
  KEY `PNum` (`PNum`),
  KEY `SubSsn` (`SubSsn`),
  CONSTRAINT `contain_ibfk_1` FOREIGN KEY (`SNum`) REFERENCES `SONG` (`Number`),
  CONSTRAINT `contain_ibfk_2` FOREIGN KEY (`PNum`) REFERENCES `PLAYLIST` (`Number`),
  CONSTRAINT `contain_ibfk_3` FOREIGN KEY (`SubSsn`) REFERENCES `SUBSCRIBER` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CONTAIN`
--

LOCK TABLES `CONTAIN` WRITE;
/*!40000 ALTER TABLE `CONTAIN` DISABLE KEYS */;
INSERT INTO `CONTAIN` VALUES (1,1,'192838844'),(2,1,'192838844'),(3,1,'192838844');
/*!40000 ALTER TABLE `CONTAIN` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `GENRE`
--

DROP TABLE IF EXISTS `GENRE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `GENRE` (
  `SNum` int(11) NOT NULL,
  `Genre` varchar(30) NOT NULL,
  PRIMARY KEY (`SNum`,`Genre`),
  CONSTRAINT `genre_ibfk_1` FOREIGN KEY (`SNum`) REFERENCES `SONG` (`Number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `GENRE`
--

LOCK TABLES `GENRE` WRITE;
/*!40000 ALTER TABLE `GENRE` DISABLE KEYS */;
INSERT INTO `GENRE` VALUES (1,'Carol');
/*!40000 ALTER TABLE `GENRE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MANAGER`
--

DROP TABLE IF EXISTS `MANAGER`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MANAGER` (
  `Name` varchar(15) NOT NULL,
  `Ssn` varchar(9) NOT NULL,
  `NickName` varchar(15) NOT NULL,
  PRIMARY KEY (`Ssn`),
  UNIQUE KEY `NickName` (`NickName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MANAGER`
--

LOCK TABLES `MANAGER` WRITE;
/*!40000 ALTER TABLE `MANAGER` DISABLE KEYS */;
INSERT INTO `MANAGER` VALUES ('Pluto','039482174','Puppy'),('Elsa','123456789','Snowflake'),('Minie','234567891','Mice'),('Donald','283940174','Duck'),('Pooh','384920394','Bear'),('Stich','457382914','Bug'),('Goofy','483028472','Dog');
/*!40000 ALTER TABLE `MANAGER` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PLAYLIST`
--

DROP TABLE IF EXISTS `PLAYLIST`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PLAYLIST` (
  `Name` varchar(15) NOT NULL,
  `Number` int(11) NOT NULL,
  `SubSsn` varchar(9) NOT NULL,
  PRIMARY KEY (`Number`,`SubSsn`),
  UNIQUE KEY `Name` (`Name`),
  KEY `SubSsn` (`SubSsn`),
  CONSTRAINT `playlist_ibfk_1` FOREIGN KEY (`SubSsn`) REFERENCES `SUBSCRIBER` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PLAYLIST`
--

LOCK TABLES `PLAYLIST` WRITE;
/*!40000 ALTER TABLE `PLAYLIST` DISABLE KEYS */;
INSERT INTO `PLAYLIST` VALUES ('Christmas',1,'192838844'),('Happy',2,'392883044');
/*!40000 ALTER TABLE `PLAYLIST` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SING`
--

DROP TABLE IF EXISTS `SING`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SING` (
  `SNum` int(11) NOT NULL,
  `ArtNum` int(11) NOT NULL,
  PRIMARY KEY (`SNum`,`ArtNum`),
  KEY `ArtNum` (`ArtNum`),
  CONSTRAINT `sing_ibfk_1` FOREIGN KEY (`SNum`) REFERENCES `SONG` (`Number`),
  CONSTRAINT `sing_ibfk_2` FOREIGN KEY (`ArtNum`) REFERENCES `ARTIST` (`Number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SING`
--

LOCK TABLES `SING` WRITE;
/*!40000 ALTER TABLE `SING` DISABLE KEYS */;
INSERT INTO `SING` VALUES (1,1),(2,2),(3,1),(5,7);
/*!40000 ALTER TABLE `SING` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SONG`
--

DROP TABLE IF EXISTS `SONG`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SONG` (
  `Title` varchar(100) NOT NULL,
  `Number` int(11) NOT NULL,
  `Lyrics` varchar(8000) NOT NULL,
  `PlayTime` int(11) NOT NULL,
  `PlayCount` int(11) NOT NULL DEFAULT 0,
  `MgrSsn` varchar(9) NOT NULL,
  PRIMARY KEY (`Number`),
  KEY `MgrSsn` (`MgrSsn`),
  CONSTRAINT `song_ibfk_1` FOREIGN KEY (`MgrSsn`) REFERENCES `MANAGER` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SONG`
--

LOCK TABLES `SONG` WRITE;
/*!40000 ALTER TABLE `SONG` DISABLE KEYS */;
INSERT INTO `SONG` VALUES ('All I Want For Christmas Is You',1,'I don\'t want a lot for Christmas\nThere is just one thing I need\nI don\'t care about the presents\nUnderneath the Christmas tree\nI just want you for my own\nMore than you could ever know\nMake my wish come true\nAll I want for Christmas is you, yeah\nI don\'t want a lot for Christmas\nThere is just one thing I need\nAnd I don\'t care about the presents\nUnderneath the Christmas tree\nI don\'t need to hang my stocking\nThere upon the fireplace\nSanta Claus won\'t make me happy\nWith a toy on Christmas Day\nI just want you for my own\nMore than you could ever know\nMake my wish come true\nAll I want for Christmas is you\nYou, baby\nOh, I won\'t ask for much this Christmas\nI won\'t even wish for snow\nAnd I\'m just gonna keep on waiting\nUnderneath the mistletoe\nI won\'t make a list and send it\nTo the North Pole for Saint Nick\nI won\'t even stay awake to\nHear those magic reindeer click\n\'Cause I just want you here tonight\nHolding on to me so tight\nWhat more can I do?\nBaby, all I want for Christmas is you\nYou, baby\nOh, all the lights are shining so brightly everywhere\nAnd the sound of children\'s laughter fills the air\nAnd everyone is singing\nI hear those sleigh bells ringing\nSanta, won\'t you bring me the one I really need?\nWon\'t you please bring my baby to me?\nOh, I don\'t want a lot for Christmas\nThis is all I\'m asking for\nI just wanna see my baby\nStanding right outside my door\nOh, I just want you for my own\nMore than you could ever know\nMake my wish come true\nBaby, all I want for Christmas... is you\nYou, baby\nAll I want for Christmas is you, baby\nAll I want for Christmas is you, baby\nAll I want for Christmas is you, baby\nAll I want for Christmas is you, baby\nAll I want for Christmas is you, baby',241,3,'457382914'),('Santa Tell Me',2,'Santa tell me if you\'re really there\nDon\'t make me fall in love again\nIf he won\'t be here next year\nSanta tell me if he really cares\n\'Cause I can give it all away if he won\'t be here next year\nFeeling Christmas all around\nAnd I\'m trying to play it cool\nBut it\'s hard to focus when I see you walking around the room\nLet it snow, it\'s blasting now\nBut I won\'t get in the mood\nI\'m avoiding every mistletoe until I know\nIt\'s true love that he thinks of\nSo next Christmas\nI\'m not all alone, boy\nSanta, tell me if you\'re really there\nDon\'t make me fall in love again if he won\'t be here\nNext year\nSanta, tell me if he really cares\n\'Cause I can\'t give it all away if he won\'t be here\nNext year\nI\'ve been down this road before\nFell in love on Christmas night\nBut on New Year\'s Day I woke up and he wasn\'t by my side\nNow I need someone to hold\nBe my fire in the cold\nBut it\'s hard to tell if this is just a fling\nOr if it\'s true love that he thinks of\nSo next Christmas\nI\'m not all alone, babe\nSanta, tell me if you\'re really there\nDon\'t make me fall in love again if he won\'t be here\nNext year\nSanta, tell me if he really cares\n\'Cause I can\'t give it all away if he won\'t be here\nNext year\nOh, I wanna have him beside me like oh-oh-oh\nOn the 25th by the fire place, oh-oh-oh\nBut I don\'t want no broken heart\nThis year I\'ve got to be smart\nOh, baby\nIf you want me, if you want me\nSanta, tell me if you\'re really there\nDon\'t make me fall in love again if he won\'t be here\nNext year\nSanta, tell me if he really cares\n\'Cause I can\'t give it all away if he won\'t be here\nNext year\nSanta, tell me if you\'re really there\nDon\'t make me fall in love again if he won\'t be here\nNext year\nSanta, tell me if he really cares\n\'Cause I can\'t give it all away if he won\'t be here\nNext year',204,2,'483028472'),('Santa Clause is Comin\' to Town',3,'You better watch out\nYou better not cry\nYou better not pout\nI\'m telling you why\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nHe\'s making a list\nHe\'s checking it twice\nHe\'s gonna find out\nWho\'s naughty or nice\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nHe sees you when you\'re sleeping\nHe knows when you\'re awake\nHe knows if you\'ve been bad or good\nSo be good for goodness sake\nSo you better watch out\nYou better not cry\nYou better not pout\nI\'m telling you why\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nSanta Claus is comin\' to town\nThe kids in girl and boyland\nWill have a jubilee\nThey\'re gonna build a toyland\nAll around the Christmas tree\nSo you better watch out\nYou better not cry\nYou better not pout\nI\'m telling you why\nSanta Claus (is comin\' to town)\nSanta Claus (is comin\' to town)\nSanta Claus is comin\'\nSanta Claus is comin\'\nSanta Claus is comin\'\nTo town',204,2,'483028472'),('Lalala',4,'Haha',180,0,'123456789'),('Sugar',5,'sugar',200,0,'283940174');
/*!40000 ALTER TABLE `SONG` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SUBSCRIBER`
--

DROP TABLE IF EXISTS `SUBSCRIBER`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SUBSCRIBER` (
  `Name` varchar(15) NOT NULL,
  `Ssn` varchar(9) NOT NULL,
  `MgrSsn` varchar(9) NOT NULL,
  `NickName` varchar(15) NOT NULL,
  PRIMARY KEY (`Ssn`),
  UNIQUE KEY `NickName` (`NickName`),
  KEY `MgrSsn` (`MgrSsn`),
  CONSTRAINT `subscriber_ibfk_1` FOREIGN KEY (`MgrSsn`) REFERENCES `MANAGER` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SUBSCRIBER`
--

LOCK TABLES `SUBSCRIBER` WRITE;
/*!40000 ALTER TABLE `SUBSCRIBER` DISABLE KEYS */;
INSERT INTO `SUBSCRIBER` VALUES ('Aladdin','119385729','384920394','Lamp'),('Abu','192838844','384920394','Monkey'),('Ariel','203985322','123456789','Foam'),('Genie','349285029','384920394','Wish'),('Snow White','392883044','123456789','apple');
/*!40000 ALTER TABLE `SUBSCRIBER` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `WRITE_SONG`
--

DROP TABLE IF EXISTS `WRITE_SONG`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `WRITE_SONG` (
  `SNum` int(11) NOT NULL,
  `ArtNum` int(11) NOT NULL,
  PRIMARY KEY (`SNum`,`ArtNum`),
  KEY `ArtNum` (`ArtNum`),
  CONSTRAINT `write_song_ibfk_1` FOREIGN KEY (`SNum`) REFERENCES `SONG` (`Number`),
  CONSTRAINT `write_song_ibfk_2` FOREIGN KEY (`ArtNum`) REFERENCES `ARTIST` (`Number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `WRITE_SONG`
--

LOCK TABLES `WRITE_SONG` WRITE;
/*!40000 ALTER TABLE `WRITE_SONG` DISABLE KEYS */;
INSERT INTO `WRITE_SONG` VALUES (1,1),(2,2),(3,3),(5,7);
/*!40000 ALTER TABLE `WRITE_SONG` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-12-07 23:39:26
