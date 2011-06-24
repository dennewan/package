// testVRPNclient.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <vrpn_Analog.h> 
 
 
/***************************************************************************** 
 * 
   Callback handler 
 * 
 *****************************************************************************/ 
 
void	VRPN_CALLBACK handle_analog(void *userdata, vrpn_ANALOGCB b) 
{ 
  for (int i=0; i< 3; i++)
	printf("Chan[%d] = %lf\n", i, b.channel[i]);

  printf("time = %lf\n", b.channel[3]);
} 
 
int main(int argc, char *argv[]) 
{	
	if(argc != 2)
	{
		fprintf(stderr,"incompatible number of argument");
		return 0;
	}

	char adresse[20];
	sprintf(adresse,"data@%s:3883",argv[1]);
	printf("%s\n",adresse);
	
	int	done = 0; 
	vrpn_Analog_Remote *ana; 
 
	/* initialize the analog */ 
	ana = new vrpn_Analog_Remote(adresse); 
 
	// Set up the analog callback handler 
	ana->register_change_handler(NULL, handle_analog); 
 
/*  
 * main interactive loop 
 */ 
while ( ! done ) 
    { 
	// Let the  analog device do its thing 
	ana->mainloop(); 
    } 
 
}   /* main */
