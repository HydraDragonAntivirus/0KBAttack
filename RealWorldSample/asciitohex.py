import os

# Ask the user for the command string
command = input("Please enter the command string: ")

# Convert the command string to hexadecimal
hex_data = ' '.join([f'{ord(c):02X}' for c in command])

# File names
hex_file_name = "hex_data.txt"
input_file_name = "input.txt"

# Write the hexadecimal data to hex_data.txt
with open(hex_file_name, 'w') as hex_file:
    hex_file.write(hex_data)

# Write the original command string to input.txt
with open(input_file_name, 'w') as input_file:
    input_file.write(command)

print(f"Hexadecimal data has been saved to {hex_file_name}.")
print(f"Original command string has been saved to {input_file_name}.")
