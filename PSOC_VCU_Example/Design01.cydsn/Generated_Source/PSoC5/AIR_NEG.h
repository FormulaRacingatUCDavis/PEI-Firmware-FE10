/*******************************************************************************
* File Name: AIR_NEG.h  
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

#if !defined(CY_PINS_AIR_NEG_H) /* Pins AIR_NEG_H */
#define CY_PINS_AIR_NEG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AIR_NEG_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AIR_NEG__PORT == 15 && ((AIR_NEG__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AIR_NEG_Write(uint8 value);
void    AIR_NEG_SetDriveMode(uint8 mode);
uint8   AIR_NEG_ReadDataReg(void);
uint8   AIR_NEG_Read(void);
void    AIR_NEG_SetInterruptMode(uint16 position, uint16 mode);
uint8   AIR_NEG_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AIR_NEG_SetDriveMode() function.
     *  @{
     */
        #define AIR_NEG_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AIR_NEG_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AIR_NEG_DM_RES_UP          PIN_DM_RES_UP
        #define AIR_NEG_DM_RES_DWN         PIN_DM_RES_DWN
        #define AIR_NEG_DM_OD_LO           PIN_DM_OD_LO
        #define AIR_NEG_DM_OD_HI           PIN_DM_OD_HI
        #define AIR_NEG_DM_STRONG          PIN_DM_STRONG
        #define AIR_NEG_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AIR_NEG_MASK               AIR_NEG__MASK
#define AIR_NEG_SHIFT              AIR_NEG__SHIFT
#define AIR_NEG_WIDTH              1u

/* Interrupt constants */
#if defined(AIR_NEG__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AIR_NEG_SetInterruptMode() function.
     *  @{
     */
        #define AIR_NEG_INTR_NONE      (uint16)(0x0000u)
        #define AIR_NEG_INTR_RISING    (uint16)(0x0001u)
        #define AIR_NEG_INTR_FALLING   (uint16)(0x0002u)
        #define AIR_NEG_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AIR_NEG_INTR_MASK      (0x01u) 
#endif /* (AIR_NEG__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AIR_NEG_PS                     (* (reg8 *) AIR_NEG__PS)
/* Data Register */
#define AIR_NEG_DR                     (* (reg8 *) AIR_NEG__DR)
/* Port Number */
#define AIR_NEG_PRT_NUM                (* (reg8 *) AIR_NEG__PRT) 
/* Connect to Analog Globals */                                                  
#define AIR_NEG_AG                     (* (reg8 *) AIR_NEG__AG)                       
/* Analog MUX bux enable */
#define AIR_NEG_AMUX                   (* (reg8 *) AIR_NEG__AMUX) 
/* Bidirectional Enable */                                                        
#define AIR_NEG_BIE                    (* (reg8 *) AIR_NEG__BIE)
/* Bit-mask for Aliased Register Access */
#define AIR_NEG_BIT_MASK               (* (reg8 *) AIR_NEG__BIT_MASK)
/* Bypass Enable */
#define AIR_NEG_BYP                    (* (reg8 *) AIR_NEG__BYP)
/* Port wide control signals */                                                   
#define AIR_NEG_CTL                    (* (reg8 *) AIR_NEG__CTL)
/* Drive Modes */
#define AIR_NEG_DM0                    (* (reg8 *) AIR_NEG__DM0) 
#define AIR_NEG_DM1                    (* (reg8 *) AIR_NEG__DM1)
#define AIR_NEG_DM2                    (* (reg8 *) AIR_NEG__DM2) 
/* Input Buffer Disable Override */
#define AIR_NEG_INP_DIS                (* (reg8 *) AIR_NEG__INP_DIS)
/* LCD Common or Segment Drive */
#define AIR_NEG_LCD_COM_SEG            (* (reg8 *) AIR_NEG__LCD_COM_SEG)
/* Enable Segment LCD */
#define AIR_NEG_LCD_EN                 (* (reg8 *) AIR_NEG__LCD_EN)
/* Slew Rate Control */
#define AIR_NEG_SLW                    (* (reg8 *) AIR_NEG__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AIR_NEG_PRTDSI__CAPS_SEL       (* (reg8 *) AIR_NEG__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AIR_NEG_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AIR_NEG__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AIR_NEG_PRTDSI__OE_SEL0        (* (reg8 *) AIR_NEG__PRTDSI__OE_SEL0) 
#define AIR_NEG_PRTDSI__OE_SEL1        (* (reg8 *) AIR_NEG__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AIR_NEG_PRTDSI__OUT_SEL0       (* (reg8 *) AIR_NEG__PRTDSI__OUT_SEL0) 
#define AIR_NEG_PRTDSI__OUT_SEL1       (* (reg8 *) AIR_NEG__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AIR_NEG_PRTDSI__SYNC_OUT       (* (reg8 *) AIR_NEG__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AIR_NEG__SIO_CFG)
    #define AIR_NEG_SIO_HYST_EN        (* (reg8 *) AIR_NEG__SIO_HYST_EN)
    #define AIR_NEG_SIO_REG_HIFREQ     (* (reg8 *) AIR_NEG__SIO_REG_HIFREQ)
    #define AIR_NEG_SIO_CFG            (* (reg8 *) AIR_NEG__SIO_CFG)
    #define AIR_NEG_SIO_DIFF           (* (reg8 *) AIR_NEG__SIO_DIFF)
#endif /* (AIR_NEG__SIO_CFG) */

/* Interrupt Registers */
#if defined(AIR_NEG__INTSTAT)
    #define AIR_NEG_INTSTAT            (* (reg8 *) AIR_NEG__INTSTAT)
    #define AIR_NEG_SNAP               (* (reg8 *) AIR_NEG__SNAP)
    
	#define AIR_NEG_0_INTTYPE_REG 		(* (reg8 *) AIR_NEG__0__INTTYPE)
#endif /* (AIR_NEG__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AIR_NEG_H */


/* [] END OF FILE */
