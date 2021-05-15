/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>


/*

Exercise1: Load 2 values from memory, add them and store the result back to the memory
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

/* 

Exercise2: Move the content of 'C' variable to ARM register
For the inline assembly statement, compile took these actions.
(1) First variable is read from the memory in to register
(2) Then 'r3' is used as source register in the final data copy instructions (mov)

*/

void move_variable_to_register(void)
{	
	int val = 50;
	__asm__ volatile("MOV R0, %0": : "r"(val));	
}

/*

Exercise3: Move the content of CONTROL register to 'C' variable "control_reg"

*/

void move_register_to_variable(void)
{
	int control_reg;
	__asm__ volatile("MRS %0, CONTROL": "=r"(control_reg));	
	printk("Value of control register : %d\r\n", control_reg);

}

/*

Exercise4: Copy the content of 'C' variable var1 to var2

*/

void move_by_register(void)
{
	int var1=10, var2;
	__asm__ volatile("MOV %0, %1": "=r"(var2): "r"(var1));
	printk("Value of var2 : %d\r\n", var2);
}

/* 

Exercise5: Copy the contents of a pointer into another varaible

*/

void move_pointer_value_by_register(void)
{
	int var1=20, var2, *ptr;
	ptr = &var1;
	__asm__ volatile("LDR %0, [%1]": "=r"(var2): "r"(ptr));
	printk("Value of var2 : %d\r\n", var2);
	
}


void main(void)
{
	fun_add();
	move_variable_to_register();
	move_register_to_variable();
	move_by_register();
        move_pointer_value_by_register();
}
