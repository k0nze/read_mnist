/* Example program on how to use the functions in read_mnist.h 
 * 
 * Author: Konstantin Luebeck (University of Tuebingen, Chair for Embedded Systems)
 */

#include "read_mnist.h"

int main(int argc, char** argv) {

    if(argc != 2) {
        printf("No path to MNIST dataset provided!\n");
        return 1;
    }

    int num_images;
    int num_labels;
    int i, row, column; 

    // read t10k images
    char t10k_images_path[strlen(argv[1]) + 20];
    t10k_images_path[0] = '\0';
    strcat(t10k_images_path, argv[1]);
    strcat(t10k_images_path, "/t10k-images.idx3-ubyte");

    uint8_t** t10k_images;
    
    num_images = read_mnist_images(t10k_images_path, &t10k_images); 

    if(num_images == 0) {
        printf("Could not read '%s'\n", t10k_images_path);
        return 1;
    }

    // read t10k labels
    char t10k_labels_path[strlen(argv[1]) + 20];
    t10k_labels_path[0] = '\0';
    strcat(t10k_labels_path, argv[1]);
    strcat(t10k_labels_path, "/t10k-labels.idx1-ubyte");

    uint8_t* t10k_labels;

    num_labels = read_mnist_labels(t10k_labels_path, &t10k_labels);

    if(num_labels == 0) {
        printf("Could not read '%s'\n", t10k_labels_path);
        return 1;
    }


    /*
	for(i = 0; i < num_images; i++) {
        printf("%d\n", t10k_labels[i]);
        for(row = 0; row < 28; row++) {
            for(column = 0; column < 28; column++) {
                printf("%02x ", t10k_images[i][row*28+column]);
            }
            printf("\n");
        }
        printf("\n");
	}
    */

    free(t10k_images);
    free(t10k_labels);


    // read t10k images
    char train_images_path[strlen(argv[1]) + 20];
    train_images_path[0] = '\0';
    strcat(train_images_path, argv[1]);
    strcat(train_images_path, "/train-images.idx3-ubyte");

    uint8_t** train_images;
    
    num_images = read_mnist_images(train_images_path, &train_images); 

    if(num_images == 0) {
        printf("Could not read '%s'\n", train_images_path);
        return 1;
    }


    // read t10k labels
    char train_labels_path[strlen(argv[1]) + 20];
    train_labels_path[0] = '\0';
    strcat(train_labels_path, argv[1]);
    strcat(train_labels_path, "/train-labels.idx1-ubyte");

    uint8_t* train_labels;

    num_labels = read_mnist_labels(train_labels_path, &train_labels);

    if(num_labels == 0) {
        printf("Could not read '%s'\n", train_labels_path);
        return 1;
    }


    /*
	for(i = 0; i < num_images; i++) {
        printf("%d\n", train_labels[i]);
        for(row = 0; row < 28; row++) {
            for(column = 0; column < 28; column++) {
                printf("%02x ", train_images[i][row*28+column]);
            }
            printf("\n");
        }
        printf("\n");
	}
    */

    free(train_images);
    free(train_labels);


    return 0;
}
