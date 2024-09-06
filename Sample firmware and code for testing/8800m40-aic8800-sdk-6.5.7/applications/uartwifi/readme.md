## **AT编译**  ##
	修改FHOST_APP=uartwifi 加上 CONSOLE=off ATCMD=on

## **AT:** 测试AT指令  ##
###  命令：  ###
	AT
###  响应  ###
	+OK
## **AT+ECHO:** AT回显使能/关闭  ##
###  命令：  ###
	AT+ECHO=1
###  响应  ###
	+OK
## **AT+SLPLVL:** 获取/设置系统SLEEP级别  ##
###  命令：  ###
	AT+SLPLVL=？
###  响应  ###
	1
	+OK
###  命令：值含义参考 POWER_MODE_LEVEL_T  ###
	AT+SLPLVL=2
###  响应  ###
	+OK
## **AT+USRWUSRC:** 设置唤醒源  ##
###  命令：值含义参考 WAKEUP_SOURCE_T  ###
	AT+USRWUSRC=2
###  响应  ###
	+OK
## **AT+USRSLP:** 用户设置休眠  ##
###  命令：###
	AT+USRSLP
###  响应  ###
	+OK
## **AT+WSCAN:** Wi-Fi搜索指定vif（一般使用0）  ##
###  命令：  ###
	AT+WSCAN=0
###  响应  ###
	AT+WSCAN=0
	vif_name AIC_CC69
	_scanu_start:0,0,0
	_scanu_confirm:0,0,0
	Got 16 scan results
	(-30 dBm) CH=  1 BSSID=04:d5:c4:07:f8:a8 SSID=ASUS-1
	(-34 dBm) CH=  1 BSSID=28:80:78:46:5e:9c SSID=BB_24G
	(-45 dBm) CH=  1 BSSID=fc:01:7c:9c:d2:37 SSID=T-1
	(-36 dBm) CH=  4 BSSID=0c:83:9a:f3:c7:dc SSID=
	(-39 dBm) CH=  4 BSSID=0c:83:9a:f3:cb:d8 SSID=TP-2
	(-52 dBm) CH=  6 BSSID=f4:83:cd:aa:98:25 SSID=OFFICE-4G
	(-39 dBm) CH=  4 BSSID=0c:89:9a:f3:c7:dd SSID=
	(-41 dBm) CH=  6 BSSID=c8:f4:e6:05:7a:74 SSID=Meetingroom
	(-31 dBm) CH=  6 BSSID=bc:57:fc:41:1f:db SSID=MERCURY-1
	(-52 dBm) CH=  6 BSSID=7c:a1:67:c3:61:c4 SSID=TP-3
	(-53 dBm) CH=  8 BSSID=c8:ee:a6:5c:5f:63 SSID=API_5F6
	(-56 dBm) CH= 11 BSSID=fc:d7:33:e7:d4:96 SSID=109
	(-41 dBm) CH= 11 BSSID=2c:61:04:2f:f6:28 SSID=360
	(-40 dBm) CH= 11 BSSID=26:40:bb:a4:38:e1 SSID=DESKTOP-1
	(-32 dBm) CH= 11 BSSID=2e:96:e5:7d:ce:59 SSID=glass
	(-35 dBm) CH= 13 BSSID=d0:17:b4:41:d7:9c SSID=TP-1
	+OK
## **AT+WMAC:** 获取/设置MAC address  ##
###  命令：获取当前MAC地址  ###
	AT+WMAC=？
###  响应  ###
	AT+WMAC=?
	88:00:33:77:69:cc
	+OK
###  命令：设置MAC地址为88:00:33:77:69::67  ###
	AT+WMAC=880033776967
###  响应  ###
	AT+WMAC=880033776967
	Wifi sta info not written before（若之前没有在flash保存）
	+OK
## **AT+WFIXIP:**  使能/禁用固定IP地址(支持保存至flash，该命令只在sta未连接时有效)  ##
###  命令：1表示使能FIXIP功能，后面分别为IP、子网掩码以及网关  ###
	AT+WFIXIP=1,192.168.1.100,255.255.255.0,192.168.1.1
###  响应  ###
	AT+WFIXIP=1,192.168.1.100,255.255.255.0,192.168.1.1
	+OK
###  命令：0表示禁用FIXIP功能  ###
	AT+WFIXIP=0
###  响应  ###
	AT+WFIXIP=0
	+OK
## **AT+RESTORE:** 清除flash信息  ##
###  命令  ###
	AT+RESTORE
###  响应  ###
	+OK
## **AT+HEAP:** 显示heap信息  ##
###  命令  ###
	AT+HEAP
###  响应  ###
	+OK
## **AT+TXPWR:** 设置TX power（范围-10 ~ 22dBm）  ##
###  命令  ###
	AT+TXPWR=0,22
###  响应  ###
	+OK
## **AT+WAPSTART:** 启动softAP  ##
###  命令: 0:2.4G/1:5G, SSID:AIC_24G, pwd:12345678  ###
	AT+WAPSTART=0,AIC_24G,12345678
###  响应  ###
	+OK
