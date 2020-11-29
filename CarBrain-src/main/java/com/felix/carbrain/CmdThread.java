package com.felix.carbrain;

import java.io.IOException;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class CmdThread extends Thread{
    private DatagramSocket sock;
    private String serverIP = "127.0.0.1";
    private int port = 9100;
    private OutputStream bleOutput;

    public CmdThread(String ip,int port){
        this.serverIP = ip;
        this.port = port;
        try{
            sock = new DatagramSocket(0);
        }catch (SocketException e){
            e.getMessage();
        }
    }

    public void setBlueOutput(OutputStream o){
        this.bleOutput = o;
        try{
            bleOutput.write("Hello".getBytes());
        }catch (IOException e){
            e.getMessage();
        }
    }

    public void dial(){
        String data = "A";
        try{
            DatagramPacket pack = new DatagramPacket(
                    data.getBytes(),
                    data.length(),
                    InetAddress.getByName(serverIP),
                    port);
            sock.send(pack);
        }catch (IOException e){
            e.getMessage();
        }
    }

    @Override
    public void run() {
        byte[] data = new byte[1];
        DatagramPacket pack = new DatagramPacket(data,0,data.length);
        while (true){
            try{
                sock.receive(pack);
                bleOutput.write(pack.getData());
            }catch (IOException e){
                e.getMessage();
            }
        }
    }
}