/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

void generate_interrupt(void)
{
	uint32_t *pSTIR  =  (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= (1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);
}

void change_access_level_unpriv(void)
{
	//read
	__asm__ volatile ("MRS R0, CONTROL");
	//modify
	__asm__ volatile ("ORR R0, R0, #0x01");
	//write
	__asm__ volatile ("MSR CONTROL, R0");
}

void main(void)
{
	change_access_level_unpriv();
	//generate_interrupt();
}

void HardFault_Handler(void)
{
	printk("Hard fault detected\r\n");
	while(1);
}