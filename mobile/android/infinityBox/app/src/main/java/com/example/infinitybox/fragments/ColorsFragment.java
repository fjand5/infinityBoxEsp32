package com.example.infinitybox.fragments;

import android.app.Fragment;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;


import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.example.infinitybox.R;
import com.example.infinitybox.services.ConnectionService;
import com.skydoves.colorpickerview.ColorPickerView;
import com.skydoves.colorpickerview.listeners.ColorListener;

import java.util.Timer;
import java.util.TimerTask;

public class ColorsFragment extends Fragment {
    ColorPickerView colorPickerView;
    View view;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        view = inflater.inflate(R.layout.fragment_colors, container, false);
        mapView();
        mapEvent();
//        init();
        return view;
    }

    private void mapEvent() {
        final Runnable[] runnable = {null};
        Handler handler = new android.os.Handler();
        colorPickerView.setColorListener(new ColorListener() {
            @Override
            public void onColorSelected(int color, boolean fromUser) {
                String hexColor = String.format("#%06X", (0xFFFFFF & color));
                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"color1_inp\",\"val\":\""+hexColor+"\"}";
                if(runnable[0] !=null)
                    handler.removeCallbacks(runnable[0]);
                runnable[0] = new Runnable() {
                    public void run() {
                        ConnectionService.sendCommand(ConnectionService.SEND,cmd);

                    }
                };
                handler.postDelayed(runnable[0]
                        , 250);
            }
        });
    }

    private void mapView() {
        colorPickerView = view.findViewById(R.id.colorPicker_pkr);
    }
//    private void init() {
//        BroadcastReceiver mRefreshReceiver;
//        IntentFilter filter = new IntentFilter();
//        filter.addAction("onMessage");
//        mRefreshReceiver = new BroadcastReceiver() {
//            @Override
//            public void onReceive(Context context, Intent intent) {
//                String data = intent.getExtras().getString("data");
//                String[] dataArr = data.split("\n");
//                for (String elm:
//                        dataArr) {
//                    String[] keyVal = elm.split(":");
//                    String key = keyVal[0];
//                    String val = keyVal[1];
//
//                    if(key.equals("speed_sld")){
//                        speedSbr.setProgress(Integer.parseInt(val));
//                    }else if(key.equals("brightness_sld")){
//                        brightnessSbr.setProgress(Integer.parseInt(val));
//                    }else if(key.equals("intensity_sld")){
//                        intensitySbr.setProgress(Integer.parseInt(val));
//                    }
//                }
//
//            }
//        };
//        LocalBroadcastManager.getInstance(view.getContext()).registerReceiver(mRefreshReceiver, filter);
//        ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");
//
//    }
}