package com.example.infinitybox.local_data;

import android.content.Context;
import android.content.SharedPreferences;

import com.google.gson.Gson;
import com.google.gson.JsonArray;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

public class LocalDataManager {
    private static final String LIST_DEVICES = "LIST_DEVICES";
    private static final String PREF_NAME = "PREF_NAME";

    private static LocalDataManager instance;
    static Context mContext;

    public static LocalDataManager getInstance() {
        if(instance == null)
            instance = new LocalDataManager();
        return instance;
    }

    public static void init(Context context){
        mContext = context;
    }

    public void addDevice(Device device){
        List<Device> curDevices = getDevices();
        curDevices.add(device);
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(PREF_NAME,Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        Gson gson = new Gson();
        JsonArray jsonArray = gson.toJsonTree(curDevices).getAsJsonArray();
        editor.putString(LIST_DEVICES,jsonArray.toString());
        editor.apply();
    }
    public List<Device> getDevices(){
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(PREF_NAME,Context.MODE_PRIVATE);
        String data = sharedPreferences.getString(LIST_DEVICES,"");


        List<Device> ret = new ArrayList<>();
        try {
            JSONArray jsonArray = new JSONArray(data);
            Device device;
            JSONObject jsonObject;
            Gson gson = new Gson();
            for (int i = 0; i < jsonArray.length(); i++) {
                jsonObject = jsonArray.getJSONObject(i);
                device = gson.fromJson(jsonObject.toString(),Device.class);
                ret.add(device);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return ret;
    }
}
