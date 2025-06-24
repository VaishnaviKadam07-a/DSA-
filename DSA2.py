class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

# Hash Table Implementation
class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * self.size

    def _hash(self, key):
        return hash(key) % self.size

    def add(self, key, value):
        index = self._hash(key)
        head = self.table[index]

        while head:
            if head.key == key:
                head.value = value
                print(f"Updated key '{key}' with value '{value}'.")
                return
            head = head.next

        # If key does not exist, insert it at the head of the chain
        new_node = Node(key, value)
        new_node.next = self.table[index]
        self.table[index] = new_node
        print(f"Added key '{key}' with value '{value}'.")

    def update(self, key, value):
        index = self._hash(key)
        head = self.table[index]

        while head:
            if head.key == key:
                head.value = value
                print(f"Updated key '{key}' to new value '{value}'.")
                return
            head = head.next

        print(f"Key '{key}' not found.")

    def delete(self, key):
        index = self._hash(key)
        head = self.table[index]
        prev = None

        while head:
            if head.key == key:
                if prev:
                    prev.next = head.next
                else:
                    self.table[index] = head.next
                print(f"Deleted key '{key}'.")
                return
            prev, head = head, head.next

        print(f"Key '{key}' not found.")

    def search(self, key):
        index = self._hash(key)
        head = self.table[index]

        while head:
            if head.key == key:
                print(f"Key found! {key}: {head.value}")
                return
            head = head.next

        print(f"Key '{key}' not found.")

    def display(self):
        print("\nHash Table Contents:")
        for i, head in enumerate(self.table):
            print(f"Index {i}:", end=" ")
            if head:
                current = head
                while current:
                    print(f"({current.key}: {current.value})", end=" -> ")
                    current = current.next
                print("None")
            else:
                print("Empty")

    def clear(self):
        self.table = [None] * self.size
        print("Hash table cleared.")

def display_menu():
    print("\nHash Table Operations:")
    print("1. Add a key-value pair")
    print("2. Update a value")
    print("3. Delete a key")
    print("4. Search for a key")
    print("5. Display all items")
    print("6. Clear the hash table")
    print("7. Exit")

def main():
    hash_table = HashTable()

    while True:
        display_menu()
        choice = input("\nEnter your choice (1-7): ")

        if choice == "1":
            key = input("Enter key: ")
            value = input("Enter value: ")
            hash_table.add(key, value)
        elif choice == "2":
            key = input("Enter the key to update: ")
            value = input("Enter new value: ")
            hash_table.update(key, value)
        elif choice == "3":
            key = input("Enter the key to delete: ")
            hash_table.delete(key)
        elif choice == "4":
            key = input("Enter the key to search for: ")
            hash_table.search(key)
        elif choice == "5":
            hash_table.display()
        elif choice == "6":
            hash_table.clear()
        elif choice == "7":
            print("Exiting the program.")
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 7.")

# Run the program
if __name__ == "__main__":
    main()

