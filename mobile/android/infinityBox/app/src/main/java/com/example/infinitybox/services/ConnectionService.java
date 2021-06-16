package com.example.infinitybox.services;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanFilter;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.WebSocket;
import okhttp3.WebSocketListener;

import static androidx.core.app.ActivityCompat.requestPermissions;

public class ConnectionService extends Service {
    public static Messenger messengerService;

    public static final int CONNECT = 1;
    public static final int DISCONNECT = 2;
    public static final int SEND = 3;
    private Messenger messenger;
    private OkHttpClient client;
    WebSocket ws;

    private void connect(String url, Context context) {
        Request request = new Request.Builder().url("ws://"+url+":81").build();
        ws = client.newWebSocket(request, new WebSocketListener() {
            @Override
            public void onOpen(WebSocket webSocket, Response response) {
                super.onOpen(webSocket, response);
                Intent intent = new Intent();
                intent.setAction("onOpen");
                LocalBroadcastManager.getInstance(context).sendBroadcast(intent);
            }

            @Override
            public void onMessage(WebSocket webSocket, String text) {
                super.onMessage(webSocket, text);
                Intent intent = new Intent();
                intent.setAction("onMessage");
                intent.putExtra("data",text);
                LocalBroadcastManager.getInstance(context).sendBroadcast(intent);


            }

            @Override
            public void onFailure(WebSocket webSocket, Throwable t, Response response) {
                super.onFailure(webSocket, t, response);
                Intent intent = new Intent();
                intent.setAction("onFailure");
                LocalBroadcastManager.getInstance(context).sendBroadcast(intent);


            }


        });

        client.dispatcher().executorService().shutdown();
    }
    class ControlHandler extends Handler{
        private Context appContext;

        public ControlHandler(Context context) {
            this.appContext = context;
        }

        @Override
        public void handleMessage(@NonNull Message msg) {
            switch (msg.what){
                case CONNECT:
                    Log.d("htl","đang kết nối tới: " + msg.obj.toString());
                    try {
                        connect(msg.obj.toString(), appContext);

                    }
                    catch (Exception e){
                        Log.d("htl","không hợp lệ: " + msg.obj.toString());

                    }
                    break;
                case DISCONNECT:
                    client.dispatcher().executorService().shutdown();
                    client =  new OkHttpClient.Builder()
                            .connectTimeout(3, TimeUnit.SECONDS)
                            .build();
                    break;
                case SEND:
                    if(ws != null)
                        ws.send(msg.obj.toString());
                    break;
                default:
                    super.handleMessage(msg);
            }

        }



    }
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        messenger = new Messenger(new ControlHandler(this));
        return messenger.getBinder();
    }

    @Override
    public void onCreate() {
        super.onCreate();
        client =  new OkHttpClient.Builder()
                .connectTimeout(3, TimeUnit.SECONDS)
                .build();

    }

    public static void sendCommand(int cmd, Object obj){

        try {
            messengerService.send(
                    Message.obtain(null, cmd, obj));
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}