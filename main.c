/*******************************************************************************************
* Programmer: Brevin Simon                                                                 *
* Class: CptS 122, Summer 2018; Lab Section 1L                                             *
* Programming Assignment: PA3                                                              *
* Date: June 25, 2018                                                                      *
* Description: Read music from .csv (excel) file then perform common ipod feature          *
*******************************************************************************************/
#include "header.h"
//main menu, (1) load, (2) store, (3) display, (6) edit, (8) rate, (9) play, and (11) exit features

int main(void) {
	FILE *infile = NULL;
	//infile = openFile("musicPlayList.csv", "r");
	Node *pNode = NULL, *pHead = NULL;
	srand(time(NULL));
	Record newSong = { "", "", "", "", 0, 0, 0, 0 };
	char lines[200][1000] = { { '\0', '\0' } };
	int holdCount = 0, menuOption = 0, flag = 0;
	while (menuOption != 11) {
		menuOption = mainMenu();
		switch (menuOption) {
		case 1:		//1. Load - Read from file and create linked list
			flag = 1;
			infile = openFile("musicPlayList.csv", "r");
			//Read the amount of lines that are being taken in
			holdCount = readFile(infile, lines);
			//Loop the new song returned from readPlayList and insert at
			//the front of the list
			for (int i = 0; i < holdCount; i++) {
				newSong = readPlaylist(lines, holdCount, i);
				insertAtFront(&pHead, newSong);
			}
			fclose(infile);
			break;
		case 2:		//2. Store - Output Linked List to file
			if (flag == 1) {
				//While data is loaded reload it into the file
				storeList("musicPlayList.csv", "w", pHead);
				fclose(infile);
			}
			else {
				printf("Cannot print without items in list!\n");
			}
			break;
		case 3:		//3. Display - Display ALL || By artist
			if (flag == 1) {
				printList(pHead);
			}
			else {
				printf("Cannot display without items in list!\n");
			}
			break;
		case 4:		//4. Insert - Add a song to list
			insertAtFront(&pHead, insertNewRecord());
			break;
		case 5:		//5. Delete - Re-connects the Linked List
			if (flag == 1) {
				delete(&pHead);
			}
			else {
				printf("Cannot delete song without items in list!\n");
			}
			break;
		case 6:		//6. Edit - Editsong function
			if (flag == 1) {
				editSong(pHead);
			}
			else {
				printf("Cannot edit song without items in list!\n");
			}
			break;
		case 7:		//7. Sort - Four Options
			if (flag == 1) {
				sortSongs(pHead);
			}
			else {
				printf("Cannot sort songs without items in list!\n");
			}
			break;
		case 8:		//8. Rate - Change rate between 1 - 5
			if (flag == 1) {
				changeRating(pHead);
			}
			else {
				printf("Cannot change ratings without items in list!\n");
			}
			break;
		case 9:		//9. Play song
			if (flag == 1) {
				playSong(pHead);
			}
			else {
				printf("Cannot play songs without items in list!\n");
			}
			break;
		case 10:	//10. Shuffle and play
			if (flag == 1) {
				shuffleSongs(&pHead, holdCount);
				playSong(pHead);
			}
			else {
				printf("Cannot shuffle songs without items in list!\n");
			}
			break;
		case 11:	//11. Exit - Stores list upon exiting
			storeList("musicPlayList.csv", "w", pHead);
			break;
		}
	}
	return 0;
}