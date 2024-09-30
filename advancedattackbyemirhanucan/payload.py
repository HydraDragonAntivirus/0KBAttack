import os
import subprocess

# Folder name
folder_name = "hexdata"

# Get the list of files and sort them
files = sorted(os.listdir(folder_name))

# Initialize the message
message = ''

# Iterate through sorted files
for file in files:
    # Split filename to get index and hex part
    if '_' in file:
        index, hex_part = file.split('_')
        hex_part = hex_part.replace('.txt', '')

        # Convert hex to character and append to message
        try:
            character = bytes.fromhex(hex_part).decode()
            message += character
        except ValueError:
            print(f"Skipping invalid hex value in file: {file}")

# Prepare to execute the message as a command
print("Prepared message:", message)

# Execute the command (if the message is safe to run)
try:
    subprocess.run(message, shell=True, check=True)
except subprocess.CalledProcessError as e:
    print(f"Error executing command: {e}")
