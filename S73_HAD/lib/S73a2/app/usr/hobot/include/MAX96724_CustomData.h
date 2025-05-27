#ifndef MAX96724_CUSTOMDATA_H
#define MAX96724_CUSTOMDATA_H

/** Maximum number of supported links */
#define MAX96724_MAX_NUM_LINK                 4U
/** Maximum number of supported video pipelines */
#define MAX96724_NUM_VIDEO_PIPELINES          4U


/** @brief enumerations of deserializer Global Failure types GMSL non-link based global errors*/
typedef enum {
    MAX96724_GLOBAL_ERROR_INVALID,      /*!< Invalid global error */
    MAX96724_GLOBAL_ERR,                /*!< ERRB */
    MAX96724_GLOBAL_CMU_UNLOCK_ERR,     /*!< Clock Multiplier Unlocked error */
    MAX96724_GLOBAL_CSIDPLL0_UNLOCK,         /*!< CSIPLL0 UNLOCK*/
    MAX96724_GLOBAL_CSIDPLL1_UNLOCK,         /*!< CSIPLL1 UNLOCK*/
    MAX96724_GLOBAL_CSIDPLL2_UNLOCK,         /*!< CSIPLL2 UNLOCK*/
    MAX96724_GLOBAL_CSIDPLL3_UNLOCK,         /*!< CSIPLL3 UNLOCK*/
    MAX96724_GLOBAL_FRAME_SYNC,         /*!< Frame Sync error */
    MAX96724_GLOBAL_REMOTE_SIDE,        /*!< Remote Side error */
    MAX96724_GLOBAL_VID_PRBS,           /*!< Video PRBS error */
    MAX96724_GLOBAL_VID_LINE_CRC,       /*!< Video Line CRC error */
    MAX96724_GLOBAL_MEM_ECC1,           /*!< Memory ECC single bit error */
    MAX96724_GLOBAL_MEM_ECC2,           /*!< Memory ECC double bit error */
    MAX96724_GLOBAL_FSYNC_SYNC_LOSS,    /*!< FSYNC sync loss error */
    MAX96724_GLOBAL_FSYNC_STATUS,       /*!< FSYNC status */
    MAX96724_GLOBAL_CMP_VTERM_STATUS,   /*!< VTERM latched low and less than 1v */
    MAX96724_GLOBAL_VDDsw_OV_FLAG,      /*!< VDD_sw Over Voltage flag */
    MAX96724_GLOBAL_VDDsw_UV_FLAG,      /*!< VDD_sw Over Under Voltage flag */
    MAX96724_GLOBAL_VDDBAD_STATUS,      /*!< VDD Bad */
    MAX96724_GLOBAL_CMP_STATUS,         /*!< CMP Status */
    MAX96724_GLOBAL_VTERM_UV,           /*!< VTERM Under Voltage */
    MAX96724_GLOBAL_VTERM_OV,           /*!< VTERM Over Voltage */
    MAX96724_GLOBAL_VDDIO_UV,           /*!< VDDIO Under Voltage */
    MAX96724_GLOBAL_VDDIO_OV,           /*!< VDDIO Over Voltage */
    MAX96724_GLOBAL_VDD18_UV,           /*!< VDD18 Under Voltage */
    MAX96724_GLOBAL_VDD18_OV,           /*!< VDD18 Over Voltage */
    MAX96724_GLOBAL_I2C_COMMS_ERROR,    /*!< Max96724 I2C Communication failed*/

    MAX96724_MAX_GLOBAL_FAILURE_TYPES   /*!< number of global failure errors */
} GlobalFailureTypeMAX96724;

/** @brief enumerations of deserializer Link Failure types */
typedef enum {
    /* DO NOT re-order w/o checking */
    MAX96724_GMSL_LINK_ERROR_INVALID,           /*!< Invalid GMSL2 Link error */

    /* GMSL2 link based errors (cnt:7) */
    MAX96724_GMSL2_LINK_UNLOCK_ERR,             /*!< GMSL2 Link Unlock error */
    MAX96724_GMSL2_LINK_DEC_ERR,                /*!< GMSL2 Decoder error */
    MAX96724_GMSL2_LINK_IDLE_ERR,               /*!< GMSL2 Link Idle error */
    MAX96724_GMSL2_LINK_EOM_ERR,                /*!< GMSL2 Link EOM error */
    MAX96724_GMSL2_LINK_ARQ_RETRANS_ERR,        /*!< GMSL2 Link ARQ Retransmission error */
    MAX96724_GMSL2_LINK_MAX_RETRANS_ERR,        /*!< GMSL2 Link Max Retransmission error */
    MAX96724_GMSL2_LINK_VIDEO_PXL_CRC_ERR,      /*!< GMSL2 Video Pixel CRC error */
    MAX96724_GMSL2_LINK_LINE_FAULT,             /*!< GMSL2 Link Line Fault*/

    MAX96724_MAX_LINK_BASED_FAILURE_TYPES   /*!< number of link based errors */
} LinkFailureTypeMAX96724;

