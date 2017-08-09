// use MinGW gcc
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include <getopt.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

int CPORT_NR = 2;
int BDRATE = 38400;
char mode[]={'8','N','1',0};
char tx_buf[512]= {0,0,0,0,0,0,0,0,0};

void RS232_tx();
void RS232_rx();

uint8_t IsConnected = 0;

int main(int argc, char **argv) {
	int ch;
	while (1) {
        static struct option long_options[] =
          {
            {"help",       no_argument,       0, '?' },
            {"port",       required_argument, 0, 'P'},
            {"baudrate" ,  required_argument, 0, 'B'},
            {0, 0, 0, 0}
          };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        ch = getopt_long (argc, argv, "P:B:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (ch == -1)
          break;

        switch (ch) {
          case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
              break;
            printf ("option %s", long_options[option_index].name);
            if (optarg)
              printf (" with arg %s", optarg);
            printf ("\n");
            break;

          case 'B':
			BDRATE = (int)strtoimax(optarg,NULL,10);
            break;

          case 'P':
  			CPORT_NR = (int)strtoimax(optarg,NULL,10)-1;
            break;

          case '?':
            printf("\nUsage: termainal.exe [--port <com>] [--baudrate <baud>]\n");
			printf("  --port <com>, -P        Use desinated port <com>\n");
			printf("  --baudrate <baud>, -B   Set baudrate\n");
			printf("  --help, -?              Display this information\n");
			return 0;
            break;

          default:
            abort ();
          }
      }



	pthread_t id;
	char ins[512]; // input string

	int ret;
	ret=pthread_create(&id,NULL,(void *) RS232_rx,NULL);
	if(ret!=0) {
		printf ("Create pthread error!\n");
		exit (1);
	}

	if(RS232_OpenComport(CPORT_NR, BDRATE, mode)) {
		printf("Can not connect to COM%d\n",CPORT_NR+1);
	} else {
		printf("Connect to COM%d\n",CPORT_NR+1);
		IsConnected = 1;
		while ( 1 ) {
			scanf("%s",tx_buf);
			if(strcmp(tx_buf,"q")==0) break;
			RS232_cputs(CPORT_NR,tx_buf);
			RS232_SendByte(CPORT_NR, 10 );
		}
		RS232_CloseComport(CPORT_NR);
		printf("Disconnect from COM%d\n",CPORT_NR+1);
		IsConnected = 0;
	}
	return (0);
}

void RS232_tx() {
    while(1) {
        scanf("%s",tx_buf);
        RS232_cputs(CPORT_NR,tx_buf);
        #ifdef _WIN32
            Sleep(1000);
        #else
            usleep(1000000);  /* sleep for 1 Second */
        #endif
    }
  return;
}
void RS232_rx() {
    int n;
	uint8_t rx_buf[4096];
	while(1)
    while( IsConnected ) {
        n = RS232_PollComport(CPORT_NR, rx_buf, 4095);

        if(n > 0) {
            rx_buf[n] = 0;
            printf("%s",(char *)rx_buf);
        }

        #ifdef _WIN32
            Sleep(100);
        #else
            usleep(100000);  /* sleep for 100 milliSeconds */
        #endif
    }

}
