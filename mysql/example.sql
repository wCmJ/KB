
show variables like "autocommit";

select * from information_schema.innodb_trx where TIME_TO_SEC(timediff(now(), trx_started)) > 60;

create table T(
    id int primary key,
    k int not null,
    name varchar(16),
    index (k)
)engine=InnoDB;

alter table T drop primary key;
alter table T add primary key(name);

insert into T values(100, 1, 'aa'), (200, 2, 'bb'), (300, 3, 'cc'), (500, 5, 'ee')；





