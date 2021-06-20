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
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;

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

    RadioGroup colorSelected;
    RadioButton color1Rdb;
    RadioButton color2Rdb;
    RadioButton color3Rdb;
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
        init();
        return view;
    }

    private void mapEvent() {
        final Runnable[] runnable = {null};
        Handler handler = new android.os.Handler();
        colorPickerView.setColorListener(new ColorListener() {
            @Override
            public void onColorSelected(int color, boolean fromUser) {
                if(!fromUser)
                    return;
                String hexColor = String.format("#%06X", (0xFFFFFF & color));
                String cmd = "";
                if(color1Rdb.isChecked())
                    cmd = "{\"cmd\":\"exe\",\"key\":\"color1_inp\",\"val\":\""+hexColor+"\"}";
                if(color2Rdb.isChecked())
                    cmd = "{\"cmd\":\"exe\",\"key\":\"color2_inp\",\"val\":\""+hexColor+"\"}";
                if(color3Rdb.isChecked())
                    cmd = "{\"cmd\":\"exe\",\"key\":\"color3_inp\",\"val\":\""+hexColor+"\"}";
                if(runnable[0] !=null)
                    handler.removeCallbacks(runnable[0]);
                String finalCmd = cmd;
                runnable[0] = new Runnable() {
                    public void run() {
                        ConnectionService.sendCommand(ConnectionService.SEND, finalCmd);

                    }
                };
                handler.postDelayed(runnable[0]
                        , 250);
            }
        });
        colorSelected.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");
            }
        });
    }

    private void mapView() {
        colorPickerView = view.findViewById(R.id.colorPicker_pkr);

        colorSelected = view.findViewById(R.id.color_select_rdg);
        color1Rdb = view.findViewById(R.id.color1_select_rdb);
        color2Rdb = view.findViewById(R.id.color2_select_rdb);
        color3Rdb = view.findViewById(R.id.color3_select_rdb);
    }
    private void init() {
        BroadcastReceiver mRefreshReceiver;
        IntentFilter filter = new IntentFilter();
        filter.addAction("onMessage");
        mRefreshReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                String data = intent.getExtras().getString("data");
                String[] dataArr = data.split("\n");

                for (String elm:
                        dataArr) {
                    String[] keyVal = elm.split(":");
                    String key = keyVal[0];
                    String val = keyVal[1];

                    if(key.equals("color1_inp") && color1Rdb.isChecked()){
                        colorPickerView.setInitialColor(Color.parseColor(val));
                    }else if(key.equals("color2_inp")&& color2Rdb.isChecked()){
                        colorPickerView.setInitialColor(Color.parseColor(val));
                    }else if(key.equals("color3_inp")&& color3Rdb.isChecked()){
                        colorPickerView.setInitialColor(Color.parseColor(val));
                    }
                }

            }
        };
        LocalBroadcastManager.getInstance(view.getContext()).registerReceiver(mRefreshReceiver, filter);
        ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");

    }
}