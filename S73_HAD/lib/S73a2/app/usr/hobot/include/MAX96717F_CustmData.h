#ifndef MAX96717F_CUSTOMDATA_H
#define MAX96717F_CUSTOMDATA_H

#include <stdint.h>

/** Maximum number of supported errors */
#define MAX96717F_MAX_ERROR_NUM       24U
/** Maximum number of supported link errors */
#define MAX96717F_MAX_SM_NUM          40U

/** @brief enumerations of serializer Initialization phase Failure types */
typedef enum {
    MAX96717F_INIT_ERROR_INVALID,            /*!< Invalid Initialization phase error */

    MAX96717F_VMERRB_PIN_OPEN_DETECT_ERR,         /*!< VMERRB pin open detect error */
    MAX96717F_ERRB_PIN_OPEN_DETECT_ERR,           /*!< ERRB pin open detect error */
    MAX96717F_PMIC_RESET_PIN_OPEN_DETECT_ERR,     /*!< PMIC RESET pin open detect error */
    MAX96717F_ADC_BIST,                           /*!< ADC BIST Errors */
    MAX96717F_LOGIC_BIST,                         /*!< Logic BIST */
    MAX96717F_MEMORY_BIST,                        /*!< Memory BIST */
    MAX96717F_CRC_OF_NONVOLATILE_MEMORY,          /*!< Efuse CRC error */
    MAX96717F_SELFTEST_OF_TEMPERATURE_SENSOR,    /*!< Temperature sensor selftest*/

    /* MAX96717F SM15 Voltage measurement and monitoring */
    MAX96717F_VDDCMP_UV_FLAG,
    MAX96717F_PORZ_UV_FLAG,
    MAX96717F_VDDBAD_INT_FLAG,

    /* MAX96717F SM27 Configuration register CRC */
    MAX96717F_CONFIGURATION_REGISTER_CRC,
    /* MAX96717F SM31 DPLL unlock indicator*/
    MAX96717F_DPLL_UNLOCK_INDICATOR,
    /* MAX96717F SM36 Info frame sent periodically */
    MAX96717F_DECODE_ERROR,
    /* MAX96717F SM36 Info frame sent periodically */
    MAX96717F_IDLE_ERROR,

    MAX96717F_MAX_INIT_FAILURE_TYPES             /*!< number of Initialization phase errors */
} InitPhaseFailureTypeMAX96717F;

/**
 * @brief Safety mechanism type for MAX96717F Serializer.
 */
