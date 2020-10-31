#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

struct _student;
typedef struct _student* Position; 

typedef struct _student {

	char ime[MAX], prezime[MAX];
	int godinaRodjenja;

	Position next;

}Student;

int printList(Position head);
Position createStudent(char* ime, char* prezime, int godinaRodjenja);
int insertBeg(Position what, Position where);
int insertEnd(Position what, Position where);
Position findElement(char* prezime, Position where);
int deleteElement(char* ime, char* prezime, Position where);
Position findPrev(char* prezime, Position where);

int main(void)
{
	Student head; 
	head.next = NULL;
	Position what;


	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	//int godinaRodjenja = 0;
	char kraj;

	printf("UNOS STUDENATA - unesite 0 ako zelite izaći iz unosa studenata\n");
	while (1) {

	/*	printf("Insert first name:\r\n");
		scanf(" %s", ime);
		if (ime[0] == '0')
			break;

		printf("Insert last name:\r\n");
		scanf(" %s", prezime);

		printf("Insert birth year:\r\n");
		scanf("%d", &godinaRodjenja);
		*/
		what = createStudent(); // Dobili smo ono sta zelimo unijeti u listu
		//insertBeg(what, &head); 
		insertEnd(what, &head); 
		printList(&head);
	}

	// Pronadi Studenta
	printf("Unesi prezime studenta kojeg trazite: \n");
	scanf(" %s", prezime);
	printf("Adresa zeljenog studenta je: %d\n", findElement(prezime, &head));

	//Pronadi prethodnog studenta
	printf("Adresa studenta prije je: %d\n", findPrev(prezime, &head));
	
	//Brisanje nekog studenta
	printf("Unesi prezime studenta kojeg zelite izbrisati: \n");
	scanf(" %s", prezime);
	deleteElement(ime, prezime, &head);
	
	//Ispis studenata nakon brisanja
	printList(&head);

	return 0;
}

Position createStudent() {  // POSITION NAM JE SAMO TIP VARIJABLE!!!
																		//Ova funkcija samo sluzi za unos u strukturu, a ne u LISTU!!!!
	Position student = NULL;
	student = (Position)malloc(sizeof(Student));

	if (NULL == student) { // ili if(!student);
		printf("Allocation failed\r\n");
		return NULL;
	}

	printf("Insert first name:\r\n");
	scanf(" %s", student->ime);

	printf("Insert last name:\r\n");
	scanf(" %s", student->prezime);

	printf("Insert birth year:\r\n");
	scanf("%d", &student->godinaRodjenja);

	//strcpy(student->ime, ime);
	//strcpy(student->prezime, prezime);
	//student->godinaRodjenja = godinaRodjenja;

	student->next = NULL;

	return student;
}

int printList(Position head) {
	Position p = NULL;
	p = head->next; // OVO JE KLJUČNO!

	printf("\nList contains:\r\n");

	while (p != NULL) {
		printf("%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
		p = p->next;
	}

	printf("\r\n\r\n");
	return 0;
}

int insertBeg(Position what, Position where) { //Funkcija koja unosi neki element nakon nekog drugoga!!!
	what->next = where->next; // Skicirat na papir pa će biti lakše za skužiti!
	where->next = what;
	return 0;
}

int insertEnd(Position what, Position where) { // Funkcija koja postavlja neki element na zadnje misto u nizu!!!
	while (where->next != NULL) {
		where = where->next;
	}

	where->next = what;   //what->next=where->next - mislim da ovo dode na isto
	what->next = NULL;	// where->next=what
	return 0;
}

Position findElement(char* prezime, Position where) {
	while (where != NULL && strcmp(where->prezime, prezime))
		where = where->next;
	return where;
}

Position findPrev(char* prezime, Position where) {

	Position Prev = NULL;
	Prev = where;
	where = where->next;

	while (where != NULL && strcmp(where->prezime, prezime))
	{
		Prev = where;
		where = where->next; // Trazimo član čiji prethodnik zelimo naci, kad ga nademo stopamo!
	}

	return Prev;
}

int deleteElement(char* ime, char* prezime, Position where) {

	Position prev = NULL;

	prev = findPrev(prezime, where);
	if (prev->next != NULL)
	{
		where = prev->next;
		prev->next = where->next;
		free(where);
	}
	return 0;
}
