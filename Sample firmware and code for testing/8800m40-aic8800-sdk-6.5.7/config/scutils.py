########################################################################################
#
# @file scutils.py
#
# @brief Utility library for all SConscripts
#
# Copyright (C) RivieraWaves 2009-2015
#
#########################################################################################

import sys
import os
import os.path
from os.path import join
import datetime
import subprocess
import binascii

#-----------------------------------------------------------
# Scons include + utility function
#-----------------------------------------------------------

from SCons.Script import *

def ext_path(scons_path):
    """Convert an absolute SCons path (with eventual #)
       to an normal path for external tools"""

    if scons_path[0] == '#':
        if len(scons_path) > 1 and scons_path[1] == '/':
            scons_path = scons_path[2:]
        else:
            scons_path = scons_path[1:]

        scons_path = join(Dir('#').abspath, scons_path)
    return os.path.normpath(scons_path)

def diff_path(path_base, path_ext):
    """Get the relative path from path_ext to path_base.
       work only if ext is included in base"""

    diff = ''
    path_base   = os.path.abspath(ext_path(path_base))
    path_ext    = os.path.abspath(ext_path(path_ext))

    while path_base != path_ext:
        path_ext, path_last = os.path.split(path_ext)
        if not path_last: raise  # not included!
        diff     = join(path_last, diff)

    return os.path.normpath(diff)

#def cyg2win(path):
#    if path[:10] == '/cygdrive/':
#        path = path[10] + ':' + path[11:]
#    elif path[0] == '/':
#        print "ERROR ", path
#    else:
#        print "relative ", path
#    return path.replace('/','\\')


#-----------------------------------------------------------
# Local includes
#-----------------------------------------------------------
def rvds_find():
    rvds = 'rvds41'
    try:
        rvds_path = os.environ['ARMCC41BIN']
    except KeyError:
        rvds = 'rvds31'
        try:
            rvds_path = os.environ['RVCT31BIN']
        except KeyError:
            print "Neither RVDS 3.1 nor 4.1 is installed on this computer"
            raise
    # First search in the SCons path and then the OS path:
    return rvds

def env_create(arch):
    #-----------------------------------------------------------
    # Build tool and default settings
    #-----------------------------------------------------------

    assert(arch in ('cortex', 'risc-v'))

    # Get build tool from command line or default
    defaulttool = ARGUMENTS.get('BT'    ,'armgcc_4_8')
    buildtool   = ARGUMENTS.get('BT_ARM', defaulttool).lower()
    optim       = ARGUMENTS.get('O'     , '2')
    build_dir   = ARGUMENTS.get('BUILD_DIR', '#/../build')

    # sanity checks
    assert(buildtool in ('rvds', 'gnuarm','armgcc_4_8','armgcc','armcc_5'))

    # create environment
    if buildtool == 'rvds':
        tool = scutils.rvds_find()
        env = Environment(tools = [tool])
    elif buildtool == 'armcc_5':
        env = Environment(tools = ['armcc_5'], ENV = {'PATH':os.environ['PATH']})
    elif buildtool == 'armgcc_4_8':
        env = Environment(tools = ['armgcc_4_8'], ENV = {'PATH':os.environ['PATH']})
    elif buildtool == 'armgcc':
        env = Environment(tools = ['armgcc'], ENV = {'PATH':os.environ['PATH']})
    else:
        env = Environment(tools = ['gnuarm'], ENV = {'PATH':os.environ['PATH']})

    # save arch and buildtool in environment
    env['ARCH']      = arch
    env['BUILDTOOL'] = buildtool
    # optimization level: default depends on ARCH
    env['OPTIM']     = optim
    # build directory
    env['BUILD_DIR'] = build_dir

    return env

