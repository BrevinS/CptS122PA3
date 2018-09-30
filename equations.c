#include "header.h"

int mainMenu(void) {
	int userOption;
	printf("Main Menu:\n");
	printf("(1) - Load\n");
	printf("(2) - Store\n");
	printf("(3) - Display\n");
	printf("(4) - Insert\n");
	printf("(5) - Delete\n");
	printf("(6) - Edit\n");
	printf("(7) - Sort\n");
	printf("(8) - Rate\n");
	printf("(9) - Play\n");
	printf("(10) - Shuffle\n");
	printf("(11) - Exit\n");
	scanf("%d", &userOption);
	return userOption;
}

//Open File
FILE *openFile(char *filename, char *mode) {
	FILE *infile = NULL;
	infile = fopen(filename, mode);
	if (infile != NULL) // successfully opened the file
	{
		puts("Opened file successfully!\n");
	}
	else
	{
		puts("Error\n");
	}
	return infile;
}

void printList(Node *pHead)
{
	Node *pCur = pHead;
	int option = 0;
	char artist[100] = "\0";
	printf("Would you like to print all or print songs by artist? 1 for all or 0 for artist!\n");
	scanf("%d", &option);
	if (option == 1) {
		while (pCur != NULL)
		{
			printf("%s\n", pCur->data.artist);
			printf("%s\n", pCur->data.albumTitle);
			printf("%s\n", pCur->data.songTitle);
			printf("%s\n", pCur->data.genre);
			printf("%d:%d\n", pCur->data.songLength.minutes, pCur->data.songLength.seconds);
			printf("%d\n", pCur->data.timesPlayed);
			printf("%d\n", pCur->data.rating);
			pCur = pCur->pNext;
			putchar('\n');
		}
	}
	else if (option == 0) {
		printf("Enter the artist's name you would like to find songs for!\n");
		scanf("%s", &artist);
		while (pCur != NULL) {
			if (strcmp(artist, pCur->data.artist) == 0) {
				printf("%s\n", pCur->data.artist);
				printf("%s\n", pCur->data.albumTitle);
				printf("%s\n", pCur->data.songTitle);
				printf("%s\n", pCur->data.genre);
				printf("%d:%d\n", pCur->data.songLength.minutes, pCur->data.songLength.seconds);
				printf("%d\n", pCur->data.timesPlayed);
				printf("%d\n", pCur->data.rating);
				putchar('\n');
			}
			pCur = pCur->pNext;
		}
	}
}

//Create Node
Node *makeNode(Record item) {
	Node *pMem = NULL;
	pMem = (Node *)malloc(sizeof(Node));
	pMem->pNext = NULL;
	pMem->pLast = NULL;

	//Hold data
	strcpy(pMem->data.artist, item.artist);
	strcpy(pMem->data.albumTitle, item.albumTitle);
	strcpy(pMem->data.songTitle, item.songTitle);
	strcpy(pMem->data.genre, item.genre);
	pMem->data.songLength.seconds = item.songLength.seconds;
	pMem->data.songLength.minutes = item.songLength.minutes;
	pMem->data.timesPlayed = item.timesPlayed;
	pMem->data.rating = item.rating;

	return pMem;
}

int readFile(FILE *infile, char lines[][1000]) {
	int flag = 0, i = 0;
	char str[1000] = " ";
	//Base Case
	fgets(lines[i], 1000, infile);
	//printf("%s", lines[i]);
	//For all values not equal to 1440
	int check = -1;
	while (fgets(lines[i], 1000, infile))
	{
		++i;
		//printf("%s", lines[i]);
	}
	return i;
}

//Load song information
//Example Line: "Swift, Taylor",1989,Shake it Off,Pop,3:35,12,3
Record readPlaylist(char lines[][1000], int count, int increment) {
	char *nulpHold = NULL, *nulpHold2 = NULL;
	Record item = { "", "", "", "", 0, 0, 0, 0 };
	//{ "", "", "", "", 0, 0, 0, 0 }
	if (lines[increment][0] == '"') {
		nulpHold = strtok(lines[increment], " ");
		strcpy(item.artist, nulpHold);
		nulpHold = strtok(NULL, ",");
		strcat(item.artist, " ");
		strcat(item.artist, nulpHold);
	}
	else {
		nulpHold = strtok(lines[increment], ",");
		strcpy(item.artist, nulpHold);
	}
	//Album Title
	nulpHold = strtok(NULL, ",");
	strcpy(item.albumTitle, nulpHold);
	//Song Name
	nulpHold = strtok(NULL, ",");
	strcpy(item.songTitle, nulpHold);
	//Genre
	nulpHold = strtok(NULL, ",");
	strcpy(item.genre, nulpHold);
	//Time Minutes
	nulpHold = strtok(NULL, ":");
	item.songLength.minutes = atoi(nulpHold);
	//Time Seconds
	nulpHold = strtok(NULL, ",");
	item.songLength.seconds = atoi(nulpHold);
	//Times Played
	nulpHold = strtok(NULL, ",");
	item.timesPlayed = atoi(nulpHold);
	//Rating
	nulpHold = strtok(NULL, "\n");
	item.rating = atoi(nulpHold);

	return item;
}

