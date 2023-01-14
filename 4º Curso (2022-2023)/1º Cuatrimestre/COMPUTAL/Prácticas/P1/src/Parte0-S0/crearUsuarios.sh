#!/bin/bash

for i in {01..20}
do
	newUser=$(echo usuBD$i)
	userPasswd=$(echo $newUser$RANDOM)
	useradd $newUser -p userPasswd
	echo usuario $newUser:$userPasswd >> lista20usuarios.txt
done
