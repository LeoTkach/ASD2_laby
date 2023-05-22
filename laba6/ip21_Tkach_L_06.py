import matplotlib.pyplot as plt
import random
import string
from random import shuffle



class HashTable:
    def __init__(self, size):
        self.size = size
        self.keys = [None] * self.size
        self.values = [None] * self.size
        self.comparisons = 0
        self.table1 = list(range(self.size))
        shuffle(self.table1)

    def pearson_hash(self, key, table_size, table1):
        
        hash_val = 0
        for char in key:
            hash_val = (table1[(hash_val ^ ord(char)) % table_size] + hash_val) % table_size
        return hash_val
    
    def double_hash_func(self, key, i):
        hash_val1 = self.pearson_hash(key, self.size , self.table1)
        hash_val2 = 1+ self.pearson_hash(key, self.size - 1, self.table1)
        return (hash_val1 + i * hash_val2) % self.size

    def insert(self, key, value):
        index = self.pearson_hash(key, self.size, self.table1)
        if self.keys[index] is None:
            self.keys[index] = key
            self.values[index] = value
        else:
            i = 1
            while i < self.size:
                index = self.double_hash_func(key, i)
                if self.keys[index] is None:
                    self.keys[index] = key
                    self.values[index] = value
                    return True
                i += 1
        return False



    def search(self, key):
        i = 0
        while i < self.size:
            index = self.double_hash_func(key, i)
            self.comparisons += 1
            if self.keys[index] is None:
                return None
            elif self.keys[index] == key:
                return self.values[index]
            i += 1
        return None

def generate_random_key(length):
    return ''.join(random.choices(string.ascii_letters, k=length))

def generate_random_value(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def plot_graph(sizes, comparisons):
    plt.plot(sizes, comparisons, marker='o')
    plt.xlabel('Розмірність структури')
    plt.ylabel('Кількість порівнянь')
    plt.title('Залежність кількості порівнянь від розмірності структури')
    plt.show()

sizes = [100, 1000, 5000, 10000, 20000]
comparisons = []

for size in sizes:
    hash_table = HashTable(size)
    keys = [generate_random_key(20) for _ in range(size)]
    values = [generate_random_value(200) for _ in range(size)]

    for i in range(size):
        key = keys[i]
        value = values[i]
        hash_table.insert(key, value)

    random_index = random.randint(0, size - 1)
    key_to_search = keys[random_index]
    hash_table.search(key_to_search)
    comp_count = hash_table.comparisons
    comparisons.append(comp_count)

plot_graph(sizes, comparisons)

size = int(input("\nВведіть розмірність таблиці: "))
hash_table = HashTable(size)
keys = [generate_random_key(20) for _ in range(size)]
values = [generate_random_value(200) for _ in range(size)]
for i in range(size):
    key = keys[i]
    value = values[i]
    hash_table.insert(key, value)
index = int(input("Введіть індекс згенерованого ключа для пошуку його в таблиці: "))
if index >= 0 and index < len(keys):
    key_to_search = keys[index]
    print(f"Ключ за індексом {index} дорівнює: {key_to_search}")
    print(f"\nЗгенероване начення елемента за ключем {key_to_search} дорівнює: ", values[index])
else:
    print("Введений індекс недійсний.")
print("\nПошук елемента в таблиці...")
print(f"Значення елемента за ключем {key_to_search} в таблиці дорівнює: ", hash_table.search(key_to_search),"\n")



