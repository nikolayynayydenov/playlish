// playlish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "./App.h"

#include <stdio.h>  // for printf
#include <SQLAPI.h> // main SQLAPI++ header

int main(int argc, char* argv[]) {
    SAConnection con;

    try {
        con.Connect(_TSA("DESKTOP-GI5Q4L5\\SQLEXPRESS@playground"), _TSA("nikolay"), _TSA("querty"), SA_SQLServer_Client);
        printf("We are connected!\n");

        SACommand insert(&con);
        insert.setCommandText(_TSA("INSERT INTO articles (name) VALUES (:1)"));
        insert << _TSA("Tom Patt");
        insert.Execute();

        con.Disconnect();
        printf("We are disconnected!\n");
    }
    catch (SAException& x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    return 0;
}