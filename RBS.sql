-- phpMyAdmin SQL Dump
-- version 4.4.10
-- http://www.phpmyadmin.net
--
-- Host: localhost:3306
-- Generation Time: 2017-05-23 23:36:36
-- 服务器版本： 5.5.42
-- PHP Version: 7.0.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `RBS`
--
CREATE DATABASE IF NOT EXISTS `RBS` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `RBS`;

-- --------------------------------------------------------

--
-- 表的结构 `Rdownorder`
--

CREATE TABLE `Rdownorder` (
  `oID` int(11) NOT NULL,
  `tID` int(11) NOT NULL,
  `name` varchar(15) NOT NULL,
  `count` int(11) NOT NULL,
  `phone` varchar(15) NOT NULL,
  `date` date NOT NULL,
  `time` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `Rdownorder`
--

INSERT INTO `Rdownorder` (`oID`, `tID`, `name`, `count`, `phone`, `date`, `time`) VALUES
(9, 5, 'xxx', 5, '88888888', '2017-05-16', '简餐'),
(8, 4, 'xxx', 2, '88888888', '2017-05-16', '正餐'),
(17, 4, 'xxx', 2, '88888888', '2017-05-20', '简餐'),
(21, 5, 'xxx', 5, '88888888', '2017-05-23', '正餐'),
(22, 3, 'xxx', 3, '88888888', '2017-05-23', '正餐');

-- --------------------------------------------------------

--
-- 表的结构 `Rorder`
--

CREATE TABLE `Rorder` (
  `oID` int(11) NOT NULL,
  `tID` int(11) NOT NULL,
  `name` varchar(15) NOT NULL DEFAULT 'xxx',
  `count` int(11) NOT NULL,
  `phone` varchar(15) NOT NULL DEFAULT '88888888',
  `date` date NOT NULL,
  `time` varchar(15) NOT NULL,
  `state` varchar(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `Rorder`
--

INSERT INTO `Rorder` (`oID`, `tID`, `name`, `count`, `phone`, `date`, `time`, `state`) VALUES
(14, 5, '貂蝉', 5, '15850513871', '2017-05-25', '简餐', '预订中'),
(23, 5, 'xxx', 7, '88888888', '2017-05-23', '正餐', '正在用餐'),
(24, 7, 'xxx', 9, '88888888', '2017-05-23', '正餐', '正在用餐'),
(25, 1, '胥艳', 2, '18012264692', '2017-05-25', '夜宵', '预订中'),
(26, 3, '栾颖', 2, '15858505993', '2017-05-23', '夜宵', '预订中'),
(27, 5, '鲁班', 8, '18251979816', '2017-06-07', '正餐', '预订中'),
(28, 7, '蔡文姬', 10, '18767297675', '2017-07-02', '正餐', '预订中'),
(32, 10, '胥超', 11, '05722877123', '2017-06-01', '简餐', '预订中'),
(33, 3, '胥艳', 3, '123455', '2017-05-23', '简餐', '预订中'),
(34, 1, '胥艳', 2, '15850513871', '2017-05-23', '简餐', '正在用餐'),
(35, 4, 'xxx', 4, '88888888', '2017-05-23', '正餐', '正在用餐');

-- --------------------------------------------------------

--
-- 表的结构 `Rtable`
--

CREATE TABLE `Rtable` (
  `tID` int(11) NOT NULL,
  `tSize` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `Rtable`
--

INSERT INTO `Rtable` (`tID`, `tSize`) VALUES
(1, 2),
(2, 2),
(3, 4),
(4, 4),
(5, 8),
(6, 8),
(7, 10),
(8, 10),
(10, 12);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Rorder`
--
ALTER TABLE `Rorder`
  ADD PRIMARY KEY (`oID`),
  ADD KEY `fk_1` (`tID`);

--
-- Indexes for table `Rtable`
--
ALTER TABLE `Rtable`
  ADD PRIMARY KEY (`tID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Rorder`
--
ALTER TABLE `Rorder`
  MODIFY `oID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=36;
--
-- 限制导出的表
--

--
-- 限制表 `Rorder`
--
ALTER TABLE `Rorder`
  ADD CONSTRAINT `fk_1` FOREIGN KEY (`tID`) REFERENCES `Rtable` (`tID`) ON DELETE CASCADE ON UPDATE CASCADE;
