#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "faad2/include/neaacdec.h"

#define QUEUE_SIZE 100

typedef struct {
    // 2k
    unsigned char data[1024 * 2];
    int bytes;
} OneSegment;


typedef struct {
    OneSegment queue[QUEUE_SIZE];
    int last_index;
    int cur_index;
    int total;
} AdtsQueue;


typedef struct {
    NeAACDecHandle aac_handle;
    NeAACDecConfigurationPtr config;
    AdtsQueue adts_queue;
    int config_ready;

} AAC_ADTS_DECODER;


AAC_ADTS_DECODER *aac_adts_decoder_create();

void aac_adts_decoder_free(AAC_ADTS_DECODER *);

/*
 * @return {int}  [ 0:fail , 1: success]
 * */
int aac_adts_decoder_enqueue(AAC_ADTS_DECODER *, unsigned char *data, size_t data_size);

int aac_adts_decoder_decode(AAC_ADTS_DECODER *decoder, unsigned char *pcm_out);
