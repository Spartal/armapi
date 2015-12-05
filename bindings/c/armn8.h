// ---------------------------------------------------------------------
// Created date: 17.11.2015
// ---------------------------------------------------------------------

/***********************************************************************

 Copyright (c) 2015 ATIM
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

***********************************************************************/

#ifndef ARM_N8_H
#define ARM_N8_H

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------
#include <stdbool.h>
#include "armport.h"

// ---------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------

/*!	\brief Constant to define the broadcast value.
 * 
 * 	Value for parameter \ref armN8SetRadioRemoteAdd() function.
 */
#define ARMN8_BROADCAST 		255

/*!	\brief Constant to define the auto power value.
 * 
 * 	Value for parameter \p power of \ref armN8SetRadioRemoteAdd() function.
 */
#define ARMN8_POWER_AUTO		-127

#ifndef __DOXYGEN__
	//Number of H registers
	#define _ARMN8_REGH_SIZE 	27
#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------

/*!	\brief Constant to define the errors.
 * 
 */
typedef enum
{
	ARMN8_ERR_NONE,						//!< No error.

	ARMN8_ERR_PORT_OPEN,				//!< Port Error, at the port opening.
	ARMN8_ERR_PORT_CONFIG,				//!< Port Error, at the port configuring.
	ARMN8_ERR_PORT_READ,				//!< Port Error, at the port reading.
	ARMN8_ERR_PORT_WRITE,				//!< Port Error, at the port writing.
	ARMN8_ERR_PORT_WRITE_READ,			//!< Port Error, at the port reading/writing.
	ARMN8_ERR_PORT_CLOSE,				//!< Port Error, at the port closing.

	ARMN8_ERR_SIGFOX_SEND_RECEIVE,		//!< Sigfox® Error, at the send/receive data to Sigfox.
	ARMN8_ERR_SIGFOX_DATA,				//!< Sigfox® Error, too date to send Sigfox.

	ARMN8_ERR_PARAM_OUT_OF_RANGE,		//!< Error, one or more of parameters is out of range.
	ARMN8_ERR_PARAM_INCOMPATIBLE,		//!< Error, the parameters is incompatible between them.
	ARMN8_ERR_ADDRESSING_NOT_ENABLE,	//!< Error, the addressing is not enable.
										//!< \note To fix this error, you can enable the addressing with \ref armN8EnableAddressing() function.
	ARMN8_ERR_WOR_ENABLE,				//!< Error, the WOR mode is enable.
										//!< \note To fix this error, you can disable the WOR mode with \ref armN8SetWorMode() function.

	ARMN8_ERR_ARM_GO_AT,				//!< \b ARM commend Error, can't switch to AT commend.
	ARMN8_ERR_ARM_BACK_AT,				//!< \b ARM commend Error, can't quit AT commend.
	ARMN8_ERR_ARM_CMD,					//!< \b ARM commend Error, from AT commend.
	ARMN8_ERR_ARM_GET_REG,				//!< \b ARM commend Error, from get register.
	ARMN8_ERR_ARM_SET_REG,				//!< \b ARM commend Error, from set register.
}armN8Error_t;

/*!	\brief Constant to define the baudrate value.
 * 
 */
typedef enum
{
	ARMN8_BAUDRATE_NONE		= 0,		//!< That is probably a error.
	ARMN8_BAUDRATE_1200		= 1200,		//!< 1200 bps.
	ARMN8_BAUDRATE_2400		= 2400,		//!< 2400 bps.
	ARMN8_BAUDRATE_4800		= 4800,		//!< 4800 bps.
	ARMN8_BAUDRATE_9600		= 9600,		//!< 9600 bps.
	ARMN8_BAUDRATE_19200	= 19200,	//!< 19200 bps.
	ARMN8_BAUDRATE_38400	= 38400,	//!< 38400 bps.
	ARMN8_BAUDRATE_57600	= 57600,	//!< 57600 bps.
	ARMN8_BAUDRATE_115200	= 115200,	//!< 115200 bps.
}armN8Baudrate_t;

/*!	\brief Constant to define the WOR mode 'Wake On Radio'.
 * 
 * \see armN8SetWorMode()
 */
