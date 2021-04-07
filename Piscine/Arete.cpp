#include "Sommet.h"

Arete::Arete(int num,std::string nomTrajet,std::string type,Sommet* numero1,Sommet* numero2)
    :m_num(num),m_trajet(nomTrajet),m_type(type),m_utiliser(false)
{
    m_lien = std::make_pair(numero1,numero2);
}

void Arete::afficherA()
{

}

///Pas besoin de type descente
void Arete::calculPoid(int typeDescente)///A diviser par 100 le poid
{
    ///rajouter SURF
    if (m_type == "V")///Verte
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(5*60);///300s = 5 mn
    }
    else if (m_type == "B") ///Bleue
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(4*60);///300s = 4 mn
    }
    else if (m_type == "R")  ///Rouge
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(3*60);///3mn = 180s
    }
    else if (m_type == "N")  ///Noir
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(2*60);///2mn = 120s
    }
    else if (m_type == "KL") ///Kilometre lancé
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*10;///10 second pour descendre 100m
    }
    else if (m_type == "TPH") ///Telephérique
    {
        m_poid = 4*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(2*60);
    }
    else if (m_type == "TC") ///Telecabine
    {
        m_poid = 2*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(3*60);
    }
    else if (m_type == "TSD")///Telesiege debrayable
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(3*60);
    }
    else if (m_type == "TS") ///Telesiege
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(4*60);
    }
    else if (m_type == "TK") ///Teleski
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(4*60);
    }
    else if (m_type == "BUS") ///Bus
    {
        //std::cout << "{" << m_lien.first->getNum() << "}";
        if((m_lien.first->getNom() == "arc1600" && m_lien.second->getNom()=="arc2000")||(m_lien.second->getNom() == "arc1600" && m_lien.first->getNom()=="arc2000"))
        {
            m_poid = 40*60*100;
        }
        else if((m_lien.first->getNom() == "arc1600" && m_lien.second->getNom()=="arc1800")||(m_lien.second->getNom() == "arc1600" && m_lien.first->getNom()=="arc1800"))
        {
            m_poid = 30*60*100;
        }
    }
    else if (m_type == "SURF")
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(10*60);
    }
}

void Arete::calculPoid2(int P)///A diviser par 100 le
{
    if(m_type == "V" || m_type == "B" || m_type == "R" || m_type == "N" || m_type == "KL" || m_type == "SURF")
    {

        switch(P)
        {
        case 1:
        {
            m_poid = 10000000;
            break;
        }
        case 2:
        {
            m_poid = 20;
            break;
        }
        case 3:
        {
            m_poid = 5;
            break;
        }
        case 4:
        {
            m_poid = 3;
            break;
        }
        case 5:
        {
            m_poid = 0;
            break;
        }
        }
    }
    if(m_type == "TPH" || m_type == "TC" || m_type == "TSD" || m_type == "TSD" || m_type == "TS" || m_type == "TK" || m_type == "BUS")
    {
        switch(P)
        {
        case 1:
        {
            m_poid = 10000000;
            break;
        }
        case 2:
        {
            m_poid = 20*1.5;
            break;
        }
        case 3:
        {
            m_poid = 5*1.5;
            break;
        }
        case 4:
        {
            m_poid = 3*1.5;
            break;
        }
        case 5:
        {
            m_poid = 0 + 2;
            break;
        }
        }
    }
}


