#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH_COMMAND 300

#define MAX_NO_TASKS 100

#define MAX_LENGTH_TITLE 100
#define MAX_LENGTH_DESCRIPTION 200
#define MAX_LENGTH_TIME 33

#define WEEK_CELL_FIRST_COL_WIDTH 10
#define WEEK_CELL_OTHER_COL_WIDTH 20

enum Status {IN_PROGRESS, DONE, ARCHIVED};
char * status_name[] = {"In Progress", "Done", "Archived"};
enum CommandType {ADD, EDIT, SHOW, DELETE, QUIT, INVALID};
char * command_name[] = {"ADD", "EDIT", "SHOW", "DELETE", "QUIT", "INVALID"};

struct Task {
    int num;
    char title[MAX_LENGTH_TITLE+1]; 
    char description[MAX_LENGTH_DESCRIPTION+1];
    char time[MAX_LENGTH_TIME+1];
    enum Status status;
};

void printTask(struct Task * task) {
    printf("--------------------------------------------\n");
    printf("Num: #%d. Title: %s\n", task->num, task->title);
    printf("Description: %s\n", task->description);
    printf("Status: %s\n", status_name[task->status]);
    printf("--------------------------------------------\n");
}
void printUnsupportedTime(struct Task * task) {
    printf("----- Show week view -----\n");
    printf("Error: Unsupported time with non-zero minutes: %s\n", task->time);
    printf("In Task:\n");
    printTask(task);
}

// ------ Begin: Student Answer ------
enum CommandType getCommandType(char * command) {  
    // TODO
    enum CommandType cmdtype[] = {ADD, EDIT, SHOW, DELETE, QUIT};
    char* cmd_name[] = {"Add", "Edit", "Show", "Delete", "Quit"};
    int i = 0;
    for (i; i < 5; i++)
    	if (strstr(command, cmd_name[i]) == command || strstr(command, command_name[i]) == command)
    		return cmdtype[i];
    
    return INVALID;
}

enum Status getStatusFromEdit(char * edit_cmd) {
	char* status_nameup[] = {"I", "D", "A"};
	char* status_namenor[] = {"i", "d", "a"};
	enum Status status[] = {IN_PROGRESS, DONE, ARCHIVED};
    char takeStatus[1];
	sscanf(edit_cmd, "%*s #%*d status:[%[^]]",takeStatus);
    int i =0;
	
	for (i;i<3;i++) 
	if (strcmp(takeStatus,status_nameup[i]) == 0 || strcmp(takeStatus,status_namenor[i]) == 0  ) 
		return status[i];

}
	
	
// Other functions
void getTitleFromAdd( char * command,char * out_title){
	sscanf(command, "%*s [%[^]] %*s %*s", out_title);
}
void getDescriptionFromAdd( char *command,char * out_description){
	sscanf(command, "%*s [%*[^]]] [%[^]] %*s", out_description);
}
void getTimeFromAdd(char*command,char * out_time){
	sscanf(command, "%*s [%*[^]]] [%*[^]]] [%[^]]", out_time);
}

int checkTitle(char * raw_title) {
	char * ptr =  raw_title;
	int ktra;

	if (strlen(raw_title) > MAX_LENGTH_TITLE){
		return strlen(raw_title);}
	else {
		if (raw_title[0] == ' ' ) 
			return 0;
		for (ptr; ptr < raw_title + strlen(raw_title);ptr++)
		{
		if ((*ptr >= 'a' && *ptr <= 'z') ||
			(*ptr >= 'A' && *ptr  <='Z') || 
			(*ptr >= '0' && *ptr <= '9') || 
			(*ptr == ',') || 
			(*ptr == '.') || 
			(*ptr == '/') || 
			(*ptr == '|') || 
			(*ptr == ':') || 
			(*ptr == '-') ||
			(*ptr == ' ')) {
				continue;
			}
			else {
				return ptr- raw_title;
				break;
			}
		}
		if (raw_title[strlen(raw_title)-1] == ' ' ) 
			return strlen(raw_title);
		else return -1;
	}
		
}


int checkDescription(char * raw_description) {
	char * ptr =  raw_description;
	int ktra = 0;
	
	if (strlen(raw_description) <= 200){
		if (raw_description[0] == ' ' ) {
			return 0;
		} 
		for (ptr; ptr < raw_description + strlen(raw_description);ptr++)
		{
		if ((*ptr >= 'a' && *ptr <= 'z') ||
			(*ptr >= 'A' && *ptr <= 'Z') || 
			(*ptr >= '0' && *ptr <= '9') || 
			(*ptr == ',') || 
			(*ptr == '.') || 
			(*ptr == '/') || 
			(*ptr == '|') || 
			(*ptr == ':') || 
			(*ptr == '-') ||
			(*ptr == ' ')) {
				continue;
			}
			else {
				return ptr-raw_description;
				break;
			}
			}
		if (raw_description[strlen(raw_description)] == ' ' ) 
			return strlen(raw_description);
		else return -1;
		}
	else {
			return strlen(raw_description);
	}
}

