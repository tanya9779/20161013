#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

// ���������� ��������� �������� ������ - ������ �� �++

class Entity // ��� �������� - �� ��� �������� ��������� ������ 
{
    private: // ��������� ������ ������ �������� ������ ������
        char * data;   // ���� ������ ���� �������
        // �� ���� ����������� �� ����� ������� ���� ���
    public: // �������� ������ ������
        // ��� ��������� �������� ��� ���������� �������       
        Entity * next; // ��������� �� ���������� - ����� �� ������� �������
        Entity * prev; // ��������� �� ����������� - ����� ������ �������

        // ����������� ������
        Entity(char * d) { 
                    data = d;
                    next = this; // ��� ������ �� ������ �������� - �������
                    prev = this;  //  ��������� �� ����
        }    

        // ���������� ������ 
        ~Entity() { 
             delete data; // ����� ���������� ������ 
             // ��� ������� ������� �� �����
             std::cout << "\n In ~Entity() destructor \n\n";
        }
        // ������ ������        
        char * getData() { // ���������� ������ data
              return data;
        }      
        // ���������� ������ �������� � ������
        void insert(char * v) // ������ ��������� ����� ��������� (this) - � ��� ���� ������
        {                     // � ����� ������� ������� �������� ���������
             Entity * ins = new Entity(v); // ������� ������ ��� ����� �������

             // ������������ ��� ���������
             ins->next = this; // ins ������ ����� ������� ��� this
             ins->prev = this->prev; // ���������� ������ �������� ������ ������ 

             prev->next = ins; // ���������� next ��������� �� ������
             this->prev = ins; // � prev ��������� �� ����

             if (this->next==this) // ��� ���� � ������ ��� ������ ���� �������
                 this->next = ins; // �� �������� - ���������� ������
        }  

        // �������� ���������� ��������
        Entity * remove(char * v) // �� ���������� ��������� �� ����� ������ "��������"
        {       // ����� ��������� ������� - ����� �������� ���, ���� ������� this
             Entity * new_this = this; // ��� ����� ����� ��������� �� ������
             Entity * current = this; // ����� ���������� ��� ��������
                     // ������ ��� �������� ������� ����� �����
             do {
                  if ( strcmp( current->getData(), v) == 0 ) { // �������
                       current->prev->next = current->next;
                       current->next->prev = current->prev;
                       if (current == this) // ������ ������ ������� �������
                            new_this = next; // ����� �� �������� ���� ������
                       delete current; // ������ ��������� ����������
                       break; // ����� �� ����� do {} while
                  }             
                  current = current->next; // ������� � ����������
             } while (current != this); // ������ �� ������������
             return new_this;    
        }        

        // ����� ������ �� ����� - ����� �� �������
        void print()
        {
             Entity * current = this; // ����� ���������� ��� ��������
             do {
                  std::cout << " (" <<   current->getData() << ") -> "; // ������� �������� �� �����
                  current = current->next; 
             } while (current != this);
             std::cout << "\n";
        }
        // ����� ������ �� ����� � ������� ������ �������
        void print_revert()
        {
             Entity * current = this; // ����� ���������� ��� ��������
             do {
                  std::cout << " (" <<   current->getData() << ") <- "; // ������� �������� �� �����
                  current = current->prev; // ������� ������ � ���� ������ 
             } while (current != this);
             std::cout << "\n";
        }


};

int main()
{
    Entity * circle = new Entity("first"); // ��������� �� ������ �� ������ ��������
    // ������� ��� ���������
    circle->insert("second");
    circle->insert("third");
    circle->insert("fourth");
    circle->insert("fifth");
    circle->insert("sixth");
    
    std::cout << "============= TEST PRINT DIRECT ===============\n";
    circle->print();  // ������� �� ����� - ����� ������
    std::cout << "============= TEST PRINT REVERT ===============\n";
    circle->print_revert();  // ������� �� ����� - ����� �����
    std::cout << "============= TEST PRINT FROM THIRD ===============\n";
    circle->next->next->print();  // ������� �� ����� ������� � ��������
    circle->next->next->print_revert();  // ������� �� ����� ������� � ��������
                // ������ ��� ������� -> ����� � ���������� ����������
                // ������ ������� �������� ����� ������ print()
    std::cout << "============= TEST DELETE third FROM CIRCLE ===============\n";
    circle = circle->remove("third"); 
    circle->print();  // ������� �� ����� ����� �������� third
    std::cout << "============= TEST INSERT (NEWLY INSERTED) TO CIRCLE ===============\n";
    circle->insert("NEWLY INSERTED");
    circle->print();  // ������� �� ����� ����� ����������

    std::cout << "============= TEST DELETE THIS (first)!!!! ===============\n";
    circle = circle->remove("first"); 
    circle->print();  // ������� �� �����
    circle->print_revert();  // ������� �� ����� - ����� �����

  // ������ ��� �������, ����� ���� ���������� ��������� �� �����������
  std::cout << "enter any integer number...";
  int z;
  std::cin >> z;
}


