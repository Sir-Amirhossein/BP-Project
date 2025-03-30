#include "orders2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "orders.h"
#include "database2.h"
extern date main_date;
extern sqlite3*db;
extern char *errorMsg;
int moghayese_date(int year,int mounth,int day){
    if((year-main_date.year)>0)
        return 1;
    else if((year-main_date.year)==0){
        if((mounth-main_date.mounth)>0)
            return 1;
        else if((mounth-main_date.mounth)==0){
            if((day-main_date.day)>0)
                return 1;
            else if((day-main_date.day)==0)
                return 0;
            else
                return -1;
        }
        else
            return -1;
    }
    else
        return -1;
}
long long int tabdil_time_be_adad(int year,int mounth,int day){
    long long int sum=0;
    sum=(year*360)+(mounth*30)+(day);

    return sum;
}
int tashkhis_saat_baraye_gereftan_ghaza(char self_id[10],char type_meal[10]){
    self*sself= cheack_self(self_id);
    if(strcmp(sself->meal,"lunch")==0){
        if((main_date.hour>=sself->lunch_start)&&(main_date.hour<=sself->lunch_finish))
            return 1;
        else
            return 0;
    }
    if(strcmp(sself->meal,"dinner")==0){
        if((main_date.hour>=sself->dinner_start)&&(main_date.hour<=sself->dinner_finish))
            return 1;
        else
            return 0;
    }
    if(strcmp(sself->meal,"both")==0){
        if(strcmp(type_meal,"lunch")==0){
            if((main_date.hour>=sself->lunch_start)&&(main_date.hour<=sself->lunch_finish))
                return 1;
            else
                return 0;
        }
        else if(strcmp(type_meal,"dinner")==0){
            if(strcmp(sself->meal,"dinner")==0) {
                if ((main_date.hour >= sself->dinner_start) && (main_date.hour <= sself->dinner_finish))
                    return 1;
                else
                    return 0;
            }
        }
    }
    free(sself);
    return 0;
}

int callback_news(void*data,int num,char**soton,char**esme_soton){
    news*khabar=(news*)data;
    char*ptr;
    khabar->id=strtol(soton[0],&ptr,10);
    strcpy(khabar->title,soton[1]);
    strcpy(khabar->content,soton[2]);
    khabar->tarikh.year=strtol(soton[3],&ptr,10);
    khabar->tarikh.mounth=strtol(soton[4],&ptr,10);
    khabar->tarikh.day=strtol(soton[5],&ptr,10);
    if(moghayese_date(khabar->tarikh.year,khabar->tarikh.mounth,khabar->tarikh.day)>=0){
        printf("Title : %s\n",khabar->title);
        printf("Content : %s\n",khabar->content);
        printf("End time news : %d-%d-%d\n",khabar->tarikh.year,khabar->tarikh.mounth,khabar->tarikh.day);
    }
    return 0;
}
void print_news(){
    char*sql="SELECT * FROM NEWS;";
    news*khabar=(news*)malloc(sizeof(news));
    khabar->id=-1;
    int exe= sqlite3_exec(db,sql,callback_news,(void*)khabar,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return ;
    }
    if(khabar->id==(-1)){
        printf("there isn't any news...\n");
    }
    free(khabar);

}
int add_news(news*khabar,user*new_user){
    if(stricmp(new_user->type,"student")==0)
        return 2;
    char sql[10000];
    sprintf(sql,"INSERT INTO NEWS (TITLE,CONTENT,"
                "YEAR,MOUNTH,DAY) VALUES ('%s','%s','%d','%d','%d');",khabar->title,khabar->content,khabar->tarikh.year,khabar->tarikh.mounth,khabar->tarikh.day);
    int cheack= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    khabar->id=sqlite3_last_insert_rowid(db);
    return 0;
}

