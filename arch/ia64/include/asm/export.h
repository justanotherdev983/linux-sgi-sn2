/* EXPORT_DATA_SYMBOL != EXPORT_SYMBOL here */
#define KSYM_FUNC(name) @fptr(name)
#include <linux/export.h>

#define EXPORT_DATA_SYMBOL(name)	EXPORT_SYMBOL(name)
#define EXPORT_DATA_SYMBOL_GPL(name)	EXPORT_SYMBOL_GPL(name)