typedef enum
{
	ARMN8_WOR_DISABLE,	//!< Disable WOR mode.
	ARMN8_WOR_LP,		//!< Enable long preamble for the transmitter, then wake up the receptor.
	ARMN8_WOR_CS,		//!< Enable WOR mode in 'Carrier Sense'.
						//!< \note The \b ARM is wake up on level rssi (choose this mode for speed).
	ARMN8_WOR_PQT		//!< Enable WOR mode in 'Preamble Quality Threshold'.
						//!< \note The \b ARM is wake up on the preamble (choose this mode for quality reception).
}armN8Wor_t;

/*!	\brief Constant to define the comportment of the LED.
 * 
 * \see armN8SetLed()
 */
typedef enum
{
	ARMN8_LED_OFF,		//!< The LED is 'off' all the time.
	ARMN8_LED_OFF_RF,	//!< The LED is 'off' on RF activity and 'on' other time.
	ARMN8_LED_ON_RF		//!< The LED is 'on' on RF activity and 'off' other time.
}armN8Led_t;

/*!	\brief Constant to define the LBT&AFA mode 'Listen before talk' and 'Adaptive Frequency Agility'.
 * 
 * \see armN8SetLbtAfaMode()
 */
typedef enum
{
	ARMN8_LBTAFA_DISABLE,	//!< Disable all LBT&AFA mode.
	ARMN8_LBTAFA_LBT,		//!< Enable Listen Before Talk .
	ARMN8_LBTAFA_AFA,		//!< Enable Adaptive Frequency Agility, is used to receive data on one channel of the two.
	ARMN8_LBTAFA_LBTAFA,	//!< Enable Listen Before Talk and adaptive Frequency Agility, listen on the tow channels and talk on the free channels.
}armN8LbtAfa_t;

// ---------------------------------------------------------------------
// struct
// ---------------------------------------------------------------------

#ifndef __DOXYGEN__
/*!	\brief Register struct, this struct a representation one register.
 * 
 */
typedef struct
{	
	uint8_t reg;	//!< A number of register.
	uint8_t val;	//!< A value of register.
	uint8_t newVal;	//!< A new value of register.
}armN8Reg_t;
#endif

/*!	\brief Arm struct, this struct is a representation one \b ARM module.
 * 
 */
typedef struct
{
	void* 		_port;						//!< Point to something for use the port for one \b ARM module.
	armN8Reg_t	_regsH[_ARMN8_REGH_SIZE];	//!< The registers used.
	int 		_maxPower;					//!< The max output radio power supported by \b ARM module.
}armN8_t;

// ---------------------------------------------------------------------
// Prototypes functions
// ---------------------------------------------------------------------

/*! \ingroup armn8_init_various
 * \brief Initialize the structure, port and \b ARM.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param port Pointer to something which mean you serial port.
 * 
 * \return Error available:
 * 		- \ref ARMN8_ERR_NONE If the initialization is success.
 * 		- \ref ARMN8_ERR_PORT_OPEN If the port can't open.
 * 		- \ref ARMN8_ERR_PORT_CONFIG If the port can't is configured.
 * 		- \ref ARMN8_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARMN8_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARMN8_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARMN8_ERR_ARM_CMD If can't execute commend from \b ARM
 * 		- \ref ARMN8_ERR_ARM_GET_REG If can't get register from \b ARM.
 * 		- \ref ARMN8_ERR_ARM_SET_REG If can't set register from \b ARM.
 */
armN8Error_t armN8Init(armN8_t* arm, void* port);

/*! \ingroup armn8_init_various
 * \brief De-initialize the port.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARMN8_ERR_NONE If the de-initialization is success.
 * 		- \ref ARMN8_ERR_PORT_CLOSE If the port can't close.
 */
armN8Error_t armN8DeInit(armN8_t* arm);

/*! \ingroup armn8_init_various
 * \brief Reboot the \b ARM.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARMN8_ERR_NONE If the reboot is success.
 * 		- \ref ARMN8_ERR_PORT_CONFIG If the port can't is configured.
 * 		- \ref ARMN8_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARMN8_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARMN8_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARMN8_ERR_ARM_CMD If can't execute commend from \b ARM
 * 		- \ref ARMN8_ERR_ARM_GET_REG If can't get register from \b ARM.
 * 		- \ref ARMN8_ERR_ARM_SET_REG If can't set register from \b ARM.
 * \todo Get max power
 */
armN8Error_t armN8Reboot(armN8_t* arm);

