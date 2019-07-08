#include "arbremap.h"

ArbreMap::Noeud::Noeud(double cle, double valeur) : 
cle(cle), 
valeur(valeur),
a(valeur),
equilibre(0),
gauche(NULL),
droite(NULL) {}

ArbreMap::ArbreMap():
racine(NULL){};

ArbreMap::~ArbreMap(){
	vider(this->racine);
}

ArbreMap::ArbreMap(const ArbreMap& autre){
	copier(autre.racine, this->racine);
}

void ArbreMap::miseAjourMaxima(Noeud*& racine){

	if(racine->gauche) miseAjourMaxima(racine->gauche);
	if(racine->droite) miseAjourMaxima(racine->droite);

	if(racine->gauche && racine->gauche->valeur > racine->valeur) {

		racine->a = racine->gauche->a;

	}

	if(racine->droite && racine->droite->valeur > racine->valeur){

		racine->a = racine->droite->a;
	}

}

double aGauche(double cle){

	return cle;
}

double ArbreMap::maxima() const{

	assert(this->racine);
	return this->racine->a;

}

double ArbreMap::maxima (double cle) const {

	assert(this->racine);

	Iterateur iter = this->recherche(cle);

	assert(iter.courant);

	return std::get<2>(*this[iter]);

}

std::string ArbreMap::appartient(double cle) const {

	std::string reponse;

	Iterateur iter = this->recherche(cle);

	if(iter.courant) {

		reponse = "vrai";

	} else {
		reponse = "faux";
	}

	return reponse;

}


void ArbreMap::inserer (double cle, double valeur){
	
	inserer(cle, valeur, this->racine);
	miseAjourMaxima(this->racine);

}

bool ArbreMap::inserer (double cle, double valeur, Noeud*& noeud){

	bool augmente = false;
	
	if(!noeud) {

		noeud = new Noeud(cle, valeur);
		augmente = true;

	} else if (cle < noeud->cle){

		if(inserer(cle, valeur, noeud->gauche)){

			noeud->equilibre++;

			if(noeud->equilibre == 1){

				augmente = true;

			} else if(noeud->equilibre == 2){

				if(noeud->gauche->equilibre == -1) rotationDroiteGauche(noeud->gauche);
				rotationGaucheDroite(noeud);

			} else {

				assert(noeud->equilibre == 0);
			}

		}

	} else if(cle > noeud->cle){

		if(inserer(cle, valeur, noeud->droite)){

			noeud->equilibre--;

			if(noeud->equilibre == -1) {

				augmente = true;

			} else if(noeud->equilibre == -2) {

				if (noeud->droite->equilibre == 1) rotationGaucheDroite(noeud->droite);

				rotationDroiteGauche(noeud);

			} else {

				assert(noeud->equilibre == 0);
			}

		}

	} else {

		noeud->valeur = valeur;

	}

	return augmente;

}

void ArbreMap::rotationGaucheDroite(Noeud*& racine){

	Noeud* tmp = racine->gauche;

	int equilibreA = tmp->equilibre;
	int equilibreB = racine->equilibre;
	int nouveauEquilibreB = - (equilibreA > 0 ? equilibreA : 0) - 1 + equilibreB;
	int nouveauEquilibreA = (nouveauEquilibreB < 0 ? nouveauEquilibreB : 0) - 1 + equilibreA;

	tmp->equilibre = nouveauEquilibreA;
    racine->equilibre = nouveauEquilibreB;
    racine->gauche = tmp->droite;
    tmp->droite = racine;
    racine = tmp;
	
}

void ArbreMap::rotationDroiteGauche(Noeud*& racine){
	
	Noeud* tmp = racine->droite;

    int equilibreB = tmp->equilibre;
    int equilibreA = racine->equilibre;
    int nouveauEquilibreA = -(equilibreB < 0 ? equilibreB : 0) + 1 + equilibreA;
    int nouveauEquilibreB = (nouveauEquilibreA > 0 ? nouveauEquilibreA : 0) + 1 + equilibreB;

    tmp->equilibre = nouveauEquilibreB;
    racine->equilibre = nouveauEquilibreA;
    racine->droite = tmp->gauche;
    tmp->gauche = racine;
    racine = tmp;
}

void ArbreMap::copier(const Noeud* source, Noeud*& noeud) const
{

	if(source != NULL){
		noeud = new Noeud(source->cle, source->valeur);
    	noeud->equilibre = source->equilibre;
    	copier(source->gauche, noeud->gauche);
    	copier(source->droite, noeud->droite);
	}
    
}

void ArbreMap::vider(Noeud*& noeud){

	if (noeud != NULL) {

		if(noeud->gauche != NULL) vider (noeud->gauche);
		if(noeud->droite != NULL) vider (noeud->droite);
		noeud = NULL;
		delete noeud;
	}


}

/*
* Méthodes en lien avec l'itérateur
*/
ArbreMap::Iterateur ArbreMap::debut() const{

	Iterateur iter(*this);

	Noeud* tmp = this->racine;

	if(tmp){

		while(tmp->gauche){

		iter.chemin.empiler(tmp);
		tmp = tmp->gauche;

		} 

	}


	iter.courant = tmp;

	return iter;
}

ArbreMap::Iterateur ArbreMap::recherche(double e) const
{
    Iterateur iter(*this);
    
    Noeud* tmp = this->racine;

    while(tmp){

        if(e < tmp->cle){

            iter.chemin.empiler(tmp);
            tmp = tmp->gauche;

        } else if(e > tmp->cle){

            tmp = tmp->droite;

        } else {

            iter.courant = tmp;
            break;
        }
    }

    if (iter.courant == NULL) iter.chemin.vider(); 

    return iter;
}

std::tuple<double, double, double> ArbreMap::operator[] (const ArbreMap::Iterateur& iter) const{

	assert(this->racine && iter.courant);
	return std::make_tuple(iter.courant->cle, iter.courant->valeur, iter.courant->a);
}


/*
* Constructeur et méthodes pour l'Itérateur 
*/

ArbreMap::Iterateur::Iterateur(const ArbreMap& arbre):
arbre_associe(arbre),
courant(NULL){}

/**
* Pré-increment
*/
ArbreMap::Iterateur& ArbreMap::Iterateur::operator++(){

	assert(courant);

    if(!this->chemin.vide()){

        this->courant = this->chemin.depiler();

        Noeud* tmp = this->courant->droite;
        if(tmp != NULL){

            this->chemin.empiler(tmp);
            tmp = tmp->gauche;

            while (tmp != NULL){

                this->chemin.empiler(tmp);
                tmp = tmp->gauche;

            }

        }        

    } else {

        this->courant = NULL;

    }

    return *this;

}