#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "Statistic.h"
#include "neuton.h"

Statistic accXStats;
Statistic accYStats;
Statistic accZStats;
Statistic gyrXStats;
Statistic gyrYStats;
Statistic gyrZStats;

uint32_t start;
uint32_t stop;

enum Target
{
  TARGET_IDLE,
  TARGET_FERRARI,
  TARGET_HAAS,
  TARGET_WILLIAMS
};

#define NUM_SAMPLES 240
#define CAR_TARGET TARGET_WILLIAMS

typedef struct
{
  float acc_x;
  float acc_y;
  float acc_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
} vector_t;

typedef struct
{
  float aXmin; // minimum acceleration in X axis
  float aXmax; // maximum acceleration in X axis
  float aXavg; // average acceleration in X axis
  float aXvar; // variance of acceleration in X axis
  float aXstdev; // standard deviation of acceleration in X axis
  float aXunbiasStdDev; // unbias standard deviation of acceleration in X axis
  float aYmin; // minimum acceleration in Y axis
  float aYmax; // maximum acceleration in Y axis
  float aYavg; // average acceleration in Y axis
  float aYvar; // variance of acceleration in Y axis
  float aYstdev; // standard deviation of acceleration in Y axis
  float aYunbiasStdDev; // unbias standard deviation of acceleration in Y axis
  float aZmin; // minimum acceleration in Z axis
  float aZmax; // maximum acceleration in Z axis
  float aZavg; // average acceleration in Z axis
  float aZvar; // variance of acceleration in Z axis
  float aZstdev; // standard deviation of acceleration in Z axis
  float aZunbiasStdDev; // unbias standard deviation of acceleration in Z axis
  float gXmin; // minimum gyroscope in X axis
  float gXmax; // maximum gyroscope in X axis
  float gXavg; // average gyroscope in X axis
  float gXvar; // variance of gyroscope in X axis
  float gXstdev; // standard deviation of gyroscope in X axis
  float gXunbiasStdDev; // unbias standard deviation of gyroscope in X axis
  float gYmin; // minimum gyroscope in Y axis
  float gYmax; // maximum gyroscope in Y axis
  float gYavg; // average gyroscope in Y axis
  float gYvar; // variance of gyroscope in Y axis
  float gYstdev; // standard deviation of gyroscope in Y axis
  float gYunbiasStdDev; // unbias standard deviation of gyroscope in Y axis
  float gZmin; // minimum gyroscope in Z axis
  float gZmax; // maximum gyroscope in Z axis
  float gZavg; // average gyroscope in Z axis
  float gZvar; // variance of gyroscope in Z axis
  float gZstdev; // standard deviation of gyroscope in Z axis
  float gZunbiasStdDev; // unbias standard deviation of gyroscope in Z axis
} stats_t;

vector_t data[NUM_SAMPLES];
stats_t stats;

int i = 0;
int j = 0;

// Function prototypes
void save_acc_data(float x, float y, float z);
void save_gyro_data(float x, float y, float z);
void calculate_statistics(vector_t *data, int length);
void save_stats(void);


void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println(__FILE__);
  Serial.print("Demo Statistics lib ");
  Serial.println(STATISTIC_LIB_VERSION);
  start = millis();

  // Initialize IMU
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
}

