/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2024 Bosch, Inc.
 *                   All rights reserved.
 ***/
#ifndef BOSCH_DEF_H_
#define BOSCH_DEF_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool isLockPinAsserted;     // Bool value. Set to true if deserializer lock pin asserted.
    uint8_t linkEnableMask;     // Mask for link enable state. bit [0:3] means link enable status.1: link enable, 0:link disable.
    uint8_t lockStatus;         // For each bit, 0: not locked, 1: locked. [0:3]: Link Lock, [4:7] Video Lock
} DeserializerLockStatus;

typedef enum {
    MAX96793_BYPASS,
    MAX96717_IDU0,
    MAX96717_IDU1,
    MAX_LOCAL_SERIALIZER
}LocalSerializerType;

typedef enum {
    CMD_GET_VOLTAGE_CURRENT,    ///< Retrieves the voltage value of channel
    CMD_GET_CHANNEL_STATE,    ///< Retrieves the power swicth channel state
    CMD_GET_POC_REGISTER,     //Get poc register
    CMD_SET_POC_REGISTER,     //Set poc register
} POCCommandType;
typedef struct{
    float link_voltage;     // Voltage at the link
    float link_current;     // Current at the link
} OutputChannelValue;

typedef struct{
    float vina_voltage;     // Voltage at VINA
    float vinb_voltage;     // Voltage at VINB
    float vdd_voltage;      // Voltage at VDD
} InputChannelValue;


typedef struct {
    OutputChannelValue outch_values;    // Output channel values
    InputChannelValue inch_values;      // Input channel values
} ChannelVoltageCurrentValue;

typedef struct {
    uint8_t outch_state[2];  ///< State of the output channel, outch_state[0]：bit[0:3]:SC state LinkA-LinkD, bit[4:7]:OT state for LinkA~LinkD. outch_state[1]:bit[0:3] OV state for LinkA~LinkD, bit[4:7] TW state for LinkA~LinkD
    uint8_t inch_state;  ///< State of the input channel，bit[0:4]: VINA_OV、VINA_UV、VINB_OV、VINB_UV、VDD_OV
} PSChannelState;

typedef struct {
	bool isErrbAsserted;        // Bool value. Set to true if deserializer errb asserted.
	bool isRemoteError;         // Bool value. Set to true if remote serializer error detected.
	uint16_t linkErrorMask;     // Mask for link error state. Valid range: [0x0000, 0x1111].
} DeserializerErrbStatus;

typedef struct {
	bool isSnrErrbAsserted;     //Bool value. Sensor errb asserted
	bool isSerErrbAsserted;     //Bool value. Serializer errb asserted
	bool isPoCErrbAsserted;     //Bool value. PMIC errb asserted
} CameraModuleErrbStatus;

typedef struct {
    uint8_t fault_0;
    uint8_t fault_1;
    uint8_t fault_2;
} CameraSensorErrors;

typedef enum {
	DEVICE_TYPE_SENSOR = 0,
	DEVICE_TYPE_SERIALIZER,
	DEVICE_TYPE_DESERILIZER,
	DEVICE_TYPE_POWERSWITCH,
	DEVICE_TYPE_IDU_SERIALIZER,
} DeviceType;

typedef struct {
    uint8_t* errorBuffer;
    size_t bufferSize;
    size_t sizeWritten;
} ErrorDetails;

typedef enum {
    CAM_MODULE_ERROR_READ_SENSOR,
    CAM_MODULE_ERROR_READ_SERIALIZER,
    CAM_MODULE_ERROR_READ_ALL,
} ModuleErrorReadFlag;

#ifdef __cplusplus
}
#endif

#endif // BOSCH_DEF_H_