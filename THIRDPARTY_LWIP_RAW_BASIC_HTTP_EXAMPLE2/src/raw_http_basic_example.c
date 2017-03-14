/**
 * \file
 *
 * \brief lwIP Raw HTTP basic example.
 *
 * Copyright (c) 2012-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 *  \mainpage lwIP Raw HTTP basic example
 *
 *  \section Purpose
 *  This documents data structures, functions, variables, defines, enums, and
 *  typedefs in the software for the lwIP Raw HTTP basic example.
 *
 *  The given example is a lwIP example using the current lwIP stack and MAC driver.
 *
 *  \section Requirements
 *
 *  This package can be used with SAM3X-EK,SAM4E-EK,SAMV71 and SAME70.
 *
 *  \section Description
 *
 *  This example features a simple lwIP web server.
 *  - Plug the Ethernet cable directly into the evaluation kit to connect to the PC.
 *  - Configuring the PC network port to local mode to setup a 'point to point' network.
 *  - Start the example.
 *  - Launch your favorite web browser.
 *  - Type the WEB server example IP address in your browser's address bar.
 *
 *  \section Usage
 *
 *  -# Build the program and download it into the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or the
 *     <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *     IAR EWARM User and reference guides</a>,
 *     depending on the solutions that users choose.
 *  -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (if DHCP mode is not enabled):
 *     \code
 *      Network up IP==xxx.xxx.xxx.xxx
 *      Static IP Address Assigned
 *     \endcode
 *
 */
#include <asf.h>
#include "sysclk.h"
#include "ioport.h"
#include "stdio_serial.h"
#include "ethernet.h"
#include "httpd.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- MODIFIED Raw HTTP Basic Example - (EE415 Opalware LLC) --"STRING_EOL \
		"-- "BOARD_NAME" --"STRING_EOL \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL


////Variables accessible from both the interrupt and main
//static volatile uint32_t count=0;
static volatile uint32_t btn;
static volatile uint32_t IP_Active=0;
static volatile uint16_t ready=1;

//ISR gets executed every time TC0 interrupt is triggered.
//void TC0_Handler()								//overwrite the TC0_Handler, which is stored in NVIC as an empty function
//{
	//if(btn==1){
		//count++;									//count the number of times the interrupt is triggered
		//if(count%100000==0)						//if enough time has passed
		//{
			//LED_Toggle(LED0);							//toggle LED

			//count=0;									//reset count
		//}
	//}
//}
/**
 *  \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#if (defined CONF_UART_CHAR_LENGTH)
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#if (defined CONF_UART_STOP_BITS)
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif
}

/**
 * \brief Main program function. Configure the hardware, initialize lwIP
 * TCP/IP stack, and start HTTP service.
 */
int main(void)
{
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure debug UART */
	configure_console();

	/* Print example information. */
	puts(STRING_HEADER);

	/* Bring up the ethernet interface & initialize timer0, channel0. */
	init_ethernet();

	/* Bring up the web server. */
	//httpd_init();						//called in ethernet.c
	
	
	////Setup Timer & Interrupt
	//pmc_enable_periph_clk(ID_TC0);				//enable peripheral clock module from PMC, so Timer Clock 0 (TC0) can use it
	//tc_init(TC0,0,TC_CMR_TCCLKS_TIMER_CLOCK4);	//Initialize TC0 to use TimerClock4 input on channel 0
	//tc_enable_interrupt(TC0,0,TC_IER_COVFS);	//enable overflow interrupt, so that TC0 interrupt is triggered when the counter overflows
	//NVIC_EnableIRQ(TC0_IRQn);					//enable the interrupt in the NVIC
	
	
	
	//Setup Sw0 BtnPress

	pio_set_input(PIOA,PIO_PA11,PIO_PULLUP);	//set sw0 push button as input and enable pullup resistor
	
	
		

	/* Program main loop. */
	while (1) {
		//get inputs
		btn = pio_get(PIOA,PIO_INPUT,PIO_PA11); //
		IP_Active=getIP_Active(); //checks with ethernet.c to see if the IP Address has been assigned yet
		ready=ready2Receive();  //checks with httpd.c if the previous TCP connection has been closed and is ready for the next
		
		/* Check for input packet and process it. */
		ethernet_task();
							
		//wait for IP_address to be assigned
		if(IP_Active==1){	

			//when btn is pressed, start the timer and initialize the chain of events to send a packet
			if(btn==0&&ready==1){
				//tc_start(TC0,0);							//Start counting
				httpd_init();		//initialize TCP connection & send packet

			}
		}
		else if(btn==0&&ready==1){printf("network is down, but ready to send");}		//for testing 
		else if(btn==0&&ready==0){printf("network is down, but not ready to send");}	//for testing


		
	}
}
