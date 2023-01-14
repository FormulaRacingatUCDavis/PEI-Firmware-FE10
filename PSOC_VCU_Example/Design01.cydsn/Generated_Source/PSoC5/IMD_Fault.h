/*******************************************************************************
* File Name: IMD_Fault.h  
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

#if !defined(CY_PINS_IMD_Fault_H) /* Pins IMD_Fault_H */
#define CY_PINS_IMD_Fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IMD_Fault_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IMD_Fault__PORT == 15 && ((IMD_Fault__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IMD_Fault_Write(uint8 value);
void    IMD_Fault_SetDriveMode(uint8 mode);
uint8   IMD_Fault_ReadDataReg(void);
uint8   IMD_Fault_Read(void);
void    IMD_Fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   IMD_Fault_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IMD_Fault_SetDriveMode() function.
     *  @{
     */
        #define IMD_Fault_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IMD_Fault_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IMD_Fault_DM_RES_UP          PIN_DM_RES_UP
        #define IMD_Fault_DM_RES_DWN         PIN_DM_RES_DWN
        #define IMD_Fault_DM_OD_LO           PIN_DM_OD_LO
        #define IMD_Fault_DM_OD_HI           PIN_DM_OD_HI
        #define IMD_Fault_DM_STRONG          PIN_DM_STRONG
        #define IMD_Fault_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IMD_Fault_MASK               IMD_Fault__MASK
#define IMD_Fault_SHIFT              IMD_Fault__SHIFT
#define IMD_Fault_WIDTH              1u

/* Interrupt constants */
#if defined(IMD_Fault__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IMD_Fault_SetInterruptMode() function.
     *  @{
     */
        #define IMD_Fault_INTR_NONE      (uint16)(0x0000u)
        #define IMD_Fault_INTR_RISING    (uint16)(0x0001u)
        #define IMD_Fault_INTR_FALLING   (uint16)(0x0002u)
        #define IMD_Fault_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IMD_Fault_INTR_MASK      (0x01u) 
#endif /* (IMD_Fault__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IMD_Fault_PS                     (* (reg8 *) IMD_Fault__PS)
/* Data Register */
#define IMD_Fault_DR                     (* (reg8 *) IMD_Fault__DR)
/* Port Number */
#define IMD_Fault_PRT_NUM                (* (reg8 *) IMD_Fault__PRT) 
/* Connect to Analog Globals */                                                  
#define IMD_Fault_AG                     (* (reg8 *) IMD_Fault__AG)                       
/* Analog MUX bux enable */
#define IMD_Fault_AMUX                   (* (reg8 *) IMD_Fault__AMUX) 
/* Bidirectional Enable */                                                        
#define IMD_Fault_BIE                    (* (reg8 *) IMD_Fault__BIE)
/* Bit-mask for Aliased Register Access */
#define IMD_Fault_BIT_MASK               (* (reg8 *) IMD_Fault__BIT_MASK)
/* Bypass Enable */
#define IMD_Fault_BYP                    (* (reg8 *) IMD_Fault__BYP)
/* Port wide control signals */                                                   
#define IMD_Fault_CTL                    (* (reg8 *) IMD_Fault__CTL)
/* Drive Modes */
#define IMD_Fault_DM0                    (* (reg8 *) IMD_Fault__DM0) 
#define IMD_Fault_DM1                    (* (reg8 *) IMD_Fault__DM1)
#define IMD_Fault_DM2                    (* (reg8 *) IMD_Fault__DM2) 
/* Input Buffer Disable Override */
#define IMD_Fault_INP_DIS                (* (reg8 *) IMD_Fault__INP_DIS)
/* LCD Common or Segment Drive */
#define IMD_Fault_LCD_COM_SEG            (* (reg8 *) IMD_Fault__LCD_COM_SEG)
/* Enable Segment LCD */
#define IMD_Fault_LCD_EN                 (* (reg8 *) IMD_Fault__LCD_EN)
/* Slew Rate Control */
#define IMD_Fault_SLW                    (* (reg8 *) IMD_Fault__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IMD_Fault_PRTDSI__CAPS_SEL       (* (reg8 *) IMD_Fault__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IMD_Fault_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IMD_Fault__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IMD_Fault_PRTDSI__OE_SEL0        (* (reg8 *) IMD_Fault__PRTDSI__OE_SEL0) 
#define IMD_Fault_PRTDSI__OE_SEL1        (* (reg8 *) IMD_Fault__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IMD_Fault_PRTDSI__OUT_SEL0       (* (reg8 *) IMD_Fault__PRTDSI__OUT_SEL0) 
#define IMD_Fault_PRTDSI__OUT_SEL1       (* (reg8 *) IMD_Fault__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IMD_Fault_PRTDSI__SYNC_OUT       (* (reg8 *) IMD_Fault__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IMD_Fault__SIO_CFG)
    #define IMD_Fault_SIO_HYST_EN        (* (reg8 *) IMD_Fault__SIO_HYST_EN)
    #define IMD_Fault_SIO_REG_HIFREQ     (* (reg8 *) IMD_Fault__SIO_REG_HIFREQ)
    #define IMD_Fault_SIO_CFG            (* (reg8 *) IMD_Fault__SIO_CFG)
    #define IMD_Fault_SIO_DIFF           (* (reg8 *) IMD_Fault__SIO_DIFF)
#endif /* (IMD_Fault__SIO_CFG) */

/* Interrupt Registers */
#if defined(IMD_Fault__INTSTAT)
    #define IMD_Fault_INTSTAT            (* (reg8 *) IMD_Fault__INTSTAT)
    #define IMD_Fault_SNAP               (* (reg8 *) IMD_Fault__SNAP)
    
	#define IMD_Fault_0_INTTYPE_REG 		(* (reg8 *) IMD_Fault__0__INTTYPE)
#endif /* (IMD_Fault__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IMD_Fault_H */


/* [] END OF FILE */
