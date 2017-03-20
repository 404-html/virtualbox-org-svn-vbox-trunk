/* $Id$ */
/** @file
 * VBox Qt GUI - UIMachineSettingsDisplay class declaration.
 */

/*
 * Copyright (C) 2008-2016 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifndef __UIMachineSettingsDisplay_h__
#define __UIMachineSettingsDisplay_h__

/* GUI includes: */
#include "UISettingsPage.h"
#include "UIMachineSettingsDisplay.gen.h"

/* COM includes: */
#include "CGuestOSType.h"

/* Forward declarations: */
class UIActionPool;

/* Machine settings / Display page / Data: */
struct UIDataSettingsMachineDisplay
{
    /* Constructor: */
    UIDataSettingsMachineDisplay()
        : m_iCurrentVRAM(0)
        , m_cGuestScreenCount(0)
        , m_dScaleFactor(1.0)
#ifdef VBOX_WS_MAC
        , m_fUseUnscaledHiDPIOutput(false)
#endif /* VBOX_WS_MAC */
        , m_f3dAccelerationEnabled(false)
#ifdef VBOX_WITH_VIDEOHWACCEL
        , m_f2dAccelerationEnabled(false)
#endif /* VBOX_WITH_VIDEOHWACCEL */
        , m_fRemoteDisplayServerSupported(false)
        , m_fRemoteDisplayServerEnabled(false)
        , m_strRemoteDisplayPort(QString())
        , m_remoteDisplayAuthType(KAuthType_Null)
        , m_uRemoteDisplayTimeout(0)
        , m_fRemoteDisplayMultiConnAllowed(false)
        , m_fVideoCaptureEnabled(false)
        , m_strVideoCaptureFolder(QString())
        , m_strVideoCaptureFilePath(QString())
        , m_iVideoCaptureFrameWidth(0)
        , m_iVideoCaptureFrameHeight(0)
        , m_iVideoCaptureFrameRate(0)
        , m_iVideoCaptureBitRate(0)
    {}

    /* Functions: */
    bool equal(const UIDataSettingsMachineDisplay &other) const
    {
        return (m_iCurrentVRAM == other.m_iCurrentVRAM) &&
               (m_cGuestScreenCount == other.m_cGuestScreenCount) &&
               (m_dScaleFactor == other.m_dScaleFactor) &&
#ifdef VBOX_WS_MAC
               (m_fUseUnscaledHiDPIOutput == other.m_fUseUnscaledHiDPIOutput) &&
#endif /* VBOX_WS_MAC */
               (m_f3dAccelerationEnabled == other.m_f3dAccelerationEnabled) &&
#ifdef VBOX_WITH_VIDEOHWACCEL
               (m_f2dAccelerationEnabled == other.m_f2dAccelerationEnabled) &&
#endif /* VBOX_WITH_VIDEOHWACCEL */
               (m_fRemoteDisplayServerSupported == other.m_fRemoteDisplayServerSupported) &&
               (m_fRemoteDisplayServerEnabled == other.m_fRemoteDisplayServerEnabled) &&
               (m_strRemoteDisplayPort == other.m_strRemoteDisplayPort) &&
               (m_remoteDisplayAuthType == other.m_remoteDisplayAuthType) &&
               (m_uRemoteDisplayTimeout == other.m_uRemoteDisplayTimeout) &&
               (m_fRemoteDisplayMultiConnAllowed == other.m_fRemoteDisplayMultiConnAllowed) &&
               (m_fVideoCaptureEnabled == other.m_fVideoCaptureEnabled) &&
               (m_strVideoCaptureFilePath == other.m_strVideoCaptureFilePath) &&
               (m_iVideoCaptureFrameWidth == other.m_iVideoCaptureFrameWidth) &&
               (m_iVideoCaptureFrameHeight == other.m_iVideoCaptureFrameHeight) &&
               (m_iVideoCaptureFrameRate == other.m_iVideoCaptureFrameRate) &&
               (m_iVideoCaptureBitRate == other.m_iVideoCaptureBitRate) &&
               (m_screens == other.m_screens);
    }

    /* Operators: */
    bool operator==(const UIDataSettingsMachineDisplay &other) const { return equal(other); }
    bool operator!=(const UIDataSettingsMachineDisplay &other) const { return !equal(other); }

    /* Variables: Video stuff: */
    int m_iCurrentVRAM;
    int m_cGuestScreenCount;
    double m_dScaleFactor;
#ifdef VBOX_WS_MAC
    bool m_fUseUnscaledHiDPIOutput;
#endif /* VBOX_WS_MAC */
    bool m_f3dAccelerationEnabled;
#ifdef VBOX_WITH_VIDEOHWACCEL
    bool m_f2dAccelerationEnabled;
#endif /* VBOX_WITH_VIDEOHWACCEL */

    /* Variables: Remote Display stuff: */
    bool m_fRemoteDisplayServerSupported;
    bool m_fRemoteDisplayServerEnabled;
    QString m_strRemoteDisplayPort;
    KAuthType m_remoteDisplayAuthType;
    ulong m_uRemoteDisplayTimeout;
    bool m_fRemoteDisplayMultiConnAllowed;

