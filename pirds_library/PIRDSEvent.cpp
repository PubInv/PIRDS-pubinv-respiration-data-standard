/*
 * =====================================================================================
 *
 *       Filename:  PIRDSEvent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2020 14:16:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriacl), lauria.clarke@gmail.com
 *   Organization:  Public Invention
 *
 * =====================================================================================
 */

#include "PIRDSEvent.h"

    
void PIRDSEvent::receiveEvent()
{
    if(eventChannel->available())
    {

    }
}


void PIRDSEvent::sendEvent()
{
  // write the data
  // ...but for now...
  eventChannel->print("Event Type:");
  eventChannel->println(eventType);
  eventChannel->print("Event Length:");
  eventChannel->println(eventLength);
}


int PIRDSEvent::setChannel(Stream* channel)
{
  eventChannel = channel;

  /* need error checking, but this doesn't make much sense yet
  // wait for connection
  // serial timeout is 1000 ms 
  delay(2000);

  // check to see if connection has been established
  if(eventChannel)
  {
    return 1;
  }
  else
  {
    return 0;
  }
  */

  return 1;
}

