/*
            FALL 2023-2024, CS-204 HOMEWORK#4
               © OSMAN SAH YILMAZ, 31316
                    24 November 2023
*/

#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node(int inputVal) : val(inputVal), next(nullptr) {}
};

class LinkedListSet {
private:
    Node* head;

    // helper function to check if an element is already in the set
    bool isContain(int inputVal) const {
        Node* current = head;
        while (current) {
            if (current->val == inputVal) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

public:
    LinkedListSet() : head(nullptr) {}

    // Insertion
    LinkedListSet& operator+(int inputVal) {
        if (!isContain(inputVal)) {
            Node* newNode = new Node(inputVal);
            if (!head || inputVal < head->val) {
                newNode->next = head;
                head = newNode;
            }
            else {
                Node* current = head;
                while (current->next && current->next->val < inputVal) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
        return *this;
    }

    // Deletion
    LinkedListSet& operator-(int inputVal) {
        if (!head) return *this;

        if (head->val == inputVal) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* current = head;
            while (current->next && current->next->val != inputVal) {
                current = current->next;
            }
            if (current->next) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
        return *this;
    }

    // operator overloading to union
    LinkedListSet& operator+=(const LinkedListSet& rhs) {
        Node* current = rhs.head;
        while (current) {
            *this + current->val;
            current = current->next;
        }
        return *this;
    }

    // operator overloading to difference
    LinkedListSet& operator-=(const LinkedListSet& rhs) {
        Node* current = rhs.head;
        while (current) {
            *this - current->val;
            current = current->next;
        }
        return *this;
    }

    // Set Intersection
    LinkedListSet& operator&=(const LinkedListSet& rhs) {
        LinkedListSet result;
        Node* current1 = head;
        Node* current2 = rhs.head;

        while (current1 && current2) {
            if (current1->val < current2->val) {
                current1 = current1->next;
            }
            else if (current1->val > current2->val) {
                current2 = current2->next;
            }
            else {
                result + current1->val;
                current1 = current1->next;
                current2 = current2->next;
            }
        }

        // Replace current object with the result
        *this = result;
        return *this;
    }

    // Display
    void display() const {
        cout << "LinkedListSet{";
        Node* current = head;
        while (current) {
            cout << current->val << ", ";
            current = current->next;
        }
        cout << "}" << endl;
    }
};

int main() {

  // Example usage
  LinkedListSet set1;
  set1 + 1 + 2 + 3 + 17; // Insertion
  set1.display();   
  
  set1 - 2; // Deletion
  set1.display(); 
  
  LinkedListSet set2;
  set2 + 3 + 4 + 5; 
  set2.display();   
  
  set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
  set2.display();
  
  LinkedListSet set3;
  set3 + 3 + 4 + 7 + 17 + 41;
  set3.display();
  
  LinkedListSet set4;
  set4 + 41 + 37+ 7 + 19 + 41;
  set4.display();
  
  // Set Union
  set1 += set2;
  set1.display(); 
  
  // Set Difference
  set1 -= set3;
  set1.display(); 
  
  // Set Intersection
  set1 &= set4;
  set1.display(); 
  
  return 0;
}
