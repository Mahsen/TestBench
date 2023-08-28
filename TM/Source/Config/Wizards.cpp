//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1401/8/12
Programmer : Mohammad Lotfi
Site : http://www.mahsen.ir
Tel : +989124662703
*/
//***************************************************************************************************************************************//
// <<< Use Configuration Wizard in Context Menu >>>
// <h> Config Wizards
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	<e> Hardware Version  SAA_0790_01_0396_03
#ifndef CONFIG_VERSIONHARDWARE_SAA_0790_01_0396_03
	#define CONFIG_VERSIONHARDWARE_SAA_0790_01_0396_03         1
#endif

#if(CONFIG_VERSIONHARDWARE_SAA_0790_01_0396_03)
//********************************************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
//--------------------------------------------------------------------------------
// <h> Application
//--------------------------------------------------------------------------------
// <h> TestBench
//  <s> Date Production
#ifndef TESTBENCH_DATE_PRODUCTION
	#define TESTBENCH_DATE_PRODUCTION            	    "0000-00-00"
#endif
//  <s> Version Hardware 
#ifndef TESTBENCH_VERSION_HARDWARE
	#define TESTBENCH_VERSION_HARDWARE            	    "v1.14020401"
#endif
//  <s> Version Software
#ifndef TESTBENCH_VERSION_SOFTWARE
	#define TESTBENCH_VERSION_SOFTWARE            	    "v1.14020605"
#endif
// <h> LED
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_LED_PORT
	#define TESTBENCH_LED_PORT            6
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_LED_PIN
	#define TESTBENCH_LED_PIN             7
#endif
// </h>
// <h> Get ID
// <h> Dec 1
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_GETID_DEC1_PORT
	#define TESTBENCH_GETID_DEC1_PORT            3
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_GETID_DEC1_PIN
	#define TESTBENCH_GETID_DEC1_PIN             7
#endif
// </h>
// <h> Dec 2 
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_GETID_DEC2_PORT
	#define TESTBENCH_GETID_DEC2_PORT            6
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_GETID_DEC2_PIN
	#define TESTBENCH_GETID_DEC2_PIN             9
#endif
// </h>
// <h> Dec 3
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_GETID_DEC3_PORT
	#define TESTBENCH_GETID_DEC3_PORT            6
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_GETID_DEC3_PIN
	#define TESTBENCH_GETID_DEC3_PIN             10
#endif
// </h>
// </h>
// <h> Relay 3-5
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_RELAY35_PORT
	#define TESTBENCH_RELAY35_PORT            3
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_RELAY35_PIN
	#define TESTBENCH_RELAY35_PIN             10
#endif
// </h>

// <h> Key
// <h> A
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_KEY_A_PORT
	#define TESTBENCH_KEY_A_PORT            2
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_KEY_A_PIN
	#define TESTBENCH_KEY_A_PIN             8
#endif
// </h>
// <h> Limit
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_KEY_LIMIT_PORT
	#define TESTBENCH_KEY_LIMIT_PORT            6
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_KEY_LIMIT_PIN
	#define TESTBENCH_KEY_LIMIT_PIN             9
#endif
// </h>
// </h>
// <h> Jac
// <h> EN1
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_EN1_PORT
	#define TESTBENCH_JAC_EN1_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_EN1_PIN
	#define TESTBENCH_JAC_EN1_PIN             1
#endif
// </h>
// <h> EN2
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_EN2_PORT
	#define TESTBENCH_JAC_EN2_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_EN2_PIN
	#define TESTBENCH_JAC_EN2_PIN             4
#endif
// </h>
// <h> I1
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_I1_PORT
	#define TESTBENCH_JAC_I1_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_I1_PIN
	#define TESTBENCH_JAC_I1_PIN             0
#endif
// </h>
// <h> I2
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_I2_PORT
	#define TESTBENCH_JAC_I2_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_I2_PIN
	#define TESTBENCH_JAC_I2_PIN             2
#endif
// </h>
// <h> I3
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_I3_PORT
	#define TESTBENCH_JAC_I3_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_I3_PIN
	#define TESTBENCH_JAC_I3_PIN             3
#endif
// </h>
// <h> I4
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef TESTBENCH_JAC_I4_PORT
	#define TESTBENCH_JAC_I4_PORT            4
#endif
//			 <o>Pin <0-15>
#ifndef TESTBENCH_JAC_I4_PIN
	#define TESTBENCH_JAC_I4_PIN             5
#endif
// </h>
// <h> Current
//			 <o> ADC
//					 <0x010A=> Channel 10b
#ifndef TESTBENCH_JAC_ADC_CHANNEL
	#define TESTBENCH_JAC_ADC_CHANNEL            0x010A
#endif
// </h>
// </h>
// <h> Test

// <h> ID 7
// <h> Media 
// <h> UI 
// <h> Media
//  <s> Name
#ifndef TESTBENCH_TEST_ID7_MEDIA_UI_NAME
	#define TESTBENCH_TEST_ID7_MEDIA_UI_NAME            		"UI"
