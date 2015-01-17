package com.blefish.huaweisettings.settings;

import android.os.SystemProperties;

/**
 * Created by rudolf on 12/26/14.
 */
public class Microphone implements Setting {
    private static final String FORCE_MIC_ENABLE_PROP = "persist.service.audio.hs_intmic";

    @Override
    public boolean isSupported() {
        return true;
    }

    @Override
    public void writeValue(String value) {
        Integer enabled = 0;
        if (value.equals("true"))
            enabled = 1;
        SystemProperties.set(FORCE_MIC_ENABLE_PROP, enabled.toString());
    }
}
