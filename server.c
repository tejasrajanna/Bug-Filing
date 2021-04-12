#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"server.h"
int checkID() //function to find the last assigned ID
{
    FILE *check; 
    struct bug ID;
    ID.id=0; // default ID in case file is empty
    check= fopen ("bug", "rb"); // Open file for reading 
    if (check == NULL) 
    return 0; 
    // read file contents till end of file 
    while(fread(&ID, sizeof(struct bug), 1, check)>0) ;
    return ID.id;
}
void datime(char *date) // function to get system date and time
{
    time_t rawtime;
    struct tm*info;
    time(&rawtime);
    info=localtime(&rawtime);
    strcpy(date,asctime(info));
}
void add() //function to add a bug to the file
{ struct bug re;int c=0;
// taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
  printf("Enter name of user filing bug (max 50 letters)\n");
  scanf(" %[^\n]",re.name); 
  printf("Enter details of bug in less than 200 letters\n");
  scanf(" %[^\n]",re.details);
  printf("Enter type of the bug (major,minor or cosmetic)\n");
  scanf("%s",re.type);
  printf("Enter priority of bug (low, medium or high) \n");
  scanf("%s",re.prio);
  strcpy(re.stat,"Not assigned"); // automatic assignment of bug status upon filing
  FILE *outfile;  
    outfile = fopen ("bug", "ab"); // open file to append
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } //handling error
    c=checkID(); //to automatically assign bug ID and ensure limit of 100 is maintained
