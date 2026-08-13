#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;
    int heart_rate;
} VirtualSensorData;

VirtualSensorData generate_mock_sensor_data(int step_index) {
    VirtualSensorData data;
    data.accel_x = 0.5f * sinf(step_index * 0.1f);
    data.accel_y = 0.2f * cosf(step_index * 0.1f);
    data.accel_z = 9.81f + (0.8f * sinf(step_index * 0.2f));
    data.heart_rate = 72 + (rand() % 8); 
    return data;
}

void process_wearable_metrics(VirtualSensorData data, int *step_count) {
    if (data.accel_z > 10.3f) {
        (*step_count)++;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    int total_steps = 0;

    printf("===========================================\n");
    printf("   WEARABLE FIRMWARE EMULATOR (PURE C)    \n");
    printf("===========================================\n\n");

    for (int cycle = 1; cycle <= 10; cycle++) {
        VirtualSensorData current_readings = generate_mock_sensor_data(cycle);
        process_wearable_metrics(current_readings, &total_steps);

        printf("[Cycle %02d] Accel Z: %.2f m/s^2 | Heart Rate: %d bpm | Total Steps: %d\n",
               cycle, current_readings.accel_z, current_readings.heart_rate, total_steps);
    }

    printf("\n[SYS] Simulation Complete. Total detected steps: %d\n", total_steps);
    return 0;
}
