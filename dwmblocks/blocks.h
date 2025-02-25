//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
     /* {"",    "sb-brightness",    5,      16},*/
        {"",    "sb-internet",      1,      16},
      /*{"",    "sb-nettraf",       1,      16},*/
        {"",    "sb-player",        0,      16},
	{"",    "sb-battery",       5,      3},
	{"", "date '+%b %d (%a) %I:%M%p'",					5,		0},

};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 6;
