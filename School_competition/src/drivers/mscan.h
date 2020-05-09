/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file mscan.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Oct. 25, 2013
*
* @brief header file for MSCAN module utilities (MSCAN). 
*
*******************************************************************************
*
* provide APIs for accessing MSCAN module (MSCAN)
******************************************************************************/
#ifndef _MSCAN_H__
#define _MSCAN_H__
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/
/******************************************************************************
* define MSCAN Data Buffer Frame status
*
*//*! @addtogroup data_buffer_frame_list
* @{
*******************************************************************************/
#define BUFFER_FRAME_INVALID				0x00	/*!< data frame is invalid */
#define BUFFER_FRAME_VALID					0x55	/*!< data frame is valid */
/*! @} End of data_buffer_frame_list							*/


/******************************************************************************
* define MSCAN baud rate 
*
*//*! @addtogroup baud_rate_list
* @{
*******************************************************************************/
#define BAUD_RATE_SJW             	SJW_3TQ	/*!< 1 set Synchronization Jump Width. */
#define BAUD_RATE_BRP				0		/*!< 1 Baud Rate Prescaler */	
#define BAUD_RATE_SAMP				0		/*!< 0-One sample per bit, 1-three sample per bit. */	
#define BAUD_RATE_TSEG1				TSEG_10  /*!< Time Segment 1*/
#define BAUD_RATE_TSEG2				TSEG_7  /*!< Time Segment 2*/
#define BAUD_RATE_CLOCK				8000000L/*!< clock source for MSCAN*/
#define Baud_RATE					BAUD_RATE_CLOCK/(BAUD_RATE_BRP+1)/\
									(BAUD_RATE_SJW+1)/(3 + BAUD_RATE_TSEG1+\
									BAUD_RATE_TSEG2)
/*! @} End of baud_rate_list													*/

/******************************************************************************
* define MSCAN receiver and transmitter buffer length
*
*//*! @addtogroup can_buffer_length_list
* @{
*******************************************************************************/
#define MSCAN_RX_BUFFER_LENGTH			5		/*!< 5 buffer for mscan receiver*/
#define MSCAN_TX_BUFFER_LENGTH			3		/*!< 5 buffer for mscan transmitter*/

/*! @} End of can_buffer_length_list    */


/******************************************************************************
* define MSCAN Synchronization Jump Width
*
*//*! @addtogroup Syn_Jump_Width_list
* @{
*******************************************************************************/
#define SJW_1TQ                        0x00			/*!< 1 Tq clock cycle. */
#define SJW_2TQ                        0x01			/*!< 2 Tq clock cycle. */
#define SJW_3TQ                        0x02			/*!< 3 Tq clock cycle. */
#define SJW_4TQ                        0x03			/*!< 4 Tq clock cycle. */

/*! @} End of Syn_Jump_Width_list                                             		*/



/******************************************************************************
* define Time Segment
*
*//*! @addtogroup Time_Segment_list
* @{
*******************************************************************************/
#define TSEG_1						   0x00			/*!< 1 Tq clock cycle. */
#define TSEG_2						   0x01			/*!< 2 Tq clock cycle. */
#define TSEG_3						   0x02			/*!< 3 Tq clock cycle. */
#define TSEG_4						   0x03			/*!< 4 Tq clock cycle. */
#define TSEG_5						   0x04			/*!< 5 Tq clock cycle. */
#define TSEG_6						   0x05			/*!< 6 Tq clock cycle. */
#define TSEG_7						   0x06			/*!< 7 Tq clock cycle. */
#define TSEG_8						   0x07			/*!< 8 Tq clock cycle. */
#define TSEG_9						   0x08			/*!< 9 Tq clock cycle. */
#define TSEG_10						   0x09			/*!< 10 Tq clock cycle. */
#define TSEG_11						   0x0a			/*!< 11 Tq clock cycle. */
#define TSEG_12						   0x0b			/*!< 12 Tq clock cycle. */
#define TSEG_13						   0x0c			/*!< 13 Tq clock cycle. */
#define TSEG_14						   0x0d			/*!< 14 Tq clock cycle. */
#define TSEG_15						   0x0e			/*!< 15 Tq clock cycle. */
#define TSEG_16						   0x0f			/*!< 16 Tq clock cycle. */

/*! @} End of Time_Segment_list                                             		*/