#endif
//	 <h> Uart
//			 <o> Uart
//					 <1=> Uart1
//					 <2=> Uart2
//					 <3=> Uart3
//					 <4=> Uart4
//					 <5=> Uart5
//					 <6=> Uart6
#ifndef TESTBENCH_TEST_ID7_MEDIA_UI_UART
	#define TESTBENCH_TEST_ID7_MEDIA_UI_UART                          2
#endif
// </h>
// </h>
// </h>
// <h> RS485 
// <h> Media
//  <s> Name
#ifndef TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_NAME
	#define TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_NAME              "RS485"
#endif
//	 <h> Uart
//			 <o> Uart
//					 <1=> Uart1
//					 <2=> Uart2
//					 <3=> Uart3
//					 <4=> Uart4
//					 <5=> Uart5
//					 <6=> Uart6
#ifndef TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART
	#define TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART                  5
#endif
// </h>
// </h>
// </h>
// <h> OP 
// <h> Media
//  <s> Name
#ifndef TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_NAME
	#define TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_NAME            		"OP"
#endif
//	 <h> Uart
//			 <o> Uart
//					 <1=> Uart1
//					 <2=> Uart2
//					 <3=> Uart3
//					 <4=> Uart4
//					 <5=> Uart5
//					 <6=> Uart6
#ifndef TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART
	#define TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART                  4
#endif
// </h>
// </h>
// </h>
// </h>
// <h> Analog Input
// <h> Power to5v Voltage
//			 <o> ADC
//					 <0x0012=> Channel 18
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_TO5V_VOLTAGE_CHANNEL            0x0012  //B12
// </h>
// <h> 4v Voltage
//			 <o> ADC
//					 <0x0102=> Channel 2
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_4V_VOLTAGE_CHANNEL            0x0102 //F12
// </h>
// <h> RTC Voltage
//			 <o> ADC
//					 <0x0000=> Channel 0
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_RTC_VOLTAGE_CHANNEL            0x0000 //A0
// </h>




// <h> Power 220v Current
//			 <o> ADC
//					 <0x001C=> Channel 28
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_220V_CURRENT_CHANNEL            0x001C
// </h>
// <h> Power 12v Current
//			 <o> ADC
//					 <0x0009=> Channel 9
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_12V_CURRENT_CHANNEL            0x0009
// </h>
// <h> Power 12v Voltage
//			 <o> ADC
//					 <0x0008=> Channel 8
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_12V_VOLTAGE_CHANNEL            0x0008
// </h>
// <h> 3V3 Voltage
//			 <o> ADC
//					 <0x0002=> Channel 2
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_3V3_VOLTAGE_CHANNEL            0x0002
// </h>
// <h> GSM Voltage
//			 <o> ADC
//					 <0x000B=> Channel 11
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_GSM_VOLTAGE_CHANNEL            0x000B
// </h>
// <h> GSM EXT Voltage
//			 <o> ADC
//					 <0x001B=> Channel 27
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_GSM_EXT_VOLTAGE_CHANNEL            0x001B
// </h>
// <h> Batt Voltage
//			 <o> ADC
//					 <0x0003=> Channel 3
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_BATT_VOLTAGE_CHANNEL            0x0003
// </h>
// <h> LED Power Voltage
//			 <o> ADC
//					 <0x000C=> Channel 12
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_POWER_VOLTAGE_CHANNEL            0x000C
// </h>
// <h> LED RS485 Voltage
//			 <o> ADC
//					 <0x000D=> Channel 13
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_RS485_VOLTAGE_CHANNEL            0x000D
// </h>
// <h> LED NET1 Voltage
//			 <o> ADC
//					 <0x0000=> Channel 0
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_NET1_VOLTAGE_CHANNEL            0x0000
// </h>
// <h> LED NET2 Voltage
//			 <o> ADC
//					 <0x0001=> Channel 1
#define TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_NET2_VOLTAGE_CHANNEL            0x0001
// </h>
// </h>
// <h> Digital Input
// <h> N Reset
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_N_RESET_PORT            1
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_N_RESET_PIN             5
// </h>
// <h> F Reset
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_F_RESET_PORT            5
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_F_RESET_PIN             0
// </h>
// <h> LED Light
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_LED_LIGHT_PORT            5
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_LED_LIGHT_PIN             4
// </h>
// <h> Zero Cross Detect
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_ZERO_CROSS_DETECT_PORT            2
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_INPUT_ZERO_CROSS_DETECT_PIN             5
// </h>
// </h>
// <h> Digital Output
// <h> Power_220v_Test
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_TEST_PORT            7
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_TEST_PIN             2
// </h>
// <h> Power_220v_En
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_EN_PORT            0
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_EN_PIN             15
// </h>
// <h> Power_12v_Test
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_TEST_PORT            4
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_TEST_PIN             8
// </h>
// <h> Power_12v_En
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_EN_PORT            4
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_EN_PIN             7
// </h>
// <h> VBatt Enable
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_VBATT_ENABLE_PORT            6
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_VBATT_ENABLE_PIN             1
// </h>
// <h> Reset
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_RESET_PORT            6
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_RESET_PIN             0
// </h>
// <h> Zero Cross Gen
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_ZERO_CROSS_GEN_PORT            2
//			 <o>Pin <0-15>
#define TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_ZERO_CROSS_GEN_PIN             4
// </h>

