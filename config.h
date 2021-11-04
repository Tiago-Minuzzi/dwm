/* See LICENSE file for copyright and license details. */
#include "movestack.c"
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "Font Awesome 5 Free Solid:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#171a1f";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#4877b1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    /* Floating apps */
    { "Gnome-calculator",       NULL,       NULL,       0,            1,           -1 },
    { "Gpick",                  NULL,       NULL,       0,            1,           -1 },
    { "Lxappearance",           NULL,       NULL,       0,            1,           -1 },
    { "Org.gnome.DejaDup",      NULL,       NULL,       0,            1,           -1 },
    { "Pavucontrol",            NULL,       NULL,       0,            1,           -1 },
    { "Eog",                    NULL,       NULL,       0,            1,           -1 },
    { "Timeshift",              NULL,       NULL,       0,            1,           -1 },
    { "SimpleScreenRecorder",   NULL,       NULL,       0,            1,           -1 },
    { "Gnome-terminal",         NULL,       NULL,       0,            1,           -1 },

    /* Open apps on tags*/
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// Added by TM
static const char *termcmd[]  = { "alacritty", NULL };
static const char *clipmenu[]   = { "bash", ".local/bin/copyToClip", NULL };
static const char *firefox[]    = { "firefox", NULL };
static const char *vivaldi[]    = { "firefox", "--private-window", NULL };
static const char *qutebro[]    = { "epiphany", NULL };
static const char *fmgui[]      = { "nautilus", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char *fmtui[]      = { "gnome-terminal", "-e", "ranger", NULL };
static const char *mutecmd[]    = { "pactl", "set-sink-mute", "1", "toggle", NULL };
static const char *suslock[]    = { "bash", "susLocker.sh", NULL };
static const char *displaysel[] = { "bash", ".local/bin/dwmDisplay", NULL };
static const char *emojis[]     = { "bash", ".local/bin/emoji-select", NULL };
static const char *nextcmd[]    = { "playerctl", "next", NULL };
static const char *playcmd[]    = { "playerctl", "play-pause", NULL };
static const char *prevcmd[]    = { "playerctl", "previous", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "1", "-5%", NULL };
static const char *volupcmd[]   = { "pactl", "set-sink-volume", "1", "+5%", NULL };
static const char *xfce4term[]  = { "gnome-terminal", NULL };
static const char *xkill[]      = { "xkill", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_space,  togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,             		    XK_Tab,    shiftviewclients, { .i = +1 } },
    { MODKEY|ShiftMask,             XK_Tab,    shiftviewclients, { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
    // Added by TM
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
    { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = clipmenu } },
    { MODKEY|ControlMask,           XK_d,      spawn,          {.v = displaysel } },
    { MODKEY|Mod1Mask,              XK_e,      spawn,          {.v = emojis } },
    { Mod1Mask|ControlMask,         XK_t,      spawn,          {.v = xfce4term } },
    { MODKEY,                       XK_n,      spawn,          {.v = fmgui } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = flameshot } },
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = fmtui } },
    { MODKEY,                       XK_b,      spawn,          {.v = firefox } },
    { MODKEY|ShiftMask|ControlMask, XK_b,      spawn,          {.v = vivaldi } },
    { MODKEY|ControlMask,           XK_b,      spawn,          {.v = qutebro } },
    { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = suslock } },
    { MODKEY|ShiftMask|ControlMask, XK_k,      spawn,          {.v = xkill } },
    { 0,                            XF86XK_AudioPlay, spawn, {.v = playcmd } },
    { 0,                            XF86XK_AudioPrev, spawn, {.v = prevcmd } },
    { 0,                            XF86XK_AudioNext, spawn, {.v = nextcmd } },
    { 0,                            XF86XK_AudioMute, spawn, {.v = mutecmd } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