/******************************************************************************
* define MSCAN Receiver Status
*
*//*! @addtogroup can_receiver_status_list
* @{
*******************************************************************************/
#define RECEIVER_STATUS_RXOK	0<<4		/*!<0¡Üreceive error counter<96*/
#define RECEIVER_STATUS_RXWRN	1<<4		/*!<96¡Üreceive error counter<128*/
#define RECEIVER_STATUS_RXERR	2<<4		/*!<128¡Üreceive error counter*/
#define RECEIVER_STATUS_RXBUS_OFF	3<<4	/*!<256¡Ütransmit error counter1*/

/*! @} End of can_receiver_status_list                                             		*/

/******************************************************************************
* define MSCAN Transmitter Status
*
*//*! @addtogroup can_transmitter_status_list
* @{
*******************************************************************************/
#define TRANSMITTER_STATUS_TXOK			0<<2		/*!<0¡Ütransmit error counter<96*/
#define TRANSMITTER_STATUS_TXWRN		1<<2		/*!<96¡Ütransmit error counter<128*/
#define TRANSMITTER_STATUS_TXERR		2<<2		/*!<128¡Ütransmit error counter*/
#define TRANSMITTER_STATUS_TXBUS_OFF	3<<2		/*!<256¡Ütransmit error counter1*/

/*! @} End of can_transmitter_status_list                                              */

/******************************************************************************
* define MSCAN Transmitter Buffer Empty Flag
*
*//*! @addtogroup can_transmitter_buffer_empty_flag_list
* @{
*******************************************************************************/
#define TRANSMITTER_TX0_EMPTY			1<<0		/*!<transmitter 0 empty*/
#define TRANSMITTER_TX1_EMPTY			1<<1		/*!<transmitter 1 empty*/
#define TRANSMITTER_TX2_EMPTY			1<<2		/*!<transmitter 2 empty*/
#define TRANSMITTER_TX_NO_EMPTY			0			/*!<all transmitter are not empty*/

/*! @} End of can_transmitter_buffer_empty_flag_list                                             	*/
/******************************************************************************
* define MSCAN Transmitter Empty Interrupt Enable
*
*//*! @addtogroup can_transmitter_empty_int_list
* @{
*******************************************************************************/
#define TRANSMITTER_TX0_EMPTY_INT_EN	1<<0		/*!<transmitter 0 empty interrupt enable*/
#define TRANSMITTER_TX1_EMPTY_INT_EN	1<<1		/*!<transmitter 1 empty interrupt enable*/
#define TRANSMITTER_TX2_EMPTY_INT_EN	1<<2		/*!<transmitter 2 empty interrupt enable*/

/*! @} End of can_transmitter_empty_int_list                                             	*/
/******************************************************************************
* define MSCAN Transmitter Message Abort Request
*
*//*! @addtogroup can_transmitter_message_abort_list
* @{
*******************************************************************************/
#define TRANSMITTER_TX0_REQEST_ABORT	1<<0		/*!<request transmitter 0 to be aborted*/
#define TRANSMITTER_TX1_REQEST_ABORT	1<<1		/*!<request transmitter 1 to be aborted*/
#define TRANSMITTER_TX2_REQEST_ABORT	1<<2		/*!<request transmitter 2 to be aborted*/

/*! @} End of can_transmitter_message_abort_list                                             	*/
/******************************************************************************
* define MSCAN Transmitter Message Abort Acknowledge
*
*//*! @addtogroup can_transmitter_message_abort_flag_list
* @{
*******************************************************************************/
#define TRANSMITTER_TX0_ABORT_FLAG	1<<0		/*!<transmitter 0 to be aborted*/
#define TRANSMITTER_TX1_ABORT_FLAG	1<<1		/*!<transmitter 1 to be aborted*/
#define TRANSMITTER_TX2_ABORT_FLAG	1<<2		/*!<transmitter 2 to be aborted*/

/*! @} End of can_transmitter_message_abort_flag_list                                             	*/
/******************************************************************************
* define MSCAN Identifier Acceptance Mode
*
*//*! @addtogroup can_identifier_acceptance_mode_list
* @{
*******************************************************************************/
#define ID_ACCEPT_MODE_TWO32    	0<<4		/*!<Two 32-bit acceptance filters*/
#define ID_ACCEPT_MODE_FOUR16    	1<<4		/*!<Four 16-bit acceptance filters*/
#define ID_ACCEPT_MODE_EIGHT8    	2<<4		/*!<Eight 8-bit acceptance filters*/
#define ID_ACCEPT_MODE_FILTER_CLOSE 3<<4		/*!<Filter closed*/

/*! @} End of can_identifier_acceptance_mode_list                                             	*/

