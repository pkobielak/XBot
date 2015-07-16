-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Czas generowania: 30 Sty 2015, 00:24
-- Wersja serwera: 5.6.21
-- Wersja PHP: 5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `xbot`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `bots_commands`
--

CREATE TABLE IF NOT EXISTS `bots_commands` (
  `ID` text NOT NULL,
  `COMMAND` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `bots_info`
--

CREATE TABLE IF NOT EXISTS `bots_info` (
  `ID` text NOT NULL,
  `VERSION` text NOT NULL,
  `IP` text NOT NULL,
  `OS` text NOT NULL,
  `CPU` text NOT NULL,
  `LAST_SEEN` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Zrzut danych tabeli `bots_info`
--

INSERT INTO `bots_info` (`ID`, `VERSION`, `IP`, `OS`, `CPU`, `LAST_SEEN`) VALUES
('a6d7edea55efff4c9a98d4e34b366e2157bccc595c7e249eea331677e1f4f76d', '1.00.05', '192.168.55.100', 'Windows 7', '3.70GHz', '2015-01-28 14:18:38');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
