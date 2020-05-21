from PIL import Image
import numpy as np


def import_image(file_name, save_color):

    img = Image.open(file_name)
    img_arr = np.asarray(img)

    try:
        dimension = np.shape(img_arr)[2]
    except:
        dimension = 1

    if save_color != True:

        if dimension != 1:

            dimension = 1
            img_h = np.shape(img_arr)[0]
            img_w = np.shape(img_arr)[1]
            gray_img = np.empty([img_h, img_w], dtype=np.uint8)
            rgb_arr = np.empty(3, dtype=np.uint8)

            for i in range(0, img_h):
                for j in range(0, img_w):

                    rgb_arr[0] = img_arr[i][j][0]
                    rgb_arr[1] = img_arr[i][j][1]
                    rgb_arr[2] = img_arr[i][j][2]
                    gray_img[i][j] = np.dot(rgb_arr, [0.2989, 0.5870, 0.1140])

            return dimension, gray_img

    return dimension, img_arr


def export_image(square_size, dimension, sample_array):

    sample_h = np.shape(sample_array)[0]
    sample_w = np.shape(sample_array)[1]

    if dimension == 1:
        img_array = np.empty([512, 512], dtype=np.uint8)

    if (dimension == 3) or (dimension == 4):
        img_array = np.empty([512, 512, dimension], dtype=np.uint8)

    for sample_row in range(0, sample_h):
        for sample_square in range(0, sample_w):

            y_upper = sample_row*square_size
            x_left = sample_square*square_size
            x_right = x_left + square_size
            y_lower = y_upper + square_size

            for i in range(y_upper, y_lower):
                for j in range(x_left, x_right):
                    if dimension == 1:
                        img_array[i][j] = sample_array[sample_row][sample_square][0]
                    else:
                        img_array[i][j] = sample_array[sample_row][sample_square]

    output_image = Image.fromarray(img_array)
    output_image.save("output.jpg")