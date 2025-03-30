#ifndef PROJECT_ORDERS_H
#define PROJECT_ORDERS_H

#include "structures.h"

int register_in_site(user*karbar,user*new_user);
int callback_cheak_user(void*data,int num,char**soton,char**satr);
int cheack_password(char user_id[12],char pass[32]);
user*cheack_user(const char user_id[12]);
int log_out(user*karbar,char name[32]);
int change_pass(char user_id[32],char*old_pass,char*new_pass,user*new_user);
int approved_users(user*new_user,char users[1000][20],int satrha);
long long int change_student_pass(char user_id[32],char*new_pass,user*new_user);
int remove_user(char name[32],user*new_user);
int deactived_user(user*new_user,char user_id[20]);
int charge_student_account(user*new_user,char*user_id,long int charge);
int charge_account(user*new_user,long int charge);
int send_charge(user*new_user,long int charge,char*user_id,char name[32]);
int callback_cheak_self(void*data,int num,char**soton,char**satr);
self*cheack_self(const char self_id[10]);
int callback_cheak_food(void*data,int num,char**soton,char**satr);
food*cheack_food(const char food_id[10]);
int define_self(self*new,user*new_user);
int define_food(food*new,user*new_user);
int callback_cheak_meal_plan(void*data,int num,char**soton,char**satr);
meal_plan*cheack_meal_plan(const char self_id[10],const char food_id[10],const char type[7],int year,int mounth,int day);
int define_meal_plan(meal_plan*meal,user*new_user);
int callback_news_testcase(void*data,int num,char**soton,char**esme_soton);
int cheak_news(user*new_user);
int callback_pool_testcase(void*data,int num,char**soton,char**esme_soton);
int cheak_pool(user*new_user);
#endif //PROJECT_ORDERS_H
