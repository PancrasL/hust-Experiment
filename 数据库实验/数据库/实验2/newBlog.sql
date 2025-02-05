USE [master]
GO
/****** Object:  Database [newBlog]    Script Date: 06/19/2019 01:00:34 ******/
CREATE DATABASE [newBlog] ON  PRIMARY 
( NAME = N'newBlog', FILENAME = N'e:\Software\Microsoft SQL Server\MSSQL10_50.SQLEXPRESS\MSSQL\DATA\newBlog.mdf' , SIZE = 3072KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'newBlog_log', FILENAME = N'e:\Software\Microsoft SQL Server\MSSQL10_50.SQLEXPRESS\MSSQL\DATA\newBlog_log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [newBlog] SET COMPATIBILITY_LEVEL = 100
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [newBlog].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [newBlog] SET ANSI_NULL_DEFAULT OFF
GO
ALTER DATABASE [newBlog] SET ANSI_NULLS OFF
GO
ALTER DATABASE [newBlog] SET ANSI_PADDING OFF
GO
ALTER DATABASE [newBlog] SET ANSI_WARNINGS OFF
GO
ALTER DATABASE [newBlog] SET ARITHABORT OFF
GO
ALTER DATABASE [newBlog] SET AUTO_CLOSE OFF
GO
ALTER DATABASE [newBlog] SET AUTO_CREATE_STATISTICS ON
GO
ALTER DATABASE [newBlog] SET AUTO_SHRINK OFF
GO
ALTER DATABASE [newBlog] SET AUTO_UPDATE_STATISTICS ON
GO
ALTER DATABASE [newBlog] SET CURSOR_CLOSE_ON_COMMIT OFF
GO
ALTER DATABASE [newBlog] SET CURSOR_DEFAULT  GLOBAL
GO
ALTER DATABASE [newBlog] SET CONCAT_NULL_YIELDS_NULL OFF
GO
ALTER DATABASE [newBlog] SET NUMERIC_ROUNDABORT OFF
GO
ALTER DATABASE [newBlog] SET QUOTED_IDENTIFIER OFF
GO
ALTER DATABASE [newBlog] SET RECURSIVE_TRIGGERS OFF
GO
ALTER DATABASE [newBlog] SET  DISABLE_BROKER
GO
ALTER DATABASE [newBlog] SET AUTO_UPDATE_STATISTICS_ASYNC OFF
GO
ALTER DATABASE [newBlog] SET DATE_CORRELATION_OPTIMIZATION OFF
GO
ALTER DATABASE [newBlog] SET TRUSTWORTHY OFF
GO
ALTER DATABASE [newBlog] SET ALLOW_SNAPSHOT_ISOLATION OFF
GO
ALTER DATABASE [newBlog] SET PARAMETERIZATION SIMPLE
GO
ALTER DATABASE [newBlog] SET READ_COMMITTED_SNAPSHOT OFF
GO
ALTER DATABASE [newBlog] SET HONOR_BROKER_PRIORITY OFF
GO
ALTER DATABASE [newBlog] SET  READ_WRITE
GO
ALTER DATABASE [newBlog] SET RECOVERY SIMPLE
GO
ALTER DATABASE [newBlog] SET  MULTI_USER
GO
ALTER DATABASE [newBlog] SET PAGE_VERIFY CHECKSUM
GO
ALTER DATABASE [newBlog] SET DB_CHAINING OFF
GO
USE [newBlog]
GO
/****** Object:  Table [dbo].[USER]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[USER](
	[UID] [int] NOT NULL,
	[NAME] [char](20) NULL,
	[SEX] [char](2) NULL,
	[BYEAR] [int] NULL,
	[CITY] [char](20) NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (1, N'赵一                ', N'男', 1967, N'武汉                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (2, N'钱二                ', N'女', 1968, N'上海                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (3, N'张三                ', N'男', 1999, N'南京                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (4, N'李四                ', N'女', 2000, N'北京                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (5, N'王五                ', N'男', 2001, N'武汉                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (6, N'孙六                ', N'女', 2001, N'武汉                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (7, N'周七                ', N'男', 2002, N'武汉                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (8, N'吴八                ', N'男', 2002, N'杭州                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (9, N'郑九                ', N'男', 2003, N'南京                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (10, N'冯十                ', N'女', 2004, N'上海                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (11, N'陈十一              ', N'男', 2011, N'武汉                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (12, N'诸十二              ', N'女', 2012, N'北京                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (13, N'卫十三              ', N'女', 2011, N'上海                ')
INSERT [dbo].[USER] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (14, N'蒋十四              ', N'女', 2011, N'武汉                ')
/****** Object:  Table [dbo].[MBLOG]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[MBLOG](
	[BID] [int] NOT NULL,
	[TITLE] [char](50) NULL,
	[UID] [int] NULL,
	[PYEAR] [int] NULL,
	[PMONTH] [int] NULL,
	[PDAY] [int] NULL,
	[CONT] [varchar](8000) NULL,
PRIMARY KEY CLUSTERED 
(
	[BID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (1, N'微博1                                             ', 1, 2019, 4, 18, N'	内容中包含了“最多地铁站”和“_华中科技大学”两个词		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (2, N'微博2                                             ', 2, 2019, 4, 18, N'	华中科技大学是国家教育部直属重点综合性大学，由原华中理工大学、同济医科大学、武汉城市建设学院于2000年5月26日合并成立建设和“985工程”建设高校之一，是首批“双一流”建设高校		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (3, N'微博3                                             ', 3, 2019, 4, 18, N'	内容中包含了“最多地铁站”和“_华中科技大学”两个词		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (4, N'微博4                                             ', 4, 2019, 4, 19, N'	学校校园占地7000余亩，园内树木葱茏，碧草如茵，环境优雅，景色秀丽，绿化覆盖率72%				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (5, N'微博5                                             ', 5, 2019, 4, 19, N'	校学科齐全、结构合理，基本构建起综合性、研究型大学的学科体系	')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (6, N'微博6                                             ', 6, 2019, 4, 19, N'	学校实施“人才兴校”战略，师资力量雄厚。现有专任教师3400余人	')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (7, N'微博7                                             ', 7, 2019, 4, 19, N'	学校贯彻建设“学生、学者与学术的大学”的教育思想			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (8, N'微博8                                             ', 8, 2019, 4, 19, N'	按照“应用领先、基础突破、协调发展”的科技发展方略		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (9, N'微博9                                             ', 9, 2019, 4, 19, N'	学校坚持“服务乃宗旨，贡献即发展”的办学思路			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (10, N'微博10                                            ', 10, 2019, 4, 19, N'	学校坚持开放式办学理念，积极开展全方位、多层次的国际交流与合作')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (11, N'微博11                                            ', 11, 2019, 4, 19, N'	《巢》：“东欧文学的良心”流亡美国的坎坷人生			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (12, N'微博12                                            ', 12, 2019, 4, 19, N'	派特·巴克代表作《重生三部曲》：写给激荡时代的悲悯史诗		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (13, N'微博13                                            ', 13, 2019, 4, 19, N'	文学巨匠翻译的经典名著：全新汇编《巴金译文集》出版		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (14, N'微博14                                            ', 14, 2019, 4, 19, N'	中国某新型核潜艇接受检阅				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (15, N'微博15                                            ', 1, 2019, 4, 20, N'	中国核电装机容量升至全球第三				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (16, N'微博16                                            ', 3, 2019, 4, 20, N'	海上阅兵活动开始 习近平检阅海上编队				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (17, N'微博17                                            ', 5, 2019, 4, 20, N'	斯里兰卡警方：爆炸袭击案死亡人数升至321人			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (18, N'微博18                                            ', 7, 2019, 4, 20, N'	辽宁舰升级改造 崭新亮相				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (19, N'微博19                                            ', 9, 2019, 4, 20, N'	若是干掉慈禧荣禄，当年康党可赢				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (20, N'微博20                                            ', 11, 2019, 4, 20, N'	三省制：唐代中书门下尚书职权之争				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (21, N'微博21                                            ', 13, 2019, 4, 20, N'	华人团队突破CAR-T疗法瓶颈，有望变革治疗格局			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (22, N'微博22                                            ', 2, 2019, 4, 20, N'	宇宙大爆炸之前究竟发生了什么？				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (23, N'微博23                                            ', 4, 2019, 4, 20, N'	“信使”号研究结果表明：水星的确拥有一个固体内核			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (24, N'微博24                                            ', 6, 2019, 4, 20, N'	科学家揭秘巨石阵 DNA测序显示当时为父系社会			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (25, N'微博25                                            ', 8, 2019, 4, 20, N'	见证人类第一张黑洞照片：宇宙“巨兽”露真容			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (26, N'微博26                                            ', 10, 2019, 4, 20, N'	奇妙的天体：“致密致迷”的中子星				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (27, N'微博27                                            ', 12, 2019, 4, 20, N'	特斯拉蔚来接连报“火警” 电动车安全问题再成焦点			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (28, N'微博28                                            ', 14, 2019, 4, 21, N'	微软疑似改变计划：放弃移除Windows 10“画图”程序			')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (29, N'微博29                                            ', 7, 2019, 4, 21, N'	工信部：将在超过300个城市部署千兆宽带网				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (30, N'微博30                                            ', 6, 2019, 4, 21, N'	中国第一代钢琴家巫漪丽逝世				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (31, N'微博31                                            ', 5, 2019, 4, 21, N'	同一首歌10大巨星经典演唱会				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (32, N'微博32                                            ', 4, 2019, 4, 21, N'	张杰上海演唱会万人蹦迪				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (33, N'微博33                                            ', 3, 2019, 4, 21, N'	中央财经委员会第四次会议释放重要信号				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (34, N'微博34                                            ', 2, 2019, 4, 21, N'	人社部回应“2035年养老金将用光”				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (35, N'微博35                                            ', 1, 2019, 4, 21, N'	新华社：证券法修订草案设科创板注册制专节				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (36, N'微博36                                            ', 6, 2019, 4, 21, N'	十个哲学思想,让思想更有深度				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (37, N'微博37                                            ', 5, 2019, 4, 21, N'	黑格尔与精神现象学				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (38, N'微博38                                            ', 4, 2019, 4, 21, N'	秘境寻踪·消逝的“天梯”				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (39, N'微博39                                            ', 3, 2019, 4, 21, N'	航拍中国第二季福建				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (40, N'微博40                                            ', 2, 2019, 4, 21, N'	中国历史朝代公元对照简表				')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (41, N'微博41                                            ', 1, 2019, 4, 21, N'	西晋王朝短暂的大一统,却又迅速灭亡的原因,更值得我们去探究		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (42, N'微博42                                            ', 1, 2019, 4, 21, N'	意大利画家达芬奇(Leonardo da Vinci)介绍及作品欣赏		')
INSERT [dbo].[MBLOG] ([BID], [TITLE], [UID], [PYEAR], [PMONTH], [PDAY], [CONT]) VALUES (43, N'微博43                                            ', 2, 2019, 4, 21, N'	西班牙画家巴勃罗·毕加索介绍及作品欣赏				')
/****** Object:  Table [dbo].[LABEL]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LABEL](
	[LID] [int] NOT NULL,
	[LNAME] [char](30) NULL,
PRIMARY KEY CLUSTERED 
(
	[LID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (1, N'文学                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (2, N'艺术                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (3, N'军事                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (4, N'历史                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (5, N'地理                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (6, N'自然科学                      ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (7, N'工程技术                      ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (8, N'经济                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (9, N'教育                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (10, N'哲学                          ')
INSERT [dbo].[LABEL] ([LID], [LNAME]) VALUES (11, N'音乐                          ')
/****** Object:  Table [dbo].[FANS_3]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[FANS_3](
	[UID] [int] NOT NULL,
	[NAME] [char](20) NULL,
	[SEX] [char](2) NULL,
	[BYEAR] [int] NULL,
	[CITY] [char](20) NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[FANS_3] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (4, N'李四                ', N'女', 2000, N'北京                ')
INSERT [dbo].[FANS_3] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (6, N'孙六                ', N'女', 2001, N'武汉                ')
INSERT [dbo].[FANS_3] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (8, N'吴八                ', N'男', 2002, N'杭州                ')
INSERT [dbo].[FANS_3] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (10, N'冯十                ', N'女', 2004, N'上海                ')
INSERT [dbo].[FANS_3] ([UID], [NAME], [SEX], [BYEAR], [CITY]) VALUES (11, N'陈十一              ', N'男', 2011, N'武汉                ')
/****** Object:  Table [dbo].[test]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[test](
	[col1] [int] NULL,
	[col2] [int] NULL
) ON [PRIMARY]
GO
INSERT [dbo].[test] ([col1], [col2]) VALUES (1, 1)
INSERT [dbo].[test] ([col1], [col2]) VALUES (1, 1)
/****** Object:  Table [dbo].[THUMB_RANK]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[THUMB_RANK](
	[BID] [int] NULL,
	[THUMBNUM] [int] NULL
) ON [PRIMARY]
GO
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (25, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (24, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (23, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (22, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (21, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (20, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (19, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (18, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (17, 1)
INSERT [dbo].[THUMB_RANK] ([BID], [THUMBNUM]) VALUES (16, 1)
/****** Object:  Table [dbo].[THUMB]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[THUMB](
	[UID] [int] NOT NULL,
	[BID] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC,
	[BID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (1, 7)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (1, 21)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (1, 35)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (2, 8)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (2, 22)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (2, 36)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (3, 9)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (3, 23)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (3, 37)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (4, 10)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (4, 24)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (4, 38)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (5, 11)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (5, 25)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (5, 39)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (6, 12)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (6, 26)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (6, 40)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (7, 13)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (7, 27)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (7, 41)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (8, 14)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (8, 28)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (8, 42)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (9, 15)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (9, 29)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (9, 43)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (10, 9)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (10, 16)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (10, 30)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (11, 10)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (11, 17)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (11, 31)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (12, 11)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (12, 18)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (12, 32)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (13, 12)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (13, 19)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (13, 33)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (14, 13)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (14, 20)
INSERT [dbo].[THUMB] ([UID], [BID]) VALUES (14, 34)
/****** Object:  Table [dbo].[SUB]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[SUB](
	[UID] [int] NOT NULL,
	[LID] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC,
	[LID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (1, 1)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (1, 4)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (1, 7)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (2, 2)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (2, 5)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (2, 8)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (3, 3)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (3, 6)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (3, 9)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (4, 4)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (4, 7)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (4, 10)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (5, 5)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (5, 8)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (5, 11)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (6, 1)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (6, 6)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (6, 9)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (7, 2)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (7, 7)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (7, 10)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (8, 3)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (8, 8)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (8, 11)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (9, 1)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (9, 4)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (9, 9)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (10, 2)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (10, 5)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (10, 10)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (11, 3)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (11, 6)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (11, 11)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (12, 1)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (12, 4)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (12, 7)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (13, 2)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (13, 5)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (13, 8)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (14, 3)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (14, 6)
INSERT [dbo].[SUB] ([UID], [LID]) VALUES (14, 9)
/****** Object:  Table [dbo].[B_L]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[B_L](
	[BID] [int] NOT NULL,
	[LID] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[BID] ASC,
	[LID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (1, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (2, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (3, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (4, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (5, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (6, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (7, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (8, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (9, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (10, 9)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (11, 1)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (12, 1)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (13, 1)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (14, 3)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (15, 3)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (15, 4)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (16, 3)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (17, 3)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (18, 3)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (19, 4)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (20, 4)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (21, 6)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (22, 6)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (23, 6)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (25, 6)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (26, 6)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (27, 7)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (28, 7)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (29, 7)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (30, 11)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (31, 11)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (32, 11)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (33, 8)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (34, 8)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (35, 8)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (36, 10)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (37, 10)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (38, 5)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (39, 5)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (40, 4)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (41, 4)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (42, 2)
INSERT [dbo].[B_L] ([BID], [LID]) VALUES (43, 2)
/****** Object:  Table [dbo].[FRIENDS]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FRIENDS](
	[UID] [int] NOT NULL,
	[FUID] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC,
	[FUID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 7)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 11)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 13)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (1, 14)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (2, 6)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (2, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (2, 12)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (2, 13)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (3, 5)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (3, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (3, 11)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (3, 12)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (4, 2)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (4, 8)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (4, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (4, 11)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (5, 1)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (5, 7)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (5, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (5, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (6, 6)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (6, 8)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (6, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (7, 5)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (7, 7)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (7, 8)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (8, 4)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (8, 6)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (8, 7)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (8, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (8, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (9, 3)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (9, 5)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (9, 6)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (10, 2)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (10, 4)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (10, 5)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (11, 1)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (11, 3)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (11, 4)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (12, 2)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (12, 3)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (12, 10)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (13, 1)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (13, 2)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (13, 9)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (14, 1)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (14, 8)
INSERT [dbo].[FRIENDS] ([UID], [FUID]) VALUES (14, 12)
/****** Object:  Table [dbo].[FOLLOW]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FOLLOW](
	[UID] [int] NOT NULL,
	[UIDFLED] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[UID] ASC,
	[UIDFLED] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (1, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (2, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (3, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (3, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (3, 4)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (3, 11)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (4, 3)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (5, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (5, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (6, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (6, 3)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (7, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (7, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (8, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (8, 3)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (9, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (9, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (10, 2)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (10, 3)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (11, 3)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (11, 4)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (12, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (13, 1)
INSERT [dbo].[FOLLOW] ([UID], [UIDFLED]) VALUES (14, 1)
/****** Object:  Table [dbo].[TOPDAY]    Script Date: 06/19/2019 01:00:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TOPDAY](
	[TYEAR] [int] NULL,
	[TMONTH] [int] NULL,
	[TDAY] [int] NULL,
	[BID] [int] NOT NULL,
	[TNO] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[BID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 18, 1, 1)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 18, 2, 2)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 18, 3, 3)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 5, 1)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 6, 2)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 7, 3)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 8, 4)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 9, 5)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 10, 6)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 11, 7)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 12, 8)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 13, 9)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 19, 14, 10)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 15, 1)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 16, 2)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 17, 3)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 18, 4)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 19, 5)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 20, 6)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 21, 7)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 22, 8)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 23, 9)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 20, 24, 10)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 28, 1)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 29, 2)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 30, 3)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 31, 4)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 32, 5)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 33, 6)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 34, 7)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 35, 8)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 4, 21, 36, 9)
INSERT [dbo].[TOPDAY] ([TYEAR], [TMONTH], [TDAY], [BID], [TNO]) VALUES (2019, 5, 16, 37, 10)
/****** Object:  StoredProcedure [dbo].[THUMB_RANK_PRO]    Script Date: 06/19/2019 01:00:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create proc [dbo].[THUMB_RANK_PRO]
@tyear int = 2019,
@tmonth int = 4,
@tday int = 19
as 
set nocount on;
begin
    delete from THUMB_RANK
insert into THUMB_RANK
select top(10) MBLOG.BID,COUNT(THUMB.UID) from MBLOG,THUMB
where pyear = @tyear and pmonth = @tmonth and pday = @tday and MBLOG.BID = THUMB.BID
group by MBLOG.BID order by count(THUMB.UID)
end
GO
/****** Object:  ForeignKey [FK__THUMB_RANK__BID__4F7CD00D]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[THUMB_RANK]  WITH CHECK ADD FOREIGN KEY([BID])
REFERENCES [dbo].[MBLOG] ([BID])
GO
/****** Object:  ForeignKey [FK__THUMB__BID__24927208]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[THUMB]  WITH CHECK ADD FOREIGN KEY([BID])
REFERENCES [dbo].[MBLOG] ([BID])
GO
/****** Object:  ForeignKey [FK__THUMB__UID__239E4DCF]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[THUMB]  WITH CHECK ADD FOREIGN KEY([UID])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__SUB__LID__1ED998B2]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[SUB]  WITH CHECK ADD FOREIGN KEY([LID])
REFERENCES [dbo].[LABEL] ([LID])
GO
/****** Object:  ForeignKey [FK__SUB__UID__1DE57479]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[SUB]  WITH CHECK ADD FOREIGN KEY([UID])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__B_L__BID__0CBAE877]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[B_L]  WITH CHECK ADD FOREIGN KEY([BID])
REFERENCES [dbo].[MBLOG] ([BID])
GO
/****** Object:  ForeignKey [FK__B_L__LID__0DAF0CB0]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[B_L]  WITH CHECK ADD FOREIGN KEY([LID])
REFERENCES [dbo].[LABEL] ([LID])
GO
/****** Object:  ForeignKey [FK__FRIENDS__FUID__1920BF5C]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[FRIENDS]  WITH CHECK ADD FOREIGN KEY([FUID])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__FRIENDS__UID__182C9B23]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[FRIENDS]  WITH CHECK ADD FOREIGN KEY([UID])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__FOLLOW__UID__1273C1CD]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[FOLLOW]  WITH CHECK ADD FOREIGN KEY([UID])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__FOLLOW__UIDFLED__1367E606]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[FOLLOW]  WITH CHECK ADD FOREIGN KEY([UIDFLED])
REFERENCES [dbo].[USER] ([UID])
GO
/****** Object:  ForeignKey [FK__TOPDAY__BID__29572725]    Script Date: 06/19/2019 01:00:34 ******/
ALTER TABLE [dbo].[TOPDAY]  WITH CHECK ADD FOREIGN KEY([BID])
REFERENCES [dbo].[MBLOG] ([BID])
GO
