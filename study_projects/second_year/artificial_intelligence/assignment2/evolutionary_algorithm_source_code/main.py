from algorithm_execution import algorithm_execution


def main():

    """
        file_name variable specifies name of the picture that is chosen for reproduction

        save_color variable allows to create the output image in RGB/RGBA or gray-scale formats
        NOTE: due to greater color space (3 or 4 channels) RGB/RGBA images (especially photos) take significantly more time
        to be reproduced (at least an hour). So, it's recommended to test it with save_color = False option
    """

    file_name = 'in6.jpg'
    save_color = False
    algorithm_execution(file_name, save_color)


main()