/*! \ingroup armn8_send_receive_data
 * \brief Send message to Sigfox network.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param bufTx The buffer of your data at send.
 * \param nbyteTx The number byte to send. \b Strictly less than or equal to 12.
 * \param bufRx The buffer of receive data, capacity's is must of 8 byte.
 * You can pass \b NULL is you don't want the acknowledge from Sigfox.
 * 
 * \return Error available:
 * 		- \ref ARMN8_ERR_NONE If the data have sent/receive correctly.
 * 		- \ref ARMN8_ERR_SIGFOX_SEND_RECEIVE If the data could not be send.
 * 		- \ref ARMN8_ERR_SIGFOX_DATA If \b nbyte bigger than 12.
 * 		- \ref ARMN8_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARMN8_ERR_PORT_READ If can't read through the port.
 * 		- \ref ARMN8_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARMN8_ERR_ARM_BACK_AT If can't back AT commend.
 * 
 * \warning If \p bufRx is not \b NULL and your \b ARM don't support the Sigfox in
 * downlink the \ref ARMN8_ERR_SIGFOX_SEND_RECEIVE is returned.
 * 
 * \todo Implement downlink.
 */
armN8Error_t armN8DataToSigfox(armN8_t* arm, const uint8_t* bufTx, size_t nbyteTx, uint8_t* bufRx);

/*! \ingroup armn8_unclassed
 * \brief Get The maximal possible power.
 * 
 * Get the maximal possible power of function channel and baudrate.
 * 
 * For more information, please consulate the main radio parameter page.
 * \todo Create the main parameter page.
 * 
 * \param radioChannel The radio channel.
 * \param radioBaud The radio baudrate.
 * 
 * \return The maximal power possible in dBm. -1 if no power possible.
 * 
 * \todo to implement.
 */
int8_t armN8GetMaxRadioPower(uint16_t radioChannel, armN8Baudrate_t radioBaud);

/*! \ingroup armn8_main_radio
 * \brief Setup the main radio configuration.
 * 
 * For more information, please consulate the main radio parameter page.
 * \todo Create the main parameter page.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param channel The main radio channel.
 * - The range possible is of 1 to 559.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * \param baud The radio baudrate.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if you give a another value defined below.
 * - Is possible to give a integer value. For example for \ref ARMN8_BAUDRATE_19200 you can directly give \b 19200.
 * - The possible value is:
 * 		- \ref ARMN8_BAUDRATE_1200 to 1200bps.
 * 		- \ref ARMN8_BAUDRATE_2400 to 2400bps.
 * 		- \ref ARMN8_BAUDRATE_4800 to 4800bps.
 * 		- \ref ARMN8_BAUDRATE_9600 to 9600bps.
 * 		- \ref ARMN8_BAUDRATE_19200 to 19200bps.
 * 		- \ref ARMN8_BAUDRATE_38400 to 38400bps.
 * 		- \ref ARMN8_BAUDRATE_57600 to 57600bps.
 * 		- \ref ARMN8_BAUDRATE_115200 to 115200bps.
 * 
 * \param power The radio output power.
 * - If you have a \b ARM in LD 'Long Distence' version the max value is 27 for 27dBm.
 * - If you have a \b ARM in LP 'Low Power' version the max value is 14 for 14dBm.
 * - The min value is -18 for -18dBm.
 * - You can passe the \ref ARMN8_POWER_AUTO value to set the max power according from the \p channel and \p baud parameter.
 * In this case, you can choose the \p channel and \p baud value without worry the \p power value.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * - \ref ARMN8_ERR_PARAM_INCOMPATIBLE The parameters of this function is link between them.
 * Is very important to chose the correct value. For more information, please consulate the main radio parameter page.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * \todo Create the main parameter page.
 * 
 * \see armN8GetRadio()
 */
armN8Error_t armN8SetRadio(armN8_t* arm, uint16_t channel, armN8Baudrate_t baud, int8_t power);

/*! \ingroup armn8_main_radio
 * \brief Get the main radio configuration.
 * 
 * Please, for more information about parameter consult the documentation of the \ref  armN8SetRadio() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param channel If the pointer is valid, the \p channel is set.
 * \param baud If the pointer is valid, the \p baud is set. If \ref ARMN8_BAUDRATE_NONE is set, there is probably a error.
 * \param power If the pointer is valid, the \p power is set. If the power is no particularity specified, the \ref ARMN8_POWER_AUTO value is set.
 * 
 * \see armN8SetRadio()
 */
