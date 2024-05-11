# tre nodi A----R1----B


VBoxManage.exe guestcontrol A run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ A
VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.1.10/24 dev enp0s3 
VBoxManage.exe guestcontrol A run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.1.1

VBoxManage.exe guestcontrol B run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ B
VBoxManage.exe guestcontrol B run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.2.10/24 dev enp0s3 
VBoxManage.exe guestcontrol B run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.2.2

VBoxManage.exe guestcontrol C run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ C
VBoxManage.exe guestcontrol C run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.3.10/24 dev enp0s3 
VBoxManage.exe guestcontrol C run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.3.2

VBoxManage.exe guestcontrol D run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ D
VBoxManage.exe guestcontrol D run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.4.10/24 dev enp0s3 
VBoxManage.exe guestcontrol D run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.4.3

VBoxManage.exe guestcontrol E run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ E
VBoxManage.exe guestcontrol E run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.5.10/24 dev enp0s3 
VBoxManage.exe guestcontrol E run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.5.2

VBoxManage.exe guestcontrol F run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ F
VBoxManage.exe guestcontrol F run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.6.10/24 dev enp0s3 
VBoxManage.exe guestcontrol F run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.6.4



VBoxManage.exe guestcontrol R1 run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ R1
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s8 up 
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.1.1/24 dev enp0s3
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.2.1/24 dev enp0s8 
VBoxManage.exe guestcontrol R1 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.2.2
VBoxManage.exe guestcontrol R1 run --exe /usr/sbin/sysctl --username root --password root  --wait-stdout -- sysctl/ -w net.ipv4.ip_forward=1


VBoxManage.exe guestcontrol R2 run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ R2
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s8 up 
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s9 up 
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.2.2/24 dev enp0s3
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.3.2/24 dev enp0s8 
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.5.2/24 dev enp0s9 
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add 1.1.1.0/24 via 1.1.2.1
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add 1.1.4.0/24 via 1.1.3.3
VBoxManage.exe guestcontrol R2 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add 1.1.6.0/24 via 1.1.5.4
VBoxManage.exe guestcontrol R2 run --exe /usr/sbin/sysctl --username root --password root  --wait-stdout -- sysctl/ -w net.ipv4.ip_forward=1

VBoxManage.exe guestcontrol R3 run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ R3
VBoxManage.exe guestcontrol R3 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s8 up 
VBoxManage.exe guestcontrol R3 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.3.3/24 dev enp0s3
VBoxManage.exe guestcontrol R3 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.4.3/24 dev enp0s8 
VBoxManage.exe guestcontrol R3 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.3.2
VBoxManage.exe guestcontrol R3 run --exe /usr/sbin/sysctl --username root --password root  --wait-stdout -- sysctl/ -w net.ipv4.ip_forward=1

VBoxManage.exe guestcontrol R4 run --exe /usr/bin/hostname --username root --password root --wait-stdout -- hostname/ R4
VBoxManage.exe guestcontrol R4 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ link set enp0s8 up 
VBoxManage.exe guestcontrol R4 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.5.4/24 dev enp0s3
VBoxManage.exe guestcontrol R4 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ addr add 1.1.6.4/24 dev enp0s8 
VBoxManage.exe guestcontrol R4 run --exe /sbin/ip --username root --password root  --wait-stdout -- ip/ route add default via 1.1.5.2
VBoxManage.exe guestcontrol R4 run --exe /usr/sbin/sysctl --username root --password root  --wait-stdout -- sysctl/ -w net.ipv4.ip_forward=1



echo "Test:ping A -> D"
VBoxManage.exe guestcontrol A run --exe /bin/ping --username root --password root  --wait-stdout -- ping/ -c 4 1.1.4.10

echo "Test:ping B -> F"
VBoxManage.exe guestcontrol B run --exe /bin/ping --username root --password root  --wait-stdout -- ping/ -c 4 1.1.6.10

