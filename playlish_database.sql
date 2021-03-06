USE [master]
GO
/****** Object:  Database [playlish]    Script Date: 10.6.2021 г. 21:49:42 ******/
CREATE DATABASE [playlish]
GO
ALTER DATABASE [playlish] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [playlish].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [playlish] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [playlish] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [playlish] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [playlish] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [playlish] SET ARITHABORT OFF 
GO
ALTER DATABASE [playlish] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [playlish] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [playlish] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [playlish] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [playlish] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [playlish] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [playlish] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [playlish] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [playlish] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [playlish] SET  DISABLE_BROKER 
GO
ALTER DATABASE [playlish] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [playlish] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [playlish] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [playlish] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [playlish] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [playlish] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [playlish] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [playlish] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [playlish] SET  MULTI_USER 
GO
ALTER DATABASE [playlish] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [playlish] SET DB_CHAINING OFF 
GO
ALTER DATABASE [playlish] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [playlish] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [playlish] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [playlish] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
ALTER DATABASE [playlish] SET QUERY_STORE = OFF
GO
USE [playlish]
GO
/****** Object:  User [tsetso]    Script Date: 10.6.2021 г. 21:49:43 ******/
CREATE USER [tsetso] FOR LOGIN [tsetso] WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  User [playlish]    Script Date: 10.6.2021 г. 21:49:43 ******/
CREATE USER [playlish] FOR LOGIN [nikolay] WITH DEFAULT_SCHEMA=[dbo]
GO
ALTER ROLE [db_owner] ADD MEMBER [tsetso]
GO
ALTER ROLE [db_owner] ADD MEMBER [playlish]
GO
/****** Object:  Table [dbo].[genres]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[genres](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](255) NOT NULL,
 CONSTRAINT [PK_genres] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[playlist_song]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[playlist_song](
	[playlist_id] [int] NOT NULL,
	[song_id] [int] NOT NULL,
 CONSTRAINT [PK_playlist_song] PRIMARY KEY CLUSTERED 
(
	[playlist_id] ASC,
	[song_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[playlist_user]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[playlist_user](
	[playlist_id] [int] NOT NULL,
	[user_id] [int] NOT NULL,
 CONSTRAINT [PK_playlist_user] PRIMARY KEY CLUSTERED 
(
	[playlist_id] ASC,
	[user_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[playlists]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[playlists](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](255) NOT NULL,
	[active_from] [datetime] NULL,
	[active_to] [datetime] NULL,
 CONSTRAINT [PK_playlists] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[songs]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[songs](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](1000) NOT NULL,
	[length] [smallint] NULL,
	[performer] [nvarchar](1000) NULL,
	[genre_id] [int] NULL,
 CONSTRAINT [PK_songs] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[users]    Script Date: 10.6.2021 г. 21:49:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[users](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](255) NOT NULL,
	[email] [nvarchar](255) NULL,
	[password] [nvarchar](255) NOT NULL,
	[active_from] [datetime] NULL,
	[active_to] [datetime] NULL,
 CONSTRAINT [PK_users] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[genres] ON 

INSERT [dbo].[genres] ([id], [name]) VALUES (4, N'Jazz')
INSERT [dbo].[genres] ([id], [name]) VALUES (5, N'Rock')
INSERT [dbo].[genres] ([id], [name]) VALUES (6, N'Metal')
INSERT [dbo].[genres] ([id], [name]) VALUES (7, N'Pop')
INSERT [dbo].[genres] ([id], [name]) VALUES (8, N'Country')
SET IDENTITY_INSERT [dbo].[genres] OFF
GO
SET IDENTITY_INSERT [dbo].[users] ON 

INSERT [dbo].[users] ([id], [name], [email], [password], [active_from], [active_to]) VALUES (38, N'nikolay', N'nikolayynayydenov@gmail.com', N'12345678', CAST(N'2021-04-21T00:00:00.000' AS DateTime), NULL)
SET IDENTITY_INSERT [dbo].[users] OFF
GO
ALTER TABLE [dbo].[playlist_song]  WITH CHECK ADD  CONSTRAINT [FK_playlist_song_playlists] FOREIGN KEY([playlist_id])
REFERENCES [dbo].[playlists] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[playlist_song] CHECK CONSTRAINT [FK_playlist_song_playlists]
GO
ALTER TABLE [dbo].[playlist_song]  WITH CHECK ADD  CONSTRAINT [FK_playlist_song_songs] FOREIGN KEY([song_id])
REFERENCES [dbo].[songs] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[playlist_song] CHECK CONSTRAINT [FK_playlist_song_songs]
GO
ALTER TABLE [dbo].[playlist_user]  WITH CHECK ADD  CONSTRAINT [FK_playlist_user_playlists] FOREIGN KEY([playlist_id])
REFERENCES [dbo].[playlists] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[playlist_user] CHECK CONSTRAINT [FK_playlist_user_playlists]
GO
ALTER TABLE [dbo].[playlist_user]  WITH CHECK ADD  CONSTRAINT [FK_playlist_user_users] FOREIGN KEY([user_id])
REFERENCES [dbo].[users] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[playlist_user] CHECK CONSTRAINT [FK_playlist_user_users]
GO
ALTER TABLE [dbo].[songs]  WITH CHECK ADD  CONSTRAINT [FK_songs_genres] FOREIGN KEY([genre_id])
REFERENCES [dbo].[genres] ([id])
GO
ALTER TABLE [dbo].[songs] CHECK CONSTRAINT [FK_songs_genres]
GO
USE [master]
GO
ALTER DATABASE [playlish] SET  READ_WRITE 
GO
