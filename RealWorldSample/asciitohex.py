import os

# Ask the user for the command string
command = input("Please enter the command string: ")

# Convert the command string to hexadecimal
hex_data = ' '.join([f'{ord(c):02X}' for c in command])

# File name
file_name = "hex_data.txt"

# Write the hexadecimal data to the file
with open(file_name, 'w') as file:
    file.write(hex_data)

print(f"Hexadecimal data has been saved to {file_name}.")
