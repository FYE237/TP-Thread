#include "synchro.h"
#include "ensitheora.h"
#include "pthread.h"


extern bool fini;

extern int windowsx ;
extern int windowsy ;
extern int  nombre_texture ;



//fye
/* les variables pour la synchro, ici */
 // 1 : GestionTaille fenêtre
 // 2 : Gestion Fen

//fye
pthread_mutex_t m1 ,m2,m3,m4,m5,m6,m7,m8;
pthread_cond_t c1,c2,c3,c4;
bool FenetreTexturePrete = false;
bool ConsommationTexture = false;
bool DepotTexture = false;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&m1);
        windowsx = buffer[0].width;
        windowsy = buffer[0].height;
        pthread_cond_signal(&c1);
    pthread_mutex_unlock(&m1);
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&m8);
        while(windowsx == 0 && windowsy == 0)
            pthread_cond_wait(&c1,&m8);
    pthread_mutex_unlock(&m8);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&m2);
        FenetreTexturePrete = true;
        pthread_cond_signal(&c2);
    pthread_mutex_unlock(&m2);
        
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&m3);
        while( ! FenetreTexturePrete){
            pthread_cond_wait(&c2,&m3);
        }
        FenetreTexturePrete = false;
    pthread_mutex_unlock(&m3);
        
}

void debutConsommerTexture() {
    pthread_mutex_lock(&m4);
        
        if(nombre_texture > 1) {
            ConsommationTexture = true;
            pthread_cond_signal(&c3);
        }
        
    pthread_mutex_unlock(&m4);

}

void finConsommerTexture() {
    pthread_mutex_lock(&m5);
        while( ! ConsommationTexture){
            pthread_cond_wait(&c3,&m5);
            
        }
        nombre_texture --;
        ConsommationTexture = false;
    pthread_mutex_unlock(&m5);
}


void debutDeposerTexture() {
    pthread_mutex_lock(&m6);
       
        if(nombre_texture < 30) {
            DepotTexture = true;
            pthread_cond_signal(&c4);
        }
    pthread_mutex_unlock(&m6);
}

void finDeposerTexture() {
    pthread_mutex_lock(&m7);
        while( ! DepotTexture){
            pthread_cond_wait(&c4,&m7);
            
        }
        nombre_texture ++;
        DepotTexture = false;
    pthread_mutex_unlock(&m7);
}

