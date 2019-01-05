import hypermedia.net.*;

UDP udp; 

void setup() {
  udp = new UDP( this, 6767 ); 
  //udp.log( true );        
  udp.listen( true );
}

void draw()
{
}

void keyPressed() {
  String ip       = "192.168.253.55"; 
  int port        = 1998;       
  String msg = ""+key;
  udp.send(msg, ip, port );
}

void receive( byte[] data ) {       
  for (int i=0; i < data.length; i++)
    print(char(data[i]));
  println();
}
