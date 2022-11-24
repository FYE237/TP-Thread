#include "synchro.h"
#include "ensitheora.h"
#include "pthread.h"


extern bool fini;

extern int windowsx ;
extern int windowsy ;

//fye
/* les variables pour la synchro, ici */
 // 1 : GestionTaille fenêtre
 // 2 : Gestion Fen

//fye
pthread_mutex_t m1 ,m2;
pthread_cond_t c1,c2;
bool FenetreTexturePrete = false;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&m1);
        windowsx = buffer[0].width;
        windowsy = buffer[1].height;
        pthread_cond_signal(&c1);
    pthread_mutex_unlock(&m1);
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&m1);
        while(windowsx == 0 && windowsy == 0)
            pthread_cond_wait(&c1,&m1);
    pthread_mutex_unlock(&m1);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&m2);
        FenetreTexturePrete = true;
        pthread_cond_signal(&c2);
    pthread_mutex_unlock(&m2);
        
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&m2);
        while( ! FenetreTexturePrete)
            pthread_cond_wait(&c2,&m2);
    pthread_mutex_unlock(&m2);
        
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
