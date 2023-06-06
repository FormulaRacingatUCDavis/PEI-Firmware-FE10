/*******************************************************************************
* File Name: Precharge.h  
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

#if !defined(CY_PINS_Precharge_H) /* Pins Precharge_H */
#define CY_PINS_Precharge_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Precharge_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Precharge__PORT == 15 && ((Precharge__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Precharge_Write(uint8 value);
void    Precharge_SetDriveMode(uint8 mode);
uint8   Precharge_ReadDataReg(void);
uint8   Precharge_Read(void);
void    Precharge_SetInterruptMode(uint16 position, uint16 mode);
uint8   Precharge_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Precharge_SetDriveMode() function.
     *  @{
     */
        #define Precharge_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Precharge_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Precharge_DM_RES_UP          PIN_DM_RES_UP
        #define Precharge_DM_RES_DWN         PIN_DM_RES_DWN
        #define Precharge_DM_OD_LO           PIN_DM_OD_LO
        #define Precharge_DM_OD_HI           PIN_DM_OD_HI
        #define Precharge_DM_STRONG          PIN_DM_STRONG
        #define Precharge_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Precharge_MASK               Precharge__MASK
#define Precharge_SHIFT              Precharge__SHIFT
#define Precharge_WIDTH              1u

/* Interrupt constants */
#if defined(Precharge__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Precharge_SetInterruptMode() function.
     *  @{
     */
        #define Precharge_INTR_NONE      (uint16)(0x0000u)
        #define Precharge_INTR_RISING    (uint16)(0x0001u)
        #define Precharge_INTR_FALLING   (uint16)(0x0002u)
        #define Precharge_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Precharge_INTR_MASK      (0x01u) 
#endif /* (Precharge__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Precharge_PS                     (* (reg8 *) Precharge__PS)
/* Data Register */
#define Precharge_DR                     (* (reg8 *) Precharge__DR)
/* Port Number */
#define Precharge_PRT_NUM                (* (reg8 *) Precharge__PRT) 
/* Connect to Analog Globals */                                                  
#define Precharge_AG                     (* (reg8 *) Precharge__AG)                       
/* Analog MUX bux enable */
#define Precharge_AMUX                   (* (reg8 *) Precharge__AMUX) 
/* Bidirectional Enable */                                                        
#define Precharge_BIE                    (* (reg8 *) Precharge__BIE)
/* Bit-mask for Aliased Register Access */
#define Precharge_BIT_MASK               (* (reg8 *) Precharge__BIT_MASK)
/* Bypass Enable */
#define Precharge_BYP                    (* (reg8 *) Precharge__BYP)
/* Port wide control signals */                                                   
#define Precharge_CTL                    (* (reg8 *) Precharge__CTL)
/* Drive Modes */
#define Precharge_DM0                    (* (reg8 *) Precharge__DM0) 
#define Precharge_DM1                    (* (reg8 *) Precharge__DM1)
#define Precharge_DM2                    (* (reg8 *) Precharge__DM2) 
/* Input Buffer Disable Override */
#define Precharge_INP_DIS                (* (reg8 *) Precharge__INP_DIS)
/* LCD Common or Segment Drive */
#define Precharge_LCD_COM_SEG            (* (reg8 *) Precharge__LCD_COM_SEG)
/* Enable Segment LCD */
#define Precharge_LCD_EN                 (* (reg8 *) Precharge__LCD_EN)
/* Slew Rate Control */
#define Precharge_SLW                    (* (reg8 *) Precharge__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Precharge_PRTDSI__CAPS_SEL       (* (reg8 *) Precharge__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Precharge_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Precharge__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Precharge_PRTDSI__OE_SEL0        (* (reg8 *) Precharge__PRTDSI__OE_SEL0) 
#define Precharge_PRTDSI__OE_SEL1        (* (reg8 *) Precharge__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Precharge_PRTDSI__OUT_SEL0       (* (reg8 *) Precharge__PRTDSI__OUT_SEL0) 
#define Precharge_PRTDSI__OUT_SEL1       (* (reg8 *) Precharge__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Precharge_PRTDSI__SYNC_OUT       (* (reg8 *) Precharge__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Precharge__SIO_CFG)
    #define Precharge_SIO_HYST_EN        (* (reg8 *) Precharge__SIO_HYST_EN)
    #define Precharge_SIO_REG_HIFREQ     (* (reg8 *) Precharge__SIO_REG_HIFREQ)
    #define Precharge_SIO_CFG            (* (reg8 *) Precharge__SIO_CFG)
    #define Precharge_SIO_DIFF           (* (reg8 *) Precharge__SIO_DIFF)
#endif /* (Precharge__SIO_CFG) */

/* Interrupt Registers */
#if defined(Precharge__INTSTAT)
    #define Precharge_INTSTAT            (* (reg8 *) Precharge__INTSTAT)
    #define Precharge_SNAP               (* (reg8 *) Precharge__SNAP)
    
	#define Precharge_0_INTTYPE_REG 		(* (reg8 *) Precharge__0__INTTYPE)
#endif /* (Precharge__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Precharge_H */


/* [] END OF FILE */
