#include "relay.h"
#include "list.h"

int main(void)
{
    int pipe, pid;

    mknod(client_connection, S_IFIFO | 0666, 0);
    pipe = open(client_connection, O_RDONLY);
    fcntl(pipe, F_SETFL, O_NONBLOCK);

    list *clients = create_list();
    buffer message;

    int msqid;
    key_t key;

    if((key = ftok(msg_key, msg_id)) == -1)
    {
        perror("ftok");
        return 404;
    }

    if((msqid = msgget(key, 0666 | IPC_CREAT)) == -1)
    {
        perror("msgget");
        return 404;
    }

    printf("Enter a message: ");
    while(fgets(message.mtext, sizeof(message.mtext), stdin) != NULL)
    {
        while(read(pipe, &pid, sizeof(pid)) > 0)
        {
            add_client(clients, pid);
        }

        if(strlen(message.mtext) > 255) 
        {
            printf("To many characters %d is the max\n", 253);
            while(message.mtext[strlen(message.mtext) - 1] != '\n')
            {
                fgets(message.mtext, sizeof(message.mtext), stdin);
            }
            message.mtext[0] = '\0';
            continue;
        }

        int len = strlen(message.mtext);
        if(len > 0)
        {
            node *current = clients->head;
            while(current != NULL) 
            {
                message.mtype = current->data;
		if(kill(current->data, 0) == ESRCH)
		{
		    delete_node(current);
		} else {
                    msgsnd(msqid, &message, len+1, 0); 
		}
                current = current->next;
            }
        }
        print_list(clients);
        printf("Enter a message: ");
    }
    delete_list(clients);
    remove(client_connection);
    printf("\n");
    return 0;
}

