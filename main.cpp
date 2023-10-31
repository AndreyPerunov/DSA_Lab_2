#include <iostream>
#include <fstream>
#include <string>
#include <vector>  

// TODO: Evaluate the speed of the algorithms on different numbers of elements.
// TODO: +add new element at the end of the collection of the data;
// TODO: +add new element at the beginning of the collection of the data;
// TODO: +add the element after specified element;

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
    std::cout << "[ERR] Stack is empty" << std::endl;
    return NULL;
  }

  T element = elements[top];
  elements.pop_back();
  top--;

  return element;
}

template<typename T>
T Stack<T>::peek() {
  if (top == -1) {
    std::cout << "[ERR] Stack is empty" << std::endl;
    return NULL;
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
    std::cout << "empty ";
    return;
  }
  std::cout << "Stack: ";
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
    int numberOfBuckets = 100; // twice amount of data (lines in programm_text.data)
    std::vector<Stack<T>> buckets;
  public:
    HashTable();
    long long hashFunction(std::string key);
    void add(std::string key, T value);
    void remove(std::string key); // delete specified element from the collection
    T get(std::string key); // search for a value by the given key
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
long long HashTable<T>::hashFunction(std::string key) {
  long long hash = 0;
  for (int i = 0; i < key.length(); i++) {
    hash+= (hash << 5)-hash + int(key[i]);
  }
  hash = abs(hash);

  return hash % numberOfBuckets;
}

template<typename T>
void HashTable<T>::add(std::string key, T value) {
  long index = hashFunction(key);
  buckets[index].push(value);
  // TODO: check if bucket contains element with the same key
}

template<typename T>
void HashTable<T>::remove(std::string key) {
  long index = hashFunction(key);
  if (buckets[index].peek != NULL) {
    std::cout << "[ERR] Bucket " << index << " is empty" << std::endl;
    return;
  }
  if (hashString(buckets[index].peek()) == key){
    buckets[index].pop();
    return;
  }
  // TODO: delete specified element from the collection
}

template<typename T>
T HashTable<T>::get(std::string key) {
  long index = hashFunction(key);
  return buckets[index].peek();
  // TODO: search for a value by the given key
}

template<typename T>
void HashTable<T>::print() {
  std::cout << "Hash Table: " << std::endl;
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

void print(std::vector<std::string> vec) {
  for (std::string str : vec) {
    std::cout << str << std::endl;
  }
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