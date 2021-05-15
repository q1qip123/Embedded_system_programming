/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>


/*
Load 2 values from memory, add them and store the result back to the memory
using inline assembly statements.
*/

void fun_add(void)
{
	__asm__ volatile ("LDR  R0, =#0x20001000");
	__asm__ volatile ("LDR  R0, =#0x20001004");
	__asm__ volatile ("LDR  R0, [R1]");
	__asm__ volatile ("LDR  R1, [R2]");
	__asm__ volatile ("ADD  R0, R0, R1");
	__asm__ volatile ("STR  R0, [R2]");

	__asm__ volatile (
			"LDR  R0, =#0x20001000\n\t"
			"LDR  R0, =#0x20001004\n\t"
			"LDR  R0, [R1]\n\t"
			"LDR  R1, [R2]\n\t"
			"ADD  R0, R0, R1\n\t"
			"STR  R0, [R2]\n\t"
			);
}

void main(void)
{
	fun_add();
}
