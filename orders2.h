#ifndef MAIN_C_ORDERS2_H
#define MAIN_C_ORDERS2_H

#include "structures.h"
int moghayese_date(int year,int mounth,int day);
long long int tabdil_time_be_adad(int year,int mounth,int day);
int tashkhis_saat_baraye_gereftan_ghaza(char self_id[10],char type_meal[10]);
int callback_news(void*data,int num,char**soton,char**esme_soton);
void print_news();
int add_news(news*khabar, user*new_user);
int callback_pool(void*data,int num,char**soton,char**esme_soton);
void print_pool();
int add_pool(pool*nazar,user*new_user);
int reserve_food(user*new_user,char self_id[10],char type_meal[7],char food_id[7],int year,int mounth,int day);
int callback_take_food(void*data,int num,char**soton,char**esm_soton);
int take_food(char self_id[10],user*new_user,char type_food[7],int year,int mounth,int day);
int callback_cancel_reserve(void*data,int num,char**soton,char**esm_soton);
int cancel_reserve(int year,int mounth,int day,char type[7],user*new_user);
int help_daily_reserve(user*new_user,char self_id[10],char food_id[10],char type[7],self*sself,food*ghaza);
int daily_reserve(user*new_user,char self_id[10],char food_id[10]);
int callback_change_self(void*data,int num,char**soton,char**esm_soton);
int change_self(user*new_user,int year,int mounth,int day,char type[7],char new_self_id[10]);
void change_date_time(int year,int mounth,int day,int hour);

#endif //MAIN_C_ORDERS2_H
