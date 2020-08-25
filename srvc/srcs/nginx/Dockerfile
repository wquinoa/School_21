# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 15:25:06 by wquinoa           #+#    #+#              #
#    Updated: 2020/08/12 17:40:57 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine

RUN apk update
RUN apk upgrade
RUN apk add nginx
RUN apk add openssl
RUN apk add openssh
RUN apk add openrc
RUN apk add supervisor
VOLUME [ "/sys/fs/cgroup" ]

COPY ./src/nginx.conf /etc/nginx/conf.d/deafult.conf
COPY ./src/supervisor.conf /etc/supervisord.conf
RUN chmod +rw /etc/supervisord.conf
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -subj '/C=AB/ST=CD/L=EF/O=21/CN=wquinoa' \
	-keyout /etc/ssl/certs/localhost.key -out /etc/ssl/certs/localhost.crt
RUN echo -e "ssh_admin\nssh_admin" | adduser ssh_user

RUN mkdir -p /run/nginx 
COPY ./src/nginx-start.sh /tmp/nginx-start.sh
RUN chmod u+x /tmp/nginx-start.sh

EXPOSE 80 443 22
ENTRYPOINT ["/tmp/nginx-start.sh"]