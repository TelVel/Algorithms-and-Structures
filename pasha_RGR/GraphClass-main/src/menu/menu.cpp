#include "menu.h"

extern SimpleGraph<int, string, int> *Graph;

void printFillMenu() {
    int command = -1;
    int vCount, eCount, weight;
    bool dir, den;
    Vertex<int, string> v1, v2;
    Edge<int, string, int> *e;
    int v1Ind, v2Ind;
    string vertexName;
    
    while (command != 9) {
        cout << "\n=== МЕНЮ ЗАПОЛНЕНИЯ ГРАФА ===\n\n"
             << "Выберите действие:\n"
             << "0) Создать пустой граф\n"
             << "1) Создать граф с вершинами без ребер\n"
             << "2) Заполнить случайными значениями\n"
             << "3) Вставить вершину\n"
             << "4) Вставить вершину с указанием имени\n"
             << "5) Удалить вершину\n"
             << "6) Вставить ребро (без веса)\n"
             << "7) Вставить ребро с указанием веса\n"
             << "8) Удалить ребро\n"
             << "9) Вернуться в главное меню\n\n";
               
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (command) {
            case 0:
                if (Graph) {
                    cout << "0\n";
                } else {
                    Graph = new SimpleGraph<int, string, int>();
                    cout << "1\n";
                }
                break;
            case 1:
                if (Graph) {
                    cout << "0\n";
                } else {
                    cin >> vCount;
                    cout << "1 - ориент, 0 - неориент: ";
                    cin >> dir;
                    cout << "1 - матрица, 0 - список: ";
                    cin >> den;
                    Graph = new SimpleGraph<int, string, int>(vCount, dir, den);
                    cout << "1\n";
                }
            break;
            case 2:
                if (Graph) {
                    cout << "0\n";
                } else {
                    cin >> vCount;
                    cin >> eCount;
                    cout << "1 - ориент, 0 - неориент: ";
                    cin >> dir;
                    cout << "1 - матрица, 0 - список: ";
                    cin >> den;
                    Graph = new SimpleGraph<int, string, int>(vCount, eCount, dir, den);
                    cout << "1\n";
                }
                break;
                
            case 3:
                if (Graph) {
                    Graph->insertV();
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
                break;
                
            case 4:
                if (Graph) {
                    cin >> vertexName;
                    Graph->insertV(vertexName);
                    cout << "1\n" ;
                } else {
                    cout << "0\n";
                }
                break;
                
            case 5:
                if (Graph) {
                    cin >> v1Ind;
                    v1.setInd(v1Ind);
                    Graph->deleteV(&v1);
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
                break;
                
            case 6:
            if (Graph) {
                cin >> v1Ind;
                cin >> v2Ind;
                v1.setInd(v1Ind);
                v2.setInd(v2Ind);
                Graph->insertE(&v1, &v2);
                cout << "1\n";
            } else {
                cout << "0\n";
            }
                break;
                
            case 7:
                if (Graph) {
                    cin >> v1Ind;
                    cin >> v2Ind;
                    cin >> weight;
                    if (v1Ind >= 0 && v1Ind < Graph->getV() && 
                        v2Ind >= 0 && v2Ind < Graph->getV()) {
                        v1.setInd(v1Ind);
                        v2.setInd(v2Ind);
                        Graph->insertE(&v1, &v2, weight);
                        cout << weight;
                    } else {
                        cout << "0\n";
                    }
                } else {
                    cout << "0\n";
                }
                break;
                
            case 8:
            if (Graph) {
                cin >> v1Ind;
                cin >> v2Ind;
                
                if (v1Ind >= 0 && v1Ind < Graph->getV() && v2Ind >= 0 && v2Ind < Graph->getV()) {
                    Edge<int, string, int>* edge = Graph->getEdge(v1Ind, v2Ind);
                    if (edge) {
                        if (Graph->deleteE(edge)) {
                            cout << "1\n";
                        } else {
                            cout << "0\n";
                        }
                    } else {
                        cout << "0\n";
                    }
                } else {
                    cout << "0\n";
                }
            } else {
                cout << "0\n";
            }
                
            default:
                break;
        }
    }
}

void iteratorsMenu() {
    int command = -1;
    while (command != 4) {
        cout << "Выберите действие:\n"
             << "1) Итератор вершин.\n"
             << "2) Итератор ребер.\n"
             << "3) Итератор исходящих ребер.\n"
             << "4) Вернуться в меню.\n";
             
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (command) {
            case 1:
                vertexIteratorMenu();
                return;
            case 2:
                edgeIteratorMenu();
                break;
            case 3:
                int v;
                cin >> v;
                if (!(v < 0 || v >= Graph->getV()))
                    inputEdgeIteratorMenu(v);
                break;
            default:
                break;
        }
    }
}

void vertexIteratorMenu() {
    int command = -1;
    vector<Vertex<int, string> *> vertexVector;
    typename SimpleGraph<int, string, int>::VertexIterator iter(vertexVector, -1);
    typename SimpleGraph<int, string, int>::VertexIterator end(vertexVector, -1);

    while (command != 5) {
        cout << "Выберите действие:\n"
             << "1) Установить итератор в начало графа\n"
             << "2) Переместить итератор вперед (++)\n"
             << "3) Получить текущий элемент\n"
             << "4) Вывести все ключи\n"
             << "5) Вернуться в главное меню\n";
             
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (command) {
            case 1:
                iter = Graph->vBegin();
                cout << "1\n";
                break;
            case 2:
                if (iter != end) {
                    iter++;
                    if (iter == end) {
                        cout << "0" << endl;
                    }
                } else {
                    cout << "0" << endl;
                }
                break;
            case 3:
                if (iter != end) {
                    cout << *iter << endl;
                } else {
                    cout << "0" << endl;
                }
                break;
            case 4:
                {
                    auto it = Graph->vBegin();
                    auto endIt = Graph->vEnd();
                    if (it == endIt) {
                        cout << "0" << endl;
                    } else {
                        while (it != endIt) {
                            cout << *it << " ";
                            ++it;
                        }
                        cout << endl;
                    }
                }
                break;
            default:
                break;
        }
    }
}

void edgeIteratorMenu() {
    int command = -1;
    typename SimpleGraph<int, string, int>::EdgeIterator iter(nullptr, -1);
    typename SimpleGraph<int, string, int>::EdgeIterator end(nullptr, -1);

    while (command != 4) {
        cout << "Выберите действие:\n"
             << "1) Установить итератор в начало графа\n"
             << "2) Переместить итератор вперед (++)\n"
             << "3) Получить текущий элемент\n"
             << "4) Вернуться в главное меню\n";
             
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (command) {
            case 1:
                iter = Graph->eBegin();
                break;
            case 2:
                if (iter != end) {
                    iter++;
                } else {
                    std::cout << "0" << std::endl;
                }
                break;
            case 3:
                if (iter != end) {
                    Edge<int, string, int>* edge = *iter;
                    std::cout << edge->getV1()->getInd() << std::endl;
                    std::cout << edge->getV2()->getInd() << std::endl;
                } else {
                    std::cout << "0" << std::endl;
                }
                break;
            default:
                break;
        }
    }
}

void inputEdgeIteratorMenu(int v) {
    int command = -1;
    typename SimpleGraph<int, string, int>::EdgeIterator iter(nullptr, -1);
    typename SimpleGraph<int, string, int>::EdgeIterator end(nullptr, -1);

    while (command != 5) {
        cout << "Выберите действие:\n"
             << "1) Установить итератор в начало графа\n"
             << "2) Переместить итератор вперед (++)\n"
             << "3) Получить текущий элемент\n"
             << "4) Вывести все ключи\n"
             << "5) Вернуться в главное меню\n";
             
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (command) {
            case 1:
                iter = Graph->adjEBegin(v);
                break;
            case 2:
                if (iter != end) {
                    iter++;
                } else {
                    std::cout << "0" << std::endl;
                }
                break;
            case 3:
                if (iter != end) {
                    std::cout << (*iter)->getV1()->getInd() << std::endl;
                    std::cout << (*iter)->getV2()->getInd() << std::endl;
                } else {
                    std::cout << "0" << std::endl;
                }
                break;
            case 4:
                for (auto it = Graph->adjEBegin(v); it != Graph->adjEEnd(v); it++) {
                    std::cout << (*it)->getV1()->getInd() << "," << (*it)->getV2()->getInd() << "; ";
                }
                std::cout << std::endl;
                break;
            default:
                break;
        }
    }
}

void task2Menu() {
    if (!Graph) {
        cout << "0\n";
        return;
    }
    int length, start;
    cin >> length;
    cin >> start;

    try {
        CycleFinder<int, string> finder(Graph, length, start);
        auto cycles = finder.result();
        if (cycles.empty()) {
            cout << "Циклы длины " << length << " из вершины " << start << " не найдены\n";
        } else {
            cout << "Найдено циклов: " << cycles.size() << endl;
            for (const auto& cycle : cycles) {
                for (int v : cycle) {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
    } catch (const std::exception& e) {
        cout << "Exception " << e.what() << endl;
    }
}

void task3Menu() {
    if (!Graph) {
        cout << "Graph is not initialized" << endl;
        return;
    }

    Task3<int, string, int> task3(Graph);
    try {
        auto allPaths = task3.getAllPaths();
        cout << "\nShortest paths between all vertices:" << endl;
        cout << "--------------------------------" << endl;
        
        for (int i = 0; i < Graph->getV(); i++) {
            for (int j = 0; j < Graph->getV(); j++) {
                if (i != j && allPaths[i][j].distance != numeric_limits<int>::max()) {
                    cout << "Path from " << i << " to " << j << ":" << endl;
                    cout << "Distance: " << allPaths[i][j].distance << endl;
                    cout << "Path: ";
                    for (size_t k = 0; k < allPaths[i][j].path.size(); k++) {
                        cout << allPaths[i][j].path[k];
                        if (k < allPaths[i][j].path.size() - 1) {
                            cout << " -> ";
                        }
                    }
                    cout << "\n--------------------------------" << endl;
                }
            }
        }
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}
