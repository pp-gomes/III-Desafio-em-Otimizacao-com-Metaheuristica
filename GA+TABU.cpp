#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class HashedString
{

private:
    // change M and B if you want

    static const long long M = 1e9 + 9;

    static const long long B = 9973;

    // pow[i] contains B^i % M

    static vector<long long> pow;

    // p_hash[i] is the hash of the first i characters of the given string

    vector<long long> p_hash;

public:
    HashedString(const string &s) : p_hash(s.size() + 1)
    {

        while (pow.size() <= s.size())
        {
            pow.push_back((pow.back() * B) % M);
        }

        p_hash[0] = 0;

        for (int i = 0; i < s.size(); i++)
        {

            p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
        }
    }

    long long get_hash(int start, int end)
    {

        long long raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));

        return (raw_val % M + M) % M;
    }
};

vector<long long> HashedString::pow = {1};

int rand_int(int a, int b)
{
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

double rand_real(double a, double b)
{
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

int calcular_makespan(const vector<int> &ordem, const vector<vector<pair<int, int>>> &tarefas, int n_maq)
{
    vector<int> tempo_maquina(n_maq, 0), tempo_tarefa(tarefas.size(), 0);
    vector<int> etapas(tarefas.size(), 0);
    int finalizado = 0;

    while (finalizado < tarefas.size())
    {
        for (int idx : ordem)
        {
            if (etapas[idx] >= tarefas[idx].size())
                continue;
            int maq = tarefas[idx][etapas[idx]].first;
            int dur = tarefas[idx][etapas[idx]].second;
            tempo_maquina[maq] = max(tempo_maquina[maq], tempo_tarefa[idx]) + dur;
            tempo_tarefa[idx] = tempo_maquina[maq];
            etapas[idx]++;
            if (etapas[idx] == tarefas[idx].size())
                finalizado++;
        }
    }

    return *max_element(tempo_maquina.begin(), tempo_maquina.end());
}

void criar_solucao(const vector<vector<pair<int, int>>> &tarefas, int k, vector<int> &resultado)
{
    vector<int> etapas_restantes(tarefas.size());
    vector<int> candidatos;

    for (int i = 0; i < tarefas.size(); i++)
    {
        etapas_restantes[i] = tarefas[i].size();
        candidatos.push_back(i);
    }

    resultado.clear();
    for (int i = 0; i < k; i++)
    {
        int pos = rand_int(0, candidatos.size() - 1);
        int escolhido = candidatos[pos];
        resultado.push_back(escolhido);
        etapas_restantes[escolhido]--;
        if (etapas_restantes[escolhido] == 0)
            candidatos.erase(candidatos.begin() + pos);
    }
}

void mutar(vector<int> &ordem)
{
    int qtd = rand_int(0, 10);
    for (int i = 0; i < qtd; i++)
    {
        int r1 = rand_int(0, ordem.size() - 1), r2 = rand_int(0, ordem.size() - 1);
        swap(ordem[r1], ordem[r2]);
    }
}

void cruzamento(vector<int> &novo, vector<int> &pai1, vector<int> &pai2, vector<int> x, int n_trab)
{
    for (int i = 0; i < pai1.size(); i++)
    {
        if (rand_real(0.0, 1.0) <= 0.5)
        {
            if (x[pai1[i]] > 0)
            {
                x[pai1[i]]--;
                novo.push_back(pai1[i]);
            }
            else
            {
                if (x[pai2[i]] > 0)
                {
                    x[pai2[i]]--;
                    novo.push_back(pai2[i]);
                }
                else
                {
                    vector<int> cand;
                    for (int j = 0; j < n_trab; j++)
                    {
                        if (x[j] > 0)
                        {
                            cand.push_back(j);
                        }
                    }
                    novo.push_back(cand[rand_int(0, cand.size() - 1)]);
                }
            }
        }
        else
        {
            if (x[pai2[i]] > 0)
            {
                x[pai2[i]]--;
                novo.push_back(pai2[i]);
            }
            else
            {
                if (x[pai1[i]] > 0)
                {
                    x[pai1[i]]--;
                    novo.push_back(pai1[i]);
                }
                else
                {
                    vector<int> cand;
                    for (int j = 0; j < n_trab; j++)
                    {
                        if (x[j] > 0)
                        {
                            cand.push_back(j);
                        }
                    }
                    novo.push_back(cand[rand_int(0, cand.size() - 1)]);
                }
            }
        }
        // cout<<novo.back()<<" ";
    } // cout<<endl;
    return;
}

bool tabu(queue<long long> s, vector<int> &atual, long long &x)
{
    while (!s.empty())
    {
        if (s.front() == x)
        {
            return true;
        }
        s.pop();
    }
    return false;
}

int main()
{
    int n_trab, n_maq;
    cin >> n_trab >> n_maq;
    int qtd = 1000;
    int popula_ini = 100;
    double escolha = 0.1;
    double qtd_filho_porc = 0.1;
    double mutac = 0.6;
    int popula_max = 130;
    int tam_queue_max = 10;
    vector<vector<pair<int, int>>> tarefas(n_trab);
    cin.ignore();
    int k = 0;
    vector<int> x(n_trab);
    for (int i = 0; i < n_trab; i++)
    {
        string g;
        getline(cin, g);
        stringstream ss(g);
        int maq, tempo;
        while (ss >> maq >> tempo)
        {
            tarefas[i].emplace_back(maq, tempo);
            k++;
            x[i]++;
        }
    }
    vector<pair<int, vector<int>>> popu;
    for (int i = 0; i < popula_ini; i++)
    {
        vector<int> atual;
        criar_solucao(tarefas, k, atual);
        popu.push_back({calcular_makespan(atual, tarefas, n_maq), atual});
    }
    sort(popu.begin(), popu.end());
    int p = popu.size();
    queue<long long> s;
    while (qtd)
    {
        for (int i = 0; i < p * escolha; i++)
        {
            for (int j = 0; j <= p * qtd_filho_porc; j++)
            {
                vector<int> novoind;
                vector<int> xn = x;
                cruzamento(novoind, popu[i].second, popu[rand_int(0, p - 1)].second, xn, n_trab);
                if (rand_real(0.0, 1.0) <= mutac)
                {
                    mutar(novoind);
                }
                string solu = "";
                for (int i = 0; i < novoind.size(); i++)
                {
                    solu = solu + to_string(novoind[i]);
                }
                HashedString h(solu);
                long long xx = h.get_hash(0, solu.size() - 1);
                if (!tabu(s, novoind, xx))
                {
                    popu.push_back({calcular_makespan(novoind, tarefas, n_maq), novoind});
                    s.push(xx);
                    while (s.size() > tam_queue_max)
                    {
                        s.pop();
                    }
                }
                else
                {
                    j--;
                }
            }
            // cout<<qtd<<endl;
        }
        qtd--;
        sort(popu.begin(), popu.end());
        while (popu.size() > popula_max)
        {
            popu.pop_back();
        }
        // cout<<qtd<<endl;
    }
    cout << popu[0].first << endl;
}