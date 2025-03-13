import numpy as np


# Define convolution function


def convolution(image, kernel):
    h, w, c = image.shape
    output = np.zeros((h, w, c))
    for y in range(1, h - 1):
        for x in range(1, w - 1):
            region = get_3x3_region(image, x, y)
            for i in range(c):
                output[y, x, i] = np.sum(region[:, :, i] * kernel)
    return np.clip(output, 0, 255).astype(np.uint8)


# Define 3x3 region extractor function
# RGB, RGB, RGB, RGB
# (0, 0)   ; (1, 0)   ; (2, 0)
# 255, 0, 0; 0, 255, 0; 0, 0, 255

# Gets the 3x3 region around the pixel at (x, y)
"""
Takes into account the edges of the image using the crop method. 
It moves the kernel such that it is always within the bounds of the image.
"""


def get_3x3_region(image, x, y):
    h, w = image.shape
    x = max(1, min(x, w - 2))
    y = max(1, min(y, h - 2))
    return image[y-1:y+2, x-1:x+2]


def convolution(image, kernel):
    h, w = image.shape
    output = np.zeros((h, w))


# Constants to test with
REGION_SIZE = 3

# R portion of 4x4 pixel image
image = np.array([[255, 0, 0, 128],
                  [0, 0, 0, 0],
                  [0, 0, 0, 0],
                  [128, 128, 128, 128]])


# Define kernels
identity = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 0]])
sharpen = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

print(get_3x3_region(image, 3, 1))
