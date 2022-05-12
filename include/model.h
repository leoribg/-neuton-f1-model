#ifndef NEUTON_MODEL_MODEL_H
#define NEUTON_MODEL_MODEL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Model info */
#define NEUTON_MODEL_HEADER_VERSION 3
#define NEUTON_MODEL_QLEVEL 32
#define NEUTON_MODEL_FLOAT_SUPPORT 1
#define NEUTON_MODEL_TASK_TYPE 0  // multiclass classification
#define NEUTON_MODEL_NEURONS_COUNT 10
#define NEUTON_MODEL_WEIGHTS_COUNT 42
#define NEUTON_MODEL_INPUTS_COUNT 36
#define NEUTON_MODEL_INPUT_LIMITS_COUNT 36
#define NEUTON_MODEL_OUTPUTS_COUNT 4
#define NEUTON_MODEL_LOG_SCALE_OUTPUTS 0
#define NEUTON_MODEL_HAS_CLASSES_RATIO 0
#define NEUTON_MODEL_HAS_NEGPOS_RATIO 0

/* Preprocessing */
#define NEUTON_PREPROCESSING_ENABLED 0
#define NEUTON_DROP_ORIGINAL_FEATURES 0
#define NEUTON_BITMASK_ENABLED 1
#define NEUTON_INPUTS_IS_INTEGER 0
#define NEUTON_MODEL_SA_PRECISION 24

/* Types */
typedef float input_t;
typedef float extracted_feature_t;
typedef float coeff_t;
typedef float weight_t;
typedef double acc_signed_t;
typedef double acc_unsigned_t;
typedef uint8_t sources_size_t;
typedef uint8_t weights_size_t;
typedef uint8_t neurons_size_t;

/* Limits */
static const input_t modelInputMin[] = {
	-4, 0.059999999, -0.059999999, 0, 0, 0, -4, -0.02, -0.02, 0, 0, 0, -2.3299999,
	0.95999998, 0.87, 0, 0, 0, -135.62, -0.18000001, -1.58, 0.0099999998, 0.12,
	0.12, -89.050003, 1.22, -0.25999999, 0.0099999998, 0.07, 0.07, -188.96001,
	-0.31, -5.8299999, 0, 0.059999999, 0.059999999 };
static const input_t modelInputMax[] = {
	0.14, 4, 0.38999999, 7.8699999, 2.8, 2.8099999, 0.059999999, 2.26, 0.23999999,
	0.47999999, 0.69, 0.69, 0.95999998, 3.6199999, 1, 0.61000001, 0.77999997,
	0.77999997, -0.67000002, 125.79, 0.75, 670.09003, 25.889999, 25.940001,
	0.98000002, 86.239998, 2.9200001, 634.34003, 25.190001, 25.24, -0.49000001,
	197.57001, 5.1300001, 7422.3501, 86.150002, 86.330002 };

static const uint8_t modelUsedInputsMask[] = { 0xa9, 0xe9, 0x45, 0x5f, 0x04 };

/* Structure */
static const weight_t modelWeights[] = {
	0.27977434, -0.63884294, -1, -1, -1, 0, 1, -0.2403325, 0, -1, 0.5, -1,
	0, -1, 0.5, -0.93147761, -0.17791156, 0.3724964, -1, -0.22000568, 0.98254299,
	0.36793223, -0.24490245, 0.99999964, -0.97388673, -0.097841933, 0.90997314,
	-1, -0.5, 0.5, 0, -1, 1, 0, -1, -1, -0.5, -0.5, 1, -1, 0.99902344, 0.12076978 };

static const sources_size_t modelLinks[] = {
	7, 13, 22, 27, 34, 36, 0, 36, 0, 11, 18, 25, 36, 2, 36, 2, 3, 15, 16, 22,
	36, 0, 2, 5, 14, 30, 36, 4, 7, 14, 26, 4, 6, 36, 5, 8, 24, 28, 36, 5, 8,
	36 };

static const weights_size_t modelIntLinksBoundaries[] = {
	0, 7, 8, 14, 16, 23, 28, 33, 35, 41 };
static const weights_size_t modelExtLinksBoundaries[] = {
	6, 8, 13, 15, 21, 27, 31, 34, 39, 42 };

static const coeff_t modelFuncCoeffs[] = {
	40, 40, 40, 40, 40, 40, 30.025002, 40, 40, 40 };
static const uint8_t modelFuncTypes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const neurons_size_t modelOutputNeurons[] = { 1, 3, 7, 9 };

#ifdef __cplusplus
}
#endif

#endif // NEUTON_MODEL_MODEL_H

