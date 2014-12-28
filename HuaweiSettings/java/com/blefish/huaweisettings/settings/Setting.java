package com.blefish.huaweisettings.settings;

/**
 * Created by rudolf on 12/19/14.
 */
public interface Setting {
    public boolean isSupported();
    public void writeValue(String value);
}
