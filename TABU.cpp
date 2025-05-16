#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class HashedString {

  private:

	// change M and B if you want

	static const long long M = 1e9 + 9;

	static const long long B = 9973;


	// pow[i] contains B^i % M

	static vector<long long> pow;


	// p_hash[i] is the hash of the first i characters of the given string

	vector<long long> p_hash;


  public:

	HashedString(const string &s) : p_hash(s.size() + 1) {

		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }


		p_hash[0] = 0;

		for (int i = 0; i < s.size(); i++) {

			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;

		}

	}


	long long get_hash(int start, int end) {

		long long raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));

		return (raw_val % M + M) % M;

	}

};

vector<long long> HashedString::pow = {1};

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

bool tabu(queue<long long>s,vector<int>&atual,long long &x){
    while(!s.empty()){
        if(s.front()==x){
            return true;
        }
        s.pop();
    }
    return false;
}

int main(){
    int n_trab,n_maq;
    cin>>n_trab>>n_maq;
    int qtd=10000;
    int max_v_pilha=10;
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
    }
    queue<long long>s;
    vector<int>solucao;
    criar_solucao(tarefas,k,solucao);
    int vs=calcular_makespan(solucao,tarefas,n_maq);
    for(int i=0;i<qtd;i++){
        vector<int>atual;
        criar_solucao(tarefas,k,atual);
        string solu="";
        for(int i=0;i<atual.size();i++){
            solu=solu+to_string(atual[i]);
            cout<<solu<<endl;
        }
        HashedString h(solu);
        long long x=h.get_hash(0,solu.size()-1);
        if(tabu(s,atual,x)==true){
            i--;
        }
        else{
            s.push(x);
            if(s.size()==max_v_pilha){
                s.pop();
            }
            int vt=calcular_makespan(atual,tarefas,n_maq);
            if(vt<vs){
                vs=vt;
                solucao=atual;
            }
        }
    }
    cout<<calcular_makespan(solucao,tarefas,n_maq)<<endl;
}