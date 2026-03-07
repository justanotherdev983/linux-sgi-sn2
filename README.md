# linux-ia64-sn2

Restoration of the SGI SN2 (Altix) ia64 platform and drivers to Linux stable v6.19.6.

The original code was removed in kernel 5.4 via
[76f0f227cffb](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=76f0f227cffb570bc5ce343b1750f14907371d80).
This project restores it for continued use on SGI Altix hardware. Not intended for upstream submission — this is a maintained out-of-tree port.

## Base

- `v6.19.6` linux-stable
- Donor commit: `d80db5c1ed8d` (last commit before ia64/SN2 deletion)

NOTE:
For this git(hub) repo i cloned the linux-stable v6.19.6 branch
and deleted .git and manually commit it as initial base commit,
because I cant push a shallow clone without clean diff's I applied.

!!!So all original git history is completly gone unfortunatly!!!

## Dependencies

- ia64-linux-gnu-gcc (or any itanium64 C compiler

## Build

```bash
make ARCH=ia64 CROSS_COMPILE=ia64-linux-gnu- defconfig

# Build
time make ARCH=ia64 CROSS_COMPILE=ia64-linux-gnu- -j$(nproc)
```

## Status

Work in progress — header compatibility fixes for modern kernel APIs are ongoing.

**Completed:**
- Restoration of 437 files: `arch/ia64/`, `arch/ia64/sn/`, `drivers/sn/`, `drivers/char/` (snsc, mspec, mbcs), `drivers/misc/ioc4`, `drivers/misc/sgi-xp/`, `drivers/tty/serial/` (sn_console, ioc4, ioc3), `drivers/pci/hotplug/sgi_hotplug`, `drivers/char/agp/sgi-agp`
- Kconfig/Makefile wiring for all restored drivers
- `drivers/firmware/qcom/Kconfig` fix (pre-existing 6.19.6 bug affecting ia64 builds)
- defconfig generates successfully

**In progress:**
- Header compatibility fixes: atomics, bitops, pgtable, uaccess, thread_info
- `task_thread_info` override for ia64's unique task/thread_info/RBS contiguous allocation layout

**Known issues:**
- `drivers/ide/sgiioc4.c` restored but not wired in — IDE subsystem removed in 6.x
- `task_thread_info` conflict with `include/linux/sched.h` pending resolution

**Patches:**
- All current saved listed patches are in patch-series/ 
    and each represent an individual patch to apply to mainline kernel.
- The code you see in this repo has the latest commited changes

## Contributing

PRs and contributions in any way/shape/form are always welcome and highly appreciated :). 

Personally I don't have the hardware to actually test this,
so if you have access to SGI Altix hardware for testing that would be amazing

