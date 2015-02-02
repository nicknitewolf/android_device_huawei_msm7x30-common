package com.blefish.huaweisettings.settings;

import android.content.Context;
import android.os.SystemProperties;
import com.blefish.huaweisettings.R;

/**
 * Created by rudolf on 12/26/14.
 */
public class BTPower implements Setting {
    private static final String BT_POWER_SUPPORTED_PROP = "ro.bt_power.supported";
    private static final String BT_POWER_CLASS_PROP = "persist.service.bt.power";

    @Override
    public boolean isSupported(Context context) {
        return context.getResources().getBoolean(R.bool.config_btPowerSupported);
    }

    @Override
    public void writeValue(String value) {
        SystemProperties.set(BT_POWER_CLASS_PROP, value.toString());
    }
}
