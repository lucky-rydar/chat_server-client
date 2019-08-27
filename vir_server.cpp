#include <iostream>
#include <windows.h>
//#include <winsock2.h>
#include <thread>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std; // this is server

void recving(SOCKET s)
{
	char buff[64] = "";
	

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
	SOCKET s, new_socket;
	struct sockaddr_in client_data;
	char message[64];



	if (WSAStartup(MAKEWORD(2, 2), &wsaD) != 0)
	{
		cout << "Error wsa sturtup: " << WSAGetLastError() << endl;
		system("pause");
		return 1;
	}
	cout << "Initialized! Error: 0" << endl;


	s = socket(AF_INET, SOCK_STREAM, NULL);
	if (s == INVALID_SOCKET)
	{
		cout << "Invalid making a socket: " << WSAGetLastError() << endl;
		system("pause");
		return 1;
	}
	cout << "Socket Created: 0" << endl;

	//initializing input connection
	client_data.sin_family = AF_INET;
	client_data.sin_port = htons(27015);
	client_data.sin_addr.s_addr = INADDR_ANY; // mean that a client can be with any IP


	auto check_bind = ::bind(s, (const sockaddr*)&client_data, sizeof(client_data));
	if (check_bind == SOCKET_ERROR)
	{
		cout << "Error binding: " << WSAGetLastError() << endl;
		system("pause");
		return 1;
	}
	cout << "Bind done: 0" << endl;

	// set listening mode
	listen(s, 3);
	
	//accept a connection
	int size_data_addr = sizeof(client_data);
	new_socket = accept(s, (struct sockaddr*)& client_data, &size_data_addr);
	if (new_socket == INVALID_SOCKET)
	{
		cout << "Error new connection: " << WSAGetLastError() << endl;
		system("pause");
		return 1;
	}
	cout << "Connection accepted: " << WSAGetLastError() << endl;

	

	std::system("cls");
	thread a(recving, new_socket);
	a.detach();
	
	


	while (true)
	{

		cin >> message;

		if (!send(new_socket, message, strlen(message), NULL))
		{
			cout << "No internet connection" << endl;
			return 1;
		}


	}




	system("pause");
	closesocket(s);
	WSACleanup();
	return 0;
}
