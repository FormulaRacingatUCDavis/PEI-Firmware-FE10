/*******************************************************************************
* File Name: AIR_POS.h  
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

#if !defined(CY_PINS_AIR_POS_H) /* Pins AIR_POS_H */
#define CY_PINS_AIR_POS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AIR_POS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AIR_POS__PORT == 15 && ((AIR_POS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AIR_POS_Write(uint8 value);
void    AIR_POS_SetDriveMode(uint8 mode);
uint8   AIR_POS_ReadDataReg(void);
uint8   AIR_POS_Read(void);
void    AIR_POS_SetInterruptMode(uint16 position, uint16 mode);
uint8   AIR_POS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AIR_POS_SetDriveMode() function.
     *  @{
     */
        #define AIR_POS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AIR_POS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AIR_POS_DM_RES_UP          PIN_DM_RES_UP
        #define AIR_POS_DM_RES_DWN         PIN_DM_RES_DWN
        #define AIR_POS_DM_OD_LO           PIN_DM_OD_LO
        #define AIR_POS_DM_OD_HI           PIN_DM_OD_HI
        #define AIR_POS_DM_STRONG          PIN_DM_STRONG
        #define AIR_POS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AIR_POS_MASK               AIR_POS__MASK
#define AIR_POS_SHIFT              AIR_POS__SHIFT
#define AIR_POS_WIDTH              1u

/* Interrupt constants */
#if defined(AIR_POS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AIR_POS_SetInterruptMode() function.
     *  @{
     */
        #define AIR_POS_INTR_NONE      (uint16)(0x0000u)
        #define AIR_POS_INTR_RISING    (uint16)(0x0001u)
        #define AIR_POS_INTR_FALLING   (uint16)(0x0002u)
        #define AIR_POS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AIR_POS_INTR_MASK      (0x01u) 
#endif /* (AIR_POS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AIR_POS_PS                     (* (reg8 *) AIR_POS__PS)
/* Data Register */
#define AIR_POS_DR                     (* (reg8 *) AIR_POS__DR)
/* Port Number */
#define AIR_POS_PRT_NUM                (* (reg8 *) AIR_POS__PRT) 
/* Connect to Analog Globals */                                                  
#define AIR_POS_AG                     (* (reg8 *) AIR_POS__AG)                       
/* Analog MUX bux enable */
#define AIR_POS_AMUX                   (* (reg8 *) AIR_POS__AMUX) 
/* Bidirectional Enable */                                                        
#define AIR_POS_BIE                    (* (reg8 *) AIR_POS__BIE)
/* Bit-mask for Aliased Register Access */
#define AIR_POS_BIT_MASK               (* (reg8 *) AIR_POS__BIT_MASK)
/* Bypass Enable */
#define AIR_POS_BYP                    (* (reg8 *) AIR_POS__BYP)
/* Port wide control signals */                                                   
#define AIR_POS_CTL                    (* (reg8 *) AIR_POS__CTL)
/* Drive Modes */
#define AIR_POS_DM0                    (* (reg8 *) AIR_POS__DM0) 
#define AIR_POS_DM1                    (* (reg8 *) AIR_POS__DM1)
#define AIR_POS_DM2                    (* (reg8 *) AIR_POS__DM2) 
/* Input Buffer Disable Override */
#define AIR_POS_INP_DIS                (* (reg8 *) AIR_POS__INP_DIS)
/* LCD Common or Segment Drive */
#define AIR_POS_LCD_COM_SEG            (* (reg8 *) AIR_POS__LCD_COM_SEG)
/* Enable Segment LCD */
#define AIR_POS_LCD_EN                 (* (reg8 *) AIR_POS__LCD_EN)
/* Slew Rate Control */
#define AIR_POS_SLW                    (* (reg8 *) AIR_POS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AIR_POS_PRTDSI__CAPS_SEL       (* (reg8 *) AIR_POS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AIR_POS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AIR_POS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AIR_POS_PRTDSI__OE_SEL0        (* (reg8 *) AIR_POS__PRTDSI__OE_SEL0) 
#define AIR_POS_PRTDSI__OE_SEL1        (* (reg8 *) AIR_POS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AIR_POS_PRTDSI__OUT_SEL0       (* (reg8 *) AIR_POS__PRTDSI__OUT_SEL0) 
#define AIR_POS_PRTDSI__OUT_SEL1       (* (reg8 *) AIR_POS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AIR_POS_PRTDSI__SYNC_OUT       (* (reg8 *) AIR_POS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AIR_POS__SIO_CFG)
    #define AIR_POS_SIO_HYST_EN        (* (reg8 *) AIR_POS__SIO_HYST_EN)
    #define AIR_POS_SIO_REG_HIFREQ     (* (reg8 *) AIR_POS__SIO_REG_HIFREQ)
    #define AIR_POS_SIO_CFG            (* (reg8 *) AIR_POS__SIO_CFG)
    #define AIR_POS_SIO_DIFF           (* (reg8 *) AIR_POS__SIO_DIFF)
#endif /* (AIR_POS__SIO_CFG) */

/* Interrupt Registers */
#if defined(AIR_POS__INTSTAT)
    #define AIR_POS_INTSTAT            (* (reg8 *) AIR_POS__INTSTAT)
    #define AIR_POS_SNAP               (* (reg8 *) AIR_POS__SNAP)
    
	#define AIR_POS_0_INTTYPE_REG 		(* (reg8 *) AIR_POS__0__INTTYPE)
#endif /* (AIR_POS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AIR_POS_H */


/* [] END OF FILE */