## **AT+WAPSTOP:** 关闭softAP  ##
###  命令  ###
	AT+WAPSTOP
###  响应  ###
	AT+WAPSTOP
	WPA Stop AP 0
	_ps_enable_cfm:800000
	_ps_upm_enter:0,94
	wpa_supplicant_main end
	WPA enter FHOST_WPA_STATE_STOPPED
	+OK
## **AT+WAPDHCPS:** 设置DHCPS参数  ##
###  命令:1:使能，2：lease time（小时），10：dhcps start，20：dhcps end  ###
	AT+WAPDHCPS=1,2,10,20
###  响应  ###
	+OK
###  命令:0:关闭 ###
	AT+WAPDHCPS=0
###  响应  ###
	+OK
## **AT+WSTACNCT:** STA连接指定路由器  ##
###  命令:1:存flash，ssi，pwd ###
	AT+WSTACNCT=1,Xiaomi_66D0,12345678
###  响应  ###
	Connect Wi-Fi: _ASUS_A8, 1qaz2wsx
	vif_name AIC_CC69
	WPA task started for interface {FVIF-0}
	WPA network 0: created and configured
	_scanu_start:1,0,0
	_scanu_confirm:1,0,0
	_scanu_start:1,0,0
	_scanu_confirm:1,0,0
	_ps_disable_cfm:800000
	_sm_auth_send
	_tx cfm:5,80800000
	_auth_handler:0
	_sm_assoc_req_send
	_tx cfm:7,80800000
	_assoc_rsp_handler:0
	_vif state active:1,2,0,0
	_ps_upm_enter:0,94
	_connect:1,0,aid=0
	_handle addba_req:tid=0
	_add ptk:1
	_add gtk:1
	WPA enter FHOST_WPA_STATE_CONNECTED
	_ps_enable_cfm:800000
	WPA network 0: connected
	Wifi sta info not written before
	_handle addba_rsp:tid=0, idx=5
	DHCP completed: ip=192.168.50.107 gw=192.168.50.1
	+OK
## **AT+WSDISCNCT:** STA断开连接  ##
###  命令: ###
	AT+WSDISCNCT
###  响应  ###
	_disconnct:1,3
	_delete reources
	_vif state inactive:0,1
	_ps_upm_exit
	Disconnect d404:7c4:a8f8
	WPA network 0: disconnected
	wpa_supplicant_main end
	WPA enter FHOST_WPA_STATE_STOPPED
	+OK
## **AT+WSETNAME:** 设置STA在host内显示的名称,需要在connect之后使用  ##
###  命令: ###
	AT+WSETNAME=aic_test
###  响应  ###
	+OK
## **AT+WSMRTCONF:** 启动smartconfig配网  ##
###  命令: ###
	AT+WSMRTCONF
###  响应  ###
	+OK
	_scanu_confirm:0,0,0
	Scan result 6
	State: Channel found
	State: Unhidden SSID/password found
	vif_name AIC_E569
	 fhost_smart_get_ssid_pswd, 2412
	_scanu_start:2,0,0
	_scanu_confirm:2,0,0
	_scanu_start:2,0,0
	_scanu_confirm:2,0,0
	SSID(_ASUS_A8), BSSID:(04:d4:c4:07:f8:a8)
	Password:1qaz2wsx
	State: Smartconfig Done.
	State: Smartconfig connect
	WPA task started for interface {FVIF-0}
	WPA network 0: created and configured
	_scanu_start:2,0,0
	_scanu_confirm:2,0,0
	_scanu_start:2,1,0
	_scanu_confirm:2,1,0
	_ps_disable_cfm:800000
	_sm_auth_send
	_tx cfm:5,80800000
	_auth_handler:0
	_sm_assoc_req_send
	_tx cfm:7,80800000
	_assoc_rsp_handler:0
	_vif state active:0,3,0,0
	_ps_upm_enter:0,94
	_connect:2,0,aid=0
	_add ptk:0
	_add gtk:2
	WPA enter FHOST_WPA_STATE_CONNECTED
	WPA network 0: connected
	_ps_enable_cfm:800000
	_curr=0, bss=4
	_handle addba_req:tid=0
	_handle addba_req:tid=0
	Wifi sta info not written before
	DHCP completed: ip=192.168.50.132 gw=192.168.50.1
	State: Smartconfig over
## **AT+WSSTOPSC:** 关闭smartconfig配网  ##
###  命令: ###
	AT+WSSTOPSC
###  响应  ###
	+OK
	_disconnct:2,3
	_delete reources
	_vif state inactive:0,1
	_ps_upm_exit
	Disconnect d404:7c4:a8f8
	wpa_supplicant_main end
	WPA enter FHOST_WPA_STATE_STOPPED
## **AT+WPING:** ping  ##
###  命令: 目标ip，执行次数，发送时间间隔（单位s），包长（max1460），1：回显/0不回显###
	AT+WPING=192.168.50.1,10,1,100,1
