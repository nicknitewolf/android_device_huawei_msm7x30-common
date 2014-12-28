package com.blefish.huaweisettings.settings;

import android.os.SystemProperties;

/**
 * Created by rudolf on 12/26/14.
 */
public class BTPower implements Setting {
    private static final String BT_POWER_SUPPORTED_PROP = "ro.bt_power.supported";
    private static final String BT_POWER_CLASS_PROP = "persist.service.bt.power";

    @Override
    public boolean isSupported() {
        return SystemProperties.getBoolean(BT_POWER_SUPPORTED_PROP, false);
    }

    @Override
    public void writeValue(String value) {
        SystemProperties.set(BT_POWER_CLASS_PROP, value.toString());
    }
}
