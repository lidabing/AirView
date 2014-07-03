// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_COMMON_H_
#define CHROME_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_COMMON_H_

//MOUSE GUEST
extern const int	MGPATTERN_UNKNOWN;
extern const int	MGPATTERN_UP;
extern const int	MGPATTERN_DOWN;
extern const int	MGPATTERN_UPDOWN;
extern const int	MGPATTERN_DOWNUP;	
extern const int	MGPATTERN_RIGHT;
extern const int	MGPATTERN_LEFT;
extern const int	MGPATTERN_RIGHTLEFT;
extern const int	MGPATTERN_LEFTRIGHT;
extern const int	MGPATTERN_DOWNRIGHT;
extern const int	MGPATTERN_DOWNLEFT;
extern const int	MGPATTERN_UPLEFT;
extern const int	MGPATTERN_UPRIGHT;
extern const int	MGPATTERN_RIGHTUP;
extern const int	MGPATTERN_RIGHTDOWN;
extern const int	MGPATTERN_LEFTUP;
extern const int	MGPATTERN_LEFTDOWN;

//MGA
extern const int	MGACTION_NULL; 
extern const int	MGACTION_PAGEDOWN;   
extern const int	MGACTION_PAGEUP;       
extern const int	MGACTION_GOBACK;         
extern const int	MGACTION_GOFORWARD;      
extern const int	MGACTION_CLOSECURRENTTAB; 
extern const int	MGACTION_SELECTPREVIOUSTAB; 
extern const int	MGACTION_SELECTNEXTTAB;
extern const int	MGACTION_REFRESH; 
extern const int	MGACTION_RESTORETAB;
extern const int	MGACTION_NEWTAB;        
extern const int	MGACTION_GOPAGETOP;
extern const int	MGACTION_GOPAGEBOTTOM;
extern const int	MGACTION_STOPLOADING;  
extern const int	MGACTION_MINIMIZEWINDOW;
extern const int	MGACTION_CLOSEOTHERTAB; 
extern const int	MGACTION_CLOSERIGHTTAB; 


typedef int MGPattern;
typedef int MGAction;

#endif //CHROME_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_COMMON_H_