void armN8GetRadio(armN8_t* arm, uint16_t* channel, armN8Baudrate_t* baud, int8_t* power);

/*! \ingroup armn8_addressing
 * \brief Set the radio remote address.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param add Remote address of 0 to 255. The 255 value is used for \e broadcast, the
 * macro ref ARMN8_BROADCAST (255) can be used in this case.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_ADDRESSING_NOT_ENABLE If the addressing is not enable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8GetRadioRemoteAdd()
 * \see armN8SetRadioLocalAdd()
 * \see armN8EnableAddressing()
 */
armN8Error_t armN8SetRadioRemoteAdd(armN8_t* arm, uint8_t add);

/*! \ingroup armn8_addressing
 * \brief Get the remote address.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The remote address.
 * 
 * \see armN8SetRadioRemoteAdd()
 */
uint8_t armN8GetRadioRemoteAdd(armN8_t* arm);

/*! \ingroup armn8_addressing
 * \brief Set the radio local address.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param add Local address of 0 to 255.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_ADDRESSING_NOT_ENABLE If the addressing is not enable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8GetRadioLocaleAdd()
 * \see armN8SetRadioRemoteAdd()
 * \see armN8EnableAddressing()
 */
armN8Error_t armN8SetRadioLocalAdd(armN8_t* arm, uint8_t add);

/*! \ingroup armn8_addressing
 * \brief Get the local address.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The local address.
 * 
 * \see armN8SetRadioLocalAdd()
 */
uint8_t armN8GetRadioLocaleAdd(armN8_t* arm);

/*! \ingroup armn8_addressing
 * \brief Enable/Disable \b Addressing.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Addressing or \e false to disable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8IsEnableAddressing()
 */
void armN8EnableAddressing(armN8_t* arm, bool enable);

/*! \ingroup armn8_addressing
 * \brief Get enable \b Addressing.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Addressing is enable or \e false if disable.
 * 
 * \see armN8EnableAddressing()
 */
bool armN8IsEnableAddressing(armN8_t* arm);

/*! \ingroup armn8_crc
 * \brief Enable/Disable \b CRC.
 * 
 * \warning This functions disable automatically the \b infinity \b mode.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b CRC or \e false to disable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8IsEnableCrc()
 * \see armN8EnableInfinityMode()
 */
void armN8EnableCrc(armN8_t* arm, bool enable);

/*! \ingroup armn8_crc
 * \brief Get enable \b CRC.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b CRC is enable or \e false if disable.
 * 
 * \see armN8EnableCrc()
 */
bool armN8IsEnableCrc(armN8_t* arm);
 
/*! \ingroup armn8_infinity_mode
 * \brief Enable/Disable \b Infinity \b mode.
 * 
 * \warning This functions disable automatically the \b CRC.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Infinity \b mode or \e false to disable.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_WOR_ENABLE If the WOR mode is enable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8IsEnableInfinityMode()
 * \see armN8EnableCrc()
 */
armN8Error_t armN8EnableInfinityMode(armN8_t* arm, bool enable);

/*! \ingroup armn8_infinity_mode
 * \brief Get enable \b Infinity \b mode.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Infinity \b mode is enable or \e false if disable.
 * 
 * \see armN8EnableInfinityMode()
 */
bool armN8IsEnableInfinityMode(armN8_t* arm);

/*! \ingroup armn8_whitening
 * \brief Enable/Disable \b Whitening.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Whitening false to disable.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8IsEnableWhitening()
 */
void armN8EnableWhitening(armN8_t *arm, bool enable);

/*! \ingroup armn8_whitening
 * \brief Get enable \b Whitening.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Whitening is enable or \e false if disable.
 * 
 * \see armN8EnableWhitening()
 */
bool armN8IsEnableWhitening(armN8_t *arm);

