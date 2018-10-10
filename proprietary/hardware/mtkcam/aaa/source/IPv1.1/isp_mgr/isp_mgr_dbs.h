/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#ifndef _ISP_MGR_DBS_H_
#define _ISP_MGR_DBS_H_

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  DBS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class ISP_MGR_DBS : public ISP_MGR_BASE_T
{
    typedef ISP_MGR_DBS    MyType;
private:
    MBOOL m_bEnable;
    MBOOL m_bCCTEnable;
    MINT32 m_u4IspAEGain;
    MUINT32 m_u4StartAddr;

    enum
    {
        ERegInfo_CAM_DBS_SIGMA,
        ERegInfo_CAM_DBS_BSTBL_0,
        ERegInfo_CAM_DBS_BSTBL_1,
        ERegInfo_CAM_DBS_BSTBL_2,
        ERegInfo_CAM_DBS_BSTBL_3,
        ERegInfo_CAM_DBS_CTL,
        ERegInfo_NUM
    };

    RegInfo_T m_rIspRegInfo[ERegInfo_NUM];

protected:
    ISP_MGR_DBS(ESensorDev_T const eSensorDev)
        : ISP_MGR_BASE_T(m_rIspRegInfo, ERegInfo_NUM, m_u4StartAddr, eSensorDev)
        , m_bEnable(MTRUE)
        , m_bCCTEnable(MTRUE)
        , m_u4IspAEGain(512)
        , m_u4StartAddr(REG_ADDR_P1(CAM_DBS_SIGMA))
    {
        // register info addr init
        INIT_REG_INFO_ADDR_P1(CAM_DBS_SIGMA);
        INIT_REG_INFO_ADDR_P1(CAM_DBS_BSTBL_0);
	    INIT_REG_INFO_ADDR_P1(CAM_DBS_BSTBL_1);
        INIT_REG_INFO_ADDR_P1(CAM_DBS_BSTBL_2);
        INIT_REG_INFO_ADDR_P1(CAM_DBS_BSTBL_3);
        INIT_REG_INFO_ADDR_P1(CAM_DBS_CTL);
    }

    virtual ~ISP_MGR_DBS() {}

public:
    static MyType&  getInstance(ESensorDev_T const eSensorDev);

public: // Interfaces.

    template <class ISP_xxx_T>
    MyType& put(ISP_xxx_T const& rParam);

    template <class ISP_xxx_T>
    MyType& get(ISP_xxx_T & rParam);

    MBOOL
    isEnable()
    {
        return m_bEnable;
    }

    MVOID
    setEnable(MBOOL bEnable)
    {
        m_bEnable = bEnable;
    }

    MBOOL
    isCCTEnable()
    {
        return m_bCCTEnable;
    }

    MVOID
    setCCTEnable(MBOOL bEnable)
    {
        m_bCCTEnable = bEnable;
    }

    MVOID setIspAEGain(MUINT32 u4IspAEGain)
    {
        m_u4IspAEGain = u4IspAEGain;
    }

    MVOID getIspAEGain(MUINT32 *u4IspAEGain)
    {
        *u4IspAEGain = m_u4IspAEGain;
    }

    MBOOL apply(EIspProfile_T eIspProfile, TuningMgr& rTuning, MINT32 i4SubsampleIdex=0);
} ISP_MGR_DBS_T;

template <ESensorDev_T const eSensorDev>
class ISP_MGR_DBS_DEV : public ISP_MGR_DBS_T
{
public:
    static
    ISP_MGR_DBS_T&
    getInstance()
    {
        static ISP_MGR_DBS_DEV<eSensorDev> singleton;
        return singleton;
    }
    virtual MVOID destroyInstance() {}

    ISP_MGR_DBS_DEV()
        : ISP_MGR_DBS_T(eSensorDev)
    {}

    virtual ~ISP_MGR_DBS_DEV() {}

};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  DBS2
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class ISP_MGR_DBS2 : public ISP_MGR_BASE_T
{
    typedef ISP_MGR_DBS2    MyType;
private:
    MBOOL m_bEnable;
    MBOOL m_bCCTEnable;
    MINT32 m_u4IspAEGain;
    MUINT32 m_u4StartAddr;

    enum
    {
        ERegInfo_DIP_X_DBS2_SIGMA,
        ERegInfo_DIP_X_DBS2_BSTBL_0,
        ERegInfo_DIP_X_DBS2_BSTBL_1,
        ERegInfo_DIP_X_DBS2_BSTBL_2,
        ERegInfo_DIP_X_DBS2_BSTBL_3,
        ERegInfo_DIP_X_DBS2_CTL,
        ERegInfo_NUM
    };

    RegInfo_T m_rIspRegInfo[ERegInfo_NUM];

protected:
    ISP_MGR_DBS2(ESensorDev_T const eSensorDev)
        : ISP_MGR_BASE_T(m_rIspRegInfo, ERegInfo_NUM, m_u4StartAddr, eSensorDev)
        , m_bEnable(MTRUE)
        , m_bCCTEnable(MTRUE)
        , m_u4IspAEGain(512)
        , m_u4StartAddr(REG_ADDR_P2(DIP_X_DBS2_SIGMA))
    {
        // register info addr init
        INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_SIGMA);
        INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_BSTBL_0);
	    INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_BSTBL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_BSTBL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_BSTBL_3);
        INIT_REG_INFO_ADDR_P2(DIP_X_DBS2_CTL);
    }

    virtual ~ISP_MGR_DBS2() {}

public:
    static MyType&  getInstance(ESensorDev_T const eSensorDev);

public: // Interfaces.

    template <class ISP_xxx_T>
    MyType& put(ISP_xxx_T const& rParam);

    template <class ISP_xxx_T>
    MyType& get(ISP_xxx_T & rParam);

    template <class ISP_xxx_T>
    MBOOL get(ISP_xxx_T & rParam, const dip_x_reg_t* pReg) const;

    MBOOL
    isEnable()
    {
        return m_bEnable;
    }

    MVOID
    setEnable(MBOOL bEnable)
    {
        m_bEnable = bEnable;
    }

    MBOOL
    isCCTEnable()
    {
        return m_bCCTEnable;
    }

    MVOID
    setCCTEnable(MBOOL bEnable)
    {
        m_bCCTEnable = bEnable;
    }

    MVOID setIspAEGain(MUINT32 u4IspAEGain)
    {
        m_u4IspAEGain = u4IspAEGain;
    }

    MVOID getIspAEGain(MUINT32 *u4IspAEGain)
    {
        *u4IspAEGain = m_u4IspAEGain;
    }

    MBOOL apply(EIspProfile_T eIspProfile, dip_x_reg_t* pReg);
} ISP_MGR_DBS2_T;

template <ESensorDev_T const eSensorDev>
class ISP_MGR_DBS2_DEV : public ISP_MGR_DBS2_T
{
public:
    static
    ISP_MGR_DBS2_T&
    getInstance()
    {
        static ISP_MGR_DBS2_DEV<eSensorDev> singleton;
        return singleton;
    }
    virtual MVOID destroyInstance() {}

    ISP_MGR_DBS2_DEV()
        : ISP_MGR_DBS2_T(eSensorDev)
    {}

    virtual ~ISP_MGR_DBS2_DEV() {}

};


#endif