//Store songs in the file
void storeList(char *filename, char *mode, Node *pHead) {
	Node *pCur = pHead;
	FILE *infile = NULL;
	infile = openFile(filename, mode);
	while (pCur != NULL) {
		fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.albumTitle, pCur->data.songTitle
			, pCur->data.genre, pCur->data.songLength.minutes, pCur->data.songLength.seconds
			, pCur->data.timesPlayed, pCur->data.rating);
		pCur = pCur->pNext;
	}
}

//Insert node in front of list
int insertAtFront(Node **pHead, Record item) {
	Node *pMem = makeNode(item);
	int success = 0;
	if (pMem != NULL) {
		success = 1;
		if (*pHead == NULL) {
			*pHead = pMem;
		}
		else {
			pMem->pNext = *pHead;
			(*pHead)->pLast = pMem;
			*pHead = pMem;
		}
	}
	return success;
}

//Record Edit Menu
int recordOptions(void) {
	int userOption;
	printf("Record Edit Options:\n");
	printf("[1] - Artist Name\n");
	printf("[2] - Album Title\n");
	printf("[3] - Song Title\n");
	printf("[4] - Song Genre\n");
	printf("[5] - Song Length (minutes)\n");
	printf("[6] - Song Length (seconds)\n");
	printf("[7] - Times Played\n");
	printf("[8] - Song Rating\n");
	printf("[9] - Exit (back)\n");
	scanf("%d", &userOption);
	return userOption;
}

Record insertNewRecord(void) {
	Record newRecord = { NULL };
	int holdRating = 0;
	printf("Please enter the artist's new name\n");
	scanf("%s", &newRecord.artist);
	printf("Please enter the new album name\n");
	scanf("%s", &newRecord.albumTitle);
	printf("Please enter the new song title\n");
	scanf("%s", &newRecord.songTitle);
	printf("Please enter the genre\n");
	scanf("%s", &newRecord.genre);
	printf("How many minutes does the song take up?\n");
	scanf("%d", &newRecord.songLength.minutes);
	printf("Excluding the minutes how many seconds remain?\n");
	scanf("%d", &newRecord.songLength.seconds);
	printf("How many times has this song been played?\n");
	scanf("%d", &newRecord.timesPlayed);
	printf("What is the rating of the song?\n");
	scanf("%d", &holdRating);
	if (holdRating >= 1 && holdRating <= 5) {
		newRecord.rating = holdRating;
	}
	else {
		printf("Not a valid rating! 1 - 5 only!\n");
	}
	return newRecord;
}

