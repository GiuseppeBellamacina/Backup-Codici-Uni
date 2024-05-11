# tre nodi A----R1----B

echo "Configurazione nodo A"
VBoxManage.exe guestcontrol A run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ A
VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 10.0.1.1/24 dev enp0s3 
VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 10.0.1.2
echo "--------- enp0s3"
VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr show dev enp0s3

VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route
echo "--------- route table"
echo ""
echo "Configurazione nodo B"

VBoxManage.exe guestcontrol B run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ B
VBoxManage.exe guestcontrol B run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 10.0.2.1/24 dev enp0s3 
VBoxManage.exe guestcontrol B run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 10.0.2.2
echo " "
echo "Configurazione router R1"

VBoxManage.exe guestcontrol R1 run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ R1
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s8 up 
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 10.0.1.2/24 dev enp0s3
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 10.0.2.2/24 dev enp0s8 
VBoxManage.exe guestcontrol R1 run --exe /usr/sbin/sysctl --username root --password root  --wait-stdout -- sysctl/ -w net.ipv4.ip_forward=1 

echo " "
echo "Test:ping A -> B"

VBoxManage.exe guestcontrol A run --exe /bin/ping --username root --password root  --wait-stdout -- ping/ -c 4 10.0.2.1
