#include "menu.h"

extern SimpleGraph<int, string, int> *graph;

void printFillMenu() {
    int command = -1;
    int vCount, eCount, weight;
    bool dir, den;
    Vertex<int, string> v1, v2;
    Edge<int, string, int> *e;
    int v1Ind, v2Ind;
    string vertexName;
    
    while (command != 9) {
        cout << "\n=== МЕНЮ ЗАПОЛНЕНИЯ ГРАФА ===\n\n";
        cout <<  "Выберите действие:\n";
        cout <<  "0) Создать пустой граф\n";
        cout <<  "1) Создать граф с вершинами без ребер\n";
        cout <<  "2) Заполнить случайными значениями\n";
        cout <<  "3) Вставить вершину\n";
        cout <<  "4) Вставить вершину с указанием имени\n";
        cout <<  "5) Удалить вершину\n";
        cout <<  "6) Вставить ребро (без веса)\n";
        cout <<  "7) Вставить ребро с указанием веса\n";
        cout <<  "8) Удалить ребро\n";
        cout <<  "9) Вернуться в главное меню\n\n";
               
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        
        switch (command) {
            case 0:
                if (graph) {
                    cout << "0\n";
                } else {
                    graph = new SimpleGraph<int, string, int>();
                    cout << "1\n";
                }
                break;
            case 1:
                if (graph) {
                    cout << "0\n";
                } else {
                    cin >> vCount;
                    cout << "1 - ориент, 0 - неориент: ";
                    cin >> dir;
                    cout << "1 - матрица, 0 - список: ";
                    cin >> den;
                    graph = new SimpleGraph<int, string, int>(vCount, dir, den);
                    cout << "1\n";
                }
            break;
            case 2:
                if (graph) {
                    cout << "0\n";
                } else {
                    cin >> vCount;
                    cin >> eCount;
                    cout << "1 - ориент, 0 - неориент: ";
                    cin >> dir;
                    cout << "1 - матрица, 0 - список: ";
                    cin >> den;
                    graph = new SimpleGraph<int, string, int>(vCount, eCount, dir, den);
                    cout << "1\n";
                }
                break;
                
            case 3:
                if (graph) {
                    graph->insertV();
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
                break;
                
            case 4:
                if (graph) {
                    cin >> vertexName;
                    graph->insertV(vertexName);
                    cout << "1\n" ;
                } else {
                    cout << "0\n";
                }
                break;
                
            case 5:
                if (graph) {
                    cin >> v1Ind;
                    v1.setInd(v1Ind);
                    graph->deleteV(&v1);
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
                break;
                
            case 6:
            if (graph) {
                cin >> v1Ind;
                cin >> v2Ind;
                v1.setInd(v1Ind);
                v2.setInd(v2Ind);
                graph->insertE(&v1, &v2);
                cout << "1\n";
            } else {
                cout << "0\n";
            }
                break;
                
            case 7:
                if (graph) {
                    cin >> v1Ind;
                    cin >> v2Ind;
                    cin >> weight;
                    if (v1Ind >= 0 && v1Ind < graph->getV() && 
                        v2Ind >= 0 && v2Ind < graph->getV()) {
                        v1.setInd(v1Ind);
                        v2.setInd(v2Ind);
                        graph->insertE(&v1, &v2, weight);
                        cout << weight;
                    } else {
                        cout << "0\n";
                    }
                } else {
                    cout << "0\n";
                }
                break;
                
            case 8:
            if (graph) {
                cin >> v1Ind;
                cin >> v2Ind;
                
                if (v1Ind >= 0 && v1Ind < graph->getV() && v2Ind >= 0 && v2Ind < graph->getV()) {
                    Edge<int, string, int>* edge = graph->getEdge(v1Ind, v2Ind);
                    if (edge) {
                        if (graph->deleteE(edge)) {
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
        printf("Выберите действие:\n"
               "1) Итератор вершин.\n"
               "2) Итератор ребер.\n"
               "3) Итератор исходящих ребер.\n"
               "4) Вернуться в меню.\n");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
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
                if (!(v < 0 || v >= graph->getV()))
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
    VertexIterator<int, string, int> iter = VertexIterator<int, string, int>(vertexVector, -1);
    VertexIterator<int, string, int> end = VertexIterator<int, string, int>(vertexVector, -1);

    while (command != 5) {
        printf("Выберите действие:\n"
               "1) Установить итератор в начало графа\n"
               "2) Переместить итератор вперед (++)\n"
               "3) Получить текущий элемент\n"
               "4) Вывести все ключи\n"
               "5) Вернуться в главное меню\n");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        switch (command) {
            case 1:
                iter = graph->vBegin();
                cout << "1\n";
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
                    std::cout << *iter << std::endl;
                } else {
                    std::cout << "0\n";
                }
                break;
            case 4:
                for (auto it = graph->vBegin(); it != graph->vEnd(); it++) {
                    std::cout << *it << " ";
                }
                std::cout << std::endl;
                break;
            default:
                break;
        }
    }
}

    void edgeIteratorMenu() {
        int command = -1;
        EdgeIterator<int, string, int> iter = EdgeIterator<int, string, int>(nullptr, -1);
        EdgeIterator<int, string, int> end = EdgeIterator<int, string, int>(nullptr, -1);

        while (command != 4) {
            printf("Выберите действие:\n"
                "1) Установить итератор в начало графа\n"
                "2) Переместить итератор вперед (++)\n"
                "3) Получить текущий элемент\n"
                "4) Вернуться в главное меню\n");
            if (scanf("%d", &command) != 1) {
                while (getchar() != '\n') {}
            }
            switch (command) {
                case 1:
                    iter = graph->eBegin();
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
    EdgeIterator<int, string, int> iter = EdgeIterator<int, string, int>(nullptr, -1);
    EdgeIterator<int, string, int> end = EdgeIterator<int, string, int>(nullptr, -1);

    while (command != 5) {
        printf("Выберите действие:\n"
               "1) Установить итератор в начало графа\n"
               "2) Переместить итератор вперед (++)\n"
               "3) Получить текущий элемент\n"
               "4) Вывести все ключи\n"
               "5) Вернуться в главное меню\n");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        switch (command) {
            case 1:
                iter = graph->adjEBegin(v);
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
                    std::cout << (*iter)->getData() << std::endl;
                } else {
                    std::cout << "0" << std::endl;
                }
                break;
            case 4:
                for (auto it = graph->adjEBegin(v); it != graph->adjEEnd(v); it++) {
                    std::cout << (*it)->getData() << " ";
                }
                std::cout << std::endl;
                break;
            default:
                break;
        }
    }
}

void task2Menu() {
    if (!graph) {
        cout << "0\n";
        return;
    }
    int length, start;
    cin >> length;
    cin >> start;

    try {
        CycleFinder<int, string> finder(graph, length, start);
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
    if (!graph) {
        cout << "Graph is not initialized" << endl;
        return;
    }

    Task3<int, string, int> task3(graph);
    try {
        auto allPaths = task3.getAllPaths();
        cout << "\nShortest paths between all vertices:" << endl;
        cout << "--------------------------------" << endl;
        
        for (int i = 0; i < graph->getV(); i++) {
            for (int j = 0; j < graph->getV(); j++) {
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
