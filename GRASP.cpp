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

vector<int> grasp(double alfa,vector<vector<pair<int,int>>>&tarefas){
    vector<int>solucao;
    multimap<int,int>candidato;
    vector<int>etapas(tarefas.size(), 0);
    vector<int>x;
    for(int i=0;i<tarefas.size();i++){
        candidato.insert({0,i});
        x.push_back(0);
    }
    while(candidato.size()>0){
        int min_val = candidato.begin()->first;
        int max_val = candidato.rbegin()->first;
        double limite = min_val + (max_val - min_val) * alfa;
        auto it = candidato.upper_bound((int)limite);
        int pos = distance(candidato.begin(), it);
        int escolha=rand_int(0,pos-1);
        it=candidato.begin();
        advance(it, escolha);
        candidato.erase(it);
        solucao.push_back(it->second);
        int dur = tarefas[it->second][etapas[it->second]].second;
        pair<int,int>p={it->first,it->second};
        p.first=max(p.first,x[it->second])+dur;
        x[it->second]=p.first;
        etapas[it->second]++;
        if(etapas[it->second]<tarefas[it->second].size()){
            candidato.insert(p);
        }
    }
    return solucao;
}

int local_search(double alfa,vector<vector<pair<int,int>>>&tarefas,int qtd,int n_maq){
    vector<int>resposta=grasp(alfa,tarefas);
    int vr=calcular_makespan(resposta,tarefas,n_maq);
    for(int i=1;i<qtd;i++){
        vector<int>atual=grasp(alfa,tarefas);
        int va=calcular_makespan(atual,tarefas,n_maq);
        if(vr>va){
            resposta=atual;
            vr=va;
        }
    }
    return vr;
}

int main(){
    int n_trab,n_maq;
    cin>>n_trab>>n_maq;
    double alfa=1;
    int qtd=10000;
    vector<vector<pair<int,int>>>tarefas(n_trab);
    cin.ignore();
    for (int  i=0;i<n_trab;i++){
        string g;
        getline(cin,g);
        stringstream ss(g);
        int maq,tempo;
        while(ss>>maq>>tempo){
            tarefas[i].emplace_back(maq, tempo);
        }
    }
    cout<<local_search(alfa,tarefas,qtd,n_maq)<<endl;
}