typedef enum {

    /* Invalid SM */
    SM_INVALID,
    /* MAX96717F SM1 Bist for serial link */
    SM01_BIST_FOR_SERIAL_LINK,
    /* MAX96717F SM2 Line fault detection on serializer output */
    SM02_LINE_FAULT_DETECTION_ON_SERIALIZER_OUTPUT,
    /* MAX96717F SM3 CRC for control channel */
    SM03_CRC_FOR_CONTROL_CHANNEL,
    /* MAX96717F SM4 CRC for forward channel */
    SM04_CRC_FOR_FORWARD_CHANNEL,
    /* MAX96717F SM5 Error correction through retransmission for control channel */
    SM05_ERROR_CORRECTION_THROUGH_RETRANSMISSION,
    /* MAX96717F SM6 Lock indicator for forward channel */
    SM06_LOCK_INDICATOR_OF_FORWARD_CHANNEL,
    /* MAX96717F SM7 ERRB indicator for forward channel */
    SM07_ERRB_INDICATOR_OF_FORWARD_CHANNEL,
    /* MAX96717F SM8 Lock indicator for reverse channel */
    SM08_LOCK_INDICATOR_OF_REVERSE_CHANNEL,
    /* MAX96717F SM9 ERRB indicator for reverse channel */
    SM09_ERRB_INDICATOR_OF_REVERSE_CHANNEL,
    /* MAX96717F SM10 Error generator */
    SM10_ERROR_GENERATOR,
    /* MAX96717F SM11 Video sequence number */
    SM11_VIDEO_SEQUENCE_NUMBER,
    /* MAX96717F SM12 Acknowledge of UART or I2C */
    SM12_ACKNOWLEDGE_OF_UART_I2C,
    /* MAX96717F SM14 Eye opening monitor */
    SM14_EYE_OPENING_MONITOR,
    /* MAX96717F SM15 Voltage measurement and monitoring */
    SM15_VDDCMP_UV_FLAG,
    SM15_PORZ_UV_FLAG,
    SM15_VDDBAD_INT_FLAG,
    /* MAX96717F SM16 Evaluate CSI-2 ECC/CRC */
    SM16_EVALUATE_CSI2_ECC_CRC,
    /* MAX96717F SM17 FIFO Overflow detection */
    SM17_FIFO_OVERFLOW_DETECTION,
    /* MAX96717F SM20 End to end CRC */
    SM20_END_TO_END_CRC_DURING_VIDEO_TRANSMISSION,
    /* MAX96717F SM21 CRC on UART and I2C transactions */
    SM21_CRC_ON_I2C_UART_TRANSACTIONS,
    /* MAX96717F SM22 Message counter */
    SM22_MESSAGE_COUNTER,
    /* MAX96717F SM23 GPO Readback */
    SM23_GPO_READBACK,
    /*!< MAX96717F SM24 Over Temperature*/
    SM24_SENSOR_OT_ERROR,
    /*!< MAX96717F SM24 Under Temperature */
    SM24_SENSOR_UT_ERROR,
    /* MAX96717F SM26 Memory-2bit ECC */
    SM26_MEMORY_2BIT_ECC,
    /* MAX96717F SM26 Memory-1bit ECC */
    SM26_MEMORY_1BIT_ECC,
    /* MAX96717F SM27 Configuration register CRC */
    SM27_CONFIGURATION_REGISTER_CRC,
    /*!< MAX96717F SM28 Temperature sensor selftest*/
    SM28_SELFTEST_OF_TEMPERATURE_SENSOR,
    /* MAX96717F SM30 Self clearing unlock register */
    SM30_SELF_CLEARING_UNLOCK_REGISTER,
    /* MAX96717F SM31 DPLL unlock indicator*/
    SM31_DPLL_UNLOCK_INDICATOR,
    /* MAX96717F SM32 Video detect */
    SM32_VIDEO_DETECT,
    /* MAX96717F SM33 9b/10b illegal symbol check */
    SM33_ILLEGAL_SYMBOL_CHECKING_RUNNING_DISPARITY,
    /* MAX96717F SM34 Packet counter for GPIO, I2C, SPI and UART */
    SM34_PACKET_COUNTER_FOR_GPIO_I2C_SPI_UART,
    /* MAX96717F SM35 I2C Timeout verification on I2C */
    SM35_I2C_TIMEOUT_VERIFICATION_ON_I2C,
    /* MAX96717F SM36 Info frame sent periodically */
    SM36_DECODE_ERROR,
    /* MAX96717F SM36 Info frame sent periodically */
    SM36_IDLE_ERROR,
    /* MAX96717F SM37 CRC on configuration data for data retention memory */
    SM37_CRC_ON_CONFIGURATION_DATA,
    /* MAX96717F SM40 GPIO open detection */
    SM40_GPIO_OPEN_DETECTION,
    /* MAX96717F Max SM number */
    SM_LIST_MAX_NUM,
} MAX96717FSMErrIndex;

typedef struct {
    int32_t junction_temperature;
}MAX96717FAnalogData;

/** @brief Parameter type used for GetErrorInformation() */
typedef struct {
    InitPhaseFailureTypeMAX96717F SerInitErr[MAX96717F_MAX_INIT_FAILURE_TYPES];
    /** hold Serializer error index */
    MAX96717FSMErrIndex SerErrIndex[SM_LIST_MAX_NUM];
    /* hold serializer analog data*/
    MAX96717FAnalogData AnalogData;
} MAX96717FErrorInfo;


#endif /* end of MAX96717F_CUSTOMDATA_H */