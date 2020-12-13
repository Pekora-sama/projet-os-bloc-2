#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include "rand.h"
#include "voiture.h"
#include "cirquit.h"
#define MAXFORK 20


int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_destroy(sem_t *sem);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);



int main(int argc, char**argv)
{


    maVoiture voitureEnMem[20]; //tableau de voitures
    /* initialisation de la m�moire partag�e */


    struct shmid_ds shmbuffer;

    /* Alloue le segment de m�moire partag�e. */
    int segment_id = shmget (IPC_PRIVATE, sizeof(maVoiture)*20, IPC_CREAT | 0666);

    /* Attache le segment de m�moire partag�e. */

    maVoiture *shared_memory  = (maVoiture *) shmat(segment_id, NULL, 0);
    printf ("memoire partagee attachee a l'adresse %p\n", shared_memory );

    /* �crit une cha�ne dans le segment de m�moire partag�e. */
    sprintf (shared_memory , "Hello, world.");
    memcpy(voitureEnMem, shared_memory , sizeof(maVoiture)*20);

    /* affiche la chaine en m�moire partag�e. */
    printf ("%s\n", shared_memory);


    //========================================

   // pthread_t threads[MAXFORK];
    //int sem_init(&semaphore, PTHREAD_PROCESS_SHARED, 1);
    char a ="";
    printf("lolol %d",strlen("semy"));








    //========================================
    int tableauResult[20][6] ;// creation du tableau global
    //srand(time(NULL)^ getpid());//ATTENTION PAS TOUCHER --> la graine du g�n�rateur al�atoire doit �tre en dehors de la fct printRandom()

    int tableau[20] = {44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};
    /*cr�ation d'un tableau de structure pour les 20 voitures
    Si vous avez une meilleure id�e n'h�sitez pas � changer*/


    int k = 0;
    for(k=0; k<20; k++)
    {
        maVoiture tableau[k];       //Chaque �l�ment du tableau devient une structure

    }
    //rouler();




    int pid[MAXFORK];
    int i,j;
    int fini;

    for(i=0; i < MAXFORK ; i++){

        pid[i] = fork() ;
        if(pid[i]== -1){
            printf("Impossible de cr�er un fils (%d)\n",i);
        }
        else if(pid[i]==0){ // FILS
            //pthread_join(threads[i], NULL);
            //faire les tours
            sprintf (shared_memory , "je suis un des fils \n");
            sleep(1);
            //printf("Fils %2d (PID=%d): Activ�\n",i,getpid());
            fflush(stdout);
            rouler();
            exit(0);
            fflush(stdout);

        }
        else {
            //printf("Pere : Activation du fils %2d\n", i);
            fflush(stdout);
        }

    }

    //printf("P�re : Fin des activations\nAttente ...\n");
    fflush(stdout);
    fini=0;
    while (!fini) {
    fini=1;
    for(i=0;i<MAXFORK;i++){
      if (pid[i]>0) {
        if (waitpid(pid[i],NULL,WNOHANG)==0) {
          //printf("P�re: fin du fils %2d (PID=%d)\n", i, pid[i]);
          fflush(stdout);
          pid[i]=0;
        }
      } else {
        fini=0;
      }
    }
    }


  //printf("Fin de tous les fils.");
  fflush(stdout);



    return 0;
}





/*=======================================================
Cr�ation des fonctions S�maphore
=========================================================*/

