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
 * MediaTek Inc. (C) 2015. All rights reserved.
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


package com.mediatek.bluetoothgatt.profile;

// Customized Start: Import ........................................................................
import android.content.Context;
import android.util.Log;

import com.mediatek.bluetoothgatt.GattUuid;
import com.mediatek.bluetoothgatt.characteristic.CharacteristicBase;
import com.mediatek.bluetoothgatt.service.Dis;
import com.mediatek.bluetoothgatt.service.Rscs;
//........................................................................ Customized End: Import //

/**
 * Public API for the GATT Running Speed and Cadence Profile(Server).
 *
 * Name: Running Speed and Cadence
 * Type: org.bluetooth.profile.running_speed_and_cadence
 * Last Modified: None
 * Revision: None
 * Role: RscSensor
 */
public class RscpRscSensor extends ServerBase {
    private static final boolean DBG = true;
    private static final String TAG = "RscpRscSensor";

    /**
     * Create a RscpRscSensor object and init value.
     *
     * @param context App context
     */
    public RscpRscSensor(Context context) {
        super(context);

        if (DBG) {
            Log.d(TAG, "RscpRscSensor()");
        }
    }

    @Override
    protected void loadServicesConfig() {
        addService(new Rscs());
        addService(new Dis());
        cfgService(GattUuid.SRVC_RSCS).setSupport(true);
        cfgService(GattUuid.SRVC_DIS).setSupport(false);
        cfgCharacteristic(GattUuid.SRVC_DIS, GattUuid.CHAR_MANUFACTURER_NAME_STRING)
                .setSupport(false);
        cfgCharacteristic(GattUuid.SRVC_DIS, GattUuid.CHAR_MODEL_NUMBER_STRING)
                .setSupport(false);
    }

    /**
     * Send a notification or indication that a local characteristic has been
     * updated.
     *
     * @param characteristic The local characteristic that has been updated
     */
    public void notifyRscsRscMeasurement(
            CharacteristicBase characteristic) {
        if (DBG) {
            Log.d(TAG, "notifyRscsRscMeasurement()");
        }

        notify(GattUuid.SRVC_RSCS,
                GattUuid.CHAR_RSC_MEASUREMENT,
                characteristic.getValue());
    }

    /**
     * Send a notification or indication that a local characteristic has been
     * updated.
     *
     * @param characteristic The local characteristic that has been updated
     */
    public void notifyRscsScControlPoint(
            CharacteristicBase characteristic) {
        if (DBG) {
            Log.d(TAG, "notifyRscsScControlPoint()");
        }

        notify(GattUuid.SRVC_RSCS,
                GattUuid.CHAR_SC_CONTROL_POINT,
                characteristic.getValue());
    }

}
