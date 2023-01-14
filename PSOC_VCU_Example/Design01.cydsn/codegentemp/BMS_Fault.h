/*******************************************************************************
* File Name: BMS_Fault.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BMS_Fault_H) /* Pins BMS_Fault_H */
#define CY_PINS_BMS_Fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BMS_Fault_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BMS_Fault__PORT == 15 && ((BMS_Fault__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BMS_Fault_Write(uint8 value);
void    BMS_Fault_SetDriveMode(uint8 mode);
uint8   BMS_Fault_ReadDataReg(void);
uint8   BMS_Fault_Read(void);
void    BMS_Fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   BMS_Fault_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BMS_Fault_SetDriveMode() function.
     *  @{
     */
        #define BMS_Fault_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BMS_Fault_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BMS_Fault_DM_RES_UP          PIN_DM_RES_UP
        #define BMS_Fault_DM_RES_DWN         PIN_DM_RES_DWN
        #define BMS_Fault_DM_OD_LO           PIN_DM_OD_LO
        #define BMS_Fault_DM_OD_HI           PIN_DM_OD_HI
        #define BMS_Fault_DM_STRONG          PIN_DM_STRONG
        #define BMS_Fault_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BMS_Fault_MASK               BMS_Fault__MASK
#define BMS_Fault_SHIFT              BMS_Fault__SHIFT
#define BMS_Fault_WIDTH              1u

/* Interrupt constants */
#if defined(BMS_Fault__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BMS_Fault_SetInterruptMode() function.
     *  @{
     */
        #define BMS_Fault_INTR_NONE      (uint16)(0x0000u)
        #define BMS_Fault_INTR_RISING    (uint16)(0x0001u)
        #define BMS_Fault_INTR_FALLING   (uint16)(0x0002u)
        #define BMS_Fault_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BMS_Fault_INTR_MASK      (0x01u) 
#endif /* (BMS_Fault__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BMS_Fault_PS                     (* (reg8 *) BMS_Fault__PS)
/* Data Register */
#define BMS_Fault_DR                     (* (reg8 *) BMS_Fault__DR)
/* Port Number */
#define BMS_Fault_PRT_NUM                (* (reg8 *) BMS_Fault__PRT) 
/* Connect to Analog Globals */                                                  
#define BMS_Fault_AG                     (* (reg8 *) BMS_Fault__AG)                       
/* Analog MUX bux enable */
#define BMS_Fault_AMUX                   (* (reg8 *) BMS_Fault__AMUX) 
/* Bidirectional Enable */                                                        
#define BMS_Fault_BIE                    (* (reg8 *) BMS_Fault__BIE)
/* Bit-mask for Aliased Register Access */
#define BMS_Fault_BIT_MASK               (* (reg8 *) BMS_Fault__BIT_MASK)
/* Bypass Enable */
#define BMS_Fault_BYP                    (* (reg8 *) BMS_Fault__BYP)
/* Port wide control signals */                                                   
#define BMS_Fault_CTL                    (* (reg8 *) BMS_Fault__CTL)
/* Drive Modes */
#define BMS_Fault_DM0                    (* (reg8 *) BMS_Fault__DM0) 
#define BMS_Fault_DM1                    (* (reg8 *) BMS_Fault__DM1)
#define BMS_Fault_DM2                    (* (reg8 *) BMS_Fault__DM2) 
/* Input Buffer Disable Override */
#define BMS_Fault_INP_DIS                (* (reg8 *) BMS_Fault__INP_DIS)
/* LCD Common or Segment Drive */
#define BMS_Fault_LCD_COM_SEG            (* (reg8 *) BMS_Fault__LCD_COM_SEG)
/* Enable Segment LCD */
#define BMS_Fault_LCD_EN                 (* (reg8 *) BMS_Fault__LCD_EN)
/* Slew Rate Control */
#define BMS_Fault_SLW                    (* (reg8 *) BMS_Fault__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BMS_Fault_PRTDSI__CAPS_SEL       (* (reg8 *) BMS_Fault__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BMS_Fault_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BMS_Fault__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BMS_Fault_PRTDSI__OE_SEL0        (* (reg8 *) BMS_Fault__PRTDSI__OE_SEL0) 
#define BMS_Fault_PRTDSI__OE_SEL1        (* (reg8 *) BMS_Fault__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BMS_Fault_PRTDSI__OUT_SEL0       (* (reg8 *) BMS_Fault__PRTDSI__OUT_SEL0) 
#define BMS_Fault_PRTDSI__OUT_SEL1       (* (reg8 *) BMS_Fault__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BMS_Fault_PRTDSI__SYNC_OUT       (* (reg8 *) BMS_Fault__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BMS_Fault__SIO_CFG)
    #define BMS_Fault_SIO_HYST_EN        (* (reg8 *) BMS_Fault__SIO_HYST_EN)
    #define BMS_Fault_SIO_REG_HIFREQ     (* (reg8 *) BMS_Fault__SIO_REG_HIFREQ)
    #define BMS_Fault_SIO_CFG            (* (reg8 *) BMS_Fault__SIO_CFG)
    #define BMS_Fault_SIO_DIFF           (* (reg8 *) BMS_Fault__SIO_DIFF)
#endif /* (BMS_Fault__SIO_CFG) */

/* Interrupt Registers */
#if defined(BMS_Fault__INTSTAT)
    #define BMS_Fault_INTSTAT            (* (reg8 *) BMS_Fault__INTSTAT)
    #define BMS_Fault_SNAP               (* (reg8 *) BMS_Fault__SNAP)
    
	#define BMS_Fault_0_INTTYPE_REG 		(* (reg8 *) BMS_Fault__0__INTTYPE)
#endif /* (BMS_Fault__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BMS_Fault_H */


/* [] END OF FILE */
