#include <iostream>
#include "queue.h"

using namespace std;

int main( )
{
    testQueue();

    Queue<int> queue;
    Queue<int> queue2;

    queue.enqueue(14);
    queue.enqueue(28);
    queue.enqueue(38);

    cout << "Моя очередь: \n";
    cout << queue.peek() << " есть пик очереди, то, что готова к выходу из очереди" <<  endl;

    cout << queue.dequeue() << " был удален \n";
    
    cout << queue.size() << " длина очереди" << endl;
    
    cout << "Моя новая очередь, где приняли 1 человека: \n";

    return 0;
}
