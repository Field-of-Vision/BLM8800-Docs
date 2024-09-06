#!/bin/sh

# Input arg will be in three:
#    1: list                      ## input 'list' will echo Genlib_Target
#    2: name in Genlib_Target <-e>## input number in Genlib_Target will build selected target, "-e" means to the end
#    3: ''                        ## input none will build all target
#    4: clean                     ## clean all  in target

Genlib_Target=(
    'target_test'
    'target_wifi'
    'target_wifi_tls'
    'target_wifi_rawdata'
    'target_wifi_sntp'
    'target_wifi_http_ota'
    'target_wifi_lowpower'
    'target_wifi_wapi'
    'target_wifi_csi'
    'target_wifi_audio'
    'target_wifi_fhostif'
    'target_8800a_wifi_audio'
    'target_dev_wifi'
    'target_m2d'
    'target_dwb'
    'target_ble'
    'target_bt'
    'target_bt_usb'
    'target_tws'
    'target_btdm'
    'target_bt_wifi_audio'
    'target_wifi_ble_smartconfig'
    'target_ble_wifi_fhostif'
    'target_btdm_wifi'
    )
Select_Target=''
Print_Array=()
Array_Offset=1
Select_Offset=0
ToEnd_Target=0
Build_Fail=0

if [ "$1" == "clean" ]; then
    echo 'clean all target '
    for i in ${Genlib_Target[@]}
    do
        Select_Target=$i
        echo $Select_Target
        cd $Select_Target
        #rm -rf ./lib/armgcc_4_8/*.a
        cd ..
    done
elif [ "$1" == "list" ]; then
    echo 'list target name'
    for i in ${Genlib_Target[@]}
    do
        Select_Target=$i
        echo $Select_Target
    done
else
    opt=''
    for choice in ${Genlib_Target[@]}; do
        if [ "$1" == "$choice" ]; then
            Select_Target=$1
            echo $Select_Target
            if [ $# -gt 1 ]; then
                if [ "$2" == "-e" ]; then
                    ToEnd_Target=1
                    if [ $# -gt 2 ]; then
                        opt=$3
                    fi
                else
                    opt=$2
                fi
            fi
            break
        fi
        let Select_Offset+=1
    done

    if [ "$Select_Target" != "" -a $ToEnd_Target -eq 0 ]; then
        echo build $Select_Target lib
        cd $Select_Target
        ./build_tgt.sh $opt
        if [ $? -eq 0 ]; then
            echo $Select_Target 'build  succeed'
        else
            echo $Select_Target 'build  failed'
            Build_Fail=1
        fi
        cd ..
    else
        if [ $Select_Target ]; then
            echo 'build' $Select_Target 'to the end target, offset:' $Select_Offset
        else
            echo 'build all'
            Select_Offset=0
            opt=$@
        fi
        for i in ${Genlib_Target[@]}
        do
            if [ $Select_Offset -ge $Array_Offset ]; then
                echo 'skip' $i
                let Array_Offset+=1
                continue
            fi
            Select_Target=$i
            echo $Select_Target
            cd $Select_Target
            ./build_tgt.sh $opt
            if [ $? -eq 0 ]; then
                Print_Array[$Array_Offset]=$Select_Target' build  succeed'
                #echo $Select_Target 'build  succeed'
            else
                Print_Array[$Array_Offset]=$Select_Target' build  failed'
                #echo $Select_Target 'build  failed'
                Build_Fail=1
                break
            fi
            let Array_Offset+=1
            cd ..
        done
        for j in $(seq 1 $Array_Offset)
        do
            if [ $Select_Offset -ge $j ]; then
                continue
            fi
            echo ${Print_Array[$j]}
        done
    fi
fi

if [ $Build_Fail -ne 0 ]; then
    exit 1
fi
