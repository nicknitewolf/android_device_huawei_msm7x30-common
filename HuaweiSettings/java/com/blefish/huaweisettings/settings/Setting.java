package com.blefish.huaweisettings.settings;

import android.content.Context;

/**
 * Created by rudolf on 12/19/14.
 */
public interface Setting {
    public boolean isSupported(Context context);
    public void writeValue(String value);
}
