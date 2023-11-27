/***********************************************
*
* @Proposito:  LSClassrooms
* @Autor/es: Daniela Amato Arrieta
* @Fecha creacion: 10/04/2022
* @Fecha ultima modificacion: 20/04/2022
*
************************************************/

#include <stdio.h>                                                                                                                                                  //librerias y constantes
#include <stdlib.h>
#include <string.h>
#define MAXSTR 20
#define MAX_STRING_LENGTH 70

typedef struct {
	char name[MAX_STRING_LENGTH];
	char login[MAX_STRING_LENGTH];
}Student;

typedef struct {
	char name[MAX_STRING_LENGTH];
	int max_capacity;
	int current_capacity;
	Student *students;
}Classroom;

typedef struct {
	char name[MAX_STRING_LENGTH];
	int num_classrooms;
	Classroom *classrooms;
}Degree;

typedef struct {
	int num_degrees;
	Degree *elements;
}Degrees;

/***********************************************
*
* @Finalidad: leer info estudiantes
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: ok (lectura correcta)
*
************************************************/

int llenaMemo (Degrees *degrees) {
	int ok, i = 0, j = 0, k, h = 0;                                                                                                                                 //contadores
	FILE *g;
	char login_aux[MAX_STRING_LENGTH], filename2[MAX_STRING_LENGTH], basura, stud_nameaux[MAX_STRING_LENGTH], aux[MAX_STRING_LENGTH], aux2[MAX_STRING_LENGTH];      //variables auxiliares
	
	do {
		printf ("\nType the name of the 'students' file: ");
		scanf ("%s", filename2);
		scanf ("%c", &basura);

		g = fopen (filename2, "r");

		if (g == NULL) {                                                                                                                                            //condicional que comprueba apertura de fichero
			printf ("\nERROR: Can't open file '%s'\n", filename2);
		}
		else {
			fscanf (g, "%s", aux);
			while (!feof (g)) {                                                                                                                                     //bucle hasta final de fichero
				i = 0;
				j = 0;
				while (aux[i] != ',') {                                                                                                                             //bucle que controla lectura del nombre del estudiante
					stud_nameaux[j] = aux[i];
					i++;
					j++;
				}
				stud_nameaux[j] = '\0'; 
				fscanf (g, "%c", &basura);
				fgets (aux2, MAX_STRING_LENGTH, g);
				aux2[strlen (aux2) - 1] = '\0';
				fgets (login_aux, MAX_STRING_LENGTH, g);
				if (login_aux[strlen (login_aux) - 1] == '\n') {                                                                                                    //condicional que controla lectura del login del estudiante
					login_aux[strlen (login_aux) - 1] = '\0';
				}
			
				for (k = 0; k < degrees->num_degrees; k++) {                                                                                                        //bucle que recorre cantidad de grados
					h = 0	;
					if (strcmp (degrees->elements[k].name, aux2) == 0) {                                                                                            //condicional que comprueba existencia de grado
						if (degrees->elements[k].classrooms[h].current_capacity < degrees->elements[k].classrooms[h].max_capacity) {                                //condicional que verifica la capacidad de la clase
							strcpy (degrees->elements[k].classrooms[h].students[degrees->elements[k].classrooms[h].current_capacity].name, stud_nameaux);
							strcpy (degrees->elements[k].classrooms[h].students[degrees->elements[k].classrooms[h].current_capacity].login, login_aux);
							degrees->elements[k].classrooms[h].current_capacity++;
						}
						else {
							h++;
							strcpy (degrees->elements[k].classrooms[h].students[degrees->elements[k].classrooms[h].current_capacity].name, stud_nameaux);
							strcpy (degrees->elements[k].classrooms[h].students[degrees->elements[k].classrooms[h].current_capacity].login, login_aux);
							degrees->elements[k].classrooms[h].current_capacity++;
						}
					}
				}
				fscanf (g, "%s", aux);
			}
			ok = 1;
			fclose(g);
		}
	}while (g == NULL);                                                                                                                                             //bucle que comprueba existencia de fichero

	return ok;
}

/***********************************************
*
* @Finalidad: pedir memoria
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: ok (lectura correcta)
*
************************************************/

