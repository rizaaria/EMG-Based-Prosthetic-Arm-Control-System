#if defined(ESP32) 
  #include <ESP32Servo.h>
#else
  #include <Servo.h>
#endif

// =========================
// KONFIG
// =========================
#define SAMPLE_RATE 500
#define INPUT_PIN A0
#define BUFFER_SIZE 32

#define SERVO_PIN 9

#define EMG_ON  30
#define EMG_OFF 10

// sudut servo
#define ANGLE_OPEN   0
#define ANGLE_CLOSE  180

// smoothing servo
#define SERVO_SPEED 5   // makin kecil makin halus

// =========================
// VARIABEL
// =========================
int circular_buffer[BUFFER_SIZE];
int data_index = 0, sum = 0;

Servo servo;

int current_angle = 0;
int target_angle = 0;

// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(115200);
  servo.attach(SERVO_PIN);
  servo.write(ANGLE_OPEN);
  current_angle = ANGLE_OPEN;
}

// =========================
// LOOP
// =========================
void loop() {

  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  static long timer = 0;
  timer -= interval;

  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;

    int sensor_value = analogRead(INPUT_PIN);
    int signal = EMGFilter(sensor_value);
    int envelop = getEnvelop(abs(signal));

    // =========================
    // LOGIKA EMG
    // =========================
    if (envelop > EMG_ON) {
      target_angle = ANGLE_CLOSE;   // kontraksi
    } 
    else if (envelop < EMG_OFF) {
      target_angle = ANGLE_OPEN;    // relaksasi
    }

    // =========================
    // SMOOTH MOVEMENT (anti jerk)
    // =========================
    if (current_angle < target_angle) {
      current_angle += SERVO_SPEED;
      if (current_angle > target_angle) current_angle = target_angle;
    } 
    else if (current_angle > target_angle) {
      current_angle -= SERVO_SPEED;
      if (current_angle < target_angle) current_angle = target_angle;
    }

    servo.write(current_angle);

    // =========================
    // DEBUG
    // =========================
    Serial.print("ENV:");
    Serial.print(envelop);
    Serial.print(" ANGLE:");
    Serial.println(current_angle);
  }
}

// =========================
// ENVELOPE
// =========================
int getEnvelop(int abs_emg) {
  sum -= circular_buffer[data_index];
  sum += abs_emg;
  circular_buffer[data_index] = abs_emg;

  data_index = (data_index + 1) % BUFFER_SIZE;

  return (sum / BUFFER_SIZE);
}

// =========================
// FILTER
// =========================
float EMGFilter(float input) {
  float output = input;

  {
    static float z1, z2;
    float x = output - 0.05159732 * z1 - 0.36347401 * z2;
    output = 0.01856301 * x + 0.03712602 * z1 + 0.01856301 * z2;
    z2 = z1; z1 = x;
  }

  {
    static float z1, z2;
    float x = output - -0.53945795 * z1 - 0.39764934 * z2;
    output = 1.0 * x + -2.0 * z1 + 1.0 * z2;
    z2 = z1; z1 = x;
  }

  {
    static float z1, z2;
    float x = output - 0.47319594 * z1 - 0.70744137 * z2;
    output = 1.0 * x + 2.0 * z1 + 1.0 * z2;
    z2 = z1; z1 = x;
  }

  {
    static float z1, z2;
    float x = output - -1.00211112 * z1 - 0.74520226 * z2;
    output = 1.0 * x + -2.0 * z1 + 1.0 * z2;
    z2 = z1; z1 = x;
  }

  return output;
}
