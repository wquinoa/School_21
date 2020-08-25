#/bin/sh

minikube start --vm-driver=virtualbox --disk-size 5000MB
minikube addons enable metallb
minikube addons enable dashboard
eval $(minikube docker-env);    
docker build -t nginx .
kubectl create -f ../nginx-deployment.yaml
kubectl apply -f ../metallb.yaml