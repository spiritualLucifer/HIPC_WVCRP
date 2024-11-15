import csv

# Open and read the text file
with open("data.txt", "r") as file:
    lines = file.read().strip().split("\n")

# Extracting the instruction and range values
instruction = int(lines[0].split(":")[1].strip())
rang = lines[1].split(":")[1].strip()

# Prepare to store parsed data
data = []
cache_size = None
cache_metrics = {}

# Process the remaining lines for cache sizes and metrics
for line in lines[2:]:
    if "Cache Size" in line:
        if cache_metrics:  # If we have collected previous cache data, append it to the list
            data.append([instruction, rang, cache_size] + list(cache_metrics.values()))
        # Update the current cache size
        cache_size = int(line.split(":")[1].strip())
        cache_metrics = {}
    else:
        # Extract metric values (LRU, Weighted, etc.)
        key, value = line.split(":")
        cache_metrics[key.strip()] = int(value.strip())

# Append the last set of data after processing all lines
if cache_metrics:
    data.append([instruction, rang, cache_size] + list(cache_metrics.values()))

# Define the CSV file name
csv_filename = "cache_performance.csv"

# Define the headers for the CSV file
headers = ["Instruction", "Range", "Cache Size", "LRU", "Weighted"]

# Writing to CSV, appending if the file already exists
with open(csv_filename, mode="a", newline="") as csvfile:
    writer = csv.writer(csvfile)
    
    # Write the header only if the file is empty (first time)
    if csvfile.tell() == 0:  
        writer.writerow(headers)

    # Write the data rows
    writer.writerows(data)

print(f"Data has been written to {csv_filename}")
