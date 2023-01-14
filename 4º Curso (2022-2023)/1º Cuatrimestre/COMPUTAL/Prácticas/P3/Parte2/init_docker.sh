#!/bin/bash

echo "Descargando minikube..."
curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
sudo install minikube-linux-amd64 /usr/local/bin/minikube

echo "Arrancar minikube con docker..."
sudo usermod -aG docker $USER
rm /tmp/juju-*; sudo minikube start --driver=docker --container-runtime=containerd
chmod +x minikube
sudo chown -R $USER /$HOME/.kube
alias kubectl="minikube kubectl --"

echo "Haciendo buildings..."
docker build -f base_dockerfile -t base_dockerfile .
docker build -f master_dockerfile -t master_dockerfile .
docker build -f worker_dockerfile -t worker_dockerfile .

echo "Haciendo runnings..."
# -i Keep STDIN open even if not attached (interactive)
# -t Allocate a pseudo-TTY
docker run -it --name spark-master master_dockerfile
docker run -it --name spark-worker worker_dockerfile