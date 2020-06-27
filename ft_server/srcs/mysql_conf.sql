CREATE DATABASE wordpress;
CREATE USER 'wquinoa'@'localhost' IDENTIFIED BY '';
GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost';
GRANT ALL PRIVILEGES ON wordpress.* TO 'wquinoa'@'localhost';
FLUSH PRIVILEGES;
UPDATE mysql.user SET plugin = 'mysql_native_password' WHERE user='root';