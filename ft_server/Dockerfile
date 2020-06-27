# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/08 02:36:44 by wquinoa           #+#    #+#              #
#    Updated: 2020/06/28 01:07:05 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

RUN apt-get update
RUN apt-get upgrade -y

# Install some good stuff
RUN apt-get -y install nginx
RUN apt-get -y install mariadb-server
RUN apt-get -y install php7.3 php-mysql php-fpm php-cli php-mbstring
RUN apt-get -y install wget

# Set up nginx
COPY ./srcs/nginx.conf /etc/nginx/sites-available/localhost
RUN ln -s /etc/nginx/sites-available/localhost /etc/nginx/sites-enabled/localhost

# Install phpmyadmin
WORKDIR /var/www/localhost/
RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.5/phpMyAdmin-4.9.5-english.tar.gz
RUN tar -xf phpMyAdmin-4.9.5-english.tar.gz
RUN rm -rf phpMyAdmin-4.9.5-english.tar.gz
RUN mv phpMyAdmin-4.9.5-english phpmyadmin
COPY ./srcs/config.inc.php phpmyadmin

# Setting up wordpress and mysql
COPY ./srcs/wordpress.tar .
RUN tar -xf wordpress.tar
RUN rm -rf wordpress.tar
COPY ./srcs/wp-config.php wordpress
COPY ./srcs/wordpress.sql /var/
COPY ./srcs/mysql_conf.sql /var/
RUN service mysql start && mysql -u root mysql < /var/mysql_conf.sql && mysql wordpress -u root --password=  < /var/wordpress.sql

# Openssl
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -subj '/C=AB/ST=CD/L=EF/O=21/CN=wquinoa' \
	-keyout /etc/ssl/certs/localhost.key -out /etc/ssl/certs/localhost.crt

# Misc
RUN chown -R www-data:www-data /var/*
RUN chmod 777 -R /var/*
RUN chmod 755 /var/www/localhost/phpmyadmin/config.inc.php
RUN rm /etc/nginx/sites-enabled/default

COPY ./srcs/run.sh /var/
COPY ./srcs/autoindex.sh /
EXPOSE 80 443
CMD bash /var/run.sh
