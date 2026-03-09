/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_FPU_H
#define _ASM_IA64_FPU_H

#include <uapi/asm/fpu.h>

#define fpsr_set_low(x)		((x) & 0x3f)
#define fpsr_set_high(x)	(((x) >> 6) & 0x3f)

#endif /* _ASM_IA64_FPU_H */
