use newBlog;
if not exists(select * from sysobjects where name = 'THUMB_RANK'
)CREATE TABLE THUMB_RANK(
BID int FOREIGN KEY REFERENCES MBLOG(BID),
THUMBNUM int
);
go

if (exists (select * from sys.objects where name = 'THUMB_RANK_PRO'))
    drop proc THUMB_RANK_PRO
go
create proc THUMB_RANK_PRO
@tyear int = YEAR,
@tmonth int = MONTH,
@tday int = DAY
as 
set nocount on;
begin
    delete from THUMB_RANK
insert into THUMB_RANK
select top(10) MBLOG.BID,COUNT(THUMB.UID) from MBLOG,THUMB
where pyear = @tyear and pmonth = @tmonth and pday = @tday and MBLOG.BID = THUMB.BID
group by MBLOG.BID order by count(THUMB.UID)
end
go

exec THUMB_RANK_PRO 2019,4,20