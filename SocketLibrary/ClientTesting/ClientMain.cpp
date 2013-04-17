#include <UDPClient.hpp>
#include <TCPClient.hpp>

using namespace std;

int main() {
	//UDPClient udpclient("127.0.0.1", 49154);
	//udpclient.connect();
	TCPClient tcpclient("127.0.0.1", 80);
	tcpclient.Connect();
	string msg = "";
	for(;;) {
		cin >> msg;
		if(msg == "e"){
			break;
		}
		else{
			tcpclient.Send(msg);
			tcpclient.Recv();
		}	
	}

	cout << "Shutting Down..." << endl;
}