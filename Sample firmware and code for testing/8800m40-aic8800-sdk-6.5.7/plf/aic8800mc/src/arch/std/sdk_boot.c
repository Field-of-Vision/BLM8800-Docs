#include <stdlib.h>
#include <stdio.h>

#if defined (__ARMCC_VERSION)

int $Super$$main(void);

int $Sub$$main(void)
{
    return $Super$$main();
}

void _platform_post_stackheap_init(void)
{
}

#elif defined (__GNUC__)

extern int __real_main(void);

void software_init_hook(void)
{
}

int __wrap_main(void)
{
    return __real_main();
}

#elif defined (__ICCARM__)

int __low_level_init(void)
{
    return 1;
}

#else
#error unknown complier
#endif
