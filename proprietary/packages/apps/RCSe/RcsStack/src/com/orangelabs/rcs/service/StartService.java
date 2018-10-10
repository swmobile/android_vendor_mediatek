/*******************************************************************************
 * Software Name : RCS IMS Stack
 *
 * Copyright (C) 2010 France Telecom S.A.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

package com.orangelabs.rcs.service;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import android.accounts.Account;
import android.app.Activity;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.res.XmlResourceParser;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Build;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.telephony.SubscriptionManager;
//import android.provider.Telephony.SIMInfo;
import android.telephony.TelephonyManager;
import android.text.TextUtils;

import com.android.internal.telephony.ITelephony;
import com.android.internal.telephony.Phone;
import com.android.internal.telephony.PhoneConstants;
//import com.mediatek.common.featureoption.FeatureOption;
//import com.mediatek.rcse.api.FlightModeApi;
import com.orangelabs.rcs.plugin.apn.RcseOnlyApnUtils;
import com.orangelabs.rcs.R;
import com.orangelabs.rcs.addressbook.AccountChangedReceiver;
import com.orangelabs.rcs.addressbook.AuthenticationService;
import com.orangelabs.rcs.platform.AndroidFactory;
import com.orangelabs.rcs.platform.registry.AndroidRegistryFactory;
import com.orangelabs.rcs.provider.eab.ContactsManager;
import com.orangelabs.rcs.provider.settings.RcsSettings;
import com.orangelabs.rcs.provider.settings.RcsSettingsData;
import com.orangelabs.rcs.provisioning.https.HttpsProvisioningManager;
import com.orangelabs.rcs.provisioning.ProvisioningInfo;
import com.orangelabs.rcs.provisioning.https.HttpsProvisioningService;
//import com.orangelabs.rcs.service.api.client.ClientApiIntents;
import com.orangelabs.rcs.utils.PhoneUtils;
import com.orangelabs.rcs.utils.logger.Logger;
import com.orangelabs.rcs.provisioning.https.HttpsProvisioningUtils;
import com.orangelabs.rcs.provisioning.https.HttpsProvisioningSMS;
/**
 * RCS start service.
 *
 * @author hlxn7157
 */
public class StartService extends Service {
    /**
     * Service name
     */
    public static final String SERVICE_NAME = "com.orangelabs.rcs.service.START";

    /**
     * M:  Add for storing 3 SIM card user data info @{
     */
    /**
     * Indicates the last first user account used
     */
    public static final String REGISTRY_LAST_FIRST_USER_ACCOUNT = "LastFirstUserAccount";
    
    /**
     * Indicates the last second user account used
     */
    public static final String REGISTRY_LAST_SECOND_USER_ACCOUNT = "LastSecondUserAccount";
    
    /**
     * Indicates the last third user account used
     */
    public static final String REGISTRY_LAST_THIRD_USER_ACCOUNT = "LastThirdUserAccount";
    
    /**
     * Indicates that db changed for current account. 
     */
    public static final String ACTION_DB_CHANGE = "com.mediatek.mms.ipmessage.dbChange";
    
    
    
        /**
     * Intent broadcasted when the RCS configuration status has changed (see constant attribute "status").
     * 
     * <p>The intent will have the following extra values:
     * <ul>
     *   <li><em>status</em> - Configuration status.</li>
     * </ul>
     * </ul>
     */
    public final static String CONFIGURATION_STATUS = "com.orangelabs.rcs.CONFIGURATION_STATUS";

    /**
     * Indicates the last User icci account
     */
    private ArrayList<String> lastUserIcci = null;
    
    /**
     * Indicates the user account index included in lastUserAccount
     */
    private final static int LAST_FIRST_USER_ACCOUNT_INDEX = 0; 
    private final static int LAST_SECOND_USER_ACCOUNT_INDEX = 1; 
    private final static int LAST_THIRD_USER_ACCOUNT_INDEX = 2; 
    /** 
     * @} 
     */

    /**
     * Current user account used
     */
    public static final String REGISTRY_CURRENT_USER_ACCOUNT = "CurrentUserAccount";

