package com.example.arduinocar;

import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import okhttp3.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Objects;

public class MainActivity extends AppCompatActivity {

    private WebSocket socket;
    private final String SERVER_PATH = "http://192.168.1.6:3000/";
    private Button forward, backward, turnLeft, turnRight;
    private String message;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE); /* will hide the title */
        Objects.requireNonNull(getSupportActionBar()).hide(); /* hide the title */

        setContentView(R.layout.activity_main);
        initSocketConnection();

        forward = findViewById(R.id.btnForward);
        backward = findViewById(R.id.btnBackward);
        turnRight = findViewById(R.id.btnRight);
        turnLeft = findViewById(R.id.btnLeft);

        forward.setOnClickListener(v -> {
            message = forward.getText().toString();
            socket.send(message);
        });
        backward.setOnClickListener(v -> {
            message = backward.getText().toString();
            socket.send(message);
        });
        turnRight.setOnClickListener(v -> {
            message = turnRight.getText().toString();
            socket.send(message);
        });
        turnLeft.setOnClickListener(v -> {
            message = turnLeft.getText().toString();
            socket.send(message);
        });
    }

	/*
	 * Descrip: initialize socket connect to server
	 */
    private void initSocketConnection() {
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder().url(SERVER_PATH).build();
        SocketListener listener = new SocketListener(this);
        socket = client.newWebSocket(request, listener);
    }

    private static class SocketListener extends WebSocketListener {

        public MainActivity mainActivity;
        public SocketListener(MainActivity mainActivity) {
            this.mainActivity = mainActivity;
        }

        @Override
        public void onFailure(WebSocket webSocket, Throwable t, @Nullable Response response) {
            super.onFailure(webSocket, t, response);
            mainActivity.runOnUiThread(() -> Toast.makeText(mainActivity, t.toString(), Toast.LENGTH_LONG).show());
            Log.d("error", t.toString());
        }

        @Override
        public void onOpen(@NotNull WebSocket webSocket, @NotNull Response response) {
            super.onOpen(webSocket, response);
            mainActivity.runOnUiThread(() -> Toast.makeText(mainActivity, "Connection Established", Toast.LENGTH_LONG).show());
        }
    }
}