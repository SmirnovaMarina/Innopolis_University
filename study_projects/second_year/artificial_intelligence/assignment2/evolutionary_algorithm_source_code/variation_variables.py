import numpy as np
from random import randint


def mutate_color(mu_coefficient, color):

    dimension = np.shape(color)[0]

    if dimension == 1:
        return randint(-mu_coefficient, mu_coefficient)+color

    if dimension == 3:
        return [randint(-mu_coefficient, mu_coefficient)+color[0], randint(-mu_coefficient, mu_coefficient)+color[1],
                randint(-mu_coefficient, mu_coefficient)+color[2]]

    if dimension == 4:
        return [randint(-mu_coefficient, mu_coefficient)+color[0], randint(-mu_coefficient, mu_coefficient)+color[1],
                randint(-mu_coefficient, mu_coefficient)+color[2], randint(-mu_coefficient, mu_coefficient)+color[3]]


def make_crossover(square_size, dimension, delta_parameter, mu_coefficient, parent1_row, parent2_row, parent1_mask, parent2_mask):

    # sum up best squares from parents
    # add bad leftovers
    # make crossover and mutation at the same time

    child_row = np.empty([1, 512//square_size, dimension], dtype=np.uint8)

    for square_counter in range(0, 512//square_size):

        if (parent1_mask[square_counter] < parent2_mask[square_counter]) and (parent1_mask[square_counter] <= delta_parameter):
            child_row[0][square_counter] = parent1_row[square_counter]

        elif (parent1_mask[square_counter] >= parent2_mask[square_counter]) and (parent2_mask[square_counter] <= delta_parameter):
            child_row[0][square_counter] = parent2_row[square_counter]

        elif parent1_mask[square_counter] < parent2_mask[square_counter]:
            child_row[0][square_counter] = mutate_color(mu_coefficient, parent1_row[square_counter])
        else:
            child_row[0][square_counter] = mutate_color(mu_coefficient, parent2_row[square_counter])

    return child_row


def create_next_gen(square_size, dimension, delta_parameter, row_samples, mask_arr, parent_indices):

    # crossover the last parent with every other one

    parents_num = np.shape(parent_indices)[0]
    parent1 = parent_indices[-1]  # the highest fitness score
    next_gen = np.empty([parents_num, 1, 512//square_size, dimension], dtype=np.uint8)

    mu_coefficient = 15

    for i in range(0, parents_num-1):

        parent2 = parent_indices[i]
        next_gen[i] = make_crossover(square_size, dimension, delta_parameter, mu_coefficient, row_samples[parent1][0], row_samples[parent2][0],
                                     mask_arr[parent1], mask_arr[parent2])

    parent1 = parent_indices[-2]
    parent2 = parent_indices[-3]
    next_gen[parents_num-1] = make_crossover(square_size, dimension, delta_parameter, mu_coefficient, row_samples[parent1][0], row_samples[parent2][0],
                                             mask_arr[parent1], mask_arr[parent2])

    return next_gen


def mutate_best_sample(population_size, square_size, dimension, mu_coefficient, best_pic):

    samples = np.empty([population_size, 512//square_size, 512//square_size, dimension], dtype=np.uint8)

    for sample_counter in range(0, population_size):
        for row_counter in range(0, 512//square_size):
            for square_counter in range(0, 512//square_size):
                samples[sample_counter][row_counter][square_counter] = mutate_color(mu_coefficient, best_pic[row_counter][square_counter])

    return samples