//Edit song using the menu print
Node *editSong(Node **pHead) {
	char str[1000];
	Node *pCur = pHead;
	int input = 0, menuOption = 0, rating = 0, timesPlayed = 0, timeSeconds = 0, timeMinutes = 0;
	printf("Name the artist of the song you want to edit. Warning: Case sensitive\n");
	scanf("%s", &str);
	//printf("%s", str);
	while (pCur != NULL) {
		if (strcmp(pCur->data.artist, str) == 0) {
			printf("Would you like to edit %s by %s? 1 for yes and 0 for no\n", pCur->data.songTitle
				, pCur->data.artist);
			scanf("%d", &input);
			if (input == 1) {
				//Edit Song
				while (menuOption != 9) {
					menuOption = recordOptions();
					switch (menuOption) {
						//Artist Name
					case 1:
						printf("Please enter the artist's new name\n");
						scanf("%s", &pCur->data.artist);
						break;
						//Artist Album
					case 2:
						printf("Please enter the new album name\n");
						scanf("%s", &pCur->data.albumTitle);
						break;
						//Song Title
					case 3:
						printf("Please enter the new song title\n");
						scanf("%s", &pCur->data.songTitle);
						break;
						//Song Genre
					case 4:
						printf("Please enter the new song genre\n");
						scanf("%s", &pCur->data.genre);
						break;
						//Song Length (minutes)
					case 5:
						printf("Please enter the new song length in minutes\n");
						scanf("%d", &timeMinutes);
						pCur->data.songLength.minutes = timeMinutes;
						break;
						//Song Length (seconds)
					case 6:
						printf("Please enter the seconds of the song\n");
						scanf("%d", &timeSeconds);
						pCur->data.songLength.seconds = timeSeconds;
						break;
						//Times Played
					case 7:
						printf("Please enter the new number of times played\n");
						scanf("%d", &timesPlayed);
						pCur->data.timesPlayed = timesPlayed;
						break;
						//Song Rating
					case 8:
						printf("Please enter the new song rating, must be between 1 and 5!\n");
						scanf("%d", &rating);
						if (rating >= 1 && rating <= 5) {
							pCur->data.rating = rating;
						}
						else {
							printf("The rating you entered was not between 1 and 5!\n");
						}
						break;
						//Exit
					case 9:
						break;
					}
				}
				return pCur;
			}
		}
		pCur = pCur->pNext;
	}
}

//Play song
void playSong(Node **pHead) {
	Node *pCur = pHead;
	int choice = 0;
	while (pCur != NULL) {
		system("cls");
		printf("Would you like to play the song %s by %s? 1 for yes or 0 for no\n", pCur->data.songTitle
			, pCur->data.artist);
		scanf("%d", &choice);
		if (choice == 1) {
			while (pCur != NULL) {
				system("cls");
				printf("%s\n", pCur->data.artist);
				printf("%s\n", pCur->data.albumTitle);
				printf("%s\n", pCur->data.songTitle);
				printf("%s\n", pCur->data.genre);
				printf("%d:%d\n", pCur->data.songLength.minutes, pCur->data.songLength.seconds);
				printf("%d\n", pCur->data.timesPlayed);
				printf("%d\n", pCur->data.rating);
				pCur = pCur->pNext;
				printf("Press any button for next song!\n");
				system("pause");
			}
		}
		else {
			pCur = pCur->pNext;
		}
	}
}

//Change rating, cannot 
void changeRating(Node **pHead) {
	Node *pCur = pHead;
	int input = 0, rating = 0;
	while (pCur != NULL) {
		printf("Would you like to change the rating for %s by %s? 1 for yes and 0 for no\n", pCur->data.songTitle
			, pCur->data.artist);
		//Change rating
		scanf("%d", &input);
		if (input == 1) {
			printf("What rating would you like to give the song? 1 - 5 Rating\n");
			scanf("%d", &rating);
			if (rating >= 1 && rating <= 5) {
				pCur->data.rating = rating;
			}
			else {
				printf("The rating you entered was not between 1 and 5!\n");
			}

		}
		pCur = pCur->pNext;
	}
}

void delete(Node **pHead) {
	Node *pCur = *pHead, *pTemp;
	char song[60] = { '\0' };
	printf("What song would you like to delete? Here: ");
	gets(song);
	gets(song);
	while (pCur != NULL && strcmp(pCur->data.songTitle, song) != 0) {
		pCur = pCur->pNext;
	}
	if (strcmp(pCur->data.songTitle, song) == 0) {
		pCur->pLast->pNext = pCur->pNext;
		pCur->pNext->pLast = pCur->pLast;
		free(pCur);
		printf("%s Was Successfully Deleted!\n", song);
	}
	else {
		printf("Item Was Not In List!\n");
	}
}

void sortSongs(Node *pHead) {
	int choice = 0;
	printf("Sort List Menu\n");
	printf("{1} - Sort Based On Artist A - Z\n");
	printf("{2} - Sort Based On Album Title A - Z\n");
	printf("{3} - Sort Based Rating Highest - Lowest\n");
	printf("{4} - Sort Based On Times Played Highest - Lowest\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		bubbleSortArtist(pHead);
		break;
	case 2:
		bubbleSortAlbumTitle(pHead);
		break;
	case 3:
		bubbleSortRating(pHead);
		break;
	case 4:
		bubbleSortTimesPlayed(pHead);
		break;
	}
}

