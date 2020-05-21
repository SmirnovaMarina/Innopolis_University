from colormath.color_objects import sRGBColor, LabColor
from colormath.color_conversions import convert_color
from colormath.color_diff import delta_e_cie2000
import numpy as np


def color_difference(dimension, norm_color_arg, norm_s_color_arg):

    if dimension == 1:
        return abs(norm_color_arg - norm_s_color_arg)

    if (dimension == 3) or (dimension == 4):
        color1_rgb = sRGBColor(norm_color_arg[0], norm_color_arg[1], norm_color_arg[2])
        color2_rgb = sRGBColor(norm_s_color_arg[0], norm_s_color_arg[1], norm_s_color_arg[2])

        color1_lab = convert_color(color1_rgb, LabColor)
        color2_lab = convert_color(color2_rgb, LabColor)

        return int(delta_e_cie2000(color1_lab, color2_lab))


def row_fitness(square_size, dimension, original_row, sample_row, mask_bit):

    fitness_score = 0
    score_mask = np.empty(512//square_size, dtype=int)

    for square_counter in range(0, 512//square_size):

        color_delta = color_difference(dimension, original_row[square_counter], sample_row[square_counter])
        fitness_score += color_delta

        score_mask[square_counter] = color_delta

    if mask_bit == 1:
        return fitness_score, score_mask
    else:
        return fitness_score


def compare_row_samples(population_size, square_size, dimension, orig_row, samples_arr):

    fitness_arr = np.zeros((population_size,), dtype=int)
    mask_arr = np.empty([population_size, 512//square_size], dtype=int)

    for sample_counter in range(0, population_size):
        fitness_arr[sample_counter], mask_arr[sample_counter] = row_fitness(square_size, dimension, orig_row,
                                                                            samples_arr[sample_counter][0], 1)

    indices_arr = np.argsort(fitness_arr)

    return mask_arr, indices_arr


def choose_best_fitness(population_size, square_size, dimension, delta_threshold, orig_row, samples_arr):

    best_fitness = 512//square_size*101  # the worst case is 101 for a single square
    best_index = -1
    for sample_counter in range(0, population_size):

        sample_fitness, mask_arr = row_fitness(square_size, dimension, orig_row, samples_arr[sample_counter][0], 1)

        if np.all(mask_arr <= delta_threshold):
            if sample_fitness < best_fitness:  # < because of summation of deltas
                best_fitness = sample_fitness
                best_index = sample_counter

    return best_fitness, best_index