int pideMemo (Degrees *degrees) {
	char filename1[MAXSTR];                                                                                                                                         //variable fichero 
	char basura;                                                                                                                                                    //variable basura                                                              
	int ok, i, j;                                                                                                                                                   //contadores y flag
	FILE *f;                                                                                                                                                        //fichero

	do {
		printf ("Type the name of the 'classrooms' file: ");
		scanf ("%s", filename1);
		scanf ("%c", &basura);

		f = fopen (filename1, "r");

		if (f == NULL) {                                                                                                                                            //condicional que comprueba apertura del fichero
			printf ("\nERROR: Can't open file '%s'\n\n", filename1);
		}
		else {
			fscanf (f, "%d", &degrees->num_degrees);
			fscanf (f, "%c", &basura);
			degrees->elements = (Degree *) malloc (sizeof (Degree) * degrees->num_degrees);
			if (degrees->elements == NULL) {                                                                                                                        //condicional que comprueba memoria disponible
				printf ("Error\n");
			}
			else {
				for (i = 0; i < degrees->num_degrees; i++) {                                                                                                        //bucle que recorre numero de grados
					fscanf (f, "%d", &degrees->elements[i].num_classrooms);
					fscanf (f, "%c", &basura);
					fgets (degrees->elements[i].name, MAX_STRING_LENGTH, f);
					degrees->elements[i].name[strlen (degrees->elements[i].name) - 1] = '\0';
					degrees->elements[i].classrooms = (Classroom *) malloc (sizeof (Classroom) * degrees->elements[i].num_classrooms);

					if (degrees->elements[i].classrooms == NULL) {                                                                                                  //condicional que comprueba memoria disponible
						printf ("Error\n");
					}
					else {

						for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                 //bucle que recorre numero de clases
							fscanf (f, "%s", degrees->elements[i].classrooms[j].name);
							fscanf (f, "%c", &basura);
							fscanf (f, "%d", &degrees->elements[i].classrooms[j].max_capacity);
							degrees->elements[i].classrooms[j].current_capacity = 0;
							degrees->elements[i].classrooms[j].students = (Student *) malloc (sizeof (Student) * degrees->elements[i].classrooms[j].max_capacity);
						}
					}
				}
			}
			fclose (f);
		}
	} while (f == NULL);                                                                                                                                            //bucle que comprueba existencia de fichero

	ok = llenaMemo (degrees);	
	
	return ok;
}

/***********************************************
*
* @Finalidad: display menu
* @Parametros: 
* @Retorno: opcion escogida
*
************************************************/

int displayMenu () {
	int opcion;                                                                                                                                                     //entero de opcion
	char basura;                                                                                                                                                    //variable basura

	do {                                                                                                                                                            //bucle que repite el menu
		printf ("\n1. Summary | 2. Show degree students | 3. Move student | 4. Exit\n");
		printf ("Select option: ");
		scanf ("%d", &opcion);
		scanf ("%c", &basura);

		if (opcion < 1 || opcion > 4) {                                                                                                                             //condicional que controla la opcion
			printf ("\nERROR: Wrong option number\n");
		}
	} while (opcion < 1 || opcion > 4);

	return opcion;
}

/***********************************************
*
* @Finalidad: mostrar info clases
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: 
*
************************************************/

void showSummary (Degrees *degrees) {
	int i, j;                                                                                                                                                       //contadores

	for (i = 0; i < degrees->num_degrees; i++) {                                                                                                                    //bucle que recorre numero de grados
		printf ("\n%s\n", degrees->elements[i].name);
		for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                                 //bucle que recorre numero de clases
			printf ("%s %d/%d\n", degrees->elements[i].classrooms[j].name, degrees->elements[i].classrooms[j].current_capacity, degrees->elements[i].classrooms[j].max_capacity);
		}
	}
}

/***********************************************
*
* @Finalidad: mostrar info estudiantes
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: 
*
************************************************/

void showStudent (Degrees *degrees) {
	int i, j, h, flag = 0;                                                                                                                                          //contadores y flags
	char degree[MAX_STRING_LENGTH];                                                                                                                                 //variable degree introducido

	printf ("\nDegree to show? ");
	fgets (degree, MAX_STRING_LENGTH, stdin);
	degree[strlen (degree) - 1] = '\0';
	printf ("\n");

	for (i = 0; i < degrees->num_degrees; i++) {                                                                                                                    //bucle que recorre numero de grados
		if (strcmp (degrees->elements[i].name, degree) == 0) {                                                                                                      //condicional que comprueba existencia de grado introducido
			flag = 1;
			for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                             //bucle que recorre numero de clases
				for (h = 0; h < degrees->elements[i].classrooms[j].current_capacity; h++) {                                                                         //bucle que recorre capacidad actual
					if (h < degrees->elements[i].classrooms[j].current_capacity) {                                                                                  //condicional que compruebe existencia de estudiantes
						printf ("%s (%s): %s\n", degrees->elements[i].classrooms[j].students[h].name, degrees->elements[i].classrooms[j].students[h].login, degrees->elements[i].classrooms[j].name);
					}
				}
			}
		}
	}

	if (flag == 0) {                                                                                                                                                //condicional que muestra error
		printf ("ERROR: Can't find degree\n");
	}
}

/***********************************************
*
* @Finalidad: trasladar estudiantes de clase
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: 
*
************************************************/

