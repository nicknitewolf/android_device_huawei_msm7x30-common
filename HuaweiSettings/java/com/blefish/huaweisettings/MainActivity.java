package com.blefish.huaweisettings;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.os.Build;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;
import android.util.Log;
import android.widget.Toast;


import com.blefish.huaweisettings.settings.BTMac;
import com.blefish.huaweisettings.settings.BTPower;
import com.blefish.huaweisettings.settings.HWAddresses;
import com.blefish.huaweisettings.settings.MagCalibration;
import com.blefish.huaweisettings.settings.Microphone;
import com.blefish.huaweisettings.settings.USBCurrent;
import com.blefish.huaweisettings.settings.USBHost;
import com.blefish.huaweisettings.settings.WlanMac;

/**
 * A {@link PreferenceActivity} that presents a set of application settings. On
 * handset devices, settings are presented as a single list. On tablets,
 * settings are split by category, with category headers shown to the left of
 * the list of settings.
 * <p/>
 * See <a href="http://developer.android.com/design/patterns/settings.html">
 * Android Design: Settings</a> for design guidelines and the <a
 * href="http://developer.android.com/guide/topics/ui/settings.html">Settings
 * API Guide</a> for more information on developing a Settings UI.
 */
public class MainActivity extends PreferenceActivity {
    /**
     * Determines whether to always show the simplified settings UI, where
     * settings are presented in a single list. When false, settings are shown
     * as a master/detail two-pane view on tablets. When true, a single pane is
     * shown on tablets.
     */
    private static final boolean ALWAYS_SIMPLE_PREFS = true;

    public static final String LOG_TAG = "HuaweiSettings";

    public static final String PREF_GENERAL_FORCE_MIC_KEY = "pref_general_force_mic";
    public static final Microphone microphone = new Microphone();

    public static final String PREF_GENERAL_BT_POWER_KEY = "pref_general_bt_power";
    public static final BTPower btPower = new BTPower();

    public static final String PREF_USB_HOST_KEY = "pref_usb_host";
    public static final USBHost usbHost = new USBHost();

    public static final String PREF_USB_CURRENT_KEY = "pref_usb_current";
    public static final USBCurrent usbCurrent = new USBCurrent();

    public static final String PREF_SENSORS_MAGNETOMETER = "pref_sensors_mag_calib";
    public static final MagCalibration magCalibration = new MagCalibration();

    public static final String PREF_HWADDR_CUSTOM = "pref_hwaddr_custom";
    public static final HWAddresses hwAddresses = new HWAddresses();

    public static final String PREF_HWADDR_BT = "pref_hwaddr_bt";
    public static final BTMac btMac = new BTMac();