// </h>
// </h>

// </h>
// <h> Task
//			 <o> Priority <1-255>
#ifndef TESTBENCH_Task_PRIORITY
	#define TESTBENCH_Task_PRIORITY            215
#endif
//			 <o> Stack Size <128-2048>
#ifndef TESTBENCH_Task_STAK_SIZE
	#define TESTBENCH_Task_STAK_SIZE            1536
#endif
// </h>
//  </h>
//--------------------------------------------------------------------------------
// </h>
// <h> Module
//--------------------------------------------------------------------------------
// <h> UI
// <h> Task
//			 <o> Priority <1-255>
#ifndef UI_MEDIA_Task_PRIORITY
	#define UI_MEDIA_Task_PRIORITY            216
#endif
//			 <o> Stack Size <128-2048>
#ifndef UI_MEDIA_Task_STAK_SIZE
	#define UI_MEDIA_Task_STAK_SIZE            1536
#endif
// </h>
// </h>
//--------------------------------------------------------------------------------
// </h>
// <h> Middle Module
//--------------------------------------------------------------------------------
// <e> Debug
#ifndef DEBUG_ENABLE
	#define DEBUG_ENABLE             0
#endif

// <e> Log File
#ifndef DEBUG_ENABLE_LOG
	#define DEBUG_ENABLE_LOG         0
#endif
// </e>

// <e> Alert
#ifndef DEBUG_ENABLE_ALERT
	#define DEBUG_ENABLE_ALERT       0
#endif

//	 <h> Uart
//			 <o> Uart
//					 <1=> Uart1
//					 <2=> Uart2
//					 <3=> Uart3
//					 <4=> Uart4
//					 <5=> Uart5
//					 <6=> Uart6
#ifndef DEBUG_UART
	#define DEBUG_UART               3
#endif

// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef DEBUG_BOUDRATE
	#define DEBUG_BOUDRATE           19200
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef DEBUG_DATABIT
	#define DEBUG_DATABIT            0x0000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef DEBUG_STOPBIT
	#define DEBUG_STOPBIT             0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef DEBUG_PARITY
	#define DEBUG_PARITY             0x0000
#endif
// </h>

//</h>

// </e>

// </e>
//--------------------------------------------------------------------------------
// <h> TaskTimer
//			 <o> Max Number of Functions <1-20>
#ifndef TASKTIMER_MAX_FUN
	#define TASKTIMER_MAX_FUN           4
#endif

//	 <h> Task
//			 <o> Priority <1-255>
#ifndef TASKTIMER_PRIORITY
	#define TASKTIMER_PRIORITY            250
#endif
//			 <o> Stack Size <128-2048>
#ifndef TASKTIMER_TASK_STAK_SIZE
	#define TASKTIMER_TASK_STAK_SIZE            512
#endif
//  </h>

// </h>
//--------------------------------------------------------------------------------
// <h> Media

// </h>
//--------------------------------------------------------------------------------
// <h> Task Manager

// </h>
//--------------------------------------------------------------------------------
// </h>
// <h> Driver
//--------------------------------------------------------------------------------
// <e> Watch dog timer
#ifndef WDT_ENABLE
	#define WDT_ENABLE             1
#endif

// <e> LED
#ifndef WDT_LED_ENABLE
	#define WDT_LED_ENABLE          1
#endif
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef WDT_LED_PORT
	#define WDT_LED_PORT            6
#endif
//			 <o>Pin <0-15>
#ifndef WDT_LED_PIN
	#define WDT_LED_PIN             8
#endif
//			 <o> Logic
//					 <0=> Low
//					 <1=> High
#ifndef WDT_LED_LOGIC
	#define WDT_LED_LOGIC          1
#endif
// </e>

// <e> BUZZER
#ifndef WDT_BUZZER_ENABLE
	#define WDT_BUZZER_ENABLE          0
#endif
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef WDT_BUZZER_PORT
	#define WDT_BUZZER_PORT            5
#endif
//			 <o>Pin <0-15>
#ifndef WDT_BUZZER_PIN
	#define WDT_BUZZER_PIN             15
#endif
//			 <o> Logic
//					 <0=> Low
//					 <1=> High
#ifndef WDT_BUZZER_LOGIC
	#define WDT_BUZZER_LOGIC          1
#endif
// </e>

//	 <h> Task
//			 <o> Priority <1-255>
#ifndef WDT_PRIORITY
	#define WDT_PRIORITY            1 //254
#endif
//			 <o> Stack Size <128-2048>
#ifndef WDT_Task_STAK_SIZE
	#define WDT_Task_STAK_SIZE            1024
#endif
//  </h>

