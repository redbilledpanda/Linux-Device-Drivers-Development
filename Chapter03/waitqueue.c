#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

// -- AIJAZ --
#include <linux/jiffies.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq);
static int condition = 0;

/* declare a work queue*/
static struct work_struct wrk;

static void work_handler(struct work_struct *work)
{ 
    pr_info("Waitqueue module handler %s, ms cnt is %u\n", __FUNCTION__, jiffies_to_msecs(jiffies));
    msleep(3000);
    pr_info("Wake up the sleeping module\n");
    condition = 1;
    wake_up_interruptible(&my_wq);
}

static int __init my_init(void)
{
    pr_info("Wait queue example, ms count is %u\n", jiffies_to_msecs(jiffies));

    INIT_WORK(&wrk, work_handler);
    schedule_work(&wrk);

    pr_info("Going to sleep %s\n", __FUNCTION__);
    wait_event_interruptible(my_wq, condition != 0);

    pr_info("woken up by the work job at %ums\n", jiffies_to_msecs(jiffies));
    return 0;
}

void my_exit(void)
{
    pr_info("waitqueue example cleanup\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>");
MODULE_LICENSE("GPL");
