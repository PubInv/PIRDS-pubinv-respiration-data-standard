/* =====================================================================================
 *
 *       Filename:  PIRDS.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2020 10:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriaclarke), lauria.clarke@gmail.com
 *   Organization:  Public Invention
 *
 * =====================================================================================
 */

#ifndef PIRDS_H
#define PIRDS_H

// struct containing measurement event values 
struct Measurement
{
  char          m {'M'};
  char          measurementType;
  char          deviceType;
  char          deviceLocation;
  int           measurementTime;
  int           measurementValue;
};


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