// </e>
//--------------------------------------------------------------------------------
// <e> GPIOs
#ifndef GPIO_ENABLE
	#define GPIO_ENABLE           1
#endif


// <e> GPIOs Output
#ifndef GPIO_OUTPUT_ENABLE
	#define GPIO_OUTPUT_ENABLE           1
#endif
//			 <o> Max Output pin <0-10>
//   <i>Most functions can be added to output mode
#ifndef GPIO_OUTPUT_MAX
	#define GPIO_OUTPUT_MAX            10
#endif

//	 <h> Task Handel
//			 <o> Priority <1-255>
#ifndef GPIO_OUTPUT_PRIORITY
	#define GPIO_OUTPUT_PRIORITY            229
#endif
//			 <o> Stack Size <128-2048>
#ifndef GPIO_OUTPUT_TASK_STAK_SIZE
	#define GPIO_OUTPUT_TASK_STAK_SIZE            512
#endif
//  </h>

// </e>

// <e> GPIOs Input
#ifndef GPIO_INPUT_ENABLE
	#define GPIO_INPUT_ENABLE           1
#endif
//			 <o> Max Input pin <0-15>
//   <i>Most functions can be added to input mode
#ifndef GPIO_INPUT_MAX
	#define GPIO_INPUT_MAX            12
#endif


//	 <h> Task Handel
//			 <o> Priority <1-255>
#ifndef GPIO_INPUT_PRIORITY
	#define GPIO_INPUT_PRIORITY            230
#endif
//			 <o> Stack Size <128-2048>
#ifndef GPIO_INPUT_TASK_STAK_SIZE
	#define GPIO_INPUT_TASK_STAK_SIZE            512
#endif
//  </h>

// </e>

// </e>
//--------------------------------------------------------------------------------
// <h> Start Init UARTs
//	 <e> UART 1
#ifndef UART_1_ENABLE
	#define UART_1_ENABLE           1
#endif
// <h> TX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_1_TX_PINSEL_PORT
	#define UART_1_TX_PINSEL_PORT           1
#endif
//			 <o>Pin <0-15>
#ifndef UART_1_TX_PINSEL_PIN
	#define UART_1_TX_PINSEL_PIN            6
#endif
// </h>
// <h> RX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_1_RX_PINSEL_PORT
	#define UART_1_RX_PINSEL_PORT           1
#endif
//			 <o>Pin <0-15>
#ifndef UART_1_RX_PINSEL_PIN
	#define UART_1_RX_PINSEL_PIN            7
#endif
// </h>
//	 <e> WakeUp
#ifndef UART_1_WAKEUPINSLEEP
	#define UART_1_WAKEUPINSLEEP           0
#endif
//       </e>
// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef UART_1_BOUDRATE
	#define UART_1_BOUDRATE           9600
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef UART_1_DATABIT
	#define UART_1_DATABIT            0x0000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef UART_1_STOPBIT
	#define UART_1_STOPBIT            0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef UART_1_PARITY
	#define UART_1_PARITY            0x0000
#endif
// </h>
// 		<e> Buffer Soft FIFO
#ifndef UART_1_INT
	#define UART_1_INT                   1
#endif
//			 <o> Mode Send
//					 <0=> Normal
//					 <1=> Task (Real)
//					 <2=> DMA (Fast)
#ifndef UART_1_INT_SEND_MODE
	#define UART_1_INT_SEND_MODE            0
#endif
//			 <o> Send Priority <1-255>
#ifndef UART_1_INT_SEND_PRIORITY
	#define UART_1_INT_SEND_PRIORITY            100
#endif
//			 <o> Send(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_1_RING_BUFSIZE_TX
	#define UART_1_RING_BUFSIZE_TX            16
#endif
//			 <o> Receive Priority <0-15>
#ifndef UART_1_INT_RECEIVE_PRIORITY
	#define UART_1_INT_RECEIVE_PRIORITY            0
#endif
//			 <o> Receive(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_1_RING_BUFSIZE_RX
	#define UART_1_RING_BUFSIZE_RX            512
#endif
// 		</e>
//	 </e>

//	 <e> UART 2
#ifndef UART_2_ENABLE
	#define UART_2_ENABLE           1
#endif
// <h> TX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_2_TX_PINSEL_PORT
	#define UART_2_TX_PINSEL_PORT           3
#endif
//			 <o>Pin <0-15>
#ifndef UART_2_TX_PINSEL_PIN
	#define UART_2_TX_PINSEL_PIN            5
#endif
// </h>
// <h> RX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_2_RX_PINSEL_PORT
	#define UART_2_RX_PINSEL_PORT           3
#endif
//			 <o>Pin <0-15>
#ifndef UART_2_RX_PINSEL_PIN
	#define UART_2_RX_PINSEL_PIN            6
#endif
// </h>
//	 <e> WakeUp
#ifndef UART_2_WAKEUPINSLEEP
	#define UART_2_WAKEUPINSLEEP           1
