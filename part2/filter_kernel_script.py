import numpy as np

# Get the 3x3 RGB values at target pixel


def get_3x3_region(image, x, y):
    depth, height, width = image.shape

    # Initialize output array to store the 3x3 region
    output = np.zeros((depth, 3, 3), dtype=int)

    for i in range(depth):
        # We need to consider the edges of the image by using the crop method.
        # It moves the kernel such that it is always within the bounds of the image.

        # Handle edge case w/ crop method (move kernel to be within bounds)
        x = max(1, min(x, width - 2))
        y = max(1, min(y, height - 2))

        # Store the RGB arrays respectively
        output[i] = image[i][y-1:y+2, x-1:x+2]

    return output

# Define convolution


def convolution(image, kernel, target_pixel):
    x, y = target_pixel
    result_RGB = np.array([], dtype=int)
    height, width = kernel.shape

    # Get region around target pixel
    region = get_3x3_region(image, x, y)

    for color_channel in region:
        accumulator = 0
        for row_index in range(height):
            for col_index in range(width):
                accumulator += color_channel[row_index,
                                             col_index] * kernel[row_index, col_index]

        # Clip the value to be within RGB range (0-255)
        accumulator = np.clip(accumulator, 0, 255)
        # Append the accumulation to the resultant pixel
        result_RGB = np.append(result_RGB, accumulator)

    return result_RGB


# Define image as given in lab
# R portion of 4x4 pixel image
image = np.array([[[255, 0, 0, 128],
                   [0, 0, 0, 0],
                   [0, 0, 0, 0],
                   [128, 128, 128, 128]],
                  # G portion of 4x4 pixel image
                  [[0, 255, 0, 128],
                   [0, 0, 0, 0],
                   [128, 128, 128, 128],
                   [0, 0, 0, 0]],
                  # B portion of 4x4 pixel image
                  [[0, 0, 255, 128],
                   [128, 128, 128, 128],
                   [0, 0, 0, 0],
                   [0, 0, 0, 0]]])

'''
*Aside*
If you want to test processing an entire image, that is currently not supported.
'''

# Define kernels
identity = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 0]])
sharpen = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

# Test kernel filter
print(get_3x3_region(image2, 0, 1))
print("\n")
print(convolution(image2, sharpen, (0, 1)))
