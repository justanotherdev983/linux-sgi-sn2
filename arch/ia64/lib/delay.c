/* SPDX-License-Identifier: GPL-2.0 */
#include <linux/export.h>
#include <linux/sched.h>
#include <asm/processor.h>

void ia64_delay_loop(unsigned long loops)
{
	unsigned long start = ia64_getreg(_IA64_REG_AR_ITC);
	while (ia64_getreg(_IA64_REG_AR_ITC) - start < loops)
		cpu_relax();
}
EXPORT_SYMBOL(ia64_delay_loop);
