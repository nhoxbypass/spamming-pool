USE [master]
GO

/****** Object:  Database [DIARY]    Script Date: 10/4/2016 11:26:02 PM ******/
CREATE DATABASE [DIARY]
GO



/****** Object:  Table [dbo].[Account]    Script Date: 10/4/2016 11:27:31 PM ******/
USE [DIARY]
GO

CREATE TABLE [Account](
	[username] [varchar](255) NOT NULL PRIMARY KEY,
	[password] [varchar](255) NULL)
GO

