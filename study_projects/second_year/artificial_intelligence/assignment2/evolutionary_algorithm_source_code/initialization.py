from sklearn.cluster import KMeans
from collections import Counter
import numpy as np
from random import randint


def dominant_color(k_clusters, dimension, square_array):

    # reshape the image to be a list of pixels
    px_array = square_array.reshape((square_array.shape[0] * square_array.shape[1], dimension))

    clt = KMeans(n_clusters=k_clusters)
    labels = clt.fit_predict(px_array)

    # count labels to find most popular
    label_counts = Counter(labels)

    # subset out most popular centroid
    dom_color = clt.cluster_centers_[label_counts.most_common(1)[0][0]]

    return list(dom_color)


def init_dominant_color_matrix(k_clusters, dimension, square_size, original_img_arr):

    grid_array_x = [i * square_size for i in range(0, 512 // square_size)]
    grid_array_y = [i * square_size for i in range(0, 512 // square_size)]

    orig_square_colors = np.empty([512//square_size, 512//square_size, dimension], dtype=np.uint8)

    for y_upper in grid_array_y:
        for x_left in grid_array_x:

            x_right = x_left + square_size
            y_lower = y_upper + square_size

            square_array = np.copy(original_img_arr[y_upper:y_lower, x_left:x_right])

            dom_color = np.array(dominant_color(k_clusters, dimension, square_array), dtype=np.uint8)
            # print(dom_color)
            orig_square_colors[y_upper//square_size][x_left//square_size] = dom_color
            # print(orig_square_colors[y_upper//square_size][x_left//square_size])

    return orig_square_colors


def random_color(dimension: int):

    if dimension == 1:
        return randint(0, 255)
    if dimension == 3:
        return [randint(0, 255), randint(0, 255), randint(0, 255)]
    if dimension == 4:
        return [randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255)]


def init_row_samples(population_size: int, square_size: int, dimension: int):

    row_samples = np.empty([population_size, 1, 512//square_size, dimension], dtype=np.uint8)
    for sample_counter in range(0, population_size):

        for square_counter in range(0, 512//square_size):

            row_samples[sample_counter][0][square_counter] = random_color(dimension)

    return row_samples


def init_samples(population_size, square_size, dimension):

    samples = np.empty([population_size, 512//square_size, 512//square_size, dimension], dtype=np.uint8)

    for sample_counter in range(0, population_size):
        for row_counter in range(0, 512//square_size):
            for square_counter in range(0, 512//square_size):
                samples[sample_counter][row_counter][square_counter] = random_color(dimension)

    return samples


def init_parameters(dimension):
    population_size = 100
    k_clusters = 1

    if dimension == 1:
        fitness_threshold = 7  # for comparison of all squares of a row
        delta_parameter = 5
        size_array = [int(pow(2, i)) for i in range(8, 1, -1)]  # from 256 till 4 square sizes

    else:
        fitness_threshold = 40  # 40 = RGB/RGBA
        delta_parameter = 40    # 40 for RGB/RGBA
        size_array = [int(pow(2, i)) for i in range(8, 2, -1)]  # from 256 till 8 square sizes

    mu_coefficient = 20

    return population_size, size_array, k_clusters, delta_parameter, fitness_threshold, mu_coefficient