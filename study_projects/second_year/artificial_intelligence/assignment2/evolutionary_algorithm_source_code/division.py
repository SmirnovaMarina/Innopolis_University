import numpy as np


def divide_pic(dimension, initial_pic):

    initial_h = np.shape(initial_pic)[0]
    initial_w = np.shape(initial_pic)[1]

    expanded_pic = np.empty([initial_h*2, initial_w*2, dimension], dtype=np.uint8)

    for i in range(0, initial_h):
        for j in range(0, initial_w):

            expanded_pic[i*2:i*2+2, j*2:j*2+2] = np.copy(initial_pic[i][j])

    return expanded_pic


def divide_samples(dimension, samples):

    population_size = np.shape(samples)[0]
    initial_h = np.shape(samples)[1]
    initial_w = np.shape(samples)[2]
    expanded_samples = np.empty([population_size, initial_h*2, initial_w*2, dimension], dtype=np.uint8)

    for sample_counter in range(0, population_size):

        expanded_samples[sample_counter] = divide_pic(dimension, samples[sample_counter])

    return expanded_samples