int checkTime(char*raw_time) {
	char datetime1[17],datetime2[17];
	int hh1,mm1,dd1,mo1,yyyy1;
	int hh2,mm2,dd2,mo2,yyyy2;
	
	//Chia rawtime thanh 2 datetime1 and datetime2
	char *link = strchr(raw_time, '-');
	strncpy(datetime1,raw_time,link-raw_time-1);
	strcpy(datetime2, link+1);
	
	//Chia datetime1 thành hh,mm,dd,mo,yyyy
	sscanf(datetime1, "%d:%*d|%*d/%*d/%*d" ,&hh1);
	sscanf(datetime1, "%*d:%d|%*d/%*d/%*d" ,&mm1);
	sscanf(datetime1, "%*d:%*d|%d/%*d/%*d" ,&dd1);
	sscanf(datetime1, "%*d:%*d|%*d/%d/%*d" ,&mo1);
	sscanf(datetime1, "%*d:%*d|%*d/%*d/%d" ,&yyyy1);
  	
  	//Chia datetime2 thành hh,mm,dd,mo,yyyy
	sscanf(datetime2, "%d:%*d|%*d/%*d/%*d" ,&hh2);
	sscanf(datetime2, "%*d:%d|%*d/%*d/%*d" ,&mm2);
	sscanf(datetime2, "%*d:%*d|%d/%*d/%*d" ,&dd2);
	sscanf(datetime2, "%*d:%*d|%*d/%d/%*d" ,&mo2);
	sscanf(datetime2, "%*d:%*d|%*d/%*d/%d" ,&yyyy2);
  	
  	//Xet gio phut
  	if (hh1 < 0 || hh1 > 23 ) {
  		return 1100 + hh1;
	  }
	if (hh2 < 0 || hh2 > 23 ) {
  		return 1200 + hh2 ;
	  }
	if (mm1 < 0 || mm1 > 59 ) {
  		return 2100 + mm1;
	  }
	if (mm2 < 0 || mm2 > 59 ) {
  		return 2200+mm2;
	  }
  	
  	//Xet nam thang ngay
  	//Nam
  	if (yyyy1 < 0 || yyyy1 > 9999) {
  		return 510000+yyyy1;}
  	if (yyyy2 < 0 || yyyy2 > 9999) {
  		return 520000+yyyy2;
	  }
	  
	//Thang
	if (mo1 < 1 || mo1 > 12) {
		return 4100+mo1;
	}
	if (mo2 < 1 || mo2 > 12) {
		return 4200+mo2;
	}
	
	//Ngay
	if (dd1 < 1 || dd1 > 31) {
		return 3100+dd1;
	}
	if (dd2 < 1 || dd2 > 31) {
		return 3200+dd2;
	}
	  
	//Check nam thang ngay phu hop
	//Nam nhuan
	if ((yyyy1 % 4 == 0 && yyyy1 % 100 != 0) || yyyy1 % 400 == 0) {
  		if (mo1 == 2 && dd1 > 29){
  			return 3100+dd1;
		  } 
	else {
		if (mo1 == 2 && dd1 > 28)
			return 3100+dd1;
	}
	
	}
	if ((yyyy2 % 4 == 0 && yyyy2 % 100 != 0) || yyyy2 % 400 == 0) {
  		if (mo2 == 2 && dd2 > 29 ) {
				return 3200+dd2;
		}
		
	}
	else {
		if (mo2 == 2 && dd2 > 28)
			return 3100+dd2;
	}
	
		  
	//Cac ngay trong thang
	if (mo1 == 4 || mo1 == 6 || mo1 == 9 || mo1 == 11) {
		if (dd1 > 30) 
			return 3100+dd1;
	}
	if (mo2 == 4 || mo2 == 6 || mo2 == 9 || mo2 == 11) {
		if (dd2 > 30) 
			return 3200+dd2;
	}		
  	
  	//Check datetime1 vs datetime2
  	if (yyyy2 < yyyy1)
  		return 0;
	else if (yyyy2 == yyyy1) {
		if (mo2 < mo1) 
			return 0;
		if (mo1 == mo2) {
			if (dd2 < dd1) 
				return 0; 
			if (dd1 == dd2) {
				if (hh2 < hh1)
					return 0;
			}
				if (hh2 == hh1) {
					if (mm2 < mm1 )
						return 0;
				}
		}
	}
	else 
	return -1;
}
void getTitleFromEdit( char * command,char * out_title){
	sscanf(command, "%*s #%*d title:[%[^]]", out_title);
}
void getDescriptionFromEdit( char *command,char * out_description){
	sscanf(command, "%*s #%*d description:[%[^]]", out_description);
}
void getTimeFromEdit(char*command,char * out_time){
	sscanf(command, "%*s #%*d time:[%[^]]", out_time);
}
int getNumFromCommand(char * command) {
	int num;
	sscanf(command, "%*s #%d ", &num);
	if (num < 1)
		return 0;
	if (num == ' ')
		return -1;
	return num;

}

  int getFieldFromEdit(char * edit_cmd) {
 	//Edit #2 status:[D]
	char field[15];
	sscanf(edit_cmd, "%*s #%*d %[^:][%[^]]", field);
	if ( strcmp(field,"title")==0)
		return 1;
	if ( strcmp(field,"description")==0) 
		return 2;
	if ( strcmp(field,"time")==0)
		return 3;
	if ( strcmp(field,"status")==0)
		return 4;
	return 0;
	
}


