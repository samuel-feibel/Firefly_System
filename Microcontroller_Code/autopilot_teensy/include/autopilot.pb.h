/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6-dev */

#ifndef PB_AUTOPILOT_PB_H_INCLUDED
#define PB_AUTOPILOT_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _BarometerStruct { 
    float pressure; 
    float temperature; 
    float alt; 
    bool hasLinearized; 
} BarometerStruct;

/* Individual Sensors */
typedef struct _GPSStruct { 
    float lat; 
    float lon; 
    float alt; 
    float groundSpeed; 
    float SIV; 
    float heading; 
    float position_NED[3]; 
    int32_t year; 
    int32_t month; 
    int32_t day; 
    int32_t hour; 
    int32_t minute; 
    int32_t second; 
    int32_t msec; 
    bool hasLinearized; 
} GPSStruct;

typedef struct _IMUStruct { 
    float acc[3]; 
    float gyr[3]; 
    float mag[3]; 
    float rawMag[3]; 
    float rawGyr[3]; 
} IMUStruct;

/* Modes */
typedef struct _ModeStruct { 
    int32_t auxMode; 
    int32_t autoMode; 
} ModeStruct;

/* State Estimator */
typedef struct _StateEstimatorStruct { 
    float xhat[10]; 
    float P[10]; 
} StateEstimatorStruct;

/* Statuses */
typedef struct _StatusStruct { 
    bool SD; 
    bool Transmitter; 
} StatusStruct;

/* Combine Sensors */
typedef struct _SensorStruct { 
    bool has_GPS;
    GPSStruct GPS; 
    bool has_IMU;
    IMUStruct IMU; 
    bool has_baro;
    BarometerStruct baro; 
    float z_input[6]; 
    float z[9]; 
} SensorStruct;

