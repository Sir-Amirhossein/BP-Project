#include "testcases.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "sqlite3.h"
#include "orders.h"
#include "orders2.h"
#include <ctype.h>
extern date main_date;extern sqlite3*db;extern char *errorMsg;extern user*log_in_user;extern user admin;
void success(FILE*fpout,char commandID[10]){
    fprintf(fpout,"%s#success\n",commandID);
}
void not_found(FILE*fpout,char commandID[10]){
    fprintf(fpout,"%s#not-found\n",commandID);
}
void permission(FILE*fpout,char commandID[10]){
    fprintf(fpout,"%s#permission-denied\n",commandID);
}
void invalid(FILE*fpout,char commandID[10]){
    fprintf(fpout,"%s#invalid\n",commandID);
}
void testcase(){

   char name_file_input[50];
    printf("Please enter input file's name:\n->");
    gets(name_file_input);
    FILE *fpin = fopen(name_file_input, "r");
    FILE *fpout = fopen("output.txt", "w");
    while(1) {
            char string[500];
            char commandID[6];
            char command[50];
        if (feof(fpin)) {
                fclose(fpin);
                fclose(fpout);
                printf("DONE...\n");
                break;
            }
            fgets(string,499,fpin);
            string[strlen(string)]='\0';
            strcpy(commandID, strtok(string, "#"));
            strcpy(command, strtok(NULL, "#"));
        if (strcmp(command, "vote\n") == 0) {//baraye in dastor chon yek # nadarad \n ham migirad
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = cheak_pool(log_in_user);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if (strcmp(command, "check-news\n") == 0) {//baraye in dastor chon yek # nadarad \n ham migirad
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = cheak_news(log_in_user);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if (strcmp(command, "login") == 0) {
                char user_id[20];
                char password[32];
                char remainSTR[200];
                strcpy(remainSTR, strtok(NULL, "#"));
                sscanf(strtok(remainSTR, "|"), "user:%s", user_id);
                sscanf(strtok(NULL, "|"), "password:%s", password);
                user *answer = cheack_user(user_id);
                if(stricmp(user_id,"admin")==0&& cheack_password(user_id,password)==1){
                    fprintf(fpout,"%s#success\n",commandID);
                    log_in_user=&admin;
                    continue;
                }
                if(answer==NULL)
                    fprintf(fpout, "%s#not-found\n", commandID);
                else if ((answer->id == (-2)) || answer == NULL || strcmp(password, answer->pass) != 0 || log_in_user != NULL)
                    fprintf(fpout, "%s#not-found\n", commandID);
                else {
                    fprintf(fpout, "%s#success\n", commandID);
                    log_in_user = answer;
                }

            }
        else if (strcmp(command, "logout") == 0) {
                char user_id[20];
                char remain[200];
                strcpy(remain,strtok(NULL,"#"));
                sscanf(strtok(remain,"|"), "user:%s", user_id);
                if(log_in_user==NULL)
                    not_found(fpout,commandID);
                else if (strcmp(user_id, log_in_user->user_id) == 0) {
                    fprintf(fpout, "%s#success\n", commandID);
                    log_in_user = NULL;
                }
                else if(strcmp(log_in_user->user_id,user_id)!=0)
                    not_found(fpout,commandID);
                else if(cheack_user(log_in_user->user_id)==NULL)//yani on adam aslan to list nist
                    not_found(fpout,commandID);
                else if (log_in_user == &admin)
                    fprintf(fpout, "%s#invalid\n", commandID);
            }
        else if (strcmp(command, "change-pass") == 0) {
                char remain[200];
                char user_id[20];
                char old_pass[20];
                char new_pass[20];
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "user:%s", user_id);
                sscanf(strtok(NULL, "|"), "old-pass:%s", old_pass);
                sscanf(strtok(NULL, "|"), "new-pass:%s", new_pass);
                if (log_in_user == NULL){
                    not_found(fpout,commandID);
                    continue;
                }
                int answer = change_pass(user_id, old_pass, new_pass, log_in_user);
                if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else{
                    invalid(fpout, commandID);
                }
            }
        else if(strcmp(command,"approve")==0){
                char user_ids[1000][20];char remain[200];
                strcpy(remain,strtok(NULL,"#"));
                sscanf(strtok(remain,"|"),"user:%s",user_ids[0]);
                int i=1;
                while(1){
                    char*cheak;
                    cheak=strtok(NULL,"|");
                    if(cheak==NULL)
                        break;
                    sscanf(cheak,"user:%s",user_ids[i]);
                    i++;
                }
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer= approved_users(log_in_user,user_ids,i);
                if(answer==1)
                    not_found(fpout,commandID);
                else if(answer==2)
                    permission(fpout,commandID);
                else if(answer==0)
                    success(fpout,commandID);
                else{
                    invalid(fpout,commandID);
                }
        }

        else if (strcmp(command, "change-student-pass") == 0) {
                char remain[200];
                char user_id[20];
                char new_pass[32];
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "user:%s", user_id);
                sscanf(strtok(NULL, "|"), "new-pass:%s", new_pass);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                long long int answer = change_student_pass(user_id, new_pass, log_in_user);
                if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if (strcmp(command, "remove-student") == 0) {
                char user_id[20];char remain[200];
                strcpy(remain,strtok(NULL,"#"));
                sscanf(strtok(remain,"|"), "user:%s", user_id);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = remove_user(user_id, log_in_user);
                if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer==3)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command,"deactivate")==0){
                char remain[200];char user_id[20];
                strcpy(remain,strtok(NULL,"#"));
                sscanf(strtok(remain,"|"),"user:%s",user_id);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer= deactived_user(log_in_user,user_id);
                if(answer==1)
                    not_found(fpout,commandID);
                else if(answer==2)
                    permission(fpout,commandID);
                else if(answer==0)
                    success(fpout,commandID);
                else
                    invalid(fpout,commandID);
            }
        else if(strcmp(command, "register") == 0) {
                char remain[200];
                user *karbar = (user *) malloc(sizeof(user));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "name:%s", karbar->name);
                sscanf(strtok(NULL, "|"), "family:%s", karbar->family);
                sscanf(strtok(NULL, "|"), "user-id:%s", karbar->user_id);
                sscanf(strtok(NULL, "|"), "password:%s", karbar->pass);
                sscanf(strtok(NULL, "|"), "national-id-code:%s", karbar->national_id);
                char*p=strtok(NULL,"|");
                while(isalpha(*p))p++;p++;karbar->birthdate_year=atoi(p);
                while(isalnum(*p))p++;p++;karbar->birthdate_month=atoi(p);
                while(isalnum(*p))p++;p++;karbar->birthdate_day=atoi(p);
                sscanf(strtok(NULL,"|"),"gender:%s",karbar->gender);
                sscanf(strtok(NULL,"|"),"type:%s",karbar->type);
                int answer = register_in_site(karbar, log_in_user);
                free(karbar);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if (strcmp(command, "define-self") == 0) {
                char remain[200];
                self *selff = (self *) malloc(sizeof(self));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "id:%s", selff->self_id);
                sscanf(strtok(NULL, "|"), "name:%s", selff->name);
                sscanf(strtok(NULL, "|"), "location:%s", selff->location);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                selff->capacity = atoi(p);
                sscanf(strtok(NULL, "|"), "type:%s", selff->gender);
                sscanf(strtok(NULL, "|"), "meal:%s", selff->meal);
                char *pp = strtok(NULL, "|");
                while (isalpha(*pp))pp++;
                pp++;
                while (isalpha(*pp))pp++;
                pp++;
                while (isalpha(*pp))pp++;
                pp++;
                selff->lunch_start = atoi(pp);
                while (isalnum(*pp))pp++;
                pp++;
                selff->lunch_finish = atoi(pp);
                pp = strtok(NULL, "|");
                while (isalpha(*pp))pp++;
                pp++;
                while (isalpha(*pp))pp++;
                pp++;
                while (isalpha(*pp))pp++;
                pp++;
                selff->dinner_start = atoi(pp);
                while (isalnum(*pp))pp++;
                pp++;
                selff->dinner_finish = atoi(pp);
                if (log_in_user == NULL) {
                    free(selff);
                    permission(fpout, commandID);
                    continue;
                }
                int answer = define_self(selff, log_in_user);
                free(selff);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 3)
                    not_found(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if (strcmp(command, "define-food") == 0) {
                char remain[200];
                food *ghaza = (food *) malloc(sizeof(food));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "id:%s", ghaza->food_id);
                sscanf(strtok(NULL, "|"), "name:%s", ghaza->name);
                sscanf(strtok(NULL, "|"), "type:%s", ghaza->type);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                ghaza->price = atoi(p);
                if (log_in_user == NULL) {
                    free(ghaza);
                    permission(fpout, commandID);
                    continue;
                }
                int answer = define_food(ghaza, log_in_user);
                free(ghaza);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 3)
                    not_found(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "define-meal-plan")==0) {
                char remain[200];
                meal_plan *vade = (meal_plan *) malloc(sizeof(meal_plan));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "self-id:%s", vade->self_id);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                vade->year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                vade->mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                vade->day = atoi(p);
                sscanf(strtok(NULL, "|"), "type:%s", vade->type);
                sscanf(strtok(NULL, "|"), "food-id:%s", vade->food_id);
                p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                vade->count = atoi(p);
                if (log_in_user == NULL) {
                    free(vade);
                    permission(fpout, commandID);
                    continue;
                }
                int answer = define_meal_plan(vade, log_in_user);
                free(vade);
                if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 3)
                    not_found(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "charge-student-account") == 0) {
                char remain[500];
                char user_id[20];
                long long int charge;
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "user:%s", user_id);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                charge = atoi(p);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = charge_student_account(log_in_user, user_id, charge);
                if (answer == 1)
                    not_found(fpout, commandID);
                else if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "add-news") == 0) {
                char remain[500];
                news *khabar = (news *) malloc(sizeof(news));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "title:%[^|]", khabar->title);
                sscanf(strtok(NULL, "|"), "content:%[^|]", khabar->content);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                while (isalpha(*p))p++;
                p++;
                khabar->tarikh.year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                khabar->tarikh.mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                khabar->tarikh.day = atoi(p);
                if (log_in_user == NULL) {
                    free(khabar);
                    permission(fpout, commandID);
                    continue;
                }
                int answer = add_news(khabar, log_in_user);
                free(khabar);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "add-poll") == 0) {
                char remain[500];
                pool *nazar = (pool *) malloc(sizeof(pool));
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "question:%[^|]", nazar->question);
                sscanf(strtok(NULL, "|"), "option:%s", nazar->first);
                sscanf(strtok(NULL, "|"), "option:%s", nazar->second);
                sscanf(strtok(NULL, "|"), "option:%s", nazar->third);
                sscanf(strtok(NULL, "|"), "option:%s", nazar->forth);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                while (isalpha(*p))p++;
                p++;
                nazar->year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                nazar->mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                nazar->day = atoi(p);
                if (log_in_user == NULL) {
                    free(nazar);
                    permission(fpout, commandID);
                    continue;
                }
                int answer = add_pool(nazar, log_in_user);
                free(nazar);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "reserve") == 0) {
                char remain[500];
                char self_id[20];
                char meal[7];
                char food_id[20];
                int year, mounth, day;
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "self-id:%s", self_id);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                day = atoi(p);
                sscanf(strtok(NULL, "|"), "meal:%s", meal);
                sscanf(strtok(NULL, "|"), "food-id:%s", food_id);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = reserve_food(log_in_user, self_id, meal, food_id, year, mounth, day);
                if (answer == 1 || answer == 11)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer == 7 || answer == 10|| answer == 5 || answer == 6 || answer == 4 || answer ==15)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
            }
        else if(strcmp(command, "take-food") == 0) {
                char remain[500];
                char meal[20];
                int year, mounth, day;
                char self_id[20];
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "self-id:%s", self_id);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                day = atoi(p);
                sscanf(strtok(NULL, "|"), "meal:%s", meal);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = take_food(self_id, log_in_user, meal, year, mounth, day);
                if (answer == 1 || answer == 10 || answer == 6 || answer == 12)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer == 11 || answer == 13)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "charge-account") == 0) {
                char remain[200];
                long int charge;
                char card_num[50];
                char pass_card[20];
                strcpy(remain, strtok(NULL, "#"));
                char *p = strtok(remain, "|");
                while (isalpha(*p))p++;
                p++;
                charge = atoi(p);
                sscanf(strtok(NULL, "|"), "card-number:%s", card_num);
                sscanf(strtok(NULL, "|"), "pass-code:%s", pass_card);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                else if (strlen(card_num) != 19){
                    invalid(fpout, commandID);
                    continue;
                }
                else if (strlen(pass_card) != 4){
                    invalid(fpout, commandID);
                    continue;
                }
                int answer = charge_account(log_in_user, charge);
                if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "send-charge") == 0) {
                char remain[200];
                char user_id[20];
                char name[20];
                long int charge;
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "user:%s", user_id);
                char *p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                charge = atoi(p);
                sscanf(strtok(NULL, "|"), "name:%s", name);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = send_charge(log_in_user, charge, user_id, name);
                if (answer == 1 || answer == 4)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer==3)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "cancel-reserve") == 0) {
                char remain[200];
                int year, mounth, day;
                char type[7];
                strcpy(remain, strtok(NULL, "#"));
                char *p = strtok(remain, "|");
                while (isalpha(*p))p++;
                p++;
                year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                day = atoi(p);
                sscanf(strtok(NULL, "|"), "meal:%s", type);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = cancel_reserve(year, mounth, day, type, log_in_user);
                if (answer == 1 || answer == 4)
                    not_found(fpout, commandID);
                else if (answer == 2)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "daily-reserve") == 0) {
                char remain[200];
                char self_id[20];
                char food_id[20];
                strcpy(remain, strtok(NULL, "#"));
                sscanf(strtok(remain, "|"), "self-id:%s", self_id);
                sscanf(strtok(NULL, "|"), "food-id:%s", food_id);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = daily_reserve(log_in_user, self_id, food_id);
                if (answer == 1 || answer == 10 || answer == -1)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer == -4 || answer == -2 || answer == -3)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "change-self") == 0) {
                char remain[200];
                char meal[7];
                char new_self_id[20];
                int year, mounth, day;
                strcpy(remain, strtok(NULL, "#"));
                char *p = strtok(remain, "|");
                while (isalpha(*p))p++;
                p++;
                year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                day = atoi(p);
                sscanf(strtok(NULL, "|"), "meal:%s", meal);
                sscanf(strtok(NULL, "|"), "new-self-id:%s", new_self_id);
                if (log_in_user == NULL){
                    permission(fpout, commandID);
                    continue;
                }
                int answer = change_self(log_in_user, year, mounth, day, meal, new_self_id);
                if (answer == 1 || answer == 13 || answer == 7)
                    not_found(fpout, commandID);
                else if (answer == 2 || answer == 10 || answer == 11 | answer == 12)
                    permission(fpout, commandID);
                else if (answer == 0)
                    success(fpout, commandID);
                else
                    invalid(fpout, commandID);
            }
        else if(strcmp(command, "change-datetime") == 0) {
                char remain[200];
                int year, mounth, day, hour;
                strcpy(remain, strtok(NULL, "#"));
                char *p = strtok(remain, "|");
                while (isalpha(*p))p++;
                p++;
                year = atoi(p);
                while (isalnum(*p))p++;
                p++;
                mounth = atoi(p);
                while (isalnum(*p))p++;
                p++;
                day = atoi(p);
                p = strtok(NULL, "|");
                while (isalpha(*p))p++;
                p++;
                hour = atoi(p);
                change_date_time(year, mounth, day, hour);
                success(fpout,commandID);
            }
        else{
            invalid(fpout,commandID);
        }
    }
}