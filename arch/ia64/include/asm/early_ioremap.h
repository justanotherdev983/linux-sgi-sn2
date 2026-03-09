/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_EARLY_IOREMAP_H
#define _ASM_IA64_EARLY_IOREMAP_H

/* 
#include <asm-generic/early_ioremap.h>
XXX: Hacky maybe, TESTING BOU
extern void __iomem * early_ioremap (unsigned long phys_addr, unsigned long size);
#define early_memremap(phys_addr, size)        early_ioremap(phys_addr, size)

extern void early_iounmap (volatile void __iomem *addr, unsigned long size);
#define early_memunmap(addr, size)             early_iounmap(addr, size)
*/

extern void __iomem *early_ioremap(unsigned long phys_addr, unsigned long size);
extern void early_iounmap(volatile void __iomem *addr, unsigned long size);

static inline void *early_memremap(unsigned long phys_addr, unsigned long size)
{ return (void *)early_ioremap(phys_addr, size); }
static inline void *early_memremap_ro(unsigned long phys_addr, unsigned long size)
{ return (void *)early_ioremap(phys_addr, size); }
static inline void early_memunmap(void *addr, unsigned long size)
{ early_iounmap((volatile void __iomem *)addr, size); }

#define early_memremap_prot(phys, size, prot) early_memremap(phys, size)

#define early_ioremap_init()  do {} while (0)


#endif
