/* =====================================================================================
 *
 *       Filename:  PIRDS.c
 *
 *    Description: Basic self-contained utilities for the PIRDS standard
 *
 *        Version:  1.0
 *        Created:  05/07/2020 10:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Robert L. Read
 *   Organization:  Public Invention
 *        License:  MIT
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include "PIRDS.h"


/* Fill the byte buffer with a PIRDS-standard bytes from the
   Measurement Object */
int fill_byte_buffer_measurement(Measurement* m,uint8_t* buff,unsigned blim) {
  buff[0] = m->event;
  buff[1] = m->type;
  buff[2] = m->loc;
  buff[3] = m->num;
  *((uint32_t *) &buff[4]) = m->ms;
  *((int32_t *) &buff[9]) = m->val;
  return 0;
}

Measurement get_measurement_from_buffer(uint8_t* buff,unsigned blim) {
  Measurement m;
  m.event = buff[0];
  m.type = buff[1];
  m.loc = buff[2];
  m.num = buff[3];
  m.ms = *((uint32_t *) &buff[4]) ;
  m.val = *((int32_t *) &buff[9]) ;
  return m;
}

int fill_JSON_buffer_measurement(Measurement* m,char* buff,unsigned blim) {
  int rval = sprintf(buff,
  "{ \"event\": \"M\", \"type\": \"%c\", \"ms\": %u, \"loc\": \"%c\", \"num\": %u, \"val\": %d }",
                     m->type,
                     m->ms,
                     m->loc,
                     m->num,
                     m->val);
  return rval;
}


// From: https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}


int assign_value(Measurement *m,char* k, char*v) {
  // First strip the key...
  char *stripped_key = trimwhitespace(k);
  char *stripped_value = trimwhitespace(v);
  if (0 == strcmp(stripped_key,"\"event\"")) {
    m->event = stripped_value[1];
  } else
  if (0 == strcmp(stripped_key,"\"type\"")) {
    m->type = stripped_value[1];
  } else
  if (0 == strcmp(stripped_key,"\"ms\"")) {
    m->ms = atoi(stripped_value);
  } else
  if (0 == strcmp(stripped_key,"\"loc\"")) {
    m->loc = stripped_value[1];
  } else
  if (0 == strcmp(stripped_key,"\"num\"")) {
    m->num = atoi(stripped_value);
  } else
  if (0 == strcmp(stripped_key,"\"val\"")) {
    m->val = atoi(stripped_value);
  } else {
    fprintf(stderr,"Key Error: %s",stripped_key);
    return 0;
  }
  return 1;
}

// Note: This is a VERY weak and specialized JSON parser
// This will fail if a string contains a colon!!!
Measurement get_measurement_from_JSON(char* buff,unsigned blim) {
  int i = 0;
  Measurement m;
  //  char *scratch = strtok(buff, "{,:}");

  // eat the first brace...
  //  scratch = strtok(NULL, "{,:}");
  //  fprintf(stderr,"scratch %s\n",scratch);
  //  fprintf(stderr,"buff %s\n",buff);
  for(i = 0; i < 5; i++) {
    char *k = strtok((i == 0) ? buff : NULL, "{,:}");
    char *v = strtok(NULL, "{,:}");
    assign_value(&m,k,v);
  }
  char *k = strtok(NULL,"{,:}");
  char *v = strtok(NULL,"{,:}");
  assign_value(&m,k,v);
  return m;
}