/******************************************************************************
* define MSCAN Identifier Acceptance Hit Indicator
*
*//*! @addtogroup can_identifier_acceptance_hit_list
* @{
*******************************************************************************/
#define ID_ACCEPT_FILTER0_HIT    	0		/*!<Filter 0 hit*/
#define ID_ACCEPT_FILTER1_HIT    	1		/*!<Filter 1 hit*/
#define ID_ACCEPT_FILTER2_HIT    	2		/*!<Filter 2 hit*/
#define ID_ACCEPT_FILTER3_HIT    	3		/*!<Filter 3 hit*/
#define ID_ACCEPT_FILTER4_HIT    	4		/*!<Filter 4 hit*/
#define ID_ACCEPT_FILTER5_HIT    	5		/*!<Filter 5 hit*/
#define ID_ACCEPT_FILTER6_HIT    	6		/*!<Filter 6 hit*/
#define ID_ACCEPT_FILTER7_HIT    	7		/*!<Filter 7 hit*/

/*! @} End of can_identifier_acceptance_mode_list                                             	*/


/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/


/******************************************************************************
*
*//*! @addtogroup mscan_setting_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN setting type.
 *
 */
typedef struct
{
	uint16_t bStopEn        :1;     			/*!< 1: The module ceases to be clocked during wait mode. */
	uint16_t bTimerEn       :1;    				/*!< Enable internal MSCAN timer for timer stamp */
	uint16_t bWakeUpEn      :1;     			/*!< MSCAN wake up enable */
	uint16_t bCanEn		    :1;     			/*!< MSCAN Enable */
	uint16_t bCLKSRC	    :1;     			/*!< MSCAN Clock Source, bus clock or oscillator clock*/
	uint16_t bLoopModeEn    :1;     			/*!< Loopback Self Test Mode */
	uint16_t bWUPM	        :1;     			/*!< WakeUp Mode */
	uint16_t bListenModeEn  :1;     			/*!< enable Listen Only Mode */
	uint16_t bWakeUpIEn		:1;    				/*!< WakeUp Interrupt Enable */
	uint16_t bStatusChangeIEn:1;  				/*!< CAN Status Change Interrupt Enable */
	uint16_t bRxStatusChangeIEn:1;  			/*!< CAN receive Status Change Interrupt Enable */
	uint16_t bTxStatusChangeIEn:1;  			/*!< CAN transmitter Status Change Interrupt Enable */
    uint16_t bOverRunIEn    :1;					/*!< Overrun Interrupt Enable */
    uint16_t bRxFullIEn		:1;					/*!< Receiver Full Interrupt Enable */
    uint16_t bTxEmptyIEn	:1;					/*!< Transmitter Empty Interrupt Enable */
    uint16_t bBusOffUser    :1;                 /*!< Bus off recovery mode, 1 - user, 0 - Auto */
}MSCAN_SettingType;
/*! @} End of mscan_setting_type                                       						*/

/******************************************************************************
*
*//*! @addtogroup mscan_baudrate_setting_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN baud rate setting type.
 *
 */
typedef struct
{
	uint16_t SJW        :2;     			/*!< Synchronization Jump Width. */
	uint16_t BRP		:6;					/*!< Baud Rate Prescaler. */
	uint16_t SAMP       :1;					/*!< Sampling. */
	uint16_t TSEG2      :3;					/*!< Time Segment 2. */
	uint16_t TSEG1      :4;					/*!< Time Segment 1. */
}MSCAN_BaudRateSettingType;
/*! @} End of mscan_baudrate_setting_type                                       				*/



/******************************************************************************
*
*//*! @addtogroup mscan_config_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN configure type.
 *
 */
typedef struct
{
    MSCAN_SettingType 			sSetting;			/*!< can setting structure */
    MSCAN_BaudRateSettingType	sBaudRateSetting; /*!< can baud rate setting structure */
    uint8_t u8IDARMode;         /*!< Set  Identifier Acceptance Mode */
    uint8_t u8IDARHit;			/*!< Set  Identifier Acceptance Hit Indicator */
    uint32_t u32IDAR0;			/*!< MSCAN Identifier Acceptance Register n of First Bank */
    uint32_t u32IDAR1;			/*!< MSCAN Identifier Acceptance Register n of Second Bank */
    uint32_t u32IDMR0;			/*!< MSCAN Identifier Mask Register n of First Bank */
    uint32_t u32IDMR1;			/*!< MSCAN Identifier Mask Register n of Second Bank */
}MSCAN_ConfigType, *MSCAN_ConfigPtr;
/*! @} End of mscan_config_type                                             				*/