/*! \ingroup armn8_serial
 * \brief Setup serial port configuration.
 * 
 * \warning In the case or the port don't support one of below parameters,
 * this function don't return error. But, the error
 * \ref ARMN8_ERR_PORT_CONFIG will return to next call \ref armN8UpdateConfig().
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param baud The serial baudrate.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if
 * you give a another value defined below.
 * - If the wake up on uart is enable and the \p baud parameter is bigger
 * of 38400 the \ref ARMN8_ERR_PARAM_OUT_OF_RANGE error is returned.
 * - Is possible to give a integer value. For example for \ref ARMPORT_BAUDRATE_19200 you can directly give \b 19200.
 * - The possible value is:
 * 		- \ref ARMPORT_BAUDRATE_1200 to 1200bps.
 * 		- \ref ARMPORT_BAUDRATE_2400 to 2400bps.
 * 		- \ref ARMPORT_BAUDRATE_4800 to 4800bps.
 * 		- \ref ARMPORT_BAUDRATE_9600 to 9600bps.
 * 		- \ref ARMPORT_BAUDRATE_19200 to 19200bps.
 * 		- \ref ARMPORT_BAUDRATE_38400 to 38400bps.
 * 		- \ref ARMPORT_BAUDRATE_57600 to 57600bps.
 * 		- \ref ARMPORT_BAUDRATE_115200 to 115200bps.
 * 		- \ref ARMPORT_BAUDRATE_230400 to 230400bps.
 * 
 * \param databits The number of data bits:
 * 		- \ref ARMPORT_DATA_7BITS 7 data bits.
 * 		- \ref ARMPORT_DATA_8BITS 8 data bits.
 * 
 * \param parity The type of parity:
 * 		- \ref ARMPORT_PARITY_NO Disable parity.
 * 		- \ref ARMPORT_PARITY_ODD Enabled, odd parity 
 * 		- \ref ARMPORT_PARITY_EVEN Enabled, even parity.
 * 
 * \param stopbit The number of stop bits:
 * 		- \ref ARMPORT_STOPBIT_1 Enable 1 stop bit.
 * 		- \ref ARMPORT_STOPBIT_2 Enable 2 stop bit.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8GetSerial()
 * \see armN8EnableWakeUpUart()
 */
armN8Error_t armN8SetSerial(armN8_t* arm, armPortBaudrate_t baud, armPortDatabits_t databits, armPortParity_t parity, armPortStopbit_t stopbit);

/*! \ingroup armn8_serial
 * \brief Get the serial port configuration.
 * 
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param baud If the pointer is valid, the \p baud is set. If \ref ARMPORT_BAUDRATE_NONE is set, there is probably a error.
 * \param databits If the pointer is valid, the \p databits is set.
 * \param parity If the pointer is valid, the \p parity is set.
 * \param stopbit If the pointer is valid, the \p stopbit is set.
 * 
 * \see armN8SetSerial()
 */
 void armN8GetSerial(armN8_t* arm, armPortBaudrate_t* baud, armPortDatabits_t* databits, armPortParity_t* parity, armPortStopbit_t* stopbit);

