package com.example.infinitybox.local_data;

public class Device {
    String ip;
    String mac;
    String name;

    public Device(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getMac() {
        return mac;
    }

    public void setMac(String mac) {
        this.mac = mac;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Device{" +
                "ip='" + ip + '\'' +
                ", mac='" + mac + '\'' +
                ", name='" + name + '\'' +
                '}';
    }
}
