/*

   _____              _        _                   __  __
  / ____|     /\     | |      | |          /\     |  \/  |
 | (___      /  \    | |      | |         /  \    | \  / |
  \___ \    / /\ \   | |      | |        / /\ \   | |\/| |
  ____) |  / ____ \  | |____  | |____   / ____ \  | |  | |
 |_____/  /_/    \_\ |______| |______| /_/    \_\ |_|  |_|

    Free Palestine
	20210614
	20201126
	20200029
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#define POPULATION_SIZE 100
#define MUTATION_THRESHOLD 0.1
#define CROSSOVER_THRESHOLD 0.7
#define BESTN 0.1 * POPULATION_SIZE
#define MAX_GENERATION 500
#define MAX_CHILDREN 0.2 * POPULATION_SIZE
using namespace std;

long double fRand(long double fMin, long double fMax){
    long double f = (long double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void initialize(vector < vector <long double> >& population, int degree){
    for(int i = 0; i < POPULATION_SIZE; i++){
        vector <long double> temp(degree);
        for(int j = 0; j < degree; j++){
            long double r = fRand(-10.0, 10.0);
            temp[j] = r;
        }
        population.push_back(temp);
    }
}

vector <pair <long double, int>> calcFitness(const vector < vector <long double> >& population, int degree,  vector <pair <long double, long double>>& vec, int& num){
    vector <pair <long double, int>> fitness;

    for(int i = 0; i < population.size(); i++){
        long double globalDiff = 0;
        for(int j = 0; j < num; j++){
            long double y = 0;
            for(int k = 0; k < degree; k++){
                if(k == 0){
                    y += population[i][k];
                }else{
                    y += population[i][k] * powl(vec[j].first, k);
                }
            }
            globalDiff += powl(abs(y - vec[j].second), 2);
        }
        fitness.push_back({globalDiff / num, i});
    }

    return fitness;
}

pair <int, int> tournamentSelection(const vector <pair <long double, int>>& fitness){
    int cParent1 = rand() % POPULATION_SIZE;
    int cParent2 = rand() % POPULATION_SIZE;
    int cParent3 = rand() % POPULATION_SIZE;
    int cParent4 = rand() % POPULATION_SIZE;

    long double x1, x2, x3, x4;
    for(int i = 0; i < POPULATION_SIZE; i++){
        if(fitness[i].second == cParent1){
            x1 = fitness[i].first;
        }
        if(fitness[i].second == cParent2){
            x2 = fitness[i].first;
        }
        if(fitness[i].second == cParent3){
            x3 = fitness[i].first;
        }
        if(fitness[i].second == cParent4){
            x4 = fitness[i].first;
        }
    }

    int parent1, parent2;

    if(x1 >= x2){
        parent1 = cParent2;
    }else{
        parent1 = cParent1;
    }

    if(x3 >= x4){
        parent2 = cParent4;
    }else{
        parent2 = cParent3;
    }

    return {parent1, parent2};
}

void mutation(vector < vector <long double> >& population, int degree, int generation){
    for(int i = 0; i < population.size(); i++){
        for(int j = 0; j < degree; j++){
            double r = (double)rand() / RAND_MAX;
            if(r > MUTATION_THRESHOLD){
                continue;
            }
            r = (double)rand() / RAND_MAX;
            int y;
            if(r <= 0.5){
                y = population[i][j] - (-10);
            }
            else{
                y = 10 - population[i][j];
            }
            double r1 = (double)rand() / RAND_MAX;
            double temp = powl(1.0*(1-generation/MAX_GENERATION), 1);
            double delta = y * (1 - powl(r1, temp));
            if(r <= 0.5)
                population[i][j] -= delta;
            else
                population[i][j] += delta;
        }
    }
}

void replacement(vector < vector <long double> >& population, int degree,  vector <pair <long double, long double>>& vec, int& num){
    vector < vector <long double> > newPop;
    vector <pair <long double, int>> fitness = calcFitness(population, degree, vec, num);
    sort(fitness.begin(), fitness.end());
    for(int i = 0; i < POPULATION_SIZE - BESTN; i++){
        newPop.push_back(population[fitness[i].second]);
    }
    population = newPop;
}

void parentSelection(vector < vector <long double> >& population, int degree,  vector <pair <long double, long double>>& vec, int& num, int generation){
    vector <pair <long double, int>> fitness = calcFitness(population, degree, vec, num);
    sort(fitness.begin(), fitness.end());
    vector <pair <int, int>> matched;
    for(int i = 0; i < MAX_CHILDREN; i++){
        long double r = (long double)rand() / RAND_MAX;
        pair <int, int> parents = tournamentSelection(fitness);
        if(r < CROSSOVER_THRESHOLD)
            matched.push_back(parents);
    }

    for(int i = 0; i < matched.size(); i++){
        vector <long double> child1, child2;

        int r1 = rand() % degree;
        int r2 = rand() % degree;
        int temp = max(r1, r2);
        r1 = min(r1, r2);
        r2 = temp;

        for(int j = 0; j < r1; j++){
            child1.push_back(population[matched[i].first][j]);
            child2.push_back(population[matched[i].second][j]);
        }

        for(int j = r1; j < r2; j++){
            child1.push_back(population[matched[i].second][j]);
            child2.push_back(population[matched[i].first][j]);
        }

        for(int j = r2; j < degree; j++){
            child1.push_back(population[matched[i].first][j]);
            child2.push_back(population[matched[i].second][j]);
        }

        population.push_back(child1);
        population.push_back(child2);
    }

    vector<vector<long double>> best;
    for(int i = 0; i < BESTN; i++){
        best.push_back(population[i]);
    }

    mutation(population, degree, generation);
    replacement(population, degree, vec, num);
    for(int i = 0; i < BESTN; i++){
        population.push_back(best[i]);
    }
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    srand(time(NULL));
    int t; cin >> t;
    for(int n = 0; n < t; n++){
        int num, degree; cin >> num >> degree;
        degree++;
        vector <pair <long double, long double>> vec;
        for(int i = 0; i < num; i++){
            long double x, y; cin >> x >> y;
            vec.push_back({x, y});
        }

        vector < vector <long double> > population;

        initialize(population, degree);

        for(int i = 0; i < MAX_GENERATION; i++){
            parentSelection(population, degree, vec, num, i);
        }
        vector <pair <long double, int>> fitness = calcFitness(population, degree, vec, num);
        sort(fitness.begin(), fitness.end());
        cout << "Test: " << n + 1 << endl;
        for(int i = 0; i < degree; i++){
            cout << population[fitness[0].second][i] << " ";
        }
        cout << endl;
        cout << "Mean squared error: ";

        cout << fixed << fitness[0].first << endl;
        cout << endl;
    }
}