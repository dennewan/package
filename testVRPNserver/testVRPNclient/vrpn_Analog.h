//----------------------------------------------------------
//************** Users deal with the following *************


// User routine to handle a change .  This is called when
// the analog callback is called (when a message from its counterpart
// across the connetion arrives).




typedef	struct {
	struct timeval	msg_time;	// Time of button press/release
	int		num_channel;		
                    // how many channels
	double		channel[vrpn_CHANNEL_MAX];  
                    // channel diliever analog values
} vrpn_ANALOGCB;


typedef void (*vrpn_ANALOGCHANGEHANDLER)(void *userdata,
					 const vrpn_ANALOGCB info);


// Open a analog device that is on the other end of a connection
// and handle updates from it.  This is the type of analog device
// that user code will  deal with.


class vrpn_Analog_Remote: public vrpn_Analog {
  public:
	// The name of the button device to connect to
	vrpn_Analog_Remote(char *name);


	// This routine calls the mainloop of the connection it's on
	virtual void mainloop(void);


	// (un)Register a callback handler to handle a button state change
	virtual int register_change_handler(void *userdata,
		vrpn_ANALOGCHANGEHANDLER handler);
	virtual int unregister_change_handler(void *userdata,
		vrpn_ANALOGCHANGEHANDLER handler);


  protected:
	typedef	struct vrpn_RBCS {
		void				*userdata;
		vrpn_ANALOGCHANGEHANDLER	handler;
		struct vrpn_RBCS		*next;
	} vrpn_ANALOGCHANGELIST;
	vrpn_ANALOGCHANGELIST	*change_list;


	static int handle_change_message(void *userdata, vrpn_HANDLERPARAM p);
};