###  响应  ###
	ping_params 192.168.50.1 -d 10 -r 1 -s 100
	Send ping ID 0
	+OK
	100 bytes from: 192.168.50.1: icmp_req=1 ttl=255 time=7019 us
	100 bytes from: 192.168.50.1: icmp_req=2 ttl=255 time=1602 us
	100 bytes from: 192.168.50.1: icmp_req=3 ttl=255 time=5890 us
	100 bytes from: 192.168.50.1: icmp_req=4 ttl=255 time=1480 us
	100 bytes from: 192.168.50.1: icmp_req=5 ttl=255 time=1449 us
	100 bytes from: 192.168.50.1: icmp_req=6 ttl=255 time=1495 us
	100 bytes from: 192.168.50.1: icmp_req=7 ttl=255 time=11627 us
	100 bytes from: 192.168.50.1: icmp_req=8 ttl=255 time=2488 us
	100 bytes from: 192.168.50.1: icmp_req=9 ttl=255 time=1480 us
	100 bytes from: 192.168.50.1: icmp_req=10 ttl=255 time=2762 us
	--- 192.168.50.1 ping statistics ---
	10 packets transmitted, 10 received, 0% packet loss, time 3729 ms
	1000 bytes transmitted, 1000 bytes received
## **AT+NDNS:** DNS  ##
###  命令: ###
	AT+NDNS="www.baidu.com"
###  响应  ###
	  www.baidu.com <-> 110.242.68.4
	+OK
## **AT+WSWPS:** WPS  ##
###  命令: ###
	AT+WSWPS
###  响应  ###
	Wps_context 348
	WPA task started for interface {FVIF-0}
	_scanu_start:0,0,0
	_scanu_confirm:0,0,0
	...
	_connect:0,0,aid=0
	_curr=0, bss=4
	_add ptk:1
	_add gtk:0
	WPA enter FHOST_WPA_STATE_CONNECTED
	_ps_enable_cfm:800000
	_handle addba_req:tid=0
	Wifi sta info not written before
	_handle addba_rsp:tid=0, idx=5
	DHCP completed: ip=192.168.50.123 gw=192.168.50.1
	+OK
## **AT+NCRECLNT:** 创建TCP/UDP client  ##
###  命令: 类型，目标IP，目标端口，本地端口 ###
	AT+NCRECLNT=UDP,192.168.50.100,4000,4002
###  响应  ###
	+OK
## **AT+NCRECLNT:** 创建TCP/UDP client  ##
###  命令: 类型，目标IP，目标端口，本地端口 ###
	AT+NCRECLNT=UDP,192.168.50.100,4000,4002
###  响应  ###
	+OK
## **AT+NSTOP:** 断开TCP/UDP 连接  ##
###  命令: 连接号(0~3） ###
	AT+NSTOP=0
###  响应  ###
	+OK
## **AT+NSEND:** 通过TCP/UDP 连接发送数据  ##
###  命令: 连接号(0~3),数据长度 ###
	AT+NSEND=0,1460
###  响应  ###
	UDP send size 1460
	+OK
## **AT+WMDNS:**  ##
###  命令:打开,host name,service name,port  ###
	AT+WMDNS=1,aicaic,_iot,8080
###  响应  ###
	+OK
## **AT+IPERF:**  ##
###  命令:iperf udp client(iperf -u -c 192.168.3.45 -t 99 -b 10M -i 1)  ###
	AT+WIPERF=U,C,192.168.3.45,99,10M,1
###  响应  ###
	+OK
	------------------------------------------------------------
	Client connecting to 192.168.3.45, UDP port 5001
	Sending 1470 byte datagrams
	------------------------------------------------------------
	[ ID] Interval       Transfer     Bandwidth
	[  0]  0.0- 1.0 sec  1.23 MByte  10.4 Mbits/sec
	[  0]  1.0- 2.0 sec  1.23 MByte  10.4 Mbits/sec
	...
	Server report:
	[ ID]  Interval      Transfer     Bandwidth       Jitter   Lost/Total Datagrams
	[  0]  0.0-74.8 sec  91.8 MByte  10.3 Mbits/sec  0.277 ms   21125/86600 (24.4%)
###  命令:iperf udp server(iperf -u -s -i 1)  ###
	AT+WIPERF=U,S,1
###  响应  ###
	+OK
	------------------------------------------------------------
	Server listening on UDP port 5001
	IP address : 192.168.3.77
	------------------------------------------------------------
###  命令:iperf tcp server(iperf -s -i 1)  ###
	AT+WIPERF=T,S,1
###  响应  ###
	+OK
	------------------------------------------------------------
	Server listening on TCP port 5001
	IP address : 192.168.3.77
	------------------------------------------------------------
###  命令:iperf tcp client(iperf -c 192.168.3.45 -t 99 -i 1)  ###
	AT+WIPERF=T,C,192.168.3.45,99,1
###  响应  ###
	+OK
	_handle addba_req:tid=7
	[ ID] Interval       Transfer     Bandwidth
	[  0]  0.0- 1.0 sec  4.41 MByte  36.9 Mbits/sec
	[  0]  1.0- 2.0 sec  4.95 MByte  41.6 Mbits/sec
###  命令:iperf stop  ###
	AT+WIPERF=STOP
###  响应  ###
	+OK

