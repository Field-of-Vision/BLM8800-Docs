1.TX
 Program lmacfw_flash_5g100_tx_8000000.bin into 0x8000000. Then 'g 8000000'.
 After started up, 'settx 1'.

2.RX
0) Modify plf/aic8800/config/maps/armgcc_4_8/map_cm4_wifi.txt DRAM's ORIGIN,
    DRAM (rwx)      : ORIGIN = 0x00100000, LENGTH = (300K - 0x100) 
1) Build 'target_wifi_csi/build_wifi_csi_case.sh', and Program the bin 'host_wb_wifi_csi.bin' into 0x8000000,
2) Program lmacfw_flash_5g100_rx_8100000.bin into 0x8100000,
3) After 1) & 2) Done, 'g 8000000'.

The API to get csi info is 'aic_fhost_rx_csi' in file 'fhost_wifi_csi.c'