def env_init():
    """
    #-----------------------------------------------------------
    # Default initialization for environments
    #-----------------------------------------------------------
    """

    # Buildtool
    env = env_create( ARGUMENTS.get('ARCH'   , 'cortex').lower() )
    # Product
    env['PRODUCT']  = ARGUMENTS.get('PRODUCT', 'basic')
    # Platform
    env['PLF']      = ARGUMENTS.get('PLF'    , 'aic8800')
    # Hardware Platform: PXP(0), FPGA(1), ASIC(2)
    env['HW_PLATFORM'] = ARGUMENTS.get('HW_PLATFORM', 'asic').lower()
    # Target Name
    env['TGTNAME']     = ARGUMENTS.get('TGTNAME'   , 'none').lower()
    # Build command
    env['BUILD_CMD']   = ARGUMENTS.get('BUILD_CMD' , 'none')
    # Target Mode
    env['TGT_MODE']   = ARGUMENTS.get('TGT_MODE' , 'none')
    # Test Case Configuration
    env['TEST']     = ARGUMENTS.get('TEST'   , 'none').lower()

    ################ RTOS/NETS Configuration ###################
    def_rtos = 'none'
    def_nets = 'none'
    def_m2d  = 'none'
    if env['PRODUCT'] in ['basic-rtos', 'host-wifi', 'host-bt', 'host-wb', 'host-dwb']:
        def_rtos = 'freertos'
    if env['PRODUCT'] in ['host-wifi', 'host-wb']:
        def_nets = 'lwip'

    # Used RTOS if any (available values: none, freertos)
    env['RTOS']          = ARGUMENTS.get('RTOS', def_rtos).lower()
    # Used Network Stack if any (available values: none, lwip)
    env['NETS']          = ARGUMENTS.get('NETS', def_nets).lower()
    # Main application for FHOST firmware (available value: ipc, example, tls_example, console, uartwifi,
    #   rtp, http_serv, web_cfg, voice, sntp_client, none)
    env['FHOST_APP']     = ARGUMENTS.get('FHOST_APP', 'console').lower()
    if env['FHOST_APP'] == 'hostif':
        env['NETS']      = ARGUMENTS.get('NETS', 'none').lower()

    # role in wifi voice(when env['FHOST_APP'] == 'voice'), dongle or headset
    env['WIFI_VOICE_ROLE'] = ARGUMENTS.get('WIFI_VOICE_ROLE', 'dongle').lower()

    # Wifi Audio Mem Exc
    env['WIFI_AUD_MEM'] = ARGUMENTS.get('WIFI_AUD_MEM', 'off').lower()

    # Used for mcu to dev mode if any (available values: ble, wifi, wb, none) tasks will be run in mcu mode.
    env['M2D']          = ARGUMENTS.get('M2D', def_m2d).lower()

    # Update the 8800M flash code if driver send msg before switch mcu mode to dev mode.
    env['M2D_OTA']      = ARGUMENTS.get('M2D_OTA', 'off').lower()

    ################ WIFI Configuration ###################
    def_wifi = 'none'
    if env['PRODUCT'] in ['host-wifi', 'host-wb', 'host-dwb']:
        def_wifi = 'wifi'
    env['WIFI_STACK']      = ARGUMENTS.get('WIFI_STACK', def_wifi).lower()

    # Host if type (available values: none, usb, sdio)
    env['HOSTIF'] = ARGUMENTS.get('HOSTIF', 'none').lower()

    # Host SDIO
    env['SDIO_FUNC2'] = ARGUMENTS.get('SDIO_FUNC2', 'off').lower()
    env['SDIO_RXMSG_Q'] = ARGUMENTS.get('SDIO_RXMSG_Q', 'on').lower()

    # DEVICE_IPC
    env['DEVICE_IPC'] = ARGUMENTS.get('DEVICE_IPC', 'off').lower()

    # Remain on mcu
    env['REMAIN_ON_MCU'] = ARGUMENTS.get('REMAIN_ON_MCU', 'on').lower()

    # 5g band
    env['BAND5G'] = ARGUMENTS.get('BAND5G', 'off').lower()

    # WPS
    env['WPS'] = ARGUMENTS.get('WPS', 'off').lower()

    # P2P
    env['P2P'] = ARGUMENTS.get('P2P', 'off').lower()

    # Ping
    env['PING'] = ARGUMENTS.get('PING', 'off').lower()

    # IPERF
    env['IPERF'] = ARGUMENTS.get('IPERF', 'off').lower()

    # High speed iperf
    env['HS_IPERF'] = ARGUMENTS.get('HS_IPERF', 'off').lower()

    # IPERF tcp optimization
    env['IPERF_TCP_OPT'] = ARGUMENTS.get('IPERF_TCP_OPT', 'on').lower()

    # softAP
    env['SOFTAP'] = ARGUMENTS.get('SOFTAP', 'off').lower()

    # Hostapd
    env['HOSTAPD'] = ARGUMENTS.get('HOSTAPD', 'off').lower()

    # SNTP
    env['SNTP'] = ARGUMENTS.get('SNTP', 'off').lower()

    # External crypto library (available value: none, mbedtls)
    if env['RTOS'] in ['freertos'] :
        env['CRYPTO'] = ARGUMENTS.get('CRYPTO', 'mbedtls').lower()
    else :
        env['CRYPTO'] = ARGUMENTS.get('CRYPTO', 'none').lower()

    #CHKSUM
    env['CHKSUM'] = ARGUMENTS.get('CHKSUM', 'on').lower()

    # RSSI of data packet
    env['RSSI_DATAPKT'] = ARGUMENTS.get('RSSI_DATAPKT', 'on').lower()

    # WIFI ENGINEERING MODE
    env['WIFI_ENGINEERING_MODE'] = ARGUMENTS.get('WIFI_ENGINEERING_MODE', 'off').lower()

    # Link wpas Library
    env['USE_LIB_WPA'] = ARGUMENTS.get('USE_LIB_WPA', 'off').lower()
    # Generate wpas Library
    env['GEN_LIB_WPA'] = ARGUMENTS.get('GEN_LIB_WPA', 'off').lower()

    # Link wapi Library
    env['USE_LIB_WAPI'] = ARGUMENTS.get('USE_LIB_WAPI', 'off').lower()
    # Generate wapi Library
    env['GEN_LIB_WAPI'] = ARGUMENTS.get('GEN_LIB_WAPI', 'off').lower()

    # Link wifi Library
    env['USE_LIB_WIFI'] = ARGUMENTS.get('USE_LIB_WIFI', 'off').lower()
    # Generate wifi Library
    env['GEN_LIB_WIFI'] = ARGUMENTS.get('GEN_LIB_WIFI', 'off').lower()

    # Link driver Library
    env['USE_LIB_DRV'] = ARGUMENTS.get('USE_LIB_DRV', 'off').lower()
    # Generate driver Library
    env['GEN_LIB_DRV'] = ARGUMENTS.get('GEN_LIB_DRV', 'off').lower()

    # Link audio Library
    env['USE_LIB_AUDIO'] = ARGUMENTS.get('USE_LIB_AUDIO', 'off').lower()
    # Generate audio Library
    env['GEN_LIB_AUDIO'] = ARGUMENTS.get('GEN_LIB_AUDIO', 'off').lower()

    # Link bt Library
    env['USE_LIB_BT'] = ARGUMENTS.get('USE_LIB_BT', 'off').lower()
    # Generate audio Library
    env['GEN_LIB_BT'] = ARGUMENTS.get('GEN_LIB_BT', 'off').lower()

    # Link dsp Library
    env['USE_LIB_DSP'] = ARGUMENTS.get('USE_LIB_DSP', 'off').lower()
    # Generate dsp Library
    env['GEN_LIB_DSP'] = ARGUMENTS.get('GEN_LIB_DSP', 'off').lower()

    # Link USB Device Library
    env['USE_LIB_USBD'] = ARGUMENTS.get('USE_LIB_USBD', 'off').lower()
    # Generate USB Device Library
    env['GEN_LIB_USBD'] = ARGUMENTS.get('GEN_LIB_USBD', 'off').lower()

    # Generate SDK version strings
    env['GEN_SDK_VER'] = ARGUMENTS.get('GEN_SDK_VER', 'off').lower()

    # WAPI
    env['WAPI'] = ARGUMENTS.get('WAPI', 'off').lower()

    # Wi-Fi hibernate
    env['WIFI_HIB'] = ARGUMENTS.get('WIFI_HIB', 'off').lower()

    # Wi-Fi CSI
    env['CSI'] = ARGUMENTS.get('CSI', 'off').lower()

    # BWMODE
    env['BWMODE'] = ARGUMENTS.get('BWMODE', 'off').lower()

    # Link algo Library
    env['USE_LIB_ALGO'] = ARGUMENTS.get('USE_LIB_ALGO', 'off').lower()
    # Generate algo Library
    env['GEN_LIB_ALGO'] = ARGUMENTS.get('GEN_LIB_ALGO', 'off').lower()

    # Bootloader ALGO
    env['ALGO'] = ARGUMENTS.get('ALGO', 'off').lower()
    env['LZMA'] = ARGUMENTS.get('LZMA', 'off').lower()
    env['BOOT_AGO'] = ARGUMENTS.get('BOOT_AGO', 'off').lower()

    # Hostif Optimize
    env['HOSTIF_OPT'] = ARGUMENTS.get('HOSTIF_OPT', 'off').lower()

    ################ BT base Configuration ###################
    def_bt = 'none'
    if env['PRODUCT'] in ['host-bt', 'host-wb', 'host-dwb']:
        def_bt = 'btdm'

    env['BT_STACK']       = ARGUMENTS.get('BT_STACK', def_bt).lower()

    ################ BT_BLE base Configuration ###################
    env['BT_BLE']            = ARGUMENTS.get('BT_BLE', 'off').lower()
    # default state is adv / scan / none
    env['BLE_DFT_STATE']     = ARGUMENTS.get('BLE_DFT_STATE', 'adv')
    # BLE_WAKEUP used for wakeup android/linux usb driver in uboot sleep mode
    env['BLE_WAKEUP']     = ARGUMENTS.get('BLE_WAKEUP', 'off')
    # BLE_DAP used for ble delay add profile in init process.
    env['BLE_DAP']     = ARGUMENTS.get('BLE_DAP', 'off')
    # Set BLE close default when sys start up, after sys setup RF calibration
    env['BLE_START_CLOSE'] = ARGUMENTS.get('BLE_START_CLOSE', 'off')

    ################ BT advanced Configuration ###################
    env['BT_TWS']         = ARGUMENTS.get('BT_TWS', 'off')
    env['BT_TWS_PLUS']    = ARGUMENTS.get('BT_TWS_PLUS', 'off')
    env['LINK_ONE']       = ARGUMENTS.get('LINK_ONE', 'off')
    env['TWS_ROLE']       = ARGUMENTS.get('TWS_ROLE', 'none')
    env['AON']            = ARGUMENTS.get('AON', 'on')
    env['A2DP']            = ARGUMENTS.get('A2DP', 'on')
    env['A2DP_SOURCE']    = ARGUMENTS.get('A2DP_SOURCE', 'off')
    env['HFP_AG']         = ARGUMENTS.get('HFP_AG', 'off')
    env['AIC_VENDOR_ADV'] = ARGUMENTS.get('AIC_VENDOR_ADV', 'off')
    env['BT_OTA']         = ARGUMENTS.get('BT_OTA', 'off')
    env['BT_OTA_BOX']     = ARGUMENTS.get('BT_OTA_BOX', 'off')
    # BT for those who won't use out bt stack
    env['BT_USER']        = ARGUMENTS.get('BT_USER', 'off')
    # BLE_ONLY=on: only support BLE,not support BR
    env['BLE_ONLY']       = ARGUMENTS.get('BLE_ONLY', 'off')
    # BTDM=on: support BR/BLE combo
    env['BTDM']           = ARGUMENTS.get('BTDM', 'off')
    # BT_PATCH_MODE=mcu/tws
    env['BT_PATCH_MODE']  = ARGUMENTS.get('BT_PATCH_MODE', 'mcu')

    ################ UTILS Configuration ###################
    env['UTILS']      = ARGUMENTS.get('UTILS', 'off').lower()

    #HW_SBC
    env['HW_SBC'] = ARGUMENTS.get('HW_SBC', 'off').lower()

    #FATFS
    env['FATFS'] = ARGUMENTS.get('FATFS', 'off').lower()

    #GSENSOR
    env['GSENSOR'] = ARGUMENTS.get('GSENSOR', 'off').lower()

    #I2CM_SFT
    env['I2CM_SFT'] = ARGUMENTS.get('I2CM_SFT', 'off').lower()

    #LIGHT_SENSOR
    env['LIGHT_SENSOR'] = ARGUMENTS.get('LIGHT_SENSOR', 'off').lower()

    #SCREEN
    env['SCREEN'] = ARGUMENTS.get('SCREEN', 'off').lower()

    #E-paper
    env['EPAPER'] = ARGUMENTS.get('EPAPER', 'off').lower()

    #XYZMDM
    env['XYZMDM'] = ARGUMENTS.get('XYZMDM', 'off').lower()

    #XMODEM
    env['XMODEM'] = ARGUMENTS.get('XMODEM', 'off').lower()

    #MINILZO
    env['MINILZO'] = ARGUMENTS.get('MINILZO', 'off').lower()

    # software watchdog
    env['SOFTWDG'] = ARGUMENTS.get('SOFTWDG', 'off').lower()

    # temperature compensation
    env['TEMP_COMP'] = ARGUMENTS.get('TEMP_COMP', 'off').lower()

    # HTTP web client
    env['WEBCLIENT'] = ARGUMENTS.get('WEBCLIENT', 'off').lower()

    # cJSON module
    env['CJSON'] = ARGUMENTS.get('CJSON', 'off').lower()

    #OTA
    env['OTA'] = ARGUMENTS.get('OTA', 'off').lower()

    #KEY_MODULE
    env['KEY_MODULE'] = ARGUMENTS.get('KEY_MODULE', 'off').lower()

    #LED_MODULE
    env['LED_MODULE'] = ARGUMENTS.get('LED_MODULE', 'off').lower()

    #MQTT
    env['MQTT'] = ARGUMENTS.get('MQTT', 'off').lower()

    #RTP
    env['RTP'] = ARGUMENTS.get('RTP', 'off').lower()

    #DPD
    env['DPD'] = ARGUMENTS.get('DPD', 'on').lower()

    ###################################################
    # Debug / Analysis Configuration
    ###################################################
    # debug mode (on or off)
    env['DBG']              = ARGUMENTS.get('DBG'    , 'on')
    # static analysis tool (all, cppcheck, flawfinder, off)
    env['ANALYSIS']         = ARGUMENTS.get('ANALYSIS', 'off')
    # cppcheck check all configuration (on, off)
    env['CPPCHECK_ALL_CFG'] = ARGUMENTS.get('CPPCHECK_ALL_CFG', 'off')
    # TRC used
    env['TRC']              = ARGUMENTS.get('TRC'    ,  'off')
    # Build trace dictionary
    env['TRC_DICT']         = ARGUMENTS.get('TRC_DICT', 'on' if env['TRC'] != 'off' else 'off')

    # verbose level: 0 by default (0 or 1 supported)
    env['VERBOSE']  = int(ARGUMENTS.get('V'      , 0))
    # save temporary files: 0 by default (0 or 1 supported)
    env['SAVETMP']  = int(ARGUMENTS.get('SAVETMP', 0))
    # only for RVDS: remarks enabled (0 or 1 supported)
    env['REM']      = int(ARGUMENTS.get('REM'    , 0))
    # coverage enabled: 0by default
    env['COV']      = int(ARGUMENTS.get('COV'    , 0))
    env['RUN']      = int(ARGUMENTS.get('RUN'    , 0))

    # only for embedded compilation: CPU type
    env['CPU']      = ARGUMENTS.get('CPU' , '')
    # consider warning as error
    env['WARN']     = ARGUMENTS.get('WARN', 'on')
    # only for embedded compilation: produce debugging information
    env['DBGINFO']  = ARGUMENTS.get('DBGINFO', 'off')

    # STDLIB
    env['STDLIB']   = ARGUMENTS.get('STDLIB', 'off').lower()

    # Fault Handler
    env['FHDLR']    = ARGUMENTS.get('FHDLR', 'on')

    # Common
    env['COMMON']   = ARGUMENTS.get('COMMON', 'off')

    # Console
    env['CONSOLE']  = ARGUMENTS.get('CONSOLE', 'on')

    # AT Command
    env['ATCMD']    = ARGUMENTS.get('ATCMD', 'off')

    # Letter Shell
    env['LETTER_SHELL'] = ARGUMENTS.get('LETTER_SHELL', 'off')

    # DSP
    env['DSP']    = ARGUMENTS.get('DSP', 'off')

    # Apps
    env['APPS']    = ARGUMENTS.get('APPS', 'off')

    # Audio Application Used By Other Modules
    env['AUD_USED']    = ARGUMENTS.get('AUD_USED', 'on')

    # Audio Stream Input Output
    env['ASIO']    = ARGUMENTS.get('ASIO', 'off')

    # Audio
    env['AUDIO']    = ARGUMENTS.get('AUDIO', 'off')

    # BT Audio
    env['BT_AUDIO']    = ARGUMENTS.get('BT_AUDIO', 'off')

    # Wi-Fi Audio
    env['WIFI_AUDIO']    = ARGUMENTS.get('WIFI_AUDIO', 'off')

    # USB BT
    env['USB_BT']    = ARGUMENTS.get('USB_BT', 'off')

    # AAC
    env['AAC']    = ARGUMENTS.get('AAC', 'off')

    # MP3
    env['MP3']    = ARGUMENTS.get('MP3', 'off')

    # LC3
    env['LC3']    = ARGUMENTS.get('LC3', 'off')

    # BT PROMPT
    env['BT_PROMPT']    = ARGUMENTS.get('BT_PROMPT', 'off')

    # PROMPT LANGUAGE (en or cn)
    env['LANG']    = ARGUMENTS.get('LANG', 'en')

    # DAC mixer mode, can be left, mute, right, lprd2, lmrd2
    # left: left channel data
    # mute: mute
    # right: right channel data
    # lprd2: (left channel + right channel) / 2
    # lmrd2: (left channel - right channel) / 2
    env['DACL_MIXER_MODE'] = ARGUMENTS.get('DACL_MIXER_MODE', 'left').lower()
    env['DACR_MIXER_MODE'] = ARGUMENTS.get('DACR_MIXER_MODE', 'right').lower()

    # AIC1000 MIC matrix
    env['AIC1000_MIC_MATRIX'] = ARGUMENTS.get('AIC1000_MIC_MATRIX', '0').lower()

    # Use external codec AIC1000
    env['EXT_AIC1000'] = ARGUMENTS.get('EXT_AIC1000', 'off').lower()

    # HCLK option: Generate I2S MCLK
    env['HCLK_MCLK']    = ARGUMENTS.get('HCLK_MCLK', 'off')

    # PMIC is valid or not
    env['PMIC']     = ARGUMENTS.get('PMIC', 'on').lower()

    # PMIC version (full, lite, aud, inner)
    env['PMIC_VER'] = ARGUMENTS.get('PMIC_VER', 'lite').lower()

    # PMIC interface (asdma, psim)
    env['PMIC_ITF'] = ARGUMENTS.get('PMIC_ITF', 'asdma').lower()

    # PMIC option: Low power mode enable
    env['PMIC_LP']  = ARGUMENTS.get('PMIC_LP', 'on').lower()

    # PMIC option: use ldo/dcdc/all(ldo+dcdc) vcore09
    env['PMIC_VCORE'] = ARGUMENTS.get('PMIC_VCORE', 'dcdc').lower()

    # PMIC option: Vcore calibration enable
    env['VCORE_CALIB'] = ARGUMENTS.get('VCORE_CALIB', 'off').lower()

    # PMIC option: Low power 128k derived from lpo 512k
    env['LPO_512K']    = ARGUMENTS.get('LPO_512K', 'on')

    # PMIC option: Generate I2S MCLK
    env['PMIC_MCLK']    = ARGUMENTS.get('PMIC_MCLK', 'off')

    # PMIC option: voltage drop
    env['DCDC_CORE_DROP']    = ARGUMENTS.get('DCDC_CORE_DROP', 'on')
    env['DCDC_RF_DROP']    = ARGUMENTS.get('DCDC_RF_DROP', 'on')
    env['LDO_VCORE09_DROP']    = ARGUMENTS.get('LDO_VCORE09_DROP', 'off')
    env['LDO_VRTC09_DROP']    = ARGUMENTS.get('LDO_VRTC09_DROP', 'on')

    # low power code in RAM
    env['LPIRAM']   = ARGUMENTS.get('LPIRAM', 'off').lower()

    # Pre-release code
    env['PRERELEASE_CODE'] = ARGUMENTS.get('PRERELEASE_CODE', 'off').lower()

    # RF MODE (null, bt_only, bt_combo, btwifi_combo)
    env['RF_MODE']    = ARGUMENTS.get('RF_MODE', 'bt_only').lower()

    # BT MODE (bt_only_sw, bt_wifi_combo, bt_only, bt_only_test, bt_wifi_combo_test, bt_only_coant, null)
    env['BT_MODE']    = ARGUMENTS.get('BT_MODE', 'bt_only').lower()

    # ROM version: >=1 indicates ROM release version
    env['ROM_VER'] = ARGUMENTS.get('ROM_VER', 'auto')

    # RAM optimization
    env['RAM_OPT'] = ARGUMENTS.get('RAM_OPT', 'off')

    # RAM version, 'on' indicates use RAM version
    env['BOOT_RAM_VER'] = ARGUMENTS.get('BOOT_RAM_VER', 'off')
    env['WIFI_RAM_VER'] = ARGUMENTS.get('WIFI_RAM_VER', 'off')
    env['BTDM_RAM_VER'] = ARGUMENTS.get('BTDM_RAM_VER', 'off')
    env['AON_RAM_VER'] = ARGUMENTS.get('AON_RAM_VER', 'off')

    # BT testmode
    env['BT_TESTMODE'] = ARGUMENTS.get('BT_TESTMODE', 'off')

    # Wi-Fi testmode
    env['WIFI_TESTMODE'] = ARGUMENTS.get('WIFI_TESTMODE', 'off')

    # Flash fw
    env['FLASH_FW'] = ARGUMENTS.get('FLASH_FW', 'off')

    # wifi tx task
    env['WIFI_TX_TASK'] = ARGUMENTS.get('WIFI_TX_TASK', 'off')

    # CODEC BOARD version, 0 indicates no codec, 1 indicates AIC8800_CODEC_U01, 2 indicates AIC8800_CODEC_U02...
    env['CODEC_BOARD_VER'] = ARGUMENTS.get('CODEC_BOARD_VER', '0')

    # USB Device
    env['USB_DEVICE'] = ARGUMENTS.get('USB_DEVICE', 'off').lower()

    # USB Device Audio
    env['USB_DEVICE_AUDIO'] = ARGUMENTS.get('USB_DEVICE_AUDIO', 'off').lower()

    # USB Audio Sampling Frequency (192k, 96k, 48k, 44_1k, 16k)
    env['USB_AUDIO_FREQ'] = ARGUMENTS.get('USB_AUDIO_FREQ', '48k').lower()

    # USB Device MSC
    env['USB_DEVICE_MSC'] = ARGUMENTS.get('USB_DEVICE_MSC', 'off').lower()

    # Flash Fat
    env['FLASH_FAT'] = ARGUMENTS.get('FLASH_FAT', 'off').lower()

    # System Heap Size in hexadecimal, for example 0x20000.
    env['HEAP_SIZE'] = ARGUMENTS.get('HEAP_SIZE', '0x10000')

    # Code Start Address
    env['CODE_START_ADDR'] = ARGUMENTS.get('CODE_START_ADDR', '0x08000000')

    # BLE role (broadcaster, observer, peripheral, central or all)
    env['BLEROLE']     = ARGUMENTS.get('BLEROLE'   , 'all')

    ###################################################
    # BLE Profiles
    ###################################################
    # All Ble Profiles
    env['BLE_ALLPRF']   = ARGUMENTS.get('BLE_ALLPRF', 'off')
    # Number of Profile Tasks allocated
    env['BLE_NBPRF']    = ARGUMENTS.get('BLE_NBPRF', '10')

    # Device Information Service Client
    env['DISC']     = ARGUMENTS.get('DISC', env['BLE_ALLPRF'])
    # Device Information Service Server
    env['DISS']     = ARGUMENTS.get('DISS', env['BLE_ALLPRF'])
    # Proximity monitor
    env['PXPM']     = ARGUMENTS.get('PXPM', env['BLE_ALLPRF'])
    # Proximity reporter
    env['PXPR']     = ARGUMENTS.get('PXPR', env['BLE_ALLPRF'])
    # Find me locator
    env['FMPL']     = ARGUMENTS.get('FMPL', env['BLE_ALLPRF'])
    # Find me target
    env['FMPT']     = ARGUMENTS.get('FMPT', env['BLE_ALLPRF'])
    # Health thermometer collector
    env['HTPC']     = ARGUMENTS.get('HTPC', env['BLE_ALLPRF'])
    # Health thermometer
    env['HTPT']     = ARGUMENTS.get('HTPT', env['BLE_ALLPRF'])
    # Blood Pressure collector
    env['BLPC']     = ARGUMENTS.get('BLPC', env['BLE_ALLPRF'])
    # Blood Pressure Sensor
    env['BLPS']     = ARGUMENTS.get('BLPS', env['BLE_ALLPRF'])
    # Heart Rate collector
    env['HRPC']     = ARGUMENTS.get('HRPC', env['BLE_ALLPRF'])
    # Heart Rate Sensor
    env['HRPS']     = ARGUMENTS.get('HRPS', env['BLE_ALLPRF'])
    # Time Client
    env['TIPC']     = ARGUMENTS.get('TIPC', env['BLE_ALLPRF'])
    # Time Server
    env['TIPS']     = ARGUMENTS.get('TIPS', env['BLE_ALLPRF'])
    # Scan Parameter Client
    env['SCPPC']    = ARGUMENTS.get('SCPPC', env['BLE_ALLPRF'])
    # Scan Parameter Server
    env['SCPPS']    = ARGUMENTS.get('SCPPS', env['BLE_ALLPRF'])
    # Battery Service Client
    env['BASC']     = ARGUMENTS.get('BASC',  env['BLE_ALLPRF'])
    # Battery Service Server
    env['BASS']     = ARGUMENTS.get('BASS',  env['BLE_ALLPRF'])
    # HID Profile Device
    env['HOGPD']    = ARGUMENTS.get('HOGPD', env['BLE_ALLPRF'])
    # HID Profile Boot Host
    env['HOGPBH']   = ARGUMENTS.get('HOGPBH', env['BLE_ALLPRF'])
    # HID Profile Report Host
    env['HOGPRH']   = ARGUMENTS.get('HOGPRH', env['BLE_ALLPRF'])
    # Glucose Collector
    env['GLPC']     = ARGUMENTS.get('GLPC', env['BLE_ALLPRF'])
    # Glucose Sensor
    env['GLPS']     = ARGUMENTS.get('GLPS', env['BLE_ALLPRF'])
    # Running Speed and Cadence Client
    env['RSCPC']    = ARGUMENTS.get('RSCPC', env['BLE_ALLPRF'])
    # Running Speed and Cadence Server
    env['RSCPS']    = ARGUMENTS.get('RSCPS', env['BLE_ALLPRF'])
    # Cycling Speed and Cadence Client
    env['CSCPC']    = ARGUMENTS.get('CSCPC', env['BLE_ALLPRF'])
    # Cycling Speed and Cadence Server
    env['CSCPS']    = ARGUMENTS.get('CSCPS', env['BLE_ALLPRF'])
    # Cycling Power Client
    env['CPPC']    = ARGUMENTS.get('CPPC', env['BLE_ALLPRF'])
    # Cycling Power Server
    env['CPPS']    = ARGUMENTS.get('CPPS', env['BLE_ALLPRF'])
    # Location and Navigation Client
    env['LANC']    = ARGUMENTS.get('LANC', env['BLE_ALLPRF'])
    # Location and Navigation Server
    env['LANS']    = ARGUMENTS.get('LANS', env['BLE_ALLPRF'])
    # Alert Notification Client
    env['ANPC']     = ARGUMENTS.get('ANPC', env['BLE_ALLPRF'])
    # Alert Notification Server
    env['ANPS']     = ARGUMENTS.get('ANPS', env['BLE_ALLPRF'])
    # Phone Alert Status Client
    env['PASPC']    = ARGUMENTS.get('PASPC', env['BLE_ALLPRF'])
    # Phone Alert Status Server
    env['PASPS']    = ARGUMENTS.get('PASPS', env['BLE_ALLPRF'])
    #  Weight Scale Client
    env['WSCC']     = ARGUMENTS.get('WSCC', env['BLE_ALLPRF'])
    #  Weight Scale Server
    env['WSCS']     = ARGUMENTS.get('WSCS', env['BLE_ALLPRF'])
    #  Body Composition Client
    env['BCSC']     = ARGUMENTS.get('BCSC', env['BLE_ALLPRF'])
    #  Body Composition Server
    env['BCSS']     = ARGUMENTS.get('BCSS', env['BLE_ALLPRF'])
    #  User Data Service Server
    env['UDSS']     = ARGUMENTS.get('UDSS', env['BLE_ALLPRF'])
    #  User Data Service Client
    env['UDSC']     = ARGUMENTS.get('UDSC', env['BLE_ALLPRF'])
    #  Ble Smartconfig Server
    env['SMARTCONFIGS']     = ARGUMENTS.get('SMARTCONFIGS', env['BLE_ALLPRF'])
    #  User Data Service Server
    env['AUDTRANSMITS']     = ARGUMENTS.get('AUDTRANSMITS', env['BLE_ALLPRF'])
    #  User Data Service Client
    env['AUDTRANSMITC']     = ARGUMENTS.get('AUDTRANSMITC', env['BLE_ALLPRF'])
    #  User Defined Service Server
    env['UDFS']     = ARGUMENTS.get('UDFS', env['BLE_ALLPRF'])
    #  User Defined Service Client
    env['UDFC']     = ARGUMENTS.get('UDFC', env['BLE_ALLPRF'])

    ###################################################
    # BLE Internal Applications
    ###################################################
    # Health Thermometer Application
    env['BLE_APP_HT']       = ARGUMENTS.get('BLE_APP_HT',      'off')
    # HID Mouse Application
    env['BLE_APP_HID']      = ARGUMENTS.get('BLE_APP_HID',     'off')
    # Heart Rate Application
    env['BLE_APP_HR']       = ARGUMENTS.get('BLE_APP_HR',      'off')
    # Device Information Application
    env['BLE_APP_DIS']      = ARGUMENTS.get('BLE_APP_DIS',     'off')
    # SmartConfig Application
    env['BLE_APP_SMARTCONFIG']      = ARGUMENTS.get('BLE_APP_SMARTCONFIG',     'off')
    # Aud Transmit Application
    env['BLE_APP_AUDTRANSMIT']      = ARGUMENTS.get('BLE_APP_AUDTRANSMIT',     'none')
    # User Defined Application
    env['BLE_APP_UDF']      = ARGUMENTS.get('BLE_APP_UDF',     'none')

    #******************************
    # User Code (none, src or lib)
    #******************************
    env['USER_CODE'] = ARGUMENTS.get('USER_CODE', 'none')

    #******************************
    # Static SW analysis          *
    #******************************
    # Get sparse program path
    path_sparse = env.WhereIs('sparse') or SCons.Util.WhereIs('sparse')
    if path_sparse:
        path_sparse = os.path.dirname(path_sparse)
        print '\n Info: SW analysis tool found:\n\t=> path:' + path_sparse
        print '\t=> SW will be analyzed during build\n'
        env.PrependENVPath('PATH', path_sparse)
        # Add library include path
        path_aps = env.WhereIs('aps-gcc') or SCons.Util.WhereIs('aps-gcc')
        path_aps = os.path.dirname(path_aps)
        path_aps_lib = os.path.join(path_aps, '../lib/gcc/aps/4.5.3/include')
