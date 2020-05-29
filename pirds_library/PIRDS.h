/* =====================================================================================
MIT License

Copyright (c) 2020 Public Invention

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 *
 *       Filename:  PIRDS.h
 *
 *    Description:
 *
 *        Version:  1.1
 *        Created:  04/07/2020 10:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriaclarke), lauria.clarke@gmail.com
 *                  Robert L. Read read.robert@gmail.com
 *   Organization:  Public Invention
 *        License:  MIT
 *
 * =====================================================================================
 */

#ifndef PIRDS_H
#define PIRDS_H

#include <inttypes.h>


#ifndef htons

#define htons(x) ( (((x)<<8)&0xFF00) | (((x)>>8)&0xFF) )
#define ntohs(x) htons(x)

#define htonl(x) ( ((x)<<24 & 0xFF000000UL) | \
                   ((x)<< 8 & 0x00FF0000UL) | \
                   ((x)>> 8 & 0x0000FF00UL) | \
                   ((x)>>24 & 0x000000FFUL) )
#define ntohl(x) htonl(x)

#endif // !defined(htons)

// struct containing measurement event values

typedef struct Measurement
{
  char     event; // I cannot figure out how to initialize this; it is 'M'
  char     type;
  char     loc;
  uint8_t  num;
  uint32_t ms;
  int32_t  val;
} Measurement;


// This has a fixed size of 1+1+4+1+256 = 263
typedef struct Message
{
  char     event; // I cannot figure out how to initialize this; it is 'E'
  char     type; // 'M' for Message
  uint32_t ms;
  uint8_t  b_size;
  char    buff[256];
} Message;


#define FLOW_TOO_HIGH "FLOW OUT OF RANGE HIGH";
#define FLOW_TOO_LOW  "FLOW OUT OF RANGE LOW";

/* Fill the byte buffer with a PIRDS-standard bytes from the
   Measurement Object */
int fill_byte_buffer_measurement(Measurement* m,uint8_t* buff,unsigned blim);

Measurement get_measurement_from_buffer(uint8_t* buff,unsigned blim);

int fill_JSON_buffer_measurement(Measurement* m,char* buff,unsigned blim);

Measurement get_measurement_from_JSON(char* buff,unsigned blim);



int fill_byte_buffer_message(Message* m,uint8_t* buff,unsigned blim);

Message get_message_from_buffer(uint8_t* buff,unsigned blim);

int fill_JSON_buffer_message(Message* m,char* buff,unsigned blim);

Message get_message_from_JSON(char* buff,unsigned blim);


/*  PLACEHOLDERS
// struct containing assertion event values
struct Assertion
{
};

// struct containing meta event values
struct Meta
{
};
*/


#endif
