from PIL import Image
import os

# Paths to the special image and the folder containing the 199 pictures
special_image_path = '/Users/hel-omra/Downloads/Background.png'
pictures_folder = '/Users/hel-omra/Downloads/edit/'
output_folder = '/Users/hel-omra/Downloads/res/'

# Load the special image
special_image = Image.open(special_image_path)

# Ensure the output folder exists
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# Loop through the 199 PNG pictures
for i in range(1, 200):
    filename = f'{i}.png'
    picture_path = os.path.join(pictures_folder, filename)

    # Skip files that are not PNG or don't exist
    if not os.path.exists(picture_path):
        continue

    # Open the picture
    picture = Image.open(picture_path)

    # Resize special image to match the size of the current picture (optional)
    special_image_resized = special_image.resize(picture.size)

    # Merge the two images (alpha blending for transparency)
    merged_image = Image.alpha_composite(picture.convert("RGBA"), special_image_resized.convert("RGBA"))

    # Save the merged image
    merged_image.save(os.path.join(output_folder, f'{i}.png'))

print("Merging complete!")
