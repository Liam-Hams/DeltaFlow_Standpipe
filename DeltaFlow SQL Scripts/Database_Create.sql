USE [master]
GO

/****** Object:  Database [Deltaflow_Home]    Script Date: 07/07/2021 10:58:16 ******/
CREATE DATABASE [Deltaflow_Home]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Deltaflow_Home', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\DATA\Deltaflow_Home.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'Deltaflow_Home_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\DATA\Deltaflow_Home_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO

IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Deltaflow_Home].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO

ALTER DATABASE [Deltaflow_Home] SET ANSI_NULL_DEFAULT OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET ANSI_NULLS OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET ANSI_PADDING OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET ANSI_WARNINGS OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET ARITHABORT OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET AUTO_CLOSE OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET AUTO_SHRINK OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET AUTO_UPDATE_STATISTICS ON 
GO

ALTER DATABASE [Deltaflow_Home] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET CURSOR_DEFAULT  GLOBAL 
GO

ALTER DATABASE [Deltaflow_Home] SET CONCAT_NULL_YIELDS_NULL OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET NUMERIC_ROUNDABORT OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET QUOTED_IDENTIFIER OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET RECURSIVE_TRIGGERS OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET  DISABLE_BROKER 
GO

ALTER DATABASE [Deltaflow_Home] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET TRUSTWORTHY OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET PARAMETERIZATION SIMPLE 
GO

ALTER DATABASE [Deltaflow_Home] SET READ_COMMITTED_SNAPSHOT OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET HONOR_BROKER_PRIORITY OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET RECOVERY SIMPLE 
GO

ALTER DATABASE [Deltaflow_Home] SET  MULTI_USER 
GO

ALTER DATABASE [Deltaflow_Home] SET PAGE_VERIFY CHECKSUM  
GO

ALTER DATABASE [Deltaflow_Home] SET DB_CHAINING OFF 
GO

ALTER DATABASE [Deltaflow_Home] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO

ALTER DATABASE [Deltaflow_Home] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO

ALTER DATABASE [Deltaflow_Home] SET DELAYED_DURABILITY = DISABLED 
GO

ALTER DATABASE [Deltaflow_Home] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO

ALTER DATABASE [Deltaflow_Home] SET QUERY_STORE = OFF
GO

ALTER DATABASE [Deltaflow_Home] SET  READ_WRITE 
GO

