
1_Datasheet 目录包含MM32F3270的Datasheet
    DS_MM32F3270_V0.7_SC.pdf
2_UserManual目录包含MM32F3270的User Manual
    UM_MM32F3270_V0.5.pdf

3_Lib_Samples包含MM32F3270_Lib_Samples代码包

    本代码包支持iar和keil两种集成开发环境, 提供mm32f327x平台基本样例工程及驱动程序.

    代码包下主要目录结构如下:

    - Demo_app

    大模块的样例工程, 目前包含以太网和USB的工程.

    以Freertos_http工程为例, 基于keil的工程位于目录"MM32F327x_Samples\Demo_app\Ethernet_Demo\ETH_RTOS\Freertos_http\KEILPRJ\Freertos_http.uvprojx".

    - Device

    与芯片硬件的源代码, 例如寄存器头文件等.

    - MM32F327x_Samples

    基本外设模块的样例工程

    以ADC_BasicExample工程为例, 基于keil的工程位于目录"MM32F327x_Samples\RegSamples\ADC\ADC_BasicExample\KEILPRJ\ADC_BasicExample.uvprojx".

4_Pack(KEIL&IAR)包含KEIL和IAR的Pack包，安装即可支持KEIL和IAR
    MindMotion.MM32F3270_DFP.1.0.3.pack
    MM32_IAR_EWARM_pack_Ver1.51.zip

5_Demo_Board 目录下有如下硬件原理图和说明
    MM32F3270_CoreBoard144.zip
    MM32F3276C7P_eMiniBoard_MB-036.zip
    MM32F3276G9P_EVB_MB-039.zip