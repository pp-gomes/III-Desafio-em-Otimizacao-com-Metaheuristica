#include <bits/stdc++.h>
#include <math.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

double euler=2.71828182846;
double pi=3.14159265359;
int rand_int(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

double rand_real(double a, double b) {
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

int calcular_makespan(const vector<int>& ordem, const vector<vector<pair<int, int>>>& tarefas, int n_maq) {
    vector<int> tempo_maquina(n_maq, 0), tempo_tarefa(tarefas.size(), 0);
    vector<int> etapas(tarefas.size(), 0);
    int finalizado = 0;
    int makespan = 0;

    while (finalizado < tarefas.size()) {
        for (int idx : ordem) {
            if (etapas[idx] >= tarefas[idx].size()) continue;
            int maq = tarefas[idx][etapas[idx]].first;
            int dur = tarefas[idx][etapas[idx]].second;
            tempo_maquina[maq] = max(tempo_maquina[maq], tempo_tarefa[idx]) + dur;
            tempo_tarefa[idx] = tempo_maquina[maq];
            etapas[idx]++;
            if (etapas[idx] == tarefas[idx].size()) finalizado++;
            makespan = max(makespan, tempo_maquina[maq]); // incremental
        }
    }
    return makespan;
}

void criar_solucao(const vector<vector<pair<int, int>>>& tarefas, int k, vector<int>& resultado) {
    vector<int> etapas_restantes(tarefas.size());
    vector<int> candidatos;

    for (int i = 0; i < tarefas.size(); i++) {
        etapas_restantes[i] = tarefas[i].size();
        candidatos.push_back(i);
    }

    resultado.clear();
    for (int i = 0; i < k; i++) {
        int pos = rand_int(0, candidatos.size() - 1);
        int escolhido = candidatos[pos];
        resultado.push_back(escolhido);
        etapas_restantes[escolhido]--;
        if (etapas_restantes[escolhido] == 0)
            candidatos.erase(candidatos.begin() + pos);
    }
}

void mov_linear(vector<int>&resultado,vector<int>&atual,vector<vector<pair<int, int>>>&tarefas,double a,vector<int>&valor,vector<int>&candidatos,int i){
    double pa=atual[i];
    double pm=resultado[i];
    double r=rand_real(0.0,1.0);
    double A=2*a*r-a;
    double C=2*r;
    double D=abs(C*pm-pa);
    int xn = ((int)(abs(pm - A * D) + 0.5)) % tarefas.size();
    if(valor[xn]>0){
        atual[i]=xn;
        valor[xn]--;
        if(valor[xn]==0){
            auto it = find(candidatos.begin(), candidatos.end(), xn);
            if (it != candidatos.end()) {
                candidatos.erase(it);
            }     
        }
    }
    else{
        int pos = rand_int(0, candidatos.size() - 1);
        int escolhido = candidatos[pos];
        atual[i] = escolhido;
        valor[escolhido]--;
        if (valor[escolhido] == 0)
            candidatos.erase(candidatos.begin() + pos);
    }
}

void mov_espiral(vector<int>&resultado,vector<int>&atual,vector<vector<pair<int, int>>>&tarefas,double a,vector<int>&valor,vector<int>&candidatos,int i){
    double pm=resultado[i];
    double pa=atual[i];
    double D=abs(pm-pa);
    double const espiral=1;
    double r=rand_real(-1.0,1.0);
    int xn=((int)abs(D*pow(euler,r*espiral)*cos(2*pi*r)+pm))% tarefas.size();
    if(valor[xn]>0){
        atual[i]=xn;
        valor[xn]--;
        if(valor[xn]==0){
            auto it = find(candidatos.begin(), candidatos.end(), xn);
            if (it != candidatos.end()) {
                candidatos.erase(it);
            }     
        }
    }
    else{
        int pos = rand_int(0, candidatos.size() - 1);
        int escolhido = candidatos[pos];
        atual[i] = escolhido;
        valor[escolhido]--;
        if (valor[escolhido] == 0)
            candidatos.erase(candidatos.begin() + pos);
    }
}

int main() {
    int n_maq, n_trab, itera = 100000;
    cin >> n_trab >> n_maq;
    cin.ignore();
    int k=0;
    vector<vector<pair<int, int>>> tarefas(n_trab);
    for (int i = 0; i < n_trab; i++) {
        string linha;
        getline(cin, linha);
        stringstream ss(linha);
        int maq, tempo;
        while (ss >> maq >> tempo){
            tarefas[i].emplace_back(maq, tempo);
            k++;
        }
    }
    vector<int>resultado;
    criar_solucao(tarefas,k,resultado);
    int soluv=calcular_makespan(resultado,tarefas,n_maq);
    double a=2;
    for(int i=0;i<itera;i++){
        a = 2.0 - (2.0 * i) / itera;
        vector<int>atual;
        criar_solucao(tarefas,k,atual);
        int atualv=calcular_makespan(atual,tarefas,n_maq);
        if(soluv>atualv){
            swap(atual,resultado);
        }
        vector<int>valor;
        for(int i=0;i<tarefas.size();i++){
            valor.push_back(tarefas[i].size());
        }
        vector<int> candidatos;
        for (int j = 0; j < valor.size(); j++) {
            candidatos.push_back(j);
        }
        for(int j=0;j<k;j++){
            double mov=rand_real(0.0,1.0);
            if(mov<=0.5){
                mov_espiral(resultado, atual, tarefas, a,valor,candidatos,j);
            }
            else{
                mov_linear(resultado,atual,tarefas,a,valor,candidatos,j);
            }
        }
        atualv=calcular_makespan(atual,tarefas,n_maq);
        if(soluv>atualv){
            swap(atual,resultado);
        }
    }
    cout<<calcular_makespan(resultado,tarefas,n_maq)<<endl;
    return 0;
}