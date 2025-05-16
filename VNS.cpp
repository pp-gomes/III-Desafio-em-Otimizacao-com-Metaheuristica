#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand_int(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

double rand_real(double a, double b) {
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

void caminho(vector<int>&ord,int total,const vector<vector<pair<int, int>>>& tarefas,int n_trab){
    set<int>s;
    set<int>::iterator it;
    for(int i=0;i<total;i++){
        s.insert(i);
    }
    for(int i=0;i<n_trab;i++){
        for(int j=0;j<tarefas[i].size();j++){
            int valor=rand_int(0,total-1);
            auto it = s.begin();
            advance(it, valor);
            ord[*it]=i;
            it=s.erase(it);
            total--;
        }    
    }
    return;
}

int calcular_makespan(const vector<int>& ordem, const vector<vector<pair<int, int>>>& tarefas, int n_maq) {
    vector<int> tempo_maquina(n_maq, 0), tempo_tarefa(tarefas.size(), 0);
    vector<int> etapas(tarefas.size(), 0);
    int finalizado = 0;

    while (finalizado < tarefas.size()) {
        for (int idx : ordem) {
            if (etapas[idx] >= tarefas[idx].size()) continue;
            int maq = tarefas[idx][etapas[idx]].first;
            int dur = tarefas[idx][etapas[idx]].second;
            tempo_maquina[maq] = max(tempo_maquina[maq], tempo_tarefa[idx]) + dur;
            tempo_tarefa[idx] = tempo_maquina[maq];
            etapas[idx]++;
            if (etapas[idx] == tarefas[idx].size()) finalizado++;
        }
    }

    return *max_element(tempo_maquina.begin(), tempo_maquina.end());
}

void vns(vector<int>&ordem,int total,int atual,int &mi, const vector<vector<pair<int, int>>>& tarefas, int n_maq){
    if(total==atual){
        return;
    }
    int rand_iter=rand_int(0,30);
    for(int i=0;i<rand_iter;i++){
        int v1=rand_int(0,ordem.size()-1),v2=rand_int(0,ordem.size()-1);
        swap(ordem[v1],ordem[v2]);
    }
    mi=min(calcular_makespan(ordem,tarefas,n_maq),mi);
    vns(ordem,total,atual+1,mi,tarefas,n_maq);
}

int main(){
    //vns
    int n_trab,n_maq;
    cin>>n_trab>>n_maq;
    vector<vector<pair<int,int>>>tarefas(n_trab);
    cin.ignore();
    int k=0;
    for (int  i=0;i<n_trab;i++){
        string g;
        getline(cin,g);
        stringstream ss(g);
        int maq,tempo;
        while(ss>>maq>>tempo){
            tarefas[i].emplace_back(maq, tempo);
            k++;
        }
        //cout<<k<<endl;
    }
    int itera=300;
    vector<int>ordem(k,-1);
    caminho(ordem,k,tarefas,n_trab);
    for(int i=0;i<ordem.size();i++){
        cout<<ordem[i]<<" ";
    }cout<<endl;
    int mi=calcular_makespan(ordem,tarefas,n_maq);
    //cout<<mi<<endl;
    vns(ordem,itera,0,mi,tarefas,n_maq);
    cout<<mi<<endl;
}