/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */


STATIC_METADATA2_BEGIN(DEVICE, SCALER, SENSOR_DRVNAME_OV5648_MIPI_RAW_TRULY)
//------------------------------------------------------------------------------
//  android.scaler
//------------------------------------------------------------------------------
    //==========================================================================
//    [ ANDROID_SCALER_CROP_REGION - ANDROID_SCALER_START ] =
//    { "cropRegion",                    TYPE_INT32  },
    //==========================================================================
    /*CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_FORMATS) //remove @ 3.2
        CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YV12, MINT32)         // YV12
        CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_Y8, MINT32)
        CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT32)
        CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCrCb_420_SP, MINT32) // NV21
        CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_422_I, MINT32) // YUY2
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_JPEG_MIN_DURATIONS)//remove @ 3.2
        CONFIG_ENTRY_VALUE(33331760L, MINT64)
    CONFIG_METADATA_END()*/
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_JPEG_SIZES)//remove @ 3.2
        CONFIG_ENTRY_VALUE(MSize(800,  600), MSize)
        CONFIG_ENTRY_VALUE(MSize(1600,  1200), MSize)
        CONFIG_ENTRY_VALUE(MSize(2560,  1920), MSize)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM)//
        CONFIG_ENTRY_VALUE(16, MFLOAT)
    CONFIG_METADATA_END()
    //==========================================================================
    /*CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_PROCESSED_MIN_DURATIONS)//remove @ 3.2
        CONFIG_ENTRY_VALUE(33331760L, MINT64)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_PROCESSED_SIZES)//remove @ 3.2
         CONFIG_ENTRY_VALUE(MSize(320,  240), MSize)
         CONFIG_ENTRY_VALUE(MSize(640,  480), MSize)
         CONFIG_ENTRY_VALUE(MSize(1280, 720), MSize)
         CONFIG_ENTRY_VALUE(MSize(1920, 1080), MSize)
         CONFIG_ENTRY_VALUE(MSize(3200, 2400), MSize)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_RAW_MIN_DURATIONS) //remove @ 3.2
        CONFIG_ENTRY_VALUE(33331760L, MINT64)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_RAW_SIZES)//remove @ 3.2
        CONFIG_ENTRY_VALUE(MSize(3200,2400), MSize)
    CONFIG_METADATA_END()*/
    //==========================================================================
    /*CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP)//new hidden
        CONFIG_ENTRY_VALUE( , MINT32)
    CONFIG_METADATA_END()*/
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS)//new hidden

#if 1
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT32)
                CONFIG_ENTRY_VALUE(1920, MINT32)
                CONFIG_ENTRY_VALUE(1088, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT32)
                CONFIG_ENTRY_VALUE(1280, MINT32)
                CONFIG_ENTRY_VALUE( 720, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)
#endif
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT32)
                CONFIG_ENTRY_VALUE( 640, MINT32)
                CONFIG_ENTRY_VALUE( 480, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT32)
                CONFIG_ENTRY_VALUE( 320, MINT32)
                CONFIG_ENTRY_VALUE( 240, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

#if 1
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE(1920, MINT32)
                CONFIG_ENTRY_VALUE(1080, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE(1280, MINT32)
                CONFIG_ENTRY_VALUE( 720, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE( 720, MINT32)
                CONFIG_ENTRY_VALUE( 480, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)
#endif
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE( 640, MINT32)
                CONFIG_ENTRY_VALUE( 480, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE( 352, MINT32)
                CONFIG_ENTRY_VALUE( 288, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT32)
                CONFIG_ENTRY_VALUE( 320, MINT32)
                CONFIG_ENTRY_VALUE( 240, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

#if 1
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE(1920, MINT32)
                CONFIG_ENTRY_VALUE(1080, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE(1280, MINT32)
                CONFIG_ENTRY_VALUE( 720, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)
#endif
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE( 720, MINT32)
                CONFIG_ENTRY_VALUE( 480, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE( 640, MINT32)
                CONFIG_ENTRY_VALUE( 480, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE( 352, MINT32)
                CONFIG_ENTRY_VALUE( 288, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT32)
                CONFIG_ENTRY_VALUE( 320, MINT32)
                CONFIG_ENTRY_VALUE( 240, MINT32)
                CONFIG_ENTRY_VALUE(MTK_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_OUTPUT, MINT32)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_MIN_FRAME_DURATIONS)//new hidden
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1088, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)


                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1080, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 352, MINT64)
                CONFIG_ENTRY_VALUE( 288, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)


                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1080, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 352, MINT64)
                CONFIG_ENTRY_VALUE( 288, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_AVAILABLE_STALL_DURATIONS)//new hidden
                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1088, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_BLOB, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(33333333, MINT64)


                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1080, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_YCbCr_420_888, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)


                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE(1920, MINT64)
                CONFIG_ENTRY_VALUE(1080, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE(1280, MINT64)
                CONFIG_ENTRY_VALUE( 720, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 640, MINT64)
                CONFIG_ENTRY_VALUE( 480, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)

                CONFIG_ENTRY_VALUE(HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED, MINT64)
                CONFIG_ENTRY_VALUE( 320, MINT64)
                CONFIG_ENTRY_VALUE( 240, MINT64)
                CONFIG_ENTRY_VALUE(   0, MINT64)
    CONFIG_METADATA_END()
    //==========================================================================
    /*CONFIG_METADATA_BEGIN(MTK_SCALER_STREAM_CONFIGURATION_MAP)//new synthetic
        CONFIG_ENTRY_VALUE( , MINT32)
    CONFIG_METADATA_END()*/
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_SCALER_CROPPING_TYPE)//new
        CONFIG_ENTRY_VALUE(MTK_SCALER_CROPPING_TYPE_CENTER_ONLY , MUINT8)
    CONFIG_METADATA_END()
    //==========================================================================
//    [ ANDROID_SCALER_MAX_DIGITAL_ZOOM - ANDROID_SCALER_START ] =
//    { "maxDigitalZoom",                TYPE_FLOAT  },
    //==========================================================================
//------------------------------------------------------------------------------
//  android.jpeg
//------------------------------------------------------------------------------
    CONFIG_METADATA_BEGIN(MTK_JPEG_AVAILABLE_THUMBNAIL_SIZES)//
        CONFIG_ENTRY_VALUE(MSize(0,   0), MSize)
        CONFIG_ENTRY_VALUE(MSize(160, 128), MSize)
        CONFIG_ENTRY_VALUE(MSize(320, 240), MSize)
        CONFIG_ENTRY_VALUE(MSize(480, 270), MSize)
    CONFIG_METADATA_END()
    //==========================================================================
    CONFIG_METADATA_BEGIN(MTK_JPEG_MAX_SIZE)//
        CONFIG_ENTRY_VALUE(2506752, MINT32) //1920x1088*2*0.6
    CONFIG_METADATA_END()
    //==========================================================================
//    [ ANDROID_JPEG_SIZE - ANDROID_JPEG_START ] =
//    { "size",                          TYPE_INT32  },
    //==========================================================================
//------------------------------------------------------------------------------
STATIC_METADATA_END()

