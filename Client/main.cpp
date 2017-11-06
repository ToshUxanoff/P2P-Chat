#include "clientwindow.h"
#include "grasshopper.h"
#include <QApplication>
#include <stdio.h>
#include <time.h>


int ServerPort = 9090;
QString ServerIP ("127.0.0.1");

int main(int argc, char* argv[])
{
    uint8_t testvec_key[32];
            QByteArray test(QCryptographicHash::hash("Username", QCryptographicHash::Sha256).toHex());
            for(int i = 0; i < 32; ++i)
            {
                testvec_key[i] = test[i];
            }

            QByteArray testText("Do sdfds i have a QString with a hex code of one Char in it. I want to get the Char. ");
            uint8_t testvec_pt[512];
            for(int i = 0; i < testText.size(); ++i)
            {
                testvec_pt[i] = testText[i];
            }
            kuz_key_t key;
            w128_t x;
            kuz_init();

            kuz_set_encrypt_key(&key, testvec_key);
            for (int i = 0; i < 512; i++)
            {
                x.b[i] = testvec_pt[i];
            }
            kuz_encrypt_block(&key, &x);

            kuz_set_decrypt_key(&key, testvec_key);
            kuz_decrypt_block(&key, &x);

            printf("Decrypted Text\t=");

            for(int i = 0; i < 512; ++i)
            {
                printf("%c" , x.b[i]);
            }

    QApplication a(argc, argv);
    ClientWindow w(ServerPort, ServerIP);
    w.show();
    return a.exec();
}