    /* Variables: Video Capture stuff: */
    bool m_fVideoCaptureEnabled;
    QString m_strVideoCaptureFolder;
    QString m_strVideoCaptureFilePath;
    int m_iVideoCaptureFrameWidth;
    int m_iVideoCaptureFrameHeight;
    int m_iVideoCaptureFrameRate;
    int m_iVideoCaptureBitRate;
    QVector<BOOL> m_screens;
};
typedef UISettingsCache<UIDataSettingsMachineDisplay> UISettingsCacheMachineDisplay;

/* Machine settings / Display page: */
class UIMachineSettingsDisplay : public UISettingsPageMachine,
                                 public Ui::UIMachineSettingsDisplay
{
    Q_OBJECT;

public:

    /** Constructor. */
    UIMachineSettingsDisplay();

    /* API: Correlation stuff: */
    void setGuestOSType(CGuestOSType guestOSType);
#ifdef VBOX_WITH_VIDEOHWACCEL
    bool isAcceleration2DVideoSelected() const;
#endif /* VBOX_WITH_VIDEOHWACCEL */

protected:

    /** Returns whether the page content was changed. */
    bool changed() const { return m_cache.wasChanged(); }

    /** Loads data into the cache from corresponding external object(s),
      * this task COULD be performed in other than the GUI thread. */
    void loadToCacheFrom(QVariant &data);
    /** Loads data into corresponding widgets from the cache,
      * this task SHOULD be performed in the GUI thread only. */
    void getFromCache();

    /** Saves data from corresponding widgets to the cache,
      * this task SHOULD be performed in the GUI thread only. */
    void putToCache();
    /** Saves data from the cache to corresponding external object(s),
      * this task COULD be performed in other than the GUI thread. */
    void saveFromCacheTo(QVariant &data);

    /** Performs validation, updates @a messages list if something is wrong. */
    bool validate(QList<UIValidationMessage> &messages);

    /** Defines TAB order. */
    void setOrderAfter(QWidget *pWidget);

    /** Handles translation event. */
    void retranslateUi();

    /** Performs final page polishing. */
    void polishPage();

private slots:

    /* Handlers: Screen stuff: */
    void sltHandleVideoMemorySizeSliderChange();
    void sltHandleVideoMemorySizeEditorChange();
    void sltHandleVideoScreenCountSliderChange();
    void sltHandleVideoScreenCountEditorChange();
    void sltHandleGuestScreenScaleSliderChange();
    void sltHandleGuestScreenScaleEditorChange();

    /* Handlers: Video Capture stuff: */
    void sltHandleVideoCaptureCheckboxToggle();
    void sltHandleVideoCaptureFrameSizeComboboxChange();
    void sltHandleVideoCaptureFrameWidthEditorChange();
    void sltHandleVideoCaptureFrameHeightEditorChange();
    void sltHandleVideoCaptureFrameRateSliderChange();
    void sltHandleVideoCaptureFrameRateEditorChange();
    void sltHandleVideoCaptureQualitySliderChange();
    void sltHandleVideoCaptureBitRateEditorChange();

private:

    /** Prepare routine. */
    void prepare();
    /** Prepare routine: Screen tab. */
    void prepareScreenTab();
    /** Prepare routine: Remote Display tab. */
    void prepareRemoteDisplayTab();
    /** Prepare routine: Video Capture tab. */
    void prepareVideoCaptureTab();
    /** Prepare routine: Validation. */
    void prepareValidation();

    /* Helpers: Video stuff: */
    void checkVRAMRequirements();
    bool shouldWeWarnAboutLowVideoMemory();
    static int calcPageStep(int iMax);

    /* Helpers: Video Capture stuff: */
    void lookForCorrespondingSizePreset();
    void updateVideoCaptureScreenCount();
    void updateVideoCaptureSizeHint();
    static void lookForCorrespondingPreset(QComboBox *pWhere, const QVariant &whichData);
    static int calculateBitRate(int iFrameWidth, int iFrameHeight, int iFrameRate, int iQuality);
    static int calculateQuality(int iFrameWidth, int iFrameHeight, int iFrameRate, int iBitRate);

    /* Guest OS type id: */
    CGuestOSType m_guestOSType;
    /* System minimum lower limit of VRAM (MiB). */
    int m_iMinVRAM;
    /* System maximum limit of VRAM (MiB). */
    int m_iMaxVRAM;
    /* Upper limit of VRAM in MiB for this dialog. This value is lower than
     * m_maxVRAM to save careless users from setting useless big values. */
    int m_iMaxVRAMVisible;
    /* Initial VRAM value when the dialog is opened. */
    int m_iInitialVRAM;
#ifdef VBOX_WITH_VIDEOHWACCEL
    /* Specifies whether the guest OS supports 2D video-acceleration: */
    bool m_f2DVideoAccelerationSupported;
#endif /* VBOX_WITH_VIDEOHWACCEL */
#ifdef VBOX_WITH_CRHGSMI
    /* Specifies whether the guest OS supports WDDM: */
    bool m_fWddmModeSupported;
#endif /* VBOX_WITH_CRHGSMI */

    /* Cache: */
    UISettingsCacheMachineDisplay m_cache;
};

#endif // __UIMachineSettingsDisplay_h__

