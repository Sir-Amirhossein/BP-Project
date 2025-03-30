#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "orders2.h"
#include "database2.h"
extern user*komak;
extern date main_date;
extern sqlite3*db;
extern char *errorMsg;
int callback_cheak_user(void*data,int num,char**soton,char**satr){
    user*fech2=(user*)data;
    if(num!=13){
        fprintf(stderr,"these are not true inputs\n");
        return 1;
    }
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->name,soton[1]);
    strcpy(fech2->family,soton[2]);
    strcpy(fech2->user_id,soton[3]);
    strcpy(fech2->pass,soton[4]);
    strcpy(fech2->national_id,soton[5]);
    fech2->birthdate_year=strtol(soton[6],&ptr,10);
    fech2->birthdate_month=strtol(soton[7],&ptr,10);
    fech2->birthdate_day=strtol(soton[8],&ptr,10);
    strcpy(fech2->gender,soton[9]);
    strcpy(fech2->type,soton[10]);
    fech2->approved=strtol(soton[11],&ptr,10);
    fech2->credit=strtol(soton[12],&ptr,10);
    return 0;
}
int cheack_password(char user_id[12],char pass[32]){
    char sql[300];
    user*dech=(user*)malloc(sizeof(user));
    sprintf(sql,"SELECT * FROM USERS WHERE USER_ID='%s' AND PASS='%s';",user_id,pass);
    int rc= sqlite3_exec(db,sql,callback_cheak_user,(void*)dech,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return -100;
    }
    if(strcmp(pass,dech->pass)==0){
        free(dech);
        return 1;
    }
    free(dech);
    return 0;
}

user*cheack_user(const char user_id[12]){
    user*fech=(user*)malloc(sizeof(user));
    char sql[100];
    sprintf(sql,"SELECT * FROM USERS WHERE USER_ID = '%s';",user_id);
    fech->id=-1;
    int exe= sqlite3_exec(db,sql,callback_cheak_user,(void*)fech,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return NULL;
    }
    if(fech->id==(-1)){
        free(fech);
        return NULL;//hamchin adami nist aslan
    }
    if(fech->approved==0){
        komak->id=-2;
        return komak;
    }
    return fech;
}

