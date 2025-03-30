#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "orders.h"
#include "database.h"
#include "orders2.h"
#include "database2.h"
#include "testcases.h"
#include "menu.h"
extern sqlite3 *db;
date main_date={2023,01,22,1700};

void show(void){
    printf("1)enter orders from a file\n");
    printf("2)enter order in consol\n");
}
user*komak;
user*log_in_user;
user admin = {-1,"admin","admin","admin","admin","0150551010",1990,12,12,"male","admin",1};

int main() {
    komak=(user*)malloc(sizeof(user));
    connect_to_database_reports();connect_to_database_users();connect_to_database_selfs();connect_to_database_foods();connect_to_database_meal_plan();connect_to_database_reserve();connect_to_database_news();connect_to_database_pool();
    delete_table_selfs();delete_table_reserve();delete_table_FOODS();delete_table_meal_plan();delete_table_users();delete_table_news();delete_table_pool();
    //create_table_reports();create_table_meal_plan();create_table_news();create_table_pool();create_table_users();create_table_foods();create_table_selfs();create_table_reserve();
    delete_table_pool();delete_table_news();delete_table_users();delete_table_meal_plan();delete_table_FOODS();delete_table_reserve();delete_table_selfs();
    user khodam={2,"amir","ahmadi","89456","123","4","1","1","1","male","student",1};
    self main={-1,"111","main_self","main",200,"male","lunch",1100,1400,0000,0000};
    food man={-1,"123","ghorme","food",12000};
    meal_plan ghaza={-1,"111",2023,01,22,"lunch","123",50};
    log_in_user=NULL;
    int n= register_in_site(&admin,log_in_user);
    fflush(stdin);int ni;
    show();
    fflush(stdin);scanf("%d",&ni);fflush(stdin);
    if(ni==1)
        testcase();
    else if(ni==2)
        menu();
    else
        printf("invalid input\n");

    return 0;
}