/******************************************************************************
*
*//*! @addtogroup mscan_tx_rx_idr1_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN tx and rx IDR1 struct type.
 *
 */
typedef struct
{
	uint8_t EID17_15			:3;	/*!< Extended Format Identifier 17-15*/
	uint8_t R_TEIDE				:1; /*!< ID Extended */
	uint8_t R_TSRR				:1; /*!< Substitute Remote Request */
	uint8_t EID20_18_OR_SID2_0	:3;	/*!< Extended Format Identifier 18-20 or standard format bit 0-2*/	
}MSCAN_IDR1Type;	
/*! @} End of mscan_tx_rx_idr1_type                                       				*/



/******************************************************************************
*
*//*! @addtogroup mscan_tx_rx_idr3_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN tx and rx IDR3 struct type.
 *
 */
typedef struct
{
	uint8_t ERTR	:1; /*!< Remote Transmission Request*/
	uint8_t EID6_0	:7;/*!< Extended Format Identifier 6-0*/
}MSCAN_IDR3Type;	
/*! @} End of mscan_tx_rx_idr3_type                                       				*/

/******************************************************************************
*
*//*! @addtogroup IDR1_IDR3_union
* @{
*******************************************************************************/
/*!
 * @brief MSCAN idr1 and idr3 union
 *
 */
typedef union{
	MSCAN_IDR1Type	IDR1;	/*!< structure for identifier 1 */
	MSCAN_IDR3Type  IDR3; /*!< structure for identifier 3 */
	uint8_t Bytes;        /*!< bytes */
	}IDR1_3_UNION;	
/*! @} End of IDR1_IDR3_union                                       				*/


/******************************************************************************
*
*//*! @addtogroup mscan_extend_id_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN extend ID struct type.
 *
 */
typedef struct
{
	uint32_t EID6_0 	:7;		/*!< ID[0:6] */
	uint32_t EID14_7	:8;		/*!< ID[14:7] */
	uint32_t EID17_15   :3;		/*!< ID[17:15] */
	uint32_t EID20_18  	:3;		/*!< ID[20:18] */
	uint32_t EID28_21   :8;  	/*!< ID[28:21] */
	uint32_t Reverse    :3;
}MSCAN_ExtendIDType;	
/*! @} End of mscan_extend_id_type                                       				*/

/******************************************************************************
*
*//*! @addtogroup mscan_standard_id_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN standard ID struct type.
 *
 */
typedef struct
{
	uint32_t EID2_0 	:3;		/*!< ID[0:2] */
	uint32_t EID10_3	:8;		/*!< ID[10:3] */
	uint32_t Reverse    :21;
}MSCAN_StandardIDType;	
/*! @} End of mscan_standard_id_type                                       				*/


/******************************************************************************
*
*//*! @addtogroup mscan_frame_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN frame struct type.
 *
 */
typedef struct
{
	union{
	MSCAN_StandardIDType StandID; /*!< standard format type */
	MSCAN_ExtendIDType   ExtID;	  /*!< extend format type */
	uint32_t ID;                  /*!< Identifire with 32 bit format */
	}ID_Type;											/*!< identifier union */
	uint8_t DSR[8];               /*!< data segment */
	uint8_t DLR;									/*!< data length */
	uint8_t BPR;									/*!< transmit buffer priority */
	uint8_t bIsRemoteFrame;				/*!< remote frame or not */
	uint8_t bIsExtOrStand;				/*!< extend frame or not */
	uint8_t u8TSRH;								/*!< time stamp high byte */
	uint8_t u8TSRL;								/*!< time stamp low byte */
}MSCAN_FrameType,*MSCAN_FramePtr;
/*! @} End of mscan_frame_type                                       				*/


/******************************************************************************
*
*//*! @addtogroup mscan_register_frame_struct_type
* @{
*******************************************************************************/
/*!
 * @brief MSCAN register frame struct type, same with register definition.
 *
 */
typedef struct
{
	uint8_t EIDR0;							/*!< Extended Identifier Register 0 */
	uint8_t EIDR1;							/*!< Extended Identifier Register 1 */
	uint8_t EIDR2;							/*!< Extended Identifier Register 2 */
	uint8_t EIDR3;							/*!< Extended Identifier Register 3 */
	uint8_t EDSR[8];						/*!< Extended Data Segment Register */
	uint8_t DLR;								/*!< data length field */
	uint8_t BPR;								/*!< Buffer Priority Register */
	uint8_t TSRH;								/*!< Time Stamp Register High */
	uint8_t TSRL;								/*!< Time Stamp Register Low */
}MSCAN_RegisterFrameType,*MSCAN_RegisterFramePtr;
/*! @} End of mscan_register_frame_struct_type                                 	*/



