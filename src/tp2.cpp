#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define OUTPUT_FILE "tp2.ps"

typedef struct
{
    int abs;
    int ord;
} coord;

/**
 * Exercice 1
 */
void pointrandom(int n, coord *point)
{
    for (int i = 0; i < n; i++) {
        point[i].abs = rand() % 612;
        point[i].ord = rand() % 792;
    }
}

/**
 * Exercice 2
 */
void distances(int n, coord *point, int **edge)
{
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            edge[k][0] = i;
            edge[k][1] = j;
            edge[k][2] = std::pow(point[i].abs - point[j].abs, 2)
                + std::pow(point[i].ord - point[j].ord, 2);
            k++;
        }
    }
}

/**
 * Exercice 3
 */
void tri(int m, int **edge)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (edge[i][2] > edge[j][2]) {
                continue;
            }

            std::swap(edge[i][0], edge[j][0]);
            std::swap(edge[i][1], edge[j][1]);
            std::swap(edge[i][2], edge[j][2]);
        }
    }
}

/**
 * Exercice 4
 *
 * Avec implémentation naïve d'une structure Union-Find (à l'arache complet).
 */
typedef struct uf
{
    struct uf *parent;
} uf;

uf *uf_find(uf *x)
{
    if (x->parent == nullptr) {
        return x;
    }

    return uf_find(x->parent);
}

void uf_union(uf *x, uf *y)
{
    uf *xroot = uf_find(x);
    uf *yroot = uf_find(y);

    if (xroot != yroot) {
        xroot->parent = yroot;
    }
}

void kruskal(int n, int m, int **edge, int **arbre)
{
    uf *set = new uf[n];

    for (int i = 0; i < n; i++) {
        set[i].parent = nullptr;
    }

    int cntArbre = 0;

    for (int i = 0; i < m; i++) {
        int x = edge[i][0];
        int y = edge[i][1];

        if (uf_find(&set[x]) != uf_find(&set[y])) {
            arbre[cntArbre][0] = x;
            arbre[cntArbre][1] = y;
            cntArbre++;

            uf_union(&set[x], &set[y]);
        }
    }
}

/**
 * Exercice 5
 */
void affichageGraphique(int n, int m, coord *point, int **edge, int **arbre)
{
    std::ofstream output;
    output.open(OUTPUT_FILE, std::ios::out);
    output << "%!PS-Adobe-3.0" << std::endl;
    output << "%%BoundingBox: 0 0 612 792" << std::endl;
    output << std::endl;

    for (int i = 0; i < n; i++) {
        output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" << std::endl;
        output << "0 setgray" << std::endl;
        output << "fill" << std::endl;
        output << "stroke"<< std::endl;
        output << std::endl;
    }

    output << std::endl;

    for (int i = 0; i < n - 1; i++) {
        output << point[arbre[i][0]].abs << " " << point[arbre[i][0]].ord
               << " moveto" << std::endl;
        output << point[arbre[i][1]].abs << " " << point[arbre[i][1]].ord
               << " lineto" << std::endl;
        output << "stroke" << std::endl;
        output << std::endl;
    }

    output << "showpage";
    output << std::endl;

    output.close();
}

/**
 * Exercice 6.2
 */
void _fusion(int n, int m, int **N, int **M, int **S)
{
    if (n == 0 && m == 0) {
        return;
    }

    if (n == 0) {
        for (int i = 0; i < m; i++) {
            S[i][0] = M[i][0];
            S[i][1] = M[i][1];
            S[i][2] = M[i][2];
        }

        return;
    }

    if (m == 0) {
        for (int i = 0; i < n; i++) {
            S[i][0] = N[i][0];
            S[i][1] = N[i][1];
            S[i][2] = N[i][2];
        }

        return;
    }

    if (N[n - 1][2] >= M[m - 1][2]) {
        S[n + m - 1][0] = N[n - 1][0];
        S[n + m - 1][1] = N[n - 1][1];
        S[n + m - 1][2] = N[n - 1][2];

        _fusion(n - 1, m, N, M, S);
    } else {
        S[n + m - 1][0] = M[m - 1][0];
        S[n + m - 1][1] = M[m - 1][1];
        S[n + m - 1][2] = M[m - 1][2];

        _fusion(n, m - 1, N, M, S);
    }
}

void triFusion(int m, int **edge)
{
    if (m <= 1) {
        return;
    }

    int a = m / 2;
    int b = m - a;

    int **edge1 = new int*[a];
    int **edge2 = new int*[b];

    for (int i = 0; i < a; i++) {
        edge1[i] = new int[3];
        edge1[i][0] = edge[i][0];
        edge1[i][1] = edge[i][1];
        edge1[i][2] = edge[i][2];
    }

    for (int i = 0; i < b; i++) {
        edge2[i] = new int[3];
        edge2[i][0] = edge[a + i][0];
        edge2[i][1] = edge[a + i][1];
        edge2[i][2] = edge[a + i][2];
    }

    triFusion(a, edge1);
    triFusion(b, edge2);

    _fusion(a, b, edge1, edge2, edge);

    for (int i = 0; i < a; i++) {
        delete edge1[i];
    }
    delete[] edge1;

    for (int i = 0; i < b; i++) {
        delete edge2[i];
    }
    delete[] edge2;
}

int main()
{
    srand(time(NULL));

    int n;

    std::cout << "Entrer le nombre de points: ";
    std::cin >> n;

    int m = n * (n - 1) / 2;

    coord *point = new coord[n];
    int **edge = new int*[m];
    for (int i = 0; i < m; i++) {
        edge[i] = new int[3];
    }
    int **arbre = new int*[n - 1];
    for (int i = 0; i < n - 1; i++) {
        arbre[i] = new int[2];
    }

    pointrandom(n, point);
    distances(n, point, edge);
    /* tri(m, edge); */
    triFusion(m, edge);
    kruskal(n, m, edge, arbre);
    affichageGraphique(n, m, point, edge, arbre);

    delete[] point;
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
