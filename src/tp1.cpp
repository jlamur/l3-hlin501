/**
 * @author Jules Lamur <contact@juleslamur.fr>
 */

#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * Exercice 1
 */
void grapherandom(int n, int m, int edge[][2])
{
    for (int i = 0; i < m; i++) {
        edge[i][0] = rand() % n;
        edge[i][1] = rand() % n;
    }
}

/**
 * Exercice 2
 */
void composantes(int n, int m, int edge[][2], int comp[])
{
    for (int i = 0; i < n; i++) {
        comp[i] = i;
    }

    for (int i = 0; i < m; i++) {
        if (comp[edge[i][0]] == comp[edge[i][1]]) {
            continue;
        }

        int x = comp[edge[i][0]];
        for (int j = 0; j < n; j++) {
            if (comp[j] == x) {
                comp[j] = comp[edge[i][1]];
            }
        }
    }
}

/**
 * Exercice 3
 */
void ecrituretailles(int n, int m, int comp[])
{
    int taille[n];
    int orderedtaille[n + 1];

    for (int i = 0; i < n; i++) {
        taille[i] = 0;
        orderedtaille[i] = 0;
    }
    orderedtaille[n] = 0;

    for (int i = 0; i < n; i++) {
        taille[comp[i]]++;
    }

    for (int i = 0; i < n; i++) {
        if (taille[i] == 0) {
            continue;
        }

        orderedtaille[taille[i]]++;
    }

    for (int i = 1; i < n + 1; i++) {
        if (orderedtaille[i] == 0) {
            continue;
        }

        std::cout << "Il y a " << orderedtaille[i]
           << " composantes de taille " << i << "." << std::endl;
    }
}

int main()
{
    int n;
    int m;

    std::cout << "Entrer le nombre de sommets:";
    std::cin >> n;
    std::cout << "Entrer le nombre d'aretes:";
    std::cin >> m;

    int edge[m][2];
    int comp[n];

    grapherandom(n, m, edge);
    composantes(n, m, edge, comp);
    ecrituretailles(n, m, comp);

    return EXIT_SUCCESS;
}
