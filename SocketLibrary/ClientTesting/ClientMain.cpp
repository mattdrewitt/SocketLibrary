#include <UDPClient.hpp>
#include <TCPClient.hpp>


using namespace std;

int main() {
	TCPClient tcpclient("127.0.0.1", 80);
	tcpclient.Connect();
	tcpclient.Recv(); //we want to recvive the welcome message that we get. 
						//eventually this will be 2 card values and the dealers cards 
	//want tp send "Ready"
	//string msg = "";
	//for(;;) {
	//	cin >> msg;
	//	if(msg == "e"){
	//		break;
	//	}
	//	else{
	//		tcpclient.Send(msg);
	//		tcpclient.Recv();
	//	}	
	//}

	cout << "sever send me something..." << endl;
	system("pause");
}

