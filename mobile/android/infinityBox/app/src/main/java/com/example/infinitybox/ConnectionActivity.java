package com.example.infinitybox;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.infinitybox.local_data.Device;
import com.example.infinitybox.local_data.LocalDataManager;
import com.example.infinitybox.services.ConnectionService;

public class ConnectionActivity extends AppCompatActivity {
    Button connectBtn;
    Button openBtn;

    EditText ipDevice;

    Device device = null;
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.config_device, menu);
        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
            getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_baseline_arrow_back_24);
            getSupportActionBar().setTitle("");
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        int id = item.getItemId();
        switch (id){
            case android.R.id.home:
                startActivity(new Intent(this,MainActivity.class));
                break;
            case R.id.confirm_device:
                if ( device != null){
                    LocalDataManager.getInstance().addDevice(device);
                    startActivity(new Intent(this,MainActivity.class));
                }else{
                    Toast.makeText(this,"Can't add device", Toast.LENGTH_LONG).show();
                }


        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connection);
        mapView();
        setEvent();


    }

    private void setEvent() {
        connectBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openBtn.setEnabled(false);
                String ip = ipDevice.getText().toString().trim();
                ConnectionService.sendCommand(ConnectionService.DISCONNECT,null);
                connectBtn.setText("Connecting...");
                BroadcastReceiver mRefreshReceiver;
                IntentFilter filter = new IntentFilter();
                filter.addAction("onOpen");
                filter.addAction("onFailure");
                mRefreshReceiver = new BroadcastReceiver() {
                    @Override
                    public void onReceive(Context context, Intent intent) {
                        if(intent.getAction().equals("onOpen")){
                            connectBtn.setText("Connect");
                            device = new Device(ip);
                            openBtn.setEnabled(true);
                        }else if(intent.getAction().equals("onFailure")){
                            connectBtn.setText("Connect failed");
                        }
                    }
                };
                LocalBroadcastManager.getInstance(v.getContext()).registerReceiver(mRefreshReceiver, filter);
                ConnectionService.sendCommand(ConnectionService.CONNECT,ip);
            }
        });
        openBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(v.getContext(),ControlActivity.class));

            }
        });
    }

    private void mapView() {
        connectBtn = findViewById(R.id.connect_btn);
        openBtn = findViewById(R.id.open_btn);
        openBtn.setEnabled(false);
        ipDevice = findViewById(R.id.ip_device);
    }
}