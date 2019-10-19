use new;
create table [USER](
	UID int primary key,
	NAME char(20),
	SEX char(2),
	BYEAR int,CITY char(20)
	); 
create table LABEL(
	LID int primary key,
	LNAME char(30)
	);

create table MBLOG(
	BID int primary key,
	TITLE char(50),
	UID int,PYEAR int,
	PMONTH int,
	PDAY int,
	CONT varchar(8000)
	);

create table B_L(
	BID int,
	LID int,
	primary key(BID,LID),
	foreign key (BID) references MBLOG(BID),
	foreign key (LID) references LABEL(LID)
	);

create table FOLLOW(
	UID int,
	UIDFLED int,
	primary key(UID,UIDFLED),
	foreign key (UID) references [USER](UID),
	foreign key (UIDFLED) references [USER](UID)
	);

create table FRIENDS(
	UID int,
	FUID int,
	primary key(UID,FUID),
	foreign key (UID) references [USER](UID),
	foreign key (FUID) references [USER](UID)
	);
	
create table SUB(
	UID int,
	LID int,
	primary key(UID,LID),
	foreign key (UID) references [USER](UID),
	foreign key (LID) references LABEL(LID)
	);
	
create table THUMB(
	UID int,
	BID int
	primary key(UID,BID),
	foreign key (UID) references [USER](UID),
	foreign key (BID) references MBLOG(BID)
	);
	
create table TOPDAY(
	TYEAR int,
	TMONTH int,
	TDAY int,
	BID int,
	TNO int
	primary key(BID),
	foreign key (BID) references MBLOG(BID)
	);
	