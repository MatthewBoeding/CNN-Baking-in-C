#include "linearalgebra.h"

struct channels{
    struct matrix * curr_channel;
    struct matrix * next_channel;
};

struct conv_layer{
    struct conv_layer * input_layer;
    struct conv_layer * output_layer;
    struct channels * kernel;
    struct channels * ofmap;
    char is_batch_norm;
    char is_pooling;
    char is_upsampling;
};

struct conv_layer * conv_layer_creation(int depth, int kernel_size, int kern_channels, int of_dima, int of_dimb, int if_channels);
void connect_layers(struct conv_layer * prev_layer, struct conv_layer * next_layer);