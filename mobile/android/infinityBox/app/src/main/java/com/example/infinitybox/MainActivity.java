package com.example.infinitybox;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Messenger;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.example.infinitybox.adapter.DevicesListAdapter;
import com.example.infinitybox.local_data.Device;
import com.example.infinitybox.local_data.LocalDataManager;
import com.example.infinitybox.services.ConnectionService;

import java.util.List;

import static com.example.infinitybox.adapter.DevicesListAdapter.updateDevicesList;

public class MainActivity extends AppCompatActivity {
    ServiceConnection connectionService;

    ListView listDevices_ltw;
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.add_device, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        int id = item.getItemId();
        switch (id){
            case R.id.add_device_button:
                Intent intent = new Intent(this,ConnectionActivity.class);
                startActivity(intent);
                break;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mapView();
        init();
        setEvent();


    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(connectionService);
    }

    void init(){
        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle("TIÊU ĐỀ ACTIVITY"); //Thiết lập tiêu đề nếu muốn
        updateDevicesList(listDevices_ltw);
        Intent intent = new Intent(this, ConnectionService.class);
        connectionService =
                new ServiceConnection() {
                    @Override
                    public void onServiceConnected(ComponentName name, IBinder service) {
                        ConnectionService.messengerService = new Messenger(service);
                    }

                    @Override
                    public void onServiceDisconnected(ComponentName name) {

                    }
                };
        bindService(intent,connectionService
                , BIND_AUTO_CREATE);



    }
    void mapView(){
        listDevices_ltw = findViewById(R.id.list_device_ltw);
    }
    void setEvent(){
    listDevices_ltw.setOnItemClickListener(new AdapterView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            ConnectionService.sendCommand(ConnectionService.DISCONNECT,null);
            Device device = (Device) listDevices_ltw.getAdapter().getItem(position);
            String ip = device.getIp();
            BroadcastReceiver mRefreshReceiver;
            IntentFilter filter = new IntentFilter();
            filter.addAction("onOpen");
            filter.addAction("onFailure");
            mRefreshReceiver = new BroadcastReceiver() {
                @Override
                public void onReceive(Context context, Intent intent) {
                    if(intent.getAction().equals("onOpen")){
                        startActivity(new Intent(view.getContext(),ControlActivity.class));
                    }else if(intent.getAction().equals("onFailure")){
                        Toast.makeText(view.getContext(),"Lost connect", Toast.LENGTH_LONG).show();
                        startActivity(new Intent(view.getContext(),MainActivity.class));
                    }
                }
            };
            LocalBroadcastManager.getInstance(view.getContext()).registerReceiver(mRefreshReceiver, filter);
            ConnectionService.sendCommand(ConnectionService.CONNECT,ip);
        }
    });
    }




}