bool addTask(struct Task * array_tasks, int no_tasks, char * new_title, char * new_description, char * new_time) {
	if (no_tasks == MAX_NO_TASKS)
		return false;
	array_tasks[no_tasks].num = no_tasks+1;
	strcpy(array_tasks[no_tasks].title, new_title );
	strcpy(array_tasks[no_tasks].description, new_description);
	strcpy(array_tasks[no_tasks].time, new_time );
	array_tasks[no_tasks].status = IN_PROGRESS;
		return true;

}

void printAllTasks(struct Task * array_tasks, int no_tasks) {
	int i;
	for ( i = 0; i < no_tasks; ++i) {
        printTask(&array_tasks[i]);
	
	}
}

void printTaskByNum(struct Task * array_tasks, int no_tasks,int num) {
	if (num >= no_tasks || num <= 0)
		printf("NO TASK AVAILABLE");
	else 
		printTask(&array_tasks[num - 1]);
}
	
void printHeadTasks(struct Task * array_tasks, int no_tasks,int quan) {
	int i,n;
	n = quan;
	if (n > no_tasks) 
	n = no_tasks;

	for ( i = 0; i < n; ++i) {
        printTask(&array_tasks[i]);
	
	}
}
	
void printTailTasks(struct Task * array_tasks, int no_tasks, int quan) {
	int i;
	i = no_tasks - quan ;
	if (i < 0) i = 0;
	
	for ( i ; i < no_tasks; ++i) {
        printTask(&array_tasks[i]);
	
	}
}

void printFilteredTasksByTitle(struct Task * array_tasks,int no_tasks, char * filter_title) {
	int i;
	for ( i = 0 ; i < no_tasks; ++i) {
		if (strstr(array_tasks[i].title, filter_title) != NULL )
        printTask(&array_tasks[i]);
	
	}
}

void printFilteredTasksByDescription(struct Task * array_tasks,int no_tasks, char * filter_description) {
	int i;
	for ( i = 0 ; i < no_tasks; ++i) {
		if (strstr(array_tasks[i].description, filter_description) != NULL )
        printTask(&array_tasks[i]);
	
	}
}

void printFilteredTasksByStatus(struct Task * array_tasks,int no_tasks, enum Status filter_status) {
	int i;
	for ( i = 0 ; i < no_tasks; ++i) {
		if (array_tasks[i].status == filter_status)
        printTask(&array_tasks[i]);
	
	}
}

void checkShow(char * command,struct Task * array_tasks, int no_tasks) {
	if (strstr(command,"Show all") == command)
		printAllTasks(array_tasks, no_tasks);
	else if (strstr(command,"Show head") == command) {
		int quan = 0;
		sscanf(command,"Show head %%%d",&quan);
		printHeadTasks(array_tasks,no_tasks,quan);
	}
	else if (strstr(command,"Show tail") == command) {
		int quan = 0;
		sscanf(command,"Show tail %%%d",&quan);
		printTailTasks(array_tasks,no_tasks,quan);
	}
	else if (strstr(command,"Show filter title:") == command) {
		char filter_title[MAX_LENGTH_TITLE];
		sscanf(command, "Show filter title:[%[^]]",filter_title);
		printFilteredTasksByTitle(array_tasks,no_tasks,filter_title);
		}
	else if (strstr(command,"Show filter description:") == command) {
		char filter_description[MAX_LENGTH_DESCRIPTION];
		sscanf(command, "Show filter description:[%[^]]",filter_description);
		printFilteredTasksByDescription(array_tasks,no_tasks,filter_description);
		}
	else if (strstr(command,"Show filter status:") == command) {
		enum Status filter_status;
		sscanf(command, "Show filter status:[%[^]]",filter_status);
		printFilteredTasksByStatus(array_tasks,no_tasks,filter_status);
		
	}
	else {
		int num = 0;
		sscanf(command, "Show #%d",&num);
		printTaskByNum(array_tasks,no_tasks,num);
	}
}

