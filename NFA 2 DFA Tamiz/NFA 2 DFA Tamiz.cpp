#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;

unordered_map<string, int> states;
vector<char> alphabet;
vector<bool> finalStates;
vector<bool> visited;
vector<bool> visited2;
vector<int> EpsClosure;
vector<int> EpsClosure2;
set<int> MovesRes;
vector<vector<pair<string, int>>> NFA;
vector<vector<int>> storedVectors;
vector<vector<int>> EpMove; //stores result of e-closure(move(state, transition)) for each state;
int labelCounter = 0;

void movefunc(vector<int> list);

void dfs(int Current) {
    //counts epsilon closure for first state
    visited[Current] = true;
    EpsClosure.push_back(Current);
    for (int i = 0; i < NFA[Current].size(); i++)
    {
        if (!visited[NFA[Current][i].second] && NFA[Current][i].first == "$") {
            dfs(NFA[Current][i].second);
        }
    }
}

void dfs2(int Current) {
    //counts epsilon closure of moves
    visited2[Current] = true;
    EpsClosure2.push_back(Current);
    for (int i = 0; i < NFA[Current].size(); i++)
    {
        if (!visited2[NFA[Current][i].second] && NFA[Current][i].first == "$") {
            dfs2(NFA[Current][i].second);
        }
    }
}

void movefunc(vector<int> list) {
    for (int k = 0; k < alphabet.size(); k++)
    {
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < NFA[list[i]].size(); j++)
            {
                if (NFA[list[i]][j].first[0] == alphabet[k]) {
                    MovesRes.insert(NFA[list[i]][j].second);
                }
            }
        }
        for (auto& a : MovesRes) {
            dfs2(a);
            visited2.assign(NFA.size(), 0);
        }
        sort(EpsClosure2.begin(), EpsClosure2.end());
        EpMove.push_back(EpsClosure2);
        EpsClosure2.clear();
        MovesRes.clear();
    }

    for (auto& a : EpMove) {
        auto it = find(storedVectors.begin(), storedVectors.end(), a);
        if (a.size() && it == storedVectors.end()) {
            storedVectors.push_back(a);
        }
    }
    EpMove.clear();
    labelCounter++;
    for (; labelCounter < storedVectors.size();)
    {
        movefunc(storedVectors[labelCounter]);
    }
}

int main()
{
    int statesNum, alphabetNum, finalStateNum, transitionsNum;
    cin >> statesNum;
    for (int i = 0; i < statesNum; i++) {
        string x;
        cin >> x;
        states[x] = i;
    }
    cin >> alphabetNum;
    alphabet.resize(alphabetNum);
    for (int i = 0; i < alphabetNum; i++) {
        cin >> alphabet[i];
    }
    cin >> finalStateNum;
    finalStates.resize(statesNum);
    for (int i = 0; i < finalStateNum; i++) {
        string x;
        cin >> x;
        finalStates[states[x]] = true;
    }
    cin >> transitionsNum;
    NFA.resize(statesNum + 1);
    visited.resize(statesNum, false);
    visited2.resize(statesNum, false);

    for (int i = 0; i < transitionsNum; i++) {
        string str;
        cin >> str;
        vector<string> v;
        stringstream ss(str);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }
        NFA[states[v[0]]].push_back({ v[1], states[v[2]] });
    }
    dfs(0);
    storedVectors.push_back(EpsClosure);
    movefunc(EpsClosure);
    cout << storedVectors.size() + 1;
}
