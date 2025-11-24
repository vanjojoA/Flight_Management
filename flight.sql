create table tickets
(
    TicketID       int auto_increment
        primary key,
    TicketType     varchar(10)                           not null comment '类型：Flight-航班, Train-火车, Bus-汽车',
    TicketNo       varchar(20)                           not null comment '票务编号',
    DepartureCity  varchar(50)                           not null comment '出发城市',
    ArrivalCity    varchar(50)                           not null comment '到达城市',
    DepartureTime  datetime                              not null comment '出发时间',
    ArrivalTime    datetime                              not null comment '到达时间',
    Price          decimal(10, 2)                        not null comment '价格',
    TotalSeats     int         default 100               not null comment '总座位数',
    AvailableSeats int         default 100               not null comment '可用座位数',
    Company        varchar(100)                          null comment '航空公司/铁路公司',
    Status         varchar(10) default 'Available'       null comment '状态：Available-可用, SoldOut-售完, Cancelled-取消',
    CreatedTime    timestamp   default CURRENT_TIMESTAMP null
);

create table users
(
    UserID      int auto_increment
        primary key,
    Username    varchar(50)                         not null,
    PWord       varchar(50)                         not null,
    CreatedTime timestamp default CURRENT_TIMESTAMP null,
    constraint Username
        unique (Username)
);

create table orders
(
    OrderID         int auto_increment
        primary key,
    UserID          int                                   not null comment '用户ID',
    TicketID        int                                   not null comment '票务ID',
    OrderNo         varchar(50)                           not null comment '订单号',
    PassengerName   varchar(50)                           not null comment '乘客姓名',
    PassengerIDCard varchar(18)                           null comment '乘客身份证号',
    ContactPhone    varchar(20)                           null comment '联系电话',
    TicketCount     int         default 1                 not null comment '购票数量',
    TotalPrice      decimal(10, 2)                        not null comment '总价',
    OrderStatus     varchar(20) default 'Pending'         null comment '订单状态：Pending-待支付, Paid-已支付, Cancelled-已取消, Completed-已完成',
    OrderTime       timestamp   default CURRENT_TIMESTAMP null comment '下单时间',
    constraint OrderNo
        unique (OrderNo),
    constraint orders_ibfk_1
        foreign key (UserID) references users (UserID)
            on delete cascade,
    constraint orders_ibfk_2
        foreign key (TicketID) references tickets (TicketID)
            on delete cascade
);

create index TicketID
    on orders (TicketID);

create index UserID
    on orders (UserID);

create table passengers
(
    PassengerID int auto_increment
        primary key,
    UserID      int                                not null,
    Name        varchar(50)                        not null,
    IDCard      varchar(18)                        not null,
    Phone       varchar(11)                        not null,
    CreatedTime datetime default CURRENT_TIMESTAMP null,
    constraint unique_user_idcard
        unique (UserID, IDCard),
    constraint passengers_ibfk_1
        foreign key (UserID) references users (UserID)
);