int callback_pool(void*data,int num,char**soton,char**esme_soton){
    pool *nazar=(pool*)data;
    int year,mounth,day;
    char question[1000];
    char first[20];
    char second[20];
    char third[20];
    char forth[20];
    char*ptr;
    nazar->id=strtol(soton[0],&ptr,10);
    strcpy(question,soton[1]);
    strcpy(first,soton[2]);
    strcpy(second,soton[3]);
    strcpy(third,soton[4]);
    strcpy(forth,soton[5]);
    year=strtol(soton[6],&ptr,10);
    mounth=strtol(soton[7],&ptr,10);
    day=strtol(soton[8],&ptr,10);
    if(moghayese_date(year,mounth,day)>=0){
        printf("question : %s\n",question);
        printf("first : %s\n",first);
        printf("second : %s\n",second);
        printf("third : %s\n",third);
        printf("forth : %s\n",forth);
        printf("End time news : %d-%d-%d\n",year,mounth,day);
    }
    return 0;
}
void print_pool(){
    pool *nazar=(pool*) malloc(sizeof(pool));
    nazar->id=(-1);
    char*sql="SELECT * FROM POOL;";
    int exe= sqlite3_exec(db,sql,callback_pool,(void*)nazar,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return ;
    }
    if(nazar->id==(-1)){
        printf("there isn't any polls\n");
    }
    free(nazar);
}
int add_pool(pool*nazar,user*new_user){
    if(stricmp(new_user->type,"student")==0)
        return 2;
    char sql[10000];
    sprintf(sql,"INSERT INTO POOL (QUESTION,FIRST,SECOND,THIRD,FORTH,"
                "YEAR,MOUNTH,DAY) VALUES ('%s','%s','%s','%s','%s','%d','%d','%d');",nazar->question,nazar->first,nazar->second,nazar->third,nazar->forth,nazar->year,nazar->mounth,nazar->day);
    int cheack= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    nazar->id=sqlite3_last_insert_rowid(db);
    return 0;
}

