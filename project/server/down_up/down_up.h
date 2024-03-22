#ifndef __DOWN_UP_H
#define __DOWN_UP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>


int Down_Calib(int clientfd,const char *buf);
int Up_Calib(int clientfd,const char *buf);

#endif