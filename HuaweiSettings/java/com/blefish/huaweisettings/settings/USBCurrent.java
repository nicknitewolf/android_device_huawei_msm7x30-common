package com.blefish.huaweisettings.settings;

import android.util.Log;

import java.io.File;

/**
 * Created by rudolf on 12/26/14.
 */
public class USBCurrent implements Setting {
    private static final String USB_CURRENT_PATH = "/sys/devices/platform/msm_otg/manual_chg";

    @Override
    public boolean isSupported() {
        File file = new File(USB_CURRENT_PATH);
        return file.exists();
    }

    @Override
    public void writeValue(String value) {
        /* Update only if value is changed. */
        if (!FileUtils.readOneLine(USB_CURRENT_PATH).equals(value))
            FileUtils.writeLine(USB_CURRENT_PATH, value);
    }
}