/*! \ingroup armn8_power_saving
 * \brief Enable/Disable and configure the \b wake \b on \b radio mode.
 * 
 * \warning If \b ARMPORT_WITH_nSLEEP is not defined and the \p mode 
 * is \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT
 * this function enable the wake up on uart (see \ref armN8EnableWakeUpUart())
 * and change the serial baudrate if necessary. In other mode
 * (and if \b ARMPORT_WITH_nSLEEP is not defined) this function 
 * disable the wake up on uart.
 * \warning If you have the \b LBT mode enable (in \ref ARMN8_LBTAFA_LBT or
 * \ref ARMN8_LBTAFA_LBTAFA see \ref armN8SetLbtAfaMode()) and the
 * \p mode is \ref ARMN8_WOR_CS the \p rssiLevel
 * is the same register in \b ARM, so if change this value with this function,
 * the \p rssiLevel value of the \b LBT is also modified.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \param mode The value available:
 * - \ref ARMN8_WOR_DISABLE To disable the wake on radio mode. The other parameters is ignored.
 * - \ref ARMN8_WOR_LP To enable the long preamble, necessary for the
 * transmitter to wake up the receptor. The parameters \p rssiLevel and \p filterLongPreamble is ignored.
 * - \ref ARMN8_WOR_CS To enable the wake on radio in 'Carrier Sense'
 * (choose this mode for speed).
 * - \ref ARMN8_WOR_PQT To enable the wake on radio in 'Preamble Quality Threshold'
 * (choose this mode for quality reception). The parameter \p rssiLevel is ignored.
 * 
 * \param periodTime The period time in milliseconds.
 * - The maximal value possible is 900.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * - If the \p mode is \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT the \p periodTime
 * is the time between two wake up. If the condition of mode is check, the \b ARM keep awaken to receive the frame.
 * This value must be same of emitter (mode in \ref ARMN8_WOR_LP).
 * - If the \p mode is \ref ARMN8_WOR_LP the \p periodTime is the time of
 * emission long preamble. It is necessary to emit the loge preamble for considerate the wake-up period of the receiver.
 *  This value must be same of receptor (mode in \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT).
 * 
 * \param postTime The time in milliseconds where the WOR is disable.
 * - The maximal value possible is 2550.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * - In the case or \p mode is:
 * 		- \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT, the \p postTime is the time
 * here the \b ARM keep awaken after the receive the last frame.
 * 		- \ref ARMN8_WOR_LP after send the first frame with long preamble,
 * the next frames are send without long preamble. After the last frame send
 * and after the \p postTime the \b ARM send the next frame with long preamble.
 * 
 * \param rssiLevel This parameter in dBm is used by \ref ARMN8_WOR_CS (the default value is -95).
 * In \ref ARMN8_WOR_CS mode the wake up is generate by the rssi level. This Level
 * is configurable by \p rssiLevel parameter.
 * 
 * \param filterLongPreamble In the case where \p mode is \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT,
 * if \p filterLongPreamble is true the receive frames with long preamble is not push on the serial port.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * \note You need to call \ref armN8UpdateConfig() for update the parameters in you \b ARM.\n
 * After call \ref armN8UpdateConfig() functions, the \b ARM go to sleep:
 * - If the \b ARMPORT_WITH_nSLEEP is not defined. 
 * - If \b ARMPORT_WITH_nSLEEP is defined and sleep is enable (see \ref armN8Sleep()).
 * 
 * \see armN8GetWorMode()
 * \see armN8EnableWakeUpUart()
 * \see armN8SetLbtAfaMode()
 * \see armN8Sleep()
 */
 armN8Error_t armN8SetWorMode(armN8_t* arm, armN8Wor_t mode, uint16_t periodTime, uint16_t postTime, int8_t rssiLevel, bool filterLongPreamble);

/*! \ingroup armn8_power_saving
 * \brief Get the wake up on mode configuration.
 * 
 * Please, for more information about parameters consult the documentation of the \ref  armN8SetWorMode() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param mode If the pointer is valid, the \p mode is set.
 * \param periodTime If the pointer is valid, the \p periodTime is set. If
 * the \p mode is \ref ARMN8_WOR_DISABLE the value is not workable.
 * \param postTime If the pointer is valid, the \p postTime is set. If the
 * \p mode is \ref ARMN8_WOR_DISABLE the value is not workable.
 * \param rssiLevel If the pointer is valid, the \p rssiLevel is set. If
 * the \p mode is not \ref ARMN8_WOR_CS the value is not workable.
 * \param filterLongPreamble If the pointer is valid, the \p filterLongPreamble is set. If
 * the \p mode is \ref ARMN8_WOR_DISABLE or \ref ARMN8_WOR_LP the value is not workable.
 * 
 * \see armN8SetWorMode()
 */
 void armN8GetWorMode(armN8_t* arm, armN8Wor_t* mode, uint16_t* periodTime, uint16_t* postTime, int8_t* rssiLevel, bool* filterLongPreamble);

/*! \ingroup armn8_power_saving
 * \brief Enable/Disable the \b Wake \b Up \b Uart.
 * 
 * \warning The \b Wake \b Up \b Uart don't supporter the serially baudrate
 * upper than 38400 bps. This function set the baudrate at 38400bps if necessary.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Wake \b Up \b Uart false to disable.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_WOR_ENABLE If you went disable the \b Wake \b Up \b Uart (\p enable = false)
 * and the case here the \b ARMPORT_WITH_nSLEEP is
 * not define and the \b WOR is enable in \ref ARMN8_WOR_CS or \ref ARMN8_WOR_PQT.
 * 
 * \note The \b Wake \b Up \b Uart can be disable by \ref armN8SetWorMode().
 * \note You need to call \ref armN8UpdateConfig() for update the parameters in you \b ARM.\n
 * After call \ref armN8UpdateConfig() functions, the \b ARM go to sleep:
 * - If the \b ARMPORT_WITH_nSLEEP is not defined. 
 * - If \b ARMPORT_WITH_nSLEEP is defined and sleep is enable (see \ref armN8Sleep()).
 * 
 * \see armN8IsEnableWakeUpUart()
 * \see armN8SetWorMode()
 * \see armN8Sleep()
 */