/** @brief enumerations of deserializer Line Failure types */
typedef enum {
    MAX96724_PIPELINE_ERROR_INVALID,            /*!< Invalid pipeline error */

    /* GMSL pipeline based errors (cnt:6) */
    MAX96724_PIPELINE_LMO_OVERFLOW_ERR,         /*!< Line Memory Overflow Error */
    MAX96724_PIPELINE_CMD_OVERFLOW_ERR,         /*!< Command Overflow Error */
    MAX96724_PIPELINE_MEM_ERR,                  /*!< Memory Error */
    MAX96724_PIPELINE_VID_SEQ_ERR,              /*!< Video Pipeline Sequence Error */
    MAX96724_PIPELINE_LCRC_ERR,                 /*!< Video line CRC Error */
    MAX96724_PIPELINE_SEQ_ERR,                  /*!< Video Rx Error */

    MAX96724_MAX_PIPELINE_FAILURE_TYPES         /*!< number of pipeline errors */
} PipelineFailureTypeMAX96724;

/** @brief enumerations of deserializer Initialization phase Failure types */
typedef enum {
    MAX96724_INIT_ERROR_INVALID,            /*!< Invalid Initialization phase error */

    MAX96724_LOCK_PIN_OPEN_DETECT_ERR,         /*!< Lock pin open detect error */
    MAX96724_ERRB_PIN_OPEN_DETECT_ERR,         /*!< ERRB pin open detect error */
    MAX96724_SIOA_ERR_PIN_OPEN_DETECT_ERR,     /*!< SIOA ERR pin open detect error */
    MAX96724_SIOB_ERR_PIN_OPEN_DETECT_ERR,     /*!< SIOB ERR pin open detect error */
    MAX96724_SIOC_ERR_PIN_OPEN_DETECT_ERR,     /*!< SIOC ERR pin open detect error */
    MAX96724_SIOD_ERR_PIN_OPEN_DETECT_ERR,     /*!< SIOD ERR pin open detect error */

    MAX96724_CMP_VTERM_STATUS,   /*!< VTERM latched low and less than 1v */
    MAX96724_VDDsw_OV_FLAG,      /*!< VDD_sw Over Voltage flag */
    MAX96724_VDDsw_UV_FLAG,      /*!< VDD_sw Over Under Voltage flag */
    MAX96724_VDDBAD_STATUS,      /*!< VDD Bad */
    MAX96724_CMP_STATUS,         /*!< CMP Status */
    MAX96724_VTERM_UV,           /*!< VTERM Under Voltage */
    MAX96724_VTERM_OV,           /*!< VTERM Over Voltage */
    MAX96724_VDDIO_UV,           /*!< VDDIO Under Voltage */
    MAX96724_VDDIO_OV,           /*!< VDDIO Over Voltage */
    MAX96724_VDD18_UV,           /*!< VDD18 Under Voltage */
    MAX96724_VDD18_OV,           /*!< VDD18 Over Voltage */
    MAX96724_EFUSE_CRC,          /*!< Efuse CRC error */

    MAX96724_GMSL2_LINKA_DEC_ERR,                /*!< GMSL2 LINKA Decoder error */
    MAX96724_GMSL2_LINKB_DEC_ERR,                /*!< GMSL2 LINKB Decoder error */
    MAX96724_GMSL2_LINKC_DEC_ERR,                /*!< GMSL2 LINKC Decoder error */
    MAX96724_GMSL2_LINKD_DEC_ERR,                /*!< GMSL2 LINKD Decoder error */

    MAX96724_GMSL2_LINKA_IDLE_ERR,               /*!< GMSL2 LINKA Idle error */
    MAX96724_GMSL2_LINKB_IDLE_ERR,               /*!< GMSL2 LINKB Idle error */
    MAX96724_GMSL2_LINKC_IDLE_ERR,               /*!< GMSL2 LINKC Idle error */
    MAX96724_GMSL2_LINKD_IDLE_ERR,               /*!< GMSL2 LINKD Idle error */

    MAX96724_MAX_INIT_FAILURE_TYPES            /*!< number of Initialization phase errors */
} InitPhaseFailureTypeMAX96724;

/** @brief Parameter type used for GetErrorInformation() */
typedef struct {
    /** hold global failure types */
    GlobalFailureTypeMAX96724 globalFailureType[MAX96724_MAX_GLOBAL_FAILURE_TYPES];

    /** Output param, hold pipeline failure types */
    PipelineFailureTypeMAX96724 pipelineFailureType[MAX96724_NUM_VIDEO_PIPELINES][MAX96724_MAX_PIPELINE_FAILURE_TYPES];

    /** Output param, hold link failure types */
    LinkFailureTypeMAX96724 linkFailureType[MAX96724_MAX_NUM_LINK][MAX96724_MAX_LINK_BASED_FAILURE_TYPES];

    /** Output param, hold deserializer Initialization phase **/
    InitPhaseFailureTypeMAX96724 InitPhaseFailureType[MAX96724_MAX_INIT_FAILURE_TYPES];
} ErrorStatusMAX96724;

#endif /* end of MAX96724_CUSTOMDATA_H */
