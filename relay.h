#ifndef RELAY_H
#define RELAY_H

#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <signal.h>

typedef struct BUFFER
{
	long mtype;
	char mtext[256];
} buffer;

const char *client_connection = "/tmp/relay_montague";
const char *msg_key = "/tmp";
const char msg_id = 'M';

#endif
