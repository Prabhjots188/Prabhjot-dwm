/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#define TERMINAL "kitty"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */

static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10:antialias=true:autohint=true:style=Bold,Italic", "Symbols Nerd Font:size=20:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10:antialias=true:autohint=true";
#include "/home/prabhjot/.cache/wal/colors-wal-dwm.h"


/*audio constants */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

/*brightness constants*/
static const char *upbrightness[] = {"/usr/bin/brightnessctl","s","+5%",NULL};
static const char *downbrightness[] = {"/usr/bin/brightnessctl","s","5%-",NULL};


/* tagging */
static const char *tags[] = { "󰣭 ", " ", "󰉋 ", "4", "5", "6", "7", "8", "󰂯 " };
static const char *defaulttagapps[] = { "tabby", "librewolf", "nautilus", NULL, NULL, NULL, NULL, NULL, "blueman-manager" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertic    ally */
#include "vanitygaps.c"

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
        { "|M|",      centeredmaster },
        { ">M>",      centeredfloatingmaster },
        { "[@]",      spiral },
        { "[\\]",      dwindle },

};

/* key definitions */
#define MODKEY 	Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
        
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]  = { "./dmenu.sh", NULL }; /*rofi -show drun*/
static const char *screenshot[]  = { "flameshot","gui", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *launch[]  = { "j4-dmenu-desktop", NULL };
/*static const char *browser[]  = { "vivaldi"," --password-store=gnome-libsecret", NULL };*/
static const char *browser[]  = { "librewolf", NULL };
static const char *files[]  = { "nautilus", NULL };
static const char *bluetooth[]  = { "blueman-manager", NULL };
static const char *compositor[]  = { "picom", NULL };
static const char *powermenu[]  = { "/home/prabhjot/suckless/scripts/powermenu.sh", NULL };
static const char *music[]  = { "kitty", "-e", "/usr/bin/cmus", NULL };
static const char *ranger[]  = { "kitty", "-e", "/usr/bin/ranger", NULL };

static const char *termcmd2[] = { "xterm", NULL };
static const char *browsercmd[] = {"librewolf", NULL};
static const char *keepassxccmd[] = {"keepassxc", NULL};
static const char *emacscmd[] = {"emacs", NULL};

Autostarttag autostarttaglist[] = {
	{.cmd = browser, .tags = 1 << 0 },
/*        {.cmd = keepassxccmd, .tags = 1 << 4 },
	{.cmd = emacscmd, .tags = 1 << 7 },
	{.cmd = termcmd2, .tags = 1 << 8 },
	{.cmd = NULL, .tags = 0 }, */
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,      spawndefault,   {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_equal,  incrgaps,       {.i = +5 } },
	{ MODKEY|Mod1Mask,              XK_minus,  incrgaps,       {.i = -5 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY|ShiftMask,             XK_minus,  setborderpx,    {.i = -1 } },
        { MODKEY|ShiftMask,             XK_equal,  setborderpx,    {.i = +1 } },
        { MODKEY|ShiftMask,             XK_numbersign,setborderpx, {.i = 0 } },      
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
        { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[6]} },
        { MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_Right,  viewnext,       {0} },
        { MODKEY,                       XK_Left,   viewprev,       {0} },
        { MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
        { MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ MODKEY|ShiftMask,             XK_h,      spawn,          {.v = bluetooth } },
	{ MODKEY,                       XK_f,      spawn,          {.v = files } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },
        { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = compositor } },
	{ MODKEY,                       XK_o,      spawn,          {.v = launch } },
        { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = powermenu } },
        { MODKEY,                       XK_m,      spawn,          {.v = music } },
        { MODKEY,                       XK_r,      spawn,          {.v = ranger } },
        { 0,                            XK_Print,  spawn,          {.v = screenshot } },
        { 0,                            XK_Insert, spawn,          {.v = screenshot } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
        { MODKEY,                       XK_s,     scratchpad_show, {0} },
 	{ MODKEY|ShiftMask,             XK_s,     scratchpad_hide, {0} },
        { MODKEY,                       XK_minus,scratchpad_remove,{0} },




	/*audio controls*/
        { 0,                     XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
        { 0,                     XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
        { 0,                     XF86XK_AudioMute, spawn, {.v = mutevol } },
        /*brightness controls*/
	{ 0,                     XK_KP_Add,  spawn, {.v = upbrightness} },
        { 0,                    XK_KP_Subtract, spawn, {.v = downbrightness} },

};





/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* Removed key bindings */
/*{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },*/
/*{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },*/
/*static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "-nf",  "-sb",  "-sf",  NULL };*/
