#include "stdafx.h"
#include <vrpn_Connection.h>
#include <vrpn_Analog.h>

#include <stdio.h> 
#include <stdlib.h> 

void init_data_magic (int, char **) {

}
void do_data_magic (double * channels) {
  static int done = 0;

  if (!done) {
    channels[0] = 0.0;
	channels[1] = 0.0;
	channels[2] = 0.0;
	channels[3] = 0.0;
    done = 1;
  } else
  {
	  if(channels[0]>50)
	  {
		channels[0] = 0.0;
		channels[1] = 0.0;
		channels[2] = 0.0;
	  }
	  else
	  {
		channels[0] += 1;
		channels[1] += 1;
		channels[2] += 1;
	  }
	  channels[3] += 1;
    
  }
}


int main (int argc, char ** argv) {

  vrpn_Connection * c;
  vrpn_Analog_Server * data;


  struct timeval delay;
 
  c = vrpn_create_server_connection(":3883","logIN.txt","logOUT.txt");
  data = new vrpn_Analog_Server ("data", c);
  data->setNumChannels(4);
 
  printf("Services named data now listening on port %d.\n", vrpn_DEFAULT_LISTEN_PORT_NO);

  delay.tv_sec = 0L;
  delay.tv_usec = 50000L;

  init_data_magic(argc, argv);
  while (1) {

    do_data_magic(data->channels());
    data->report_changes();

    c->mainloop(&delay);
fprintf(stderr, "while():  x = %.2g, y = %.2g, z = %.2g.\n", data->channels()[0],
data->channels()[1],data->channels()[2]);
  }
}


