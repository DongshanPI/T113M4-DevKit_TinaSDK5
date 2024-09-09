#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "interrupt.h"
#include <portmacro.h>
#include "FreeRTOS.h"
#include "task.h"

#include <openamp/sunxi_helper/openamp.h>
#include <console.h>

#ifdef CONFIG_DRIVERS_MSGBOX
#include <hal_msgbox.h>
#endif

#ifdef CONFIG_COMPONENTS_AW_DEVFS
#include <devfs.h>
#endif

#ifdef CONFIG_COMPONENTS_OPENAMP
#include <openamp/sunxi_helper/rpmsg_master.h>

extern int openamp_init(void);
extern int rpbuf_init(void);

void openamp_init_thread(void *param)
{
        (void)param;

        openamp_init();

#ifdef CONFIG_RPMSG_CLIENT
        rpmsg_ctrldev_create();
#endif

#ifdef CONFIG_RPMSG_HEARBEAT
        extern int rpmsg_heart_init(void);
        rpmsg_heart_init();
#endif

#ifdef CONFIG_MULTI_CONSOLE
        extern int multiple_console_init(void);
        multiple_console_init();
#endif

#ifdef CONFIG_COMPONENTS_RPBUF
extern int rpbuf_init(void);
	rpbuf_init();
#endif
        hal_thread_stop(NULL);
}
#endif

void cpu0_app_entry(void *param)
{
        (void)param;

#ifdef CONFIG_COMPONENTS_AW_DEVFS
	devfs_mount("/dev");
#endif

#if defined CONFIG_COMPONENTS_OPENAMP
        void *thread;
        thread = hal_thread_create(openamp_init_thread, NULL,
				"amp_init", 8 * 1024, HAL_THREAD_PRIORITY_SYS);
        if (thread != NULL)
            hal_thread_start(thread);
#endif

#ifdef CONFIG_COMPONENT_CLI
    vCommandConsoleStart(0x1000, HAL_THREAD_PRIORITY_CLI, NULL);
#endif

    	vTaskDelete(NULL);
}
