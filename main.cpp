#include <iostream>
#include <algorithm>
#include "octagon.h"
#include "containers/queue.h"

/*==================план действий============//
 * сделать менюшку с кейсами. Кейсы:
 * ман
 * выход
 * очистка очереди
 * обычный пуш
 * пуш по номеру
 * обычный поп
 * делит по номеру
 * вывод очереди на экран
 * вывод кол-ва октагонов с площадью меньше заданной (зачем???)
//===========================================*/

int main() {
    /*Octagon<int> test1(std::cin);
    Octagon<int> test2(std::cin);
    Octagon<int> test3(std::cin);

    containers::queue<Octagon<int>> q;
    containers::queue<Octagon<int>> c_q;

    q.push(test1);
    q.push(test2);
    q.push(test3);
    q.push(test1);
    q.push(test2);
    q.push(test3);
    std::for_each(q.begin(), q.end(), [](Octagon<int>& X){X.Printout(std::cout);});
    std::cout << q.length() << std::endl;

    //c_q = q;
    //std::for_each(c_q.begin(), c_q.end(), [](Octagon<int>& X){X.Printout(std::cout);});

     0 0     2 0     4 0     4 2     4 4     2 4     0 4     0 2
0 0     1 1     2 2     3 3     4 4     5 5     6 6     7 7
1 1     2 2     3 3     4 4     5 5     6 6     7 7     8 8

    //containers::queue<Octagon<int>>::forward_iterator it = q.begin();
    //Octagon<int> test_unit = *it;
    //++it;
    //++it;
    q.insert_by_number(3, test1);
    std::for_each(q.begin(), q.end(), [](Octagon<int>& X){X.Printout(std::cout);});
    std::cout << std::endl;
    q.delete_by_number(3);
    std::for_each(q.begin(), q.end(), [](Octagon<int>& X){X.Printout(std::cout);});
    int N;
    std::cin >> N;
    std::cout << std::count_if(q.begin(), q.end(), [=](Octagon<int>& X){return X.Area() < N;});
    return 0;*/
    size_t N;
    float S;
    char option = '0';
    containers::queue<Octagon<int>> q;
    Octagon<int> oct{};
    while (option != 'q') {
        std::cout << "choose option (m for man, q to quit)" << std::endl;
        std:: cin >> option;
        switch (option) {
            case 'q':
                break;
            case 'm':
                std::cout << "1) push new element into queue\n"
                << "2) insert element into chosen position\n"
                << "3) pop element from the queue\n"
                << "4) delete element from the chosen position\n"
                << "5) print queue\n"
                << "6) count elements with area less then chosen value\n" << std::endl;
                break;
            case '1': {
                std::cout << "enter octagon (have to enter dots consequently): " << std::endl;
                oct = Octagon<int>(std::cin);
                q.push(oct);
                break;
            }
            case '2': {
                std::cout << "enter position to insert to: ";
                std::cin >> N;
                oct = Octagon<int>(std::cin);
                std::cout << "enter octagon: ";
                q.insert_by_number(N, oct);
                break;
            }
            case '3': {
                q.pop();
                break;
            }
            case '4': {
                std::cout << "enter position to delete: ";
                std::cin >> N;
                q.delete_by_number(N);
                break;
            }
            case '5': {
                std::for_each(q.begin(), q.end(), [](Octagon<int> &X) { X.Printout(std::cout); });
                break;
            }
            case '6': {
                std::cout << "enter max area to search to: ";
                std::cin >> S;
                std::cout <<"number of elements with value less than " << S << "is " << std::count_if(q.begin(), q.end(), [=](Octagon<int>& X){return X.Area() < S;}) << std::endl;
                break;
            }
            default:
                std::cout << "no such option. Try m for man" << std::endl;
                break;
        }

    }

}