package com.felix.carbrain;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.hardware.camera2.*;

import java.io.IOException;
import java.util.UUID;

public class CameraView extends AppCompatActivity {
    //Ble and Udp
    private BluetoothDevice bd;
    private BluetoothSocket sock;
    //SerialPortServiceClass_UUID = ‘{00001101-0000-1000-8000-00805F9B34FB}’
    private String uuid = "00001101-0000-1000-8000-00805F9B34FB"; //device
    private String ip = "127.0.0.1";
    private int port = 9100;
    private CmdThread cmdThread = null;

    //Camera
    private CameraManager manager;
    private CameraDevice device;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_view);
        Intent intent = getIntent();
        bd = intent.getParcelableExtra("BleDevice");
        ip = intent.getStringExtra("IP");
        cmdThread = new CmdThread(ip,port);
        try {
            sock = bd.createRfcommSocketToServiceRecord(UUID.fromString(uuid));
            sock.connect();
            if(sock.isConnected()){
                cmdThread.setBlueOutput(sock.getOutputStream());
                cmdThread.dial();
                cmdThread.start();
            }
        }catch (IOException e){

        }
        manager.openCamera(0,);
    }

    private CameraDevice.StateCallback callback = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(@NonNull CameraDevice camera) {

        }

        @Override
        public void onDisconnected(@NonNull CameraDevice camera) {

        }

        @Override
        public void onError(@NonNull CameraDevice camera, int error) {

        }
    }
}