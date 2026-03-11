# linux-ia64-sn2

Restoration of the SGI SN2 (Altix) ia64 platform and drivers to Linux stable v6.19.6.

The original code was removed in kernel 5.4 via
[76f0f227cffb](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=76f0f227cffb570bc5ce343b1750f14907371d80).
This project restores it for continued use on SGI Altix hardware.

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

## Running on SKI Simulator (Emulator)

ski is an ia64  simulator that can boot the kernel without real hardware.

### Dependencies
- `ski` or `bski`
- A disk image with an ia64 rootfs (I use gentoo stage3 ia64 tarball)

### Build for SKI
```bash
make ARCH=ia64 sn2_ski_defconfig
make ARCH=ia64 CROSS_COMPILE=ia64-linux-gnu- -j$(nproc)
```

### Create disk image
```bash
dd if=/dev/zero of=sda bs=1M count=2048
mkfs.ext2 -F sda
mkdir mnt
sudo mount -o loop sda mnt
sudo tar xpf stage3-ia64-systemd-*.tar.xz -C mnt --numeric-owner
sudo umount mnt
```

### Boot
```bash
sudo bski -forcesystem -noconsole \
  arch/ia64/hp/sim/boot/bootloader \
  vmlinux \
  "root=/dev/sda simscsi=$(pwd)/sda machvec=hpsim init=/bin/bash PATH=/bin rw"
```

## Status

Work in progress.

Currently it builds and boots(and crashes)!

**Completed:**
- Restoration of 437 files: `arch/ia64/`, `arch/ia64/sn/`, `drivers/sn/`, `drivers/char/` (snsc, mspec, mbcs), `drivers/misc/ioc4`, `drivers/misc/sgi-xp/`, `drivers/tty/serial/` (sn_console, ioc4, ioc3), `drivers/pci/hotplug/sgi_hotplug`, `drivers/char/agp/sgi-agp`
- Kconfig/Makefile wiring for all restored drivers
- `drivers/firmware/qcom/Kconfig` fix (pre-existing 6.19.6 bug affecting ia64 builds)
- It compiles successfully
- In ski boots, but hits NULL ptr dereference


**Known issues:**
- There are some changes that touch core files
- We get a few build warnings, nothing too bad
- Nullptr dereference crash on boot

**Patches:**
- All current saved listed patches are in custom-linux-sgi-sn2-patch-series/
    and each represent an individual patch to apply to mainline kernel.
- The code you see in this repo has the latest commited changes

## Contributing

PRs and contributions in any way/shape/form are always welcome and highly appreciated :). 

Personally I don't have the hardware to actually test this,
so if you have access to SGI Altix hardware for testing that would be amazing

