#ifndef MINI_RAIL_SERIAL_H
#define MINI_RAIL_SERIAL_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int serial_set_interface_attribs(int fd, int speed);

#endif  // MINI_RAIL_SERIAL_H
