#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

typedef enum boolean
{
	FALSE, TRUE
} Boolean;

typedef struct duration
{
	int seconds;
	int minutes;
} Duration;

typedef struct record
{
	char artist[90];
	char albumTitle[90];
	char songTitle[90];
	char genre[90];
	Duration songLength;
	int timesPlayed;
	int rating;
} Record;

typedef struct node
{
	Record data;
	struct node *pNext; //Point to next node
	struct node *pLast; //Point to last node
} Node;

int mainMenu(void);

FILE *openFile(char *filename, char *mode);

void storeList(char *filename, char *mode, Node *pHead);

Node *makeNode(Record data);

int readFile(FILE *infile, char lines[][1000]);

int insertAtFront(Node **pHead, Record item);

Record readPlaylist(char lines[][1000], int count, int increment);

Node *editSong(Node **pHead);

int recordOptions(void);

void playSong(Node **pHead);

void changeRating(Node **pHead);

Record insertNewRecord(void);

void delete(Node **pHead);

void sortSongs(Node *pHead);

void bubbleSortRating(Node *pHead);

void bubbleSortTimesPlayed(Node *pHead);

void bubbleSortAlbumTitle(Node *pHead);

void bubbleSortArtist(Node *pHead);

void swap(Node *pFirst, Node *pAfter);

void shuffleSongs(Node **pHead, int holdCount);