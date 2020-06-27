# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/27 21:57:56 by wquinoa           #+#    #+#              #
#    Updated: 2020/06/27 22:04:39 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

service nginx start
service php7.3-fpm start
service mysql start

sleep infinity;