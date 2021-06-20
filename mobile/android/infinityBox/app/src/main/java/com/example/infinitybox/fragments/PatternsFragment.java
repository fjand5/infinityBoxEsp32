package com.example.infinitybox.fragments;

import android.app.Fragment;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;


import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Spinner;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.example.infinitybox.R;
import com.example.infinitybox.services.ConnectionService;

public class PatternsFragment extends Fragment {
    View view;

    ImageView previousIco;
    ImageView nextIco;
    Spinner currentSpn;
    boolean userSelect = false;
    String listMode[]={
            "STATIC",
            "BLINK",
            "BREATH",
            "COLOR_WIPE",
            "COLOR_WIPE_INV",
            "COLOR_WIPE_REV",
            "COLOR_WIPE_REV_INV",
            "COLOR_WIPE_RANDOM",
            "RANDOM_COLOR",
            "SINGLE_DYNAMIC",
            "MULTI_DYNAMIC",
            "RAINBOW",
            "RAINBOW_CYCLE",
            "SCAN",
            "DUAL_SCAN",
            "FADE",
            "THEATER_CHASE",
            "THEATER_CHASE_RAINBOW",
            "RUNNING_LIGHTS",
            "TWINKLE",
            "TWINKLE_RANDOM",
            "TWINKLE_FADE",
            "TWINKLE_FADE_RANDOM",
            "SPARKLE",
            "FLASH_SPARKLE",
            "HYPER_SPARKLE",
            "STROBE",
            "STROBE_RAINBOW",
            "MULTI_STROBE",
            "BLINK_RAINBOW",
            "CHASE_WHITE",
            "CHASE_COLOR",
            "CHASE_RANDOM",
            "CHASE_RAINBOW",
            "CHASE_FLASH",
            "CHASE_FLASH_RANDOM",
            "CHASE_RAINBOW_WHITE",
            "CHASE_BLACKOUT",
            "CHASE_BLACKOUT_RAINBOW",
            "COLOR_SWEEP_RANDOM",
            "RUNNING_COLOR",
            "RUNNING_RED_BLUE",
            "RUNNING_RANDOM",
            "LARSON_SCANNER",
            "COMET",
            "FIREWORKS",
            "FIREWORKS_RANDOM",
            "MERRY_CHRISTMAS",
            "FIRE_FLICKER",
            "FIRE_FLICKER_SOFT",
            "FIRE_FLICKER_INTENSE",
            "CIRCUS_COMBUSTUS",
            "HALLOWEEN",
            "BICOLOR_CHASE",
            "TRICOLOR_CHASE",
            "TWINKLEFOX"};
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        view = inflater.inflate(R.layout.fragment_patterns, container, false);
        mapView();
        mapEvent();

        init();
        return view;
    }

    private void init() {
        ArrayAdapter<String> spinnerAdapter;
        spinnerAdapter = new ArrayAdapter<String>(view.getContext(),
                R.layout.support_simple_spinner_dropdown_item,
                listMode);

        spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        currentSpn.setAdapter(spinnerAdapter);

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

                    if(key.equals("current_mode")){
                        currentSpn.setSelection(Integer.parseInt(val));
                    }
                }

            }
        };
        LocalBroadcastManager.getInstance(view.getContext()).registerReceiver(mRefreshReceiver, filter);
        ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");
    }

    private void mapEvent() {
        previousIco.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"previous_mode\",\"val\":\"\"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
        nextIco.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"next_mode\",\"val\":\"\"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
        currentSpn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                userSelect = true;
                return false;
            }
        });
        currentSpn.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(userSelect){
                    String cmd = "{\"cmd\":\"exe\",\"key\":\"current_mode\",\"val\":\""+position+"\"}";
                    ConnectionService.sendCommand(
                            ConnectionService.SEND,cmd);
                    userSelect = false;
                }
            }
            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                userSelect = false;
            }

        });
    }

    private void mapView() {
        previousIco = view.findViewById(R.id.previousMode_ico);
        nextIco = view.findViewById(R.id.nextMode_ico);
        currentSpn = view.findViewById(R.id.currentMode_spn);

    }
}