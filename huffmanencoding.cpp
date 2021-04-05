#include <string>
#include <stdio.h>
using namespace std;

struct MyNode {
   char key;
   int frequency;
   string code;
   MyNode *left;
   MyNode *right;
};

struct Cell {
   MyNode *node;
   Cell *predecessor;
   Cell *successor;
};

class MyDict {

public:

    MyDict();

    ~MyDict();

    MyNode *get(int &index) const;

    char get_key(int &index) const;

    int get_frequency(char &key) const;

    int get_frequency(int &index) const;

    string get_code(char &key) const;

    int get_count() const;

    void add(char &key);

    void add_code(char &key, string code);

private:

    int count;
    MyNode *null_node;
    Cell *head;
    Cell *tail;
    Cell *null_cell;

    Cell* findKey(char &key) const;
};

MyDict::MyDict() {
    head = NULL;
    tail = NULL;
    count = 0;
    null_node = NULL;
    null_cell = NULL;
}

MyDict::~MyDict() {}

MyNode *MyDict::get(int &index) const {
    Cell *ce = head;
    for (int i = 0; i != index; i++) {
        ce = ce->successor;
    }
    return ce->node;
}

char MyDict::get_key(int &index) const {
    Cell *ce = head;
    for (int i = 0; i != index; i++) {
        ce = ce->successor;
    }
    return ce->node->key;
}

int MyDict::get_frequency(char &key) const {
    Cell *ce = findKey(key);
    if (ce == NULL) {
        return 0;
    } else {
        return ce->node->frequency;
    }
}

int MyDict::get_frequency(int &index) const {
    Cell *ce = head;
    for (int i = 0; i != index; i++) {
        ce = ce->successor;
    }
    return ce->node->frequency;
}

string MyDict::get_code(char &key) const {
    Cell *ce = findKey(key);
    if (ce == NULL) {
        return "";
    } else {
        return ce->node->code;
    }
}

int MyDict::get_count() const {
    return count;
}

void MyDict::add(char &key) {
    Cell *ce = findKey(key);
    if (ce == NULL) {
        MyNode *entry = new MyNode;
        entry->key = key;
        entry->frequency = 1;
        entry->code = "";
        entry->left = NULL;
        entry->right = NULL;

        Cell *c = new Cell;
        c->node = entry;
        c->predecessor = NULL;
        c->successor = NULL;
        if (head == NULL) {
            head = c;
        } else {
            c->predecessor = tail;
            tail->successor = c;
        }
        tail = c;
        count++;
    } else {
        ce->node->frequency = ce->node->frequency + 1;
    }
}

void MyDict::add_code(char &key, string code) {
    Cell *ce = findKey(key);
    ce->node->code = code;
}

Cell *MyDict::findKey(char &key) const {
    Cell *ce = head;
    for (int i = 0; i < count; i++) {
        if (ce->node->key == key) {
            return ce;
        }
        ce = ce->successor;
    }
    return null_cell;
}

class MyQueue {

public:

   MyQueue();

   ~MyQueue();

   int size() const;

   bool isEmpty() const;

   void clear();

   void enqueue(MyNode *n);

   MyNode *dequeue();

   MyNode *peek() const;

private:

   Cell *head;
   Cell *tail;
   int count;
   
   void swap_cell(Cell *c1, Cell *c2);
   void insert_cell(Cell *c1, Cell *c2);

   MyNode *null_node;
   Cell *null_cell;
};

MyQueue::MyQueue() {
    head = NULL;
    tail = NULL;
    count = 0;
    null_node = NULL;
    null_cell = NULL;
}

MyQueue::~MyQueue() {
    clear();
}

int MyQueue::size() const {
    return count;
}

bool MyQueue::isEmpty() const {
    return count == 0;
}

void MyQueue::clear() {
    while (count > 0) {
        dequeue();
    }
}

void MyQueue::enqueue(MyNode *n) {
    Cell *cp = new Cell;
    cp->node = n;
    cp->predecessor = NULL;
    cp->successor = NULL;
    
    if (head == NULL) {
        head = cp;
    } else {
        cp->predecessor = tail;
        tail->successor = cp;
    }
    tail = cp;
    count++;

    if (count != 1) {
        Cell *pre_cp = cp;
        while (cp->node->frequency < pre_cp->predecessor->node->frequency ||
        (cp->node->frequency == pre_cp->predecessor->node->frequency && cp->node->key < pre_cp->predecessor->node->key)) {
            pre_cp = pre_cp->predecessor;
            if (pre_cp == head) {
                break;
            }
        }
        if (pre_cp != cp) {
            insert_cell(pre_cp, cp);
        }
    }
}

