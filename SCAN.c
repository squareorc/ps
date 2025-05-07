//Disk scheduling using SCAN algorithm - also known as Elevator algorithm and moves only in one direction
#include<stdio.h>
#include<stdlib.h>

void sort(int tracks[] , int n){
    for(int i=0 ; i<n-1 ; i++){
        for(int j=0 ; j<n-i-1 ; j++){
            if(tracks[j] > tracks[j+1]){
                int temp = tracks[j];
                tracks[j] = tracks[j+1];
                tracks[j+1] = temp;
            }
        }
    }
}
void SCAN(){
    int disk_size, head, total_movement = 0, direction;
    printf("Enter the disk size: ");
    scanf("%d",&disk_size);
    int n;
    printf("Enter the no of tracks: ");
    scanf("%d",&n);
    printf("Enter track requests: ");
    int tracks[n];
    for(int i=0 ; i<n ; i++){
        scanf("%d",&tracks[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d",&head);
    printf("Enter the direction (1 for right and 0 for left): ");
    scanf("%d",&direction);

    tracks[n++] = head;
    tracks[n++] = (direction == 1) ? disk_size - 1 : 0;
    /*This guarantees the head will sweep fully to the end before reversing. After sorting, those appear at indices pos (head) and either 0 or n–1 (the end). We then remove them conceptually when computing the average:
    float avg_seek_time = total_movement / (n – 2);
    We divide by n–2 because we don’t count the two “dummy” requests (the head’s starting position and the end-of-disk) in the average seek‑time denominator.*/

    sort(tracks , n);

    int k;
    for(k=0 ; k<n ; k++)
        if(tracks[k] == head) break;

    printf("-----SCAN DISK SCHEDULING-----\n");
    printf("%-15s %-15s %-20s\n","FROM","TO","SEEK(TRACKS)");

    if(direction == 1){
        //Move “right” (toward higher track numbers)
        for(int i= k ; i<n ; i++){
            int move = abs(head - tracks[i]);
            printf("%-15d %-15d %-20d\n",head,tracks[i],move);
            total_movement += move;
            head = tracks[i];
        }
        //Then reverse and service any remaining on the “left”
        for(int i = k-1 ; i>=0 ; i--){
            int move = abs(head - tracks[i]);
            printf("%-15d %-15d %-20d\n",head,tracks[i],move);
            total_movement += move;
            head = tracks[i];
        }
    }
        else{
            //first move “left” (toward 0)
            for(int i = k ; i>=0 ; i--){
                int move = abs(head - tracks[i]);
                printf("%-15d %-15d %-20d\n",head,tracks[i],move);
                total_movement += move;
                head = tracks[i];
            }
            // then reverse direction and service the rest on the “right”
            for(int i = k+1 ; i<n ; i++){
                int move = abs(head - tracks[i]);
                printf("%-15d %-15d %-20d\n",head,tracks[i],move);
                total_movement += move;
                head = tracks[i];
            }
        }
    float avg_seek_Time = (float)total_movement/(n-2);
    printf("Total tracks moved: %d\n", total_movement);
    printf("Average seek time: %.2f",avg_seek_Time);
}

int main(){
    SCAN();
    return 0;
}