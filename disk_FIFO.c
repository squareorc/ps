#include<stdio.h>
#include<stdlib.h>

void FIFO(){
    int disk_size, head, total_movement = 0;
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
    printf("-----FIFO DISK SCHEDULING-----\n");
    printf("%-15s %-15s %-20s\n", "FROM","TO","SEEK(TRACKS)");
    for(int i=0 ; i<n ; i++){
        int move = abs(tracks[i] - head);
        printf("%-15d %-15d %-20d\n", head,tracks[i],move);
        total_movement += move;
        head = tracks[i];
    }
    float avg_seek_time = (float)total_movement/n;
    printf("Total tracks moved: %d\n",total_movement);
    printf("Avg seek time : %.2f",avg_seek_time);
}

int main(){
    FIFO();
    return 0;
}