/******************************************************************************
*
*//*! @addtogroup mscan_callback
* @{
*******************************************************************************/
typedef void (*MSCAN_CallbackType)(void);		/*!< MSCAN call back function */
/*! @} End of mscan_callback                                             						*/

/******************************************************************************
* inline functions
******************************************************************************/
/******************************************************************************
*
*//*! @addtogroup mscan_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief Check Received Frame Flag.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Received Frame Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsRxFrameFlag(MSCAN_Type *pCANx)
{
    return pCANx->CANCTL0 & MSCAN_CANCTL0_RXFRM_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check Receiver Active Status.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Receiver Active Status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsReceiving(MSCAN_Type *pCANx)
{
    return pCANx->CANCTL0 & MSCAN_CANCTL0_RXACT_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Check CAN Synchronized Status.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Synchronized Status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsSynToBus(MSCAN_Type *pCANx)
{
    return pCANx->CANCTL0 & MSCAN_CANCTL0_SYNCH_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Sleep Mode Request.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_SleepModeReq(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_SLPRQ_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Initialization Mode Request.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_InitialModeReq(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_INITRQ_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Normal Mode Request.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_NormalModeReq(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 &= ~MSCAN_CANCTL0_INITRQ_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Loopback Self Test Mode Enable.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_LoopModeEn(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 |= MSCAN_CANCTL1_LOOPB_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Loopback Self Test Mode Disable.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_LoopModeDisable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 &= ~MSCAN_CANCTL1_LOOPB_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Listen Only Mode Enable.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ListenModeEn(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 |= MSCAN_CANCTL1_LISTEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Listen Only Mode Disable.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ListenModeDisable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 &= ~MSCAN_CANCTL1_LISTEN_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Bus-Off Recovery Mode - user request.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_BusOffUserRecovery(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 |= MSCAN_CANCTL1_BORM_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Bus-Off Recovery Mode - Auto.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_BusOffAutoRecovery(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 &= ~MSCAN_CANCTL1_BORM_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Check Sleep Mode Acknowledge.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Sleep Mode Acknowledge
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsSleepMode(MSCAN_Type *pCANx)
{
    return pCANx->CANCTL1 & MSCAN_CANCTL1_SLPAK_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check Initialization Mode Acknowledge.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Initialization Mode Acknowledge
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsInitialMode(MSCAN_Type *pCANx)
{
    return pCANx->CANCTL1 & MSCAN_CANCTL1_INITAK_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check Wake-Up Interrupt Flag.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Wake-Up Interrupt Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsWakeUpIntFlag(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG& MSCAN_CANRFLG_WUPIF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check CAN Status Change Interrupt Flag.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return CAN Status Change Interrupt Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsStatusChangeFlag(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG& MSCAN_CANRFLG_CSCIF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check Overrun Interrupt Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Overrun Interrupt Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsOverRunFlag(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG& MSCAN_CANRFLG_OVRIF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Check Receive Buffer Full Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Overrun Interrupt Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsRxBuffFull(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG & MSCAN_CANRFLG_RXF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Get Receiver Status
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Receiver Status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetReceiverStatus(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG & MSCAN_CANRFLG_RSTAT_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Get Transmitter Status
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Transmitter Status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetTransmitterStatus(MSCAN_Type *pCANx)
{
    return pCANx->CANRFLG & MSCAN_CANRFLG_TSTAT_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Get Transmitter Buffer Empty Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Transmitter Buffer Empty Flag
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetTransmitterBufferEmptyFlag(MSCAN_Type *pCANx)
{
    return pCANx->CANTFLG & MSCAN_CANTFLG_TXE_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Transmitter Empty Interrupt Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TransmitterEmptyIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANTIER |= MSCAN_CANTIER_TXEIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Transmitter Empty Interrupt Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TransmitterEmptyIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANTIER &= ~MSCAN_CANTIER_TXEIE_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Write Abort Request Register 
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] u8AbortRequest     abort request to tx buffer.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteAbortRequestReg(MSCAN_Type *pCANx,uint8_t u8AbortRequest)
{
    pCANx->CANTARQ = MSCAN_CANTARQ_ABTRQ(u8AbortRequest&0x07);
}

/*****************************************************************************//*!
   *
   * @brief Get Abort Acknowledge
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Abort Acknowledge
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetAbortFlag(MSCAN_Type *pCANx)
{
    return (pCANx->CANTAAK & MSCAN_CANTAAK_ABTAK_MASK);
}
/*****************************************************************************//*!
   *
   * @brief Transmit Buffer Select - The lowest numbered bit places the respective transmit buffer in
   *           the CANTXFG register space
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] u8TxBuff       tx buff to be selected.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TxBuffSelect(MSCAN_Type *pCANx,uint8_t u8TxBuff)
{
    pCANx->CANTBSEL = MSCAN_CANTBSEL_TX(u8TxBuff);
}
/*****************************************************************************//*!
   *
   * @brief Get the selected transmitter buffer
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetTxBuffSelect(MSCAN_Type *pCANx)
{
    return pCANx->CANTBSEL&MSCAN_CANTBSEL_TX_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Set Identifier Acceptance Mode
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] u8IDAcceptMode       Identifier Acceptance Mode.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_IDAcceptMode(MSCAN_Type *pCANx,uint8_t u8IDAcceptMode)
{
    pCANx->CANIDAC = MSCAN_CANIDAC_IDAM(u8IDAcceptMode);
}

/*****************************************************************************//*!
   *
   * @brief Set Identifier Acceptance Hit Indicator
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] u8IDAcceptHit       Identifier Acceptance Hit Indicator.
   *
   * @return filter number for hit
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IDAcceptHit(MSCAN_Type *pCANx)
{
    return pCANx->CANIDAC & MSCAN_CANIDAC_IDHIT_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Check if is Bus-Off Status
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Bus-Off Status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_IsBusOff(MSCAN_Type *pCANx)
{
    return pCANx->CANMISC |= MSCAN_CANMISC_BOHOLD_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Get Receive Error Counter
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return Receive Error Counter
   *
   * @ Pass/ Fail criteria: This field is read only in sleep mode (SLPRQ = 1 and SLPAK = 1) or initialization mode (INITRQ = 1 and
   *                                INITAK = 1)
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_GetReceiveErrorCount(MSCAN_Type *pCANx)
{
    return pCANx->CANRXERR & MSCAN_CANRXERR_RXERR_MASK;
}

/*****************************************************************************//*!
   *
   * @brief CAN enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_Enable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 |= MSCAN_CANCTL1_CANE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_Disable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 &= ~MSCAN_CANCTL1_CANE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief WakeUp Interrupt Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_WUPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief WakeUp Interrupt Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_WUPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN Status Change Interrupt Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_StatusChangeIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_CSCIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN Status Change Interrupt Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_StatusChangeIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_CSCIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Receiver Status Change Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ReceiverStatusChangeIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_RSTATE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN Receiver Status Change Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ReceiverStatusChangeIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_RSTATE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Transmitter Status Change Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TransmitterStatusChangeIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_TSTATE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Transmitter Status Change Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TransmitterStatusChangeIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_TSTATE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Overrun Interrupt Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_OverrunIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_OVRIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Overrun Interrupt Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_OverrunIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_OVRIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Receiver Full Interrupt Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ReceiverFullIntEn(MSCAN_Type *pCANx)
{
    pCANx->CANRIER |= MSCAN_CANRIER_RXFIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Receiver Full Interrupt Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ReceiverFullIntDisable(MSCAN_Type *pCANx)
{
    pCANx->CANRIER &= ~MSCAN_CANRIER_RXFIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Timer Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TimerEn(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_TIME_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Timer Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_TimerDisable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 &= ~MSCAN_CANCTL0_TIME_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN Stops in Wait Mode Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_StopInWaitModeEn(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_CSWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief CAN Stops in Wait Mode Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_StopInWaitModeDisable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 &= ~MSCAN_CANCTL0_CSWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief WakeUp Enable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpEn(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_WUPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief WakeUp Disable
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpDisable(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 &= ~MSCAN_CANCTL0_WUPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief MSCAN wakes up only in case of a dominant pulse on the CAN bus that has a length of Twup.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpModeFilter(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 |= MSCAN_CANCTL1_WUPM_MASK;
}
/*****************************************************************************//*!
   *
   * @brief MSCAN wakes up on any dominant level on the CAN bus.
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WakeUpModeNoFilter(MSCAN_Type *pCANx)
{
    pCANx->CANCTL1 &= ~MSCAN_CANCTL1_WUPM_MASK;
}

/*****************************************************************************//*!
   *
   * @brief write MSCAN Identifier Acceptance Register n of First Bank
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteIDAR0Reg(MSCAN_Type *pCANx,uint8_t *pID)
{
    pCANx->CANIDAR_BANK_1[0] = pID[3];
    pCANx->CANIDAR_BANK_1[1] = pID[2];
    pCANx->CANIDAR_BANK_1[2] = pID[1];
    pCANx->CANIDAR_BANK_1[3] = pID[0];
}
/*****************************************************************************//*!
   *
   * @brief write MSCAN Identifier Acceptance Register n of Second Bank
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteIDAR1Reg(MSCAN_Type *pCANx,uint8_t *pID)
{
    pCANx->CANIDAR_BANK_2[0] = pID[3];
    pCANx->CANIDAR_BANK_2[1] = pID[2];
    pCANx->CANIDAR_BANK_2[2] = pID[1];
    pCANx->CANIDAR_BANK_2[3] = pID[0];
}
/*****************************************************************************//*!
   *
   * @brief write MSCAN Identifier Mask Register n of First Bank
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/

__STATIC_INLINE void CAN_WriteIDAM0Reg(MSCAN_Type *pCANx,uint8_t *pID)
{
    pCANx->CANIDMR_BANK_1[0] = pID[3];
    pCANx->CANIDMR_BANK_1[1] = pID[2];
    pCANx->CANIDMR_BANK_1[2] = pID[1];
    pCANx->CANIDMR_BANK_1[3] = pID[0];
}
/*****************************************************************************//*!
   *
   * @brief write MSCAN Bus Timming Register
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_SetBaudRateReg(MSCAN_Type *pCANx,MSCAN_BaudRateSettingType sBspSetting)
{
    pCANx->CANBTR0 = MSCAN_CANBTR0_SJW(sBspSetting.SJW) | MSCAN_CANBTR0_BRP(sBspSetting.BRP);
    pCANx->CANBTR1 = MSCAN_CANBTR1_TSEG1(sBspSetting.TSEG1)
    				|MSCAN_CANBTR1_TSEG2(sBspSetting.TSEG2);
   	if(sBspSetting.SAMP)
   	{
		pCANx->CANBTR1 |= MSCAN_CANBTR1_SAMP_MASK;
   	}
   	else
   	{
		pCANx->CANBTR1 &= ~MSCAN_CANBTR1_SAMP_MASK;
   	}
    				
}
/*****************************************************************************//*!
   *
   * @brief write MSCAN Identifier Mask Register n of Second Bank
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteIDAM1Reg(MSCAN_Type *pCANx,uint8_t *pID)
{
    pCANx->CANIDMR_BANK_2[0] = pID[3];
    pCANx->CANIDMR_BANK_2[1] = pID[2];
    pCANx->CANIDMR_BANK_2[2] = pID[1];
    pCANx->CANIDMR_BANK_2[3] = pID[0];
}
/*****************************************************************************//*!
   *
   * @brief Clear Transmitter Buffer Empty Flag to schedule for transmission
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] TxBuffer    point to CAN transmitter buffer to be launched.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_LaunchTransmitBuffer(MSCAN_Type *pCANx,uint8_t TxBuffer)
{
    pCANx->CANTFLG = TxBuffer&0x07;
}
/*****************************************************************************//*!
   *
   * @brief Write Transmit Extended and Standard Identifier Register 0
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] ucBuffer    the data written to IDR0 register.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteTEIDR0Reg(MSCAN_Type *pCANx,uint8_t ucBuffer)
{
    pCANx->TEIDR0 = ucBuffer;
}
/*****************************************************************************//*!
   *
   * @brief Write Transmit Extended  Identifier Register 1
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] ucBuffer    the data written to TEIDR1 register.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteTEIDR1Reg(MSCAN_Type *pCANx,uint8_t ucBuffer)
{
    pCANx->TEIDR1 = ucBuffer;
}
/*****************************************************************************//*!
   *
   * @brief Write Transmit Extended  Identifier Register 2
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] ucBuffer    the data written to TEIDR2 register.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteTEIDR2Reg(MSCAN_Type *pCANx,uint8_t ucBuffer)
{
    pCANx->TEIDR2 = ucBuffer;
}
/*****************************************************************************//*!
   *
   * @brief Write Transmit Extended  Identifier Register 3
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] ucBuffer    the data written to TEIDR3 register.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteTEIDR3Reg(MSCAN_Type *pCANx,uint8_t ucBuffer)
{
    pCANx->TEIDR3 = ucBuffer;
}

/*****************************************************************************//*!
   *
   * @brief Write Transmit Standard  Identifier Register 1
   *        
   * @param[in] pCANx      point to CAN module type.
   * @param[in] ucBuffer    the data written to TSID1 register.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_WriteTSIDR1Reg(MSCAN_Type *pCANx,uint8_t ucBuffer)
{
    pCANx->TSIDR1 = ucBuffer;
}


/*****************************************************************************//*!
   *
   * @brief Read receiver extend and standard identifier register 1
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return REIDR0 or RSIDR0
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadIDR1Reg(MSCAN_Type *pCANx)
{
    return pCANx->REIDR1;
}
/*****************************************************************************//*!
   *
   * @brief Read receiver extend and standard identifier register 0
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return REIDR1 or RSIDR1
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadIDR0Reg(MSCAN_Type *pCANx)
{
    return pCANx->REIDR0;
}

/*****************************************************************************//*!
   *
   * @brief Read receiver extend identifier register 2
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return REIDR2
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadIDR2Reg(MSCAN_Type *pCANx)
{
    return pCANx->REIDR2;
}

/*****************************************************************************//*!
   *
   * @brief Read receiver extend identifier register 3
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return REIDR3
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadIDR3Reg(MSCAN_Type *pCANx)
{
    return pCANx->REIDR3;
}

/*****************************************************************************//*!
   *
   * @brief Read receiver stamps registers high bytes
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return RTSRH
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadRTSRHReg(MSCAN_Type *pCANx)
{
    return pCANx->RTSRH;
}
/*****************************************************************************//*!
   *
   * @brief Read receiver stamps registers low bytes
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return RTSRL
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadRTSRLReg(MSCAN_Type *pCANx)
{
    return pCANx->RTSRL;
}

/*****************************************************************************//*!
   *
   * @brief Read transmitter stamps registers high byte
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return TTSRH
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadTTSRHReg(MSCAN_Type *pCANx)
{
    return pCANx->TTSRH;
}
/*****************************************************************************//*!
   *
   * @brief Read transmitter stamps registers low byte
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return TTSRL
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t CAN_ReadTTSRLReg(MSCAN_Type *pCANx)
{
    return pCANx->TTSRL;
}
/*****************************************************************************//*!
   *
   * @brief Clear Wake-Up Interrupt Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearWUPIF_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANRFLG |= MSCAN_CANRFLG_WUPIF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Clear CAN Status Change Interrupt Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearCSCIF_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANRFLG |= MSCAN_CANRFLG_CSCIF_MASK;
}


/*****************************************************************************//*!
   *
   * @brief Clear Overrun Interrupt Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearOVRIF_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANRFLG |= MSCAN_CANRFLG_OVRIF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Clear Receive Buffer Full Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearRXF_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANRFLG |= MSCAN_CANRFLG_RXF_MASK;
}

/*****************************************************************************//*!
   *
   * @brief Clear Received Frame Flag
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearRXFRM_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 |= MSCAN_CANCTL0_RXFRM_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Clear Sleep Mode Request
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_ClearSLPRQ_Flag(MSCAN_Type *pCANx)
{
    pCANx->CANCTL0 &= ~MSCAN_CANCTL0_SLPRQ_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Identifier Acceptance Mode
   *        
   * @param[in] pCANx      point to CAN module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void CAN_SetIDAMode(MSCAN_Type *pCANx,uint8_t IDAMode)
{
    pCANx->CANIDAC = MSCAN_CANIDAC_IDAM(IDAMode);
}


/******************************************************************************
* Global functions
******************************************************************************/


void CAN_Init(MSCAN_Type *pCANx,MSCAN_ConfigPtr pCANConfig);
uint8_t CAN_DeInit(MSCAN_Type *pCANx);
uint8_t CAN_EnterSleep(MSCAN_Type *pCANx);
uint8_t CAN_WakeUpFromSleep(MSCAN_Type *pCANx);
uint8_t CAN_LaunchInitialRequest(MSCAN_Type *pCANx);
uint8_t CAN_ReadOneFrameFromBuff(MSCAN_Type *pCANx,MSCAN_FramePtr pRxFrame);
uint8_t CAN_LoadOneFrameToBuff(MSCAN_Type *pCANx,MSCAN_RegisterFramePtr pFrameBuff);
void MSCAN_SetRxCallBack( MSCAN_CallbackType pCallBack );
void MSCAN_SetTxCallBack( MSCAN_CallbackType pCallBack );
void MSCAN_RxIsr( void );
void MSCAN_TxIsr( void );




#ifdef __cplusplus
}
#endif
#endif //


