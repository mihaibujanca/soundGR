 // -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
    2 
    3 /*
    4  * Copyright (C) 2013 iCub Facility - Istituto Italiano di Tecnologia
    5  * Authors: Marco Randazzo
    6  * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
    7  *
    8  */
    9 
   10 #include "PortAudioBuffer.h"
   11 
   12 #include <stdio.h>
   13 #include <stdlib.h>
   14 #include <portaudio.h>
   15 
   16 
   17 circularBuffer::circularBuffer(int bufferSize)
   18 {
   19     maxsize  = bufferSize + 1; 
   20     start = 0;
   21     end   = 0;
   22     elems = (SAMPLE *) calloc(maxsize, sizeof(SAMPLE));
   23 }
   24 
   25 circularBuffer::~circularBuffer()
   26 {
   27     free(elems);
   28 }
   29 