    /**
     * RCS new user account
     */
    public static final String REGISTRY_NEW_USER_ACCOUNT = "NewUserAccount";

    
    /*
     * KEY FOR SHARED PREFERENCE FOR IMS SERVICES
     */
     //XDM SERVICE 
    
    private static final String KEY_XDM_REQUEST_ENABLE = "XdmRequestEnable";
    /*
     * @:KEY FOR SHARED PREFERENCE FOR IMS SERVICES [ENDS]
     */
    
    
    /**
     * Connection manager
     */
    private ConnectivityManager connMgr = null;

    /**
     * Network state listener
     */
    private BroadcastReceiver networkStateListener = null;

    /**
     * Last User account
     */
    private String lastUserAccount = null;

    /**
     * Current User account
     */
    private String currentUserAccount = null;


    /**
     * M: 
     */
    /**
     * Indicate whether network state listener has been registered.
     */
    private final AtomicBoolean mIsRegisteredAtomicBoolean = new AtomicBoolean();
    

    /**
     * Launch boot flag
     */
    private boolean boot = false;

    public         boolean user = false;


    /**
     * The logger
     */
    private static Logger logger = Logger.getLogger(StartService.class.getSimpleName());
    
    private static final String INTENT_KEY_BOOT = "boot";
    private static final String INTENT_KEY_USER = "user";

    
    /**
     * Account changed broadcast receiver
     */
    private HttpsProvisioningSMS reconfSMSReceiver = null;
    

    @Override
    public void onCreate() {
        if (logger.isActivated()) {
            logger.debug("onCreate() called");
        }
       // AndroidFactory.setApplicationContext(getApplicationContext());
        // Instantiate RcsSettings
        RcsSettings.createInstance(getApplicationContext());
        /**
         * M: rcse only apn feature @{
         */
        // because LauncherUtils may be called by UI process, so there
        // may not createInstance in core process.
        if (RcseOnlyApnUtils.getInstance() == null) {
            RcseOnlyApnUtils.createInstance(getApplicationContext());
        }
        /** @} */

        // Use a network listener to start RCS core when the data will be ON 
        if (RcsSettings.getInstance().getAutoConfigMode() == RcsSettingsData.NO_AUTO_CONFIG) {
            // Get connectivity manager
            if (connMgr == null) {
                connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
            }
            
            // Instantiate the network listener
            networkStateListener = new BroadcastReceiver() {
                @Override
                public void onReceive(Context context, final Intent intent) {
                    Thread t = new Thread() {
                        public void run() {
                            connectionEvent(intent.getAction());
                        }
                    };
                    t.start();
                }
            };
    
            // Register network state listener
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
            registerReceiver(networkStateListener, intentFilter);
            mIsRegisteredAtomicBoolean.set(true);
            /**
             * M: Modified for doing unregister when device go to flight mode. @{
             */
        //    new FlightModeApi(getApplicationContext()).connectApi();
            /**
             * @}
             */
        }
    }

