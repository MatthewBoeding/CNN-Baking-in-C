/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Convolutional Layer Library
* Written by: Matthew Boeding
* This convolutional layer implements a gradient descent with optional batch normalization
* pooling, and upsampling.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "convolutional_layer.h"

struct conv_layer * conv_layer_creation(int depth, int kernel_size, int kern_channels, int of_dima, int of_dimb, int if_channels)
{
    struct conv_layer * curr_layer = (struct conv_layer *) malloc(sizeof(struct conv_layer));
    struct channels * kern_channel_ptr = (struct channels *)malloc(sizeof(struct channels)*kern_channels);
    struct channels * of_channel_ptr = (struct channels *)malloc(sizeof(struct channels)*if_channels);

    curr_layer->kernel = kern_channel_ptr;
    struct channels * last_channel = kern_channel_ptr;
    
    for(int i = 0; i < kern_channels; i++)
    {
        last_channel->next_channel = kern_channel_ptr->curr_channel;
        kern_channel_ptr->curr_channel = matrix_create(depth, kernel_size, kernel_size);
        last_channel = kern_channel_ptr;
        kern_channel_ptr++;
    }

    curr_layer->ofmap = of_channel_ptr;
    last_channel = of_channel_ptr;
    for(int i = 0; i < if_channels; i++)
    {
        last_channel->next_channel = of_channel_ptr->curr_channel;
        of_channel_ptr->curr_channel = matrix_create(kern_channels, of_dima, of_dimb);
        last_channel = of_channel_ptr;
        of_channel_ptr++;
    }

    return curr_layer;
}

void connect_layers(struct conv_layer * prev_layer, struct conv_layer * next_layer)
{
    prev_layer->output_layer = next_layer;
    next_layer->input_layer = prev_layer;
}