armN8Error_t armN8EnableWakeUpUart(armN8_t *arm, bool enable);

/*! \ingroup armn8_power_saving
 * \brief Get enable \b Wake \b Up \b Uart.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Wake \b Up \b Uart is enable or \e false if disable.
 * 
 * \see armN8EnableWakeUpUart()
 */
bool armN8IsEnableWakeUpUart(armN8_t *arm);

#if defined ARMPORT_WITH_nSLEEP || defined __DOXYGEN__
/*! \ingroup armn8_power_saving
 * \brief Enable/Disable sleep with pin.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable sleep false to disable.
 * 
 * \note This function is defined only if \b ARMPORT_WITH_nSLEEP is defined.
 * \note The sleep must be disable if the \b Wake \b Up \b Uart is disable
 * and you went call \ref armN8Send() of \ref armN8UpdateConfig().
 * 
 * \see armN8EnableWakeUpUart();
 */
void armN8Sleep(armN8_t* arm, bool sleep);
#endif
 
/*! \ingroup armn8_lbt_afa_mode
 * \brief Enable/Disable and configure the \b Lbt&Afa mode.
 * 
 * \warning If you have the \b WOR mode enable (in \ref ARMN8_WOR_CS
 *  see \ref armN8SetWorMode()) and the
 * \p mode is not \ref ARMN8_LBTAFA_DISABLE the \p rssiLevel
 * is the same register in \b ARM, so if change this value with this function,
 * the \p rssiLevel value of the \b WOR mode is also modified.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \param mode The value available:
 * - \ref ARMN8_LBTAFA_DISABLE To disable the LBT&AFA mode. 
 * - \ref ARMN8_LBTAFA_LBT To enable Listen Before Talk mode. Use this to emit
 * on the radio if the rssi is less than \p rssiLevel.
 * - \ref ARMN8_LBTAFA_AFA To enable Adaptive Frequency Agility mode. Use this to receive
 * on one channel of the two (\p channel in \ref armN8SetRadio() and \p channel2).
 * - \ref ARMN8_LBTAFA_LBTAFA To enable Listen Before Talk and
 * adaptive Frequency Agility, listen on the tow channels (\p channel in
 * \ref armN8SetRadio() and \p channel2) and talk on the free channels.
 * 
 * \param rssiLevel This parameter in dBm is used by \ref ARMN8_LBTAFA_AFA and
 * \ref ARMN8_LBTAFA_LBTAFA (the default value is -95) for define the
 * level rssi who say if the channels is busy or not.
 * 
 * \param nSamples This is the number of rssi sample (the default value is 240).
 * 
 * \param channel2 The secondary channel, the primary channel
 * (and the other radio parameters) must be set with \ref armN8SetRadio() function.
 * - The range possible is of 1 to 559.
 * - The function, return the error \ref ARMN8_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \return Error available:
 * - \ref ARMN8_ERR_NONE If successful.
 * - \ref ARMN8_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * - \ref ARMN8_ERR_PARAM_INCOMPATIBLE The parameter \p channel2 of this function is link
 * with the parameters of the function \ref armN8SetRadio(). Is very important to chose the correct value.
 * For more information, please consulate the main radio parameter page
 * and the documentation of \ref armN8SetRadio() function.
 * 
 * \note To configured the other radio parameters please call \ref armN8SetRadio() function.
 * \note You need to call \ref armN8UpdateConfig() for update the parameters in you \b ARM.
 * 
 * \see armN8SetLbtAfaMode()
 * \see armN8SetRadio()
 * \see armN8SetWorMode()
 */
armN8Error_t armN8SetLbtAfaMode(armN8_t* arm, armN8LbtAfa_t mode, int8_t rssiLevel, uint16_t nSamples, uint16_t channel2);

