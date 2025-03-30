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
const char name_database[] = "project_sqlite.db";
sqlite3 *db = NULL;
char *errorMsg=NULL;
extern date main_date;
//FILE*fp=fopen("outputfile.txt","w+");

int connect_to_database_users(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_users(){
    char*sql="CREATE TABLE USERS("  \
    "ID             INTEGER PRIMARY KEY   NOT NULL,"\
    "NAME               CHAR(38)          NOT NULL,"\
    "FAMILY             CHAR(38)          NOT NULL,"\
    "USER_ID            CHAR(32)          NOT NULL,"\
    "PASS               CHAR(32)          NOT NULL,"\
    "NATIONAL_ID        CHAR(12)          NOT NULL,"\
    "BIRTHDATE_YEAR       INT             NOT NULL,"\
    "BIRTHDATE_MOUNTH     INT             NOT NULL,"\
    "BIRTHDATE_DAY        INT             NOT NULL,"\
    "GENDER             CHAR(10)          NOT NULL,"\
    "TYPE               CHAR(10)          NOT NULL,"\
    "APPROVED            INT              NOT NULL,"\
    "CREDIT              INT              NOT NULL);";


    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    char*sql1="CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    int cheack2= sqlite3_exec(db,sql1,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_users(){
    char*sql="DELETE FROM USERS;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}
int connect_to_database_selfs(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}

void create_table_selfs(){
    char*sql="CREATE TABLE SELFS("  \
    "ID             INTEGER PRIMARY KEY   NOT NULL,"\
    "SELF_ID            CHAR(10)          NOT NULL,"\
    "NAME               CHAR(38)          NOT NULL,"\
    "LOCATION           CHAR(50)          NOT NULL,"\
    "CAPACITY             INT             NOT NULL,"\
    "GENDER             CHAR(10)          NOT NULL,"\
    "MEAL               CHAR(7)           NOT NULL,"\
    "LUNCH_START          INT                     ,"\
    "LUNCH_FINISH         INT                     ,"\
    "DINNER_START         INT                     ,"\
    "DINNER_FINISH        INT                     );";


    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    char*sql1="CREATE UNIQUE INDEX unique_self_id ON SELFS (SELF_ID);";
    int cheack2= sqlite3_exec(db,sql1,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_selfs(){
    char*sql="DELETE FROM SELFS;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}

int connect_to_database_foods(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_foods(){
    char*sql="CREATE TABLE FOODS("  \
    "ID             INTEGER PRIMARY KEY   NOT NULL,"\
    "FOOD_ID            CHAR(10)          NOT NULL,"\
    "NAME               CHAR(38)          NOT NULL,"\
    "TYPE               CHAR(10)          NOT NULL,"\
    "PRICE                INT             NOT NULL);";


    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    char*sql1="CREATE UNIQUE INDEX unique_food_id ON FOODS (FOOD_ID);";
    int cheack2= sqlite3_exec(db,sql1,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_FOODS(){
    char*sql="DELETE FROM FOODS;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}

int connect_to_database_meal_plan(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_meal_plan(){
    char*sql="CREATE TABLE MEALPLAN("  \
    "ID             INTEGER PRIMARY KEY   NOT NULL,"\
    "SELF_ID            CHAR(10)          NOT NULL,"\
    "YEAR                 INT             NOT NULL,"\
    "MOUNTH               INT             NOT NULL,"\
    "DAY                  INT             NOT NULL,"\
    "TYPE               CHAR(7)           NOT NULL,"\
    "FOOD_ID            CHAR(10)          NOT NULL,"\
    "COUNT                INT             NOT NULL);";


    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_meal_plan(){
    char*sql="DELETE FROM MEALPLAN;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}

int connect_to_database_reserve(){
    int rc= sqlite3_open(name_database,&db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
        fprintf(stdout,"Open database succesfully\n");
    }
    return 0;
}
void create_table_reserve(){
    char*sql="CREATE TABLE RESERVE("  \
    "ID             INTEGER PRIMARY KEY   NOT NULL,"\
    "USER_ID            CHAR(10)          NOT NULL,"\
    "MEAL_ID              INT             NOT NULL,"\
    "RESERVED             INT             NOT NULL);";


    int check= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(check!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    printf("creating table succesfully\n");

}
void delete_table_reserve(){
    char*sql="DELETE FROM RESERVE;";
    int cheack2= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack2!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
}

