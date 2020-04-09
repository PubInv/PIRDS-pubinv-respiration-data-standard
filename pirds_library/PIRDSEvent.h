/*
 * =====================================================================================
 *
 *       Filename:  PIRDSEvent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2020 14:25:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriacl), lauria.clarke@intel.com
 *   Organization:  NSG
 *
 * =====================================================================================
 */

#ifndef PIRDSEVENT_H
#define PIRDSEVENT_H

#include <Stream.h>
#include <Arduino.h>

class PIRDSEvent
{
  public:
    char    eventType;
    int     eventLength;
    Stream* eventChannel;

    PIRDSEvent(char type = 'M', int length = 12) :
      eventType{type}, eventLength{length}
    {
    } 

    int  setChannel(Stream* channel);
    void receiveEvent();
    void sendEvent();
};


class Measurement: public PIRDSEvent
{
  char          measurementType;
  char          deviceType;
  unsigned char deviceLocation;
  unsigned long measurementTime;
  long          measurementValue;

  public:
    Measurement() = default;
    Measurement(char measurement, char device, char location, long time, long value) :
      measurementType {measurement},
      deviceType      {device},
      deviceLocation  {location},
      measurementTime {time},
      measurementValue{value}
      {   
        eventType = 'M';
        eventLength = 12;
      }
};


class Assertion: public Measurement
{

  public:
    Assertion()
    {   
      eventType = 'A';
      eventLength = 12;
    }
};


class Meta: public PIRDSEvent
{

  public:
    Meta()
    {
      eventType = 'E';
    }

    // something is wrong with this constructor
    Meta(int length) : PIRDSEvent{length}
    { 
      eventType = 'E';      
    }
};
#endif