void loop(void)
{
  // IMU variables
  float x, y, z;

  // Read IMU
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable())
  {
    // Read accelerometer
    IMU.readAcceleration(x, y, z);

    // Save accelerometer data
    save_acc_data(x, y, z);

    // Read gyroscope
    IMU.readGyroscope(x, y, z);

    // Save gyroscope data
    save_gyro_data(x, y, z);

    i++;
    if (i == NUM_SAMPLES)
    {
      i = 0;
      // Calculate statistics for each axis of accelerometer and gyroscope
      calculate_statistics(data, NUM_SAMPLES);
      // Save statistics
      save_stats();

      if (neuton_model_set_inputs((input_t *)&stats) == 0)
      {
        uint16_t predictedClass;
        float *probabilities;

        if (neuton_model_run_inference(&predictedClass, &probabilities) == 0)
        {
          // code for handling prediction result
          Serial.print("Predicted CAR: ");
          switch (predictedClass)
          {
          case TARGET_IDLE:
            Serial.println("IDLE");
            Serial.print("Probability: ");
            Serial.println(probabilities[0]);
            break;
          case TARGET_FERRARI:
            Serial.println("FERRARI F1 CAR! P1!");
            Serial.print("Probability: ");
            Serial.println(probabilities[1]);
            break;
          case TARGET_HAAS:
            Serial.println("HAAS CAR! P12!");
            Serial.print("Probability: ");
            Serial.println(probabilities[2]);
            break;
          case TARGET_WILLIAMS:
            Serial.println("WILLIAMS CAR! P19!");
            Serial.print("Probability: ");
            Serial.println(probabilities[3]);
            break;
          default:
            Serial.println("UNKNOWN");
            break;
          }
        }
      }
    }
  }
}

void save_acc_data(float x, float y, float z)
{
  data[i].acc_x = x;
  data[i].acc_y = y;
  data[i].acc_z = z;
}

void save_gyro_data(float x, float y, float z)
{
  data[i].gyro_x = x;
  data[i].gyro_y = y;
  data[i].gyro_z = z;
}

void calculate_statistics(vector_t *data, int length)
{
  start = millis();

  // Calculate statistics for each axis of accelerometer and gyroscope
  accXStats.clear(); // explicitly start clean
  accYStats.clear();
  accZStats.clear();
  gyrXStats.clear();
  gyrYStats.clear();
  gyrZStats.clear();

  for (int i = 0; i < length; i++)
  {
    accXStats.add(data[i].acc_x);
    accYStats.add(data[i].acc_y);
    accZStats.add(data[i].acc_z);
    gyrXStats.add(data[i].gyro_x);
    gyrYStats.add(data[i].gyro_y);
    gyrZStats.add(data[i].gyro_z);
  }
  stop = millis();
}

void save_stats(void)
{
  stats.aXmin = accXStats.minimum();
  stats.aXmax = accXStats.maximum();
  stats.aXavg = accXStats.average();
  stats.aXvar = accXStats.variance();
  stats.aXstdev = accXStats.pop_stdev();
  stats.aXunbiasStdDev = accXStats.unbiased_stdev();
  stats.aYmin = accYStats.minimum();
  stats.aYmax = accYStats.maximum();
  stats.aYavg = accYStats.average();
  stats.aYvar = accYStats.variance();
  stats.aYstdev = accYStats.pop_stdev();
  stats.aYunbiasStdDev = accYStats.unbiased_stdev();
  stats.aZmin = accZStats.minimum();
  stats.aZmax = accZStats.maximum();
  stats.aZavg = accZStats.average();
  stats.aZvar = accZStats.variance();
  stats.aZstdev = accZStats.pop_stdev();
  stats.aZunbiasStdDev = accZStats.unbiased_stdev();
  stats.gXmin = gyrXStats.minimum();
  stats.gXmax = gyrXStats.maximum();
  stats.gXavg = gyrXStats.average();
  stats.gXvar = gyrXStats.variance();
  stats.gXstdev = gyrXStats.pop_stdev();
  stats.gXunbiasStdDev = gyrXStats.unbiased_stdev();
  stats.gYmin = gyrYStats.minimum();
  stats.gYmax = gyrYStats.maximum();
  stats.gYavg = gyrYStats.average();
  stats.gYvar = gyrYStats.variance();
  stats.gYstdev = gyrYStats.pop_stdev();
  stats.gYunbiasStdDev = gyrYStats.unbiased_stdev();
  stats.gZmin = gyrZStats.minimum();
  stats.gZmax = gyrZStats.maximum();
  stats.gZavg = gyrZStats.average();
  stats.gZvar = gyrZStats.variance();
  stats.gZstdev = gyrZStats.pop_stdev();
  stats.gZunbiasStdDev = gyrZStats.unbiased_stdev();
}