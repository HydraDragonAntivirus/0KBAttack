import os

# Hex command
hex_command = "6d 73 68 74 61 20 22 6a 61 76 61 73 63 72 69 70 74 3a 61 6c 65 72 74 28 27 79 6f 75 20 67 6f 74 20 68 61 63 6b 65 64 27 29 3b 63 6c 6f 73 65 28 29 22"

# Folder name
folder_name = "hexdata"
os.makedirs(folder_name, exist_ok=True)

# Process hex characters and create empty files
for index, hex_char in enumerate(hex_command.split(), start=1):
    # Create a two-digit filename with the index and hex character
    file_name = f"{index:02d}_{hex_char.replace(' ', '')}.txt"
    file_path = os.path.join(folder_name, file_name)
    
    # Create the empty file
    with open(file_path, 'w') as f:
        pass  # Leave the file empty

print("Empty files have been created.")
