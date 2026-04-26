#include <iostream>
#include <unordered_map>
struct Node {
  int key, value;
  Node *prev;
  Node *next;

  Node(int k, int v) {
    key = k;
    value = v;
    prev = next = nullptr;
  }
};

class LRUCache {
private:
  int capacity;
  std::unordered_map<int, Node *> cache;

  Node *head;
  Node *tail;

  void addToFirst(Node *node);
  void removeNode(Node *node);
  void moveToFront(Node *node);

public:
  LRUCache(int capacity);
  int get(int key);
  void put(int key, int value);
  ~LRUCache();
};

void LRUCache::addToFirst(Node *node) {
  node->next = head->next;
  node->prev = head;
  head->next->prev = node;
  head->next = node;
};

void LRUCache::removeNode(Node *node) {
  Node *prevNode = node->prev;
  Node *nextNode = node->next;
  prevNode->next = nextNode;
  nextNode->prev = prevNode;
  node->prev = nullptr;
  node->next = nullptr;
};

void LRUCache::moveToFront(Node *node) {
  removeNode(node);
  addToFirst(node);
};

LRUCache::LRUCache(int capacity) {
  this->capacity = capacity;

  head = new Node(0, 0);
  tail = new Node(0, 0);

  head->next = tail;
  tail->prev = head;
};

int LRUCache::get(int key) {
  if (cache.find(key) == cache.end()) {
    return -1;
  }
  Node *node = cache[key];
  moveToFront(node);
  return node->value;
};

void LRUCache::put(int key, int value) {

  if (cache.find(key) != cache.end()) {
    Node *node = cache[key];
    node->value = value;
    moveToFront(node);
    return;
  }

  if (cache.size() == capacity) {
    Node *lru = tail->prev;
    std::cout << "Evicting key " << lru->key
              << "\n"; // ai wrote this line not me
    cache.erase(lru->key);
    removeNode(lru);
    delete lru;
  }

  Node *newNode = new Node(key, value);
  addToFirst(newNode);
  cache[key] = newNode;
}

LRUCache::~LRUCache() {

  Node *current = head;
  while (current != nullptr) {
    Node *nextNode = current->next;
    delete current;
    current = nextNode;
  }
};

// ai wrote this last main func block not me
int main() {
  std::cout << "Creating LRU Cache with capacity 2\n";

  LRUCache cache(2);

  std::cout << "put(1,1)\n";
  cache.put(1, 1);

  std::cout << "put(2,2)\n";
  cache.put(2, 2);

  std::cout << "get(1): " << cache.get(1) << "\n";

  std::cout << "put(3,3) -- evicts key 2\n";
  cache.put(3, 3);

  std::cout << "get(2): " << cache.get(2) << "\n";

  std::cout << "put(4,4) -- evicts key 1\n";
  cache.put(4, 4);

  std::cout << "get(1): " << cache.get(1) << "\n";
  std::cout << "get(3): " << cache.get(3) << "\n";
  std::cout << "get(4): " << cache.get(4) << "\n";

  std::cout << "Program ending, destructor frees memory.\n";

  return 0;
}
