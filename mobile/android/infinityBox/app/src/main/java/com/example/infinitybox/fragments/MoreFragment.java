package com.example.infinitybox.fragments;

import android.app.Fragment;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;


import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Spinner;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.example.infinitybox.local_data.Device;
import com.example.infinitybox.services.ConnectionService;
import com.example.infinitybox.R;

import java.util.ArrayList;
import java.util.List;

public class MoreFragment extends Fragment {
    View view;

    SeekBar brightnessSbr;
    SeekBar speedSbr;
    SeekBar intensitySbr;

    Spinner symmetric_spn;
    String listSym[]={
            "VERTEX",
            "NO SYMMETRY",
            "SURFACE"};

    Button freezeBtn;
    boolean isPause;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    private void mapEvent() {
        symmetric_spn.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {

                String cmd = "";
                if(position == 2)
                    cmd = "{\"cmd\":\"exe\",\"key\":\"sym_surface_btn\",\"val\":\"\"}";
                if(position == 1)
                    cmd = "{\"cmd\":\"exe\",\"key\":\"sym_no_sym_btn\",\"val\":\"\"}";
                if(position == 0)
                    cmd = "{\"cmd\":\"exe\",\"key\":\"sym_vertex_btn\",\"val\":\"\"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd);

            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
        brightnessSbr.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"brightness_sld\",\"val\":"+progress+"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
        speedSbr.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"speed_sld\",\"val\":"+progress+"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
        intensitySbr.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                String cmd =
                        "{\"cmd\":\"exe\",\"key\":\"intensity_sld\",\"val\":"+progress+"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
        freezeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String cmd;
                if(isPause)
                    cmd = "{\"cmd\":\"exe\",\"key\":\"pause_tgl\",\"val\":\"true\"}";
                else
                    cmd = "{\"cmd\":\"exe\",\"key\":\"pause_tgl\",\"val\":\"false\"}";
                ConnectionService.sendCommand(
                        ConnectionService.SEND,cmd
                );

            }
        });
    }

    private void mapView() {
        speedSbr = view.findViewById(R.id.speed_sbr);
        brightnessSbr = view.findViewById(R.id.brightness_sbr);
        intensitySbr = view.findViewById(R.id.intensity_sbr);

        symmetric_spn = view.findViewById(R.id.symmetry_spn);

        freezeBtn = view.findViewById(R.id.freeze_btn);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        view = inflater.inflate(R.layout.fragment_more, container, false);
        mapView();
        mapEvent();
        init();
        return view;
    }

    private void init() {
        ArrayAdapter<String> spinnerAdapter;
        spinnerAdapter = new ArrayAdapter<String>(view.getContext(),
                R.layout.support_simple_spinner_dropdown_item,
                listSym);

        spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        symmetric_spn.setAdapter(spinnerAdapter);

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

                    if(key.equals("speed_sld")){
                        speedSbr.setProgress(Integer.parseInt(val));
                    }else if(key.equals("brightness_sld")){
                        brightnessSbr.setProgress(Integer.parseInt(val));
                    }else if(key.equals("intensity_sld")){
                        intensitySbr.setProgress(Integer.parseInt(val));
                    }else if(key.equals("pause_tgl")){
                        isPause = val.equals("true")?false:true;
                        if(isPause){
                            freezeBtn.setText("Resume");
                        }else{
                            freezeBtn.setText("Pause");
                        }
                    }
                }

            }
        };
        LocalBroadcastManager.getInstance(view.getContext()).registerReceiver(mRefreshReceiver, filter);
        ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");

    }
}