
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<chrono>
#include<vector>
using namespace std;

map<string, int> Affichier_Mot_NbOccurence(const string& nomfich)
{
    ifstream fichier(nomfich);
    map<string, int> MotsOcc;
    string mot;
    if (!fichier.is_open()) 
    {
        cerr << "Impossible d'ouvrir le fichier." << std::endl;
        exit(1);
    }
    while (fichier >> mot) 
    {
        MotsOcc[mot]++;
    }
    fichier.close();
    return MotsOcc;
}

map<string,vector<int>> Stocker_Mot_PosLigne(const string nomfich)
{
    map<string,vector<int>> lignesParMot;
    string ligne;
    int numeroLigne = 1;
    char mot[50];
    int j=0;
    ifstream fichier(nomfich);
    if (!fichier.is_open()) 
    {
        cerr << "Impossible d'ouvrir le fichier." << std::endl;
        exit(1);
    }
    while(getline(fichier, ligne)) 
    {
        for(int i=0;i<ligne.size();i++)
        {
            if(isalnum(ligne[i]))
            {
                mot[j++]=ligne[i];
            }
            else 
            {
                if(j!=0)
                {
                    mot[j]='\0';
                    j=0;
                    lignesParMot[mot].push_back(numeroLigne);
                }
            }
        }
        ++numeroLigne;
        j=0;
    }
    
    return lignesParMot;
}

void afficherLignesParMot(const map<string, vector<int>> lignesParMot) {
    for (const auto& var : lignesParMot) 
    {
        cout << "Le mot : ----" << var.first << " ----apparait dans les lignes :";
        for (int numeroLigne : var.second) {
            cout << " " << numeroLigne;
        }
        cout << endl;
    }
}


int main()
{
    cout<<"/****** COMPTER LE NOMBRE DES MOTS DANS LE ROMAN ET LE NOMBRE D OCCURENCE DE CHAQUE MOT : ********/"<<endl;
    map<string, int> MotsOcc;
    int nbmot=0;
    auto start = chrono::high_resolution_clock::now();
    MotsOcc = Affichier_Mot_NbOccurence("rouge_et_noir.txt");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    for (const auto& var : MotsOcc) {
        // cout<< var.first << " : " << var.second << " fois" <<endl;
        nbmot+=var.second;
    }
    cout<<"LE FICHIER CONTIENT "<<nbmot<< "mot(s)"<<endl;
    cout << "Temps d'execution juste de la lecture du fichier et stockage des mots (l affichage n est pas inclus) : " << duration.count() << " milliseconds" <<endl;
    
    cout<<"/****** STOCKER CHAQUE MOT AVEC LES LIGNES OU IL SE TROUVE :  ********/"<<endl;

    auto start2 = chrono::high_resolution_clock::now();
    map<string,vector<int>> res=Stocker_Mot_PosLigne("rouge_et_noir.txt");
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
    cout << "Temps d'execution : " << duration2.count() << " milliseconds" <<endl;
    // afficherLignesParMot(res);
    return 0;
}
