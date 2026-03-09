/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_ASM_PROTOTYPES_H
#define _ASM_IA64_ASM_PROTOTYPES_H

#include <linux/types.h>

#include <asm/cacheflush.h>
#include <asm/checksum.h>
#include <asm/esi.h>
#include <asm/ftrace.h>
#include <asm/page.h>
#include <asm/pal.h>
#include <asm/string.h>
#include <linux/uaccess.h>
#include <asm/unwind.h>
#include <asm/xor.h>

#define do_fork kernel_clone
#define sys_bdflush sys_ni_syscall
#define sys_sysctl sys_ni_syscall
#define sys_lookup_dcookie sys_ni_syscall

extern struct resource crashk_res;
extern void ia64_delay_loop(unsigned long loops);
extern void ia64_switch_mode_phys(void);
extern void ia64_switch_mode_virt(void);
extern void ia64_jump_to_sal(void);
extern void ia64_save_debug_regs(unsigned long *save_area);
extern void ia64_load_debug_regs(unsigned long *save_area);
extern void __ia64_save_fpu(void *fpu_save_area);
extern char init_stack[THREAD_SIZE];

extern void *memcpy(void *, const void *, __kernel_size_t);
extern void *memset(void *, int, __kernel_size_t);
extern __kernel_size_t strlen(const char *);

extern const char ia64_ivt[];

extern void ia64_ivt(void);
extern void clear_page(void *page);
extern void copy_page(void *to, void *from);
extern void *memcpy(void *to, const void *from, size_t n);
extern void *memset(void *s, int c, size_t n);
extern size_t strlen(const char *s);

signed int __divsi3(signed int, unsigned int);
signed int __modsi3(signed int, unsigned int);

signed long long __divdi3(signed long long, unsigned long long);
signed long long __moddi3(signed long long, unsigned long long);

unsigned int __udivsi3(unsigned int, unsigned int);
unsigned int __umodsi3(unsigned int, unsigned int);

unsigned long long __udivdi3(unsigned long long, unsigned long long);
unsigned long long __umoddi3(unsigned long long, unsigned long long);

extern struct ia64_pal_retval ia64_pal_call_static(u64, u64, u64, u64);
extern struct ia64_pal_retval ia64_pal_call_stacked(u64, u64, u64, u64);
extern struct ia64_pal_retval ia64_pal_call_phys_static(u64, u64, u64, u64);
extern struct ia64_pal_retval ia64_pal_call_phys_stacked(u64, u64, u64, u64);

#endif /* _ASM_IA64_ASM_PROTOTYPES_H */
