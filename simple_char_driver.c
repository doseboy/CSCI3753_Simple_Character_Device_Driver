

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */

void* device_buffer;
int open_count = 0;
int close_count = 0;
int buffer_offset = 0;



ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
	/*int readBytes;//actual bytes that will be read.
	int toReadBytes = BUFFER_SIZE - *offset;//gotta start at some byte from the buffer size.
	if(toReadBytes == 0)//if EOF is reached durrr
	{
		printk(KERN_ALERT "EOF Alert");//hey print in dmesg that there is nada to read
		return toReadBytes;//hey, why don't you stop reading because of this line...
	}
	readBytes = toReadBytes - copy_to_user(buffer, ker_buffer + *offset, toReadBytes);//way to account for offset and do copy_to_user
	printk(KERN_ALERT "Reading %d bytes\n", readBytes);//So we know whats happening in dmesg
	*offset += readBytes;//wanna reach EOF this is how!
	return readBytes;*/
	//copy_to_user(buffer, device_buffer, length);
	//printk(KERN_ALERT "reading %zu \n", length);
	//*offset = buffer_offset;
	//return 0;
	int maxbytes;           /* maximum bytes that can be read from ppos to BUFFER_SIZE*/
        int bytes_to_read;      /* gives the number of bytes to read*/
        int bytes_read;         /* number of bytes actually read*/
        maxbytes = BUFFER_SIZE - *offset;
        if (maxbytes > length)
                bytes_to_read = length;
        else
                bytes_to_read = maxbytes;
        if (bytes_to_read == 0)
                printk(KERN_ALERT "Reached the end of the device\n");

        bytes_read = bytes_to_read - copy_to_user(buffer, device_buffer + *offset, bytes_to_read);
        printk(KERN_ALERT "device has been read %d\n", bytes_read);

        *offset += bytes_read;
        printk(KERN_ALERT "device has been read\n");

        return bytes_read;
	
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	//copy_from_user(device_buffer, buffer, length);
	//*offset = buffer_offset;
	//printk(KERN_ALERT "Copied %zu bytes.", length);
	//return length;
	int maxbytes;           /* maximum bytes that can be read from ppos to BUFFER_SIZE*/
        int bytes_to_write;     /* gives the number of bytes to write*/
        int bytes_writen;       /* number of bytes actually writen*/
        maxbytes = BUFFER_SIZE - *offset;
        if (maxbytes > length)
                bytes_to_write = length;
        else
                bytes_to_write = maxbytes;

        printk(KERN_ALERT "bytestowrite %d\n", bytes_to_write);
	bytes_writen = bytes_to_write - copy_from_user(device_buffer + *offset, buffer, bytes_to_write);
        
	printk(KERN_ALERT "device has been written %d\n", bytes_writen);
        *offset += bytes_writen;
        printk(KERN_ALERT "device has been written\n");
        return bytes_writen;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	open_count++;	
	printk(KERN_ALERT "Device has opened %i", open_count);	
	return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	close_count++;
	printk(KERN_ALERT "Device has closed %i", close_count);	
	return 0;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	/* Update open file position according to the values of offset and whence */
	loff_t new_pos = 0;
	printk(KERN_ALERT "Inside seek function\n");
	switch(whence)
	{
		case 0:
			printk(KERN_ALERT "Inside set");
			new_pos = offset;
			break;
		case 1:
			printk(KERN_ALERT "Inside cur");
			new_pos = pfile->f_pos + offset;
			break;
		case 2:
			printk(KERN_ALERT "Inside end");
			new_pos = BUFFER_SIZE - offset;
			break;
	}	
	printk(KERN_ALERT "Outside switch");
	if (new_pos > BUFFER_SIZE)
                new_pos = BUFFER_SIZE;
        if (new_pos < 0)
                new_pos = 0;
        pfile->f_pos = new_pos;
	printk(KERN_ALERT "new_pos: %lld", new_pos);
        return new_pos;
}

struct file_operations simple_char_driver_file_operations = {

	.owner   = THIS_MODULE,
	.read    = simple_char_driver_read,
	.write   = simple_char_driver_write,
	.open    = simple_char_driver_open,
	.release = simple_char_driver_close,
	.llseek  = simple_char_driver_seek,

/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
};

static int simple_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	
	printk(KERN_ALERT "init\n");
	register_chrdev(235, "simple_char_device", &simple_char_driver_file_operations);
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	return 0;
}

static void simple_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "EXIT simple char driver\n");
	unregister_chrdev(235, "simple_char_device");
	kfree(device_buffer);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