#        print '[SPARSE] Add Cortus library include path: ' + path_aps_lib + '\n'
        env['LIBINC'] = '-I' + path_aps_lib
        # Insert analysis tool compiler wrapper
        env['ENV']['REAL_CC'] = env['CC']
        env['CC'] = 'cgcc -gcc-base-dir ' + path_aps + '/../aps/'
    else:
        print "\n Warning : SW analysis tool not found"
        print "\t=> check sparse is available on your environment (linux only)\n"

    if 'I' in ARGUMENTS:
        env['INST'] = ARGUMENTS['I']
    elif 'BLE_INSTALL' in os.environ:
        env['INST'] = os.environ['BLE_INSTALL']
    elif 'BT_INSTALL' in os.environ:
        env['INST'] = os.environ['BT_INSTALL']
    else:
        env['INST'] = ''

    runcov = int(ARGUMENTS.get('RUNCOV', 0))

    if runcov == 0:
        runcov = int(ARGUMENTS.get('COVRUN', 0))

    if runcov:
        env['COV'] = runcov
        env['RUN'] = runcov

    # Max command line length for the linker. 0 means disabled.
    # Work with gcc 4.2.x or above
    # Work with python-win32
    # Therefore, will fail with gcc-3 and python-cygwin
    if sys.platform == 'win32':
        env['MAXLINELENGTH'] = 8000
    elif sys.platform == 'cygwin':
        env['MAXLINELENGTH'] = 0
    else:
        env['MAXLINELENGTH'] = 8000

    # speed up?
    env.Decider('MD5')  # MD5-timestamp, MD5, timestamp-match
    #env.SourceCode('.', None)

    # set output strings
    if env['VERBOSE'] == 0:
        outstr_set(env, env['BUILDTOOL'])

    #if env['COV'] == 2:
    #    winbase = os.path.abspath('../..').replace('\\','\\\\\\\\')
    #    env['SED_SUBST_OBJ'] = "'/" + winbase + "/ s+\\\\\\\\+/+g'"
    #    env['SED_PATH'] = SCons.Util.WhereIs("sed.exe")

    return env


