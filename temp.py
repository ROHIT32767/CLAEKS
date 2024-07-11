import matplotlib.pyplot as plt
from collections import Counter

# Sample array containing various strings
data = ["AUTOMATED", "RESOLUTION", "AUTOMATED", "ALERT", "WORKFLOW", "RESOLUTION", "AUTOMATED"]

# Count the occurrences of each element
counter = Counter(data)

# Extract the elements and their counts
labels = list(counter.keys())
sizes = list(counter.values())

# Plotting the bar chart
plt.figure(figsize=(10, 6))
bars = plt.bar(labels, sizes, color=plt.cm.Paired(range(len(labels))))

# Add labels and title
plt.xlabel('Elements')
plt.ylabel('Counts')
plt.title('Distribution of Elements in Array')

# Add the values on top of the bars
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval + 0.1, yval, ha='center', va='bottom')

# Display the bar chart
plt.show()
