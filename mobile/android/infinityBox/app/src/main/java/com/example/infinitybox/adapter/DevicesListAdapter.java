package com.example.infinitybox.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.example.infinitybox.R;
import com.example.infinitybox.local_data.Device;
import com.example.infinitybox.local_data.LocalDataManager;

import java.util.List;

public class DevicesListAdapter extends ArrayAdapter<Device> {
    public DevicesListAdapter(@NonNull Context context, int resource, @NonNull List<Device> objects) {
        super(context, resource, objects);
    }

    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        convertView = LayoutInflater.from(parent.getContext()).inflate(R.layout.device_item, parent, false);

        TextView deviceIp = convertView.findViewById(R.id.device_item_ip_tw);

        deviceIp.setText(getItem(position).getIp());
        return convertView;
    }
    public static void updateDevicesList(ListView view){

        DevicesListAdapter devicesListAdapter = new DevicesListAdapter(
                view.getContext(),
                R.id.list_device_ltw,
                LocalDataManager.getInstance().getDevices()
        );
        view.setAdapter(devicesListAdapter);

    }
}
