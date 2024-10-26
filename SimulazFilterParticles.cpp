#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

const int NUM_PARTICLES = 1000;   // particelle
const int MAX_NUMBER = 10;       // massimo range

struct Particle {
    int value;
    double weight;
};

// inizializzo le particelle
void iniziaParticles(std::vector<Particle>& particles) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, MAX_NUMBER);

    for (auto& particle : particles) {
        particle.value = distribution(generator);
        particle.weight = 1.0 / NUM_PARTICLES;
    }
}

// aggiorna pesi particelle
void updatePesi(std::vector<Particle>& particles, int userInput) {
    std::default_random_engine generator;
    std::normal_distribution<double> noise(0, 1);  

    for (auto& particle : particles) {
        double likelihood = 1.0 / (1.0 + std::abs(userInput - particle.value + noise(generator)));
        particle.weight = likelihood;
    }

    // normalizza
    double sumWeights = 0.0;
    for (const auto& particle : particles) {
        sumWeights += particle.weight;
    }
    for (auto& particle : particles) {
        particle.weight /= sumWeights;
    }
}

// risampling
void resampleParticles(std::vector<Particle>& particles) {
    std::vector<Particle> newParticles;
    std::default_random_engine generator;

    // estrazione pesi per tentare il calcolo
    std::vector<double> weights;
    for (const auto& particle : particles) {
        weights.push_back(particle.weight);
    }

    // pariziale distribuzione
    std::discrete_distribution<int> distribution(weights.begin(), weights.end());

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        newParticles.push_back(particles[distribution(generator)]);
    }
    particles = newParticles;
}

// calcola la stima sul numero
int stimaNum(const std::vector<Particle>& particles) {
    double estimate = 0;
    for (const auto& particle : particles) {
        estimate += particle.value * particle.weight;
    }
    return static_cast<int>(estimate + 0.1);  // arrotondo per evitare errori
}

int main() {
    int userInput;
    char continueLoop = 'y';

    // SIMULAZIONE
    do {
        std::cout << "Inserisci un numero tra 1 e 10 (0 per uscire): ";
        std::cin >> userInput;

        if (userInput == 0) {
            std::cout << "Uscita dal programma...\n";
            break;
        }

        if (userInput < 1 || userInput > 10) {
            std::cerr << "Input non valido ! \n";
            continue;
        }

        // inizializza particles
        std::vector<Particle> particles(NUM_PARTICLES);
        iniziaParticles(particles);

        // aggiorna le particles
        for (int i = 0; i < 20; ++i) {  
            updatePesi(particles, userInput); 
            resampleParticles(particles);
            int estimatedNumber = stimaNum(particles);

            std::cout << "\033[1;31mDEBUG : Iterazione " << i + 1 << ", Stima del numero: " << estimatedNumber << "\033[0m\n";
        }

        // stampa la stima finale
        int finalEstimate = stimaNum(particles);
        std::cout << "\033[1;32mStima finale del numero inserito: " << finalEstimate << "\033[0m\n";
        std::cout << "\nVuoi inserire un altro numero? (s/n): ";
        std::cin >> continueLoop;

    } while (continueLoop == 's' || continueLoop == 'S');

    return 0;
}
