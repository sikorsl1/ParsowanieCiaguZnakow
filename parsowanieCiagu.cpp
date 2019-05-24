#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Wezel{
    int litera;
    bool czyKoncowy;
};

int main()
{
    cout << "Podaj ciag wejsciowy: ";//poieranie ciagu znakow
    string wejscie;
    cin >> wejscie;
    char *wejscieZnaki;
    wejscieZnaki = (char*) malloc(sizeof(char)*wejscie.length());
    strcpy(wejscieZnaki,wejscie.c_str());

    vector <string> Slownik{};//tworzenie slownika
    int iloscSlow;
    cout << "\nPodaj ilosc slow: ";
    cin >> iloscSlow;
    cout << "\nPodaj slowa: ";
    string tmp;
    for(int i=0;i<iloscSlow;i++){
        cin >> tmp;
        Slownik.push_back(tmp);
    }

    int *Start; //stan poczatkowy - inicjacja i zdefiniowanie
    Start = (int*) malloc(sizeof(int)*iloscSlow);
    Start[0] = 0;
    for(int i=1;i<iloscSlow;i++){
        Start[i]=Start[i-1]+Slownik[i-1].length();
    }

    vector <Wezel> Wezly{};//implementacja wezlow grafu
    Wezel wezelTmp = {'a',0};
    for(int k=0;k<iloscSlow;k++){
        for(int i=0;i<Slownik[k].length()-1;i++){
            wezelTmp.czyKoncowy = 0;
            wezelTmp.litera = Slownik[k][i];
            Wezly.push_back(wezelTmp);
        }
        wezelTmp.czyKoncowy = 1;
        wezelTmp.litera = Slownik[k][Slownik[k].length()-1];
        Wezly.push_back(wezelTmp);
    }


    vector <int> stany{};//przetrzymuje aktualne stany
    vector <string> hipotezy{};//przetrzymuje hipotezy wystapienia slow

    cout << "\nSlowa, ktore pojawily sie w ciagu znakow: ";
    for(int i=0;i<wejscie.length();i++){
        for(int j=0;j<stany.size();j++){
            if(Wezly[stany[j]+1].litera == wejscie[i]){
                stany[j]++;
                if(Wezly[stany[j]].czyKoncowy==1){
                    cout << hipotezy[j] << " ";
                    stany.erase(stany.begin()+j);
                    hipotezy.erase(hipotezy.begin()+j);
                    j--;
                }
            }else{
                stany.erase(stany.begin()+j);
                hipotezy.erase(hipotezy.begin()+j);
                j--;
            }
        }
        for(int j=0;j<iloscSlow;j++){
            if(Wezly[Start[j]].litera == wejscie[i]){
                stany.push_back(Start[j]);
                hipotezy.push_back(Slownik[j]);
            }
        }
    }

    return 0;
}
