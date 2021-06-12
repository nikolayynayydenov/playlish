#pragma once
#include <stdio.h>  
#include <SQLAPI.h>

class DB
{
public:
    DB(DB const&) = delete;
    void operator=(DB const&) = delete;
    SAConnection connection;

    static DB& getInstance()
    {
        static DB instance;
        return instance;
    }

    static SAConnection& conn()
    {
        return DB::getInstance().connection;
    }
private:   

    DB() {
        try {
            connection.Connect(_TSA("DESKTOP-RL43607\\SQLEXPRESS01@playlish"), _TSA("test_login"), _TSA("test_login"), SA_SQLServer_Client);
        }
        catch (SAException& x) {
            connection.Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
        }
    }
};