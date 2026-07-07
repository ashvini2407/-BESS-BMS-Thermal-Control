#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// ========== CONFIGURATION ==========
#define TEMP_SHUTDOWN 55.0f  // System shutdown above this
#define TEMP_DERATE 45.0f    // Start derating power above this
#define TEMP_NORMAL_MAX 35.0f // Cooling starts above this
#define TEMP_FREEZE 0.0f     // No charging below this

// ========== GLOBAL VARIABLES ==========
uint8_t fan_pwm = 0;        // Fan speed 0-100%
uint8_t power_limit = 100;  // Power limit 0-100%

// ========== THERMAL CONTROL LOGIC ==========
void bms_thermal_control(float current_temp) {
    printf("\n>>> Current Temperature: %.1f°C <<<\n", current_temp);

    // State Machine Logic
    if (current_temp > TEMP_SHUTDOWN) {
        fan_pwm = 100;
        power_limit = 0;
        printf("[CRITICAL] %.1f°C > %.1f°C! SYSTEM SHUTDOWN\n", current_temp, TEMP_SHUTDOWN);
        printf("Action: Contactor OPEN, Fan 100%%, Power 0%%\n");
    }
    else if (current_temp > TEMP_DERATE) {
        fan_pwm = 100;
        power_limit = 50;
        printf("[HOT] %.1f°C > %.1f°C! DERATE MODE\n", current_temp, TEMP_DERATE);
        printf("Action: Fan 100%%, Power Limit 50%%\n");
    }
    else if (current_temp > TEMP_NORMAL_MAX) {
        fan_pwm = 60;
        power_limit = 100;
        printf("[WARM] %.1f°C > %.1fC. COOLING ACTIVE\n", current_temp, TEMP_NORMAL_MAX);
        printf("Action: Fan 60%%, Power 100%%\n");
    }
    else if (current_temp < TEMP_FREEZE) {
        fan_pwm = 0;
        power_limit = 30;
        printf("[COLD] %.1f°C < %.1f°C! HEATING MODE\n", current_temp, TEMP_FREEZE);
        printf("Action: Heater ON, Charge Limit 30%%\n");
    }
    else {
        fan_pwm = 20;
        power_limit = 100;
        printf("[NORMAL] %.1f°C - All Good\n", current_temp);
        printf("Action: Fan 20%%, Power 100%%\n");
    }
    printf("-------------------------------------------\n");
}

// ========== MAIN FUNCTION ==========
int main(void) {
    float user_temp;
    char choice;

    printf("=========================================\n");
    printf("   BESS BMS Thermal Control Simulator   \n");
    printf("=========================================\n");
    printf("Temperature Limits: \n");
    printf("  < 0°C     = COLD - Heating mode\n");
    printf("  0-35°C    = NORMAL - Baseline cooling\n");
    printf("  35-45°C   = WARM - Active cooling\n");
    printf("  45-55°C   = HOT - Derate power\n");
    printf("  > 55°C    = CRITICAL - Shutdown\n");
    printf("=========================================\n");

    while(1) {
        printf("\nEnter temperature value (°C): ");
        scanf("%f", &user_temp);

        // Call control function
        bms_thermal_control(user_temp);

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &choice); // Note the space before %c

        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    printf("\nSimulation completed. Thank you!\n");
    return 0;
}