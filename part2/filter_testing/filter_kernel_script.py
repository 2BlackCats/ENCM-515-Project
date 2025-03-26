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


# Define top left 4x4 area of image
# R portion of pixels
image = np.array([[[113, 112, 111, 112],
                   [116, 115, 114, 115],
                   [117, 115, 115, 115],
                   [116, 115, 114, 113]],
                  # G portion of pixels
                  [[175, 174, 173, 174],
                   [178, 177, 176, 177],
                   [179, 177, 177, 177],
                   [178, 177, 176, 175]],
                  # B portion of pixels
                  [[234, 233, 232, 233],
                   [237, 236, 235, 236],
                   [236, 234, 234, 234],
                   [235, 234, 233, 232]]])

'''
*Aside*
If you want to test processing an entire image, that is currently not supported.
'''

# Define kernels
identity = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 0]])
sharpen = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

# Test kernel filter
print(get_3x3_region(image, 0, 1))
print("\n")
print(convolution(image, sharpen, (0, 1)))
