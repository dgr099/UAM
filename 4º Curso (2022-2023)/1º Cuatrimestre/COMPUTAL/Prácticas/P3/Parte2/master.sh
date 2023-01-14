#!/bin/bash

unset SPARK_MASTER_PORT

echo "$(hostname -i) spark-master" >> /etc/hosts

/opt/spark-3.3.0-bin-hadoop3/bin/spark-class org.apache.spark.deploy.master.Master --ip spark-master --port 7077 --webui-port 8080
