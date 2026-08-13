#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FILTER_WINDOW_SIZE 3

typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;
    int heart_rate;
} VirtualSensorData;

// Moving Average Filter Structure for DSP
typedef struct {
    float buffer[FILTER_WINDOW_SIZE];
    int index;
} MovingAverageFilter;

// Initialize filter buffer to resting gravity (~9.81 m/s^2)
void init_filter(MovingAverageFilter *filter) {
    filter->index = 0;
    for (int i = 0; i < FILTER_WINDOW_SIZE; i++) {
        filter->buffer[i] = 9.81f;
    }
}

// Compute moving average filter output
float apply_filter(MovingAverageFilter *filter, float raw_val) {
    filter->buffer[filter->index] = raw_val;
    filter->index = (filter->index + 1) % FILTER_WINDOW_SIZE;

    float sum = 0.0f;
    for (int i = 0; i < FILTER_WINDOW_SIZE; i++) {
        sum += filter->buffer[i];
    }
    return sum / (float)FILTER_WINDOW_SIZE;
}

VirtualSensorData generate_mock_sensor_data(int step_index) {
    VirtualSensorData data;
    data.accel_x = 0.5f * sinf(step_index * 0.1f);
    data.accel_y = 0.2f * cosf(step_index * 0.1f);
    
    // Simulate motion wave with occasional raw noise spikes
    float noise = ((rand() % 100) / 500.0f) - 0.1f; 
    data.accel_z = 9.81f + (0.8f * sinf(step_index * 0.2f)) + noise;
    
    data.heart_rate = 72 + (rand() % 8); 
    return data;
}

void process_wearable_metrics(float filtered_accel_z, int *step_count) {
    // Peak detection on smoothed signal
    if (filtered_accel_z > 10.3f) {
        (*step_count)++;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    int total_steps = 0;
    MovingAverageFilter accel_filter;
    init_filter(&accel_filter);

    printf("===================================================\n");
    printf("   WEARABLE FIRMWARE EMULATOR v2.0 (DSP FILTER)    \n");
    printf("===================================================\n\n");

    for (int cycle = 1; cycle <= 10; cycle++) {
        VirtualSensorData raw_data = generate_mock_sensor_data(cycle);
        
        // Apply Digital Signal Processing (DSP) filter
        float filtered_z = apply_filter(&accel_filter, raw_data.accel_z);
        
        process_wearable_metrics(filtered_z, &total_steps);

        printf("[Cycle %02d] Raw Z: %.2f | Filtered Z: %.2f m/s^2 | HR: %d bpm | Steps: %d\n",
               cycle, raw_data.accel_z, filtered_z, raw_data.heart_rate, total_steps);
    }

    printf("\n[SYS] Processing Complete. Total detected steps: %d\n", total_steps);
    return 0;
}
