package com.example.arduinoesp;

import android.app.Activity;
import android.content.Context;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;


public class MainActivity extends Activity {

    EditText editIp;
    Button btnUp, btnDown, btnRight, btnLeft;
    TextView textInfo1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        editIp = (EditText)findViewById(R.id.ip);
        btnUp = (Button)findViewById(R.id.btnUp);
        btnDown = (Button)findViewById(R.id.btnDown);
        btnLeft = (Button)findViewById(R.id.btnLeft);
        btnRight = (Button)findViewById(R.id.btnRight);
        textInfo1 = (TextView)findViewById(R.id.info1);

        btnUp.setOnTouchListener(btnUpClickListener);
        btnDown.setOnTouchListener(btnDownClickListener);
        btnLeft.setOnTouchListener(btnLeftClickListener);
        btnRight.setOnTouchListener(btnRightClickListener);

        String networkSSID = "ESP_TAILER";
        //String networkPass = "pass";

//        WifiConfiguration conf = new WifiConfiguration();
//        conf.SSID = "\"" + networkSSID + "\"";
//        conf.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
//
//
//        WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
//        wifiManager.addNetwork(conf);
//
//        List<WifiConfiguration> list = wifiManager.getConfiguredNetworks();
//        for( WifiConfiguration i : list ) {
//            if(i.SSID != null && i.SSID.equals("\"" + networkSSID + "\"")) {
//                wifiManager.disconnect();
//                wifiManager.enableNetwork(i.networkId, true);
//                wifiManager.reconnect();
//
//                break;
//            }
//        }
    }

    View.OnTouchListener btnUpClickListener = new View.OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            v.setSelected(true);
            String state;
            String serverIP = editIp.getText().toString()+":80";
            TaskEsp taskEsp = new TaskEsp(serverIP);

            if(event.getAction() == MotionEvent.ACTION_DOWN){
                state = "/up?state=on";
                taskEsp.execute(state);
            }else if(event.getAction() == MotionEvent.ACTION_UP){
                v.setSelected(false);
                state = "/up?state=off";
                taskEsp.execute(state);
            }
            return true;
        }
    };

    View.OnTouchListener btnDownClickListener = new View.OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            v.setSelected(true);
            String state;
            String serverIP = editIp.getText().toString()+":80";
            TaskEsp taskEsp = new TaskEsp(serverIP);

            if(event.getAction() == MotionEvent.ACTION_DOWN){
                state = "/down?state=on";
                taskEsp.execute(state);
            }else if(event.getAction() == MotionEvent.ACTION_UP){
                v.setSelected(false);
                state = "/down?state=off";
                taskEsp.execute(state);
            }
            return true;
        }
    };

    View.OnTouchListener btnLeftClickListener = new View.OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            v.setSelected(true);
            String state;
            String serverIP = editIp.getText().toString()+":80";
            TaskEsp taskEsp = new TaskEsp(serverIP);

            if(event.getAction() == MotionEvent.ACTION_DOWN){
                state = "/left?state=on";
                taskEsp.execute(state);
            }else if(event.getAction() == MotionEvent.ACTION_UP){
                v.setSelected(false);
                state = "/left?state=off";
                taskEsp.execute(state);
            }
            return true;
        }
    };

    View.OnTouchListener btnRightClickListener = new View.OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            v.setSelected(true);
            String state;
            String serverIP = editIp.getText().toString()+":80";
            TaskEsp taskEsp = new TaskEsp(serverIP);

            if(event.getAction() == MotionEvent.ACTION_DOWN){
                state = "/right?state=on";
                taskEsp.execute(state);
            }else if(event.getAction() == MotionEvent.ACTION_UP){
                v.setSelected(false);
                state = "/right?state=off";
                taskEsp.execute(state);
            }
            return true;
        }
    };

    private class TaskEsp extends AsyncTask<String, Void, String> {

        String server;

        TaskEsp(String server){
            this.server = server;
        }

        @Override
        protected String doInBackground(String... params) {

            String val = params[0];
            final String p = "http://"+server+val;

            runOnUiThread(new Runnable(){
                @Override
                public void run() {
                    textInfo1.setText(p);
                }
            });

            String serverResponse = "";
            HttpClient httpclient = new DefaultHttpClient();
            try {
                HttpGet httpGet = new HttpGet();
                httpGet.setURI(new URI(p));
                HttpResponse httpResponse = httpclient.execute(httpGet);

                InputStream inputStream = null;
                inputStream = httpResponse.getEntity().getContent();
                BufferedReader bufferedReader =
                        new BufferedReader(new InputStreamReader(inputStream));
                serverResponse = bufferedReader.readLine();

                inputStream.close();
            } catch (URISyntaxException e) {
                e.printStackTrace();
                serverResponse = e.getMessage();
            } catch (ClientProtocolException e) {
                e.printStackTrace();
                serverResponse = e.getMessage();
            } catch (IOException e) {
                e.printStackTrace();
                serverResponse = e.getMessage();
            }

            return serverResponse;
        }

        @Override
        protected void onPostExecute(String s) {
            //textInfo2.setText(s);
            btnUp.setEnabled(true);
            btnDown.setEnabled(true);
            btnLeft.setEnabled(true);
            btnRight.setEnabled(true);
        }
    }

}
