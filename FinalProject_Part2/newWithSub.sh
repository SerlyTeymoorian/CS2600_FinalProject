#!/bin/bash

#to keep track of the number iterations 
counter=1
counter2=1
printing="1"
printing2="2"
printing3="3"
printing4="4"

while true; do
	if [ $(($counter%3)) -eq 0 ]
	then
		echo "ALL LIGHTS ARE ON"	
		mosquitto_pub -h 192.168.1.2 -t esp32/test1 -m $printing4
		counter=$(($counter+1))
		#sleep 1
		mosquitto_sub -h 192.168.1.2 -t pub/message -C 2 > receivedCommands.txt
	elif [ $(($counter%2)) -ne 0 ]
	then
		echo "LED GREEN IS ON"	
		mosquitto_pub -h 192.168.1.2 -t esp32/test1 -m $printing
		counter=$(($counter+1))
		#sleep 1
		mosquitto_sub -h 192.168.1.2 -t pub/message -C 2 > receivedCommands.txt	
	elif [ $(($counter%2)) -eq 0 ]
	then 
		echo "LED RED IS ON"
		mosquitto_pub -h 192.168.1.2 -t esp32/test1 -m $printing2
		#sleep 1
		mosquitto_sub -h 192.168.1.2 -t pub/message -C 1 > receivedCommands.txt
		counter=$(($counter+1))
	fi
	
	#sleep 5s

	mosquitto_pub -h 192.168.1.2 -t esp32/test1 -m $printing3
	#sleep 1
	mosquitto_sub -h 192.168.1.2 -t pub/message -C 1 > receivedCommands.txt
	counter2=$(($counter2+1))
done