#endif
//       </e>
// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef UART_2_BOUDRATE
	#define UART_2_BOUDRATE           4800
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef UART_2_DATABIT
	#define UART_2_DATABIT            0x2000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef UART_2_STOPBIT
	#define UART_2_STOPBIT            0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef UART_2_PARITY
	#define UART_2_PARITY            0x0400
#endif
// </h>
// 		<e> Buffer Soft FIFO
#ifndef UART_2_INT
	#define UART_2_INT                   1
#endif
//			 <o> Mode Send
//					 <0=> Normal
//					 <1=> Task (Real)
//					 <2=> DMA (Fast)
#ifndef UART_2_INT_SEND_MODE
	#define UART_2_INT_SEND_MODE            0
#endif
//			 <o> Send Priority <1-255>
#ifndef UART_2_INT_SEND_PRIORITY
	#define UART_2_INT_SEND_PRIORITY            100
#endif
//			 <o> Send(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_2_RING_BUFSIZE_TX
	#define UART_2_RING_BUFSIZE_TX            16
#endif
//			 <o> Receive Priority <0-15>
#ifndef UART_2_INT_RECEIVE_PRIORITY
	#define UART_2_INT_RECEIVE_PRIORITY            0
#endif
//			 <o> Receive(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_2_RING_BUFSIZE_RX
	#define UART_2_RING_BUFSIZE_RX            512
#endif
// 		</e>
//	 </e>


//	 <e> UART 3
#ifndef UART_3_ENABLE
	#define UART_3_ENABLE           1
#endif
// <h> TX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_3_TX_PINSEL_PORT
	#define UART_3_TX_PINSEL_PORT           3
#endif
//			 <o>Pin <0-15>
#ifndef UART_3_TX_PINSEL_PIN
	#define UART_3_TX_PINSEL_PIN            8
#endif
// </h>
// <h> RX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_3_RX_PINSEL_PORT
	#define UART_3_RX_PINSEL_PORT           3
#endif
//			 <o>Pin <0-15>
#ifndef UART_3_RX_PINSEL_PIN
	#define UART_3_RX_PINSEL_PIN            9
#endif
// </h>
//	 <e> WakeUp
#ifndef UART_3_WAKEUPINSLEEP
	#define UART_3_WAKEUPINSLEEP           0
#endif
//       </e>
// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef UART_3_BOUDRATE
	#define UART_3_BOUDRATE           9600
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef UART_3_DATABIT
	#define UART_3_DATABIT            0x1000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef UART_3_STOPBIT
	#define UART_3_STOPBIT            0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef UART_3_PARITY
	#define UART_3_PARITY            0x0400
#endif
// </h>
// 		<e> Buffer Soft FIFO
#ifndef UART_3_INT
	#define UART_3_INT                   1
#endif
//			 <o> Mode Send
//					 <0=> Normal
//					 <1=> Task (Real)
//					 <2=> DMA (Fast)
#ifndef UART_3_INT_SEND_MODE
	#define UART_3_INT_SEND_MODE            0
#endif
//			 <o> Send Priority <1-255>
#ifndef UART_3_INT_SEND_PRIORITY
	#define UART_3_INT_SEND_PRIORITY            100
#endif
//			 <o> Send(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_3_RING_BUFSIZE_TX
	#define UART_3_RING_BUFSIZE_TX            16
#endif
//			 <o> Receive Priority <0-15>
#ifndef UART_3_INT_RECEIVE_PRIORITY
	#define UART_3_INT_RECEIVE_PRIORITY            0
#endif
//			 <o> Receive(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_3_RING_BUFSIZE_RX
	#define UART_3_RING_BUFSIZE_RX            512
#endif
// 		</e>
//	 </e>

//	 <e> UART 4
#ifndef UART_4_ENABLE
	#define UART_4_ENABLE           1
#endif
// <h> TX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_4_TX_PINSEL_PORT
	#define UART_4_TX_PINSEL_PORT           2
#endif
//			 <o>Pin <0-15>
#ifndef UART_4_TX_PINSEL_PIN
	#define UART_4_TX_PINSEL_PIN            10
#endif
// </h>
// <h> RX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_4_RX_PINSEL_PORT
	#define UART_4_RX_PINSEL_PORT           2
#endif
//			 <o>Pin <0-15>
#ifndef UART_4_RX_PINSEL_PIN
	#define UART_4_RX_PINSEL_PIN            11
#endif
// </h>
//	 <e> WakeUp
#ifndef UART_4_WAKEUPINSLEEP
	#define UART_4_WAKEUPINSLEEP           0
#endif
//       </e>
// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef UART_4_BOUDRATE
	#define UART_4_BOUDRATE           9600
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef UART_4_DATABIT
	#define UART_4_DATABIT            0x0000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef UART_4_STOPBIT
	#define UART_4_STOPBIT            0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef UART_4_PARITY
	#define UART_4_PARITY            0x0000
#endif
// </h>
// 		<e> Buffer Soft FIFO
#ifndef UART_4_INT
	#define UART_4_INT                   1
