sudo dd iflag=dsync oflag=dsync if=tiny210-uboot.bin of=/dev/sdb seek=1
# 台式机上 烧写 u-boot
# seek=1 跳过0，因为存厂商信息
# dsync 同步
