#ifndef OMNIVISION_SENSOR_CUSTOMDATA_H
#define OMNIVISION_SENSOR_CUSTOMDATA_H

/** @brief enumerations of Sensor Initialization phase Failure types */
typedef enum {
    SENSOR_INIT_ERROR_INVALID,                 /*!< Invalid Initialization phase error */
    SENSOR_OTP_CRC_ERR,                        /*!< OTP CRC error */
    SENSOR_ROM_CRC_ERR,                        /*!< ROM CRC error */
    SENSOR_MBIST_ERR,                          /*!< memory BIST error */
    SENSOR_I2C_READBACK_INIT_ERROR,            /*!< I2C SCCB Errors */

    SENSOR_MAX_INIT_FAILURE_TYPES              /*!< number of Initialization phase errors */
} SensorInitPhaseErrInfo;

/**
 * @brief Safety mechanism type for Sensor.
 */
typedef enum {

    /* Invalid SM */
    SENSOR_ERROR_INVALID,
    /*Sensor Errb Fault */
    SENSOR_ERRB_ERROR,
    /*Fault ASSERT*/
    SENSOR_ERROR,
    /*I2C Read back Fault */
    SENSOR_I2C_READBACK_ERROR,
    /*Online Pixel test Fault*/
    SENSOR_ONLINE_PIXEL_ERROR,
    /*Analog test pattern row Fault*/
    SENSOR_ANALOG_TEST_PATTERN_ROW_ERROR,
    /*Column-lD Fault*/
    SENSOR_COLUMN_ID_ERROR,
    /*ROW-lD Fault*/
    SENSOR_ROW_ID_ERROR,
    /*X-decoder checke Fault*/
    SENSOR_X_DECODER_CHECKER_ERROR,
    /*Voltage Monitor Fault*/
    SENSOR_VOLTAGE_MONITOR_ERROR,
    /*Digital SYNC Check Fault*/
    SENSOR_DIGITAL_SYNC_CHECK_ERROR,
    /*Digital test pattern rows checker Fault*/
    SENSOR_DIGITAL_ROW_CHECKER_ERROR,
    /*BLC Checker Fault*/
    SENSOR_BLC_CHECKER_ERROR,
    /*PLL CLOCK Monitor Checker Fault*/
    SENSOR_PLL_MONITOR_ERROR,
    /*PLL CLOCK UnLock state Fault*/
    SENSOR_PLL_UNLOCK_ERROR,
    /*VFIFO CRC Fault*/
    SENSOR_VFIFO_CRC_ERROR,
    /*SRAM CRC Fault*/
    SENSOR_GRF_ERROR,
    /*Temperature Sensor Fault*/
    SENSOR_TEMPERATURE_SENSOR_ERROR,
    /*Sensor EMB CRC ERROR*/
    SENSOR_EMB_CRC_ERROR,
    /*Sensor Temperture Over ERROR*/
    SENSOR_TEMPERATURE_OVER_ERROR,
    /*Sensor SCCB CRC ERROR*/
    SENSOR_SCCB_CRC_ERROR,
    /*Sensor I2C NACK ERROR*/
    SENSOR_I2C_NACK_ERROR,
    /* Max Sensor Error number */
    SENSOR_LIST_MAX_NUM
} SensorErr;

typedef struct {
    int32_t sensor_temperature;
    float dvdd_voltage;
    float dovdd_voltage;
    float avdd_voltage;
}SensorAnalogData;

/** @brief Parameter type used for GetErrorInformation() */
typedef struct {
    /** hold Sensor error */
    SensorErr SensError[SENSOR_LIST_MAX_NUM];
    /* hold Sensor analog data*/
    SensorAnalogData AnalogData;
    SensorInitPhaseErrInfo InitPhaseErrInfo[SENSOR_MAX_INIT_FAILURE_TYPES];
} SensorErrorInfo;


#endif /* end of OMNIVISION_SENSOR_CUSTOMDATA_H */