void moveStudent (Degrees *degrees) {
	int i, j, k = 1, y, flag = 0, flag2 = 1, class;                                                                                                                 //contadores y flags
	char degree[MAX_STRING_LENGTH], student[MAX_STRING_LENGTH];                                                                                                     //variables introducidas
	char basura;                                                                                                                                                    //variable basura

	printf ("\nDegree? ");
	fgets (degree, MAX_STRING_LENGTH, stdin);
	degree[strlen (degree) - 1] = '\0';

	for (i = 0; i < degrees->num_degrees; i++) {                                                                                                                    //bucle que recorre numero de grados
		if (strcmp (degrees->elements[i].name, degree) == 0) {                                                                                                      //condicional que comprueba existencia de grado
			flag = 1;
			printf ("\nClassrooms and capacity:\n");
			for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                             //bucle que recorre numero de clases
				printf ("%d. %s %d/%d\n", k, degrees->elements[i].classrooms[j].name, degrees->elements[i].classrooms[j].current_capacity, degrees->elements[i].classrooms[j].max_capacity);
				for (y = 0; y < degrees->elements[i].classrooms[j].current_capacity; y++){                                                                          //bucle que recorre capacidad actual
					printf ("%s\n", degrees->elements[i].classrooms[j].students[y].login);

				}
				k++;
			}
			flag2 = 0;
			printf ("\nWho do you want to move (login)? ");
			fgets (student, MAX_STRING_LENGTH, stdin);
			student[strlen (student) - 1] = '\0';

			for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                             //bucle que recorre numero de clases
				for (y = 0; y < degrees->elements[i].classrooms[j].current_capacity; y++) {                                                                         //bucle que recorre capacidad actual
					if (strcmp (degrees->elements[i].classrooms[j].students[y].login, student) == 0 && flag2 == 0) {                                                //condicional que controla existencia de estudiante y error
						flag2 = 1;
						printf ("\nTo which classroom (index)? ");
						scanf ("%d", &class);
						scanf ("%c", &basura);
						
						if (class > degrees->elements[i].num_classrooms || class == 0 || class < 0) {                                                               //condicional que controla error
							printf ("\nERROR: Can't move student\n");		
						}
						else {
							if (j + 1 == class) {                                                                                                                   //condicional que controla error
								printf ("\nERROR: Can't move student\n");		
							}
							else {
								class--;
								if (degrees->elements[i].classrooms[class].current_capacity < degrees->elements[i].classrooms[class].max_capacity) {                //condicional que controla error
									strcpy (degrees->elements[i].classrooms[class].students[degrees->elements[i].classrooms[class].current_capacity].name, degrees->elements[i].classrooms[j].students[y].name);
									strcpy (degrees->elements[i].classrooms[class].students[degrees->elements[i].classrooms[class].current_capacity].login, degrees->elements[i].classrooms[j].students[y].login);
									degrees->elements[i].classrooms[class].current_capacity++;
									degrees->elements[i].classrooms[j].current_capacity--;
								}
								else {
									printf ("\nERROR: Can't move student\n");		
								}
							}
						}
					}
				}
			}
		}
	}

	if (flag == 0) {                                                                                                                                                //condicional que muestra el error
		printf ("\nERROR: Can't move student\n");
	}

	if (flag2 == 0) {                                                                                                                                              //condicional que muestra el error
		printf ("\nERROR: Can't move student\n");
	}
}

/***********************************************
*
* @Finalidad: liberar memoria
* @Parametros: in/out: degrees (puntero con toda la info)
* @Retorno: 
*
************************************************/

void freeMemo (Degrees *degrees) {
	int i, j;                                                                                                                                                      //contadores

	for (i = 0; i < degrees->num_degrees; i++) {                                                                                                                   //bucle que recorre numero de grados
		for (j = 0; j < degrees->elements[i].num_classrooms; j++) {                                                                                                //bucle que recorre numero de clases
			free (degrees->elements[i].classrooms[j].students);
		}
		free (degrees->elements[i].classrooms);
	}

	free (degrees->elements);
}

int main () {
	Degrees degrees;                                                                                                                                                //variable tipo
	int ok, opcion;                                                                                                                                                 //flag y opcion menu

	printf ("Welcome!\n\n");

	ok = pideMemo (&degrees);

	if (ok == 1) {                                                                                                                                                  //condicional para la opcion del menu
		do {
			opcion = displayMenu ();

			if (opcion == 1) {
				showSummary (&degrees);
			}

			if (opcion == 2) {
				showStudent (&degrees);
			}

			if (opcion == 3) {
				moveStudent (&degrees);
			}
		} while (opcion != 4);                                                                                                                                      //bucle que repite el menu
	}

	if (opcion == 4) {                                                                                                                                              //condicional para cerrar el programa y liberar memoria
		freeMemo (&degrees);
		printf ("\nBye!\n");
	}

	return 0;
}
