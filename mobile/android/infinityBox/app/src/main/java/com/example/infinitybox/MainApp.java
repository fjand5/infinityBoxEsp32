package com.example.infinitybox;

import android.app.Application;

import com.example.infinitybox.local_data.LocalDataManager;

public class MainApp extends Application {
    @Override
    public void onCreate() {
        LocalDataManager.init(this);
        super.onCreate();
    }
}
