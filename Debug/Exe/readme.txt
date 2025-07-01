远程地址：git@github.com:Git-Wyb/RSSI_IDCheck_TEST.git

2025.06.04    OK05-1_LoginCheck001.hex
检测OK05-1无线登录模式

2025.06.04    OK05-1_LoginCheck002.hex
添加按键切换ID检查模式和登录检查模式，按键切换RSSI有效值

2025.06.05    TEST_LoginCheck_V003.hex
默认RSSI设定-50dbm

2025.06.06    TEST_LoginCheck_V004.hex
添加测试模式

2025.06.13   TEST_LoginCheck_V005.hex
改动：登录显示改为日文，进入登录模式后，没有受信，80超时退出。退出登录模式后，5秒清除。
现在软件有4个模式：
①右下角开关向下拨再上电：检测登录状态模式 "トウロクケンサ"。
②右下角开关向上拨再上电：测试模式，检测无线特性。
③右下角开关向下拨且按住SW2上电：ID检查模式，频率429.350、429.550.
④右下角开关向上拨且按住SW2上电：ID检查模式，频率426.075.

2025.06.13   TEST_LoginCheck_V006.hex
未进入登录模式显示“LOGIN CHECKER”，进入登录模式显示“トウロクモードチュウ”，退出登录模式显示“トウロクシュウリョウ”。

2025.03.16  TEST_LoginCheck_V007.hex
设定值rssi保存至eeprom

2025.06.20  QL-TEST_LoginCheck_V008.hex
青柳内部使用，ID检查模式可以设置RSSI有效值。

2025.07.01  QL-TEST_LoginCheck_V009.hex
ID检查模式显示429接收数据


