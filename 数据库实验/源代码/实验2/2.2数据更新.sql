use newBlog;
-- (1)
--��
insert into MBLOG values(44,'΢��44',1,2019,5,5,'���Բ���');
--��
update MBLOG set CONT='������' where BID = 44;
--ɾ
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
create trigger myRule --����������
on THUMB        -- ָ�������������ı�
instead of insert,update        -- insert,update ������
as
begin 
	--��ȡ�����UID��BID
	declare @newUid int
	declare @newBid int
	select @newUid = UID,@newBid = BID from inserted
	
	--��ȡɾ����(UPDATEʱ)UID��BID
	declare @oldUid int
	declare @oldBid int
	select @oldUid = UID,@oldBid = BID from deleted
	
	--��ȡ����id
	declare @blogOwnerId int
	select @blogOwnerId=UID from MBLOG where BID=@newBid
	
	if @newUid=@blogOwnerId begin	--����������ǲ������ˣ���ܾ�ִ��
		print '�ܾ�ִ��'
	end
	else begin
		--�ǲ����¼�
		if exists(select 1 from inserted) and not exists(select 1 from deleted) begin
			insert into THUMB values(@newUid,@newBid)
		end
		--�Ǹ����¼�
		else begin
			update THUMB set UID=@newUid, BID=@newBid where UID=@oldUid and BID=@oldBid
		end
	end
end
