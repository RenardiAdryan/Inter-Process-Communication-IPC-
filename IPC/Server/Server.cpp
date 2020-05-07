#include "stdio.h"
#include "iostream"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

using namespace std;
#define sharedData(xxx)  (int *)shmat(shmget(xxx, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR), NULL, 0)

#define sendX   1000 
#define receiveY 1001

int x,y;
int writeIPC(int flag){
	static int *resultRB;
	if(flag==0){
		resultRB = sharedData(sendX);*resultRB = 0;
			   }
	else {
		*resultRB = x;
		 }
}



int readIPC(int flag){
	static int *resultRB;
	if(flag==0){
		resultRB = sharedData(receiveY);*resultRB = 0;
			   }
	else {
		y = *resultRB;
		 }
}



int main(){
static int count;
	writeIPC(0);readIPC(0);
    cout<<"Init Done!!"<<endl;	
	
	while(1){
    count++;
    if(x>=65530)x=0;
    if(count>1000) {x++;count=0;}
    writeIPC(1);
    readIPC (1);
    printf("data X = %d || data Y = %d \n",x,y);

	}
}