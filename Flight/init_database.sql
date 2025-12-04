-- 订票系统数据库初始化脚本
-- 数据库名称: Flight

-- 用户表（如果不存在）
CREATE TABLE IF NOT EXISTS users (
    UserID INT AUTO_INCREMENT PRIMARY KEY,
    Username VARCHAR(50) NOT NULL UNIQUE,
    PWord VARCHAR(50) NOT NULL,
    CreatedTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
ALTER TABLE users ADD COLUMN Balance DECIMAL(10, 2) NOT NULL DEFAULT 0.00;

-- 票务表（航班/车次信息）
CREATE TABLE IF NOT EXISTS tickets (
    TicketID INT AUTO_INCREMENT PRIMARY KEY,
    TicketType VARCHAR(10) NOT NULL COMMENT '类型：Flight-航班, Train-火车, Bus-汽车',
    TicketNo VARCHAR(20) NOT NULL COMMENT '票务编号',
    DepartureCity VARCHAR(50) NOT NULL COMMENT '出发城市',
    ArrivalCity VARCHAR(50) NOT NULL COMMENT '到达城市',
    DepartureTime DATETIME NOT NULL COMMENT '出发时间',
    ArrivalTime DATETIME NOT NULL COMMENT '到达时间',
    Price DECIMAL(10, 2) NOT NULL COMMENT '价格',
    TotalSeats INT NOT NULL DEFAULT 100 COMMENT '总座位数',
    AvailableSeats INT NOT NULL DEFAULT 100 COMMENT '可用座位数',
    Company VARCHAR(100) COMMENT '航空公司/铁路公司',
    Status VARCHAR(10) DEFAULT 'Available' COMMENT '状态：Available-可用, SoldOut-售完, Cancelled-取消',
    CreatedTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 订单表
CREATE TABLE IF NOT EXISTS orders (
    OrderID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT NOT NULL COMMENT '用户ID',
    TicketID INT NOT NULL COMMENT '票务ID',
    OrderNo VARCHAR(50) NOT NULL UNIQUE COMMENT '订单号',
    PassengerName VARCHAR(50) NOT NULL COMMENT '乘客姓名',
    PassengerIDCard VARCHAR(18) COMMENT '乘客身份证号',
    ContactPhone VARCHAR(20) COMMENT '联系电话',
    TicketCount INT NOT NULL DEFAULT 1 COMMENT '购票数量',
    TotalPrice DECIMAL(10, 2) NOT NULL COMMENT '总价',
    OrderStatus VARCHAR(20) DEFAULT 'Pending' COMMENT '订单状态：Pending-待支付, Paid-已支付, Cancelled-已取消, Completed-已完成',
    OrderTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '下单时间',
    FOREIGN KEY (UserID) REFERENCES users(UserID) ON DELETE CASCADE,
    FOREIGN KEY (TicketID) REFERENCES tickets(TicketID) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS favorites (
    FavoriteID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT NOT NULL,
    TicketID INT NOT NULL,
    CreatedTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES users(UserID) ON DELETE CASCADE,
    FOREIGN KEY (TicketID) REFERENCES tickets(TicketID) ON DELETE CASCADE,
    UNIQUE KEY unique_user_ticket (UserID, TicketID)
);
-- 插入示例票务数据
INSERT INTO tickets (TicketType, TicketNo, DepartureCity, ArrivalCity, DepartureTime, ArrivalTime, Price, TotalSeats, AvailableSeats, Company, Status) VALUES
('Flight', 'CA1234', '北京', '上海', '2024-12-20 08:00:00', '2024-12-20 10:30:00', 680.00, 150, 150, '中国国际航空', 'Available'),
('Flight', 'MU5678', '北京', '上海', '2024-12-20 14:00:00', '2024-12-20 16:30:00', 720.00, 180, 180, '中国东方航空', 'Available'),
('Flight', 'CZ9012', '上海', '广州', '2024-12-21 09:00:00', '2024-12-21 11:30:00', 850.00, 200, 200, '中国南方航空', 'Available'),
('Flight', 'CA3456', '广州', '深圳', '2024-12-21 15:00:00', '2024-12-21 16:00:00', 380.00, 120, 120, '中国国际航空', 'Available'),
('Train', 'G123', '北京', '上海', '2024-12-20 07:00:00', '2024-12-20 12:30:00', 553.00, 500, 500, '中国铁路', 'Available'),
('Train', 'G456', '北京', '上海', '2024-12-20 13:00:00', '2024-12-20 18:30:00', 553.00, 500, 498, '中国铁路', 'Available'),
('Train', 'D789', '上海', '广州', '2024-12-21 08:00:00', '2024-12-21 16:00:00', 730.00, 600, 600, '中国铁路', 'Available'),
('Train', 'G101', '广州', '深圳', '2024-12-21 10:00:00', '2024-12-21 11:00:00', 74.50, 800, 800, '中国铁路', 'Available'),
('Bus', 'B001', '北京', '天津', '2024-12-20 08:00:00', '2024-12-20 10:00:00', 45.00, 40, 40, '长途客运', 'Available'),
('Bus', 'B002', '上海', '苏州', '2024-12-20 09:00:00', '2024-12-20 10:30:00', 35.00, 45, 45, '长途客运', 'Available');
