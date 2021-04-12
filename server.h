struct bug // a structure to read and write 
{ 
    int id; //stores bug ID
    char name[50]; //stores name of user filing bug
    char details[200];  //stores details of bug
    char type[50]; //stores type of bug
    char prio[50]; // stores priority of bug
    char stat[50]; //stores status of bug
    char assiper[50]; //stores name of person assigned to bug
    char time[50]; //stores time and date when bug was filed
}; 
int checkID();
void datime(char *);
void add();
int disp(int);
void assign(char[],int);
void changestat(int, char[],char[]);
int person(char[]);
int pri(char[]);
int status(char[]);
int type(char[]);
