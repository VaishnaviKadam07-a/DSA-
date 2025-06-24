def hash_function(key, size):
    return key % size

# Linear probing with count of comparisons
def insert_element_linear(arr, size, key):
    index = hash_function(key, size)
    comparisons = 1  # Initial comparison for the first index
    
    if arr[index] is None:
        arr[index] = key
    else:
        print(f"Collision occurred at index {index}. Using linear probing...")
        i = (index + 1) % size
        comparisons += 1  # Increment comparison for probing
        
        while arr[i] is not None:
            i = (i + 1) % size
            comparisons += 1  # Increment comparisons on each collision
        arr[i] = key
        
    print(f"Total comparisons during insertion (linear probing): {comparisons}")

# Quadratic probing with count of comparisons
def insert_element_quadratic(arr, size, key):
    index = hash_function(key, size)
    comparisons = 1  # Initial comparison for the first index
    
    if arr[index] is None:
        arr[index] = key
    else:
        print(f"Collision occurred at index {index}. Using quadratic probing...")
        i = 1
        new_index = (index + i ** 2) % size
        comparisons += 1  # Increment comparison for quadratic probing
        
        while arr[new_index] is not None:
            i += 1
            new_index = (index + i ** 2) % size
            comparisons += 1  # Increment comparisons on each collision
        arr[new_index] = key
        
    print(f"Total comparisons during insertion (quadratic probing): {comparisons}")

def search(arr, size, key):
    index = hash_function(key, size)
    comparisons = 1  # Initial comparison for the first index
    
    if arr[index] == key:
        return index, comparisons

    # Linear probing search with count of comparisons
    i = (index + 1) % size
    comparisons += 1  # Increment comparison for probing
    while arr[i] is not None:
        if arr[i] == key:
            return i, comparisons
        i = (i + 1) % size
        comparisons += 1  # Increment comparisons on each collision

    # Quadratic probing search with count of comparisons
    i = 1
    new_index = (index + i ** 2) % size
    comparisons += 1  # Increment comparison for quadratic probing
    while arr[new_index] is not None:
        if arr[new_index] == key:
            return new_index, comparisons
        i += 1
        new_index = (index + i ** 2) % size
        comparisons += 1  # Increment comparisons on each collision

    return -1, comparisons  # Element not found

def display(arr):
    print("Hash Table:")
    for i in range(len(arr)):
        print(f"Index {i}: {arr[i]}")

n = int(input('Enter the number of elements to store in hash table: '))
print("You are going to enter", n, "elements.")

size = n * 2
arr = [None] * size

for i in range(n):
    ele = int(input(f"Enter the number {i + 1} in array: "))
    insert_element_linear(arr, size, ele)

while True:
    print("\nMenu:")
    print("1. Display the hash table")
    print("2. Insert an element (linear probing)")
    print("3. Insert an element (quadratic probing)")
    print("4. Search for an element")
    print("5. Exit")

    ch = input("Enter your choice: ")

    if ch == '1':
        display(arr)
    elif ch == '2':
        ele = int(input("Enter element to insert (linear probing): "))
        insert_element_linear(arr, size, ele)
    elif ch == '3':
        ele = int(input("Enter element to insert (quadratic probing): "))
        insert_element_quadratic(arr, size, ele)
    elif ch == '4':
        ele = int(input("Enter element to search: "))
        result, comparisons = search(arr, size, ele)
        if result != -1:
            print(f"Element {ele} found at index {result}.")
        else:
            print(f"Element {ele} not found.")
        print(f"Total comparisons during search: {comparisons}")
    elif ch == '5':
        print("Exiting program.")
        break
    else:
        print("Invalid choice. Please try again.")