#-----------------------------------------------------------
# output strings
#-----------------------------------------------------------

OUTSTR = '%16s ${TARGET.file}'

OUTSTR_REG = '[py REG]'
OUTSTR_MIB = '[py MIB]'
OUTSTR_TTR = '[py TTR]'
OUTSTR_FLT = '[elf2bflt]'
OUTSTR_SEDX = '[sed exe]'
OUTSTR_SEDO = '[sed obj]'
OUTSTR_LC_I = '[lcov init]'
OUTSTR_LC_P = '[lcov proc]'
OUTSTR_LC_G = '[locv gen]'

def outstr_set(env, buildtool):

    cc_str  = OUTSTR % ('[' + buildtool + '  CC]')
    ld_str  = OUTSTR % ('[' + buildtool + '  LD]')
    as_str  = OUTSTR % ('[' + buildtool + '  AS]')
    aspp_str= OUTSTR % ('[' + buildtool + '  ASPP]')
    cxx_str = OUTSTR % ('[' + buildtool + '  CXX]')
    ar_str  = OUTSTR % ('[' + buildtool + '  AR]')

    env.Replace(CCCOMSTR   = cc_str)
    env.Replace(LINKCOMSTR = ld_str)
    env.Replace(ASCOMSTR   = as_str)
    env.Replace(ASPPCOMSTR = aspp_str)
    env.Replace(CXXCOMSTR  = cxx_str)
    env.Replace(ARCOMSTR   = ar_str)


