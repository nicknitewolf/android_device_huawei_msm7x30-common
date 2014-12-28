package com.blefish.huaweisettings.settings;

import android.util.Log;

import java.io.File;

/**
 * Created by rudolf on 12/19/14.
 */
public class USBHost implements Setting {
    private static final String USB_HOST_PATH  = "/sys/devices/platform/msm_otg/mode";
    private static final Integer USB_HOST_ON_STATE = 1;
    private static final Integer USB_HOST_OFF_STATE = 0;

    @Override
    public boolean isSupported() {
        File file = new File(USB_HOST_PATH);
        return file.exists();
    }

    @Override
    public void writeValue(String value) {
        Integer state = USB_HOST_OFF_STATE;
        if (value.equals("true"))
            state = USB_HOST_ON_STATE;

        /* Update only if value is changed. */
        if (!FileUtils.readOneLine(USB_HOST_PATH).equals(state.toString()))
            FileUtils.writeLine(USB_HOST_PATH, state.toString());
    }
}
