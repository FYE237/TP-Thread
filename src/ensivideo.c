#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>

// //fye

 #include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"


//fye
 pthread_t thread_audio;

  pthread_t thread_video;
   pthread_t thread_decodeur;


  pthread_mutex_t lock;


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);
    
    // start the two stream readers

   

    //vidéo
   
    pthread_create(&thread_video,NULL,theoraStreamReader,argv[1]);
   


    //audio
  
    pthread_create(&thread_audio,NULL,vorbisStreamReader,argv[1]);
  

    
    // wait audio thread
    pthread_join(thread_audio,NULL);

    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(thread_video);
    pthread_cancel(thread_decodeur);

    // attendre les 2 threads videos
    pthread_join(thread_video,NULL);
    pthread_join(thread_decodeur,NULL);

    exit(EXIT_SUCCESS);    
}
