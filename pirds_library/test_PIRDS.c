/* Copyright Robert L. Read, 2020
Released under MIT License
*/

#include <stdio.h>
#include "minunit.h"
#include "PIRDS.h"

int tests_run = 0;

int foo = 7;
int bar = 4;

/* Create a Measurement, load it into an buffer and read it back */
static char *test_can_create_Measurement_and_read_back_as_byte_buffer() {

  Measurement m = {
    'M','T',101,'B',3,400
  };
  const unsigned BUFF_SIZE = 13;
  uint8_t buff[BUFF_SIZE];
  int err = fill_byte_buffer_measurement(&m,buff,BUFF_SIZE);
  Measurement mp = get_measurement_from_buffer(buff,BUFF_SIZE);
  mu_assert("measurement byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("device location wrong", m.loc == mp.loc);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("value wrong", m.val == mp.val);
  return 0;
}

static char *test_can_create_Measurement_and_read_back_as_JSON() {
  Measurement m = {
    'M','T',101,'B',3,400
  };
  const unsigned BUFF_SIZE = 256;
  char buff[BUFF_SIZE];
  int err = fill_JSON_buffer_measurement(&m,buff,BUFF_SIZE);
  mu_assert("buffer problem", err > 0);

  Measurement mp = get_measurement_from_JSON(buff,BUFF_SIZE);

  mu_assert("measurement byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("device type wrong", m.type == mp.type);
  mu_assert("device location wrong", m.loc == mp.loc);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("value wrong", m.val == mp.val);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_can_create_Measurement_and_read_back_as_JSON);
  mu_run_test(test_can_create_Measurement_and_read_back_as_byte_buffer);
  return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
