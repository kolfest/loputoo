#include <wiringSerial.h>
#include <syslog.h>
#include <unistd.h>
#include <wiringPi.h>
#include <fcntl.h> 
#include <stdio.h>
int buffer[33];
char buff[31];
int buffe;

#include <errno.h>
int main()
{
	wiringPiSetup();
	int fd2 = serialOpen("/dev/ttyAMA0", 9600);
	int count = 0;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	while(1)
	{	
 	//buffer[count]
	buffe = serialGetchar(fd2);
 	//printf("\nbuffer: %d\n", buffe);  
	if(buffe != -1)
	{
	 char buffeg = (char)buffe;
//	 printf("%c", buffeg);
 	 int fd1 = open("/home/pi/Monitoring/serial.log", O_WRONLY|O_CREAT|O_APPEND, mode);
 	 write(fd1,&buffeg,sizeof(char));
 	 close(fd1); 
         count++;
	    if(count == 34)
        {
         char newline[2] = "\n";
	char separator = '@';
//         printf("newline inserted\n");
         int fd1 = open("/home/pi/Monitoring/serial.log", O_WRONLY|O_CREAT|O_APPEND, mode);
         write(fd1,&separator,sizeof(char));
         close(fd1);
                count =0;
        }
	
	}
	} 
	serialClose(fd2);
	return 0;	

}
