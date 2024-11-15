import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read the CSV file
df = pd.read_csv('../csv_data/cache_performance.csv')

# Extract cache sizes and performance metrics
cache_sizes = df['Cache Size']

# Set the width of the bars
bar_width = 0.15

# Set positions of the bars on the x-axis
index = np.arange(len(cache_sizes))

# Create figure and axis with larger size
plt.figure(figsize=(12, 7))

# Plot bars for each cache replacement policy
plt.bar(index, df['LRU'], bar_width, label='LRU', color='black')
plt.bar(index + bar_width, df['Weighted'], bar_width, label='WVCRP', color='gray')

# Customize the plot
plt.xlabel('Cache Block', fontsize=16, fontweight='bold')
plt.ylabel('Number of Cache Misses', fontsize=16, fontweight='bold')
plt.title('Cache Performance Comparison of LRU and WVCRP', fontsize=18, fontweight='bold')

# Set x-axis ticks perfectly aligned with the center of bar groups
plt.xticks(index + bar_width / 2, cache_sizes, fontsize=14, fontweight='bold')

# Adjust y-axis ticks
plt.yticks(fontsize=14, fontweight='bold')

# Add grid for better readability
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Add legend
plt.legend(fontsize=14, loc='upper right')

# Adjust layout to prevent label cutoff
plt.tight_layout()

# Show plot
plt.show()

# Print statistical summary
print("\nStatistical Summary:")
print("\nAverage misses by policy:")
for policy in ['LRU', 'Weighted']:
    avg_misses = df[policy].mean()
    print(f"{policy}: {avg_misses:.2f}")

print("\nPerformance improvement with cache size:")
