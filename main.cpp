#include <iostream>
#include <cmath>
#include <iomanip>

struct ParticleTrack {
    double position; 
    double velocity; 
    double energy;   
};

// Calculates acceleration from an attractive force towards 0
double calculate_acceleration(double x) {
    if (std::abs(x) < 1e-9) return 0.0; // Prevent division by zero at the exact limit
    return 1.0 / (x * x); 
}

int main() {
    double epsilon = 0.1;           // Starting offset at -0.1
    double asymptote_limit = -1e-6; // Barrier approaching 0^-
    double dt = 0.00001;            // Smaller time step for high-speed accuracy near the fold
    
    ParticleTrack particle = {-epsilon, 0.0, 0.0};

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "=== ENHANCED HIDA DECOMPOSITION BRIDGE SIMULATOR ===" << std::endl;
    std::cout << "Initial Position (x_0): " << particle.position << std::endl;
    std::cout << "Asymptote Limit:      " << asymptote_limit << std::endl << std::endl;

    int total_steps = 0;
    int folds_triggered = 0;
    const int target_folds = 3; // Let's watch it loop 3 times

    while (folds_triggered < target_folds && total_steps < 500000) {
        total_steps++;

        // Verlet/Euler integration step
        double accel = calculate_acceleration(particle.position);
        particle.velocity += accel * dt;
        particle.position += particle.velocity * dt;
        particle.energy = 0.5 * particle.velocity * particle.velocity;

        // Boundary Fold Check: Trigger topological fold R(x) near 0^-
        if (particle.position >= asymptote_limit) {
            folds_triggered++;
            std::cout << "\n[!] LOOP " << folds_triggered 
                      << " -- BOUNDARY FOLD TRIGGERED at x = " << particle.position << std::endl;
            std::cout << "    Re-injecting at -epsilon (" << -epsilon << ") with preserved velocity: " 
                      << particle.velocity << " | Energy: " << particle.energy << std::endl << std::endl;
            
            // Re-inject while preserving momentum state
            particle.position = -epsilon;
        }

        // Print status periodically so console isn't flooded
        if (total_steps % 5000 == 0 && folds_triggered == 0) {
            std::cout << "Step " << std::setw(6) << total_steps 
                      << " | x: " << std::setw(12) << particle.position 
                      << " | v: " << std::setw(12) << particle.velocity 
                      << " | Energy: " << particle.energy << std::endl;
        }
    }

    std::cout << "\nSimulation completed after " << total_steps << " total steps and " 
              << folds_triggered << " boundary folds." << std::endl;

    return 0;
}
