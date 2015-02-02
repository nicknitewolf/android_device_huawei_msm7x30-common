package com.blefish.huaweisettings;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

/**
 * Created by rudolf on 12/26/14.
 */
public class Startup extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction() == Intent.ACTION_BOOT_COMPLETED)
            restoreSettings(context);
    }

    private void restoreSettings(Context context) {
        /* This only writes back items that do not persist after boot. */
        Log.d(MainActivity.LOG_TAG, "Restoring settings after boot");

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);

        if (MainActivity.usbHost.isSupported(context)) {
            Boolean value = sharedPreferences.getBoolean(MainActivity.PREF_USB_HOST_KEY, false);
            MainActivity.usbHost.writeValue(value.toString());
        }
        if (MainActivity.usbCurrent.isSupported(context)) {
            String value = sharedPreferences.getString(MainActivity.PREF_USB_CURRENT_KEY, "-1");
            MainActivity.usbCurrent.writeValue(value.toString());
        }

        /* Disabled HWAddresses because hwprops binary sets MAC addresses on boot if needed. */
    }
}
