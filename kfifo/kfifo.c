#include <linux/init.h>
#include <linux/module.h>
#include <linux/kfifo.h>

//#define PAGE_SIZE	2048
static struct kfifo out;

int kfifo_test_init(void)
{
	int i = 0;
	int ret = 0;
	unsigned char databuf[50] = {0};
	unsigned char buffer[10] = {1};
	unsigned char data[10] = {2};
	int buff_len = 10;
	
	ret = kfifo_alloc(&out, PAGE_SIZE, GFP_KERNEL);
	if(ret){
		printk("failed to allocate out fifo\n");
		goto error;
	}
	
	kfifo_in(&out, buffer, buff_len);
	
	kfifo_in(&out, data, sizeof(data));
	
	ret = kfifo_out(&out, databuf, sizeof(databuf));
	printk(KERN_ERR "ret:%d\n", ret);
	for(i=0; i< sizeof(databuf);i++)
		printk(KERN_ERR "0x%02X ", databuf[i]);
	printk(KERN_ERR "kfifo size:%d\n", kfifo_len(&out));
error:

	return ret;
}

void kfifo_test_exit(void)
{
	kfifo_free(&out);
}

module_init(kfifo_test_init);
module_exit(kfifo_test_exit);

MODULE_LICENSE("GPL");