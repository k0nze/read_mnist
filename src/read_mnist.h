#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t change_endianess(uint32_t value) {
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

// returns number of images read
// 0 : problem occured
int read_mnist_images(const char* path_to_mnist_images, uint8_t*** mnist_images) {

    FILE *images;
    images = fopen(path_to_mnist_images, "r");

    if(images != 0) {
        uint32_t magic_number;
        uint32_t num_images;
        uint32_t height;
        uint32_t width;

        int i;

        fread(&magic_number, sizeof(magic_number), 1, images);
        magic_number = change_endianess(magic_number);

        // check magic number
        if(magic_number != 2051) {
            fclose(images);
            return 0;
        }

		fread(&num_images, sizeof(num_images), 1, images);
        num_images = change_endianess(num_images);

		fread(&height, sizeof(height), 1, images);
        height = change_endianess(height);

		fread(&width, sizeof(width), 1, images);
        width = change_endianess(width);

        // allocate pointers for all images
        *mnist_images = (uint8_t**) malloc(num_images*sizeof(uint8_t*));

        // start reading images
        for(i = 0; i < num_images; i++) {
            
            // allocate memory for single image
            (*mnist_images)[i] = (uint8_t*) malloc(width*height*sizeof(uint8_t));
			fread(&(*mnist_images)[i][0], height*width, 1, images);
        }

        fclose(images);

        return num_images;
    }

    return 0;
}

// returns number of labels read
// 0 : problem occured
int read_mnist_labels(const char* path_to_mnist_labels, uint8_t** mnist_labels) {

	FILE *labels;
    labels = fopen(path_to_mnist_labels, "r");

	if(labels != 0) {
        uint32_t magic_number;
        uint32_t num_labels;

        int i;

        fread(&magic_number, sizeof(magic_number), 1, labels);
        magic_number = change_endianess(magic_number);

        // check magic number
        if(magic_number != 2049) {
            fclose(labels);
            return 0;
        }


		fread(&num_labels, sizeof(num_labels), 1, labels);
        num_labels = change_endianess(num_labels);

		// allocate pointers for all images
        *mnist_labels = (uint8_t*) malloc(num_labels*sizeof(uint8_t));

        // start reading images
        for(i = 0; i < num_labels; i++) {
			uint8_t label = getc(labels);
        	(*mnist_labels)[i] = label;
        }

        fclose(labels);

        return num_labels;
    }

    return 0;
}
