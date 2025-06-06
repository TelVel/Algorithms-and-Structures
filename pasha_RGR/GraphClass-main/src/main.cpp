#include "menu/menu.h"

SimpleGraph<int, string, int> *Graph = nullptr;
using namespace std;

int main() {
    int command = -1;
    
    while (command != 13) {
        cout << "\n\t=== МЕНЮ РАБОТЫ С ГРАФОМ ===\n\n"
             << "Выберите действие:\n"
             << " 1) Меню заполнения графа\n"
             << " 2) Получить количество вершин\n"
             << " 3) Получить количество рёбер\n"
             << " 4) Проверить ориентированность графа\n"
             << " 5) Проверить тип представления графа\n"
             << " 6) Получить коэффициент насыщенности\n"
             << " 7) Преобразовать в матричный граф\n"
             << " 8) Преобразовать в списковый граф\n"
             << " 9) Вывести граф на экран\n"
             << "10) Меню итераторов\n"
             << "11) Найти цикл заданной величины, включающий заданную вершину\n"
             << "12) Кратчайшие пути Беллмана-Форда\n"
             << "13) Выход\n\n"
             << "Ваш выбор: ";
               
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (command) {
            case 1:
                printFillMenu();
                break;
            case 2:
                if (Graph)
                    cout << Graph->getV() << endl;
                else
                    cout << "0\n";
                break;
            case 3:
                if (Graph)
                    cout << Graph->getE() << endl;
                else
                    cout << "0\n";
                break;
            case 4:
                if (Graph)
                    cout << "Граф " << (Graph->isDirected() ? "ориентированный" : "неориентированный") << endl;
                else
                    cout << "0\n";
                break;
            case 5:
                if (Graph)
                    cout << "Граф представлен в виде " << (Graph->isDense() ? "матрицы" : "списка") << endl;
                else
                    cout << "0\n";
                break;
            case 6:
                if (Graph)
                    cout << Graph->getK() << endl;
                else
                    cout << "0\n";
                break;
            case 7:
                if (Graph) {
                    Graph->toMatrixGraph();
                    cout << "1" << endl;
                }
                else
                    cout << "0\n";
                break;
            case 8:
                if (Graph) {
                    Graph->toListGraph();
                    cout << "1" << endl;
                }
                else
                    cout << "0\n";
                break;
            case 9:
                if (Graph)
                    Graph->printGraph();
                else
                    cout << "0\n";
                break;
            case 10:
                if (Graph)
                    iteratorsMenu();
                else
                    cout << "0\n";
                break;
            case 11:
                if (Graph)
                    task2Menu();
                else
                    cout << "0\n";
                break;
            case 12:
                if (Graph)
                    task3Menu();
                else
                    cout << "0\n";
                break;
            default:
                break;
        }
    }
    return 0;
}