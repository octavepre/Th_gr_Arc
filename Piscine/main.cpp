#include <iostream>
#include "Graphe.h"
#include "Sommet.h"


void menu(Graphe& ski)
{
    int menu=0;
    std::cout << "SUPER TRAVELLER 3000"<<std::endl;
    std::cout << "Vous aide a vous trouvez le meilleur chemin selon VOTRE niveau" << std::endl;
    std::cout << "0. Afficher toute les stations" <<std::endl;
    std::cout << "1. Chercher un itineraire" <<std::endl;
    std::cout << "2. Determiner un chemin adapter a votre niveau" <<std::endl;
    std::cout << "3. Sheeeeeeeeeeee" <<std::endl;
    do
    {
        std::cin >> menu;
    }while(menu < 0 || menu > 4);
    //std::cout << "lol";

    switch (menu)
    {
    case 0:
        {
            system("cls");
            ski.afficher();
            break;
        }
    case 1:
        {
            int depart=0,arriver=0;
            do
            {
                system("cls");
                std::cout << "Dans quel station etes vous ?" << std::endl;
                std::cin >> depart;
                std::cout << "Dans quel station souhaitez vous vous rendre ?" << std::endl;
                std::cin >> arriver;
            }while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
            system("cls");
            ski.Dijkstra(depart-1,arriver-1);
            break;
        }
    case 2:
        {
            system("cls");
            std::cout << "Veuillez repondre a ce questionniare." << std::endl;
            //std::cout << std::endl << "Appuyer sur une touche pour continuer...";
            system("pause");
            ski.setPoidDescente (1);
            //system("cls");
            int depart=0,arriver=0;
            do
            {
                system("cls");
                std::cout << "Dans quel station etes vous ?" << std::endl;
                std::cin >> depart;
                std::cout << "Dans quel station souhaitez vous vous rendre ?" << std::endl;
                std::cin >> arriver;
            }while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
            system("cls");
            ski.Dijkstra(depart-1,arriver-1);
            break;
        }
    case 3:
        {
            system("cls");
            std::cout << "SHEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
            break;
        }
    }
}


int main()
{
    Graphe ski("data_arcs.txt");
    //ski.afficher();
    menu(ski);
    return 0;
}