/* Plane Object is highest */
typedef struct _PlaneBuf { 
    float delt; 
    bool has_sensors;
    SensorStruct sensors; 
    bool has_stateEstimator;
    StateEstimatorStruct stateEstimator; 
    bool has_status;
    StatusStruct status; 
    bool has_mode;
    ModeStruct mode; 
    float mcTime; 
} PlaneBuf;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define GPSStruct_init_default                   {0, 0, 0, 0, 0, 0, {0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0}
#define IMUStruct_init_default                   {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
#define BarometerStruct_init_default             {0, 0, 0, 0}
#define SensorStruct_init_default                {false, GPSStruct_init_default, false, IMUStruct_init_default, false, BarometerStruct_init_default, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define StateEstimatorStruct_init_default        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define StatusStruct_init_default                {0, 0}
#define ModeStruct_init_default                  {0, 0}
#define PlaneBuf_init_default                    {0, false, SensorStruct_init_default, false, StateEstimatorStruct_init_default, false, StatusStruct_init_default, false, ModeStruct_init_default, 0}
#define GPSStruct_init_zero                      {0, 0, 0, 0, 0, 0, {0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0}
#define IMUStruct_init_zero                      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
#define BarometerStruct_init_zero                {0, 0, 0, 0}
#define SensorStruct_init_zero                   {false, GPSStruct_init_zero, false, IMUStruct_init_zero, false, BarometerStruct_init_zero, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define StateEstimatorStruct_init_zero           {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define StatusStruct_init_zero                   {0, 0}
#define ModeStruct_init_zero                     {0, 0}
#define PlaneBuf_init_zero                       {0, false, SensorStruct_init_zero, false, StateEstimatorStruct_init_zero, false, StatusStruct_init_zero, false, ModeStruct_init_zero, 0}

/* Field tags (for use in manual encoding/decoding) */
#define BarometerStruct_pressure_tag             1
#define BarometerStruct_temperature_tag          2
#define BarometerStruct_alt_tag                  3
#define BarometerStruct_hasLinearized_tag        4
#define GPSStruct_lat_tag                        1
#define GPSStruct_lon_tag                        2
#define GPSStruct_alt_tag                        3
#define GPSStruct_groundSpeed_tag                4
#define GPSStruct_SIV_tag                        5
#define GPSStruct_heading_tag                    6
#define GPSStruct_position_NED_tag               7
#define GPSStruct_year_tag                       8
#define GPSStruct_month_tag                      9
#define GPSStruct_day_tag                        10
#define GPSStruct_hour_tag                       11
#define GPSStruct_minute_tag                     12
#define GPSStruct_second_tag                     13
#define GPSStruct_msec_tag                       14
#define GPSStruct_hasLinearized_tag              15
#define IMUStruct_acc_tag                        1
#define IMUStruct_gyr_tag                        2
#define IMUStruct_mag_tag                        3
#define IMUStruct_rawMag_tag                     4
#define IMUStruct_rawGyr_tag                     5
#define ModeStruct_auxMode_tag                   1
#define ModeStruct_autoMode_tag                  2
#define StateEstimatorStruct_xhat_tag            1
#define StateEstimatorStruct_P_tag               2
#define StatusStruct_SD_tag                      1
#define StatusStruct_Transmitter_tag             2
#define SensorStruct_GPS_tag                     1
#define SensorStruct_IMU_tag                     2
#define SensorStruct_baro_tag                    3
#define SensorStruct_z_input_tag                 4
#define SensorStruct_z_tag                       5
#define PlaneBuf_delt_tag                        1
#define PlaneBuf_sensors_tag                     2
#define PlaneBuf_stateEstimator_tag              3
#define PlaneBuf_status_tag                      4
#define PlaneBuf_mode_tag                        5
#define PlaneBuf_mcTime_tag                      6

/* Struct field encoding specification for nanopb */
#define GPSStruct_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    lat,               1) \
X(a, STATIC,   SINGULAR, FLOAT,    lon,               2) \
X(a, STATIC,   SINGULAR, FLOAT,    alt,               3) \
X(a, STATIC,   SINGULAR, FLOAT,    groundSpeed,       4) \
X(a, STATIC,   SINGULAR, FLOAT,    SIV,               5) \
X(a, STATIC,   SINGULAR, FLOAT,    heading,           6) \
X(a, STATIC,   FIXARRAY, FLOAT,    position_NED,      7) \
X(a, STATIC,   SINGULAR, INT32,    year,              8) \
X(a, STATIC,   SINGULAR, INT32,    month,             9) \
X(a, STATIC,   SINGULAR, INT32,    day,              10) \
X(a, STATIC,   SINGULAR, INT32,    hour,             11) \
X(a, STATIC,   SINGULAR, INT32,    minute,           12) \
X(a, STATIC,   SINGULAR, INT32,    second,           13) \
X(a, STATIC,   SINGULAR, INT32,    msec,             14) \
X(a, STATIC,   SINGULAR, BOOL,     hasLinearized,    15)
#define GPSStruct_CALLBACK NULL
#define GPSStruct_DEFAULT NULL

#define IMUStruct_FIELDLIST(X, a) \
X(a, STATIC,   FIXARRAY, FLOAT,    acc,               1) \
X(a, STATIC,   FIXARRAY, FLOAT,    gyr,               2) \
X(a, STATIC,   FIXARRAY, FLOAT,    mag,               3) \
X(a, STATIC,   FIXARRAY, FLOAT,    rawMag,            4) \
X(a, STATIC,   FIXARRAY, FLOAT,    rawGyr,            5)
#define IMUStruct_CALLBACK NULL
#define IMUStruct_DEFAULT NULL

#define BarometerStruct_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    pressure,          1) \
X(a, STATIC,   SINGULAR, FLOAT,    temperature,       2) \
X(a, STATIC,   SINGULAR, FLOAT,    alt,               3) \
X(a, STATIC,   SINGULAR, BOOL,     hasLinearized,     4)
#define BarometerStruct_CALLBACK NULL
#define BarometerStruct_DEFAULT NULL

#define SensorStruct_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  GPS,               1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  IMU,               2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  baro,              3) \
X(a, STATIC,   FIXARRAY, FLOAT,    z_input,           4) \
X(a, STATIC,   FIXARRAY, FLOAT,    z,                 5)
#define SensorStruct_CALLBACK NULL
#define SensorStruct_DEFAULT NULL
#define SensorStruct_GPS_MSGTYPE GPSStruct
#define SensorStruct_IMU_MSGTYPE IMUStruct
#define SensorStruct_baro_MSGTYPE BarometerStruct

#define StateEstimatorStruct_FIELDLIST(X, a) \
X(a, STATIC,   FIXARRAY, FLOAT,    xhat,              1) \
X(a, STATIC,   FIXARRAY, FLOAT,    P,                 2)
#define StateEstimatorStruct_CALLBACK NULL
#define StateEstimatorStruct_DEFAULT NULL

#define StatusStruct_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     SD,                1) \
X(a, STATIC,   SINGULAR, BOOL,     Transmitter,       2)
#define StatusStruct_CALLBACK NULL
#define StatusStruct_DEFAULT NULL

#define ModeStruct_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    auxMode,           1) \
X(a, STATIC,   SINGULAR, INT32,    autoMode,          2)
#define ModeStruct_CALLBACK NULL
#define ModeStruct_DEFAULT NULL

#define PlaneBuf_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    delt,              1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  sensors,           2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  stateEstimator,    3) \
X(a, STATIC,   OPTIONAL, MESSAGE,  status,            4) \
X(a, STATIC,   OPTIONAL, MESSAGE,  mode,              5) \
X(a, STATIC,   SINGULAR, FLOAT,    mcTime,            6)
#define PlaneBuf_CALLBACK NULL
#define PlaneBuf_DEFAULT NULL
#define PlaneBuf_sensors_MSGTYPE SensorStruct
#define PlaneBuf_stateEstimator_MSGTYPE StateEstimatorStruct
#define PlaneBuf_status_MSGTYPE StatusStruct
#define PlaneBuf_mode_MSGTYPE ModeStruct

extern const pb_msgdesc_t GPSStruct_msg;
extern const pb_msgdesc_t IMUStruct_msg;
extern const pb_msgdesc_t BarometerStruct_msg;
extern const pb_msgdesc_t SensorStruct_msg;
extern const pb_msgdesc_t StateEstimatorStruct_msg;
extern const pb_msgdesc_t StatusStruct_msg;
extern const pb_msgdesc_t ModeStruct_msg;
extern const pb_msgdesc_t PlaneBuf_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define GPSStruct_fields &GPSStruct_msg
#define IMUStruct_fields &IMUStruct_msg
#define BarometerStruct_fields &BarometerStruct_msg
#define SensorStruct_fields &SensorStruct_msg
#define StateEstimatorStruct_fields &StateEstimatorStruct_msg
#define StatusStruct_fields &StatusStruct_msg
#define ModeStruct_fields &ModeStruct_msg
#define PlaneBuf_fields &PlaneBuf_msg

/* Maximum encoded size of messages (where known) */
#define BarometerStruct_size                     17
#define GPSStruct_size                           124
#define IMUStruct_size                           75
#define ModeStruct_size                          22
#define PlaneBuf_size                            442
#define SensorStruct_size                        297
#define StateEstimatorStruct_size                100
#define StatusStruct_size                        4

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
