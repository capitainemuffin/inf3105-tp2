/**
 * Déclaration et implémentation d'une pile.
 *
 * AUTEUR(S):
 *  1) SELS28049204
 */

#if !defined(__PILE__H__)
#define __PILE__H__

#include <cstdlib>
#include <assert.h>

template<class T>
class Pile {
public:

    Pile();

    ~Pile();

    void empiler(const T &);

    T depiler();

    bool vide() const { return sommet == NULL; }

    void vider();

    const Pile<T> &operator=(const Pile<T> &);

private:

    class Cellule {
    public:
        Cellule(const T &e, Cellule *c);

        T contenu;
        Cellule *suivante;
    };

    Cellule *sommet;
};

template<class T>
Pile<T>::Pile() {
    sommet = NULL;
}

template<class T>
Pile<T>::~Pile() {
    vider();
}

template<class T>
void Pile<T>::vider() {
    while (!vide())
        depiler();
}

template<class T>
Pile<T>::Cellule::Cellule(const T &e, Cellule *c)
        : suivante(c) {
    contenu = e;
}

template<class T>
void Pile<T>::empiler(const T &e) {
    sommet = new Cellule(e, sommet);
    assert(sommet);
}

template<class T>
T Pile<T>::depiler() {
    assert(sommet);
    Cellule c(*sommet);
    delete sommet;
    sommet = c.suivante;
    return c.contenu;
}

template<class T>
const Pile<T> &Pile<T>::operator=(const Pile<T> &autre) {
    if (&autre == this) return *this;

    Cellule **t = &sommet;
    Cellule *a = autre.sommet;
    while (a) {
        if ((*t) == NULL)
            *t = new Cellule(a->contenu, NULL);
        else
            (*t)->contenu = a->contenu;
        t = &((*t)->suivante);
        a = a->suivante;
    }
    a = *t;
    *t = NULL;
    while (a != NULL) {
        Cellule *temp = a->suivante;
        delete a;
        a = temp;
    }

    return *this;
}

#endif