#endif
//			 <o> Mode Send
//					 <0=> Normal
//					 <1=> Task (Real)
//					 <2=> DMA (Fast)
#ifndef UART_4_INT_SEND_MODE
	#define UART_4_INT_SEND_MODE            0
#endif
//			 <o> Send Priority <1-255>
#ifndef UART_4_INT_SEND_PRIORITY
	#define UART_4_INT_SEND_PRIORITY            100
#endif
//			 <o> Send(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_4_RING_BUFSIZE_TX
	#define UART_4_RING_BUFSIZE_TX            16
#endif
//			 <o> Receive Priority <0-15>
#ifndef UART_4_INT_RECEIVE_PRIORITY
	#define UART_4_INT_RECEIVE_PRIORITY            0
#endif
//			 <o> Receive(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_4_RING_BUFSIZE_RX
	#define UART_4_RING_BUFSIZE_RX            512
#endif
// 		</e>
//	 </e>

//	 <e> UART 5
#ifndef UART_5_ENABLE
	#define UART_5_ENABLE           1
#endif
// <h> TX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_5_TX_PINSEL_PORT
	#define UART_5_TX_PINSEL_PORT           2
#endif
//			 <o>Pin <0-15>
#ifndef UART_5_TX_PINSEL_PIN
	#define UART_5_TX_PINSEL_PIN            12
#endif
// </h>
// <h> RX PINSEL
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef UART_5_RX_PINSEL_PORT
	#define UART_5_RX_PINSEL_PORT           3
#endif
//			 <o>Pin <0-15>
#ifndef UART_5_RX_PINSEL_PIN
	#define UART_5_RX_PINSEL_PIN            2
#endif
// </h>
//	 <e> WakeUp
#ifndef UART_5_WAKEUPINSLEEP
	#define UART_5_WAKEUPINSLEEP           0
#endif
//       </e>
// <h> Data Packet
//			 <o> Boudrate
//					 <300=> 300
//					 <600=> 600
//					 <1200=> 1200
//					 <4800=> 4800
//					 <9600=> 9600
//					 <19200=> 19200
//					 <38400=> 38400
//					 <57600=> 57600
//					 <115200=> 115200
//					 <27000=> 27000
#ifndef UART_5_BOUDRATE
	#define UART_5_BOUDRATE           9600
#endif
//			 <o> Data Bit
//					 <0x2000=> 7
//					 <0x0000=> 8
//					 <0x1000=> 9
#ifndef UART_5_DATABIT
	#define UART_5_DATABIT            0x0000
#endif
//			 <o> Stop bits
//					 <0x1000=> 0.5
//					 <0x0000=> 1
//					 <0x3000=> 1.5
//					 <0x2000=> 2
#ifndef UART_5_STOPBIT
	#define UART_5_STOPBIT            0x0000
#endif
//			 <o> Parity
//					 <0x0000=> None
//					 <0x0400=> Even
//					 <0x0600=> Odd
#ifndef UART_5_PARITY
	#define UART_5_PARITY            0x0000
#endif
// </h>
// 		<e> Buffer Soft FIFO
#ifndef UART_5_INT
	#define UART_5_INT                   1
#endif
//			 <o> Mode Send
//					 <0=> Normal
//					 <1=> Task (Real)
//					 <2=> DMA (Fast)
#ifndef UART_5_INT_SEND_MODE
	#define UART_5_INT_SEND_MODE            0
#endif
//			 <o> Send Priority <1-255>
#ifndef UART_5_INT_SEND_PRIORITY
	#define UART_5_INT_SEND_PRIORITY            100
#endif
//			 <o> Send(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_5_RING_BUFSIZE_TX
	#define UART_5_RING_BUFSIZE_TX            16
#endif
//			 <o> Receive Priority <0-15>
#ifndef UART_5_INT_RECEIVE_PRIORITY
	#define UART_5_INT_RECEIVE_PRIORITY            0
#endif
//			 <o> Receive(bytes)
//					 <16=> 16
//					 <32=> 32
//					 <64=> 64
//					 <128=> 128
//					 <27=> 27
//					 <512=> 512
//					 <1024=> 1024
#ifndef UART_5_RING_BUFSIZE_RX
	#define UART_5_RING_BUFSIZE_RX            512
#endif
// 		</e>
//	 </e>
// </h>
//--------------------------------------------------------------------------------
// <e> TIMER
#ifndef TIMER_ENABLE
	#define TIMER_ENABLE             1
#endif
// </e>
//--------------------------------------------------------------------------------
// <h> SPI

// <e> SPI1
#ifndef SPI1_ENABLE
	#define SPI1_ENABLE    1
#endif
//  <h> SCK
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI1_SCK_PORT
	#define SPI1_SCK_PORT    4
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI1_SCK_PIN
	#define SPI1_SCK_PIN    13
#endif
//  </h>
//  <h> MISO
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI1_MISO_PORT
	#define SPI1_MISO_PORT    4
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI1_MISO_PIN
	#define SPI1_MISO_PIN    14
