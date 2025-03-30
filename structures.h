#ifndef PROJECT_STRUCTURES_H
#define PROJECT_STRUCTURES_H
typedef struct{
    long long int id;
    char name[38];
    char family[38];
    char user_id[32];
    char pass[32];
    char national_id[12];
    int birthdate_year;
    int birthdate_month;
    int birthdate_day;
    char gender[10];
    char type[8];
    int approved;
    long int credit;
}user;
typedef struct{
    int year;
    int mounth;
    int day;
    int hour;
}date;
typedef struct{
    long long int id;
    char self_id[10];
    char name[38];
    char location[50];
    int capacity;
    char gender[10];
    char meal[7];
    int lunch_start;
    int lunch_finish;
    int dinner_start;
    int dinner_finish;
}self;
typedef struct{
    long long int id;
    char food_id[10];
    char name[38];
    char type[10];
    long int price;
}food;
typedef struct{
    long long int id;
    char self_id[10];
    int year;
    int mounth;
    int day;
    char type[7];//dinner or lunch
    char food_id[10];
    int count;
}meal_plan;
typedef struct{
    long long int id;
    char user_id[10];
    int meal_id;
    int reserved;
}reserve;
typedef struct{
    long long int id;
    char title[50];
    char content [5000];
    date tarikh;
}news;
typedef struct{
    long long int id;
    char question[1000];
    char first[20];
    char second[20];
    char third[20];
    char forth[20];
    int year;
    int mounth;
    int day;
}pool;
typedef struct{
    int id;
    char user_id[10];
    char self_id[10];
    char type[10];//lunch or dinner
    char food_id[10];
    int reserved;
}takefood;
typedef struct{
    int meal_id;
    char old_self_id[10];
    char food_id[10];
}ksh;

#endif //PROJECT_STRUCTURES_H