int register_in_site(user*karbar,user*new_user){//new_user onie k login karde
    if((new_user!=NULL)&&strcmp(new_user->type,"admin")==0)
        karbar->approved=1;
    else if(new_user==NULL)
        karbar->approved=0;
    user*k=cheack_user(karbar->user_id);
    if(k!=NULL){
        free(k);
        return 2;
    }
    char sql[1020];
    sprintf(sql,"INSERT INTO USERS (NAME,FAMILY,USER_ID,"
                "PASS,NATIONAL_ID,BIRTHDATE_YEAR,BIRTHDATE_MOUNTH,BIRTHDATE_DAY,GENDER,TYPE,APPROVED,CREDIT) VALUES ('%s','%s','%s','%s','%s','%d','%d','%d','%s','%s','%d','ld');",karbar->name,karbar->family,karbar->user_id,karbar->pass,karbar->national_id,karbar->birthdate_year,karbar->birthdate_month,karbar->birthdate_day,karbar->gender,karbar->type,karbar->approved,0);
    int cheack= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    karbar->id=sqlite3_last_insert_rowid(db);
    return 0;
    //baraye sabt nam hamonja ke mikhay pas bedi check kon ke hame ro vared karde bashe

}
int log_out(user*karbar,char name[32]){//log_out(khoroji check_user,name gerefte hsode)
    if(strcmp(karbar->name,name)==0)
        return 0;
    return 1;
}
int change_pass(char user_id[32],char*old_pass,char*new_pass,user*new_user){
    if(new_user==NULL)
        return 1;
    if(strcmp(user_id,new_user->user_id)!=0)
        return 1;
    if(strcmp(new_user->pass,old_pass)!=0)
        return 2;
    char sql[100];
    sprintf(sql,"UPDATE USERS SET PASS='%s' WHERE USER_ID='%s';",new_pass,new_user->user_id);
    int chek= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(chek!=SQLITE_OK){
        fprintf(stderr,"sql error: %s\n",errorMsg);
        return 5;
    }
    return 0;
}
int approved_users(user*new_user,char users[1000][20],int satrha){//inja new user hamon karbar loginemone v to on matrixe ham bayad esm user ha ro benevisim to har radif matrix ham user id e
    if(stricmp(new_user->type,"student")==0)
        return 2;
    else {
        for (int i = 0; i < satrha; i++) {
            if (cheack_user(users[i]) == NULL)
                return 1;//yeki az karbaran dar list nist
            else {
                char sql[100];
                sprintf(sql, "UPDATE USERS SET APPROVED=1 WHERE USER_ID='%s';", users[i]);
                int chek = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
                if (chek != SQLITE_OK) {
                    fprintf(stderr, "sql error: %s\n", errorMsg);
                    return 5;
                }
            }
        }
    }
    return 0;
}
long long int change_student_pass(char user_id[32],char*new_pass,user*new_user){//user_id mishe id user va ... new_user karbare login kardast
    if(stricmp(new_user->type,"student")==0)
        return 2;
    if(cheack_user(user_id)==NULL||cheack_user(user_id)->id==-2)
        return 1;
    user*karbar= cheack_user(user_id);
    if(stricmp(karbar->type,"admin")==0)
        return 2;
    char sql[100];
    sprintf(sql,"UPDATE USERS SET PASS='%s' WHERE USER_ID='%s';",new_pass,user_id);
    int chek= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(chek!=SQLITE_OK){
        fprintf(stderr,"sql error: %s\n",errorMsg);
        return 5;
    }
    return 0;
}
int remove_user(char name[32],user*new_user) {//name user id hast user*new_user ham baraye karbare login shode hast
    if(strcmp(new_user->type,"student")==0)
        return 2;
    if(cheack_user(name)==NULL)
        return 1;
    if(stricmp(cheack_user(name)->type,"admin")==0)
        return 3;
    if (cheack_user(name) == NULL)
        return 1;
    char sql[210];
    sprintf(sql,"DELETE FROM USERS WHERE USER_ID='%s';",name);
    int chek = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
    if (chek != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int deactived_user(user*new_user,char user_id[20]){//inja new user hamon karbar loginemone v to on matrixe ham bayad esm user ha ro benevisim to har radif matrix ham user id e
    if(stricmp(new_user->type,"student")==0)
        return 2;
    if(cheack_user(user_id)==NULL)
        return 1;
    if(stricmp(cheack_user(user_id)->type,"admin")==0)
        return 2;
    else {
            if (cheack_user(user_id) == NULL|| cheack_user(user_id)->id==(-2))
                return 1;
            else {
                char sql[100];
                sprintf(sql, "UPDATE USERS SET APPROVED=0 WHERE USER_ID='%s';",user_id);
                int chek = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
                if (chek != SQLITE_OK) {
                    fprintf(stderr, "sql error: %s\n", errorMsg);
                    return 5;
                }
            }
    }
    return 0;
}
int charge_student_account(user*new_user,char*user_id,long int charge){
    if(cheack_user(user_id)==NULL)
        return 1;
    if(stricmp(new_user->type,"admin")!=0)
        return 2;
    if(stricmp(cheack_user(user_id)->type,"admin")==0)
        return 2;
    user*karbar= cheack_user(user_id);
    char sql[200];
    long int money=charge+karbar->credit;
    sprintf(sql,"UPDATE USERS SET CREDIT='%ld' WHERE USER_ID='%s';",money,user_id);
    int chek = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
    if (chek != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    char rep[500];char r[500];
    sprintf(r,"admin charge account user %s amount of %ld",user_id,charge);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int charge_account(user*new_user,long int charge){
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    char sql[200];
    long int money=charge+new_user->credit;
    sprintf(sql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",money,new_user->user_id);
    new_user->credit=money;
    int chek = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
    if (chek != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    char rep[500];char r[500];
    sprintf(r,"user %s charge his/her account amount of %ld",new_user->user_id,charge);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int send_charge(user*new_user,long int charge,char*user_id,char name[32]){
    if(cheack_user(user_id)==NULL)
        return 1;
    if(stricmp(name,(cheack_user(user_id)->name))!=0)
        return 4;
    if(strcmp(new_user->type,"admin")==0||stricmp(cheack_user(user_id)->type,"admin")==0)
        return 2;
    if(new_user->credit<charge)
        return 3;//invalid
    char ssql[200];
    int pol=new_user->credit-charge;
    sprintf(ssql,"UPDATE USERS SET CREDIT='%ld' WHERE USER_ID='%s';",pol,new_user->user_id);
    int rrc = sqlite3_exec(db, ssql, NULL, NULL, &errorMsg);
    if (rrc != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    char sql[200];
    user*karbar= cheack_user(user_id);
    long int money=charge+karbar->credit;
    sprintf(sql,"UPDATE USERS SET CREDIT='%ld' WHERE USER_ID='%s';",money,user_id);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    char rep[500];char r[500];
    sprintf(r,"user %s send charge to user %s amount of %ld",new_user->user_id,user_id,charge);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int chew = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (chew != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;

}
int callback_cheak_self(void*data,int num,char**soton,char**satr){
    self*fech2=(self*)data;
    if(num!=11){
        fprintf(stderr,"these are not true inputs\n");
        return 1;
    }
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->self_id,soton[1]);
    strcpy(fech2->name,soton[2]);
    strcpy(fech2->location,soton[3]);
    fech2->capacity=strtol(soton[4],&ptr,10);
    strcpy(fech2->gender,soton[5]);
    strcpy(fech2->meal,soton[6]);
    fech2->lunch_start=strtol(soton[7],&ptr,10);
    fech2->lunch_finish=strtol(soton[8],&ptr,10);
    fech2->dinner_start=strtol(soton[9],&ptr,10);
    fech2->dinner_finish=strtol(soton[10],&ptr,10);
    return 0;
}
self*cheack_self(const char self_id[10]){
    self*fech=(self*)malloc(sizeof(self));
    char sql[100];
    sprintf(sql,"SELECT * FROM SELFS WHERE SELF_ID = '%s';",self_id);
    fech->id=-1;
    int exe= sqlite3_exec(db,sql,callback_cheak_self,(void*)fech,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(fech->id==(-1)){
        free(fech);
        return NULL;
    }
    return fech;
}
int callback_cheak_food(void*data,int num,char**soton,char**satr){
    food*fech2=(food*)data;
    if(num!=5){
        fprintf(stderr,"these are not true inputs\n");
        return 1;
    }
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->food_id,soton[1]);
    strcpy(fech2->name,soton[2]);
    strcpy(fech2->type,soton[3]);
    fech2->price=strtol(soton[4],&ptr,10);
    return 0;
}
food*cheack_food(const char food_id[10]){
    food*fech=(food*)malloc(sizeof(food));
    char sql[100];
    sprintf(sql,"SELECT * FROM FOODS WHERE FOOD_ID = '%s';",food_id);
    fech->id=-1;
    int exe= sqlite3_exec(db,sql,callback_cheak_food,(void*)fech,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return NULL;
    }
    if(fech->id==(-1)){
        free(fech);
        return NULL;
    }
    return fech;
}
int define_self(self*new,user*new_user){
    if(stricmp(new_user->type,"student")==0)
        return 2;
    if(cheack_self(new->self_id)==NULL) {
        char sql[1020];
        sprintf(sql, "INSERT INTO SELFS (SELF_ID,NAME,LOCATION,"
                     "CAPACITY,GENDER,MEAL,LUNCH_START,LUNCH_FINISH,DINNER_START,DINNER_FINISH) VALUES ('%s','%s','%s','%d','%s','%s','%d','%d','%d','%d');",
                new->self_id, new->name, new->location, new->capacity, new->gender, new->meal, new->lunch_start,
                new->lunch_finish, new->dinner_start, new->dinner_finish);
        int cheack = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
        if (cheack != SQLITE_OK) {
            printf("can't create table : %s\n", errorMsg);
            fprintf(stdout, "can't create a table : %s\n", errorMsg);
            exit(1);
        }
        new->id = sqlite3_last_insert_rowid(db);
        return 0;
    }
    else{
        fprintf(stdout,"self already exist...\n");
        return 3;//3 baraye halate tekrari ast
    }
}
int define_food(food*new,user*new_user){
    if(stricmp(new_user->type,"student")==0)
        return 2;
    if(cheack_food(new->food_id)==NULL) {
        char sql[1020];
        sprintf(sql, "INSERT INTO FOODS (FOOD_ID,NAME,TYPE,"
                     "PRICE) VALUES ('%s','%s','%s','%ld');", new->food_id, new->name, new->type, new->price);
        int cheack = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
        if (cheack != SQLITE_OK) {
            printf("can't create table : %s\n", errorMsg);
            fprintf(stdout, "can't create a table : %s\n", errorMsg);
            exit(1);
        }
        new->id = sqlite3_last_insert_rowid(db);
        return 0;
    }
    else{
        fprintf(stdout,"food already exist...\n");
        return 3;//3 baraye halate tekrari ast
    }

}
int callback_cheak_meal_plan(void*data,int num,char**soton,char**satr){
    meal_plan*fech2=(meal_plan*)data;
    if(num!=8){
        fprintf(stderr,"these are not true inputs\n");
        return 1;
    }
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->self_id,soton[1]);
    fech2->year=strtol(soton[2],&ptr,10);
    fech2->mounth=strtol(soton[3],&ptr,10);
    fech2->day=strtol(soton[4],&ptr,10);
    strcpy(fech2->type,soton[5]);
    strcpy(fech2->food_id,soton[6]);
    fech2->count=strtol(soton[7],&ptr,10);
    return 0;
}
meal_plan*cheack_meal_plan(const char self_id[10],const char food_id[10],const char type[7],int year,int mounth,int day){
    meal_plan*fech=(meal_plan*)malloc(sizeof(meal_plan));
    char sql[200];
    sprintf(sql,"SELECT * FROM MEALPLAN WHERE SELF_ID = '%s' AND YEAR='%d' AND MOUNTH='%d' AND DAY='%d' AND FOOD_ID='%s' AND TYPE='%s';",self_id,year,mounth,day,food_id,type);
    fech->id=-12;
    int exe= sqlite3_exec(db,sql,callback_cheak_meal_plan,(void*)fech,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return NULL;
    }
    if(fech->id==(-12)){
        free(fech);
        return NULL;
    }
    return fech;
}
int define_meal_plan(meal_plan*meal,user*new_user){//new_user onie k login karde
    if(cheack_self(meal->self_id)==NULL|| cheack_food(meal->food_id)==NULL)
        return 1;
    if(stricmp(new_user->type,"student")==0)
        return 2;
    if(cheack_meal_plan(meal->self_id,meal->food_id,meal->type,meal->year,meal->mounth,meal->day)==NULL) {
        char sql[1020];
        sprintf(sql, "INSERT INTO MEALPLAN (SELF_ID,YEAR,MOUNTH,DAY,TYPE,"
                     "FOOD_ID,COUNT) VALUES ('%s','%d','%d','%d','%s','%s','%d');", meal->self_id, meal->year,
                meal->mounth, meal->day, meal->type, meal->food_id, meal->count);
        int cheack = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
        if (cheack != SQLITE_OK) {
            printf("can't create table : %s\n", errorMsg);
            fprintf(stdout, "can't create a table : %s\n", errorMsg);
            exit(1);
        }
        meal->id = sqlite3_last_insert_rowid(db);

        return 0;
    }
    else{
        fprintf(stdout,"meal_plan already exist...\n");
        return 3;//3 baraye halate tekrari ast
    }
}
int callback_news_testcase(void*data,int num,char**soton,char**esme_soton){
    news*khabar=(news*)data;
    char*ptr;
    strcpy(khabar->title,soton[1]);
    strcpy(khabar->content,soton[2]);
    khabar->tarikh.year=strtol(soton[3],&ptr,10);
    khabar->tarikh.mounth=strtol(soton[4],&ptr,10);
    khabar->tarikh.day=strtol(soton[5],&ptr,10);
    if(moghayese_date(khabar->tarikh.year,khabar->tarikh.mounth,khabar->tarikh.day)>=0){
        khabar->id=strtol(soton[0],&ptr,10);
    }
    return 0;
}
int cheak_news(user*new_user){
    if(strcmp(new_user->type,"admin")==0)
        return 2;
    char*sql="SELECT * FROM NEWS;";
    news*khabar=(news*)malloc(sizeof(news));
    khabar->id=-1;
    int exe= sqlite3_exec(db,sql,callback_news_testcase,(void*)khabar,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    if(khabar->id==-1){
        free(khabar);
        return 1;
    }
    free(khabar);
    return 0;
}
int callback_pool_testcase(void*data,int num,char**soton,char**esme_soton){
    pool*nazar=(pool*)data;
    char*ptr;
    strcpy(nazar->question,soton[1]);
    strcpy(nazar->first,soton[2]);
    strcpy(nazar->second,soton[3]);
    strcpy(nazar->third,soton[4]);
    strcpy(nazar->forth,soton[5]);
    nazar->year=strtol(soton[6],&ptr,10);
    nazar->mounth=strtol(soton[7],&ptr,10);
    nazar->day=strtol(soton[8],&ptr,10);
    if(moghayese_date(nazar->year,nazar->mounth,nazar->day)>=0){
        nazar->id=strtol(soton[0],&ptr,10);
    }
    return 0;
}
int cheak_pool(user*new_user){
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    pool*nazar=(pool*)malloc(sizeof(pool));
    nazar->id=-1;
    char*sql="SELECT * FROM POOL;";
    int exe= sqlite3_exec(db,sql,callback_pool_testcase,(void*)nazar,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    if(nazar->id==-1){
        free(nazar);
        return 1;
    }
    free(nazar);
    return 0;
}
