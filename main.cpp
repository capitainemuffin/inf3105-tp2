#include "arbremap.h"
#include <iostream>
#include <iomanip>
#include <utility>

std::ostream& operator << (std::ostream& os, ArbreMap& arbre){
	return os;
}

std::istream& operator >> (std::istream& is, ArbreMap& arbre){

	double cle, valeur;
	char vir, parentheseD, point;
	is >> cle >> vir >> valeur >> parentheseD >> point;

			if(!is.fail()
				&& vir == ','
				&& parentheseD == ')'
				&& point == '.'){

				std::cout << "cle et valeur : " << cle << valeur << std::endl;
				arbre.inserer(cle, valeur);
	
			} else {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);

			}

	return is;

}

int main (){

	ArbreMap arbre = ArbreMap();

	char test;
	std::cin >> test;

	switch (test){

		case '(' : {

			std::cin >> arbre;
			break;
		}

		case 'm' : {

			char a, x, question;
			std::cin >> a >> x >> question;

			if(!std::cin.fail()
				&& a == 'a'
				&& x == 'x'
				&& question == '?') {

				std::cout << arbre.maxima() << std::endl;

			} else {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);

			}

			break;
		}

		case 'd' : {

			char o, n, n2, e, question;
			double valeur;

			std::cin >> o, n, n, e, valeur, question;

			if(!std::cin.fail()
				&& o == 'o' 
				&& n == 'n' 
				&& n2 == 'n' 
				&& e == 'e' 
				&& question == '?') {

				std::cout << arbre.maxima(valeur) << std::endl; 

			} else {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);

			}

			break;

		}

		case 'a' : {

			char v, a, n, t, question;
			double valeur;

			std::cin >> v >> a >> n >> t >> valeur >> question;

			if(!std::cin.fail()
				&& v == 'v'
				&& a == 'a'
				&& n == 'n'
				&& t == 't'
				&& question == '?') {

			} else {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);

			}

			break;

		}

		default : {

			std::cerr << "Commande non reconnue." << std::endl;
			exit(-1);
		}


	} 
	

	for(int i = 30; i > 0; i--) {

		arbre.inserer(i, i/2.0);
	}

	ArbreMap::Iterateur iter = arbre.debut();

	for(int i = 0; i < 30; i++) {

		std::cout << "(" << std::get<0>(arbre[iter]) << ",";
		std::cout << std::get<1>(arbre[iter]) << ")" << std::endl;
		++iter;

	}

	return 0;
}