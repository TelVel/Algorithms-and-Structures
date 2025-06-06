#include "menu/menu.h"

SimpleGraph<int, string, int> *graph = nullptr;
using namespace std;

int main() {
    int command = -1;
    
    while (command != 13) {
        printf("\n\t=== МЕНЮ РАБОТЫ С ГРАФОМ ===\n\n"
               "Выберите действие:\n"
               " 1) Меню заполнения графа\n"
               " 2) Получить количество вершин\n"
               " 3) Получить количество рёбер\n"
               " 4) Проверить ориентированность графа\n"
               " 5) Проверить тип представления графа\n"
               " 6) Получить коэффициент насыщенности\n"
               " 7) Преобразовать в матричный граф\n"
               " 8) Преобразовать в списковый граф\n"
               " 9) Вывести граф на экран\n"
               "10) Меню итераторов\n"
               "11) Найти цикл заданной величины, включающий заданную вершину\n"
               "12) Кратчайшие пути Беллмана-Форда\n"
               "13) Выход\n\n"
               "Ваш выбор: ");
               
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        
        switch (command) {
            case 1:
                printFillMenu();
                break;
            case 2:
                if (graph)
                    cout << graph->getV() << endl;
                else
                    cout << "0\n";
                break;
            case 3:
                if (graph)
                    cout << graph->getE() << endl;
                else
                    cout << "0\n";
                break;
            case 4:
                if (graph)
                    cout << "Граф " << (graph->isDirected() ? "ориентированный" : "неориентированный") << endl;
                else
                    cout << "0\n";
                break;
            case 5:
                if (graph)
                    cout << "Граф представлен в виде " << (graph->isDense() ? "матрицы" : "списка") << endl;
                else
                    cout << "0\n";
                break;
            case 6:
                if (graph)
                    cout << graph->getK() << endl;
                else
                    cout << "0\n";
                break;
            case 7:
                if (graph) {
                    graph->toMatrixGraph();
                    cout << "1" << endl;
                }
                else
                    cout << "0\n";
                break;
            case 8:
                if (graph) {
                    graph->toListGraph();
                    cout << "1" << endl;
                }
                else
                    cout << "0\n";
                break;
            case 9:
                if (graph)
                    graph->printGraph();
                else
                    cout << "0\n";
                break;
            case 10:
                if (graph)
                    iteratorsMenu();
                else
                    cout << "0\n";
                break;
            case 11:
                if (graph)
                    task2Menu();
                else
                    cout << "0\n";
                break;
            case 12:
                if (graph)
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