#!/sbin/static/busybox sh
export PATH=/sbin/static:/sbin

# Scan for LVM physical volumes and set up volume groups
/sbin/lvm vgscan --mknodes --ignorelockingfailure
# Activate LVM logical volumes in found volume groups
/sbin/lvm vgchange -aly --ignorelockingfailure

busybox mkdir /dev/partitions

if [ -d /dev/lvpool ]
then
	busybox ln -s /dev/lvpool/system /dev/partitions/system
	busybox ln -s /dev/lvpool/cache /dev/partitions/cache
	busybox ln -s /dev/lvpool/userdata /dev/partitions/userdata
	busybox ln -s /dev/lvpool/media /dev/partitions/media

	# Update fstab
	busybox cp /fstab.qcom /fstab.qcom.std
	busybox mv /fstab.qcom.lvm /fstab.qcom

	# In recovery, need to replace recovery fstab
	if [ -f /etc/recovery.fstab ]
	then
		busybox cp /fstab.qcom /etc/recovery.fstab
	fi
	exit
fi

# LVM volume not found, symlink standard partitions
busybox ln -s /dev/block/mmcblk0p12 /dev/partitions/system
busybox ln -s /dev/block/mmcblk0p6 /dev/partitions/cache
busybox ln -s /dev/block/mmcblk0p13 /dev/partitions/userdata
busybox ln -s /dev/block/mmcblk0p14 /dev/partitions/media