int reserve_food(user*new_user,char self_id[10],char type_meal[7],char food_id[7],int year,int mounth,int day){
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    if(cheack_self(self_id)==NULL|| cheack_food(food_id)==NULL)
        return 1;
    self*self_tmp= cheack_self(self_id);
    if((stricmp(new_user->gender,"male")==0)&&(stricmp(self_tmp->gender,"girlish")==0)){
        free(self_tmp);
        return 7;
    }
    if((stricmp(new_user->gender,"female")==0)&&(stricmp(self_tmp->gender,"boyish")==0)){
        free(self_tmp);
        return 7;
    }
    if((stricmp(self_tmp->meal,"lunch")==0&&stricmp(type_meal,"dinner")==0)||(stricmp(self_tmp->meal,"dinner")==0)&&stricmp(type_meal,"lunch")==0)
        return 10;
    free(self_tmp);
    meal_plan*barname_ghazai= cheack_meal_plan(self_id,food_id,type_meal,year,mounth,day);
    if(barname_ghazai==NULL)
        return 1;
    if((year!=barname_ghazai->year)||(mounth!=barname_ghazai->mounth)||(day!=barname_ghazai->day))
        return 11;
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)>14)
        return 15;
    if(barname_ghazai->count==0)
        return 4;//ghaza tamam shode ast
    char sql[500];
    food*ghaza= cheack_food(food_id);
    int hesab=new_user->credit-ghaza->price;
    if(hesab<0) {
        free(ghaza);
        return 5;//adam dashtan pol kafi
    }
    if(tabdil_time_be_adad(year,mounth,day)-tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)<2)
        return 6;//az mooed gozashte
    char ssql[500];
    sprintf(ssql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",hesab,new_user->user_id);
    int rcc= sqlite3_exec(db,ssql,NULL,NULL,&errorMsg);
    if(rcc!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    sprintf(sql,"INSERT INTO RESERVE (USER_ID,MEAL_ID,RESERVED) VALUES ('%s','%d','%d');",new_user->user_id,barname_ghazai->id,0);
    int cheack= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(cheack!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    int tedad=barname_ghazai->count-1;
    char sqll[200];
    sprintf(sqll,"UPDATE MEALPLAN SET COUNT='%d' WHERE ID='%d';",tedad,barname_ghazai->id);
    int rc= sqlite3_exec(db,sqll,NULL,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        printf("can't create table : %s\n",errorMsg);
        fprintf(stdout,"can't create a table : %s\n",errorMsg);
        exit(1);
    }
    free(barname_ghazai);
    free(ghaza);
    char rep[500];char r[500];
    sprintf(r,"user %s reserve food with id %s in self with id %s in %d-%d-%d;",new_user->user_id,self_id,food_id,year,mounth,day);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int callback_take_food(void*data,int num,char**soton,char**esm_soton){
    takefood*sefaresh=(takefood*)data;
    char*ptr;
    sefaresh->id=strtol(soton[0],&ptr,10);
    strcpy(sefaresh->user_id,soton[1]);
    strcpy(sefaresh->self_id,soton[2]);
    strcpy(sefaresh->type,soton[3]);
    strcpy(sefaresh->food_id,soton[4]);
    sefaresh->reserved=strtol(soton[5],&ptr,10);

    return 0;
}
int take_food(char self_id[10],user*new_user,char type_food[7],int year,int mounth,int day){
    self*selff= cheack_self(self_id);
    if(selff==NULL)
        return 1;
    if(strcmp(new_user->type,"admin")==0)
        return 2;
    char sql[1000];
    if(tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)- tabdil_time_be_adad(year,mounth,day)!=0)
        return 6;//be moed nareside rozesh ya gozashte
    if((strcmp(selff->meal,"lunch")==0&&strcmp(type_food,"dinner")==0)||(strcmp(selff->meal,"dinner")==0)&&strcmp(type_food,"lunch")==0)
        return 10;
    int n= tashkhis_saat_baraye_gereftan_ghaza(self_id,type_food);
    if(n==0){
        return 11;//saate moed nist
    }
    takefood*sefaresh=(takefood*)malloc(sizeof(takefood));
    sefaresh->id=-1;
    sprintf(sql,"SELECT MEAL_ID,USER_ID,SELF_ID,TYPE,FOOD_ID,RESERVED FROM RESERVE JOIN MEALPLAN ON RESERVE.MEAL_ID=MEALPLAN.ID WHERE USER_ID='%s' AND SELF_ID='%s' AND TYPE='%s' AND YEAR='%d'"
                "AND MOUNTH='%d' AND DAY='%d';",new_user->user_id,self_id,type_food,year,mounth,day);
    int rc= sqlite3_exec(db,sql,callback_take_food,(void*)sefaresh,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -1;
    }
    if(sefaresh->id==-1){
        free(sefaresh);
        return 12;
    }
    if(sefaresh->reserved==1)
        return 13;//ghablan in ghazaro gerefte
    meal_plan*ghaza= cheack_meal_plan(self_id,sefaresh->food_id,type_food,year,mounth,day);
    char ssql[100];
    sprintf(ssql,"UPDATE RESERVE SET RESERVED='%d' WHERE USER_ID='%s' AND MEAL_ID='%d';",1,new_user->user_id,ghaza->id);
    int rcc= sqlite3_exec(db,ssql,NULL,NULL,&errorMsg);
    if(rcc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -1;
    }
    free(sefaresh);
    free(ghaza);
    free(selff);
    char rep[500];char r[500];
    sprintf(r,"user %s take food at self with id %s in %d-%d-%d",new_user->user_id,self_id,year,mounth,day);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int callback_cancel_reserve(void*data,int num,char**soton,char**esm_soton){
    takefood*sefaresh=(takefood*)data;
    char*ptr;
    sefaresh->id= strtol(soton[0],&ptr,10);
    strcpy(sefaresh->user_id,soton[1]);
    strcpy(sefaresh->self_id,soton[2]);
    strcpy(sefaresh->type,soton[3]);
    strcpy(sefaresh->food_id,soton[4]);
    sefaresh->reserved=strtol(soton[5],&ptr,10);
    return 0;
}
int cancel_reserve(int year,int mounth,int day,char type[7],user*new_user){
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    takefood*sefaresh=(takefood*)malloc(sizeof(takefood));
    sefaresh->id=-1;
    char sql[500];
    sprintf(sql,"SELECT MEAL_ID,USER_ID,SELF_ID,TYPE,FOOD_ID,RESERVED FROM RESERVE JOIN MEALPLAN ON "
                "RESERVE.MEAL_ID = MEALPLAN.ID WHERE USER_ID='%s' AND YEAR='%d' AND MOUNTH='%d' AND DAY='%d' AND TYPE='%s';",new_user->user_id,year,mounth,day,type);
    int rc= sqlite3_exec(db,sql,callback_cancel_reserve,(void*)sefaresh,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -1;
    }
    if(sefaresh->id==-1){
        free(sefaresh);
        return 1;//hamchin reservi nist
    }
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)<0)
        return 4;//zaman gozashte
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)==0){
        self*sself= cheack_self(sefaresh->self_id);
        if(strcmp(type,"lunch")==0) {
            if (sself->lunch_start - main_date.hour >= 100) {
                char ssql[300];
                sprintf(ssql,"DELETE FROM RESERVE WHERE USER_ID='%s' AND MEAL_ID='%d';",new_user->user_id,sefaresh->id);
                int rrc= sqlite3_exec(db,ssql,NULL,NULL,&errorMsg);
                if(rrc!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                char sqll[300];
                meal_plan*meall= cheack_meal_plan(sself->self_id,sefaresh->food_id,type,year,mounth,day);
                int count=meall->count+1;
                sprintf(sqll,"UPDATE MEALPLAN SET COUNT='%d' WHERE ID='%d';",count,meall->id);
                int rcc= sqlite3_exec(db,sqll,NULL,NULL,&errorMsg);
                if(rcc!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                food*ghaza= cheack_food(sefaresh->food_id);
                int money=(new_user->credit)+(ghaza->price)*(0.9);
                char sqql[200];
                sprintf(sqql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",money,new_user->user_id);
                int exe= sqlite3_exec(db,sqql,NULL,NULL,&errorMsg);
                if(exe!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                free(meall);
                free(ghaza);
            }
        }
        else if(strcmp(type,"dinner")==0){
            if(sself->dinner_start-main_date.hour>=100){
                char ssql[300];
                sprintf(ssql,"DELETE FROM RESERVE WHERE USER_ID='%s' AND MEAL_ID='%d';",new_user->user_id,sefaresh->id);
                int rrc= sqlite3_exec(db,ssql,NULL,NULL,&errorMsg);
                if(rrc!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                char sqll[300];
                meal_plan*meall= cheack_meal_plan(sself->self_id,sefaresh->food_id,type,year,mounth,day);
                int count=meall->count+1;
                sprintf(sqll,"UPDATE MEALPLAN SET COUNT='%d' WHERE ID='%d';",count,meall->id);
                int rcc= sqlite3_exec(db,sqll,NULL,NULL,&errorMsg);
                if(rcc!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                food*ghaza= cheack_food(sefaresh->food_id);
                int money=(new_user->credit)+(ghaza->price)*(0.9);
                char sqql[200];
                sprintf(sqql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",money,new_user->user_id);
                int exe= sqlite3_exec(db,sqql,NULL,NULL,&errorMsg);
                if(exe!=SQLITE_OK){
                    fprintf(stderr,"sql error: %s",errorMsg);
                    return -1;
                }
                free(meall);
                free(ghaza);
            }

        }
        free(sself);
    }
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)>0){
        self*sself= cheack_self(sefaresh->self_id);
        char ssql[300];
        sprintf(ssql,"DELETE FROM RESERVE WHERE USER_ID='%s' AND MEAL_ID='%d';",new_user->user_id,sefaresh->id);
        int rrc= sqlite3_exec(db,ssql,NULL,NULL,&errorMsg);
        if(rrc!=SQLITE_OK){
            fprintf(stderr,"sql error: %s",errorMsg);
            return -1;
        }
        char sqll[300];
        meal_plan*meall= cheack_meal_plan(sself->self_id,sefaresh->food_id,type,year,mounth,day);
        int count=meall->count+1;
        sprintf(sqll,"UPDATE MEALPLAN SET COUNT='%d' WHERE ID='%d';",count,meall->id);
        int rcc= sqlite3_exec(db,sqll,NULL,NULL,&errorMsg);
        if(rcc!=SQLITE_OK){
            fprintf(stderr,"sql error: %s",errorMsg);
            return -1;
        }
        food*ghaza= cheack_food(sefaresh->food_id);
        int money=(new_user->credit)+(ghaza->price)*(0.9);
        char sqql[200];
        sprintf(sqql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",money,new_user->user_id);
        int exe= sqlite3_exec(db,sqql,NULL,NULL,&errorMsg);
        if(exe!=SQLITE_OK){
            fprintf(stderr,"sql error: %s",errorMsg);
            return -1;
        }
        free(ghaza);
        free(meall);
        free(sself);
    }
    free(sefaresh);
    char rep[500];char r[500];
    sprintf(r,"user %s cancel his/her food in %d-%d-%d",new_user->user_id,year,mounth,day);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int help_daily_reserve(user*new_user,char self_id[10],char food_id[10],char type[7],self*sself,food*ghaza){
    meal_plan*meall= cheack_meal_plan(self_id,food_id,type,main_date.year,main_date.mounth,main_date.day);
    if(meall==NULL)
        return -1;
    if(meall->count==0)
        return -3;
    int hesab=new_user->credit-ghaza->price-ghaza->price;
    if(hesab<0)
        return -2;
    char sql[200];
    sprintf(sql,"UPDATE USERS SET CREDIT='%d' WHERE USER_ID='%s';",hesab,new_user->user_id);
    int rc= sqlite3_exec(db,sql,NULL,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    int tedad=meall->count-1;
    char sqll[200];
    sprintf(sqll,"UPDATE MEALPLAN SET COUNT='%d' WHERE ID='%d';",tedad,meall->id);
    int rrc= sqlite3_exec(db,sqll,NULL,NULL,&errorMsg);
    if(rrc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    char sqql[200];
    sprintf(sqql,"INSERT INTO RESERVE (USER_ID,MEAL_ID,RESERVED)"
                 "VALUES ('%s','%d','%d');",new_user->user_id,meall->id,0);
    int rcc= sqlite3_exec(db,sqql,NULL,NULL,&errorMsg);
    if(rcc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    free(meall);
    return 0;
}
int daily_reserve(user*new_user,char self_id[10],char food_id[10]){
    self*sself= cheack_self(self_id);
    food*ghaza= cheack_food(food_id);
    if(sself==NULL)
        return 1;
    if(ghaza==NULL)
        return 10;
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    if(main_date.hour<1600){
        if(sself->lunch_finish-main_date.hour<30)
            return -4;//vaght tamam ast
        else{
            int n= help_daily_reserve(new_user,self_id,food_id,"lunch",sself,ghaza);
            if(n==0)return 0;if(n==-1)return -1;if(n==-3)return -3;if(n==-2)return -2;if(n==-100)
                return -100;
        }
    }
    else if(main_date.hour>=1600){
        if(sself->dinner_finish-main_date.hour<30)
            return -4;//vaght tamam ast
        else{
            int n= help_daily_reserve(new_user,self_id,food_id,"dinner",sself,ghaza);
            if(n==0)return 0;if(n==-1)return -1;if(n==-3)return -3;if(n==-2)return -2;if(n==-100)return -100;
        }
    }
    free(sself);
    free(ghaza);
    char rep[500];char r[500];
    sprintf(r,"user %s reserve daily food in %d-%d-%d",new_user->user_id,main_date.year,main_date.mounth,main_date.day);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
int callback_change_self(void*data,int num,char**soton,char**esm_soton){
    ksh*p=(ksh*)data;
    char*ptr;
    p->meal_id=strtol(soton[0],&ptr,10);
    strcpy(p->old_self_id,soton[1]);
    strcpy(p->food_id,soton[2]);
    return 0;
}
int change_self(user*new_user,int year,int mounth,int day,char type[7],char new_self_id[10]){
    if(stricmp(new_user->type,"admin")==0)
        return 2;
    self*selff= cheack_self(new_self_id);
    if(selff==NULL)
        return 1;
    ksh*p=(ksh*)malloc(sizeof(ksh));
    p->meal_id=-1;
    char sql[300];
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)<0)
        return 10;
    if(tabdil_time_be_adad(year,mounth,day)- tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)==0) {
        if (stricmp(type, "lunch") == 0) {
            if(selff->lunch_finish-main_date.hour<300)
                return 11;
        }
        else if (stricmp(type, "dinner") == 0) {
            if(selff->dinner_finish-main_date.hour<300)
                return 12;
        }
    }
    sprintf(sql,"SELECT MEAL_ID,SELF_ID,FOOD_ID FROM RESERVE JOIN MEALPLAN ON RESERVE.MEAL_ID=MEALPLAN.ID"
                " WHERE USER_ID='%s' AND YEAR='%d' AND MOUNTH='%d' AND DAY='%d' AND TYPE='%s';",new_user->user_id,year,mounth,day,type);
    int exe= sqlite3_exec(db,sql,callback_change_self,(void*)p,&errorMsg);
    if(exe!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    if(p->meal_id==-1){
        return 13;//hamchin ghazai reserve nakarde
    }
    meal_plan*meall= cheack_meal_plan(new_self_id,p->food_id,type,year,mounth,day);
    /*if(meall==NULL){
        //dar self mored nazar in ghaza serve nmishavad
        free(selff);
        free(p);
        return 7;
    }*/
    char ss[200];
    sprintf(ss,"UPDATE MEALPLAN SET SELF_ID='%s' WHERE ID='%d';",new_self_id,p->meal_id);
    int cheack= sqlite3_exec(db,ss,NULL,NULL,&errorMsg);
    if(cheack!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return -100;
    }
    char rep[500];char r[500];
    sprintf(r,"user %s change his/her self in %d-%d-%d",new_user->user_id,main_date.year,main_date.mounth,main_date.day);
    sprintf(rep,"INSERT INTO REPORTS (USER_ID,CONTENT) VALUES ('%s','%s');",new_user->user_id,r);
    int che = sqlite3_exec(db, rep, NULL, NULL, &errorMsg);
    if (che != SQLITE_OK) {
        fprintf(stderr, "sql error: %s\n", errorMsg);
        return 5;
    }
    return 0;
}
void change_date_time(int year,int mounth,int day,int hour){
    main_date.year=year;
    main_date.mounth=mounth;
    main_date.day=day;
    main_date.hour=hour;
}




