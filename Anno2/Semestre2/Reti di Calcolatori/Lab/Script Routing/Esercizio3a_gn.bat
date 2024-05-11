
VBoxManage.exe snapshot DebianSenzaInterfaccia delete Snapshot
VBoxManage.exe snapshot DebianSenzaInterfaccia take Snapshot

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name R1 --options link --register
VBoxManage.exe modifyvm R1 --memory 1024 --nic1 intnet --intnet1 lan01 --nic2 intnet --intnet2 lan02 --nic3 none --nic4 none
VBoxManage.exe startvm R1

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name R2 --options link --register
VBoxManage.exe modifyvm R2 --memory 1024 --nic1 intnet --intnet1 lan02 --nic2 intnet --intnet2 lan03 --nic3 intnet --intnet3 lan05 --nic4 none
VBoxManage.exe startvm R2

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name R3 --options link --register
VBoxManage.exe modifyvm R3 --memory 1024 --nic1 intnet --intnet1 lan03 --nic2 intnet --intnet2 lan04 --nic3 none --nic4 none
VBoxManage.exe startvm R3

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name R4 --options link --register
VBoxManage.exe modifyvm R4 --memory 1024 --nic1 intnet --intnet1 lan05 --nic2 intnet --intnet2 lan06 --nic3 none --nic4 none
VBoxManage.exe startvm R4

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name A --options link --register
VBoxManage.exe modifyvm A --memory 1024 --nic1 intnet --intnet1 lan01 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm A

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name B --options link --register
VBoxManage.exe modifyvm B --memory 1024 --nic1 intnet --intnet1 lan02 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm B

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name C --options link --register
VBoxManage.exe modifyvm C --memory 1024 --nic1 intnet --intnet1 lan03 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm C

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name D --options link --register
VBoxManage.exe modifyvm D --memory 1024 --nic1 intnet --intnet1 lan04 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm D

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name E --options link --register
VBoxManage.exe modifyvm E --memory 1024 --nic1 intnet --intnet1 lan05 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm E

VBoxManage.exe clonevm DebianSenzaInterfaccia --snapshot Snapshot --name F --options link --register
VBoxManage.exe modifyvm F --memory 1024 --nic1 intnet --intnet1 lan06 --nic2 none --nic3 none --nic4 none
VBoxManage.exe startvm F

