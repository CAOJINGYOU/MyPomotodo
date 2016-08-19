CREATE TABLE IF NOT EXISTS [MyPotato] (
[ID] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[CreateTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL,
[PotatoName] NVARCHAR(256)  NULL,
[Finish] BOOLEAN DEFAULT '0' NOT NULL,
[Pin] BOOLEAN DEFAULT '0' NOT NULL
)

--insert into MyPotato( PotatoName ) values ("×ßÂ·")

--UPDATE MyPotato SET PotatoName = 'Fred' WHERE LastName = 'Wilson' 


--UPDATE MyPotato SET Finish = 0
--select Finish from MyPotato

UPDATE MyPotato SET Finish = 1 where ID in (17)



--select PotatoName from MyPotato where Finish = 0 order by CreateTime ASC
--select PotatoName from MyPotato where Finish = 0 order by CreateTime DESC,ID DESC

CREATE VIEW IF NOT EXISTS [MyPotato_view] AS 
            select PotatoName,ID,Pin from MyPotato where Finish = 0 order by Pin DESC,CreateTime DESC,ID DESC
			
			
CREATE TABLE IF NOT EXISTS[SysConfigInfo] (
[TomatoTime] INTEGER DEFAULT '25' NOT NULL,
[RestTime] INTEGER DEFAULT '5' NOT NULL,
[LongRestTime] INTEGER DEFAULT '15' NOT NULL,
[LongRestInterval] INTEGER DEFAULT '4' NOT NULL,
[strWorkSound] NVARCHAR(256)  NULL,
[strThatSound] NVARCHAR(256)  NULL,
[DisplaySystemNotifications] BOOLEAN DEFAULT '1' NOT NULL,
[PlayTick] BOOLEAN DEFAULT '0' NOT NULL,
[PlayPromptSound] BOOLEAN DEFAULT '1' NOT NULL,
[RunningWithSystem] BOOLEAN DEFAULT '0' NOT NULL,
[FromSystemTray] BOOLEAN DEFAULT '0' NOT NULL,
[AutoAdjustSize] BOOLEAN DEFAULT '0' NOT NULL,
[State] INTEGER DEFAULT '0' NOT NULL,
[WorkTime] NVARCHAR(256) NULL,
[WorkRestTime] NVARCHAR(256) NULL
)


-- insert into SysConfigInfo values (25, 5, 15, 4, "", "", 1, 0, 1, 0, 0, 0, 0,datetime('now','localtime'),datetime('now','localtime'))

-- update SysConfigInfo set State=1
-- update SysConfigInfo set WorkTime="2016-03-25 13:48:23"

--update SysConfigInfo set TomatoTime=25
--update SysConfigInfo set RestTime=5


CREATE TABLE IF NOT EXISTS [MyTomato] (
[ID] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[TomatoName] NVARCHAR(256)  NULL,
[BeigTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL,
[EndTime] TIMESTAMP DEFAULT (datetime('now','localtime')) NOT NULL
)

--insert into MyTomato(TomatoName,BeigTime,EndTime) values  ("aa","2016-04-11 17:20:09","2016-04-11 17:20:09")

--select * from MyTomato order by ID DESC