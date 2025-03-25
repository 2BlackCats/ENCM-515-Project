from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

# Converts a binary file containing multiple RGB images to individual images and displays them.


def binary_to_rgb_images(binary_file, width, height):
    # Read the binary file
    with open(binary_file, 'rb') as binary_file:
        binary_data = binary_file.read()

    # Calculate the size of one image in bytes
    image_size = width * height * 3  # 3 bytes per pixel (RGB)

    # Ensure the binary file size is a multiple of one image size
    if len(binary_data) % image_size != 0:
        raise ValueError(
            "Binary file size is not a multiple of one image size.")

    # Calculate the number of images in the binary file
    num_images = len(binary_data) // image_size
    print(f"Number of images in the binary file: {num_images}")

    # Process each image
    for i in range(num_images):
        # Extract the data for the current image
        start = i * image_size
        end = start + image_size
        image_data = binary_data[start:end]

        # Convert the image data to a NumPy array
        pixel_data = np.frombuffer(image_data, dtype=np.uint8)
        pixel_data = pixel_data.reshape((height, width, 3))

        # Create an image from the pixel data
        image = Image.fromarray(pixel_data, mode='RGB')

        # Display the image using matplotlib
        plt.imshow(image)
        plt.axis('off')  # Turn off axis labels
        plt.title(f"Image {i + 1}")
        plt.show()


# Example usage
# binary_to_rgb_images("part2/combined.bin", 64, 64)

# Filter
binary_to_rgb_images("part2/test.bin", 64, 64)
