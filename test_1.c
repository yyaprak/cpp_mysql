#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //usleep
#include <mysql/mysql.h>
#include <iostream>
#include <ctime>

#define DATABASE_NAME		"sensor_test"
#define DATABASE_USERNAME	"root"
#define DATABASE_PASSWORD	"320457"


MYSQL *mysql1;

void mysql_connect (void)
{
    //initialize MYSQL object for connections
	mysql1 = mysql_init(NULL);

    if(mysql1 == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(mysql1));
        return;
    }

    //Connect to the database
    if(mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL)
    {
    	fprintf(stderr, "%s\n", mysql_error(mysql1));
    }
    else
    {
        printf("Database connection successful.\n");
    }
}
void mysql_disconnect (void)
{
    mysql_close(mysql1);
    printf( "Disconnected from database.\n");
}

void mysql_insert (int id,double isi,double nem,double gas)
{
   //vector times;   //a vector of alarm times

    if(mysql1 != NULL)
    {

    	//time_t t = time(0);   // get time now
    	//struct tm * now = localtime( & t );
	//printf("%d %d %d %lu ",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
	 time_t now = time(0);
 	char* dt = ctime(&now);
        printf("zaman %s\n",dt);
        char zaman[20];
        int say=0;
             

    	/*cout << (now->tm_year + 1900) << '-' 
    	     << (now->tm_mon + 1) << '-'
    	     <<  now->tm_mday
    	     << endl;*/
        
        char statement[512];
	//2017-02-22 07:20:20
	struct tm *ltm = localtime(&now);
	//const char *my_str = "'"+id+"','"+isi+"','"+nem+"','"+gas+"'";
	snprintf(statement, 512, "insert into sensor_log (log_slaveid,log_isi,log_nem,log_gaz,log_date) VALUES (%d,%1f,%1f,%1f,'%d-%d-%d %d:%d:%d')", id,isi,nem,gas,ltm->tm_year+1900,ltm->tm_mon+1,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
        printf("%s\n",statement);	
	//mysql_query(conn, statement);
        //Retrieve all data from alarm_times
        if (mysql_query(mysql1,statement ))

        {
            fprintf(stderr, "hataaaa kocum %s\n", mysql_error(mysql1));
            return;
        }
    }
}

int main()
{
mysql_connect();

while(1){
if (mysql1 != NULL)
    {
        if (!mysql_query(mysql1, "SELECT * FROM sensor_slave"))
        {
        	MYSQL_RES *result = mysql_store_result(mysql1);
        	if (result != NULL)
        	{
        		//Get the number of columns
        		int num_rows = mysql_num_rows(result);
        		int num_fields = mysql_num_fields(result);

        		MYSQL_ROW row;			//An array of strings
			printf(" Gelen degerler\n");
				while( (row = mysql_fetch_row(result)) ){
					//if(num_fields >= 2)
					{
						/*char *slave_id = row[0];
						char *slave_name =  row[3];*/
					
						printf( "%s %s\n", row[0],row[3]);
			        	}
				}
			    
			    
			    
	
   	            mysql_free_result(result);
        	}
        }

    }
   mysql_insert(1,-90.25,30.35,999);//veri inserting to the database
  usleep(1000000);
  }
 mysql_disconnect();


return 0;
}
