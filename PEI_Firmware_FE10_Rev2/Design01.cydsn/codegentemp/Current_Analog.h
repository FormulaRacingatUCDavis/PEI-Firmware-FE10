/*******************************************************************************
* File Name: Current_Analog.h  
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

#if !defined(CY_PINS_Current_Analog_H) /* Pins Current_Analog_H */
#define CY_PINS_Current_Analog_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Current_Analog_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Current_Analog__PORT == 15 && ((Current_Analog__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Current_Analog_Write(uint8 value);
void    Current_Analog_SetDriveMode(uint8 mode);
uint8   Current_Analog_ReadDataReg(void);
uint8   Current_Analog_Read(void);
void    Current_Analog_SetInterruptMode(uint16 position, uint16 mode);
uint8   Current_Analog_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Current_Analog_SetDriveMode() function.
     *  @{
     */
        #define Current_Analog_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Current_Analog_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Current_Analog_DM_RES_UP          PIN_DM_RES_UP
        #define Current_Analog_DM_RES_DWN         PIN_DM_RES_DWN
        #define Current_Analog_DM_OD_LO           PIN_DM_OD_LO
        #define Current_Analog_DM_OD_HI           PIN_DM_OD_HI
        #define Current_Analog_DM_STRONG          PIN_DM_STRONG
        #define Current_Analog_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Current_Analog_MASK               Current_Analog__MASK
#define Current_Analog_SHIFT              Current_Analog__SHIFT
#define Current_Analog_WIDTH              1u

/* Interrupt constants */
#if defined(Current_Analog__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Current_Analog_SetInterruptMode() function.
     *  @{
     */
        #define Current_Analog_INTR_NONE      (uint16)(0x0000u)
        #define Current_Analog_INTR_RISING    (uint16)(0x0001u)
        #define Current_Analog_INTR_FALLING   (uint16)(0x0002u)
        #define Current_Analog_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Current_Analog_INTR_MASK      (0x01u) 
#endif /* (Current_Analog__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Current_Analog_PS                     (* (reg8 *) Current_Analog__PS)
/* Data Register */
#define Current_Analog_DR                     (* (reg8 *) Current_Analog__DR)
/* Port Number */
#define Current_Analog_PRT_NUM                (* (reg8 *) Current_Analog__PRT) 
/* Connect to Analog Globals */                                                  
#define Current_Analog_AG                     (* (reg8 *) Current_Analog__AG)                       
/* Analog MUX bux enable */
#define Current_Analog_AMUX                   (* (reg8 *) Current_Analog__AMUX) 
/* Bidirectional Enable */                                                        
#define Current_Analog_BIE                    (* (reg8 *) Current_Analog__BIE)
/* Bit-mask for Aliased Register Access */
#define Current_Analog_BIT_MASK               (* (reg8 *) Current_Analog__BIT_MASK)
/* Bypass Enable */
#define Current_Analog_BYP                    (* (reg8 *) Current_Analog__BYP)
/* Port wide control signals */                                                   
#define Current_Analog_CTL                    (* (reg8 *) Current_Analog__CTL)
/* Drive Modes */
#define Current_Analog_DM0                    (* (reg8 *) Current_Analog__DM0) 
#define Current_Analog_DM1                    (* (reg8 *) Current_Analog__DM1)
#define Current_Analog_DM2                    (* (reg8 *) Current_Analog__DM2) 
/* Input Buffer Disable Override */
#define Current_Analog_INP_DIS                (* (reg8 *) Current_Analog__INP_DIS)
/* LCD Common or Segment Drive */
#define Current_Analog_LCD_COM_SEG            (* (reg8 *) Current_Analog__LCD_COM_SEG)
/* Enable Segment LCD */
#define Current_Analog_LCD_EN                 (* (reg8 *) Current_Analog__LCD_EN)
/* Slew Rate Control */
#define Current_Analog_SLW                    (* (reg8 *) Current_Analog__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Current_Analog_PRTDSI__CAPS_SEL       (* (reg8 *) Current_Analog__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Current_Analog_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Current_Analog__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Current_Analog_PRTDSI__OE_SEL0        (* (reg8 *) Current_Analog__PRTDSI__OE_SEL0) 
#define Current_Analog_PRTDSI__OE_SEL1        (* (reg8 *) Current_Analog__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Current_Analog_PRTDSI__OUT_SEL0       (* (reg8 *) Current_Analog__PRTDSI__OUT_SEL0) 
#define Current_Analog_PRTDSI__OUT_SEL1       (* (reg8 *) Current_Analog__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Current_Analog_PRTDSI__SYNC_OUT       (* (reg8 *) Current_Analog__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Current_Analog__SIO_CFG)
    #define Current_Analog_SIO_HYST_EN        (* (reg8 *) Current_Analog__SIO_HYST_EN)
    #define Current_Analog_SIO_REG_HIFREQ     (* (reg8 *) Current_Analog__SIO_REG_HIFREQ)
    #define Current_Analog_SIO_CFG            (* (reg8 *) Current_Analog__SIO_CFG)
    #define Current_Analog_SIO_DIFF           (* (reg8 *) Current_Analog__SIO_DIFF)
#endif /* (Current_Analog__SIO_CFG) */

/* Interrupt Registers */
#if defined(Current_Analog__INTSTAT)
    #define Current_Analog_INTSTAT            (* (reg8 *) Current_Analog__INTSTAT)
    #define Current_Analog_SNAP               (* (reg8 *) Current_Analog__SNAP)
    
	#define Current_Analog_0_INTTYPE_REG 		(* (reg8 *) Current_Analog__0__INTTYPE)
#endif /* (Current_Analog__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Current_Analog_H */


/* [] END OF FILE */
