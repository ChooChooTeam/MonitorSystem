/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     2018/1/9 18:50:10                            */
/*==============================================================*/


if exists (select 1
            from  sysobjects
           where  id = object_id('Admin')
            and   type = 'U')
   drop table Admin
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Client')
            and   type = 'U')
   drop table Client
go

/*==============================================================*/
/* Table: Admin                                                 */
/*==============================================================*/
create table Admin (
   AdminName            char(32)             not null,
   AdminPWord           char(32)             not null,
   constraint PK_ADMIN primary key nonclustered (AdminName)
)
go

/*==============================================================*/
/* Table: Client                                                */
/*==============================================================*/
create table Client (
   UserName             char(32)             not null,
   ClientPwd            char(32)             not null,
   constraint PK_CLIENT primary key nonclustered (UserName)
)
go

