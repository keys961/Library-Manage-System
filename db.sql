create schema book_manager;
	use book_manager;
	set autocommit = 0;

create table user
(
	username varchar(16),
	password varchar(16) not null,
	authority int,
	primary key(username)
);

create table admin
(
        username varchar(16),
        password varchar(16) not null,
        primary key(username)
);

create table book
(
	book_id char(6),
	name varchar(30) not null,
	number int unsigned not null,
	store_date date,
	publisher varchar(20) not null,
        publish_year year,
	type varchar(10) not null,
	author varchar(20) not null,
	primary key(book_id)
);

create table loan
(
	username varchar(16),
	book_id char(6),
	loan_date date,
	loan_number int unsigned,
	primary key(username, book_id, loan_number),
	foreign key(username) references user(username),
	foreign key(book_id) references book(book_id)
);

