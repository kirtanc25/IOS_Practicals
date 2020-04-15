#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_AUTHOR("0xe7, 0x1e");
MODULE_DESCRIPTION("A simple character device which reverses the words in a string");
MODULE_LICENSE("GPL");

#define DEVICE_SIZE 512

char data[DEVICE_SIZE+1]=" ";

void insert_word(char *word, unsigned int n)
{
    int i, c;
    char tmpword[DEVICE_SIZE+1];
    for (i = strlen(word)-1, c = 0; i >= 0; i--, c++) {
        tmpword[c] = word[i];
    }
    tmpword[strlen(word)] = '\0';
    if (n == 0) {
        memset(data, 0, sizeof data);
        strcpy(data, tmpword);
    } else {
        data[strlen(data)] = ' ';
        data[strlen(data)+1] = '\0';
        strcat(data, tmpword);
    }
}

void reverse(char *tmpdata)
{
    int i, c;
    unsigned int n = 0;
    char word[DEVICE_SIZE+1];
    for (i = strlen(tmpdata)-1, c = 0; i >= 0; i--, c++) {
        if (tmpdata[i] == ' ') {
            word[c] = '\0';
            insert_word(word, n);
            n += 1;
            c = -1;
        } else
            word[c] = tmpdata[i];

    }
    word[c] = '\0';
    insert_word(word, n);
    data[strlen(tmpdata)] = '\0';
}

ssize_t reverse_read(struct file *filep,char *buff,size_t count,loff_t *offp )
{
    if ( copy_to_user(buff,data,strlen(data)) != 0 ) {
        printk( "Kernel -> userspace copy failed!\n" );
        return -1;
    }
    return strlen(data);
}

ssize_t reverse_write(struct file *filep,const char *buff,size_t count,loff_t *offp )
{
    char tmpdata[DEVICE_SIZE+1];
    if ( copy_from_user(tmpdata,buff,count) != 0 ) {
        printk( "Userspace -> kernel copy failed!\n" );
        return -1;
    }
    reverse(tmpdata);
    return 0;
}

struct file_operations reverse_fops = {
    read: reverse_read,
    write: reverse_write
};

static struct miscdevice reverse_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "reverse",
    .fops = &reverse_fops
};

static int __init reverse_init(void)
{
    misc_register(&reverse_misc_device);

        return 0;
}

static void __exit reverse_exit(void)
{
    misc_deregister(&reverse_misc_device);
}

module_init(reverse_init);
module_exit(reverse_exit);
