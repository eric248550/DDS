#!/bin/sh
cd $HOME;
# Identifying Modes : LAN or WAN
[  -z "$MODE" ] && echo "No Specific Mode Defined : Defaulting to LAN";

case "$MODE" in
 WAN) 	
	cp ./dispenser/QOS/USER_QOS_PROFILES_WAN.xml ./dispenser/USER_QOS_PROFILES.xml
	echo 'Updating qos to NDDS_TRANSPORT_CLASSID_TCPV4_WAN (Using Publisher Public IP)'
	[  -z "$PUB_PUBLICIP" ] && echo "Error : Publisher Peer is invalid" && exit 1 || echo 'Updating publisher public ip...{'$PUB_PUBLICIP'}';
	[  -z "$PUB_BINDPORT" ] && echo "Error : Publisher Bind Port is invalid" && exit 1  || echo 'Updating publisher bindport...{'$PUB_BINDPORT'}';
	[  -z "$SUB_PEER" ] && echo "Error : Subscriber Peer is invalid" && exit 1  || echo 'Updating subscriber peer...{'$SUB_PEER'}';
	# PUBLISHER PUBLIC IP:PORT
	sed -i '55s%\(<value>\).*\(<\/value>\)%<value>'"$PUB_PUBLICIP"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	# PUBLISHER BIND PORT
	sed -i '59s%\(<value>\).*\(<\/value>\)%<value>'"$PUB_BINDPORT"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	# SUBSCRIBER PEER
	sed -i '69s%\(<element>\).*\(<\/element>\)%<element>'"$SUB_PEER"'<\/element>%' ./dispenser/USER_QOS_PROFILES.xml;
	;;
 WAN_REV)
	cp ./dispenser/QOS/USER_QOS_PROFILES_WAN_REV.xml ./dispenser/USER_QOS_PROFILES.xml
	echo 'Updating qos to NDDS_TRANSPORT_CLASSID_TCPV4_WAN on Reverse Mode (Using Subscriber Public IP)'
 	# PUBLISHER PEER
	sed -i '53s%\(<element>\).*\(<\/element>\)%<element>'"$PUB_PEER"'<\/element>%' ./dispenser/USER_QOS_PROFILES.xml;
	# SUBSCRIBER PUBLIC IP:PORT
	sed -i '72s%\(<value>\).*\(<\/value>\)%<value>'"$SUB_PUBLICIP"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	# SUBSCRIBER BIND PORT
	sed -i '76s%\(<value>\).*\(<\/value>\)%<value>'"$SUB_BINDPORT"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	;;
 *) 
	# LAN MODE:
	cp ./dispenser/QOS/USER_QOS_PROFILES.xml ./dispenser/USER_QOS_PROFILES.xml
	echo 'Defaulting qos to NDDS_TRANSPORT_CLASSID_TCPV4_LAN'
	# Checking Dependencies Variable
	[  -z "$PUB_PEER" ] && echo "Error : Publisher Peer is invalid" && exit 1 || echo 'Updating publisher peer...{'$PUB_PEER'}';
	[  -z "$PUB_BINDPORT" ] && echo "Error : Publisher Bind Port is invalid" && exit 1  || echo 'Updating publisher bindport...{'$PUB_BINDPORT'}';
	[  -z "$SUB_PEER" ] && echo "Error : Subscriber Peer is invalid" && exit 1  || echo 'Updating subscriber peer...{'$SUB_PEER'}';
	[  -z "$SUB_BINDPORT" ] && echo "Error : Subscriber Bind Port is invalid" && exit 1  || echo 'Updating subscriber bindport...{'$SUB_BINDPORT'}';
 	# PUBLISHER PEER
	sed -i '53s%\(<element>\).*\(<\/element>\)%<element>'"$PUB_PEER"'<\/element>%' ./dispenser/USER_QOS_PROFILES.xml;
	# PUBLISHER BIND PORT
	sed -i '60s%\(<value>\).*\(<\/value>\)%<value>'"$PUB_BINDPORT"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	# SUBSCRIBER PEER
	sed -i '70s%\(<element>\).*\(<\/element>\)%<element>'"$SUB_PEER"'<\/element>%' ./dispenser/USER_QOS_PROFILES.xml;
	# SUBSCRIBER BIND PORT
	sed -i '77s%\(<value>\).*\(<\/value>\)%<value>'"$SUB_BINDPORT"'<\/value>%' ./dispenser/USER_QOS_PROFILES.xml;
	;;
esac

cd $HOME/dispenser;
make -f makefile_water_x64Linux3gcc5.4.0;

[  -z "$ROLE" ] && echo 'No Specific Role Defined : Defaulting to Subscriber';

case "$ROLE" in
 PUBLISHER) 
			./objs/x64Linux3gcc5.4.0/water_publisher ;;
   		 *) 
			[  -z "$MONGO_ADDRESS" ] && echo 'No Specific MongoDB Address Given' && exit 1;
			./objs/x64Linux3gcc5.4.0/water_subscriber ;;
esac