def outstr_gen(s, target, source, env):
    for t in target:
        print '%16s ' % (env['OUTSTR']) + t.name


def outstr_utest(s, target, source, env):
    for t in target:
        print '%16s ' % ('[' + source[0].name + ']') + t.name

def outstr_inst(s, target, source, env):
    for t in target:
        print '%16s ' % ('[install]') + t.abspath

def outstr_date(s, target, source, env):
    for t in target:
        print '%16s ' % ('[py date]') + t.name


import re

def modules_import(env, modules_list, abs_path):
    """Import sourcelist and includelist from modules"""
    inclist = []
    srclist = []

    for module in modules_list:
        inclist += [join(abs_path, module, 'api')]
        srclist += file_list_read(env, join(abs_path, module, 'sourcelist.txt'), join(module, 'src'))
        module = module.replace('-', '_')
        env['CPPDEFINES'] += ['CFG_MODULE_' + module.upper()]

    return inclist, srclist

def file_list_read(env, filelist_name, append_path = ''):
    """Read a list from a file"""
    filelist = []

    try:
        fin = open(filelist_name, 'rU')
    except:
        print("Cannot open list file: " + filelist_name)
        sys.exit()

    if append_path != '':
        directory = append_path
    else:
        directory = os.path.dirname(filelist_name)

    filter_list = [False]
    for line in fin:
        # remove leading and trailing trash
        line = env.subst(line.strip())

        cond_pattern = re.compile("^#if (.*)$").match(line)
        else_cond_pattern = re.compile("^#else .*$").match(line)
        end_cond_pattern = re.compile("^#endif .*$").match(line)
        include_pattern = re.compile('^\s*include (.*)').match(line)

        if (cond_pattern != None):
            if not filter_list[-1]:
                filter = False
                condition = "if not(%s): filter = True" % (cond_pattern.group(1))
                exec condition
                filter_list.append(filter)
            else:
                filter_list.append(True)

        elif (else_cond_pattern != None):
            if not filter_list[-2]:
                filter_list[-1] = not filter_list[-1]
        elif (end_cond_pattern != None):
            filter_list.pop()

        elif line and line[0] != '#' and (not filter_list[-1]):
            #print "added:", line
            if include_pattern :
                include_file = os.path.join(directory, include_pattern.group(1))
                #print 'apath:', append_path, 'file:', include_file
                filelist += file_list_read(env, include_file, append_path)
            else:
                filelist += [join(append_path, line)]

    fin.close()

    return filelist


