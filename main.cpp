#include <iostream>
#include "LinkedList.h"
using namespace std;

// Добавление элемента в конец
void addElement(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Удаление элемента по значению
void deleteElement(Node*& head, int value) {
    if (!head) return;
    
    Node* current = head;
    while (current) {
        if (current->data == value) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            delete current;
            return;
        }
        current = current->next;
    }
}

// Ввод списка с клавиатуры
Node* inputList() {
    Node* head = nullptr;
    int n, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        addElement(head, value);
    }
    return head;
}

Node* createList(const vector<int>& numbers) {//сделать цепочку из чисел
    if (numbers.empty()) {//проверяем пустоту
        return nullptr;//если тру то вернем null
    }
  
  Node* head = new Node(numbers[0]);//первый узел
  Node* current = head;
  
  for (int i = 1; i < numbers.size(); i++) {//начиная со второго...
      Node* newNode = new Node(numbers[i]);//создаем новый узел
      current->next = newNode;//текущий связываем со следующим через указатель
      newNode->prev = current;//новый связываем с предыдущим
      current = newNode;
  }
  return head;//возвращаем первый узел (он знает где следующие)
}

Node* findNode(Node* head, int c) {
  Node* current = head;
  while (current != nullptr) {
      if (current->data == c) return current;
      current = current->next;
  }
  return nullptr;
}

pair<Node*, Node*> splitList(Node* head, int c) {
  Node* target = findNode(head, c);
  
  // Список 1: числа ДО c в ОБРАТНОМ порядке
  Node* list1 = nullptr;
  Node* current = target->prev; // Идём назад от c
  Node* list1Tail = nullptr;
  
  while (current != nullptr) {
      Node* newNode = new Node(current->data);
      if (list1 == nullptr) {
          list1 = newNode;
          list1Tail = newNode;
      } else {
          list1Tail->next = newNode;  // Добавляем в конец
          newNode->prev = list1Tail;
          list1Tail = newNode;
      }
      current = current->prev;
  }
  
  // Список 2: числа после c
  Node* list2 = nullptr;
  current = target->next; // Идём вперёд от c
  Node* list2Tail = nullptr;
  
  while (current != nullptr) {
      Node* newNode = new Node(current->data);
      if (list2 == nullptr) {
          list2 = newNode;
          list2Tail = newNode;
      } else {
          list2Tail->next = newNode;
          newNode->prev = list2Tail;
          list2Tail = newNode;
      }
      current = current->next;
  }
  
  return {list1, list2};
}

void printList(Node* head) {
    Node* current = head;//берем первый узел
    while (current != nullptr) {//пока узлы есть
        cout << current->data << " ";//печатаем текущую
        current = current->next;//переходим к следующей
    }
    cout << endl;
}

int main() {
    // Начальный список
    vector<int> initialNumbers = {6, 4, 3, 8, 9, 1, 2};
    Node* originalList = createList(initialNumbers);
    
    cout << "=== ПРОГРАММА ДЛЯ РАБОТЫ СО СПИСКОМ ===" << endl;
    cout << "Начальный список: ";
    printList(originalList);
    
    int choice;
    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Показать текущий список" << endl;
        cout << "2. Добавить элемент" << endl;
        cout << "3. Удалить элемент" << endl;
        cout << "4. Ввести число C и разделить список" << endl;
        cout << "5. Выйти из программы" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Текущий список: ";
                printList(originalList);
                break;
            }
            case 2: {
                int value;
                cout << "Введите элемент для добавления: ";
                cin >> value;
                addElement(originalList, value);
                cout << "Элемент добавлен! Новый список: ";
                printList(originalList);
                break;
            }
            case 3: {
                int value;
                cout << "Введите элемент для удаления: ";
                cin >> value;
                deleteElement(originalList, value);
                cout << "Текущий список: ";
                printList(originalList);
                break;
            }
            case 4: {
                int c;
                cout << "Введите число C: ";
                cin >> c;
                
                if (!findNode(originalList, c)) {
                    cout << "Ошибка: число " << c << " не найдено в списке!" << endl;
                    break;
                }
                auto [list1, list2] = splitList(originalList, c);
                
                cout << "\n=== РЕЗУЛЬТАТ РАЗДЕЛЕНИЯ ===" << endl;
                cout << "Исходный список: ";
                printList(originalList);
                cout << "Число C: " << c << endl;
                cout << "Список 1 (до " << c << " в обратном порядке): ";
                printList(list1);
                cout << "Список 2 (после " << c << " в прямом порядке): ";
                printList(list2);
                
                // Очищаем память результирующих списков
                // (в реальной программе нужно добавить функцию очистки)
                break;
            }
            case 5: {
                cout << "Выход из программы..." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 5);
    
    return 0;
}
