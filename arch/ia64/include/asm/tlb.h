/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_TLB_H
#define _ASM_IA64_TLB_H
/*
 * Based on <asm-generic/tlb.h>.
 *
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
/*
 * Removing a translation from a page table (including TLB-shootdown) is a four-step
 * procedure:
 *
 *	(1) Flush (virtual) caches --- ensures virtual memory is coherent with kernel memory
 *	    (this is a no-op on ia64).
 *	(2) Clear the relevant portions of the page-table
 *	(3) Flush the TLBs --- ensures that stale content is gone from CPU TLBs
 *	(4) Release the pages that were freed up in step (2).
 *
 * Note that the ordering of these steps is crucial to avoid races on MP machines.
 *
 * The Linux kernel defines several platform-specific hooks for TLB-shootdown.  When
 * unmapping a portion of the virtual address space, these hooks are called according to
 * the following template:
 *
 *	tlb <- tlb_gather_mmu(mm, start, end);		// start unmap for address space MM
 *	{
 *	  for each vma that needs a shootdown do {
 *	    tlb_start_vma(tlb, vma);
 *	      for each page-table-entry PTE that needs to be removed do {
 *		tlb_remove_tlb_entry(tlb, pte, address);
 *		if (pte refers to a normal page) {
 *		  tlb_remove_page(tlb, page);
 *		}
 *	      }
 *	    tlb_end_vma(tlb, vma);
 *	  }
 *	}
 *	tlb_finish_mmu(tlb, start, end);	// finish unmap for address space MM
 */
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <linux/swap.h>

#include <asm-generic/tlb.h>
#include <asm/pgalloc.h>
#include <asm/processor.h>
#include <asm/tlbflush.h>
#include <asm/machvec.h>

/*
 * If we can't allocate a page to make a big batch of page pointers
 * to work on, then just handle a few from the on-stack structure.
 */
#define	IA64_GATHER_BUNDLE	8

struct ia64_tr_entry {
	u64 ifa;
	u64 itir;
	u64 pte;
	u64 rr;
}; /*Record for tr entry!*/

extern int ia64_itr_entry(u64 target_mask, u64 va, u64 pte, u64 log_size);
extern void ia64_ptr_entry(u64 target_mask, int slot);

extern struct ia64_tr_entry *ia64_idtrs[NR_CPUS];

/*
 region register macros
*/
#define RR_TO_VE(val)   (((val) >> 0) & 0x0000000000000001)
#define RR_VE(val)	(((val) & 0x0000000000000001) << 0)
#define RR_VE_MASK	0x0000000000000001L
#define RR_VE_SHIFT	0
#define RR_TO_PS(val)	(((val) >> 2) & 0x000000000000003f)
#define RR_PS(val)	(((val) & 0x000000000000003f) << 2)
#define RR_PS_MASK	0x00000000000000fcL
#define RR_PS_SHIFT	2
#define RR_RID_MASK	0x00000000ffffff00L
#define RR_TO_RID(val) 	((val >> 8) & 0xffffff)

static inline void
arch_tlb_flush(struct mmu_gather *tlb) 
{
	unsigned long start = tlb->start;
	unsigned long end = tlb->end;

	if (tlb->fullmm) {
		/*
		 * Tearing down the entire address space.  This happens both as a result
		 * of exit() and execve().  The latter case necessitates the call to
		 * flush_tlb_mm() here.
		 */
		flush_tlb_mm(tlb->mm);
	} else if (unlikely (end - start >= 1024*1024*1024*1024UL
			     || REGION_NUMBER(start) != REGION_NUMBER(end - 1)))
	{
		/*
		 * If we flush more than a tera-byte or across regions, we're probably
		 * better off just flushing the entire TLB(s).  This should be very rare
		 * and is not worth optimizing for.
		 */
		flush_tlb_all();
	} else {
		/*
		 * flush_tlb_range() takes a vma instead of a mm pointer because
		 * some architectures want the vm_flags for ITLB/DTLB flush.
		 */
		struct vm_area_struct vma = TLB_FLUSH_VMA(tlb->mm, 0);

		/* flush the address range from the tlb: */
		flush_tlb_range(&vma, start, end);
		/* now flush the virt. page-table area mapping the address range: */
		flush_tlb_range(&vma, ia64_thash(start), ia64_thash(end));
	}

}

#define tlb_migrate_finish(mm)	platform_tlb_migrate_finish(mm)

#define tlb_start_vma(tlb, vma)			
#define tlb_end_vma(tlb, vma)		

#define tlb_remove_tlb_entry(tlb, ptep, addr)		\
	__tlb_remove_tlb_entry(tlb, ptep, addr);

#define tlb_remove_huge_tlb_entry(h, tlb, ptep, address)	\
	tlb_remove_tlb_entry(tlb, ptep, address)

#define tlb_remove_check_page_size_change tlb_remove_check_page_size_change
static inline void tlb_remove_check_page_size_change(struct mmu_gather *tlb,
						     unsigned int page_size)
{
}

#ifndef pte_free_tlb
#define pte_free_tlb(tlb, ptep, address)		\
	__pte_free_tlb(tlb, ptep, address);
#endif

#ifndef pmd_free_tlb
#define pmd_free_tlb(tlb, ptep, address)		\
	__pmd_free_tlb(tlb, ptep, address);
#endif

#ifndef pud_free_tlb
#define pud_free_tlb(tlb, pudp, address)		\
	__pud_free_tlb(tlb, pudp, address);
#endif


/*
// XXX: Hacky fix for some tbl dual includes. We should search for root cause istead
#ifndef tlb_delay_rmap
#define tlb_delay_rmap(tlb) 
#endif
#ifndef tlb_flush_rmaps
#define tlb_flush_rmaps(tlb, vma) 
#endif
#ifndef tlb_change_page_size
#define tlb_change_page_size(tlb, page_size) 
#endif
#ifndef tlb_remove_tlb_entries
#define tlb_remove_tlb_entries(tlb, ptep, nr, page_size) 
#endif
#ifndef __tlb_remove_folio_pages
#define __tlb_remove_folio_pages(tlb, page, nr, flags) 
#endif
#ifndef tlb_free_vmas
#define tlb_free_vmas(tlb) 
#endif
*/

#endif /* _ASM_IA64_TLB_H */
