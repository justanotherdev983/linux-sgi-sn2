/* arch/ia64/include/asm/efi.h */
#ifndef _ASM_IA64_EFI_H
#define _ASM_IA64_EFI_H

typedef int (*efi_freemem_callback_t) (u64 start, u64 end, void *arg);
extern void efi_memmap_walk (efi_freemem_callback_t callback, void *arg);
extern void efi_memmap_walk_uc (efi_freemem_callback_t callback, void *arg);

#endif
