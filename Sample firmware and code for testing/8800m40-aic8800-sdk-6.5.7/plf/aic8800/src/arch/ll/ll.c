/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/

#include "ll.h"

/*****************************************************************************/
/* Variables                                                                 */
/*****************************************************************************/

static unsigned int critical_sect_count = 0U;
static unsigned int critical_ctxt_saved = 0U;

/*****************************************************************************/
/* Functions                                                                 */
/*****************************************************************************/

void critical_section_start(void)
{
    if (__get_IPSR() == 0U) {
        if  (0U == critical_sect_count) {
            critical_ctxt_saved = __get_PRIMASK();
            __disable_irq();
        }
        critical_sect_count++;
    }
}

void critical_section_end(void)
{
    if (__get_IPSR() == 0U) {
        critical_sect_count--;
        if  (0U == critical_sect_count) {
            __set_PRIMASK(critical_ctxt_saved);
        }
    }
}
