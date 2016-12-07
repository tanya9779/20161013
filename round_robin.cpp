#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

// Реализация КРУГОВОГО СВЯЗНОГО БУФЕРА - КОЛЬЦА на с++

class Entity // это Сущность - то что является элементом КОЛЬЦА 
{
    private: // приватные данные класса напрямую менять нельзя
        char * data;   // пока только один атрибут
        // но если потребуется мы легко добавим сюда ещё
    public: // открытые данные класса
        // эти указатели доступны для присвоения снаружи       
        Entity * next; // указатель на следующего - пусть по часовой стрелке
        Entity * prev; // указатель на предыдущего - пусть против часовой

        // конструктор класса
        Entity(char * d) { 
                    data = d;
                    next = this; // это кольцо из одного элемента - поэтому
                    prev = this;  //  указатели на себя
        }    

        // деструктор класса 
        ~Entity() { 
             delete data; // нужно освободить память 
             // для отладки выведем на экран
             std::cout << "\n In ~Entity() destructor \n\n";
        }
        // методы класса        
        char * getData() { // возвращает строку data
              return data;
        }      
        // добавление нового значения в КОЛЬЦО
        void insert(char * v) // всегда добавляем перед элементом (this) - у нас ведь кольцо
        {                     // и левым соседом первого является последний
             Entity * ins = new Entity(v); // выделим память под новый элемент

             // модифицируем все указатели
             ins->next = this; // ins станет левым соседом для this
             ins->prev = this->prev; // назначение новому элементу левого соседа 

             prev->next = ins; // выставляем next указатель на нового
             this->prev = ins; // и prev указатель на него

             if (this->next==this) // Это если в КОЛЬЦЕ был только один элемент
                 this->next = ins; // то поправим - появляется второй
        }  

        // удаление указанного значения
        Entity * remove(char * v) // мы возвращаем указатель на новый объект "СУЩНОСТЬ"
        {       // нужно осторожно удалять - можно потерять все, если удалить this
             Entity * new_this = this; // это будем новый указатель на КОЛЬЦО
             Entity * current = this; // будем перебирать все элементы
                     // потому что значение сначала нужно найти
             do {
                  if ( strcmp( current->getData(), v) == 0 ) { // найдено
                       current->prev->next = current->next;
                       current->next->prev = current->prev;
                       if (current == this) // сейчас удалим текущий элемент
                            new_this = next; // чтобы не потерять наше КОЛЬЦО
                       delete current; // должен вызваться деструктор
                       break; // выход из цикла do {} while
                  }             
                  current = current->next; // переход к следующему
             } while (current != this); // защита от зацикливания
             return new_this;    
        }        

        // вывод КОЛЬЦА на экран - обход по часовой
        void print()
        {
             Entity * current = this; // будем перебирать все элементы
             do {
                  std::cout << " (" <<   current->getData() << ") -> "; // Выводим значение на экран
                  current = current->next; 
             } while (current != this);
             std::cout << "\n";
        }
        // вывод КОЛЬЦА на экран с обходом против часовой
        void print_revert()
        {
             Entity * current = this; // будем перебирать все элементы
             do {
                  std::cout << " (" <<   current->getData() << ") <- "; // Выводим значение на экран
                  current = current->prev; // отличие только в этой строке 
             } while (current != this);
             std::cout << "\n";
        }


};

int main()
{
    Entity * circle = new Entity("first"); // указатель на кольцо из одного элемента
    // добавим еще несколько
    circle->insert("second");
    circle->insert("third");
    circle->insert("fourth");
    circle->insert("fifth");
    circle->insert("sixth");
    
    std::cout << "============= TEST PRINT DIRECT ===============\n";
    circle->print();  // выведем на экран - обход вперед
    std::cout << "============= TEST PRINT REVERT ===============\n";
    circle->print_revert();  // выведем на экран - обход назад
    std::cout << "============= TEST PRINT FROM THIRD ===============\n";
    circle->next->next->print();  // выведем на экран начиная с третьего
    circle->next->next->print_revert();  // выведем на экран начиная с третьего
                // первые две стрелки -> ведут к следующему следующего
                // третья стрелка вызывает метод класса print()
    std::cout << "============= TEST DELETE third FROM CIRCLE ===============\n";
    circle = circle->remove("third"); 
    circle->print();  // выведем на экран после удаления third
    std::cout << "============= TEST INSERT (NEWLY INSERTED) TO CIRCLE ===============\n";
    circle->insert("NEWLY INSERTED");
    circle->print();  // выведем на экран после добавления

    std::cout << "============= TEST DELETE THIS (first)!!!! ===============\n";
    circle = circle->remove("first"); 
    circle->print();  // выведем на экран
    circle->print_revert();  // выведем на экран - обход назад

  // только для отладки, чтобы окно запущенной программы не закрывалось
  std::cout << "enter any integer number...";
  int z;
  std::cin >> z;
}


