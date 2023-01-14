/*******************************************************************************
* File Name: GPIO2_ESD.h  
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

#if !defined(CY_PINS_GPIO2_ESD_H) /* Pins GPIO2_ESD_H */
#define CY_PINS_GPIO2_ESD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "GPIO2_ESD_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 GPIO2_ESD__PORT == 15 && ((GPIO2_ESD__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    GPIO2_ESD_Write(uint8 value);
void    GPIO2_ESD_SetDriveMode(uint8 mode);
uint8   GPIO2_ESD_ReadDataReg(void);
uint8   GPIO2_ESD_Read(void);
void    GPIO2_ESD_SetInterruptMode(uint16 position, uint16 mode);
uint8   GPIO2_ESD_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the GPIO2_ESD_SetDriveMode() function.
     *  @{
     */
        #define GPIO2_ESD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define GPIO2_ESD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define GPIO2_ESD_DM_RES_UP          PIN_DM_RES_UP
        #define GPIO2_ESD_DM_RES_DWN         PIN_DM_RES_DWN
        #define GPIO2_ESD_DM_OD_LO           PIN_DM_OD_LO
        #define GPIO2_ESD_DM_OD_HI           PIN_DM_OD_HI
        #define GPIO2_ESD_DM_STRONG          PIN_DM_STRONG
        #define GPIO2_ESD_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define GPIO2_ESD_MASK               GPIO2_ESD__MASK
#define GPIO2_ESD_SHIFT              GPIO2_ESD__SHIFT
#define GPIO2_ESD_WIDTH              1u

/* Interrupt constants */
#if defined(GPIO2_ESD__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GPIO2_ESD_SetInterruptMode() function.
     *  @{
     */
        #define GPIO2_ESD_INTR_NONE      (uint16)(0x0000u)
        #define GPIO2_ESD_INTR_RISING    (uint16)(0x0001u)
        #define GPIO2_ESD_INTR_FALLING   (uint16)(0x0002u)
        #define GPIO2_ESD_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define GPIO2_ESD_INTR_MASK      (0x01u) 
#endif /* (GPIO2_ESD__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GPIO2_ESD_PS                     (* (reg8 *) GPIO2_ESD__PS)
/* Data Register */
#define GPIO2_ESD_DR                     (* (reg8 *) GPIO2_ESD__DR)
/* Port Number */
#define GPIO2_ESD_PRT_NUM                (* (reg8 *) GPIO2_ESD__PRT) 
/* Connect to Analog Globals */                                                  
#define GPIO2_ESD_AG                     (* (reg8 *) GPIO2_ESD__AG)                       
/* Analog MUX bux enable */
#define GPIO2_ESD_AMUX                   (* (reg8 *) GPIO2_ESD__AMUX) 
/* Bidirectional Enable */                                                        
#define GPIO2_ESD_BIE                    (* (reg8 *) GPIO2_ESD__BIE)
/* Bit-mask for Aliased Register Access */
#define GPIO2_ESD_BIT_MASK               (* (reg8 *) GPIO2_ESD__BIT_MASK)
/* Bypass Enable */
#define GPIO2_ESD_BYP                    (* (reg8 *) GPIO2_ESD__BYP)
/* Port wide control signals */                                                   
#define GPIO2_ESD_CTL                    (* (reg8 *) GPIO2_ESD__CTL)
/* Drive Modes */
#define GPIO2_ESD_DM0                    (* (reg8 *) GPIO2_ESD__DM0) 
#define GPIO2_ESD_DM1                    (* (reg8 *) GPIO2_ESD__DM1)
#define GPIO2_ESD_DM2                    (* (reg8 *) GPIO2_ESD__DM2) 
/* Input Buffer Disable Override */
#define GPIO2_ESD_INP_DIS                (* (reg8 *) GPIO2_ESD__INP_DIS)
/* LCD Common or Segment Drive */
#define GPIO2_ESD_LCD_COM_SEG            (* (reg8 *) GPIO2_ESD__LCD_COM_SEG)
/* Enable Segment LCD */
#define GPIO2_ESD_LCD_EN                 (* (reg8 *) GPIO2_ESD__LCD_EN)
/* Slew Rate Control */
#define GPIO2_ESD_SLW                    (* (reg8 *) GPIO2_ESD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define GPIO2_ESD_PRTDSI__CAPS_SEL       (* (reg8 *) GPIO2_ESD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define GPIO2_ESD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) GPIO2_ESD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define GPIO2_ESD_PRTDSI__OE_SEL0        (* (reg8 *) GPIO2_ESD__PRTDSI__OE_SEL0) 
#define GPIO2_ESD_PRTDSI__OE_SEL1        (* (reg8 *) GPIO2_ESD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define GPIO2_ESD_PRTDSI__OUT_SEL0       (* (reg8 *) GPIO2_ESD__PRTDSI__OUT_SEL0) 
#define GPIO2_ESD_PRTDSI__OUT_SEL1       (* (reg8 *) GPIO2_ESD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define GPIO2_ESD_PRTDSI__SYNC_OUT       (* (reg8 *) GPIO2_ESD__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(GPIO2_ESD__SIO_CFG)
    #define GPIO2_ESD_SIO_HYST_EN        (* (reg8 *) GPIO2_ESD__SIO_HYST_EN)
    #define GPIO2_ESD_SIO_REG_HIFREQ     (* (reg8 *) GPIO2_ESD__SIO_REG_HIFREQ)
    #define GPIO2_ESD_SIO_CFG            (* (reg8 *) GPIO2_ESD__SIO_CFG)
    #define GPIO2_ESD_SIO_DIFF           (* (reg8 *) GPIO2_ESD__SIO_DIFF)
#endif /* (GPIO2_ESD__SIO_CFG) */

/* Interrupt Registers */
#if defined(GPIO2_ESD__INTSTAT)
    #define GPIO2_ESD_INTSTAT            (* (reg8 *) GPIO2_ESD__INTSTAT)
    #define GPIO2_ESD_SNAP               (* (reg8 *) GPIO2_ESD__SNAP)
    
	#define GPIO2_ESD_0_INTTYPE_REG 		(* (reg8 *) GPIO2_ESD__0__INTTYPE)
#endif /* (GPIO2_ESD__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_GPIO2_ESD_H */


/* [] END OF FILE */
