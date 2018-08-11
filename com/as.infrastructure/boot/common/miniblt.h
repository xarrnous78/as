/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef _MINIBLT_H_
#define _MINIBLT_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Can.h"
/* ============================ [ MACROS    ] ====================================================== */
#define DCM_ERASE_OK					((Dcm_ReturnEraseMemoryType)0x00)
#define DCM_ERASE_PENDING				((Dcm_ReturnEraseMemoryType)0x01)
#define	DCM_ERASE_FAILED				((Dcm_ReturnEraseMemoryType)0x02)

#define DCM_READ_OK						((Dcm_ReturnReadMemoryType)0x00)
#define DCM_READ_PENDING				((Dcm_ReturnReadMemoryType)0x01)
#define	DCM_READ_FAILED					((Dcm_ReturnReadMemoryType)0x02)

#define DCM_WRITE_OK					((Dcm_ReturnWriteMemoryType)0x00)
#define DCM_WRITE_PENDING				((Dcm_ReturnWriteMemoryType)0x01)
#define DCM_WRITE_FAILED				((Dcm_ReturnWriteMemoryType)0x02)

#define DCM_INITIAL						((Dcm_OpStatusType)0x00)
#define DCM_PENDING						((Dcm_OpStatusType)0X01)
#define DCM_CANCEL						((Dcm_OpStatusType)0x02)

#define DCM_E_POSITIVE_RESPONSE								((Dcm_NegativeResponseCodeType)0x00)
#define DCM_E_SERVICE_NOT_SUPPORTED							((Dcm_NegativeResponseCodeType)0x11)
#define DCM_E_SUB_FUNCTION_NOT_SUPPORTED					((Dcm_NegativeResponseCodeType)0x12)
#define DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT	((Dcm_NegativeResponseCodeType)0x13)
#define DCM_E_RESPONSE_PENDING								((Dcm_NegativeResponseCodeType)0x78)
#define DCM_E_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION		((Dcm_NegativeResponseCodeType)0x7F)
#define DCM_E_GENERAL_REJECT								((Dcm_NegativeResponseCodeType)0x10)
#define DCM_E_CONDITIONS_NOT_CORRECT						((Dcm_NegativeResponseCodeType)0x22)
#define DCM_E_REQUEST_SEQUENCE_ERROR						((Dcm_NegativeResponseCodeType)0x24)
#define DCM_E_REQUEST_OUT_OF_RANGE							((Dcm_NegativeResponseCodeType)0x31)
#define DCM_E_SECUTITY_ACCESS_DENIED						((Dcm_NegativeResponseCodeType)0x33)
#define DCM_E_INVALID_KEY									((Dcm_NegativeResponseCodeType)0x35)
#define DCM_E_GENERAL_PROGRAMMING_FAILURE					((Dcm_NegativeResponseCodeType)0x72)
#define DCM_E_WRONG_BLOCK_SEQUENCE_COUNTER                  ((Dcm_NegativeResponseCodeType)0x73)

#define DCM_DEFAULT_SESSION					((Dcm_SesCtrlType)0x01)
#define DCM_PROGRAMMING_SESSION				((Dcm_SesCtrlType)0x02)
#define DCM_EXTENDED_DIAGNOSTIC_SESSION		((Dcm_SesCtrlType)0x03)

#define DCM_SEC_LEV_LOCKED					((Dcm_SecLevelType)0x00)

#define SID_DIAGNOSTIC_SESSION_CONTROL			0x10
#define SID_ECU_RESET							0x11
#define SID_SECURITY_ACCESS						0x27
#define SID_ROUTINE_CONTROL						0x31
#define SID_REQUEST_DOWNLOAD					0x34
#define SID_REQUEST_UPLOAD						0x35
#define SID_TRANSFER_DATA						0x36
#define SID_REQUEST_TRANSFER_EXIT				0x37

#define SID_NEGATIVE_RESPONSE					0x7F

#define SUPPRESS_POS_RESP_BIT		(uint8)0x80
#define SID_RESPONSE_BIT			(uint8)0x40

#define NTFRSLT_OK						0x00
#define NTFRSLT_E_NOT_OK				0x01


#define CANIF_CHL_LS 0

#define CANIF_ID_RxDiagP2P 0
#define CANIF_ID_TxDiagP2P 0

#define CANTP_ID_RxDiagP2P 0
#define CANTP_ID_TxDiagP2P 1

#define DCM_USE_SERVICE_ROUTINE_CONTROL				1
#define DCM_USE_SERVICE_REQUEST_DOWNLOAD			1
#define DCM_USE_SERVICE_REQUEST_UPLOAD				1
#define DCM_USE_SERVICE_TRANSFER_DATA				1
#define DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT		1
/* ============================ [ TYPES     ] ====================================================== */
typedef uint8 Dcm_ReturnEraseMemoryType;
typedef uint8 Dcm_ReturnReadMemoryType;
typedef uint8 Dcm_ReturnWriteMemoryType;
typedef uint8 Dcm_OpStatusType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_SecLevelType;

typedef Std_ReturnType (*Dcm_CallbackGetSeedFncType)(uint8 *securityAccessDataRecord, uint8 *seed, Dcm_NegativeResponseCodeType *errorCode);
typedef Std_ReturnType (*Dcm_CallbackCompareKeyFncType)(uint8 *key);
typedef Std_ReturnType (*Dcm_CallbackGetSesChgPermissionFncType)(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew);

#if defined(__LINUX__) || defined(__WINDOWS__)
typedef uint64 Dcm_ParameterType;
#else
typedef uint32 Dcm_ParameterType;
#endif

/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void CanIf_TxConfirmation( PduIdType canTxPduId );
void CanIf_RxIndication( uint16 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr );
Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr);

void CanTp_Init(void);
void CanTp_SetParameter(PduIdType Instance, const uint16* parameter);
Std_ReturnType CanTp_Transmit( PduIdType CanTpTxSduId, const PduInfoType * pdu );
void CanTp_MainFunction(void);
void CanTp_RxIndication( PduIdType Instance, const PduInfoType *pdu );
void CanTp_TxConfirmation( PduIdType CanTpTxSduId );

void Dcm_Init(void);
void Dcm_SetParameter(PduIdType Instance, const Dcm_ParameterType* parameter);
void Dcm_AppendTX(PduIdType Instance, uint8 v);
void Dcm_RxIndication(PduIdType Instance, NotifResultType result);
void Dcm_TxConfirmation(PduIdType Instance, NotifResultType result);
BufReq_ReturnType Dcm_ProvideRxBuffer(PduIdType Instance, PduLengthType tpSduLength, PduInfoType **pduInfoPtr);
BufReq_ReturnType Dcm_ProvideTxBuffer(PduIdType Instance, PduInfoType **pduInfoPtr, PduLengthType length);
void Dcm_MainFunction(void);
Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType *secLevel);
Dcm_ReturnEraseMemoryType Dcm_EraseMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize);
Dcm_ReturnWriteMemoryType Dcm_WriteMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize,
											   uint8* MemoryData);
Dcm_ReturnReadMemoryType Dcm_ReadMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize,
											   uint8* MemoryData);
#endif /* _MINIBLT_H_ */
