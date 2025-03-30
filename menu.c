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
#include "menuORDERS.h"
extern date main_date;extern sqlite3*db;extern char *errorMsg;extern user*log_in_user;extern user admin;
void menu(){
    while(1){
        int n;
        printf("1)register\n2)login\n3)Exit\n->");
        scanf("%d",&n);
        if(n==1){
            printf("please enter your info hunestly:\n");
            log_in_user=NULL;user*user1=(user*)malloc(sizeof(user));
            fflush(stdin);
            printf("name:");gets(user1->name);
            printf("family:");gets(user1->family);
            printf("user-id:");gets(user1->user_id);
            printf("password:");gets(user1->pass);
            printf("national-id-code:");gets(user1->national_id);
            printf("birthdate(year):");gets(user1->birthdate_year);
            printf("birthdate(mounth):");gets(user1->birthdate_month);
            printf("birthdate(day):");gets(user1->birthdate_day);
            printf("gender:");gets(user1->gender);
            printf("type:");gets(user1->type);
            int a=register_in_site(user1,log_in_user);
            if(a==2){
                printf("you are already registerd...\n");
            }
            else if(a==0){
                printf("register successfull\n");
            }


        }
        else if(n==2){
            while(1) {
                        char user_id[20];
                        char pass[32];
                        fflush(stdin);
                        printf("user-id:");
                        gets(user_id);
                        printf("password:");
                        gets(pass);
                        user *new_user = cheack_user(user_id);
                        int d = cheack_password(user_id, pass);
                        if (new_user == NULL) {
                            printf("This ID is not registered...\n");
                            break;
                        }
                        else if (d == 0) {
                            printf("invalid password\n");
                        }
                        else if(new_user->id==(-2)&&d==1){
                            printf("The ID has not been confirmed. Please wait for confirmation by the admin.\n");
                            break;
                        }
                        else if(stricmp(new_user->type,"admin")==0&&d==1){//this is admin####********
                            log_in_user=new_user;
                            while(1) {
                                fflush(stdin);
                                int nn;
                                printf("1)register an user\n2)change password\n3)approve users\n4)change student pass\n5)deactive student\n");
                                printf("6)define self\n7)define food\n8)define meal plan\n9)charge student account\n10)Reservation and food delivery statistics\n");
                                printf("11)user performance report\n12)add news\n13)add poll\n14)remove students\n15)report general\n16)logout\n17)change date time\n");
                                scanf("%d", &nn);
                                fflush(stdin);
                                if (nn == 1) {
                                        user *user2 = (user *) malloc(sizeof(user));
                                        fflush(stdin);
                                        printf("name:");gets(user2->name);
                                        printf("family:");gets(user2->family);
                                        printf("user-id:");gets(user2->user_id);
                                        printf("password:");gets(user2->pass);
                                        printf("national-id-code:");gets(user2->national_id);
                                        printf("birthdate(year):");gets(user2->birthdate_year);
                                        printf("birthdate(mounth):");gets(user2->birthdate_month);
                                        printf("birthdate(day):");gets(user2->birthdate_day);
                                        printf("gender:");gets(user2->gender);
                                        printf("type:");gets(user2->type);
                                        int aa = register_in_site(user2, log_in_user);
                                        if(aa==2){
                                            printf("user already exist...\n");
                                        }
                                        else if(aa==0){
                                            printf("register and approved successfully\n");
                                        }

                                }
                                else if(nn==2){
                                    while(1) {
                                        char ol_pass[32];char new_pass[32];
                                        fflush(stdin);printf("old pass:");gets(ol_pass);fflush(stdin);
                                        printf("new pass:");gets(new_pass);fflush(stdin);
                                        int answer = change_pass(new_user->user_id, ol_pass, new_pass, new_user);
                                        if (answer == 2) {
                                            printf("please enter your old pass correct...\n");
                                        }
                                        else if(answer==0){
                                            printf("change pass successfully\n");
                                            break;
                                        }
                                    }
                                }
                                else if(nn==3){
                                        char approveusers[1000][20];
                                        approve_menu();
                                        printf("\nplease enter the number of IDs you want to approved them:\n");int number;fflush(stdin);
                                        scanf("%d",&number);fflush(stdin);
                                        printf("Please enter the IDs you want to be approved:\n");fflush(stdin);
                                        int i=0;
                                        for( ;i<number;i++){
                                            gets(approveusers[i]);fflush(stdin);
                                        }
                                        int p= approved_users(new_user,approveusers,i);
                                        if(p==0){
                                            printf("successfully\n");
                                        }
                                        else{
                                            printf("Error...\n");
                                        }

                                }
                                else if(nn==4){
                                    char us[20];char np[32];fflush(stdin);
                                    printf("user-ID : ");scanf("%s",us);fflush(stdin);
                                    printf("new password : ");sscanf("%s",np);fflush(stdin);
                                    int t= change_student_pass(us,np,new_user);
                                    if(t==1){
                                        printf("not-found this user\n");
                                    }
                                    else if(t==2){
                                        printf("this user is admin...!\n");
                                    }
                                    else if(t==0){
                                        printf("change student pass successfull\n");
                                    }
                                    else{
                                        printf("invalid\n");
                                    }
                                }
                                else if(nn==5){
                                    char approveusers2[1000][20];
                                    deactivate_menu();
                                    printf("\nplease enter the number of IDs you want to deactive them:\n");int number2;fflush(stdin);
                                    scanf("%d",&number2);fflush(stdin);
                                    printf("Please enter the IDs you want to be deactive:\n");fflush(stdin);
                                    int i=0;
                                    for( ;i<number2;i++){
                                        gets(approveusers2[i]);fflush(stdin);
                                    }
                                    int p= approved_users(new_user,approveusers2,i);
                                    if(p==0){
                                        printf("successfully\n");
                                    }
                                    else{
                                        printf("Error...\n");
                                    }
                                }
                                else if(nn==6){
                                    self*self1=(self*)malloc(sizeof(self));fflush(stdin);
                                    while(1) {
                                        printf("self ID:");gets(self1->self_id);fflush(stdin);
                                        printf("name:");gets(self1->name);fflush(stdin);
                                        printf("location:");gets(self1->location);fflush(stdin);
                                        printf("capacity:");scanf("%d", &(self1->capacity));fflush(stdin);
                                        printf("gender(boyish-girlish):");gets(self1->gender);fflush(stdin);
                                        printf("meal(lunch-dinner-both):");gets(self1->meal);fflush(stdin);
                                        printf("please enter the hours like this 1230 it means twelve and half\n");fflush(stdin);
                                        printf("if the self doesn't serve lunch-dinner enter 0000\n");fflush(stdin);
                                        printf("lunch start time:");scanf("%d", &(self1->lunch_start));fflush(stdin);
                                        printf("lunch finissh time:");scanf("%d", &(self1->lunch_finish));fflush(stdin);
                                        printf("dinner start time:");scanf("%d", &(self1->dinner_start));fflush(stdin);
                                        printf("dinner finish time:");scanf("%d", &(self1->dinner_finish));fflush(stdin);
                                        int u = define_self(self1, new_user);
                                        if (u == 3) {
                                            char j[5];
                                            printf("this self already exist...\n");fflush(stdin);
                                            printf("do you wanna to define another self ? (yes-no)\n");fflush(stdin);gets(j);fflush(stdin);
                                            if(stricmp(j,"no")==0)
                                                break;
                                        }
                                        else if (u == 0) {
                                            char ja[5];
                                            printf("define self successfull\n");
                                            printf("do you wanna to define another self ? (yes-no)\n");fflush(stdin);gets(ja);fflush(stdin);
                                            if(stricmp(ja,"no")==0)
                                                break;
                                        }
                                        else{
                                            printf("invalid\n");
                                        }
                                    }
                                }
                                else if(nn==7){
                                    food*ghaza=(food*)malloc(sizeof(food));
                                    while(1){
                                        printf("food ID:");gets(ghaza->food_id);fflush(stdin);
                                        printf("name:");gets(ghaza->name);fflush(stdin);
                                        printf("type:");gets(ghaza->type);fflush(stdin);
                                        printf("price:");scanf("%d",&(ghaza->price));fflush(stdin);
                                        int y= define_food(ghaza,new_user);
                                        if (y == 3) {
                                            char j[5];
                                            printf("this food already exist...\n");fflush(stdin);
                                            printf("do you wanna to define another food ? (yes-no)\n");fflush(stdin);gets(j);fflush(stdin);
                                            if(stricmp(j,"no")==0)
                                                break;
                                        }
                                        else if (y == 0) {
                                            char ja[5];
                                            printf("define food successfull\n");
                                            printf("do you wanna to define another food ? (yes-no)\n");fflush(stdin);gets(ja);fflush(stdin);
                                            if(stricmp(ja,"no")==0)
                                                break;
                                        }
                                        else{
                                            printf("invalid\n");
                                        }
                                    }
                                }
                                else if(nn==8){
                                    meal_plan*vade=(meal_plan*) malloc(sizeof(meal_plan));
                                    while(1){
                                        fflush(stdin);
                                        printf("         SELFS\n");fflush(stdin);
                                        self_menu();fflush(stdin);
                                        printf("\n");fflush(stdin);printf("\n");fflush(stdin);
                                        printf("       FOODS\n");fflush(stdin);
                                        printf("\n");fflush(stdin);
                                        printf("\n");fflush(stdin);
                                        printf("self ID:");gets(vade->self_id);fflush(stdin);
                                        printf("year:");scanf("%d",&(vade->year));fflush(stdin);
                                        printf("mounth:");scanf("%d",&(vade->mounth));fflush(stdin);
                                        printf("day:");scanf("%d",&(vade->day));fflush(stdin);
                                        printf("type(food-desert):");gets(vade->type);fflush(stdin);
                                        printf("food ID:");gets(vade->food_id);fflush(stdin);
                                        printf("count:");scanf("%d",&(vade->count));fflush(stdin);
                                        int w= define_meal_plan(vade,new_user);
                                        if (w == 3) {
                                            char j[5];
                                            printf("this meal plan already exist...\n");fflush(stdin);
                                            printf("do you wanna to define another meal plan ? (yes-no)\n");fflush(stdin);gets(j);fflush(stdin);
                                            if(stricmp(j,"no")==0)
                                                break;
                                        }
                                        else if (w == 0) {
                                            char ja[5];
                                            printf("define meal plan successfull\n");
                                            printf("do you wanna to define another meal plan ? (yes-no)\n");fflush(stdin);gets(ja);fflush(stdin);
                                            if(stricmp(ja,"no")==0)
                                                break;
                                        }
                                        else{
                                            printf("invalid\n");
                                        }

                                    }
                                }
                                else if(nn==9){
                                    fflush(stdin);char userd[20];long int chargee;
                                    printf("please enter user ID:");gets(userd);fflush(stdin);
                                    printf("please enter count:");scanf("%ld",&chargee);fflush(stdin);
                                    int x= charge_student_account(new_user,user_id,chargee);
                                    if(x==1){
                                        printf("this user isn't exist...\n");fflush(stdin);
                                    }
                                    else if(x==2){
                                        printf("this user is an admin...\n");fflush(stdin);
                                    }
                                    else if(x==0){
                                        printf("charge student account successfull\n");
                                    }
                                    else{
                                        printf("invalid\n");
                                    }
                                }
                                else if(nn==10){
                                    fflush(stdin);int ka;
                                    printf("1)report meal plans before today\n2)report meal plans after today\n");fflush(stdin);int h;
                                    scanf("%d",&h);fflush(stdin);
                                    if(h==1){
                                        printf("meal plans before today:\n");fflush(stdin);
                                        meal_plan *vadee=see_mealplan_before();printf("\n");fflush(stdin);printf("\n");fflush(stdin);printf("\n");fflush(stdin);
                                        if(vadee==NULL){
                                            printf("No meal plans...\n");fflush(stdin);
                                        }
                                        else if(vadee!=NULL){
                                            printf("please enter your meal plan ID (first column) :");scanf("%d",&ka);fflush(stdin);
                                            see_amar_mealplan_before(ka);
                                        }
                                    }
                                    else if(h==2) {
                                        printf("meal plans after today:\n");printf("\n");fflush(stdin);printf("\n");fflush(stdin);
                                        meal_plan *vadee=see_mealplan_after();printf("\n");fflush(stdin);printf("\n");fflush(stdin);printf("\n");fflush(stdin);
                                        if(vadee==NULL){
                                            printf("No meal plans...\n");fflush(stdin);
                                        }
                                        else if(vadee!=NULL){
                                            printf("please enter your meal plan ID (first column) :");scanf("%d", &ka);fflush(stdin);
                                            see_amar_mealplan_after(ka);
                                        }
                                    }

                                }
                                else if(nn==11){
                                    fflush(stdin);char ttt[20];
                                    printf("please enter user ID you want to see it's reports : ");
                                    report_user(ttt);
                                }
                                else if(nn==12){
                                    news*khabar=(news*) malloc(sizeof(khabar));fflush(stdin);
                                    printf("Title : ");gets(khabar->title);fflush(stdin);
                                    printf("content : ");gets(khabar->content);fflush(stdin);
                                    printf("enter end date time (enter like 2023-05-24) : ");scanf("%d-%d-%d",khabar->tarikh.year,khabar->tarikh.mounth,khabar->tarikh.day);fflush(stdin);
                                    int o= add_news(khabar,new_user);
                                    if(o==0){
                                        printf("add news successfully\n");
                                    }
                                    else if(o!=2){
                                        printf("invalid\n");
                                    }
                                    free(khabar);
                                }
                                else if(nn==13){
                                    pool*nazar=(pool*)malloc(sizeof(pool));fflush(stdin);
                                    printf("question : ");gets(nazar->question);fflush(stdin);
                                    printf("1) ");gets(nazar->first);fflush(stdin);
                                    printf("2) ");gets(nazar->second);fflush(stdin);
                                    printf("3) ");gets(nazar->third);fflush(stdin);
                                    printf("4) ");gets(nazar->forth);fflush(stdin);
                                    printf("enter end date (like 2023-02-24) :");scanf("%d-%d-%d",nazar->year,nazar->mounth,nazar->day);fflush(stdin);
                                    int q= add_pool(nazar,new_user);
                                    if(q==0){
                                        printf("add poll successfully\n");
                                    }
                                    else if(q!=2){
                                        printf("invalid\n");
                                    }
                                    free(nazar);
                                }
                                else if(nn==14){
                                    fflush(stdin);
                                    while(1) {
                                        int cheak = show_users();
                                        if (cheak == 0) {
                                            printf("please enter the user ID you want to be remove : ");fflush(stdin);char userrr[20];
                                            printf("are you sure ? (yes-no) ");fflush(stdin);char eee[5];gets(eee);fflush(stdin);
                                            if(stricmp(eee,"yes")==0){
                                                int oo = remove_user(userrr, new_user);
                                                if (oo == 0) {
                                                    printf("remove succesfull\n");fflush(stdin);
                                                    printf("do you want to exit ? (yes-no) ");fflush(stdin);char jj[5];gets(jj);fflush(stdin);
                                                    if (stricmp(jj, "yes") == 0) {
                                                        break;
                                                    }
                                                }
                                                else if (oo != 2) {
                                                    printf("this user ID isn't exist or maybe an admin\n");fflush(stdin);
                                                    printf("do you want to exit ? (yes-no) ");fflush(stdin);char jj[5];gets(jj);fflush(stdin);
                                                    if (stricmp(jj, "yes") == 0) {
                                                        break;
                                                    }
                                                }
                                            }
                                            else{
                                                printf("do you want to exit ? (yes-no) ");fflush(stdin);char jj[5];gets(jj);fflush(stdin);
                                                if (stricmp(jj, "yes") == 0) {
                                                    break;
                                                }
                                            }
                                        }
                                        else if(cheak!=0){
                                            printf("no user to remove\n");
                                            break;
                                        }
                                    }
                                }
                                else if(nn==15){
                                    report_general();
                                }
                                else if(nn==16){
                                    log_in_user=NULL;
                                    break;
                                }
                                else if(nn==17){
                                    int yyear,mmounth,dday,hhour;
                                    printf("enter date and time (like 2023-02-24-1400) : ");fflush(stdin);
                                    scanf("%d-%d-%d-%d",&yyear,&mmounth,&dday,&hhour);fflush(stdin);
                                    printf("changing time successfully\n");fflush(stdin);
                                }
                                else{
                                    printf("invalid input...!!!\n");
                                }

                            }

                        }
                        else if(stricmp(new_user->type,"student")==0&&d==1){//this is student
                            log_in_user=new_user;fflush(stdin);int ll;
                            while(1) {
                                printf("welcome...\n");fflush(stdin);
                                printf("1)change password\n2)reserve foods\n3)take food\n4)charge account\n");
                                printf("5)send charge\n6)see meal plans\n7)cancel reserve\n8)daily reserve\n9)change self\n");
                                printf("10)financial reporting\n11)food delivery report\n12)cheack news\n13)cheack polls\n14)logout\n15)change time\n");fflush(stdin);
                                scanf("%d", &ll);fflush(stdin);
                                if (ll == 1) {
                                    while (1) {
                                        char ol_pass[32];char new_pass[32];fflush(stdin);
                                        printf("old pass:");gets(ol_pass);fflush(stdin);
                                        printf("new pass:");gets(new_pass);fflush(stdin);
                                        int answer = change_pass(new_user->user_id, ol_pass, new_pass, new_user);
                                        if (answer == 2) {
                                            printf("please enter your old pass correct...\n");
                                        }
                                        else if (answer == 0) {
                                            printf("change pass successfully\n");
                                            break;
                                        }
                                    }
                                }
                                else if (ll == 2) {
                                    while (1) {
                                        fflush(stdin);
                                        printf("meal ID    self ID    date time    type    food ID    count\n");printf("\n");fflush(stdin);
                                        meal_plan *vade = show_mealplan(new_user);
                                        if (vade == NULL) {
                                            printf("there isn't any meal plans...\n");fflush(stdin);
                                            break;
                                        }
                                        else {
                                            char selfidd[20];char type[7];char food_id[20];int year, mounth, day;
                                            printf("self ID: ");fflush(stdin);gets(selfidd);fflush(stdin);
                                            printf("type: ");fflush(stdin);gets(type);fflush(stdin);
                                            printf("food ID: ");fflush(stdin);gets(food_id);fflush(stdin);
                                            printf("year-mounth-day: ");fflush(stdin);
                                            scanf("%d-%d-%d", &year, &mounth, &day);fflush(stdin);
                                            int answer = reserve_food(new_user, selfidd, type, food_id, year, mounth,day);
                                            if (answer == 0) {
                                                printf("reserve successfull\n");
                                                printf("do you want to reserve another meal ? (yes-no) ");fflush(stdin);char kk[7];gets(kk);fflush(stdin);
                                                if (stricmp(kk, "no") == 0) {
                                                    break;
                                                }
                                            }
                                            else if (answer == 5) {
                                                printf("you dont'have enough credit please increase your wallet\n");fflush(stdin);
                                                char card_id[20];char pass_card[10];long int charge;
                                                printf("Please enter the desired amount: ");scanf("%ld", &charge);fflush(stdin);
                                                while (1) {
                                                    printf("card ID: ");gets(card_id);fflush(stdin);
                                                    printf("card ID password: ");gets(pass_card);fflush(stdin);
                                                    if (strlen(card_id) != 16 || strlen(pass_card) != 8) {
                                                        printf("the card ID or card ID's password isn't correct!!!\n");
                                                        printf("do you want to exit? (yes-no) ");fflush(stdin);char po[5];gets(po);fflush(stdin);
                                                        if(stricmp(po,"yes")==0)
                                                            break;
                                                    }
                                                    else {
                                                        int e = charge_account(new_user, charge);
                                                        if (e == 0) {
                                                            printf("charge account successfull\n");
                                                            fflush(stdin);
                                                            break;
                                                        }
                                                        else {
                                                            printf("invalid\n");
                                                            fflush(stdin);
                                                        }
                                                    }
                                                }

                                            }
                                            else {
                                                printf("invalid\n");
                                            }
                                        }
                                    }
                                }
                                else if (ll == 3) {
                                    char self_id[20];char typeee[7];
                                    printf("self ID: ");gets(self_id);fflush(stdin);
                                    printf("type the food: ");gets(typeee);fflush(stdin);
                                    int rr = take_food(self_id, new_user, typeee, main_date.year, main_date.mounth,main_date.day);
                                    if (rr == 1) {
                                        printf("this self isn't exist\n ");
                                    }
                                    else if (rr == 11) {
                                        printf("The time is not due...!!!\n");
                                    }
                                    else if (rr == 12) {
                                        printf("this reserve isn't exist\n");
                                    }
                                    else if (rr == 13) {
                                        printf("this food was taken before...\n");
                                    }
                                    else if (rr == 0) {
                                        printf("taking food successfull\n");
                                    }
                                    else {
                                        printf("invalid\n");
                                    }

                                }
                                else if (ll == 4) {
                                    char card_id[20];char pass_card[10];long int charge;
                                    printf("Please enter the desired amount: ");scanf("%ld", &charge);fflush(stdin);
                                    while (1) {
                                        printf("card ID: ");gets(card_id);fflush(stdin);
                                        printf("card ID password: ");gets(pass_card);fflush(stdin);
                                        if (strlen(card_id) != 16 || strlen(pass_card) != 4) {
                                            printf("the card ID or card ID's password isn't correct!!!\n");
                                        }
                                        else {
                                            int e = charge_account(new_user, charge);
                                            if (e == 0) {
                                                printf("charge account successfull\n");fflush(stdin);
                                                break;
                                            }
                                            else {
                                                printf("invalid\n");
                                                fflush(stdin);
                                            }
                                        }
                                    }

                                }
                                else if (ll == 5) {
                                    char youser[20];char nam[20];long int charge;
                                    printf("enter your desired amount: ");scanf("%ld", &charge);fflush(stdin);
                                    printf("user ID: ");gets(youser);fflush(stdin);
                                    printf("name:");gets(nam);fflush(stdin);
                                    int send = send_charge(new_user, charge, youser, nam);
                                    if (send == 1) {
                                        printf("this user isn't exist\n");
                                    }
                                    else if (send == 4) {
                                        printf("Name and ID do not match...\n");
                                    }
                                    else if (send == 2) {
                                        printf("invalid (tuiaa)\n");
                                    }
                                    else if (send == 3) {
                                        printf("your credit isn't enough please increase ypur credit\n");
                                    }
                                    else if (send == 0) {
                                        printf("esnd charge to user %s    %s successfull\n", nam, youser);
                                    }
                                    else {
                                        printf("invalid\n");
                                    }
                                }
                                else if (ll == 6) {
                                    meal_plan *vade = show_mealplan(new_user);
                                    if (vade == NULL) {
                                        printf("nothing to show , The food tables have not been defined yet...\n");
                                    }
                                }
                                else if (ll == 7) {
                                    printf("meal ID    self ID    type    food ID    date time\n");printf("\n");fflush(stdin);
                                    meal_plan *vade = food_reserve(new_user);
                                    if (vade == NULL) {
                                        printf("you don't have any reserve\n");
                                    }
                                    else if (vade != NULL) {
                                        int yearr, mounthh, dayy;char tttype[7];
                                        printf("date time(like 2023-02-24) : ");scanf("%d-%d-%d", &yearr, &mounthh, &dayy);fflush(stdin);
                                        printf("type: ");gets(tttype);fflush(stdin);
                                        int pasokh = cancel_reserve(yearr, mounthh, dayy, tttype, new_user);
                                        if (pasokh == 0) {
                                            printf("canceling reserve successfull\n");
                                            fflush(stdin);
                                        }
                                        else {
                                            printf("invalid\n");
                                            fflush(stdin);
                                        }
                                    }
                                }
                                else if (ll == 8) {
                                    char si[20];char fi[20];
                                    printf("self ID: ");gets(si);fflush(stdin);
                                    printf("food ID: ");gets(fi);fflush(stdin);
                                    int javab = daily_reserve(new_user, si, fi);
                                    if (javab == 0) {
                                        printf("resrve meal successfull\n");fflush(stdin);
                                    }
                                    else if (javab == 1 || javab == 10) {
                                        printf("this self or food isn't exist\n");fflush(stdin);
                                    }
                                    else if (javab == (-4)) {
                                        printf("time is out\n");
                                    }
                                    else if (javab == (-1)) {
                                        printf("this meal plan isn't exist or define\n");
                                    }
                                    else if (javab == (-3)) {
                                        printf("The food is finished\n");
                                    }
                                    else if (javab == (-2)) {
                                        printf("you dont'have enough credit please increase your wallet\n");fflush(stdin);
                                        char card_id[20];char pass_card[10];long int charge;
                                        printf("Please enter the desired amount: ");scanf("%ld", &charge);fflush(stdin);
                                        while (1) {
                                            printf("card ID: ");gets(card_id);fflush(stdin);
                                            printf("card ID password: ");gets(pass_card);fflush(stdin);
                                            if (strlen(card_id) != 16 || strlen(pass_card) != 4) {
                                                printf("the card ID or card ID's password isn't correct!!!\n");
                                            }
                                            else {
                                                int e = charge_account(new_user, charge);
                                                if (e == 0) {
                                                    printf("charge account successfull\n");fflush(stdin);
                                                    break;
                                                }
                                                else {
                                                    printf("invalid\n");fflush(stdin);
                                                }
                                            }
                                        }
                                    }
                                    else {
                                        printf("invalid\n");
                                    }
                                }
                                else if (ll == 9) {
                                    fflush(stdin);
                                    int sal, mah, roz;char tipe[20];char new_self_id[20];
                                    printf("date time(like 2023-02-24) : ");scanf("%d-%d-%d", &sal, &mah, &roz);fflush(stdin);
                                    printf("type meal (lunch-dinner) : ");gets(tipe);fflush(stdin);
                                    printf("new self ID: ");gets(new_self_id);fflush(stdin);
                                    int h = change_self(new_user, sal, mah, roz, tipe, new_self_id);
                                    if (h == 1) {
                                        printf("this self isn't exist\n");
                                    }
                                    else if (h == 10 || h == 11 || h == 12) {
                                        printf("time is out\n");
                                    }
                                    else if (h == 13) {
                                        printf("you didn't serve this food\n");
                                    }
                                    else if (h == 7) {
                                        printf("in this self this food isn't served\n");
                                    }
                                    else if (h == 0) {
                                        printf("change self successfully\n");
                                    }
                                    else {
                                        printf("invalid\n");
                                    }
                                }
                                else if (ll == 10) {
                                    report_user(new_user->user_id);
                                }
                                else if (ll == 11) {
                                    printf("meal ID    self ID    type    food ID    date time\n");printf("\n");fflush(stdin);
                                    meal_plan *vade = see_a(new_user);
                                    if (vade == NULL) {
                                        printf("you didn't any reserve\n");
                                    }
                                    printf("these are your reserves...\n");fflush(stdin);
                                }
                                else if (ll == 12) {
                                    print_news();
                                }
                                else if (ll == 13) {
                                    print_pool();
                                }
                                else if (ll == 14) {
                                    log_in_user = NULL;
                                    break;
                                }
                                else if(ll==15){
                                    int yyear,mmounth,dday,hhour;
                                    printf("enter date and time (like 2023-02-24-1400) : ");fflush(stdin);
                                    scanf("%d-%d-%d-%d",&yyear,&mmounth,&dday,&hhour);fflush(stdin);
                                    printf("changing time successfully\n");fflush(stdin);
                                }
                                else{
                                    printf("invaild input\n");
                                }
                            }

                        }

            }
        }
        else if(n==3){
            break;
        }
        else{
            printf("invalid input...\n");
        }
    }
}