#include "stdio.h"
#include "iostream"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

using namespace std;
#define sharedData(xxx)  (int *)shmat(shmget(xxx, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR), NULL, 0)

#define receiveX    1000 
#define sendY       1001

int x,y;
int writeIPC(int flag){
	static int *resultRB;
	if(flag==0)
{		resultRB = sharedData(sendY);*resultRB = 0;
			   }
	else {
		*resultRB = y;
		 }

}



int readIPC(int flag){
	static int *resultRB;
	if(flag==0){
		resultRB = sharedData(receiveX);*resultRB = 0;
			   }
	else {
		x = *resultRB;
		 }

}



int main(){
static int count;
	writeIPC(0);
	readIPC(0);
    cout<<"Init Done!!"<<endl;	
	while(1){
	
    count++;
    if(y>=65530)y=0;
    if(count>10000) {y++;count=0;}
    writeIPC(1);
    readIPC(1);
    printf("data X = %d || data Y = %d \n",x,y);

	}
}