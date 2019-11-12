#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
int fd = 0;
int ppos = 0;


int open_driver()
{
	fd = open("/dev/simple_char_device", O_RDWR | O_APPEND);
	printf("%i", fd);
	printf("DEVICE OPENED: simple_char_device");
	getIn();
	
	return 0;
}

int read_driver()
{
	char* device_buffer = malloc(BUFFER_SIZE);
	printf("Enter number: ");	
	scanf("%d", &ppos);
	printf("%d",ppos);
	read(fd, device_buffer, ppos);
	printf("\nData read:\n");
	printf("%s", device_buffer);
	
	free(device_buffer);
	getIn();
	return 0;
}


int write_driver()
{
	char* device_buffer = malloc(BUFFER_SIZE);
	printf("\nWrite to device:\n");
	//char buffer[BUFFER_SIZE];
	//char data[BUFFER_SIZE];
	int pos = scanf("%s", device_buffer);
	pos = strlen(device_buffer);
	printf("%i",pos);	
	write(fd, device_buffer, pos);
	
	
	free(device_buffer); 	
	getIn();
	return 0;
}


int seek_driver()
{
	int lseek_offset = 0;
	int seek_value = 0;
	printf("Enter the offset:\n");
        scanf("%d", &lseek_offset);
	printf("0 for SEEK_SET, 1 for SEEK_CUR and 2 for SEEK_END:\n");
        scanf("%d", &seek_value);
        llseek(fd, lseek_offset, seek_value);
getIn();
	return 0;	
}

int getIn()
{
	//printf("\nEnter Open('o'), Read('r'), Write('w'), Seek('s'), or Exit('e') as a command: ");	
	char c;
while ((c = getchar()) != '\n' && c!= EOF);
	//while(1){
	printf("\nEnter Open('o'), Read('r'), Write('w'), Seek('s'), or Exit('e') as a command: ");	
	c = getchar();
	if(c)
	{
		
		//printf("\nEnter Open('o'), Read('r'), Write('w'), Seek('s'), or Exit('e') as a command: ");		//printf("%c",c);
		switch(c)
		{
		case 'o': open_driver();
			  break;
		case 'r': read_driver();
			  break;
		case 'w': write_driver();
			  break;
		case 'e': printf("see ya later!");
			  break;
		case 's': seek_driver();
			  printf("seeking called");
			  break;
		default:
printf("%c\n",c);
			printf("wrong input");
			getIn();
			break;
		}
	}
	while (c != '\n' && c != EOF){
	c = getchar();
	}
	return 0;
}

int main()
{
	
	getIn();
	return 0;
	
}


