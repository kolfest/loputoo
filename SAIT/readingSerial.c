#include <wiringSerial.h>
#include <syslog.h>
#include <unistd.h>
#include <wiringPi.h>
#include <fcntl.h> 
#include <stdio.h>
int buffer[33];
char buff[31];
int buffe;
typedef uint16_t crc;
#define POLYNOMIAL 0xBAAD
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc MISC_crc(uint8 const message[], int nBytes);

#include <errno.h>
int main()
{
	wiringPiSetup();
	int fd2 = serialOpen("/dev/ttyAMA0", 9600);
	int count = 0;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	while(1)
	{	

		buffe = serialGetchar(fd2);
		if(buffe != -1)
		{
			 char buffeg = (char)buffe;
 			 int fd1 = open("/home/pi/Monitoring/serial.log", O_WRONLY|O_CREAT|O_APPEND, mode);
 			 write(fd1,&buffeg,sizeof(char));
 			 close(fd1); 
 		         count++;
  		    	
			 if(count == 34)
       		         {	
			   		
     			   char separator = '@';
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

crc
MISC_crc(uint8_t const message[], int nBytes)
{
    crc  remainder = 0;	

    for (int byte = 0; byte < nBytes; ++byte)
    {

        remainder ^= (message[byte] << (WIDTH - 8));
        for (uint8_t bit = 8; bit > 0; --bit)
        {

            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);
}
