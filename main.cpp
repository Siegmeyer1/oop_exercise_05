#include <iostream>
#include <algorithm>
#include "octagon.h"
#include "containers/queue.h"

int main() {
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
                std::cout << "enter octagon: ";
                oct = Octagon<int>(std::cin);
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
                std::cout <<"number of elements with value less than " << S << " is " << std::count_if(q.begin(), q.end(), [=](Octagon<int>& X){return X.Area() < S;}) << std::endl;
                break;
            }
            default:
                std::cout << "no such option. Try m for man" << std::endl;
                break;
        }
    }
    return 0;
}