def load_script(file):
    script = ""
    try:
        script_file = open(file, 'r')
        for line in script_file.readlines():
            script += line
        script_file.close()
    except:
        pass

    return script


def action_sed_obj(target, source, env):

    gcno = str(target[0]).replace('.obj', '.gcno')

    if os.access(gcno, os.W_OK):
        os.spawnl(os.P_WAIT, env['SED_PATH'], "sed", "-b", "-i", "-e", env['SED_SUBST_OBJ'], gcno)

    return 0

def build_object(env, src_list, src_dir, obj_dir, build_dir = ""):

    fake_src_list = []
    fake_src_list2 = []
    preproc_src_list = []
    for source in src_list:
        # prep paths
        fake_file = join(obj_dir, build_dir, source)
        fake_dir = os.path.dirname(fake_file)
        real_dir = os.path.dirname(join(src_dir, source))

        #print "VAR: %80s <-> %s" % (fake_dir, real_dir)
        # translate object directory into source directory
        env.VariantDir(fake_dir, real_dir, duplicate=0)

        #
        # The object to the build list
        #
        # Special case for RiCow boot file that must NOT be comipled with option flto
        # Actually the only way to change the compile option for some files is to modify the
        # environment applied to these files. The hook has been implemented here until
        # a solution for applying file-specific options is available
        #
        if re.search("boot\.c", source) or re.search("interrupt\.c", source):
            fake_src_list2.append(fake_file)
        else:
            fake_src_list.append(fake_file)
            fake_file_split = fake_file.rsplit('.', 1)
            if (fake_file_split[1] == 'c'):
                env['SRC_LIST'].append(join(src_dir, source))
                preproc_file = fake_file_split[0] + '.i'
                preproc_src_list.append(preproc_file)

    env['PREPROC_SRC'] += preproc_src_list

    # build the object files
    objlist = env.Object(fake_src_list)

    # Add the specific file with their options modification
    if len(fake_src_list2):
        env2 = env.Clone()
        env2['FLTO'] = ''
        objlist.append(env2.Object(fake_src_list2))

    if env['COV'] and GetOption('clean'):
        for obj in objlist:
            #print "remove? ", str(obj).replace('.obj', '.gcno')
            Execute(Delete(str(obj).replace(env['OBJSUFFIX'], '.gcno')))
            Execute(Delete(str(obj).replace(env['OBJSUFFIX'], '.gcda')))
    #    else:
    #        for obj in objlist:
    #            #env.AddPostAction(obj, Action(action_sed_obj, string_sed_obj))
    #
    #            env.AddPostAction(obj, Action(action_sed_obj, '%16s ${TARGET.filebase}.gcno' % (OUTSTR_SEDO)))

    return objlist