int getNumFromDelete(char * command) {
	int num;
	sscanf(command,"Delete #%d",&num);
	if (num < 1)
		return 0;
	if (num == ' ')
		return -1;
	return num;
}

 bool deleteTask(struct Task * array_tasks, int no_tasks, int num) {
 	
 	if ( num <= 0 || no_tasks == 0 || num > no_tasks ) 
 		return false;
 	int i = num ;
 	for (i ; i < no_tasks ;i++) {
 		array_tasks[i-1]= array_tasks[i];
 		array_tasks[i-1].num = i ;
	}

	 return true;
}

//void showWeekTime(char* command,char * date) {
	
	
//}
//
// int printWeekTime(struct Task * array_tasks, int no_tasks,char * date) {
// 	char thu[3];
// 	int ngay,thang,nam;
// 	sscanf(date,"%s/%d/%d/%d", thu,&ngay,&thang,&nam );
// 	char weekday_lw[]= {"MON","TUE","WED","THU","FRI","SAT","SUN"};
// 	char weekday_up[]= {"mon","tue","wed","thu","fri","sat","sun"};
// 	int i;
// 	char batdau[];
// 	char ketthuc[];
// 	
// 	for ( i = 0 ; i < 7; ++i) {
// 		strcmp(weekday_lw[i], thu) == 0 || strcmp(weekday_up[i], thu) == 0 {
// 			thu = weekday_up[i];
//		}
// 		
//	for ( i = 0 ; i < no_tasks; ++i) {
// 	if ( array_tasks == NULL || no_tasks == 0 || date == NULL)
// 		return -1;
// 		
// }

// ------ End: Student Answer ------

void runTodoApp() {
    // Example of command Add
    char command[MAX_LENGTH_COMMAND+1];
    char raw_title[300], raw_description[300],raw_time[100];
    struct Task * array_tasks = malloc(MAX_NO_TASKS * sizeof(struct Task));
    int no_tasks = 0;
    bool escape = true;
    int num;
//	char date[]
    
    while (escape) {
        // Sample input:
        // Add [Course Intro: to Programming] [Room 701-H6] [07:00|29/02/2023-12:00|29/02/2023]
/*  
Add [aaaaaa] [1111] [07:00|01/10/2023-12:00|01/10/2023]
Add [bbbbbb] [2222] [07:00|01/10/2023-12:00|01/10/2023]
Add [cccccc] [3333] [07:00|01/10/2023-12:00|01/10/2023]
Add [dddddd] [4444] [07:00|01/10/2023-12:00|01/10/2023]
*/
        fgets(command, MAX_LENGTH_COMMAND+1, stdin);
        command[strlen(command)-1] = '\0';
        
        enum Status getStatus = getStatusFromEdit(command);
        enum CommandType commandType = getCommandType(command);
        printf("Command     : %s\n", command);
        printf("Command type: %s\n", command_name[commandType]);

        switch (getCommandType(command)) {
        	case ADD:
        	getTitleFromAdd(command, raw_title);
			getDescriptionFromAdd(command, raw_description);
			getTimeFromAdd(command, raw_time);
			printf("%d\n",checkTitle(raw_title));
			printf("%d\n",checkDescription(raw_description));
			printf("%d\n",checkTime(raw_time));
			if (addTask(array_tasks,no_tasks,raw_title,raw_description,raw_time)) 
				no_tasks++;
			break;
    
			case EDIT:
			getTitleFromEdit(command, raw_title);
			getDescriptionFromEdit(command, raw_description);
			getTimeFromEdit(command, raw_time);
			printf("%d\n",getNumFromCommand(command)); 
			printf("%d\n",getFieldFromEdit(command)); 
			printf("Status: %s\n", status_name[getStatus]);
			break;
			
			case SHOW:
		    checkShow(command,array_tasks,no_tasks);
			break;	
			
			case DELETE:
			num = getNumFromDelete(command);
			if (deleteTask(array_tasks,no_tasks,num))
			no_tasks--;
			else printf("Can't Delete");
			break;
			
			case QUIT:
			escape = false;
			break;
			
		break;
		}
		

 	
		
		
//        break;  // only one loop for simple test
                // actual app will break when encounter QUIT command
    }
    free(array_tasks);
}

int main() {
    runTodoApp();
    return 0;
}