//SOURCE FOR HELP https://www.geeksforgeeks.org/shuffle-a-given-array/
//THIS SOURCE HELPED SHUFFLE AN ARRAY BUT I CREATED THE SWAP FUNCTION
//AND IMPLEMENTED IT INTO LINKED LISTS
void shuffleSongs(Node **pHead, int holdCount)
{
	Node *pCur = *pHead;
	Node *pMem = *pHead;
	srand(time(NULL));
	for (int i = holdCount - 1; i > 0; i--)
	{
		pCur = *pHead;
		int j = rand() % (i + 1);
		while (j > 0 && pCur != NULL) {
			pCur = pCur->pNext;
			j--;
		}
		swap(pMem, pCur);
	}
}


//ALL BUBBLESORT FUNCTIONS FROM: 
//ANDYS CLASS NOTES FROM 121 &&
//https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
void bubbleSortRating(Node *pHead)
{
	int flip = 0;
	Node *pCur, *pHold = NULL;

	do
	{
		flip = 0;
		pCur = pHead;
		while (pCur->pNext != pHold)
		{
			if (pCur->data.rating > pCur->pNext->data.rating)
			{
				swap(pCur, pCur->pNext);
				flip = 1;
			}
			pCur = pCur->pNext;
		}
		pHold = pCur;
	} while (flip);
}

void bubbleSortTimesPlayed(Node *pHead)
{
	int flip = 0;
	Node *pCur, *pHold = NULL;

	do
	{
		flip = 0;
		pCur = pHead;
		while (pCur->pNext != pHold)
		{
			if (pCur->data.timesPlayed > pCur->pNext->data.timesPlayed)
			{
				swap(pCur, pCur->pNext);
				flip = 1;
			}
			pCur = pCur->pNext;
		}
		pHold = pCur;
	} while (flip);
}

void bubbleSortAlbumTitle(Node *pHead)
{
	int flip = 0;
	Node *pCur, *pHold = NULL;

	do
	{
		flip = 0;
		pCur = pHead;

		while (pCur->pNext != pHold)
		{
			if (strcmp(pCur->data.albumTitle, pCur->pNext->data.albumTitle) > 0)
			{
				swap(pCur, pCur->pNext);
				flip = 1;
			}
			pCur = pCur->pNext;
		}
		pHold = pCur;
	} while (flip);
}

void bubbleSortArtist(Node *pHead)
{
	int flip = 0;
	Node *pCur, *pHold = NULL;

	do
	{
		flip = 0;
		pCur = pHead;

		while (pCur->pNext != pHold)
		{
			if (strcmp(pCur->data.artist, pCur->pNext->data.artist) > 0)
			{
				swap(pCur, pCur->pNext);
				flip = 1;
			}
			pCur = pCur->pNext;
		}
		pHold = pCur;
	} while (flip);
}

void swap(Node *pFirst, Node *pAfter)
{
	Node *pTemp = (Node *)malloc(sizeof(Node));
	strcpy(pTemp->data.artist, pFirst->data.artist);
	strcpy(pTemp->data.albumTitle, pFirst->data.albumTitle);
	strcpy(pTemp->data.songTitle, pFirst->data.songTitle);
	strcpy(pTemp->data.genre, pFirst->data.genre);
	pTemp->data.songLength.seconds = pFirst->data.songLength.seconds;
	pTemp->data.songLength.minutes = pFirst->data.songLength.minutes;
	pTemp->data.timesPlayed = pFirst->data.timesPlayed;
	pTemp->data.rating = pFirst->data.rating;

	strcpy(pFirst->data.artist, pAfter->data.artist);
	strcpy(pFirst->data.albumTitle, pAfter->data.albumTitle);
	strcpy(pFirst->data.songTitle, pAfter->data.songTitle);
	strcpy(pFirst->data.genre, pAfter->data.genre);
	pFirst->data.songLength.seconds = pAfter->data.songLength.seconds;
	pFirst->data.songLength.minutes = pAfter->data.songLength.minutes;
	pFirst->data.timesPlayed = pAfter->data.timesPlayed;
	pFirst->data.rating = pAfter->data.rating;

	strcpy(pAfter->data.artist, pTemp->data.artist);
	strcpy(pAfter->data.albumTitle, pTemp->data.albumTitle);
	strcpy(pAfter->data.songTitle, pTemp->data.songTitle);
	strcpy(pAfter->data.genre, pTemp->data.genre);
	pAfter->data.songLength.seconds = pTemp->data.songLength.seconds;
	pAfter->data.songLength.minutes = pTemp->data.songLength.minutes;
	pAfter->data.timesPlayed = pTemp->data.timesPlayed;
	pAfter->data.rating = pTemp->data.rating;
}