def rvds_elf2bin(env, target, source):
    OUTSTR_ELF = '[rvds ELF]'
    return env.Command(target + '.bin', source, 'fromelf -c --bin --output $TARGET $SOURCE',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def armcc_5_elf2bin(env, target, source):
    OUTSTR_ELF = '[armcc_5 ELF2bin]'
    return env.Command(target+'.bin', source, 'fromelf --bin -o $TARGET $SOURCE',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def armcc_5_elf2rcf(env, target, source):
    OUTSTR_ELF = '[armcc_5 ELF2rcf]'
    return env.Command(target+'.rcf', source, 'fromelf --vhx --32x1 -o $TARGET $SOURCE',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def armcc_5_elf2dasm(env, target, source):
    OUTSTR_ELF = '[armcc_5 ELF2dasm]'
    return env.Command(target+'_dasm.txt', source, 'fromelf --text -rc -o $TARGET $SOURCE',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def armcc_5_elf2data(env, target, source):
    OUTSTR_ELF = '[armcc_5 ELF2data]'
    return env.Command(target+'_data.txt', source, 'fromelf --text -ad -o $TARGET $SOURCE',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def arm_none_eabi_elf2bin(env, target, source):
    OUTSTR_ELF = '[gcc ELF]'
    return env.Command(target + '.bin', source, 'arm-none-eabi-objcopy -v -O binary $SOURCE $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

# Can NOT be used, cause Command do NOT support redirection. Use gcc_elf2dasm instead.
def arm_none_eabi_elf2asm(env, target, source):
    OUTSTR_ELF = '[gcc ELF]'
    return env.Command(target+'.asm', source, 'arm-none-eabi-objdump -d $SOURCE > $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def aps_elf2bin(env, target, source):
    OUTSTR_ELF = '[aps ELF]'
    return env.Command(target + '.bin', source, 'aps-objcopy -O binary -R .lpus_bss $SOURCE $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def riscv_elf2bin(env, target, source):
    OUTSTR_ELF = '[riscv ELF]'
    return env.Command(target +'.bin', source, 'riscv32-unknown-elf-objcopy -O binary -R .lpus_bss $SOURCE $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def gcc_elf2bin(env, target, source):
    OUTSTR_ELF = '[gcc ELF]'
    return env.Command(target+'.bin', source, 'arm-none-eabi-objcopy -O binary $SOURCE $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def elf2dasm_command(target, source, env):
    dasmf = target[0].path
    dataf = dasmf.replace('_dasm.txt', '_data.txt')
    elff = source[0].path
    fh_dasm = open(dasmf, 'w')
    fh_data = open(dataf, 'w')
    try:
        cmdstr_dasm = 'arm-none-eabi-objdump -dS -j .text -j .lptext -j .pavol_text -j .fast_func -j .pstext -j .ramtext ' + elff
        stdstr_dasm = os.popen(cmdstr_dasm).read()
        fh_dasm.write(stdstr_dasm)
        cmdstr_data = 'arm-none-eabi-objdump -dS -j .data -j .bss -j .uninited ' + elff
        stdstr_data = os.popen(cmdstr_data).read()
        fh_data.write(stdstr_data)
    finally:
        fh_dasm.close()
        fh_data.close()

def gcc_elf2dasm(env, target, source):
    OUTSTR_ELF = '[gcc ELF2dasm]'
    return env.Command(target+'_dasm.txt', source, elf2dasm_command,
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_ELF)

def bin2rcf_common(binf, rcff, bytew):
    fh_bin = open(binf, 'rb')
    fh_rcf = open(rcff, 'wb')
    try:
        while True:
            chunk = fh_bin.read(bytew)
            if not chunk:
                break
            hexstr = binascii.b2a_hex(chunk)
            if bytew > 1:
                hexstr = hexstr.decode('hex')[::-1].encode('hex_codec')
            fh_rcf.write(hexstr)
            fh_rcf.write('\r\n')
    finally:
        fh_rcf.close()
        fh_bin.close()

def bin2rcf_command(target, source, env):
    rcff = target[0].path
    binf = source[0].path
    bin2rcf_common(binf, rcff, 4)
    rcff = os.path.splitext(target[0].path)[0] + '_8b.rcf'
    bin2rcf_common(binf, rcff, 1)

def gcc_bin2rcf(env, target, source):
    OUTSTR_RCF = '[gcc bin2rcf]'
    return env.Command(target+'.rcf', source, bin2rcf_command,
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_RCF)

def gcc_lds_preproc(env, target, source):
    OUTSTR_LDS = '[gcc LDSPP]'
    return env.Command(target, source, 'arm-none-eabi-cpp -E -P $SOURCE $LINKFLAGS $CPPFLAGS $_CPPDEFFLAGS -o $TARGET',
                       PRINT_CMD_LINE_FUNC=outstr_gen, OUTSTR=OUTSTR_LDS)


def gcov_cygwin(env, target):

    winconf = os.path.abspath('..').replace('\\', '/')
    cygconf = '/cygdrive/' + winconf[0].lower() + winconf[2:]
    winbuild = os.path.abspath(ext_path(env['OBJ_DIR'])) + '\\'

    # awfull bug in scons/python/cygwin: if '*' in the argument, '\' must be duplicated!
    #winbuild = winbuild.replace('\\', '\\\\\\\\')

    sed_subst = "'s+" + cygconf + "/" + winbuild.replace('\\', '\\\\\\\\') + "\\(.*\\)\\.gcda" \
                "+" + winbuild.replace('\\', '/') + "\\1\\.gcda\\x00" + cygconf + "+g'"

    action_cmd = "sed -b -i " + sed_subst + " " + str(target[0])
    action_str = '%16s $TARGET.name' % (OUTSTR_SEDX)
    env.AddPostAction(target, Action(action_cmd, action_str))

def static_analysis(tool_name, build_dir, includelist, env):
    if tool_name == 'cppcheck':
        sources = []
        includes = []
        for src in env['SRC_LIST']:
            pos = src.find('$')
            while pos != -1:
                stop = src.find('\\', pos)
                if stop == -1:
                    stop = src.find('/', pos)
                if stop == -1:
                    stop = src.find('}', pos)
                    if stop > -1: stop += 1
                if stop == -1:
                    var = src[pos:]
                else:
                    var = src[pos:stop]

                key = var[1:].replace('{', '').replace('}', '')
                src = src.replace(var, env[key])
                pos = src.find('$', pos)
            sources.append(src)

        for inc in includelist:
            pos = inc.find('$')
            while pos != -1:
                stop = inc.find('\\', pos)
                if stop == -1:
                    stop = inc.find('/', pos)
                if stop == -1:
                    stop = inc.find('}', pos)
                    if stop > -1: stop += 1
                if stop == -1:
                    var = inc[pos:]
                else:
                    var = inc[pos:stop]

                key = var[1:].replace('{', '').replace('}', '')
                inc = inc.replace(var, env[key])
                pos = inc.find('$', pos)
            includes.append(inc)
        text = True
        if sys.platform == "win32" or sys.platform == 'cygwin':
            cmd = ext_path('#/../tools/analysis_tools/Cppcheck/cppcheck.exe')
            html = True
        elif sys.platform == "linux2":
            cmd = ext_path('#/../tools/analysis_tools/Cppcheck/cppcheck')
            html = False
        options = ['--template=gcc', '--enable=all', '--std=posix', '--std=c99', '--language=c', '--suppress=missingIncludeSystem', '-D__GNUC__']
        if env['CPPCHECK_ALL_CFG'] == 'on':
            options.append('--force')
        else:
            options += ['-D%s' % (e) for e in env['CPPDEFINES']]
        options += ['-I%s' % (e) for e in includes]
        txt_file = os.path.join(build_dir, 'analysis', 'cppcheck', 'result.txt')

        if text:
            if not os.path.exists(os.path.dirname(txt_file)):
                os.makedirs(os.path.dirname(txt_file))
            args = [cmd] + options + sources
            f_err = open(txt_file, "wb")
            p = subprocess.Popen(
                args,
                stderr=f_err,
                universal_newlines = True)
            p.communicate()
            f_err.close()
            print "%s %s %s" % (cmd, options, sources)

        if html:
            import pip
            options.append('--xml')
            options.append('--xml-version=2')
            xml_file = os.path.join(build_dir, 'analysis', 'cppcheck', 'result.xml')
            html_report_tool = os.path.join(os.path.dirname(cmd), 'htmlreport', 'cppcheck-htmlreport.py')
            html_report_path  = os.path.join(os.path.dirname(xml_file), 'htmlreport')

            if not 'pygments' in [pkg.key for pkg in pip.get_installed_distributions()]:
                path = os.path.join(os.path.dirname(html_report_tool), 'Pygments-2.2.0-py2.py3-none-any.whl')
                pip.main(['install', path])

            if not os.path.exists(html_report_path):
                os.makedirs(html_report_path)
            args = [cmd] + options + sources

            f_err = open(xml_file, "wb")
            p = subprocess.Popen(
                                 args,
                                 stderr=f_err,
                                 universal_newlines = True)
            p.communicate()
            f_err.close()

            args = ["python", html_report_tool, "--file=" + xml_file, "--report-dir=" + html_report_path, "--source-dir=" + env['SRC_DIR'][0]] + env['SRC_DIR'][1:] + includes
            p = subprocess.Popen(args)
            p.communicate()
        fd = open(txt_file, 'r')
        print fd.read()
        fd.close()
        print "%s %s %s" % (cmd, ' '.join(options), ' '.join(sources))
    elif tool_name == 'flawfinder':
        sources = ' '.join(env['SRC_DIR'])
        cmd = ext_path('#/../tools/analysis_tools/flawfinder-1.31/flawfinder')
        options = "-H -C -c %s" % (sources)
        html_file = os.path.join(build_dir, 'analysis', 'flawfinder', 'result.html')

        if not os.path.exists(os.path.dirname(html_file)):
            os.makedirs(os.path.dirname(html_file))

        args = "python %s %s" % (cmd, options)
        f_out = open(html_file, "wb")
        p = subprocess.Popen(
                             args,
                             env=os.environ.copy(),
                             stdout=f_out,
                             shell=True,
                             universal_newlines=True)
        p.communicate()
        f_out.close()

#-----------------------------------------------------------
# build string
#-----------------------------------------------------------


build_string_file = '#../src/build/build_version.c'

def get_id_string():
    """ Return info line with logname + date + time
    """
    return os.environ.get('LOGNAME', '-') + \
        datetime.datetime.today().strftime(' %b %d %Y %H:%M:%S')

def get_git_string():
    """ Return info line with svn revision number
    """
    if SCons.Util.WhereIs('git') == None:
        return ''

    get_git_ver = subprocess.Popen(['git', 'describe', '--tags', '--always'], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    if get_git_ver.stderr.read().strip('\n\t\r') == '':
        git_ver = ' - git ' + get_git_ver.stdout.read().strip('\n\t\r').split('-g')[-1]
    else:
        git_ver = ''

    return git_ver

def build_version_cmd(target, source, env):
    """ SCons command generating the build_version.c file. This file must be generated;
        it cannot be commited because of its frequent modifications
    """

    f = open(target[0].path, 'wb')
    f.write('// automatically generated before each link\n' +
            'const char usr_build_date[64] = "' + get_id_string() + get_git_string() + '";\n')
    f.close()


def build_version_add(nodes, env, folder):
    build_string_file = os.path.join(folder, 'build_version.c')
    """ Register the command generating build_version.c and add it to the nodes
    """
    env.Command(build_string_file, nodes, build_version_cmd,
                PRINT_CMD_LINE_FUNC = outstr_date)

    nodes += [build_string_file]


build_ver_string_file = '../modules/common/src/co_version.c'

def build_sdk_version_update(env):
    """ Register the command generating build_version.c and add it to the nodes
    """
    f = open(build_ver_string_file, 'wb')
    f.write('// automatically generated before each link\n' +
            '#include "sdk_version.h"\n' +
            'const char sdk_version_str[] = SDK_VERSION_STR;\n' +
            'const char sdk_build_date[] = "' + get_id_string() + get_git_string() + '";\n' +
            'const char sdk_build_cmd[] = "' + env['BUILD_CMD'] + '";\n')
    f.close()


#-----------------------------------------------------------
# stop build
#-----------------------------------------------------------
def stop_build():
    """Parameter Error. """

    print("\nBuild Configuration Error!\n")

    sys.exit()
