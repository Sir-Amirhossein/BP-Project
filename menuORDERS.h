#ifndef ORDERS_C_MENUORDERS_H
#define ORDERS_C_MENUORDERS_H
#include "structures.h"
int callback_approve_menu(void*data,int num,char**soton,char**esm_soton);
void approve_menu(void);
int callback_deactivate_menu(void*data,int num,char**soton,char**esm_soton);
void deactivate_menu(void);
int callback_self_menu(void*data,int num,char**soton,char**esm_soton);
void self_menu(void);
int callback_food_menu(void*data,int num,char**soton,char**esm_soton);
void food_menu(void);
int callback_see_mealplan_after(void*data,int num,char**soton,char**esm_soton);
meal_plan* see_mealplan_after(void);
int callback_see_mealplan_before(void*data,int num,char**soton,char**esm_soton);
meal_plan* see_mealplan_before(void);
int callback_amar_mealplan_before(void*data,int num,char**soton,char**esm_soton);
void see_amar_mealplan_before(int meal_id);
int callback_amar_mealplan_after(void*data,int num,char**soton,char**esm_soton);
void see_amar_mealplan_after(int meal_id);
int callback_show_users(void*data,int num,char**soton,char**esm_soton);
int show_users(void);
int callback_show_mealplan(void*data,int num,char**soton,char**esm_soton);
meal_plan* show_mealplan(user*new_user);
int callback_food_reserve(void*data,int num,char**soton,char**esm_soton);
meal_plan *food_reserve(user*new_user);
int callback_a(void*data,int num,char**soton,char**esm_soton);
meal_plan *see_a(user*new_user);
int callback_repu(void*data,int nu,char**soton,char**esm_soton);
void report_user(char user_id[20]);
int callback_repu_general(void*data,int nu,char**soton,char**esm_soton);
void report_general();


#endif //ORDERS_C_MENUORDERS_H
