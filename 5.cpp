#include <iostream>
#include <vector>
using namespace std;

void generation(vector <int>& mod, int X0, int A, int B, int C, int& repeat){

    int Xi; 
    bool firstAppear = false;   

    for (int i=0; i<C; i++){
        Xi = (A*mod[i] + B) % C;
        mod.push_back(Xi);
        if (X0==Xi && mod.size()>1 && firstAppear==false){
            repeat = i+2; // +2 потому что в индекс с нуля и прибавляется знач только на след итерации
            firstAppear = true;
        }
    }
}

int main () {
    vector <int> mod;
    int repeat;
    int X0, A, B, C;

    cout << "Enter x0, A, B, C" << endl; 
    cin >> X0 >> A >> B >> C;

    if (!(0<=A && A<=C) || (!(0<=B && B<=C)) || (!(0<=X0 && X0 < C))){
        cout << "error";
        return -1;
    }
    mod.push_back(X0);

    generation(mod,X0, A, B, C, repeat);

    for (int n : mod){
        cout << n << " ";
    }

    cout << endl;
    cout << repeat;
}