/*! \ingroup armn8_lbt_afa_mode
 * \brief Get the wake up on mode configuration.
 * 
 * Please, for more information about parameters consult the documentation of the \ref  armN8SetLbtAfaMode() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param mode If the pointer is valid, the \p mode is set.
 * \param rssiLevel If the pointer is valid, the \p rssiLevel is set. If
 * the \p mode is \ref ARMN8_LBTAFA_DISABLE  the value is not workable.
 * \param nSamples If the pointer is valid, the \p nSamples is set. If
 * the \p mode is \ref ARMN8_LBTAFA_DISABLE  the value is not workable.
 * \param channel2 If the pointer is valid, the \p channel2 is set. If
 * the \p mode is \ref ARMN8_LBTAFA_DISABLE  the value is not workable.
 * 
 * \see armN8SetLbtAfaMode()
 */
void armN8GetLbtAfaMode(armN8_t* arm, armN8LbtAfa_t* mode, int8_t* rssiLevel, uint16_t* nSamples, uint16_t* channel2);

/*! \ingroup armn8_init_various
 * \brief Set the \a LED behavior.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param led The behavior of the \a LED:
 * 		- \ref ARMN8_LED_OFF, The \a LED is 'off' all the time.
 * 		- \ref ARMN8_LED_OFF_RF, The \a LED is 'off' on RF activity and 'on' other time.
 * 		- \ref ARMN8_LED_ON_RF, The \a LED is 'on' on RF activity and 'off' other time.
 * 
 * \note You need to call \ref armN8UpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armN8GetLed()
 */
void armN8SetLed(armN8_t* arm, armN8Led_t led);

/*! \ingroup armn8_init_various
 * \brief Get the \a LED behavior.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The behavior of the \a LED:
 * 		- \ref ARMN8_LED_OFF, The \a LED is 'off' all the time.
 * 		- \ref ARMN8_LED_OFF_RF, The \a LED is 'off' on RF activity and 'on' other time.
 * 		- \ref ARMN8_LED_ON_RF, The \a LED is 'on' on RF activity and 'off' other time.
 * 
 * \see armN8SetLed()
 */
armN8Led_t armN8GetLed(armN8_t* arm);

/*! \ingroup armn8_init_various
 * \brief Update the configuration in \b ARM.
 * 
 * None of parameters/modes previously configured, is no set in your \b ARM.
 * This function send/set the necessary registers to apply the previously
 * configuration and reconfigure the port if necessary.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARMN8_ERR_NONE If success.
 * 		- \ref ARMN8_ERR_PORT_CONFIG If the port can't is configured.
 * 		- \ref ARMN8_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARMN8_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARMN8_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARMN8_ERR_ARM_SET_REG If can't set register from \b ARM.
 */
armN8Error_t armN8UpdateConfig(armN8_t* arm);

/*! \ingroup armn8_send_receive_data
 * \brief Send data to \b ARM.
 * 
 * - In the case or the infinity mode is enable, this function send the data.
 * - In the case or the infinity mode is disable, the packet mode is enable,
 * this function send the data to the \b ARM, 120 byte by 120 byte and
 * wait the necessary time to send the data on the radio.
 * 
 * \warning You can use your method to write data to \b ARM (for example:
 * in interruption method), but you don't must influence on the behavior
 * of serial port when \ref armN8Init(), \ref armN8Reboot() or \ref armN8UpdateConfig() is call.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param buf The buffer.
 * \param nbyte The number of data to send.
 * 

 * 
 * \return The number of data write. -1 if error from the serial port.
 * 
 * \see armN8Receive()
 * \see armN8EnableInfinityMode()
 * \todo Finish implementation and add doc to explained the wait time
 * between send data.
 */
ssize_t armN8Send(armN8_t* arm, const uint8_t* buf, size_t nbyte);

/*! \ingroup armn8_send_receive_data
 * \brief Receive data from \b ARM.
 * 
 * This function is exit when the timeout is achieved from the last receive
 * data or if the \p nbyte is achieved.
 * 
 * \warning You can use your method to read data from \b ARM (for example:
 * in interruption method), but you don't must influence on the behavior
 * of serial port when \ref armN8Init(), \ref armN8Reboot() or \ref armN8UpdateConfig() is call.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param buf The buffer.
 * \param nbyte The size of buffer.
 * \param timeout The timeout.
 * 
 * \return The number of data read. -1 if error from the serial port.
 * 
 * \see armN8Send()
 */
ssize_t armN8Receive(armN8_t* arm, uint8_t* buf, size_t nbyte, int timeout);

#endif //ARM_N8_H
