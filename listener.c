#include "relay.h"

static bool pipe_exist(const char *fifo_name);

int main(void)
{
    if(!pipe_exist(client_connection))
    {
        printf("Pipe to dispaccter not found.\n");
        printf("Make sure dispacher is running.\n");
        return 0;
    }

    int pipe, pid = getpid();

    mknod(client_connection, S_IFIFO | 0666, 0);
    pipe = open(client_connection, O_WRONLY);

    write(pipe, &pid, sizeof(pid));

    buffer message;
    int msqid;
    key_t key;

    if((key = ftok(msg_key, msg_id)) == -1) 
    {
        perror("ftok");
        return 404;
    }

    usleep(5);

    if((msqid = msgget(key, 0666)) == -1) 
    { 
        perror("msgget");
        return 404;
    }

    while(pipe_exist(client_connection))
    {
        msgrcv(msqid, &message, sizeof(message.mtext), pid, 0);
        printf("%s", message.mtext);
    }
    return 0;
}

static bool pipe_exist(const char *fifo_name)
{
    if(access(fifo_name, W_OK) == -1)
    {
        return false;
    } else {
        return true;
    }
}
