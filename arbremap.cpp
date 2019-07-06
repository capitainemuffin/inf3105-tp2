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


void ArbreMap::inserer (double cle, double valeur){
	
	inserer(cle, valeur, this->racine);

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