MyNode *MyQueue::dequeue() {
    if (isEmpty()) {
        return null_node;
    }
    Cell *cp = head;
    MyNode *result = cp->node;

    if (count != 1) {
        head->successor->predecessor = NULL;
    }
    head = cp->successor;
    if (head == NULL) {
        tail = NULL;
    }
    delete cp;
    count--;
    return result;
}

MyNode *MyQueue::peek() const {
    if (isEmpty()) {
       return null_node;
    }
    return head->node;
}

void MyQueue::swap_cell(Cell *c1, Cell *c2) {
    if (c1->predecessor != NULL) {
        c1->predecessor->successor = c2;
    }
    if (c1 != c2->predecessor) {
        c1->successor->predecessor = c2;
        c2->predecessor->successor = c1;
    }
    if (c2->successor != NULL) {
        c2->successor->predecessor = c1;
    }
    c1->successor = c2->successor;
    c2->predecessor = c1->predecessor;
    c1->predecessor = c2;
    c2->successor = c1;
    if (c1 == head) {
        head = c2;
    }
    if (c2 == tail) {
        tail = c1;
    }
}

void MyQueue::insert_cell(Cell *c1, Cell *c2) {
    if (c2 == tail) {
        tail = c2->predecessor;
    }
    if (c1->predecessor != NULL) {
        c1->predecessor->successor = c2;
    }
    if (c1 != c2->predecessor) {
        if (c2->successor != NULL) {
        c2->successor->predecessor = c2->predecessor;
        }
        c2->predecessor->successor = c2->successor;
    }
    c2->predecessor = c1->predecessor;

    c1->predecessor = c2;
    c2->successor = c1;
    if (c1 == head) {
        head = c2;
    }
}

void count_frequency(string &str, MyDict *my_dict);
void sort_frequency(MyDict *my_dict, MyQueue *my_queue);
void get_Huffman_tree(MyQueue *my_queue);
void get_Huffman_code(MyDict *my_dict, MyQueue *my_queue);
void iterate_Huffman_code(MyDict *my_dict, MyNode *node);
void translate_Huffmann_code(MyDict *my_dict, string &str);

int main() {
    MyDict *my_dict = new MyDict;
    MyQueue *my_queue = new MyQueue;
    string str = "";
    char ch;
    while((ch = getchar_unlocked()) != '\n') {
        str += ch;
    }

    count_frequency(str, my_dict);

    sort_frequency(my_dict, my_queue);

    get_Huffman_tree(my_queue);

    get_Huffman_code(my_dict, my_queue);

    translate_Huffmann_code(my_dict, str);

    return 0;
}

void count_frequency(string &str, MyDict *my_dict) {
    string::size_type len = str.length();
    for (string::size_type i = 0; i != len; i++) {
        my_dict->add(str[i]);
    }
}

void sort_frequency(MyDict *my_dict, MyQueue *my_queue) {
    int count = my_dict->get_count();
    for (int i = 0; i != count; i++) {
        MyNode *node = my_dict->get(i);
        my_queue->enqueue(node);
    }
}

void get_Huffman_tree(MyQueue *my_queue) {
    while (my_queue->size() != 1) {
        MyNode *left = my_queue->dequeue();
        MyNode *right = my_queue->dequeue();
        MyNode *parent = new MyNode;
        parent->key = left->key;
        parent->frequency = left->frequency + right->frequency;
        parent->code = "";
        parent->left = left;
        parent->right = right;
        my_queue->enqueue(parent);
    }
}

void get_Huffman_code(MyDict *my_dict, MyQueue *my_queue) {
    MyNode *root = my_queue->dequeue();
    if (root->left == NULL) {
        root->code = '0';
        my_dict->add_code(root->key, root->code);
        return;
    }
    root->left->code = '0';
    root->right->code = '1';
    iterate_Huffman_code(my_dict, root->left);
    iterate_Huffman_code(my_dict, root->right);
}

void iterate_Huffman_code(MyDict *my_dict, MyNode *node) {
    if (node->left == NULL) {
        my_dict->add_code(node->key, node->code);
        return;
    }
    node->left->code = node->code + '0';
    node->right->code = node->code + '1';
    iterate_Huffman_code(my_dict, node->left);
    iterate_Huffman_code(my_dict, node->right);
}

void translate_Huffmann_code(MyDict *my_dict, string &str) {
    string stri;
    string::size_type leni;
    string::size_type len = str.length();
    for (string::size_type i = 0; i != len; i++) {
        stri = my_dict->get_code(str[i]);
        leni = stri.length();
        for (string::size_type j = 0; j != leni; j++) {
            putchar_unlocked(stri[j]);
        }
    }
}