    public static final String PREF_HWADDR_WLAN = "pref_hwaddr_wlan";
    public static final WlanMac wlanMac = new WlanMac();

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);

        setupSimplePreferencesScreen();
    }

    /**
     * Shows the simplified settings UI if the device configuration if the
     * device configuration dictates that a simplified, single-pane UI should be
     * shown.
     */
    private void setupSimplePreferencesScreen() {
        if (!isSimplePreferences(this)) {
            return;
        }

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);

        // In the simplified UI, fragments are not used at all and we instead
        // use the older PreferenceActivity APIs.

        // Add 'general' preferences.
        addPreferencesFromResource(R.xml.preferences);

        // Bind the summaries of EditText/List/Dialog/Ringtone preferences to
        // their values. When their values change, their summaries are updated
        // to reflect the new value, per the Android Design guidelines.
        bindPreferenceSummaryToValue(findPreference(PREF_GENERAL_BT_POWER_KEY));
        bindPreferenceSummaryToValue(findPreference(PREF_USB_CURRENT_KEY));
        bindPreferenceSummaryToValue(findPreference(PREF_HWADDR_BT));
        bindPreferenceSummaryToValue(findPreference(PREF_HWADDR_WLAN));

        findPreference(PREF_GENERAL_FORCE_MIC_KEY).setEnabled(microphone.isSupported(this));
        findPreference(PREF_GENERAL_BT_POWER_KEY).setEnabled(btPower.isSupported(this));
        findPreference(PREF_USB_HOST_KEY).setEnabled(usbHost.isSupported(this));
        findPreference(PREF_USB_CURRENT_KEY).setEnabled(usbCurrent.isSupported(this));
        findPreference(PREF_SENSORS_MAGNETOMETER).setEnabled(magCalibration.isSupported(this));

        Boolean hwAddrEnabled = hwAddresses.isSupported(this);
        findPreference(PREF_HWADDR_CUSTOM).setEnabled(hwAddrEnabled);
        Boolean hwAddrValue = sharedPreferences.getBoolean(PREF_HWADDR_CUSTOM, false);
        findPreference(PREF_HWADDR_BT).setEnabled(hwAddrValue && btMac.isSupported(this));
        findPreference(PREF_HWADDR_WLAN).setEnabled(hwAddrValue && wlanMac.isSupported(this));

        if (!hwAddrValue) {
            EditTextPreference btPreference = (EditTextPreference)findPreference(PREF_HWADDR_BT);
            btPreference.setText(btMac.getValue());
            btPreference.setSummary(btPreference.getText());
            EditTextPreference wlanPreference = (EditTextPreference)findPreference(PREF_HWADDR_WLAN);
            wlanPreference.setText(wlanMac.getValue());
            wlanPreference.setSummary(wlanPreference.getText());
        }

        findPreference(PREF_SENSORS_MAGNETOMETER).setOnPreferenceClickListener(sOnPreferenceClickListener);
        sharedPreferences.registerOnSharedPreferenceChangeListener(sOnSharedPreferenceChangeListener);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean onIsMultiPane() {
        return isXLargeTablet(this) && !isSimplePreferences(this);
    }

    /**
     * Helper method to determine if the device has an extra-large screen. For
     * example, 10" tablets are extra-large.
     */
    private static boolean isXLargeTablet(Context context) {
        return (context.getResources().getConfiguration().screenLayout
                & Configuration.SCREENLAYOUT_SIZE_MASK) >= Configuration.SCREENLAYOUT_SIZE_XLARGE;
    }

    /**
     * Determines whether the simplified settings UI should be shown. This is
     * true if this is forced via {@link #ALWAYS_SIMPLE_PREFS}, or the device
     * doesn't have newer APIs like {@link PreferenceFragment}, or the device
     * doesn't have an extra-large screen. In these cases, a single-pane
     * "simplified" settings UI should be shown.
     */
    private static boolean isSimplePreferences(Context context) {
        return ALWAYS_SIMPLE_PREFS
                || Build.VERSION.SDK_INT < Build.VERSION_CODES.HONEYCOMB
                || !isXLargeTablet(context);
    }

    /**
     * A preference value change listener that updates the preference's summary
     * to reflect its new value.
     */
    private static Preference.OnPreferenceChangeListener sBindPreferenceSummaryToValueListener = new Preference.OnPreferenceChangeListener() {
        @Override
        public boolean onPreferenceChange(Preference preference, Object value) {
            String stringValue = value.toString();

            if (preference instanceof ListPreference) {
                // For list preferences, look up the correct display value in
                // the preference's 'entries' list.
                ListPreference listPreference = (ListPreference) preference;
                int index = listPreference.findIndexOfValue(stringValue);

                // Set the summary to reflect the new value.
                preference.setSummary(
                        index >= 0
                                ? listPreference.getEntries()[index]
                                : null);

            } else {
                // For all other preferences, set the summary to the value's
                // simple string representation.
                preference.setSummary(stringValue);
            }
            return true;
        }
    };

    private Preference.OnPreferenceClickListener sOnPreferenceClickListener = new Preference.OnPreferenceClickListener() {
        @Override
        public boolean onPreferenceClick(Preference preference) {
            if (preference.getKey().equals(PREF_SENSORS_MAGNETOMETER)) {
                magCalibration.writeValue("");
                findPreference(PREF_SENSORS_MAGNETOMETER).setEnabled(false);
            }
            return true;
        }
    };

    private SharedPreferences.OnSharedPreferenceChangeListener sOnSharedPreferenceChangeListener = new SharedPreferences.OnSharedPreferenceChangeListener() {
        @Override
        public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
            if (key.equals(PREF_GENERAL_FORCE_MIC_KEY)) {
                Boolean value = sharedPreferences.getBoolean(PREF_GENERAL_FORCE_MIC_KEY, false);
                microphone.writeValue(value.toString());
                showToast(getString(R.string.toast_replug_headset));
            } else if (key.equals(PREF_GENERAL_BT_POWER_KEY)) {
                String value = sharedPreferences.getString(PREF_GENERAL_BT_POWER_KEY, "0");
                btPower.writeValue(value.toString());
                showToast(getString(R.string.toast_restart_bluetooth));
            } else if (key.equals(PREF_USB_HOST_KEY)) {
                Boolean value = sharedPreferences.getBoolean(PREF_USB_HOST_KEY, false);
                usbHost.writeValue(value.toString());
            } else if (key.equals(PREF_USB_CURRENT_KEY)) {
                String value = sharedPreferences.getString(PREF_USB_CURRENT_KEY, "-1");
                usbCurrent.writeValue(value.toString());
            } else if (key.equals(PREF_HWADDR_CUSTOM)) {
                Boolean value = sharedPreferences.getBoolean(PREF_HWADDR_CUSTOM, false);
                hwAddresses.writeValue(value.toString());

                findPreference(PREF_HWADDR_BT).setEnabled(value);
                findPreference(PREF_HWADDR_WLAN).setEnabled(value);

                if (!value) {
                    EditTextPreference btPreference = (EditTextPreference)findPreference(PREF_HWADDR_BT);
                    btPreference.setText(btMac.getValue());
                    btPreference.setSummary(btPreference.getText());
                    EditTextPreference wlanPreference = (EditTextPreference)findPreference(PREF_HWADDR_WLAN);
                    wlanPreference.setText(wlanMac.getValue());
                    wlanPreference.setSummary(wlanPreference.getText());
                }
            } else if (key.equals(PREF_HWADDR_BT)) {
                String value = sharedPreferences.getString(PREF_HWADDR_BT, "00:11:22:33:44:55");
                btMac.writeValue(value);
                showToast(getString(R.string.toast_restart_bluetooth));
            } else if (key.equals(PREF_HWADDR_WLAN)) {
                String value = sharedPreferences.getString(PREF_HWADDR_WLAN, "00:11:22:33:44:55");
                wlanMac.writeValue(value);
                showToast(getString(R.string.toast_restart_wifi));
            }
        }
    };

    /**
     * Binds a preference's summary to its value. More specifically, when the
     * preference's value is changed, its summary (line of text below the
     * preference title) is updated to reflect the value. The summary is also
     * immediately updated upon calling this method. The exact display format is
     * dependent on the type of preference.
     *
     * @see #sBindPreferenceSummaryToValueListener
     */
    private static void bindPreferenceSummaryToValue(Preference preference) {
        // Set the listener to watch for value changes.
        preference.setOnPreferenceChangeListener(sBindPreferenceSummaryToValueListener);

        // Trigger the listener immediately with the preference's
        // current value.
        sBindPreferenceSummaryToValueListener.onPreferenceChange(preference,
                PreferenceManager
                        .getDefaultSharedPreferences(preference.getContext())
                        .getString(preference.getKey(), ""));
    }

    private void showToast(String text) {
        Toast.makeText(this, text, Toast.LENGTH_SHORT).show();
    }
}
