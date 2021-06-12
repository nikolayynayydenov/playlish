# Playlish
Екипен проект за курс по качествен програмен код във ФМИ, 2021

# SQLAPI++ конфигурация:
1. Сваляте trail версията на библиотеката от тук: https://sqlapi.com/Download/ в папка D:\Programs (иначе ще имаме проблеми с git)
2. Във Visual Studio - Десен бутон на проекта -> properties -> VC++ directories -> include directories -> edit -> new line -> добавяте пътят до include директорията на sqlapi - "D:\Programs\SQLAPI\include"
3. Десен бутон на проекта -> properties -> Linker -> General -> Additional Library Directories -> edit -> New line ->  D:\Programs\SQLAPI\vs2019\lib
4. Десен бутон на проекта -> properties -> Linker -> Input -> Additional Dependancies  -> Edit -> sqlapid.lib
5. properties -> Build Events -> Post-Build Event -> Command Line -> пействате това: "xcopy /y/d D:\Programs\SQLAPI\vs2019\bin\sqlapid.dll $(OutDir)"


# SQL Server конфигурация:
1. След като сте инсталирали SQL Server и SSMS Създавате login и user - https://www.youtube.com/watch?v=11Rx35l8Khc
2. Allow remote connections - https://www.youtube.com/watch?v=5UkHYNwUtCo
3. Копирате db_credentials.example в същата папка и го преименувате на db_credentials. В този файл задавате вашите креденшъли да базата
