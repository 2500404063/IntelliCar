package com.felix.carbrain;

import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.bluetooth.*;
import android.widget.EditText;

import java.io.IOException;
import java.util.Set;

public class MainActivity extends AppCompatActivity {

    /*
    +VERSION=JDY-31-V1.35,Bluetooth V3.0
    +LADDR=77:D9:18:08:20:20
    +PIN=1234
    +NAME=FelixBle
    * */

    private BluetoothAdapter ba;
    private BluetoothDevice bd;

    private String MAC = "77:D9:18:08:20:20";
    private String PIN = "1234";

    private boolean found = false;

    private Button but_scan;
    private Button but_stop;
    private EditText list;
    private EditText iptext;

    private String bleList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ba = BluetoothAdapter.getDefaultAdapter();

        but_scan = (Button) findViewById(R.id.but_scan);
        but_stop = (Button) findViewById(R.id.but_stop);
        list = (EditText) findViewById(R.id.list);
        iptext = (EditText) findViewById(R.id.iptext);

        but_scan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openBluetooth();
                scan();
            }
        });

        but_stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ba.cancelDiscovery();
            }
        });
    }

    public boolean openBluetooth(){
        if(!ba.isEnabled()){
            return ba.enable();
        }else {
            return true;
        }
    }

    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (BluetoothDevice.ACTION_FOUND.equals(intent.getAction())) {
                bd = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                String Addr = bd.getAddress();
                bleList += "Found:"+bd.getName() + ":"+ Addr + "\n";
                list.setText(bleList);
                if(Addr.equals(MAC)){
                    list.setText("Founed Bluetooth Device!");
                    found = true;
                    connect();
                    ba.cancelDiscovery();
                }
            }
        }
    };

    public void scan(){
        bleList = "";
        Set<BluetoothDevice> devices = ba.getBondedDevices();
        for (BluetoothDevice i:devices){
            bleList += "Bound:"+ i.getName() + ":"+ i.getAddress() + "\n";
            list.setText(bleList);
            if(i.getAddress().equals(MAC)){
                list.setText("Founed Bluetooth Device!");
                found = true;
                bd = i;
                connect();
                break;
            }
        }
        if(!found){
            registerReceiver(receiver,new IntentFilter(BluetoothDevice.ACTION_FOUND));
            ba.startDiscovery();
        }
    }

    public void connect(){
        bd.setPin(PIN.getBytes());
        Intent intent = new Intent();
        intent.setClass(MainActivity.this,CameraView.class);
        intent.putExtra("IP",iptext.getText().toString());
        intent.putExtra("BleDevice",bd);
        startActivity(intent);
    }
}