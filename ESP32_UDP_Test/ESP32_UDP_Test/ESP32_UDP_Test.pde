import hypermedia.net.*;

UDP udp; 
String remoteIp = "255.255.255.255";
static int remotePort = 1998;
boolean[] remoteIpPortInitialized={false,false};

void setup() {
  udp = new UDP( this, 6767 ); 
  udp.listen( true );
}

void draw()
{
}

void keyPressed() {
  String msg = ""+key;
  println("you sent "+ msg+" to ip: "+ remoteIp);
  if (key == 's') {
    udp.send("UDP_START", remoteIp, remotePort );
  } else {
    udp.send(msg, remoteIp, remotePort );
  }
}

void receive( byte[] data ) {  
  if (!remoteIpPortInitialized[0]) {
    String udp_connected_receive = "";
    for (int i=0; i < data.length; i++) {
      udp_connected_receive+=char(data[i]);
    }
    udp_connected_receive+='\0';
    if (udp_connected_receive.equals("UDP Connected\0")) {
      println(udp_connected_receive);
      remoteIpPortInitialized[0] = true;
    }else{
      println("UDP not connected");
    }
  } else if(!remoteIpPortInitialized[1]){
    remoteIp = "";
    for (int i=0; i < data.length; i++) {
      remoteIp+=int(data[i]);
      if(i<3){
        remoteIp+=".";
      }
    }
    println("Remote IP: "+remoteIp);
    remoteIpPortInitialized[1] = true;
  } 
  else {
    for (int i=0; i < data.length; i++) {
      //A+=char(data[i]);
      //print(int(data[i]));
      print(char(data[i]));
    }
    println();
  }
}
