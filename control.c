#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#define KEY 42069

int main(int argc, char * args[]){
  int shmd = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0600);

  if(!strcmp(args[1], "-v")){

    printf("semaphore: %d", semctl(shmd, 0, GETVAL));
    return 0;

  }

  else if(!strcmp(args[1], "-r")){
 
    semctl(shmd, IPC_RMID, 0);


    printf("removed semaphore");
  } 



  else if(!strcmp(args[1], "-c")){

    if(shmd < 0){
      printf("mem already exists\n");
      return 0;
    }
    else{
      semctl(shmd, 0, SETVAL, atoi(args[2]));
      printf("semaphore created: %d", shmd);
    }    
  }


  return 0;



}
