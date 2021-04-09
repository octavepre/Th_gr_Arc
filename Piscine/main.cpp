#include <iostream>
#include "Graphe.h"
#include "Sommet.h"


void menu(Graphe& ski)
{
    int menu=0;
    do
    {
        system("cls");
        std::cout << "SUPER TRAVELLER 3000"<<std::endl;
        std::cout << "Vous aide a vous trouvez le meilleur chemin selon VOTRE niveau" << std::endl;
        std::cout << "0. Afficher toute les stations" <<std::endl;
        std::cout << "1. Chercher l'itineraire le plus rapide" <<std::endl;
        std::cout << "2. Chercher l'itineraire le plus court" <<std::endl;
        std::cout << "3. Vos chemin prefere" <<std::endl;
        std::cout << "4. Creer profile" << std::endl;
        std::cout << "5. Quitter" <<std::endl;
        do
        {
            std::cin >> menu;
        }
        while(menu < 0 || menu > 5);

        switch (menu)
        {
        case 0:
        {
            system("cls");
            ski.afficher();
            system("pause");
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
            }
            while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
            system("cls");
            ski.setPoidDescente(DEFAULT);
            ski.Dijkstra(depart-1,arriver-1,0);
            std::cout<<std::endl<<"0. Quitter"<<std::endl;
            int shee;
            do
            {
                std::cin >> shee;
            }
            while(shee != 0);
            break;
        }
        case 2:
        {
            int depart=0,arriver=0;
            do
            {
                system("cls");
                std::cout << "Dans quel station etes vous ?" << std::endl;
                std::cin >> depart;
            }
            while(depart < 1 || depart > 37);
            system("cls");
            ski.BFS(depart-1);
            std::cout<<std::endl<<"0. Quitter"<<std::endl;
            int shee;
            do
            {
                std::cin >> shee;
            }
            while(shee != 0);
            break;
        }
        case 3:
        {
            ski.setUtiliserToFalse();
            system("cls");
            ski.setPoidDescente (1);
            system("cls");
            int depart=0,arriver=0;
            if(ski.getUtiliser() == true)
            {
                do
                {
                    system("cls");
                    std::cout << "Dans quel station etes vous ?" << std::endl;
                    std::cin >> depart;
                    std::cout << "Dans quel station souhaitez vous vous rendre ?" << std::endl;
                    std::cin >> arriver;
                }
                while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
                system("cls");
                //std::cout << "SHEEEEEE";
                ski.Dijkstra(depart-1,arriver-1,1);
                std::cout<<std::endl<<"0. Quitter"<<std::endl;
                int shee;
                do
                {
                    std::cin >> shee;
                }
                while(shee != 0);
            }
            else if(ski.getUtiliser() == false)
            {
                std::cout << "Il n'existe pas de compte a ce nom." << std::endl;
                system("pause");
            }
            break;
        }
        case 4:
        {
            ski.setPoidDescente (2);
            break;
        }
        case 5:
        {
            system("cls");
            std::cout << "SHEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
            break;
        }
        }
    }
    while(menu != 5);
}


int main()
{
    Graphe ski("data_arcs.txt");
    menu(ski);
    return 0;
}
