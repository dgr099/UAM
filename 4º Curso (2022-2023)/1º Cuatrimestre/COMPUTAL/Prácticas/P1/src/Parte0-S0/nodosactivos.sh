#!/bin/bash

numNodes=$(rocks run host "hostname" | wc -l)
noActiveNodes=$(qstat -f | grep "compute" | grep au | wc -l)
let activeNodes=$numNodes-$noActiveNodes

echo "Numero de nodos = $numNodes"
echo "Numero de nodos no activos = $noActiveNodes"
echo "Porcentaje de nodos activos = $activeNodes/$numNodes"
echo
echo "Listado de Nodos"

for node in $(rocks run host "hostname" | cut -d. -f1)
do
	ip=$(rocks run host $node "hostname -i")
	active=$(qstat -f | grep $node | awk '{if ($6=="au") {print "NO ACTIVO"} else {print "ACTIVO"}}')
	echo -e $node'\t'$ip'\t'$active
done
