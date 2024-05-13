#include <iostream>
#include "deQueue.h"

using namespace std;

int main( )
{
    testDeQueue();
    cout << "Тесты прошли успешно \n";

    DeQueue<int> queue;
    DeQueue<int> queue2;

    queue.pushFront(14);
    queue.pushFront(28);
    queue.pushFront(38);

    // cout << "Моя очередь после pushFront: \n" << queue.to_string() << endl;

    queue.pushBack(14);
    queue.pushBack(28);
    queue.pushBack(38);

    // cout << "Моя очередь после pushBack: \n" << queue.to_string() << endl;

    // cout << "Сделали popBack: \n И удалили: " << queue.popBack() << "\nПолучили очередь: \n" << queue.to_string() << endl;
    // cout << "Сделали popFront: \n И удалили: " << queue.popFront() << "\nПолучили очередь: \n" << queue.to_string() << endl;

    queue.clear();
    // cout << "Почистив, получили очередь: " << queue.to_string() << endl;

    // cout << "Моя очередь: \n";
    // cout << queue.peek() << " есть пик очереди, то, что готова к выходу из очереди" <<  endl;

    // cout << queue.dequeue() << " был удален \n";
    
    // cout << queue.size() << " длина очереди" << endl;
    
    // cout << "Моя новая очередь, где приняли 1 человека: \n";

    // cout << queue.to_string();

    return 0;
}
