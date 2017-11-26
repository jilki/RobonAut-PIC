/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <xc.h>
#include <pic18f43k22.h>
#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

uint16_t tcrt[8];
const int TRESHOLD = 0x8000;
const int AN_CHANNEL[] = {channel_AN18, channel_AN27, channel_AN9, channel_AN13, channel_AN1, channel_AN4, channel_AN7, channel_AN15};
void drawToLeds(void);
void sendOverSpi(void);
void setLed(int pos, int value);
void setTCRT(int pos, int value);
void main(void);

void setTCRT(int pos, int value)
{
        switch(pos)
    {
        case 0:
            IO_RC5_LAT = value;
            break;
        case 1:
            IO_RD6_LAT = value;
            break;
        case 2:
            IO_RB2_LAT = value;
            break;
        case 3:
            IO_RB4_LAT = value;
            break;
        case 4:
            IO_RA2_LAT = value;
            break;
        case 5:
            IO_RA4_LAT = value;
            break;
        case 6:
            IO_RE1_LAT = value;
            break;
        case 7:
            IO_RC2_LAT = value;
            break;            
    }
}

void setLed(int pos, int value)
{
    switch(pos)
    {
        case 0:
            IO_RC4_LAT = value;
            break;
        case 1:
            IO_RD5_LAT = value;
            break;
        case 2:
            IO_RB1_LAT = value;
            break;
        case 3:
            IO_RD2_LAT = value;
            break;
        case 4:
            IO_RA0_LAT = value;
            break;
        case 5:
            IO_RA3_LAT = value;
            break;
        case 6:
            IO_RE0_LAT = value;
            break;
        case 7:
            IO_RC1_LAT = value;
            break;            
    }
}

void drawToLeds()
{
    for(int i = 0; i<8; i++)
        setLed(i, tcrt[i]<TRESHOLD);
}

void sendOverSpi()
{
        int readDummy;
        for(int i = 0; i<8; i++)
        {
            readDummy = SPI2_Exchange8bit((char)i);
            readDummy = SPI2_Exchange8bit((char)(tcrt[i]>>8));
            readDummy = SPI2_Exchange8bit((char)tcrt[i]);
        }
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    PIN_MANAGER_Initialize();
    ADC_Initialize();
    //setLed(0,1);
    while (1)
    {
        // Add your application code
        
        for(int i = 0; i < 8; i++)
        {
            setTCRT(i, 1);
            __delay_ms(2);
            //ADC_StartConversion(AN_CHANNEL[i]);
            //while(!ADC_IsConversionDone());
            //tcrt[i] = ADC_GetConversionResult();
            tcrt[i] = ADC_GetConversion(AN_CHANNEL[i]);
            setTCRT(i, 0);
            //__delay_ms(20);
        }
        drawToLeds();
       
        
        //IO_RC4_SetHigh();
/*        IO_RC5_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN18);
        while(!ADC_IsConversionDone());
        tcrt[0] = ADC_GetConversionResult();
         IO_RC5_SetLow();
        //IO_RC5_SetLow();
        
        //IO_RD5_SetHigh();
        IO_RD6_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN27);
        while(!ADC_IsConversionDone());
        tcrt[1] = ADC_GetConversionResult();
        //IO_RD5_SetLow();
        IO_RD6_SetLow();
        
        IO_RB2_SetHigh();
        //IO_RB1_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN9);
        while(!ADC_IsConversionDone());
        tcrt[2] = ADC_GetConversionResult();
        IO_RB2_SetLow();
        //IO_RB1_SetLow();

        IO_RB4_SetHigh();
        //IO_RD2_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN13);
        while(!ADC_IsConversionDone());
        tcrt[3] = ADC_GetConversionResult();
        IO_RB4_SetLow();
        //IO_RD2_SetLow();
        
        IO_RA2_SetHigh();
        //IO_RA0_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN1);
        while(ADC_IsConversionDone());
        tcrt[4] = ADC_GetConversionResult();
        IO_RA2_SetLow();
        //IO_RA0_SetLow();
 
        IO_RA4_SetHigh();
        //IO_RA3_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN4);
        while(ADC_IsConversionDone());
        tcrt[5] = ADC_GetConversionResult();
        IO_RA4_SetLow();
        //IO_RA3_SetLow();
        
        IO_RE1_SetHigh();
        //IO_RE0_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN7);
        while(ADC_IsConversionDone());
        tcrt[6] = ADC_GetConversionResult();
        IO_RE1_SetLow();
        //IO_RE0_SetLow();
        
        IO_RC2_SetHigh();
        //IO_RC1_SetHigh();
        __delay_ms(20);
        ADC_StartConversion(channel_AN15);
        while(ADC_IsConversionDone());
        tcrt[7] = ADC_GetConversionResult();
        IO_RC2_SetLow();
        //IO_RC1_SetLow();
        drawToLeds();
*/ 
        //__delay_ms(1000);
    }
}
/**
 End of File
*/