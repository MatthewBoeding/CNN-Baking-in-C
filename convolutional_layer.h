#include "linearalgebra.h"

struct channels{
    struct matrix * curr_channel;
    struct matrix * next_channel;
};

struct conv_layer{
    struct conv_layer * input_layer;
    struct conv_layer * output_layer;
    struct channels * kernel;
    struct channels * ifmap;
    struct channels * ofmap;
    char is_batch_norm;
    char is_pooling;
    char is_upsampling;
};

struct conv_layer * non_hidden_conv_layer_creation(int depth, int input_size, int kernel_size, int input_channels, int kern_channels);
struct conv_layer * hidden_conv_layer_creation(struct conv_layer * input_layer, int depth, int input_size, int kernel_size, int input_channels, int kern_channels);
