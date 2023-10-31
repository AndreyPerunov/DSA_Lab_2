#include <iostream>
#include <fstream>
#include <string>
#include <vector>  

// STACK
template<typename T>
class Stack {
  public:
    Stack();
    void push(T element);
    T pop();
    T peek();
    bool contains(T element);
    void print();
  private:
    int top;
    std::vector<T> elements;
};

template <typename T>
Stack<T>::Stack() {
  top = -1;
  elements = {};
}

template<typename T>
void Stack<T>::push(T element) {
  elements.push_back(element);
  top++;
}

template<typename T>
T Stack<T>::pop() {
  if (top == -1) {
    return "";
  }

  T element = elements[top];
  elements.pop_back();
  top--;

  return element;
}

template<typename T>
T Stack<T>::peek() {
  if (top == -1) {
    return "";
  }

  return elements[top];
}

template<typename T>
bool Stack<T>::contains(T element) {
  for (T el : elements) {
    if (el == element) {
      return true;
    }
  }
  return false;
}

template<typename T>
void Stack<T>::print() {
  if (top == -1) {
    // std::cout << "empty ";
    return;
  }
  // std::cout << "Stack: ";
  for (T element : elements) {
    std::cout << "['" << element << "'] ";
  }
}


// HASHMAP:
// (key, value) ==> ("return", "return") ==> "return" ==> 128321083 ==> 2
// 0 -- ["}"]
// 1 -- []
// 2 -- ["a", ";", "return"]
// 3 -- ["b"]
// 4 -- ["if"]

template<typename T>
class HashTable {
  private:
    int numberOfBuckets = 80; // twice amount of data (lines in programm_text.data)
    int elementsCount = 0;
    std::vector<Stack<T>> buckets;
  public:
    HashTable();
    long hashFunction(std::string key);
    void add(std::string key, T value);
    void remove(std::string key); // delete specified element from the collection
    T get(std::string key); // search for a value by the given key
    bool contains(std::string key);
    void print(); // display the contents of the dataset
};

template<typename T>
HashTable<T>::HashTable() {
  buckets = {};
  for (int i = 0; i < numberOfBuckets; i++) {
    Stack<T> stack = Stack<T>();
    buckets.push_back(stack);
  }
}

template<typename T>
long HashTable<T>::hashFunction(std::string key) {
  long hash = 0;
  for (int i = 0; i < key.length(); i++) {
    hash+= (hash << 5)-hash + int(key[i]);
  }
  hash = abs(hash);

  return hash;
}

template<typename T>
void HashTable<T>::add(std::string key, T value) {
  if (value == "") return;
  if (contains(key)) return;
  if(buckets.size() == elementsCount) {
    // Resizing the hash table
    std::vector<Stack<T>>newBuckets (numberOfBuckets * 2);
    for (int i = 0; i < numberOfBuckets; i++) {
      std::string keyExisting;
      do {
        keyExisting = buckets[i].pop();
        if (keyExisting == "") break;
        long index = hashFunction(keyExisting) % (numberOfBuckets * 2);
        newBuckets[index].push(keyExisting);
      } while (keyExisting != "");
    }
    buckets = newBuckets;
    numberOfBuckets *= 2;
  }
  elementsCount++;
  long index = hashFunction(key) % numberOfBuckets;
  buckets[index].push(value);
}

template<typename T>
void HashTable<T>::remove(std::string key) {
  long index = hashFunction(key) % numberOfBuckets;
  if (buckets[index].peek() == "") {
    std::cout << "[ERR] Bucket " << index << " is empty" << std::endl;
    return;
  }
  Stack<T> newStack = Stack<T>();
  std::string element;
  do {
    element = buckets[index].pop();
    if (element == "") {
      break;
    }
    if (element == key) {
      // skip this element
      continue;
    }
    newStack.push(element);
  } while (element != "");

  buckets[index] = newStack;
}

template<typename T>
T HashTable<T>::get(std::string key) {
  long index = hashFunction(key) % numberOfBuckets;
  Stack stack = buckets[index];
  std::string element = stack.pop();
  do {
    if (element == key) {
      return element;
    }
    element = stack.pop();
  } while (element != "");
  return "";
}

template<typename T>
bool HashTable<T>::contains(std::string key) {
  if (get(key) == "") {
    return false;
  }
  return true;
}

template<typename T>
void HashTable<T>::print() {
  std::cout << "Hash Table: " << std::endl;
  std::cout << "Total number of elements: " << elementsCount << std::endl;
  for (int i = 0; i < numberOfBuckets; i++) {
    std::cout << "[" << i << "]: ";
    buckets[i].print();
    std::cout << std::endl;
  }
}

void readData(std::string filename, std::vector<std::string>& arr) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }

  std::string line;

  while (getline(file, line)) {
    try {
      arr.push_back(line);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error reading line number." << std::endl;
    }
  }

  file.close();
}

int main() {
  std::vector<std::string> programm;
  readData("programm_text.data", programm);
  // first line is ���def for some reason
  programm[0] = programm[0].substr(3);

  HashTable HT = HashTable<std::string>();
  
  for (std::string line : programm) {
    HT.add(line, line);
  }

  HT.print();

  return 0;
}