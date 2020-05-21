from initialization import *
from fitness import compare_row_samples, choose_best_fitness
from variation_variables import create_next_gen, mutate_best_sample
from division import divide_samples
from import_export import *


def row_execution(population_size, square_size, dimension, delta_parameter, fitness_threshold, orig_row, row_samples):

    fitness_pass = False
    best_index = 0
    gen_counter = 0
    while fitness_pass != True:

        mask_arr, indices_arr = compare_row_samples(population_size, square_size, dimension, orig_row, row_samples)

        if population_size > 50:
            population_size -= int(population_size*0.1)
            parent_indices = indices_arr[:population_size]
        else:
            parent_indices = indices_arr

        row_samples = create_next_gen(square_size, dimension, delta_parameter, row_samples, mask_arr, parent_indices)

        best_fitness, best_index = choose_best_fitness(population_size, square_size, dimension, fitness_threshold,
                                                       orig_row, row_samples)

        if best_index != -1:
            fitness_pass = True

        gen_counter += 1

    return row_samples[best_index]


def pic_execution(population_size, square_size, dimension, delta_parameter, fitness_threshold, color_matrix, samples):

    best_pic = np.empty([512 // square_size, 512 // square_size, dimension], dtype=np.uint8)
    for row_counter in range(0, 512 // square_size):
        best_pic[row_counter] = row_execution(population_size, square_size, dimension, delta_parameter,
                                                          fitness_threshold, color_matrix[row_counter],
                                                          samples[:, row_counter:row_counter+1, :, :])
        # print('row {} is ready'.format(row_counter))

    return best_pic


def algorithm_execution(file_name, save_color):

    dimension, img_arr = import_image(file_name, save_color)

    population_size, size_array, k_clusters, delta_parameter, fitness_threshold, mu_coefficient = init_parameters(dimension)
    img_height, img_width = img_arr.shape[0], img_arr.shape[1]

    # start with samples of square_size 256x256
    # init samples(256x256) with random colors

    # LOOP:
    # calculate color_matrix for a particular square_size from size_array
    # build the fittest picture
    # initialize new samples by mutating the best picture a little (use mu_coefficient for difference in colors)
    # divide samples (decrease the size of squares -> increase number of squares twice)

    samples = init_samples(population_size, size_array[0], dimension)

    for square_size in size_array:

        color_matrix = init_dominant_color_matrix(k_clusters, dimension, square_size, img_arr)
        best_pic = pic_execution(population_size, square_size, dimension,
                                             delta_parameter, fitness_threshold, color_matrix, samples)
        print('picture for square size {} is ready'.format(square_size))

        samples = mutate_best_sample(population_size, square_size, dimension, mu_coefficient, best_pic)
        samples = divide_samples(dimension, samples)

    export_image(size_array[-1], dimension, best_pic)

