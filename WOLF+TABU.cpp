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

void ordenar_lobos(vector<int> &makespans, vector<vector<int>> &posicoes)
{
    vector<pair<int, vector<int>>> pares;
    for (size_t i = 0; i < makespans.size(); i++)
        pares.push_back({makespans[i], posicoes[i]});

    sort(pares.begin(), pares.end());

    for (size_t i = 0; i < makespans.size(); i++)
    {
        makespans[i] = pares[i].first;
        posicoes[i] = pares[i].second;
    }
}

void exibir_caminho_alfa(const vector<int> &ordem, const vector<vector<pair<int, int>>> &tarefas, int n_maq)
{
    vector<int> tempo_maquina(n_maq, 0), tempo_tarefa(tarefas.size(), 0);
    vector<int> etapas(tarefas.size(), 0);
    int finalizado = 0;

    struct Operacao
    {
        int tarefa, etapa, maq, ini, fim;
    };

    vector<Operacao> caminho;

    while (finalizado < tarefas.size())
    {
        for (int idx : ordem)
        {
            if (etapas[idx] >= tarefas[idx].size())
                continue;
            int maq = tarefas[idx][etapas[idx]].first;
            int dur = tarefas[idx][etapas[idx]].second;
            int ini = max(tempo_maquina[maq], tempo_tarefa[idx]);
            int fim = ini + dur;

            caminho.push_back({idx, etapas[idx], maq, ini, fim});

            tempo_maquina[maq] = fim;
            tempo_tarefa[idx] = fim;
            etapas[idx]++;
            if (etapas[idx] == tarefas[idx].size())
                finalizado++;
        }
    }

    cout << "\n--- Caminho do Lobo Alfa (tarefa, etapa, máquina, início, fim) ---\n";
    for (const auto &op : caminho)
    {
        cout << "Tarefa " << op.tarefa << ", Etapa " << op.etapa
             << ", Máquina " << op.maq
             << ", Início " << op.ini
             << ", Fim " << op.fim << "\n";
    }
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

int main()
{
    int n_maq, n_trab, n_wolf = 100, itera = 1000;
    int max_v_pilha = 10;
    cin >> n_trab >> n_maq;
    cin.ignore();
    int k = 0;
    vector<vector<pair<int, int>>> tarefas(n_trab);
    for (int i = 0; i < n_trab; i++)
    {
        string linha;
        getline(cin, linha);
        stringstream ss(linha);
        int maq, tempo;
        while (ss >> maq >> tempo)
        {
            tarefas[i].emplace_back(maq, tempo);
            k++;
        }
    }
    vector<vector<int>> lobos(n_wolf);
    vector<int> makespans(n_wolf);
    // Inicialização aleatória
    for (int i = 0; i < n_wolf; i++)
    {
        vector<int> ordem;
        for (int j = 0; j < n_trab; j++)
            ordem.push_back(j);
        shuffle(ordem.begin(), ordem.end(), rng);
        lobos[i] = ordem;
        makespans[i] = calcular_makespan(ordem, tarefas, n_maq);
    }
    ordenar_lobos(makespans, lobos);
    // Início do GWO
    queue<long long> s;
    for (int t = 1; t < itera; t++)
    {
        double a = 2.0 * (1.0 - double(t) / itera);
        for (int i = 3; i < n_wolf; i++)
        {
            vector<int> nova_ordem;
            for (size_t j = 0; j < lobos[i].size(); j++)
            {
                double r1 = rand_real(0.0, 1.0), r2 = rand_real(0.0, 1.0);
                double A = 2 * a * r1 - a, C = 2 * r2;

                double d1 = abs(C * lobos[0][j] - lobos[i][j]);
                double d2 = abs(C * lobos[1][j] - lobos[i][j]);
                double d3 = abs(C * lobos[2][j] - lobos[i][j]);

                double x1 = lobos[0][j] - A * d1;
                double x2 = lobos[1][j] - A * d2;
                double x3 = lobos[2][j] - A * d3;

                int x_novo = round((x1 + x2 + x3) / 3.0);
                x_novo = max(0, min(n_trab - 1, x_novo));
                nova_ordem.push_back(x_novo);
            }
            // Corrigir possíveis repetições na ordem
            vector<bool> usado(n_trab, false);
            for (int &val : nova_ordem)
            {
                if (usado[val])
                {
                    for (int k = 0; k < n_trab; k++)
                    {
                        if (!usado[k])
                        {
                            val = k;
                            break;
                        }
                    }
                }
                usado[val] = true;
            }
            string solu = "";
            for (int i = 0; i < nova_ordem.size(); i++)
            {
                solu = solu + to_string(nova_ordem[i]);
            } // cout<<solu<<"*"<<endl;
            HashedString h(solu);
            long long x = h.get_hash(0, solu.size() - 1);
            if (tabu(s, nova_ordem, x))
            {
                vector<int> resultado;
                criar_solucao(tarefas, k, resultado);
                lobos[i] = resultado;
                makespans[i] = calcular_makespan(resultado, tarefas, n_maq);
            }
            else
            {
                s.push(x);
                if (s.size() == max_v_pilha)
                {
                    s.pop();
                }
                lobos[i] = nova_ordem;
                makespans[i] = calcular_makespan(nova_ordem, tarefas, n_maq);
            }
        }
        ordenar_lobos(makespans, lobos);
    }

    // Saída do melhor resultado
    cout << makespans[0] << "\n";
    for (int val : lobos[0])
        cout << val << " ";
    cout << endl;

    // Exibe o caminho detalhado do lobo alfa
    exibir_caminho_alfa(lobos[0], tarefas, n_maq);
}