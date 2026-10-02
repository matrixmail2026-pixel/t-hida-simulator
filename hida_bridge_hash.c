#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    double position; 
    double velocity; 
    double energy;   
} ParticleTrack;

static inline double calculate_acceleration(double x) {
    double abs_x = (x < 0) ? -x : x;
    if (abs_x < 1e-9) return 0.0; 
    return 1.0 / (x * x); 
}

// The core algorithm: physics-based cryptographic hash
void hida_bridge_hash(const void *input, size_t len, void *output) {
    uint32_t seed = 0;
    const uint8_t *byte_ptr = (const uint8_t *)input;
    for (size_t i = 0; i < len && i < 64; i++) {
        seed = seed * 33 + byte_ptr[i];
    }

    double epsilon = 0.1 + ((seed % 1000) * 0.00001);
    double asymptote_limit = -1e-6; 
    double dt = 0.00001;            
    
    ParticleTrack particle = {-epsilon, 0.0, 0.0};
    int total_steps = 0;
    int folds_triggered = 0;
    const int target_folds = 3; 

    while (folds_triggered < target_folds && total_steps < 500000) {
        total_steps++;
        double accel = calculate_acceleration(particle.position);
        particle.velocity += accel * dt;
        particle.position += particle.velocity * dt;

        if (particle.position >= asymptote_limit) {
            folds_triggered++;
            particle.position = -epsilon; 
        }
    }

    particle.energy = 0.5 * particle.velocity * particle.velocity;
    
    uint64_t high_velocity_bits;
    uint64_t energy_bits;
    memcpy(&high_velocity_bits, &particle.velocity, sizeof(double));
    memcpy(&energy_bits, &particle.energy, sizeof(double));

    // Fill the 32-byte (256-bit) crypto output buffer
    uint64_t *out64 = (uint64_t *)output;
    out64[0] = high_velocity_bits ^ 0x5555555555555555ULL;
    out64[1] = energy_bits ^ 0xAAAAAAAAAAAAAAAAULL;
    out64[2] = (uint64_t)total_steps;
    out64[3] = (uint64_t)seed;
}

// Simulates a crypto pool checking if the hash meets the target difficulty
bool check_crypto_difficulty(const uint8_t *hash, const uint8_t *target) {
    for (int i = 0; i < 32; i++) {
        if (hash[i] < target[i]) return true;
        if (hash[i] > target[i]) return false;
    }
    return true; // Exactly equal
}

int main() {
    printf("=== HIDA-BRIDGE CRYPTO TARGET SIMULATION ===\n\n");

    uint8_t block_header[76] = "Genesis_Block_Data_Payload_Simulation_2026_With_Extra_Entropy_Padding_Bytes";
    uint32_t *nonce_ptr = (uint32_t *)&block_header[72];

    uint8_t target[32];
    memset(target, 0xFF, 32);
    target[0] = 0x00;
    target[1] = 0x0F; 

    printf("Target Boundary: ");
    for(int i=0; i<32; i++) printf("%02x", target[i]);
    printf("\n\nMining simulation started...\n");

    uint8_t output_hash[32];
    uint32_t loop_count = 0;
    bool block_found = false;

    for (*nonce_ptr = 0; *nonce_ptr < 100000; (*nonce_ptr)++) {
        loop_count++;
        hida_bridge_hash(block_header, sizeof(block_header), output_hash);

        if (check_crypto_difficulty(output_hash, target)) {
            printf("\n[!] VALID BLOCK FOUND AT NONCE: %u\n", *nonce_ptr);
            printf("Resulting Hash:  ");
            for(int i=0; i<32; i++) printf("%02x", output_hash[i]);
            printf("\n");
            block_found = true;
            break;
        }

        if (loop_count % 20000 == 0) {
            printf("Evaluated %u nonces... (No shares met the target yet)\n", loop_count);
        }
    }

    if (!block_found) {
        printf("\nSimulation finished. 0 valid blocks found. Try lowering the difficulty target.\n");
    }

    return 0;
}
