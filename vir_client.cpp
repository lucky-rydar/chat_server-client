#include <iostream>
#include <Windows.h>
//#include <winsock2.h>
#include <thread>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std; // this is client

void recving(SOCKET s)
{
	char buff[564];
	for (int i = 0; i < 64; i++)
	{
		buff[i] = ']';
	}

	while (true)
	{
		recv(s, buff, strlen(buff), NULL);

		for (int i = 0; i < 64; i++)
		{
			if (buff[i] != ']')
			{
				cout << buff[i];
			}
			else
			{
				continue;
			}

		}
		cout << endl;

		for (int i = 0; i < 64; i++)
		{
			buff[i] = ']';
		}
	}


}


int main() 
{

	WSADATA wsaD;
	SOCKET s;
	struct sockaddr_in server_data;
	//char message[256];

	if (WSAStartup(MAKEWORD(2,2), &wsaD) != 0)
	{
		cout << "Error wsa sturtup: " << WSAGetLastError() << endl;
		std::system("pause");
		return 1;
	}
	std::cout << "Initialized! Error: 0" << std::endl;


	s = socket(AF_INET, SOCK_STREAM, NULL);
	if (s == INVALID_SOCKET)
	{
		std::cout << "Invalid making a socket: " << WSAGetLastError() << std::endl;
		std::system("pause");
		return 1;
	}
	std::cout << "Socket Created: 0" << std::endl;


	//initializing server data of connection
	server_data.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_data.sin_port = htons(27015);
	server_data.sin_family = AF_INET;

	
	//connecting to server
	auto check_conn = connect(s, (const sockaddr*)&server_data, sizeof(server_data));
	if (check_conn != 0)
	{
		cout << "Error connection: " << WSAGetLastError() << endl;
		std::system("pause");
		return 1;
	}
	cout << "Connected" << endl;
	Sleep(1000);
	std::system("cls");




	
	
	
	

	
	//sending into chat
	char message[64] = "";

	thread all_recv(recving, s);
	all_recv.detach();

	while (true)
	{
		
		cin >> message;

		if (!send(s, message, strlen(message), NULL))
		{
			cout << "No internet connection" << endl;
			return 1;
		}


	}





	std::system("pause");
	closesocket(s);
	WSACleanup();
	return 0;
}
