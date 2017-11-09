#include "clientwindow.h"
#include "Kuznyechik.hpp"
#include "mycrypto.hpp"
#include <QApplication>
#include <string>
#include <vector>
#include <iostream>
int ServerPort = 9090;
QString ServerIP ("127.0.0.1");


int main(int argc, char* argv[])
{
    /*const ByteBlock key = hex_to_bytes("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
        std::string testmessstr("546573746f766f6520536f6f62736368656e6965");
        ByteBlock messageraw = hex_to_bytes(testmessstr);
        Kuznyechik test(key);
        std::vector<ByteBlock> message = split_blocks(messageraw, 16);
        //encrypt
        std::string debug;
        for(size_t i = 0; i < message.size(); ++i)
        {
            test.encrypt(message[i], message[i]);
            debug+= hex_representation(message[i]);
            //encoded:"56a9e7c7e86f73234bf893801c14934fc1328d13"
        }
        std::cout << debug <<std::endl;
        debug.clear();
        //decrypt
        for(size_t i = 0; i < message.size(); ++i)
       {
            test.decrypt(message[i], message[i]);
            debug += hex_representation(message[i]);
        }
        std::cout << debug;
        return 0;*/
   QApplication a(argc, argv);
    ClientWindow w(ServerPort, ServerIP);
    w.show();
    return a.exec();
}
