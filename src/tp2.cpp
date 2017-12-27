#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

typedef struct
{
    int abs;
    int ord;
} coord;

int main()
{
    int n;

    std::cout << "Entrer le nombre de points: ";
    std::cin >> n;

    int m = n * (n - 1) / 2;

    coord *points = new coord[n];
    int **edge = new int*[m];
    for (int i = 0; i < m; i++) {
        edge[i] = new int[3];
    }
    int **arbre = new int*[n - 1];
    for (int i = 0; i < n - 1; i++) {
        arbre[i] = new int[2];
    }

    delete[] points;
    for (int i = 0; i < m; i++) {
        delete[] edge[i];
    }
    delete[] edge;
    for (int i = 0; i < n - 1; i++) {
        delete[] arbre[i];
    }
    delete[] arbre;

    return 0;
}
