/*
    Kennedy Jacinto
    #65303185
    github.com/kennedy-jacinto

    Honório Neto
    #75751835
    github.com/honorio-sousa-neto

    Joseph Pascoal

    Yolanda Canguia
    #83612809
    github.com/yolanda-silva


*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "commandlinereader.h"

typedef struct {
    int process_identifier;
    int process_status;
}PROCESS;

typedef struct Elem {
    PROCESS info;
    struct Elem *next;
}ELEM;

typedef struct {
    ELEM *head;
}LSL;

LSL* create_list(){
    LSL *list = (LSL*)malloc(sizeof(LSL));
    list->head = NULL;
    return list;
}
void insert_pid (LSL *lsl, int pid){
    ELEM *elem = (ELEM*)malloc(sizeof(ELEM));
    elem->info.process_identifier = pid;
    elem->next = lsl->head;
    lsl->head = elem;
}

void update_status (LSL *lsl, int pid, int status){
    
    ELEM *aux = lsl->head;

    while (aux != NULL){
        if (aux->info.process_identifier == pid)
            aux->info.process_status = status;
        
        aux = aux->next;
    }
}

void print_process (LSL *lsl){
    ELEM *aux = lsl->head;

    while (aux != NULL){
        printf("pid: %d exited normally; status: %d\n", aux->info.process_identifier, aux->info.process_status);
        aux = aux->next;
    }
}

int main (int argc, char** argv) {
    char *args[7];
    char buffer[100];
    int pid, status;

    LSL *list = create_list();

    while (1){

        if (readLineArguments(args,7,buffer,100) == EOF){
            continue;
        }

        if (strcmp(args[0], "exit") == 0){
            int process_identifier;
            do {
                process_identifier = wait(&status);
                update_status(list, process_identifier, status);
            } while(process_identifier >0);
            print_process(list);
            exit(0);
        }

        pid = fork();
        insert_pid(list, pid);
        if (pid==0){            
            execv(args[0], args);            
        } else if (pid == -1) {
            continue;
            //;
        }

       
                        
    }

}