#include "arbremap.h"
#include <iostream>
#include <iomanip>
#include <utility>

std::ostream& operator << (std::ostream& os, ArbreMap& arbre){
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

				arbre.inserer(cle, valeur);
	
			} else {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);

			}

	return is;

}

int main (){

	ArbreMap arbre = ArbreMap();

	while(std::cin){

		char test;
		std::cin >> test >> std::ws;

		switch (test){

			case '(' : {

				std::cin >> arbre >> std::ws;
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

				std::cin >> o >> n >> n2 >> e >> valeur >> question;

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

			case 'q' : {

				char point;
				std::cin >> point;

				if(!std::cin.fail() && point == '.') {

					exit(0);

				} else {

					std::cerr << "Commande non reconnue." << std::endl;
					exit(-1);

				}
			}

			default : {

				std::cerr << "Commande non reconnue." << std::endl;
				exit(-1);
			}


		} 


	}
		
	return 0;
}