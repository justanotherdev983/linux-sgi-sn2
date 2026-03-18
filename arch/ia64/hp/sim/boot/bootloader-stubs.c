/* 
 * arch/ia64/hp/sim/boot/bootloader-stubs.c 
 * Needed for individual compilation and proper linking for the bootloader
 */

/* From arch/ia64/kernel/setup.c, needed by arch/ia64/lib/io.o */

#include <linux/types.h>

#define MAX_IO_SPACES 16
struct io_space {
	unsigned long mmio_base;
	int sparse;
};
struct io_space io_space[MAX_IO_SPACES];
unsigned int num_io_spaces;

int _printk(const char *fmt, ...) { return 0; }

__attribute__((weak))
void warn_slowpath_fmt(const char *file, int line,
		      unsigned int taint, const char *fmt, ...) { }
