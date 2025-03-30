#include "menuORDERS.h"
#include "menu.h"
#include "testcases.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "orders.h"
#include "database.h"
#include "orders2.h"
#include "database2.h"
#include <conio.h>
extern date main_date;extern sqlite3*db;extern char *errorMsg;extern user*log_in_user;extern user admin;
int callback_approve_menu(void*data,int num,char**soton,char**esm_soton){
    char name[20];char family[20];char user_id[20];char type[10];
    strcpy(name,soton[0]);
    strcpy(family,soton[1]);
    strcpy(user_id,soton[2]);
    strcpy(type,soton[3]);
    printf("%s  %s        %s          %s\n",name,family,user_id,type);
    return 0;
}
void approve_menu(void){
    char sql[200];
    sprintf(sql,"SELECT NAME,FAMILY,USER_ID,TYPE FROM USERS WHERE APPROVED='%d';",0);
    int rc= sqlite3_exec(db,sql,callback_approve_menu,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return;
    }
}
int callback_deactivate_menu(void*data,int num,char**soton,char**esm_soton){
    char name[20];char family[20];char user_id[20];char type[10];
    strcpy(name,soton[0]);
    strcpy(family,soton[1]);
    strcpy(user_id,soton[2]);
    strcpy(type,soton[3]);
    printf("%s  %s        %s          %s\n",name,family,user_id,type);
    return 0;
}
void deactivate_menu(void){
    char sql[200];
    sprintf(sql,"SELECT NAME,FAMILY,USER_ID,TYPE FROM USERS WHERE APPROVED='%d';",1);
    int rc= sqlite3_exec(db,sql,callback_deactivate_menu,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql erroe: %s",errorMsg);
        return;
    }
}
int callback_self_menu(void*data,int num,char**soton,char**esm_soton){
    char name[20];char self_id[20];char gender[20];char meal[20];
    strcpy(name,soton[0]);
    strcpy(name,soton[1]);
    strcpy(name,soton[2]);
    strcpy(name,soton[3]);
    printf("%s      %s      %s      %s\n",name,self_id,gender,meal);
    return 0;
}
void self_menu(void){
    char*sql="SELECT NAME,SELF_ID,GENDER,MEAL FROM SELFS;";
    int rc= sqlite3_exec(db,sql,callback_self_menu,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
}
int callback_food_menu(void*data,int num,char**soton,char**esm_soton){
    char name[20];char food_id[20];char type[20];
    strcpy(name,soton[0]);
    strcpy(food_id,soton[1]);
    strcpy(type,soton[2]);
    printf("%s      %s      %s\n",name,food_id,type);
    return 0;
}
void food_menu(void){
    char*sql="SELECT NAME,FOOD_ID,TYPE FROM FOODS;";
    int rc= sqlite3_exec(db,sql,callback_food_menu,NULL,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
}
int callback_see_mealplan_after(void*data,int num,char**soton,char**esm_soton){
    meal_plan*fech2=(meal_plan*)data;
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->self_id,soton[1]);
    fech2->year=strtol(soton[2],&ptr,10);
    fech2->mounth=strtol(soton[3],&ptr,10);
    fech2->day=strtol(soton[4],&ptr,10);
    strcpy(fech2->type,soton[5]);
    strcpy(fech2->food_id,soton[6]);
    fech2->count=strtol(soton[7],&ptr,10);
    if(tabdil_time_be_adad(fech2->year,fech2->mounth,fech2->day)-tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)>=0){
        printf("%d    %s    %d-%d-%d    %s    %s    %d\n",fech2->id,fech2->self_id,fech2->year,fech2->mounth,fech2->day,fech2->type,fech2->food_id,fech2->count);
    }
    return 0;
}
meal_plan* see_mealplan_after(void){
    meal_plan*vade=(meal_plan*)malloc(sizeof(meal_plan));
    vade->id=(-5);
    char*sql="SELECT * FROM MEALPLAN;";
    int rc= sqlite3_exec(db,sql,callback_see_mealplan_after,(void*)vade,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(vade->id==(-5)){
        free(vade);
        return NULL;
    }
    return vade;
}
int callback_see_mealplan_before(void*data,int num,char**soton,char**esm_soton){
    meal_plan*fech2=(meal_plan*)data;
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->self_id,soton[1]);
    fech2->year=strtol(soton[2],&ptr,10);
    fech2->mounth=strtol(soton[3],&ptr,10);
    fech2->day=strtol(soton[4],&ptr,10);
    strcpy(fech2->type,soton[5]);
    strcpy(fech2->food_id,soton[6]);
    fech2->count=strtol(soton[7],&ptr,10);
    if(tabdil_time_be_adad(fech2->year,fech2->mounth,fech2->day)-tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)<0){
        printf("%d    %s    %d-%d-%d    %s    %s    %d\n",fech2->id,fech2->self_id,fech2->year,fech2->mounth,fech2->day,fech2->type,fech2->food_id,fech2->count);
    }
    return 0;
}
meal_plan* see_mealplan_before(void){
    meal_plan*vade=(meal_plan*)malloc(sizeof(meal_plan));
    vade->id=(-5);
    char*sql="SELECT * FROM MEALPLAN;";
    int rc= sqlite3_exec(db,sql,callback_see_mealplan_before,(void*)vade,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(vade->id==(-5)){
        free(vade);
        return NULL;
    }
    return vade;
}
int callback_amar_mealplan_before(void*data,int num,char**soton,char**esm_soton){
    int*tedad=(int*)data;
    int reserv;char*ptr;
    reserv=strtol(soton[3],&ptr,10);
    if(reserv==1){
        (*tedad)++;
    }
    return 0;
}
void see_amar_mealplan_before(int meal_id){
    int*tedad=(int*)malloc(sizeof(int));
    char sql[200];
    sprintf(sql,"SELECT * FROM RESERVE WHERE MEAL_ID='%d';",meal_id);
    int rc= sqlite3_exec(db,sql,callback_amar_mealplan_before,(void*)tedad,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
    printf("The meal plan had %d reserved.\n",(*tedad));
    free(tedad);
}
int callback_amar_mealplan_after(void*data,int num,char**soton,char**esm_soton){
    int*tedad=(int*)data;
    int reserv;char*ptr;
    reserv=strtol(soton[3],&ptr,10);
    if(reserv==0){
        (*tedad)++;
    }
    return 0;
}
void see_amar_mealplan_after(int meal_id){
    int*tedad=(int*)malloc(sizeof(int));
    char sql[200];
    sprintf(sql,"SELECT * FROM RESERVE WHERE MEAL_ID='%d';",meal_id);
    int rc= sqlite3_exec(db,sql,callback_amar_mealplan_after,(void*)tedad,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
    printf("The meal plan has %d reserve.\n",(*tedad));
    free(tedad);
}
int callback_show_users(void*data,int num,char**soton,char**esm_soton){
    int*cheak=(int*)data;
    char name[20];char user_id[20];char family[20];int approved;char*ptr;
    (*cheak)=strtol(soton[0],&ptr,10);
    strcpy(user_id,soton[1]);
    strcpy(name,soton[2]);
    strcpy(family,soton[3]);
    approved=strtol(soton[4],&ptr,10);
    if((*cheak)>=0)
        printf("%s     %s     %s     %d\n",user_id,name,family,approved);
    return 0;
}
int show_users(void){
    int*cheak=(int*) malloc(sizeof(int));
    char sql[200];
    (*cheak)=(-4);
    sprintf(sql,"SELECT ID,USER_ID,NAME,FAMILY,APPROVED FROM USERS WHERE TYPE='%s';","student");
    int rc= sqlite3_exec(db,sql,callback_show_users,(void*)cheak,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return 1;
    }
    if(*cheak==(-4)){
        free(cheak);
        return 2;
    }
    free(cheak);
    return 0;
}


int callback_show_mealplan(void*data,int num,char**soton,char**esm_soton){
    meal_plan*fech2=(meal_plan*)data;
    char*ptr;
    fech2->id=strtol(soton[0],&ptr,10);
    strcpy(fech2->self_id,soton[1]);
    fech2->year=strtol(soton[2],&ptr,10);
    fech2->mounth=strtol(soton[3],&ptr,10);
    fech2->day=strtol(soton[4],&ptr,10);
    strcpy(fech2->type,soton[5]);
    strcpy(fech2->food_id,soton[6]);
    fech2->count=strtol(soton[7],&ptr,10);
    if((tabdil_time_be_adad(fech2->year,fech2->mounth,fech2->day)-tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day)>=2)&&((tabdil_time_be_adad(fech2->year,fech2->mounth,fech2->day)-tabdil_time_be_adad(main_date.year,main_date.mounth,main_date.day))<=14)&&(fech2->count>0)){
        printf("%d    %s    %d-%d-%d    %s    %s    %d\n",fech2->id,fech2->self_id,fech2->year,fech2->mounth,fech2->day,fech2->type,fech2->food_id,fech2->count);
    }
    return 0;
}
meal_plan* show_mealplan(user*new_user){
    meal_plan*vade=(meal_plan*)malloc(sizeof(meal_plan));
    vade->id=(-5);
    char sql[200];
    sprintf(sql,"SELECT ID,SELF_ID,YEAR,MOUNTH,DAY,TYPE,FOOD_ID,COUNT,GENDER FROM MEALPLAN JOIN SELFS WHERE GENDER='%s';",new_user->gender);
    int rc= sqlite3_exec(db,sql,callback_show_mealplan,(void*)vade,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(vade->id==(-5)){
        free(vade);
        return NULL;
    }
    return vade;
}
int callback_food_reserve(void*data,int num,char**soton,char**esm_soton){
    meal_plan*vade=(meal_plan*)data;char*ptr;
    vade->id=strtol(soton[0],&ptr,10);
    strcpy(vade->self_id,soton[1]);
    strcpy(vade->type,soton[2]);
    strcpy(vade->food_id,soton[3]);
    vade->year=strtol(soton[4],&ptr,10);
    vade->mounth=strtol(soton[5],&ptr,10);
    vade->day=strtol(soton[6],&ptr,10);
    if(vade->id>=0)
        printf("%d    %s    %s    %s    %d-%d-%d\n",vade->id,vade->self_id,vade->type,vade->food_id,vade->year,vade->mounth,vade->day);
    return 0;
}
meal_plan *food_reserve(user*new_user){
    meal_plan *vade=(meal_plan*) malloc(sizeof(meal_plan));
    vade->id=(-5);
    char sql[200];
    sprintf(sql,"SELECT ID,SEL_ID,TYPE,FOOD_ID,YEAR,MOUNTH,DAY,RESERVED FROM MEALPLAN JOIN RESERVE ON"
                "RESERVE.MEAL_ID=MEALPLAN.ID WHERE USER_ID='%s' AND APPROVED='%d';",new_user->user_id,0);
    int rc= sqlite3_exec(db,sql,callback_food_reserve,(void*)vade,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(vade->id==(-5)){
        free(vade);
        return NULL;
    }
    return vade;
}
int callback_a(void*data,int num,char**soton,char**esm_soton){
    meal_plan*vade=(meal_plan*)data;char*ptr;
    vade->id=strtol(soton[0],&ptr,10);
    strcpy(vade->self_id,soton[1]);
    strcpy(vade->type,soton[2]);
    strcpy(vade->food_id,soton[3]);
    vade->year=strtol(soton[4],&ptr,10);
    vade->mounth=strtol(soton[5],&ptr,10);
    vade->day=strtol(soton[6],&ptr,10);
    if(vade->id>=0)
        printf("%d    %s    %s    %s    %d-%d-%d\n",vade->id,vade->self_id,vade->type,vade->food_id,vade->year,vade->mounth,vade->day);
    return 0;
}
meal_plan *see_a(user*new_user){
    meal_plan *vade=(meal_plan*) malloc(sizeof(meal_plan));
    vade->id=(-5);
    char sql[200];
    sprintf(sql,"SELECT ID,SEL_ID,TYPE,FOOD_ID,YEAR,MOUNTH,DAY,RESERVED FROM MEALPLAN JOIN RESERVE ON"
                "RESERVE.MEAL_ID=MEALPLAN.ID WHERE USER_ID='%s' AND APPROVED='%d';",new_user->user_id,1);
    int rc= sqlite3_exec(db,sql,callback_a,(void*)vade,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return NULL;
    }
    if(vade->id==(-5)){
        free(vade);
        return NULL;
    }
    return vade;
}
int callback_repu(void*data,int nu,char**soton,char**esm_soton){
    int*adad=(int*)data;char jomle[2000];char*ptr;
    (*adad)=strtol(soton[0],&ptr,10);
    strcpy(jomle,soton[1]);
    if((*adad)>=0)
        printf("%s\n",jomle);
    return 0;
}
void report_user(char user_id[20]){
    int*adad=(int*) malloc(sizeof(int));
    char sql[200];
    (*adad)=(-5);
    sprintf(sql,"SELECT ID,CONTENT FROM REPORTS WHERE USER_ID='%s';",user_id);
    int rc= sqlite3_exec(db,sql,callback_repu,(void*)adad,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
    if((*adad)==-5)
        printf("don't have any reports\n");
}
int callback_repu_general(void*data,int nu,char**soton,char**esm_soton){
    int*adad=(int*)data;char jomle[2000];char*ptr;
    (*adad)=strtol(soton[0],&ptr,10);
    strcpy(jomle,soton[1]);
    if((*adad)>=0)
        printf("%s\n",jomle);
    return 0;
}
void report_general(){
    int*adad=(int*) malloc(sizeof(int));
    char*sql="SELECT ID,CONTENT FROM REPORTS;";
    (*adad)=(-5);
    int rc= sqlite3_exec(db,sql,callback_repu_general,(void*)adad,&errorMsg);
    if(rc!=SQLITE_OK){
        fprintf(stderr,"sql error: %s",errorMsg);
        return;
    }
    if((*adad)==-5)
        printf("don't have any reports\n");
}