#endif
//  </h>
//  <h> MOSI
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI1_MOSI_PORT
	#define SPI1_MOSI_PORT    4
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI1_MOSI_PIN
	#define SPI1_MOSI_PIN    15
#endif
//  </h>
// </e>

// <e> SPI2
#ifndef SPI2_ENABLE
	#define SPI2_ENABLE    1
#endif
//  <h> SCK
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI2_SCK_PORT
	#define SPI2_SCK_PORT    3
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI2_SCK_PIN
	#define SPI2_SCK_PIN    1
#endif
//  </h>
//  <h> MISO
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI2_MISO_PORT
	#define SPI2_MISO_PORT    3
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI2_MISO_PIN
	#define SPI2_MISO_PIN    3
#endif
//  </h>
//  <h> MOSI
//			 <o> PINSEL Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SPI2_MOSI_PORT
	#define SPI2_MOSI_PORT    3
#endif
//			 <o> PINSEL Pin <0-15>
#ifndef SPI2_MOSI_PIN
	#define SPI2_MOSI_PIN    4
#endif
//  </h>
// </e>

// </h>
//--------------------------------------------------------------------------------
// <h> ADC

// <e> Channel 0
#ifndef ADC_CHANNEL0_ENABLE
	#define ADC_CHANNEL0_ENABLE    1
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL0_PORT
	#define ADC_CHANNEL0_PORT    0
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL0_PIN
	#define ADC_CHANNEL0_PIN    0
#endif
//  </e>

// <e> Channel 1
#ifndef ADC_CHANNEL1_ENABLE
	#define ADC_CHANNEL1_ENABLE    1
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL1_PORT
	#define ADC_CHANNEL1_PORT    0
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL1_PIN
	#define ADC_CHANNEL1_PIN    1
#endif
//  </e>

// <e> Channel 1b
#ifndef ADC_CHANNEL1B_ENABLE
	#define ADC_CHANNEL1B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL1B_PORT
	#define ADC_CHANNEL1B_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL1B_PIN
	#define ADC_CHANNEL1B_PIN    12
#endif
//  </e>

// <e> Channel 2
#ifndef ADC_CHANNEL2_ENABLE
	#define ADC_CHANNEL2_ENABLE    1
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL2_PORT
	#define ADC_CHANNEL2_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL2_PIN
	#define ADC_CHANNEL2_PIN    12
#endif
//  </e>

// <e> Channel 2b
#ifndef ADC_CHANNEL2B_ENABLE
	#define ADC_CHANNEL2B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL2B_PORT
	#define ADC_CHANNEL2B_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL2B_PIN
	#define ADC_CHANNEL2B_PIN    12
#endif
//  </e>

// <e> Channel 3
#define ADC_CHANNEL3_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL3_PORT    0
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL3_PIN    3
//  </e>

// <e> Channel 3b
#ifndef ADC_CHANNEL3B_ENABLE
	#define ADC_CHANNEL3B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL3B_PORT
	#define ADC_CHANNEL3B_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL3B_PIN
	#define ADC_CHANNEL3B_PIN    13
#endif
//  </e>

// <e> Channel 6b
#ifndef ADC_CHANNEL6B_ENABLE
	#define ADC_CHANNEL6B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL6B_PORT
	#define ADC_CHANNEL6B_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL6B_PIN
	#define ADC_CHANNEL6B_PIN    14
#endif
//  </e>

// <e> Channel 7b
#ifndef ADC_CHANNEL7B_ENABLE
	#define ADC_CHANNEL7B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL7B_PORT
	#define ADC_CHANNEL7B_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL7B_PIN
	#define ADC_CHANNEL7B_PIN    15
#endif
//  </e>

// <e> Channel 8
#define ADC_CHANNEL8_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL8_PORT    1
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL8_PIN    0
//  </e>

// <e> Channel 9
#define ADC_CHANNEL9_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL9_PORT    1
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL9_PIN    1
//  </e>

// <e> Channel 10
#define ADC_CHANNEL10_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL10_PORT    2
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL10_PIN    0
//  </e>

// <e> Channel 10b
#ifndef ADC_CHANNEL10B_ENABLE
	#define ADC_CHANNEL10B_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL10B_PORT
	#define ADC_CHANNEL10B_PORT    6
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL10B_PIN
	#define ADC_CHANNEL10B_PIN    2
#endif
//  </e>

// <e> Channel 11
#define ADC_CHANNEL11_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL11_PORT    2
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL11_PIN    1
//  </e>

// <e> Channel 12
#define ADC_CHANNEL12_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL12_PORT    2
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL12_PIN    2
//  </e>

// <e> Channel 13
#define ADC_CHANNEL13_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL13_PORT    2
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL13_PIN    3
//  </e>

// <e> Channel 18
#ifndef ADC_CHANNEL18_ENABLE
	#define ADC_CHANNEL18_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL18_PORT
	#define ADC_CHANNEL18_PORT    1
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL18_PIN
	#define ADC_CHANNEL18_PIN    12
#endif
//  </e>

