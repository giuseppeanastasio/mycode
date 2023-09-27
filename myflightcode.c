void init() {
    // Initialize state and timestamps
    state = STATE_INIT;
    cur_ts = 0;
    liftoff_ts = 0;
    apogee_ts = 0;
    landed_ts = 0;
}

void update(float acc_x, float acc_y, float acc_z, float gyro_x, float gyro_y,
            float gyro_z, float baro) {

    // Calculate the total acceleration magnitude
    float acc_magnitude = sqrt(acc_x * acc_x + acc_y * acc_y + acc_z * acc_z);

    // Detect liftoff event using accelerometer data
    if (state == STATE_INIT && acc_magnitude > LIFTOFF_THRESHOLD) {
        // Check if there's a rapid increase in barometric pressure
        if (baro > BARO_THRESHOLD) {
            liftoff();
        }
    }

    // Detect apogee event using barometer data
    if (state == STATE_FLIGHT && baro < APOGEE_THRESHOLD) {
        // Check if the gyroscope indicates minimal movement
        if (sqrt(gyro_x * gyro_x + gyro_y * gyro_y + gyro_z * gyro_z) < GYRO_THRESHOLD) {
            apogee();
        }
    }

    // Detect landing event using accelerometer data
    if (state == STATE_DESCENT && acc_magnitude < LANDING_THRESHOLD) {
        // Check if there's a rapid decrease in barometric pressure
        if (baro < BARO_THRESHOLD) {
            landed();
        }
    }
}

// LIFTOFF_THRESHOLD, APOGEE_THRESHOLD, LANDING_THRESHOLD, BARO_THRESHOLD, and GYRO_THRESHOLD should be the actual numbers that the team reckons suitable enough for a good result.

