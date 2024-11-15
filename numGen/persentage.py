# # Cache miss counts for Weighted and LFU policies
# weighted_misses = [122947, 105753, 70004, 35222]
# lfu_misses = [122749, 105379, 70606, 35937]

# # Calculate total misses
# total_weighted_misses = sum(weighted_misses)
# total_lfu_misses = sum(lfu_misses)

# # Calculate overall percentage difference
# overall_percentage_difference = (total_weighted_misses - total_lfu_misses) / total_weighted_misses * 100

# # Display result
# print(f"Overall Percentage Difference between LFU and Weighted: {overall_percentage_difference:.2f}%")
# Cache miss counts for LRU and Weighted policies
lru_misses = [123090, 106154, 71667, 36478]
weighted_misses = [122947, 105753, 70004, 35222]

# Calculate total misses
total_lru_misses = sum(lru_misses)
total_weighted_misses = sum(weighted_misses)

# Calculate overall percentage difference
overall_percentage_difference_lru_weighted = (total_lru_misses - total_weighted_misses) / total_lru_misses * 100

# Display result
print(f"Overall Percentage Difference between LRU and Weighted: {overall_percentage_difference_lru_weighted:.2f}%")
