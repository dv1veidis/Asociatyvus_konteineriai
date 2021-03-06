#include "My_lib.h"
 
using namespace std;

struct elements{

string zodis;
int kiekis;
vector<int> eilutes;
};

bool compare (elements A,elements B) { return (A.kiekis>B.kiekis);}

string check (string word){
    //regex url("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    string urlCheck;
    string wwwCheck;
    if(!word.empty()){
        for(int i=1; i<word.length()-1;i++){
            if(word[i]=='.' && isalnum(word[0])){
                if(word[word.length()-1]=='/'|| isalnum(word[word.length()-1])){
                    return "This is a link";
                    break;
                } 
            }
        }
        
    }

    int skaicius;
    if(!word.empty() ){
        word.erase(remove(word.begin(), word.end(), '.'), word.end());
        word.erase(remove(word.begin(), word.end(), '!'), word.end());
        word.erase(remove(word.begin(), word.end(), ','), word.end());
        word.erase(remove(word.begin(), word.end(), '?'), word.end());
        word.erase(remove(word.begin(), word.end(), '('), word.end());
        word.erase(remove(word.begin(), word.end(), ')'), word.end()); 
        word.erase(remove(word.begin(), word.end(), ':'), word.end());
        word.erase(remove(word.begin(), word.end(), ';'), word.end());
        word.erase(remove(word.begin(), word.end(), '-'), word.end());
        word.erase(remove(word.begin(), word.end(), '"'), word.end());
    }
    
    if(!word.empty()) {
        if( (word[0] >= 'A' && word[0] <= 'Z')){
            word[0]=tolower(word[0]);
    }
    }

    
    if(!word.empty() && !(std::isdigit(word[0]))){
        return word;
    }
     
    else {
        return "";
    }
    
}

void ivedimas ( map<string , vector<int>> &unikalus, vector<elements> &elementai, string failas){

    map<string, vector<int>>::iterator it;
    elements elementas;
    int eilute=0;
    string zodis, eil;
    stringstream my_buffer;
    ifstream openf;
    openf.open(failas);
    while(!openf){
        cout<<failas<<" nerastas"<<endl;
        cout<<"Iveskite egzistuojanti faila(formatu 'pavyzdys.txt')"<<endl;
        cin>>failas;
        openf.open(failas);
    }
    my_buffer<<openf.rdbuf();
    openf.close();
    while(getline(my_buffer, eil)){
        eilute++;
        istringstream is(eil);
        while(is>>zodis){
            if(check(zodis)=="This is a link"){
                cout<<zodis<<endl;
            }
            else if(check(zodis)!=""){
                auto value = unikalus.insert(make_pair(check(zodis), 0));      
                  it =  unikalus.find(check(zodis));
                  unikalus[it->first].push_back(eilute);
            } 
        } 
    }
    for(auto words: unikalus){
        if(words.second.size()>1){
        elementas.zodis=words.first;
        elementas.kiekis=words.second.size();
        elementas.eilutes=words.second;
        elementai.push_back(elementas);
        } 
    //fd<<words.first<<" "<<words.second<<endl;
    }
    sort(elementai.begin(), elementai.end(), compare);

}

void isvedimas (vector<elements> elementai){
ofstream fd ("rezultatai.txt");
for(int i=0; i<elementai.size(); i++){
        fd<<"Zodis -'"<<elementai[i].zodis<<"' pasikartoja "<<elementai[i].kiekis;
        if(elementai[i].kiekis%10==0 || (elementai[i].kiekis>10 && elementai[i].kiekis<20)){
        fd<<" kartu, eilutes, kuriose pasirodo zodis: ";
        }
        else if((elementai[i].kiekis-1)%10==0){
        fd<<" karta, eilutes, kuriose pasirodo zodis: ";
        }
        else{
        fd<<" kartus, eilutes, kuriose pasirodo zodis: ";
        }
        for(int j=0; j<elementai[i].eilutes.size(); j++){
            if(elementai[i].eilutes[j]!=elementai[i].eilutes[j-1])
                fd<<" "<<elementai[i].eilutes[j];
        }
        fd<<"\n";
    }
    fd.close();
}
 
int main()
{
    setlocale(LC_ALL, "Lithuanian");
    vector<elements> elementai;
    map<string , vector<int> > unikalus;
    string failas;
    cout<<"Is kokio failo norite traukti teksta?(del geriausio rezultato naudokite lietuviska rasvedybos faila)"<<endl;
    cout<<"Iveskite formatu 'pavyzdys.txt'"<<endl;
    cin>>failas;
    auto start = std::chrono::high_resolution_clock::now(); auto st=start;
    ivedimas(unikalus, elementai, failas);
    isvedimas(elementai);
    std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now()-start; // Skirtumas (s)
    cout <<"Programos trukmes laikas: "<<diff2.count() << " s\n";
    


   return 0;
}