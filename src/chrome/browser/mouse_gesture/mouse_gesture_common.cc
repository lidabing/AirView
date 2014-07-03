// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/mouse_gesture/mouse_gesture_common.h"

//!!!!!!!!DON'T MODIFIY THIS VALUE, IF U ADD NEW VALUE,PLEASE APPEND TO THE END!!!!!

//MOUSE GUEST
const int	MGPATTERN_UNKNOWN = -1;
const int	MGPATTERN_UP = 1;
const int	MGPATTERN_DOWN = 2;
const int	MGPATTERN_UPDOWN = 3;
const int	MGPATTERN_DOWNUP = 4;	
const int	MGPATTERN_RIGHT = 5;
const int	MGPATTERN_LEFT = 6;
const int	MGPATTERN_RIGHTLEFT = 7;
const int	MGPATTERN_LEFTRIGHT = 8;
const int	MGPATTERN_DOWNRIGHT = 9;
const int	MGPATTERN_DOWNLEFT  =10;
const int	MGPATTERN_UPLEFT = 11;
const int	MGPATTERN_UPRIGHT =12;
const int	MGPATTERN_RIGHTUP =13;
const int	MGPATTERN_RIGHTDOWN=14;
const int	MGPATTERN_LEFTUP=15;
const int	MGPATTERN_LEFTDOWN=16;

//MGA
const int	MGACTION_NULL = -1; 
const int	MGACTION_PAGEDOWN = 1;   
const int	MGACTION_PAGEUP = 2;       
const int	MGACTION_GOBACK = 3;         
const int	MGACTION_GOFORWARD = 4;      
const int	MGACTION_CLOSECURRENTTAB = 5; 
const int	MGACTION_SELECTPREVIOUSTAB = 6; 
const int	MGACTION_SELECTNEXTTAB = 7;
const int	MGACTION_REFRESH = 8; 
const int	MGACTION_RESTORETAB = 9;
const int	MGACTION_NEWTAB = 10;        
const int	MGACTION_GOPAGETOP = 11;
const int	MGACTION_GOPAGEBOTTOM = 12;
const int	MGACTION_STOPLOADING = 13;  
const int	MGACTION_MINIMIZEWINDOW = 14;
const int	MGACTION_CLOSEOTHERTAB = 15;
const int	MGACTION_CLOSERIGHTTAB = 16;