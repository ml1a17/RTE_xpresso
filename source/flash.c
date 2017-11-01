/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    flash.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKW41Z4.h"
#include "FreeRTOS.h"
#include "task.h"
/* TODO: insert other include files here. */
#define NUM_LEDS  (4)                   // Number of available LEDs
                           /*   rgb_red,   rgb_blue,  rgb_green,        red */
const uint32_t led_pin[]  = {         1,         18,         19,          0};
const uint32_t led_port[] = {PORTC_BASE, PORTA_BASE, PORTA_BASE, PORTB_BASE};
const uint32_t led_gpio[] = {GPIOC_BASE, GPIOA_BASE, GPIOA_BASE, GPIOB_BASE};

/* TODO: insert other definitions and declarations here. */



/*
 * @brief   Application entry point.
 */

/**
  \fn          int32_t LED_Initialize (void)
  \brief       Initialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_Initialize (void) {
  uint32_t i;

  SIM->SCGC5 |= ((1U << SIM_SCGC5_PORTA_SHIFT) |
                 (1U << SIM_SCGC5_PORTB_SHIFT) |
                 (1U << SIM_SCGC5_PORTC_SHIFT)  );

  /* Port Initialization */
  for (i = 0; i < NUM_LEDS; i++) {
    ((PORT_Type *)led_port[i])->PCR[led_pin[i]] = (1U << 8);
    ((PORT_Type *)led_port[i])->ISFR           &= (1U << led_pin[i]);
  }

  /* GPIO Initialization */
  for (i = 0; i < NUM_LEDS; i++) {
    ((GPIO_Type *)led_gpio[i])->PDOR           |=  (1U << led_pin[i]);
    ((GPIO_Type *)led_gpio[i])->PDDR           |=  (1U << led_pin[i]);
  }

//  LED_SetOut(0);

  return 0;
}



/**
  \fn          int32_t LED_On (uint32_t num)
  \brief       Turn on requested LED
  \param[in]   num  LED number
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_On (uint32_t num) {

  if (num < NUM_LEDS) {
    ((GPIO_Type *)led_gpio[num])->PCOR  =  (1U << led_pin[num]);
  }

  return 0;
}

/**
  \fn          int32_t LED_Off (uint32_t num)
  \brief       Turn off requested LED
  \param[in]   num  LED number
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_Off (uint32_t num) {

  if (num < NUM_LEDS) {
    ((GPIO_Type *)led_gpio[num])->PSOR  =  (1U << led_pin[num]);
  }

  return 0;
}

void led1_task(void *pvParmeters)
{
	while(1)
	{
		LED_On(1);
		vTaskDelay( 500 );
		LED_Off(1);
		vTaskDelay( 500 );
	}
}

void led2_task(void *pvParmeters)
{
	while(1)
	{
		LED_On(3);
		vTaskDelay( 1000 );
		LED_Off(3);
		vTaskDelay( 1000 );
	}
}


int main(void) {

	LED_Initialize();                                            // initialize LEDs
    xTaskCreate(led1_task,"led1",configMINIMAL_STACK_SIZE,NULL,configMAX_PRIORITIES-3,NULL);
    xTaskCreate(led2_task,"led2",configMINIMAL_STACK_SIZE+400,NULL,configMAX_PRIORITIES-3,NULL);

    vTaskStartScheduler();
    while(1);

}
