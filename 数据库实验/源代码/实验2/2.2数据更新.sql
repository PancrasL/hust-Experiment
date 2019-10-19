use newBlog;
-- (1)
--增
insert into MBLOG values(44,'微博44',1,2019,5,5,'测试测试');
--改
update MBLOG set CONT='新内容' where BID = 44;
--删
delete from MBLOG where BID = 44;
-- (2)
create table FANS_3(
	UID int primary key,
	NAME char(20),
	SEX char(2),
	BYEAR int,
	CITY char(20))
insert into FANS_3 select * from [USER]
where [USER].UID in
	(select UID from FOLLOW where FOLLOW.UIDFLED=3);
		
-- (5)
go
create trigger myRule --触发器名称
on THUMB        -- 指定创建触发器的表
instead of insert,update        -- insert,update 触发器
as
begin 
	--获取插入的UID和BID
	declare @newUid int
	declare @newBid int
	select @newUid = UID,@newBid = BID from inserted
	
	--获取删除的(UPDATE时)UID和BID
	declare @oldUid int
	declare @oldBid int
	select @oldUid = UID,@oldBid = BID from deleted
	
	--获取博主id
	declare @blogOwnerId int
	select @blogOwnerId=UID from MBLOG where BID=@newBid
	
	if @newUid=@blogOwnerId begin	--如果点赞者是博主本人，则拒绝执行
		print '拒绝执行'
	end
	else begin
		--是插入事件
		if exists(select 1 from inserted) and not exists(select 1 from deleted) begin
			insert into THUMB values(@newUid,@newBid)
		end
		--是更新事件
		else begin
			update THUMB set UID=@newUid, BID=@newBid where UID=@oldUid and BID=@oldBid
		end
	end
end
