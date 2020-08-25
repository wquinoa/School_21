#!/bin/sh

rc default
rc-service sshd start
ssh-keygen -A
rc-service sshd stop
/usr/bin/supervisord -c /etc/supervisord.conf