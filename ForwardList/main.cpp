#include<iostream>
using namespace std;
#define tab "\t"
#define BASE_CHECK

class Element
{
    int Data;
    Element* pNext;
    static int count;
public:
    
    Element(int Data, Element* pNext = nullptr): Data(Data), pNext(pNext)
    {
        count ++;
        //cout << "EConstructor: \t" << this << endl;
    }
    
    ~Element ()
    {
        count --;
        //cout << "EDestructor:\t" << this << endl;
    }
    friend class ForwardList;
};

int Element::count = 0;

class ForwardList // односвязный (однонаправленный) список
{
    Element* Head; // Голова списка, указывает на начальный элемент списка
    unsigned int size; // размер списка
    
public:
    ForwardList()
    {
        Head = nullptr; // Если голова указывает на 0, то список пуст
        size = 0;
        //cout << "LConstructor: \t" << this << endl;
    }
    ~ForwardList()
    {
        //cout << "LDestructor:\t" << this << endl;
    }
    // MARK: -- ADDING ELEMENTS
    
    void push_front(int Data)
    {
        Element* New = new Element(Data); // создаем новый элемент и помещаем в него значение Data
        New -> pNext = Head; // привязываем новый элемент в начало списка
        Head = New; //переводим голову на новый элемент
        size ++;
    }
    void push_back(int Data)
    {
        // Проверяем, является ли список пустым.
        if (Head == nullptr)
            return push_front(Data);
        // 1. Создаем новый элемент:
        Element* New = new Element(Data);
        // 2. Доходим до конца списка:
        Element* Temp = Head;
        while(Temp -> pNext)// пока pNext текущего элемента не 0
            Temp = Temp -> pNext; // переходим на следующий элемент
        // Теперь находимся в последнем элементе, то есть Temp -> pNext == nullptr
        // Теперь мы находимся в последнем элементе
        // 3. Присоединяем новый элемент к последнему:
        Temp -> pNext = New;
        size ++;
    }
    // MARK: -- REMOVING ELEMENTS:
    
    void pop_front()
    {
        if (Head == nullptr) return; // проверка на заполненность списка
        // 1. Запоминаем адрес удаляемого элемента:
        Element* Erased = Head;
        // 2. Исключаем удаляемый элемент из списка
        Head = Erased -> pNext;
        // 3. Удаляем элемент из памяти:
        delete Erased;
        size --;
    }
    void pop_back()
    {
        if (Head == nullptr) return;
        if (Head -> pNext == nullptr) return pop_front();
        // 1. Доходим до предпоследнего элемента
        Element* Temp = Head; // создаем итератор
        while(Temp->pNext->pNext) Temp = Temp->pNext;
        // 2. Удаляем элемент их памяти:
        delete Temp -> pNext;
        // 3. Затираем адрес удаленного элемента нулем
        Temp -> pNext = nullptr;
        size --;
    }
    void insert(int index, int Data)
    {
        if (index == 0 || Head == nullptr) return push_front(Data);
        if (index > size) return;
        Element* New = new Element(Data);
        // 1. Доходим до нужного элемента
        Element* Temp = Head;
        for (int i = 0; i < index - 1; ++i)
        {
            Temp = Temp -> pNext;
        }
        // 2. Включаем новый элемент в список:
        New -> pNext = Temp -> pNext;
        Temp -> pNext = New;
        size ++;
    }
    void erase(int index)
    {
        if (index > size) return;
        if (index == 0) return pop_front();
        // 1. Доходим до нужного объекта
        Element* Temp = Head;
        for (int i = 0; i < index - 1; ++i) {
            Temp = Temp -> pNext;
        }
        // 2. Запоминаем адрес удаляемого элемента:
        Element* Erased = Temp -> pNext;
        // 3. Исключаем элемент из списка
        Temp -> pNext = Temp -> pNext -> pNext;
        // 4. Удаляем элемент из памяти
        delete Erased;
        size --;

    }
    
    // MARK: -- METHODS:
    
    void print()const
    {
        Element* Temp = Head; // Temp это итератор
        // Итератор это указатель, при помощи которого нужно получить доступ к следующему элементу структуры данных
        while (Temp) // пока итератор содержит не нулевой адрес
        {
            cout << Temp << tab << Temp -> Data << tab << Temp -> pNext << endl;
            Temp = Temp -> pNext; // переход на следующий элемент
        }
        cout << "Element's count of the list: " << size << endl;
        cout << "General count of elements: " << Head -> count << endl;
    }
};

int main()
{
    
#ifdef BASE_CHECK
    int n;
    cout << "Enter the size of the list: "; cin >> n;
    ForwardList list;
    for(int i = 0; i < n; ++i)
    {
        //list.push_front(rand() % 100);
        list.push_back(rand() % 100);
    }
    list.print();
   /*
    list.push_back(123);
    list.print();
    cout << endl;
    list.pop_front();
    list.pop_back();
    list.print();
    cout << endl;
    */
    
    int index = 0;
    int value = 0;
    
    cout << "Enter index: "; cin >>  index;
//    cout << "Enter value: "; cin >> value;
//    list.insert(index, value);
//    list.print();
    cout << endl;
    list.erase(index);
    list.print();
    
    
#endif // BASE_CHECK

    /*
    ForwardList list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1.print();
    
    cout << endl;
    
    ForwardList list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    list2.print();
   */
    
    return 0;
}