if(c>99)
{
    printf("Maximum limit of 100 reached\n");
    return;
} 
    re.id=c+1;   // automatically assign ID
    strcpy(re.assiper," "); //blank space for assigned person which needs to be decided by manager
    datime(re.time);
    fwrite (&re, sizeof(struct bug), 1, outfile);  // write structure to file 
    if(fwrite != 0)  
        {
            printf("contents to file written successfully !\n"); 
            printf("Your bug ID is %d \n",re.id);
        }
    else 
        printf("error writing file !\n"); //handling error
    fclose (outfile);  // close file 
} 
int disp(int choice) //function to display contents of file
{int i=0,nf=0;
FILE *infile; 
    struct bug in; 
    infile = fopen ("bug", "rb");  // Open file for reading 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    if(choice==0) 
   {  // read file contents till end of file 
       while(fread(&in, sizeof(struct bug), 1, infile)>0) 
        printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        in.id, in.name, in.details, in.time, in.type, in.prio, in.stat,in.assiper); //print details of bug on screen    
   }
   if(choice!=0)
   {
         // read file contents till end of file 
    while(fread(&in, sizeof(struct bug), 1, infile)>0) 
    {
       if (in.id==choice)  //check for ID match
        printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        in.id, in.name, in.details, in.time, in.type, in.prio, in.stat,in.assiper); //print details of bug on screen
       else
       nf++;
     i++;  
    }
    if(nf==i) //check if no ID matched input ID
    printf("Matching ID not found\n");
   }
    fclose (infile);  // close file 
    return checkID();
}
void assign(char as[50],int sid) // function for manager to assign a person to specific bug
{  int i=0,nf=0,j=1;
struct bug assi[100];
FILE *infile;
infile = fopen ("bug", "rb"); // open file for reading
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
    // read file contents till end of file 
    while(fread(&assi[i], sizeof(struct bug), 1, infile)>0) 
    {
       if (assi[i].id==sid)  //check for ID match
       {
       strcpy(assi[i].assiper,as); //filling in the name according to manager input
       strcpy(assi[i].stat,"Assigned"); // automatically change status after person has been assigned to specific bug by manager
       }
       else
       nf++;
     i++;  
    }
    if(nf==i) //check if no ID matched input ID
    {
    printf("Matching ID not found\n");
    return; // if input ID does not match, no need to rewrite the file so exit the function
    }
    fclose(infile); // close file
   FILE *p;
p=fopen("bug","wb");  //open file for writing, erase the previously stored data and rewrite the file using the new structure 
if ((p == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } //handling error
fwrite(&assi[0],sizeof(struct bug),1,p); // write the first bug details
fclose(p); // close file
FILE *change;
change=fopen("bug","ab"); // open file to append for the other bug details to avoid rewriting the file
if((change==NULL))
{
    fprintf(stderr,"\nError opening file\n");
    exit(1);
} //handling error
 while(j<i)
 {
     fwrite(&assi[j], sizeof(struct bug), 1, change);  //writing the whole new structure into the file
     j++;
 }
    if(fwrite != 0)  
        {
            printf("contents to file written and status automatically changed to assigned\n"); 
        }
    else 
        printf("error writing file !\n");//handling error        
fclose(change); // close file
}
void changestat(int nid, char cper[50],char chan[50]) //function for assigned person of a specific bug to change its status
{ int i=0,nfc=0,j=1;
struct bug n[100];
FILE *fp; 
    fp = fopen ("bug", "rb"); // Open file for reading
    if ((fp == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
    // read file contents till end of file 
    while(fread(&n[i], sizeof(struct bug), 1, fp)>0) 
       {
       if (n[i].id==nid) // checking for input ID in the file
       {printf("Matching ID found\n");
       if(strcmpi(n[i].assiper,cper)==0) // checking for input name of assigned person within the file
           strcpy(n[i].stat,chan); //changing status if both ID and name match
        else
        {
        printf("But assigned person name does not match\n");
        return; // if input assigned person name does not match, no need to rewrite file so exit the function
        }   
        }
        else
         nfc++;
       i++;
       }
       if(nfc==i) //check if no ID matched input ID
       {printf("Matching ID not found\n"); 
       return; //if input ID does not match no need to rewrite file so exit the function
       }
 fclose (fp); // close file
FILE *p;
p=fopen("bug","wb");  //open file for writing, erase the previously stored data and rewrite the file using the new structure 
if ((p == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
fwrite(&n[0],sizeof(struct bug),1,p); //writing the first bug details
fclose(p); //close file
FILE *change;
change=fopen("bug","ab"); //open file to append for the other bug details to avoid rewriting the file
if((change==NULL))
{
    fprintf(stderr,"\nError opening file\n");
    exit(1);
}// handling error
 while(j<i)
 {
     fwrite(&n[j], sizeof(struct bug), 1, change);  //writing the whole new structure into the file
     j++;
 }
    if(fwrite != 0)  
        {
            printf("contents to file written successfully !\n"); 
        }
    else 
        printf("error writing file !\n"); //handling error       
fclose(change); // close file 
}
int person(char per[50]) //function to search for bugs filed by a specific person
{  struct bug p;int count=0;

   FILE *fp; 
    fp = fopen ("bug", "rb"); // Open file for reading 
    if ((fp == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } //handling error
    // read file contents till end of file 
    while(fread(&p, sizeof(struct bug), 1, fp)>0) 
       {
       if (strcmpi(per,p.name)==0) //checking if input name matches any user name within the file
       {
        printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        p.id, p.name, p.details, p.time, p.type, p.prio, p.stat,p.assiper); //printing details of bug filed by input user name
        count++;
       }
     }
  fclose(fp); //close file
  return count;
}
int pri(char pr[50]) //function search for bugs with specific priority
{  struct bug p;int count=0;
FILE *fp;  
    fp = fopen ("bug", "rb"); // Open file for reading
    if ((fp == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
    // read file contents till end of file 
    while(fread(&p, sizeof(struct bug), 1, fp)>0) 
       {
       if (strcmpi(pr,p.prio)==0) //checking if input priority matches with any within the file
       {
       printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        p.id, p.name, p.details, p.time, p.type, p.prio, p.stat,p.assiper); // printing details of bug if priority matches
        count++;
       }
     }
fclose(fp); //close file
return count;
}
int status(char st[50]) // function to search for bugs with specific status
{  struct bug p;int count=0;
   FILE *fp; 
    fp = fopen ("bug", "rb"); // Open file for reading 
    if ((fp == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
    // read file contents till end of file 
    while(fread(&p, sizeof(struct bug), 1, fp)>0) 
       {
       if (strcmpi(st,p.stat)==0) //checking if input status matches withy any within the file
       {
       printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        p.id, p.name, p.details, p.time, p.type, p.prio, p.stat,p.assiper); // printing details of bug if status matches
        count++;
       }
     }
  fclose(fp);// close file
  return count;
}
int type(char ty[50]) // function to search for bugs with a specific type
{ struct bug p;int count=0;
   FILE *fp;  
    fp = fopen ("bug", "rb");  // Open file for reading
    if ((fp == NULL)) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } // handling error
    // read file contents till end of file 
    while(fread(&p, sizeof(struct bug), 1, fp)>0) 
       {
       if (strcmpi(ty,p.type)==0) // checking if input type matches with any within the file
       {
         printf ("id = %d    name = %s   details=%s  date,time=%s type=%s     priority=%s    status=%s   assigned person=%s\n", 
        p.id, p.name, p.details, p.time, p.type, p.prio, p.stat,p.assiper); // printing details of bug if type matches
        count++;
       }
     }
  fclose(fp); //close file
  return count;
}