// <e> Channel 19
#ifndef ADC_CHANNEL19_ENABLE
	#define ADC_CHANNEL19_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL19_PORT
	#define ADC_CHANNEL19_PORT    1
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL19_PIN
	#define ADC_CHANNEL19_PIN    13
#endif
//  </e>

// <e> Channel 27
#ifndef ADC_CHANNEL27_ENABLE
	#define ADC_CHANNEL27_ENABLE    1
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL27_PORT
	#define ADC_CHANNEL27_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL27_PIN
	#define ADC_CHANNEL27_PIN    6
#endif
//  </e>

// <e> Channel 28
#define ADC_CHANNEL28_ENABLE    1
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#define ADC_CHANNEL28_PORT    5
//	<o> PINSEL Pin <0-15>
#define ADC_CHANNEL28_PIN    7
//  </e>

// <e> Channel 30
#ifndef ADC_CHANNEL30_ENABLE
	#define ADC_CHANNEL30_ENABLE    0
#endif
//	<o> PINSEL Port
//		<0=> PORTA
//		<1=> PORTB
//		<2=> PORTC
//		<3=> PORTD
//		<4=> PORTE
//		<5=> PORTF
//		<6=> PORTG
//		<7=> PORTH
//		<8=> PORTI
//		<9=> PORTJ
//		<10=> PORTK
#ifndef ADC_CHANNEL30_PORT
	#define ADC_CHANNEL30_PORT    5
#endif
//	<o> PINSEL Pin <0-15>
#ifndef ADC_CHANNEL30_PIN
	#define ADC_CHANNEL30_PIN    9
#endif
//  </e>

// </h>
//--------------------------------------------------------------------------------

// <h> PWM
// <e> Timer 2 Channel 2
#define PWM_CHANNEL_2_2_ENABLE          1
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#define PWM_CHANNEL_2_2_PORT           1
//			 <o>Pin <0-15>
#define PWM_CHANNEL_2_2_PIN            8
// </e>
// </h>
//--------------------------------------------------------------------------------
// <h> Segment

// <h> Serial
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SEGMENT_SERIAL_PORT
	#define SEGMENT_SERIAL_PORT            2
#endif
//			 <o>Pin <0-15>
#ifndef SEGMENT_SERIAL_PIN
	#define SEGMENT_SERIAL_PIN             6
#endif
// </h>

// <h> Enable
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SEGMENT_ENABLE_PORT
	#define SEGMENT_ENABLE_PORT            2
#endif
//			 <o>Pin <0-15>
#ifndef SEGMENT_ENABLE_PIN
	#define SEGMENT_ENABLE_PIN             7
#endif
//			 <o> Logic
//					 <0=> Low
//					 <1=> High
#ifndef SEGMENT_ENABLE_LOGIC
	#define SEGMENT_ENABLE_LOGIC          0
#endif
// </h>

// <h> Load Right
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SEGMENT_LOADRIGHT_PORT
	#define SEGMENT_LOADRIGHT_PORT            2
#endif
//			 <o>Pin <0-15>
#ifndef SEGMENT_LOADRIGHT_PIN
	#define SEGMENT_LOADRIGHT_PIN             8
#endif
//			 <o> Logic
//					 <0=> Low
//					 <1=> High
#ifndef SEGMENT_LOADRIGHT_LOGIC
	#define SEGMENT_LOADRIGHT_LOGIC          1
#endif
// </h>

// <h> Load Left
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SEGMENT_LOADLEFT_PORT
	#define SEGMENT_LOADLEFT_PORT            2
#endif
//			 <o>Pin <0-15>
#ifndef SEGMENT_LOADLEFT_PIN
	#define SEGMENT_LOADLEFT_PIN             9
#endif
//			 <o> Logic
//					 <0=> Low
//					 <1=> High
#ifndef SEGMENT_LOADLEFT_LOGIC
	#define SEGMENT_LOADLEFT_LOGIC          1
#endif
// </h>

// <h> Clock
//			 <o> Port
//					 <0=> PORTA
//					 <1=> PORTB
//					 <2=> PORTC
//					 <3=> PORTD
//					 <4=> PORTE
//					 <5=> PORTF
//					 <6=> PORTG
//					 <7=> PORTH
//					 <8=> PORTI
//					 <9=> PORTJ
//					 <10=> PORTK
#ifndef SEGMENT_CLOCK_PORT
	#define SEGMENT_CLOCK_PORT            0
#endif
//			 <o>Pin <0-15>
#ifndef SEGMENT_CLOCK_PIN
	#define SEGMENT_CLOCK_PIN             8
#endif
// </h>

// </h>
//--------------------------------------------------------------------------------

// </h>
//--------------------------------------------------------------------------------
//********************************************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

#endif
// </e>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if((CONFIG_VERSIONHARDWARE_v2_13950701+CONFIG_VERSIONHARDWARE_v3_13950901+CONFIG_VERSIONHARDWARE_v4_13960101+CONFIG_VERSIONHARDWARE_SAA_0790_01_0396_03)>1)
#error "You can only use a selection option"
#endif

// </h>
// <<< end of configuration section >>>
