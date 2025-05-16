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

void vns(vector<int>&ordem,int total,int atual, const vector<vector<pair<int, int>>>& tarefas, int n_maq){
    if(total==atual){
        return;
    }
    int rand_iter=rand_int(0,30);
    for(int i=0;i<rand_iter;i++){
        int v1 = rand_int(0, ordem.size() - 1);
        int v2 = rand_int(0, ordem.size() - 1);
        swap(ordem[v1],ordem[v2]);
    }
}

vector<int> grasp(double alfa, vector<vector<pair<int, int>>>& tarefas) {
    vector<int> solucao;
    multimap<int, int> candidato;
    vector<int> etapas(tarefas.size(), 0);
    vector<int> x(tarefas.size(), 0);

    for (int i = 0; i < tarefas.size(); i++) {
        candidato.insert({0, i});
    }

    while (!candidato.empty()) {
        int min_val = candidato.begin()->first;
        int max_val = candidato.rbegin()->first;
        double limite = min_val + (max_val - min_val) * alfa;
        auto it_limite = candidato.upper_bound((int)limite);
        int pos = distance(candidato.begin(), it_limite);

        if (pos == 0) {
            it_limite = candidato.begin();  // fallback seguro
        } else {
            int escolha = rand_int(0, pos - 1);
            it_limite = candidato.begin();
            advance(it_limite, escolha);
        }

        int tarefa_id = it_limite->second;
        int etapa = etapas[tarefa_id];
        int dur = tarefas[tarefa_id][etapa].second;

        int novo_inicio = max(it_limite->first, x[tarefa_id]) + dur;
        x[tarefa_id] = novo_inicio;
        etapas[tarefa_id]++;
        solucao.push_back(tarefa_id);

        candidato.erase(it_limite);

        if (etapas[tarefa_id] < tarefas[tarefa_id].size()) {
            candidato.insert({novo_inicio, tarefa_id});
        }
    }

    return solucao;
}

int local_search(double alfa,vector<vector<pair<int,int>>>&tarefas,int qtd,int n_maq){
    vector<int>resposta=grasp(alfa,tarefas);
    int vr=calcular_makespan(resposta,tarefas,n_maq);
    for(int i=1;i<qtd;i++){
        vector<int>atual=grasp(alfa,tarefas);
        int itera=10;
        vector<int>mod=atual;
        vns(mod,itera,0,tarefas,n_maq);
        int va=calcular_makespan(atual,tarefas,n_maq);
        int vm=calcular_makespan(mod,tarefas,n_maq);
        if(vr>va){
            resposta=atual;
            vr=va;
        }
        if(vr>vm){
            resposta=mod;
            vr=vm;
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