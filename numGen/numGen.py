import random

# Ask the user for the size of the array
array_size = int(input("Enter the size of the array: "))
unique_block = int(input("Enter number of unique block: "))

# Generate a list of random numbers based on the provided array size
random_numbers = [random.randint(0, unique_block) for _ in range(array_size)]

# Define the file path and name
file_name = "random_numbers.txt"

# Create and write the random numbers into the text file in array format
with open(file_name, 'w') as file:
    file.write(str(random_numbers))

print(f"Random numbers stored as array data in {file_name}")
