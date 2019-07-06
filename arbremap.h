/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes

   AUTEUR:
    1) Sofiane Selaoui SELS28049204
*/

#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__
#include "pile.h"
#include <cassert>
#include <utility>
#include <vector>
class ArbreMap {

public:

    //constructeurs

    ArbreMap();
    ArbreMap(const ArbreMap&);
    ~ArbreMap();

    //méthodes

    void inserer(double, double);
    double maxima() const;
    double maxima(double) const;
    std::vector<std::pair<double, double> > jusqua(double) const;
    double aGauche(double);
    void appartient(double) const;

    //surcharge d'opérateurs

    const double operator[] (const double) const;
    double operator[] (const double);

    //méthodes avec Iterateur

    class Iterateur;
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur recherche(double) const;
    Iterateur egalOuSuivant(double) const;
    Iterateur egalOuPrecedent(double) const;

    class Noeud {

    public:

        Noeud(double, double);
        double cle;
        double valeur;
        double a;
        int equilibre;
        Noeud *gauche, *droite;

    };


    Noeud* racine;

    bool inserer(double, double, Noeud*& noeud);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    void vider(Noeud*&);

    class Iterateur {

    public:

        Iterateur(const ArbreMap&);
        Iterateur(const Iterateur&);
        Iterateur(const Iterateur&, Noeud*);

        operator bool() const;
        bool operator !() const;
        bool operator == (const Iterateur&) const;
        bool operator != (const Iterateur&) const;

    private:

        const ArbreMap& arbre_associe;
        Pile<Noeud*> chemin;
        Noeud* courant;

        friend class ArbreMap;

    };

};

#endif

