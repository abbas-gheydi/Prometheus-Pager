#About the project:

  

The "Prometheus Pager" is an Arduino sketch for ESP8266 microcontrollers.

It Checks Prometheus API frequently to check for any alerts status changes.

If it detects any alert then starts blinking, you can change the action from blinking to anything you want, like some buzzer alert or vibration and so on.

What Do You Need Before the Beginning:

1 - an Arduino compatible ESP8266 board

2 - Arduino IDE

  

#How To Use:

You must add some dependency in the library manager of the Arduino IDE.

Open arduino IDE > file > preferences > Additional Boards manager URLs and paste

```

[http://arduino.esp8266.com/stable/package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json)

```

Then go to tools > Manage library > search and install 'ESP8266' library

Open Prometheus.ino and edit this value to connect to your wireless and Prometheus server

  

```

#define WIFISSID "YOUR WIFI SSID"

#define PASSWORD "WIFI PASSWORD"

String URLADDR = "http://192.168.1.10:9090/api/v1/alerts"; //promthues address

```

Then Click On Verify and Upload.

## License

MIT