    @Override
    public void onDestroy() {
        // finalize the RcseOnlyApnUtils instance
        RcseOnlyApnUtils.getInstance().destroy();
        
        // Unregister network state listener
         if (networkStateListener != null && mIsRegisteredAtomicBoolean.compareAndSet(true, false)) {
            try {
                unregisterReceiver(networkStateListener);
                   networkStateListener = null;
            } catch (IllegalArgumentException e) {
                // Nothing to do
            }
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (logger.isActivated()) {
            logger.debug("Start RCS service");
        }

        // Check boot
        if (intent != null) {
            boot = intent.getBooleanExtra("boot", false);
            user = intent.getBooleanExtra(INTENT_KEY_USER, false);
        }


        /**
         * M: Check account in a background thread, fix an ANR issue. @{
         */
        AsyncTask.execute(new Runnable() {
            @Override
            public void run() {
                // if it should use only apn due to network status, and it
                // is not already started or route fail, then do start to
                // request to use only apn
                if (RcsSettings.getInstance().isRcseOnlyApnEnabled()
                        && !RcseOnlyApnUtils.getInstance().isRcsOnlyApnStarted()) {
                    RcseOnlyApnUtils.getInstance().switchRcseOnlyApn();
                }
                boolean accountAvailable = checkAccount();
                if (logger.isActivated()) {
                    logger.debug("accountAvailable = " + accountAvailable);
        }
                if (accountAvailable) {
            launchRcsService(boot, user);
        } else {
            // User account can't be initialized (no radio to read IMSI, .etc)
            if (logger.isActivated()) {
                logger.error("Can't create the user account");
            }
/*
            // Send service intent 
            Intent stopIntent = new Intent(ClientApiIntents.SERVICE_STATUS);
            stopIntent.putExtra("status", ClientApiIntents.SERVICE_STATUS_STOPPED);
            sendBroadcast(stopIntent);
*/
            // Exit service
            stopSelf();
        }
            }
        });
        /** 
         * @} 
         */

        // We want this service to continue running until it is explicitly
        // stopped, so return sticky.
        return START_STICKY;
    }

    /**
     * Connection event
     *
     * @param action Connectivity action
     */
    private void connectionEvent(String action) {
        if (logger.isActivated()) {
            logger.debug("Connection event " + action);
        }
        // Try to start the service only if a data connectivity is available
        if (action.equals(ConnectivityManager.CONNECTIVITY_ACTION)) {
            NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
            if ((networkInfo != null) && networkInfo.isConnected()) {
                if (logger.isActivated()) {
                    logger.debug("Device connected - Launch RCS service");
                }
                 boolean accountAvailable = checkAccount();
                if (logger.isActivated()) {
                    logger.debug("accountAvailable = " + accountAvailable);
                }
                if (accountAvailable) {
                /**
                 * M:  Add for displaying roaming notification @{
                 */
                // Start the RCS service
                launchRcseCoreServie();
                /** 
                 * @} 
                 */
                
                // Stop Network listener
               if (networkStateListener != null
                            && mIsRegisteredAtomicBoolean.compareAndSet(true, false)) {
                    try {
                        unregisterReceiver(networkStateListener);
                            networkStateListener = null;
                    } catch (IllegalArgumentException e) {
                        // Nothing to do
                    }
                  }
                   }else {
                    // Exit service
                    stopSelf();
                }
            }
        }
    }

    /**
     * Set the country code
     * 
     * @return Boolean
     */
    private boolean setCountryCode() {
        // Get country code 
        int subId=0;
        subId=(int)SubscriptionManager.getDefaultDataSubId();
        if (logger.isActivated()) {
            logger.error("setCountryCode subId" + subId);
        }
        if(subId == -1){
             subId=(int)SubscriptionManager.getDefaultSubId();
        }
        if (logger.isActivated()) {
            logger.error("setCountryCode subId" + subId);
        }
        TelephonyManager mgr = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
        String countryCodeIso = mgr.getSimCountryIso(subId);
        if (logger.isActivated()) {
                logger.error("countryCodeIso" + countryCodeIso);
            }
        
        if (countryCodeIso == null) {
            if (logger.isActivated()) {
                logger.error("Can't read country code from SIM");
            }
            return false;
        }


        // Parse country table to resolve the area code and country code
        try {
            XmlResourceParser parser = getResources().getXml(R.xml.country_table);
            parser.next();
            int eventType = parser.getEventType();
            while (eventType != XmlPullParser.END_DOCUMENT) {
                if (eventType == XmlPullParser.START_TAG) {
                    if (parser.getName().equals("Data")) {
                        if (parser.getAttributeValue(null, "code").equalsIgnoreCase(countryCodeIso)) {
                            String countryCode = parser.getAttributeValue(null, "cc");
                        //    String areaCode = parser.getAttributeValue(null, "tc");
                            if (countryCode != null) {
                                if (!countryCode.startsWith("+")) {
                                    countryCode = "+" + countryCode;
                                }
                                if (logger.isActivated()) {
                                    logger.info("Set country code to " + countryCode);
                                }
                               /**
                                 * M: Add for storing 3 SIM card user data info @{
                                 */
                                // Used to avoid ANR while do I/O operation
                                final String finalCountryCode = countryCode;
                                AsyncTask.execute(new Runnable(){
                                    public void run() {
                                        RcsSettings.getInstance().setCountryCode(finalCountryCode);
                                    }
                                });
                                /**
                                 * @}
                                 */
                            }

                            final String areaCode = parser.getAttributeValue(null, "tc");
                            if (areaCode != null) {
                                if (logger.isActivated()) {
                                    logger.info("Set area code to " + areaCode);
                                }
                                /**
                                 * M: Add for storing 3 SIM card user data info @{
                                 */
                                // Used to avoid ANR while do I/O operation
                                AsyncTask.execute(new Runnable(){
                                    public void run() {
                                RcsSettings.getInstance().setCountryAreaCode(areaCode);
                            }
                                });
                                /**
                                 * @}
                                 */
                            }
                                return true;
                            }
                        }
                    }
                eventType = parser.next();
            }

            if (logger.isActivated()) {
                logger.error("Country code not found");
            }
            return false;
        } catch (XmlPullParserException e) {
            if (logger.isActivated()) {
                logger.error("Can't parse country code from XML file", e);
            }
            return false;
        } catch (IOException e) {
            if (logger.isActivated()) {
                logger.error("Can't read country code from XML file", e);
            }
            return false;
        }
    }

    /**
     * Check account
     *
     * @return true if an account is available
     */
    private boolean checkAccount() {
       // AndroidFactory.setApplicationContext(getApplicationContext());
        
        if(LauncherUtils.isSecondaryDevice()){
            return true;
        }
        
        // Read the current and last end user account
        currentUserAccount = LauncherUtils.getCurrentUserAccount(getApplicationContext());
        lastUserAccount = LauncherUtils.getLastUserAccount(getApplicationContext());
        if (logger.isActivated()) {
            logger.info("Last user account is " + lastUserAccount);
            logger.info("Current user account is " + currentUserAccount);
        }

        // Check the current SIM
        if (currentUserAccount == null) {
            if (isFirstLaunch()) {
                // If it's a first launch the IMSI is necessary to initialize the service the first time
                return false;
            } else {
                // Set the user account ID from the last used IMSI
                currentUserAccount = lastUserAccount;
            }
        }

        // On the first launch and if SIM card has changed
        if (isFirstLaunch()) {
            // Set the country code
            boolean result = setCountryCode();
            if (!result) {
                // Can't set the country code
                return false;
            }

            // Set new user flag
            setNewUserAccount(true);
        } else
        if (hasChangedAccount()) {
            // Backup last account settings
            if (lastUserAccount != null) {
                if (logger.isActivated()) {
                    logger.info("Backup " + lastUserAccount);
                }
                RcsSettings.getInstance().backupAccountSettings(lastUserAccount);
                LauncherUtils.backupMessage(getApplicationContext());
            }
            RcsSettings.getInstance().setFristLaunchState(true);
            // Set the country code
            boolean result = setCountryCode();
            if (!result) {
                // Can't set the country code
                return false;
            }

            // Reset RCS account 
            LauncherUtils.resetRcsConfig(getApplicationContext());

            // Restore current account settings
            if (logger.isActivated()) {
                logger.info("Restore " + currentUserAccount);
            }
            RcsSettings.getInstance().restoreAccountSettings(currentUserAccount);
            RcsSettings.createInstance(AndroidFactory.getApplicationContext());

            LauncherUtils.restoreMessages(getApplicationContext());
            Intent intent = new Intent(ACTION_DB_CHANGE);
            AndroidFactory.getApplicationContext().sendBroadcast(intent);
            
            // Activate service if new account
            RcsSettings.getInstance().setServiceActivationState(true);

            // Set new user flag
            setNewUserAccount(true);
        } else {
            // Set new user flag
            setNewUserAccount(false);
        }
 /*       
        // Check if the RCS account exists
        Account account = AuthenticationService.getAccount(getApplicationContext(),
                getString(R.string.rcs_core_account_username));
        if (account == null) {
            // No account exists 
            if (logger.isActivated()) {
                logger.debug("The RCS account does not exist");
            }
            if (AccountChangedReceiver.isAccountResetByEndUser()) {
                // It was manually destroyed by the user
                if (logger.isActivated()) {
                    logger.debug("It was manually destroyed by the user, we do not recreate it");
                }
                return false;
            } else {
                if (logger.isActivated()) {
                    logger.debug("Recreate a new RCS account");
                }
                AuthenticationService.createRcsAccount(getApplicationContext(),
                        getString(R.string.rcs_core_account_username), true);
            }
        } else {
            // Account exists: checks if it has changed
            if (hasChangedAccount()) {
                // Account has changed (i.e. new SIM card): delete the current account and create a new one
                if (logger.isActivated()) {
                    logger.debug("Deleting the old RCS account for " + lastUserAccount);
                }
                ContactsManager.createInstance(getApplicationContext());
                ContactsManager.getInstance().deleteRCSEntries();
                AuthenticationService.removeRcsAccount(getApplicationContext(), null);
    
                if (logger.isActivated()) {
                    logger.debug("Creating a new RCS account for " + currentUserAccount);
                }
                AuthenticationService.createRcsAccount(getApplicationContext(),
                        getString(R.string.rcs_core_account_username), true);
            }
        }

  */
        // Save the current end user account
        LauncherUtils.setLastUserAccount(getApplicationContext(), currentUserAccount);

        return true;
    }

    /**
     * Launch the RCS service.
     *
     * @param boot indicates if RCS is launched from the device boot
     * @param user indicates if RCS is launched from the user interface
     */
    private void launchRcsService(boolean boot, boolean user) {
        int mode = RcsSettings.getInstance().getAutoConfigMode();

        if (logger.isActivated())
            logger.debug("Launch RCS service: HTTPS=" + (mode == RcsSettingsData.HTTPS_AUTO_CONFIG) + ", boot=" + boot + ", user=" + user);

        if(boot){
            //set the boot flag initialization needed for some IMS service
            setIMSServicePropertyInSharedPrefs(boot);
        }
        
        if (mode == RcsSettingsData.HTTPS_AUTO_CONFIG) {
            // HTTPS auto config
            String version = RcsSettings.getInstance().getProvisioningVersion();
            
            if (logger.isActivated())
                logger.debug("launchRcsService : getProvisioningVersion := " + version);


            // Check the last provisioning version
            if (ProvisioningInfo.Version.RESETED_NOQUERY.equals(version)) {
                // (-1) : RCS service is permanently disabled. SIM change is required
                if (hasChangedAccount()) {
                    // Start provisioning as a first launch
                    HttpsProvisioningService.startHttpsProvisioningService(getApplicationContext(), true, user);
                } else {
                    if (logger.isActivated()) {
                        logger.debug("Provisioning is blocked with this account");
                    }
                    
           
                    //register a listner for Provisioning SMS
                    if (reconfSMSReceiver == null) {
                        reconfSMSReceiver = new HttpsProvisioningSMS(this);
                        reconfSMSReceiver.registerSmsProvisioningReceiver(Integer.toString(HttpsProvisioningUtils.DEFAULT_SMS_PORT), null, null, null);
                    }
                    
                }
            } else {
                if (isFirstLaunch() || hasChangedAccount()) {
                    // First launch: start the auto config service with special tag
                    HttpsProvisioningService.startHttpsProvisioningService(getApplicationContext(), true, user);
                } else {
                    if (ProvisioningInfo.Version.DISABLED_NOQUERY.equals(version)) {
                        // -2 : RCS client and configuration query is disabled
                        if (user) {
                            // Only start query if requested by user action
                            HttpsProvisioningService.startHttpsProvisioningService(getApplicationContext(), false, user);
                        }else{
                            
                            
                            
                            //register a listner for Provisioning SMS
                                        if (reconfSMSReceiver == null) {
                                             reconfSMSReceiver = new HttpsProvisioningSMS(this);
                                             reconfSMSReceiver.registerSmsProvisioningReceiver(Integer.toString(HttpsProvisioningUtils.DEFAULT_SMS_PORT), null, null, null);
                                         }
                        }
                    } else {
                        // Start or restart the HTTP provisioning service
                        HttpsProvisioningService.startHttpsProvisioningService(getApplicationContext(), false, user);
                        if (ProvisioningInfo.Version.DISABLED_DORMANT.equals(version)) {
                            // -3 : RCS client is disabled but configuration query is not
                } else {
                    // Start the RCS core service
                  /**M:
                  * core services will be started by the after provisining is validated 
                 */  
                  //LauncherUtils.launchRcsCoreService(getApplicationContext());
                }
            }
                }
            }
        } else {
            
            if(RcsSettings.getInstance().isSupportOP08()){
              updateSIMDetailsinDB();
            }
            
            RcsSettings.getInstance().setConfigurationState(true);
            // No auto config: directly start the RCS core service
            LauncherUtils.launchRcsCoreService(getApplicationContext());
        }
    }

    
    
    public  void updateSIMDetailsinDB(){
        if(RcsSettings.getInstance().isSupportOP08()){
        boolean akaFlag = true;
        if (logger.isActivated())
            logger.debug("updateSIMDetailsinDB");
        if ((RcsSettings.getInstance().getImsAuhtenticationProcedureForMobile()==RcsSettingsData.AKA_AUTHENT)
        ||akaFlag
        ) {
            if (logger.isActivated())
                logger.debug("RcsSettingsData.AKA_AUTHENT : update RCS_setting fileds  ");
            
            TelephonyManager tm = (TelephonyManager) getApplicationContext().getSystemService(
                    Context.TELEPHONY_SERVICE);
            
            String impi = tm.getIsimImpi();
            String[] impu = tm.getIsimImpu();
            String domain = tm.getIsimDomain();
            String MSISDN="";
            try {
                MSISDN = extractUserNamePart(impu[0]);
            } catch (Exception e) {
                MSISDN="";
                if (logger.isActivated()) {
                    logger.error("updateSIMDetailsinDB is MSISDN null");
                }
                e.printStackTrace();
            }
            if(MSISDN == null) {
                MSISDN="";
            }
            RcsSettings.getInstance().setUserProfileImsUserName_full(impu[0]);
            RcsSettings.getInstance().setUserProfileImsPrivateId(impi);
            RcsSettings.getInstance().setUserProfileImsDomain(domain);
            RcsSettings.getInstance().setUserProfileImsDisplayName(MSISDN);
            RcsSettings.getInstance().setUserProfileImsUserName(MSISDN);
            RcsSettings.getInstance().setImConferenceUri("sip:adhoc@msg.pc.t-mobile.com");
            
            //XDM CHANGES
            RcsSettings.getInstance().setXdmServer("xcap.msg.pc.t-mobile.com");
            RcsSettings.getInstance().setXdmLogin(impu[0]);
            RcsSettings.getInstance().writeParameter(RcsSettingsData.XDM_AUTH_TYPE,"GBA");
            
            //SERVICE CHANGES
            RcsSettings.getInstance().writeParameter(RcsSettingsData.CAPABILITY_SOCIAL_PRESENCE, Boolean.toString(true));
            RcsSettings.getInstance().writeParameter(RcsSettingsData.AUTO_ACCEPT_CHAT,RcsSettingsData.TRUE);
            RcsSettings.getInstance().writeParameter(RcsSettingsData.AUTO_ACCEPT_GROUP_CHAT,RcsSettingsData.TRUE);
            RcsSettings.getInstance().writeParameter(RcsSettingsData.PERMANENT_STATE_MODE,RcsSettingsData.TRUE);
            RcsSettings.getInstance().setCPMSupported(true);
        }
    }
    }
    
    private  String extractUserNamePart(String uri) {
        if ((uri == null) || (uri.trim().length() == 0)) {
            return "";
        }

        try {
            uri = uri.trim();
            int index1 = uri.indexOf("sip:");
            if (index1 != -1) {
                int index2 = uri.indexOf("@", index1);
                String result = uri.substring(index1+4, index2);
                return result;
            } else {
                return uri;
            }
        } catch(Exception e) {
            return "";
        }
    }
    
    /**
     * Is the first RCs is launched ?
     *
     * @return true if it's the first time RCS is launched
     */
    private boolean isFirstLaunch() {
        
        if(LauncherUtils.isSecondaryDevice()){    
            //if MSISDN is not entered
           if(RcsSettings.getInstance().getMsisdn()!=null){
               RcsSettings.getInstance().setFristLaunchState(false);
               return false;
           }
           else{
               RcsSettings.getInstance().setFristLaunchState(true);
               return true;
           }
        }
        if(lastUserAccount == null)
            RcsSettings.getInstance().setFristLaunchState(true);
        return (lastUserAccount == null);
    }

    /**
     * Check if RCS account has changed since the last time we started the service
     *
     * @return true if the active account was changed
     */
    private boolean hasChangedAccount() {
        
        if(LauncherUtils.isSecondaryDevice()){
          return false;    
        }
        
        
        if (lastUserAccount == null) {
            return true;
        } else
        if (currentUserAccount == null) {
            return false;
        } else {
            return (!currentUserAccount.equalsIgnoreCase(lastUserAccount));
        }
    }

    /**
     * Set true if new user account
     *
     * @param value true if new user account
     */
    private void setNewUserAccount(boolean value) {
        SharedPreferences preferences = getSharedPreferences(AndroidRegistryFactory.RCS_PREFS_NAME, Activity.MODE_PRIVATE);
        SharedPreferences.Editor editor = preferences.edit();
        editor.putBoolean(REGISTRY_NEW_USER_ACCOUNT, value);
        editor.commit();
    }

    /**
     * Check if new user account
     *
     * @param context Application context
     * @return true if new user account
     */
    public static boolean getNewUserAccount(Context context) {
        SharedPreferences preferences = context.getSharedPreferences(AndroidRegistryFactory.RCS_PREFS_NAME, Activity.MODE_PRIVATE);
        return preferences.getBoolean(REGISTRY_NEW_USER_ACCOUNT, false);
    }
   
    /** 
     * Launch the RCS start service
     * 
     * @param context
     * @param boot
     *            start RCS service upon boot
     * @param user
     *            start RCS service upon user action
     */
    static void LaunchRcsStartService(Context context, boolean boot, boolean user) {
        if (logger.isActivated())
            logger.debug("Launch RCS service (boot=" + boot + ") (user="+user+")");
        //AndroidFactory.setApplicationContext(context);
        Intent intent = new Intent(context, StartService.class);
        intent.putExtra(INTENT_KEY_BOOT, boot);
        intent.putExtra(INTENT_KEY_USER, user);
        context.startService(intent);
    }
    /** 
     * M: Added to indicate whether the receiver is registered. @{ 
     */

    /**
     * NetworkChangedReceiver instance
     */
  //  private final NetworkChangedReceiver mNetworkChangedReceiver = new NetworkChangedReceiver();

    private void launchRcseCoreServie() {
                    LauncherUtils.launchRcsCoreService(getApplicationContext());
                }

   /* private synchronized void registerNetworkReceiver() {
        IntentFilter filter = new IntentFilter();
        filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
        this.registerReceiver(mNetworkChangedReceiver, filter);
        }

    private synchronized void unregisterNetworkReceiver() {
        this.unregisterReceiver(mNetworkChangedReceiver);
    }*/
    /** 
     * @} 
     */
    
    /*
     * Set device boot flag. its for achaiveing one request per boot for XDM manager
     */
    public static void setXDMBootFlag(Context context,boolean value) {
        SharedPreferences preferences = context.getSharedPreferences(AndroidRegistryFactory.RCS_PREFS_IMS_SERVICES, Activity.MODE_PRIVATE);
        SharedPreferences.Editor editor = preferences.edit();
        editor.putBoolean(KEY_XDM_REQUEST_ENABLE, value);
        editor.commit();
    }
    
    public static boolean getXDMBootFlag(Context context) {
        SharedPreferences preferences = context.getSharedPreferences(AndroidRegistryFactory.RCS_PREFS_IMS_SERVICES, Activity.MODE_PRIVATE);
        return preferences.getBoolean(KEY_XDM_REQUEST_ENABLE, false);
    }
   
    private void setIMSServicePropertyInSharedPrefs(boolean isBoot){
        
        //for XDM set its RCS service initialization via boot
        setXDMBootFlag(getApplicationContext(),isBoot);
    }
    
}