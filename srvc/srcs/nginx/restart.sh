#!/bin/sh

docker build . -t nginx
kubectl delete deploy nginx  
kubectl apply -f /Users/user/Projects/21_school/root/ft_services/srcs/nginx-deployment.yaml
sleep 2
kubectl get pods