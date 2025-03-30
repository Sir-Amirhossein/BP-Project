#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "database.h"
#include "orders.h"
#include "orders2.h"
#include "database2.h"
extern const char name_database[];
extern date main_date;
extern sqlite3*db;
extern char *errorMsg;
int connect_to_database_news(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_news(){
    char*sql="CREATE TABLE NEWS("  \
    "ID             INTEGER PRIMARY KEY    NOT NULL,"\
    "TITLE               TEXT              NOT NULL,"\
    "CONTENT             TEXT              NOT NULL,"\
    "YEAR                INT               NOT NULL,"\
    "MOUNTH              INT               NOT NULL,"\
    "DAY                 INT               NOT NULL,"\
    "HOUR                INT                      );";

    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    char*sql1="CREATE UNIQUE INDEX unique_content ON NEWS (CONTENT);";
    int cheack2= sqlite3_exec(db,sql1,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_news(){
    char*sql="DELETE FROM NEWS;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}


int connect_to_database_pool(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_pool(){
    char*sql="CREATE TABLE POOL("  \
    "ID             INTEGER PRIMARY KEY    NOT NULL,"\
    "QUESTION            TEXT              NOT NULL,"\
    "FIRST             CHAR(20)            NOT NULL,"\
    "SECOND            CHAR(20)            NOT NULL,"\
    "THIRD             CHAR(20)            NOT NULL,"\
    "FORTH             CHAR(20)            NOT NULL,"\
    "YEAR                INT               NOT NULL,"\
    "MOUNTH              INT               NOT NULL,"\
    "DAY                 INT               NOT NULL);";

    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    char*sql1="CREATE UNIQUE INDEX unique_question ON POOL (QUESTION);";
    int cheack2= sqlite3_exec(db,sql1,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_pool(){
    char*sql="DELETE FROM POOL;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}
int connect_to_database_reports(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_reports(){
    char*sql="CREATE TABLE REPORTS("  \
    "ID             INTEGER PRIMARY KEY    NOT NULL,"\
    "USER_ID           CHAR(20)            NOT NULL,"\
    "CONTENT            TEXT               NOT NULL);";

    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_reports(){
    char*sql="DELETE FROM REPORTS;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}