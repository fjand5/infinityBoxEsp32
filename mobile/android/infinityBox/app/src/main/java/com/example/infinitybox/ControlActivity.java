package com.example.infinitybox;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.app.FragmentTransaction;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.infinitybox.fragments.ColorsFragment;
import com.example.infinitybox.fragments.FavoritesFragment;
import com.example.infinitybox.fragments.MoreFragment;
import com.example.infinitybox.fragments.PatternsFragment;
import com.example.infinitybox.services.ConnectionService;

public class ControlActivity extends AppCompatActivity {

    PatternsFragment patternsFragment;
    ColorsFragment colorsFragment;
    MoreFragment moreFragment;
    FavoritesFragment favoritesFragment;

    Button powerBtn;
    Boolean _isOn = false;

    Button pauseBtn;
    Boolean _isPause = false;


    Button reactBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        init();
        mapView();
        setEvent();

    }
    private void init(){
        patternsFragment = new PatternsFragment();
        colorsFragment = new ColorsFragment();
        moreFragment = new MoreFragment();
        favoritesFragment = new FavoritesFragment();

        showFragment(findViewById(R.id.colors_btn));

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

                    if(key.equals("on_off_tgl")){
                        if(val.equals("true")){
                            _isOn=true;
                            powerBtn.setBackgroundColor(Color.GRAY);
                        }
                        else{
                            _isOn=false;
                            powerBtn.setBackgroundColor(0xFF424242);

                        }
                    }
                    if(key.equals("timer_tgl")){
                        if(val.equals("true")){
                            _isPause=true;
                            pauseBtn.setBackgroundColor(Color.GRAY);
                        }
                        else{
                            _isPause=false;
                            pauseBtn.setBackgroundColor(0xFF424242);

                        }
                    }
                }

            }
        };
        LocalBroadcastManager.getInstance(this).registerReceiver(mRefreshReceiver, filter);
        ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"gal\"}");

    }
    private void setEvent() {
        powerBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(_isOn)
                    ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"exe\",\"key\":\"on_off_tgl\",\"val\":\"false\"}");
                else
                    ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"exe\",\"key\":\"on_off_tgl\",\"val\":\"true\"}");

            }
        });
        pauseBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(_isPause)
                    ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"exe\",\"key\":\"timer_tgl\",\"val\":\"false\"}");
                else
                    ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"exe\",\"key\":\"timer_tgl\",\"val\":\"true\"}");

            }
        });

        reactBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ConnectionService.sendCommand(ConnectionService.SEND,"{\"cmd\":\"exe\",\"key\":\"reactBright_btn\",\"val\":\"\"}");
            }
        });


    }

    private void mapView() {
        powerBtn = findViewById(R.id.power_btn);
        reactBtn = findViewById(R.id.react_btn);
        pauseBtn = findViewById(R.id.timer_btn);
    }

    public void showFragment(View view){
        FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
        switch (view.getId()){
            case R.id.patterns_btn:
                fragmentTransaction.replace(R.id.main_frm, patternsFragment);
                break;
            case R.id.colors_btn:
                fragmentTransaction.replace(R.id.main_frm, colorsFragment);
                break;
            case R.id.more_btn:
                fragmentTransaction.replace(R.id.main_frm, moreFragment);
                break;
            case R.id.favorites_btn:
                fragmentTransaction.replace(R.id.main_frm, favoritesFragment);
                break;
        }
        fragmentTransaction.commit();
    }


}