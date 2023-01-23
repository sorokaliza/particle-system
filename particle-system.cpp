#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class Particle {
public:
    double x, y;
    double vx, vy;
    double age;
    double maxAge;

    Particle(double x, double y, double vx, double vy, double maxAge) :
        x(x), y(y), vx(vx), vy(vy), maxAge(maxAge) {
            age = 0;
    }

    void update(double dt) {
        x += vx * dt;
        y += vy * dt;
        age += dt;
    }

    bool isAlive() {
        return age < maxAge;
    }
};

class ParticleSystem {
public:
    std::vector<Particle> particles;
    double x, y;
    double vx, vy;
    double spawnRate;
    double spawnRadius;
    double maxAge;

    ParticleSystem(double x, double y, double vx, double vy, double spawnRate, double spawnRadius, double maxAge) :
        x(x), y(y), vx(vx), vy(vy), spawnRate(spawnRate), spawnRadius(spawnRadius), maxAge(maxAge) { }

    void update(double dt) {
        std::random_device rd;
        std::mt19937 engine(rd());
        std::uniform_real_distribution<double> dist(-1, 1);

        for (int i = 0; i < particles.size(); i++) {
            if (!particles[i].isAlive()) {
                particles.erase(particles.begin() + i);
                i--;
                continue;
            }
            particles[i].update(dt);
        }

        int spawnCount = spawnRate * dt;
        for (int i = 0; i < spawnCount; i++) {
            double angle = dist(engine) * 2 * M_PI;
            double vx = cos(angle);
            double vy = sin(angle);
            particles.push_back(Particle(x, y, vx, vy, maxAge));
        }
    }
};

int main() {
    double dt = 0.01; // time step (s)
    double time = 0;
    ParticleSystem ps(0, 0, 0, 0, 10, 1, 5);

    while (time < 5) {
        ps.update(dt);
        time += dt;
    }

    for (auto& p : ps.particles) {
        std::c
