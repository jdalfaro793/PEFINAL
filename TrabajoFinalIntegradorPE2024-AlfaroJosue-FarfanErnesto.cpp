#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cctype>

using namespace std;

// Declaracion de constantes
const int MAX_Nombre = 10;
const int MAX_Continentes = 5;
const int MAX_Proyectos = 3;
const int MAX_Participante = 1000; 			//PARTICIPANTES
const int MAX_Jurados = 6; 					//JURADOS
const int MAX_Finalistas = 5; 				//FINALISTAS

// Declaracion de cadenas
typedef char tcad[30];
typedef tcad v_nombres[MAX_Nombre];
typedef tcad v_continentes[MAX_Continentes];  	//AFRICA, AMERICA, ASIA, EUROPA, OCEANIA
typedef int v_proyectos[MAX_Proyectos]; // 0: finalizados , 1: ejecucion , 2: liderados (finalizados + ejecucion)

// Declaracion de registros
typedef struct t_jurado
{
    int ID_jurado;
    tcad apellido;
    tcad nombre;
    tcad empresa;
    tcad cargo;
    int anios_indst;
};

typedef struct nota_jurado_primera_etapa
{
    int ID_jurado;
    tcad apellido_jurado;
    tcad nombre_jurado;

    int nota_vestuario;
    int nota_elegancia;
    int nota_elocuencia;
    float nota_idiomas;
};

typedef nota_jurado_primera_etapa v_notas_jurado[MAX_Jurados]; //notas jurado individual 1er etapa

typedef struct primera_etapa
{
    v_notas_jurado notas_jurado;
    float suma_nota_vestuario;
    float suma_nota_elegancia;
    float suma_nota_elocuencia;
    float suma_nota_idiomas;
    float puntaje_total;
};

typedef struct segunda_etapa
{
    int lenguajes_pro;
    int experiencia;
    int proyectos_finalizados;
    int proyectos_en_ejecucion;
    float proyectos_liderados;
    float suma_total;
};

typedef struct t_participante
{
    int id;
    tcad apellido;
    tcad primer_nombre;
    tcad segundo_nombre;
    int edad;
    float altura;
    int cant_idiomas;
    tcad continente;
    int cant_lenguajes_prog;
    int anios_experiencia;
    v_proyectos proyectos;

    primera_etapa etapa1;
    segunda_etapa etapa2;
    float puntaje_Coronacion;
};

typedef t_jurado v_jurados[MAX_Jurados]; 					//jurados
typedef t_participante v_participantes[MAX_Participante];	//participantes
typedef t_participante v_finalistas[MAX_Finalistas];		//finalistas

//--------------------------------------------------------------------------------------------
//CONTINENTES
bool buscar_continente(v_continentes conts, tcad conti, int ocup_continente);
//--------------------------------------------------------------------------------------------
//JURADOS
void Cargar_Jurados(v_jurados v, int ocup, t_jurado &jurado);
bool existe_apellido_nombre_jurado(v_jurados v, int ocup, tcad apell, tcad nombre);
void Agregar_Jurados(v_jurados &v, int &ocup);//MOSTRAR
void Mostrar_Jurados(v_jurados vec, int ocup);
void Lista_recursivo(v_jurados vec, int ocup);
void Borrar(v_jurados &vec, int &ocup, tcad borrar);
int Busqueda_Binaria_Recursiva_JURADO(v_jurados vec, int bajo, int alto, int buscado);
void cambio_Jurados(t_jurado  &x, t_jurado  &y);
void modificar_jurado(v_jurados  &vec, int ocup, int id_buscado);
//-------------------------------------------------------------------------------------------------------------------
//PARTICIPANTES
void insertar_participante(v_participantes &parts, int &ocup, t_participante nuevo);
void eliminar_participante(v_participantes &vec, int &ocup, int id);
void consultar_participante(v_participantes v, int ocup, int id, int tipo_consulta);
void modificar_participante(v_participantes &vec, int ocup_parts, int id, v_continentes conts, int ocup_conts);
void cargar_participante_manual(t_participante &p, v_continentes continentes, int ocup_continente);
void cargar_participante_auto(t_participante &p, v_continentes continentes, int ocup_continente);
void listar_participantes_rec(v_participantes parts, int ocup);
void imprimirParticipante(t_participante p);
void orden_sacudida_participante_ID(v_participantes &vconti, int ocup);
void shell_apell_nombres(v_participantes &parts, int ocup);

bool buscar_participante_by_nombre_apellido(v_participantes &listaAuxiliar, int ocup, t_participante buscado);
void buscar_participante_bin_by_id(v_participantes parts, int bajo, int alto, int id_buscado, int &posicion);

void generar_participantes_automaticos(int &id_participante, int total_cargados, v_participantes &parts, v_continentes continentes, int ocup_continentes, int &ocup, t_participante &nuevo);
void generar_participantes_manual(int &id_participante, v_participantes &parts, v_continentes continentes, int ocup_continentes, int &ocup, t_participante &nuevo);
void control_continentes(v_participantes parts, v_continentes continentes, int ocup_parts, int &vAfrica, int &vAmerica, int &vAsia, int &vEuropa, int &vOceania, bool &control_participante);

void copiar_participantes(v_participantes parts, v_participantes &copia, int ocup);
void cambio_participante(t_participante &x, t_participante &y);
//-------------------------------------------------------------------------------------------------------------------
//PRIMERA ETAPA
void pertenece_continente(v_participantes list_part, int ocup_part, v_participantes &vconti, int &ocup_conti, tcad c);
void Ordenacion_Continentes(v_participantes &lista_auxiliar, int ocup_auxiliar, v_participantes &seleccionadas, int &ocup_seleccionadas);
void Insercion_primera(v_participantes &vconti, int ocup);
void clasificar_participantes(v_continentes continentes, v_participantes &participantes, int ocup_participantes, v_jurados jurados, int ocup_jurados, v_participantes &seleccionadas, int &ocup_seleccionadas);
void mostrar_Participante_etapa1(t_participante p);

//--------------------------------------------------------------------------------------------
//SEGUNDA ETAPA
void Evaluacion_2da_ETAPA(v_participantes &listaPriEtapa, int ocup_selec);
void Insercion_segunda(v_participantes &v, int ocup);
void mostrar_Participante_etapa2(t_participante p);
//--------------------
//CORONACION
void evaluacion_Coronacion(v_participantes &listaPriEtapa, int ocup_selec, v_finalistas &listaFinalistas, int &ocup_Finalistas);
void Insercion_coronacion(v_participantes &v, int ocup);
void mostrar_Participante_Coronacion(t_participante p);

void guardar_finalistas(v_participantes &lista_2da_etapa, int ocup_2da_etapa, v_finalistas &finalistas, int &ocup_finalistas);
void mostrar_finalistas(v_finalistas finalistas, int &ocup_finalistas);

// utiles
int aleatorio(int inf, int sup);
void mayuscula(tcad &cadena);
bool verificacion_cadena(tcad cadena); //verifica si la cadena tiene todo letras o no

// GESTION DEL SISTEMA
void administracion_participantes(v_continentes continentes, v_participantes &parts, int &ocup, int &id_participante, int &vAfrica, int &vAmerica, int &vAsia, int &vEuropa, int &vOceania, bool &control_participante);
void administracion_jurados(v_jurados &jurados, int &ocupado_ju, bool &control_jurados, int &id_jurado_base);
void administracion_etapa_1(v_continentes continentes, v_participantes &participantes, int ocup_participantes, int vAfrica, int vAmerica, int vAsia, int vEuropa, int vOceania, v_jurados jurados, int ocup_jurados, bool control_jurados, bool control_participante, v_participantes &seleccionadas, int &ocup_seleccionadas, bool &ctr_1erEtapa);
void administracion_etapa_2(v_participantes &participantes, int ocup_participantes, bool ctr_1erEtapa, bool &ctr_2daEtapa);
void administracion_coronacion(v_participantes &participantes, int ocup_participantes, v_finalistas &finalistas, int &ocup_finalistas, bool ctrCoronacion);

// MENUS PRINCIPALES
void menu_principal(char &opcion);
void menu_gestion_participantes(int &opc);
void menu_gestion_jurados(int &opc);
void menu_primera_etapa(int &opc);
void menu_segunda_etapa(int &opc);
void menu_coronacion(int &opc);

main()
{
    srand(time(NULL));
    char op;
    v_continentes continentes = {"AFRICA", "AMERICA", "ASIA", "EUROPA", "OCEANIA"};

    //PARTICIPANTES
    int vAfrica = 0, vAmerica = 0, vAsia = 0, vEuropa = 0, vOceania = 0; 	//contadores para participantes por continentes; 4 participantes por continentes son necesarios para 1er etapa
    bool control_participante = false; //bandera de participantes necesarios para primera etapa (EVALUA QUE HAYAN 30 PARTICIPANTES COMO MINIMO)
    v_participantes participantes; //vector
    int ocup_participantes = -1;
    int id_participante_base = 1000;

    //JURADOS
    v_jurados jurados; //vector
    int ocupado_ju = -1;
    bool control_jurados = false; //bandera de jurado necesarios para primera etapa (EVALUA QUE HAYAN 3 JURADOS MINIMO)
    int id_jurado_base = 8000;

    //ETAPA 1
    v_participantes seleccionadas_et1;
    int ocup_seleccionadas_et1 = -1; //contiene las 4 mejores de cada continente -> mejores 20
    bool control_etapa1 = false; 	//luego de realizar clasificacion etapa 1

    //ETAPA 2
    bool control_etapa2 = false; 	//luego de realizar clasificacion etapa 2

    //CORONACION
    v_finalistas finalistas;
    int ocup_finalistas = -1;

    do
    {
        system("cls");
        menu_principal(op);
        switch (op)
        {
        case '1':
            administracion_participantes(continentes, participantes, ocup_participantes, id_participante_base,  vAfrica, vAmerica, vAsia, vEuropa, vOceania, control_participante);
            break;
        case '2':
            administracion_jurados(jurados, ocupado_ju, control_jurados, id_jurado_base);
            break;
        case '3':
            administracion_etapa_1(continentes, participantes, ocup_participantes, vAfrica, vAmerica, vAsia, vEuropa, vOceania, jurados, ocupado_ju, control_jurados, control_participante,
                                   seleccionadas_et1, ocup_seleccionadas_et1, control_etapa1);
            break;
        case '4':
            administracion_etapa_2(seleccionadas_et1, ocup_seleccionadas_et1, control_etapa1, control_etapa2);
            break;
        case '5':
            administracion_coronacion(seleccionadas_et1, ocup_seleccionadas_et1, finalistas, ocup_finalistas, control_etapa2);
            break;
        case '6':
            cout << "\n- Fin del programa -" << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
        }
        system("pause");
    }
    while (op != '6');
}

//----------->>MENUS<<-------------
void menu_principal(char &opcion)
{
    cout << "**********************************************\n";
    cout << "* SISTEMA DE CONCURSO MISS PROGRAMACION 2024 *\n";
    cout << "******************************************** *\n";
    cout << "*                                            *\n";
    cout << "*  1. Gestión de participantes               *\n";
    cout << "*  2. Gestión de Jurados                     *\n";
    cout << "*  3. Primera Etapa                          *\n";
    cout << "*  4. Segunda Etapa                          *\n";
    cout << "*  5. Coronación                             *\n";
    cout << "*  6. Salir                                  *\n";
    cout << "*                                            *\n";
    cout << "**********************************************\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
}

void menu_gestion_participantes(int &opc)
{
    cout << "----------------------------------------------\n";
    cout << "*   1. Gestión de Participantes              *\n";
    cout << "----------------------------------------------\n";
    cout << "*                                            *\n";
    cout << "*  1. Registro de participantes              *\n";
    cout << "*  2. Consultar participante                 *\n";
    cout << "*  3. Modificar participante                 *\n";
    cout << "*  4. Eliminar participante                  *\n";
    cout << "*  5. Listar participantes                   *\n";
    cout << "*  6. Volver a Menú Principal                *\n";
    cout << "*                                            *\n";
    cout << "----------------------------------------------\n";
    cout << "Seleccione una opcion: ";
    cin >> opc;
}

void menu_gestion_jurados(int &opc)
{
    cout << "----------------------------------------------\n";
    cout << "*   2. Gestión de Jurados                    *\n";
    cout << "----------------------------------------------\n";
    cout << "*                                            *\n";
    cout << "*   1. Registrar Jurados                     *\n";
    cout << "*   2. Consultar Jurado                      *\n";
    cout << "*   3. Modificar Jurado                      *\n";
    cout << "*   4. Eliminar Jurado                       *\n";
    cout << "*   5. Listar Jurados                        *\n";
    cout << "*   6. Volver a Menú Principal               *\n";
    cout << "*                                            *\n";
    cout << "----------------------------------------------\n";
    cout << "Seleccione una opcion: ";
    cin >> opc;
}

void menu_primera_etapa(int &opc)
{
    cout << "----------------------------------------------\n";
    cout << "*   3. Primera Etapa                         *\n";
    cout << "----------------------------------------------\n";
    cout << "*                                            *\n";
    cout << "*   1. Puntuar las 20 mejores                *\n";
    cout << "*   2. Consultar un puntaje                  *\n";
    cout << "*   3. Volver a Menú Principal               *\n";
    cout << "*                                            *\n";
    cout << "----------------------------------------------\n";
    cout << "Seleccione una opcion: ";
    cin >> opc;
}
void menu_segunda_etapa(int &opc)
{
    cout << "----------------------------------------------\n";
    cout << "*   4. Segunda Etapa                         *\n";
    cout << "----------------------------------------------\n";
    cout << "*                                            *\n";
    cout << "*   1. Puntuar las 20 mejores                *\n";
    cout << "*   2. Consultar un puntaje                  *\n";
    cout << "*   3. Volver a Menú Principal               *\n";
    cout << "*                                            *\n";
    cout << "----------------------------------------------\n";
    cout << "Seleccione una opcion: ";
    cin >> opc;
}

void menu_coronacion(int &opc)
{
    cout << "----------------------------------------------\n";
    cout << "*   5. ¡ CORONACION !                        *\n";
    cout << "----------------------------------------------\n";
    cout << "*                                            *\n";
    cout << "*   1. Realizar la coronacion                *\n";
    cout << "*   2. Mostrar Finalistas                    *\n";
    cout << "*   3. Volver a Menú Principal               *\n";
    cout << "*                                            *\n";
    cout << "*                                            *\n";
    cout << "----------------------------------------------\n";
    cout << "Seleccione una opcion: ";
    cin >> opc;
}

//MODULOS UTILES
int aleatorio(int inf, int sup)
{
    return rand() % (sup - inf + 1) + inf;
}

void mayuscula(tcad &cadena)
{
    int i;
    for (i = 0; i < strlen(cadena); i++)
    {
        cadena[i] = toupper(cadena[i]);
    }
}
bool verificacion_cadena(tcad cadena)  //verifica si la cadena tiene todo letras o no
{
    int longitud, i;
    bool band = true;

    longitud = strlen(cadena);

    for(i = 0; i < longitud && band == true; i++)
    {
        band =	((cadena[i] >= 'a' && cadena[i] <= 'z') ||
                 (cadena[i] >= 'A' && cadena[i] <= 'Z') ||
                 cadena[i] == ' ');
    }

    return band;
}

//------------------------------------------------------------------------------
bool buscar_continente(v_continentes conts, tcad conti, int ocup_continente)
{
    bool encontrado = false;
    tcad aux;  // para guardar en un auxiliar el continente del arreglo
    tcad aux2;  // para guardar en un auxiliar el continente del arreglo
    int i;
    strcpy(aux2, conti);
    mayuscula(aux2);

    for (i = 0; i <= ocup_continente && !encontrado; i++)
    {
        strcpy(aux, conts[i]);

        mayuscula(aux); // llevamos ambos valores a mayuscula

        if (strcmp(aux, aux2) == 0)
        {
            // se compara que sean iguales
            encontrado = true;
        }
    }
    return encontrado;
}

//------------------------------------>>>MODULOS DE PARTICIPANTES<<<-----------------------------------------------
void administracion_participantes(v_continentes continentes, v_participantes &parts, int &ocup, int &id_participante, int &vAfrica, int &vAmerica, int &vAsia, int &vEuropa, int &vOceania, bool &control_participante)
{
    int op, tipo_registro, valor;
    int ocup_continentes = MAX_Continentes - 1;
    t_participante nuevo;
    char opcion;
    bool bandCargados;

    do
    {
        bandCargados = false;
        system("cls");
        menu_gestion_participantes(op);
        switch (op)
        {
        case 1:

            do
            {
                system("cls");
                cout << "--Registrar Participante--" << endl;
                cout << "- Seleccione tipo de registro -" << endl;
                cout << "1) Automatico - 2) Manual: ";
                cin >> tipo_registro;

                if (tipo_registro != 1 && tipo_registro != 2)
                {
                    cout << "Ingresó tipo registro inválido: " << tipo_registro << endl;
                    system("pause");
                }
            }
            while (tipo_registro != 1 && tipo_registro != 2);

            switch (tipo_registro)
            {
            case 1:
                do
                {
                    cout << "Ingrese cantidad de registros a generar (entre 30 y 1000): ";
                    cin >> valor;
                    if(!(valor >= 30 && valor <= 1000))
                        cout << "\nValor fuera del rango..." << endl;
                }
                while(!(valor >= 30 && valor <= 1000));

                if((MAX_Participante - ocup) > valor)
                {
                    cout << "\nSe generaran: " << valor << " participantes automaticamente...\n" << endl;
                    generar_participantes_automaticos(id_participante, valor, parts, continentes, ocup_continentes, ocup, nuevo);
                    bandCargados = true;
                }
                else
                {
                    cout << "\nSolo puede agregar: " << (MAX_Participante - 1) - ocup << " participantes.\n" << endl;
                }
                break;

            case 2:
                do
                {
                    bandCargados = true;
                    generar_participantes_manual(id_participante, parts, continentes, ocup_continentes, ocup, nuevo);
                    cout << "Desea seguir ingresando participantes? s/n: " << endl;
                    cin >> opcion;
                }
                while(opcion != 'n' && opcion != 'N');
                break;
            }

            control_continentes(parts, continentes, ocup, vAfrica, vAmerica, vAsia, vEuropa, vOceania, control_participante);
            if(bandCargados == true)
            {
                cout << "\nSe cargaron: " << vAfrica << " participantes de AFRICA" << endl;
                cout << "Se cargaron: " << vAmerica << " participantes de AMERICA" << endl;
                cout << "Se cargaron: " << vAsia << " participantes de ASIA" << endl;
                cout << "Se cargaron: " << vEuropa << " participantes de EUROPA" << endl;
                cout << "Se cargaron: " << vOceania << " participantes de OCEANIA\n" << endl;
            }
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "--Consultar Participante--" << endl;
            cout << "Ingrese ID de participante a consultar: ";
            cin >> valor;
            consultar_participante(parts, ocup, valor, 0);
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "--Modificar Participante--" << endl;
            cout << "Ingrese ID de participante a modificar: ";
            cin >> valor;
            modificar_participante(parts, ocup, valor, continentes, ocup_continentes);
            control_continentes(parts, continentes, ocup, vAfrica, vAmerica, vAsia, vEuropa, vOceania, control_participante);
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "--Eliminar Participante--" << endl;
            cout << "Ingrese ID de participante a eliminar: ";
            cin >> valor;
            eliminar_participante(parts, ocup, valor);
            control_continentes(parts, continentes, ocup, vAfrica, vAmerica, vAsia, vEuropa, vOceania, control_participante);
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "---Lista de Participantes---" << endl;
            listar_participantes_rec(parts, ocup);
            system("pause");
            break;
        case 6:
            break;
        default:
            cout << "Opción inválida" << endl;
            system("pause");
            break;
        }
    }
    while (op != 6);
}

void cargar_participante_auto(t_participante &p, v_continentes continentes, int ocup_continente)
{

    v_nombres nombres1 = {"Maria", "Soledad", "Merrye", "Cristal", "Alexis", "Abigail", "Anya", "Lizbeth", "Yesica", "Abril"};
    v_nombres nombres2 = {"Aba", "Trinidad", "Carla", "Defina", "Antonella", "Leonarda", "Amy", "Mirtha", "Josefa", "Isabel"};
    v_nombres apellidos = {"Willson", "Vince", "Jhonson", "Santillan", "Velazques", "Birge", "Calvo", "Renteria", "Torres", "Reinaga"};

    strcpy (p.primer_nombre, nombres1[aleatorio(0, MAX_Nombre - 1)]);
    strcpy (p.segundo_nombre, nombres2[aleatorio(0, MAX_Nombre - 1)]);
    strcpy (p.apellido, apellidos[aleatorio(0, MAX_Nombre - 1)]);
    strcpy(p.continente, continentes[aleatorio(0, ocup_continente)]);

    p.edad = aleatorio(21, 40);
    p.altura = aleatorio(150, 190) / 100.0;

    p.cant_idiomas =  aleatorio(1, 6);
    p.cant_lenguajes_prog = aleatorio(1, 10);
    p.anios_experiencia = aleatorio(0, 20);

    p.proyectos[1] = aleatorio(0, 4);

    if(p.anios_experiencia > 0)
    {
        p.proyectos[0] = aleatorio(0, 25);
        p.proyectos[2] = aleatorio(0, p.proyectos[0] + p.proyectos[1]);
    }
    else
    {
        p.proyectos[0] = 0;
        p.proyectos[2] = 0;
    }
}

void generar_participantes_automaticos(int &id_participante,
                                       int total_cargados,
                                       v_participantes &parts,
                                       v_continentes continentes,
                                       int ocup_continentes,
                                       int &ocup,
                                       t_participante &nuevo)
{
    int i;

    v_participantes aux_participantes;

    for (i = 1; i <= total_cargados; i++)
    {
        nuevo.id = id_participante;
        cargar_participante_auto(nuevo, continentes, ocup_continentes); //genera un participante con datos aleatorios

        copiar_participantes(parts, aux_participantes, ocup); //copiamos la lista existe a una lista auxiliar para poder hacer la busqueda sin alterar los registros existentes

        while(buscar_participante_by_nombre_apellido(aux_participantes, ocup, nuevo))//si la participante ya existe, se genera otro distinto automaticamente y vuelve a verificar.
        {
            cargar_participante_auto(nuevo, continentes, ocup_continentes);
        }
        insertar_participante(parts, ocup, nuevo); //Inserta una nueva participante luego de verificar que no exista.
        id_participante++; //actualiza el id del participante para un nuevo llamado
    }
}

void cargar_participante_manual(t_participante &p, v_continentes continentes, int ocup_continente)
{
    bool valido = false;

    system("cls");
    int minimoCaracteres = 3;

    do
    {
        cout << "Ingrese Apellido: ";
        fflush(stdin);
        gets(p.apellido);
        valido = strlen(p.apellido) >= minimoCaracteres;

        if (!valido || !verificacion_cadena(p.apellido))
        {
            cout << "Ingresó un apellido inválido" << endl;
            system("pause");
        }
    }
    while (!valido || !verificacion_cadena(p.apellido));

    do
    {
        cout << "Ingrese Primer Nombre: ";
        fflush(stdin);
        gets(p.primer_nombre);
        valido = strlen(p.primer_nombre) >= minimoCaracteres;

        if (!valido || !verificacion_cadena(p.primer_nombre))
        {
            cout << "Ingresó Primer nombre inválido" << endl;
            system("pause");
        }
    }
    while (!valido || !verificacion_cadena(p.primer_nombre));

    do
    {
        cout << "Ingrese Segundo Nombre: ";
        fflush(stdin);
        gets(p.segundo_nombre);
        valido = strlen(p.segundo_nombre) >= minimoCaracteres;

        if (!valido || !verificacion_cadena(p.segundo_nombre))
        {
            cout << "Ingresó Segundo nombre inválido" << endl;
            system("pause");
        }
    }
    while (!valido || !verificacion_cadena(p.segundo_nombre));

    do
    {
        cout << "Ingrese Edad (años): ";
        cin >> p.edad;
        valido = p.edad >= 21 && p.edad <= 40;

        if (!valido)
        {
            cout << "Ingresó una edad inválida (debe ser entre 21 y 40 años)" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese Altura (mts): ";
        cin >> p.altura;
        valido = p.altura >= 1.50 && p.altura <= 1.90;

        if (!valido)
        {
            cout << "Ingresó una altura inválida (debe ser entre 1.50 mts. y 1.90 mts.)" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese Cant. Idiomas que maneja: ";
        cin >> p.cant_idiomas;
        valido = p.cant_idiomas >= 1 && p.cant_idiomas <= 6;

        if (!valido)
        {
            cout << "Ingresó cantidad de idiomas inválida (debe tener entre 1 y 6 idiomas)" << endl;
            system("pause");
        }
    }
    while(!valido);

    do
    {
        cout << "Ingrese Continente: ";
        fflush(stdin);
        gets(p.continente);

        valido = buscar_continente(continentes, p.continente, ocup_continente); //verifca que el continente que ingreso el usuario exista en la lista y en casod e que no exista muestra la lista de contientes validos.

        valido = valido && verificacion_cadena(p.continente);
        if(!valido)
        {
            cout << "El continente no es válido: " << p.continente << endl;
            cout << "\n--Continentes válidos: --" << endl;
            for (int i = 0; i <= ocup_continente; i++)
            {
                cout << continentes[i] << " , ";
            }
            cout << "\n-------------------------\n" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese Cant. de Lenguajes de programacion que conoce: ";
        cin >> p.cant_lenguajes_prog;
        valido = p.cant_lenguajes_prog >= 1 && p.cant_lenguajes_prog <= 10;
        if(!valido)
        {
            cout << "Ingresó cantidad de lenguajes de prog. inválidos (debe tener entre 1 y 10 lenguajes)" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese Años de Experiencia que posee: ";
        cin >> p.anios_experiencia;
        valido = p.anios_experiencia >= 0 && p.anios_experiencia <= 20;

        if (!valido)
        {
            cout << "Ingresó Años de experiencia inválidos (debe tener entre 0 y 20 Años de experiencia)" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese Cant. de Proyectos en ejecución: ";
        cin >> p.proyectos[1]; //1: ejecucion
        valido = p.proyectos[1] >= 0 && p.proyectos[1] <= 4;

        if (!valido)
        {
            cout << "Ingresó Cant. de Proyectos en ejecución inválidos (debe tener entre 0 y 4 proyectos)" << endl;
            system("pause");
        }
    }
    while (!valido);

    if (p.anios_experiencia > 0)
    {
        do
        {
            cout << "Ingrese Cant. de Proyectos finalizados: ";
            cin >> p.proyectos[0]; // 0: finalizados
            valido = p.proyectos[0] >= 0 && p.proyectos[0] <= 25;

            if (!valido)
            {
                cout << "Ingresó Cant. de Proyectos finalizados inválidos (debe tener entre 0 y 25 proyectos finalizados)" << endl;
                system("pause");
            }
        }
        while (!valido);

        do
        {
            cout << "Ingrese Cant. de Proyectos liderados: ";
            cin >> p.proyectos[2]; //2: liderados 0<=(finalizados + ejecucion)
            valido = (p.proyectos[2] >= 0) && (p.proyectos[2] <=  p.proyectos[0] + p.proyectos[1]);

            if (!valido)
            {
                cout << "Ingresó Cant. de Proyectos liderados inválidos (debe tener entre 0 y la suma de proyectos en ejec. y fin.)" << endl;
                system("pause");
            }
        }
        while (!valido);

        p.proyectos[2] = p.proyectos[0] + p.proyectos[1]; // suma de proyectos: (finalizados + en ejecucion)
    }
    else
    {
        p.proyectos[0] = 0; // no tiene finalizado ningun proyecto por falta de experiencia (0)
        p.proyectos[2] = 0; // no tiene liderados  ningun proyecto por falta de experiencia (0)
    }
    mayuscula(p.continente);
}

void generar_participantes_manual(int &id_participante,
                                  v_participantes &parts,
                                  v_continentes continentes,
                                  int ocup_continentes,
                                  int &ocup,
                                  t_participante &nuevo)
{

    v_participantes aux_participantes;
    nuevo.id = id_participante; //asignamos el id actual al nuevo participante

    cargar_participante_manual(nuevo, continentes, ocup_continentes); //Se solicita al usuario que cargue el nuevo participante manualmente

    copiar_participantes(parts, aux_participantes, ocup); //Se copia la lista existente a un auxiliar para realizar la busqueda del participante

    while(buscar_participante_by_nombre_apellido(aux_participantes, ocup, nuevo)) //Verificamos que el participante no exista, de lo contrario se solicita que cargue nuevamente los campos
    {
        cout << "(Advertencia) El participante: " << nuevo.apellido << ", " << nuevo.primer_nombre << ", " << nuevo.segundo_nombre << " Ya esta registrado." << endl;
        system("pause");
        cargar_participante_manual(nuevo, continentes, ocup_continentes);
    }

    insertar_participante(parts, ocup, nuevo); //Una vez el participante es válido se inserta en el vector original y se incrementa el id para la prox carga
    id_participante++;
}

void insertar_participante(v_participantes &parts, int &ocup, t_participante nuevo)
{
    int i, j;

    if (ocup == MAX_Participante - 1)
        cout << "\nParticipantes llenos.\n" << endl;
    else
    {
        i = 0;
        while ((i <= ocup) && (nuevo.id > parts[i].id))
        {
            i++;
        }
        j = ocup;

        while (j >= i)
        {
            parts[j + 1] = parts[j];
            j--;
        }
        parts[i] = nuevo;
        ocup++;
    }
}

void imprimirParticipante(t_participante p)
{
    cout << "--------------------------" << endl;
    cout << "ID: " << p.id << endl;
    cout << "Apellido: " << p.apellido << endl;
    cout << "Primer Nombre: " << p.primer_nombre << endl;
    cout << "Segundo Nombre: " << p.segundo_nombre << endl;
    cout << "Edad: " << p.edad << " años" << endl;
    cout << "Altura: " << p.altura << " mts." << endl;
    cout << "Cantidad de Idiomas: " << p.cant_idiomas << endl;
    cout << "Continente: " << p.continente << endl;
    cout << "Cantidad de Lenguajes de Programación: " << p.cant_lenguajes_prog << endl;
    cout << "Años de Experiencia: " << p.anios_experiencia << " años" << endl;
    cout << "Proyectos Finalizados: " << p.proyectos[0] << endl;
    cout << "Proyectos En ejecución: " << p.proyectos[1] << endl;
    cout << "Proyectos Liderados: " << p.proyectos[2] << endl;
    cout << "--------------------------" << endl;
}

void cambio_participante(t_participante &x, t_participante &y)
{
    t_participante aux;
    aux = x;
    x = y;
    y = aux;
}

void shell_apell_nombres(v_participantes &parts, int ocup)
{
    int i, j, salto;
    t_participante aux; //declaramos un auxiliar para guardar la posicion del valor a ordenar

    for(i = 0; i <= ocup; i++) //primero llevamos todos los campos a ordenar a un solo tipo de "formato" (Mayusculas) para que el ordenamiento sea correcto
    {
        mayuscula(parts[i].apellido);
        mayuscula(parts[i].primer_nombre);
        mayuscula(parts[i].segundo_nombre);
    }

    salto = ocup / 2;

    while (salto > 0)
    {
        for (i = salto; i <= ocup; i++)
        {
            aux = parts[i];
            j = i - salto;
            while (j >= 0 &&
                    (strcmp(parts[j].apellido, aux.apellido) > 0 || //Se compara que los apellidos sean iguales
                     (strcmp(parts[j].apellido, aux.apellido) == 0 && strcmp(parts[j].primer_nombre, aux.primer_nombre) > 0) || //si son iguales compara por apellido y primer nombre
                     (strcmp(parts[j].apellido, aux.apellido) == 0 && strcmp(parts[j].primer_nombre, aux.primer_nombre) == 0
                      && strcmp(parts[j].segundo_nombre, aux.segundo_nombre) > 0) //si el apellido y el primer nombre son iguales, compara por el segundo nombre
                    )
                  )
            {
                parts[j + salto] = parts[j];
                j -= salto;
            }
            parts[j + salto] = aux;
        }
        salto /= 2;
    }
}


void orden_sacudida_participante_ID(v_participantes &vconti, int ocup) //ordena por ID
{
    bool ordenado = false;
    int pri = 0, ult = ocup, i;

    while ((ordenado == false) && (pri < ult))
    {
        ordenado = true;
        for (i = ult; i > pri; i--)
        {
            if (vconti[i].id < vconti[i - 1].id) // criterio ascendente
            {
                cambio_participante(vconti[i], vconti[i - 1]);
                ordenado = false;
            }
        }
        pri = pri + 1;
        if (ordenado == false)
        {
            ordenado = true;
            for (i = pri; i < ult; i++)
            {
                if (vconti[i].id > vconti[i + 1].id) // criterio ascendente
                {
                    cambio_participante(vconti[i], vconti[i + 1]);
                    ordenado = false;
                }
            }
            ult = ult - 1;
        }
    }
}

void copiar_participantes(v_participantes parts, v_participantes &copia, int ocup)
{
    int i;
    for(i = 0; i <= ocup; i++)
    {
        copia[i] = parts[i];
    }
}

bool buscar_participante_by_nombre_apellido(v_participantes &parts, int ocup, t_participante buscado) //busqueda por 1er nombre, 2do nombre y apellido
{
    int comparo_apellido, comparo_primer_nombre, comparo_segundo_nombre;

    bool encontrado = false;
    int i = 0;

    tcad aux_buscado_1er_nombre, aux_buscado_2do_nombre, aux_buscado_apellido;

    shell_apell_nombres(parts, ocup); //ordena el vector por apellido, primer y segundo nombre, y lo convierte a mayusculas todos los "nombres"

    strcpy(aux_buscado_1er_nombre, buscado.primer_nombre); //guardamos los campos del reg. buscado en variables auxiliares
    strcpy(aux_buscado_2do_nombre, buscado.segundo_nombre);
    strcpy(aux_buscado_apellido, buscado.apellido);

    mayuscula(aux_buscado_1er_nombre); // llevamos valores del registro buscado a mayuscula
    mayuscula(aux_buscado_2do_nombre);
    mayuscula(aux_buscado_apellido);

    bool buscar = true;  // bandera para controlar la búsqueda

    while (i <= ocup && buscar)
    {
        comparo_apellido = strcmp(parts[i].apellido, aux_buscado_apellido); //obtenemos el valor de la comparacion de apellido
        comparo_primer_nombre = strcmp(parts[i].primer_nombre, aux_buscado_1er_nombre); //obtenemos el valor de la comparacion de apellido
        comparo_segundo_nombre = strcmp(parts[i].segundo_nombre, aux_buscado_2do_nombre); //obtenemos el valor de la comparacion de apellido

        if (comparo_apellido > 0 ||
                (comparo_apellido == 0 && comparo_primer_nombre > 0) ||
                (comparo_apellido == 0 && comparo_primer_nombre == 0 && comparo_segundo_nombre > 0))
        {
            buscar = false;  // detiene la busqueda porque no tiene sentido seguir buscando en un vector ordenado por apellido, primer y segundo nombre.
        }
        else if (comparo_apellido == 0 && comparo_primer_nombre == 0 && comparo_segundo_nombre == 0)
        {
            encontrado = true;
            buscar = false;  // detiene la busqueda porq encontro el participante
        }

        i++;  // se incrementa el indice del participante
    }

    return encontrado;
}

void listar_participantes_rec(v_participantes parts, int ocup)
{
    t_participante p;

    if(ocup < 0)
    {
        cout << "\nLista de participantes vacía." << endl;
        cout << "\n-------------------\n" << endl;
    }
    else
    {
        if(ocup == 0)
        {
            p = parts[ocup];
        }
        else
        {
            listar_participantes_rec(parts, ocup - 1);
            p = parts[ocup];
        }
        imprimirParticipante(p);
    }
}

void eliminar_participante(v_participantes &vec, int &ocup, int id)
{
    int i, alto, bajo;
    bool encontrado = false;

    if(ocup == -1)
        cout << "\nNo existe ningún participante.\n" << endl; //validamos que existe al menos un participante
    else
    {
        i = -1;
        bajo = 0;
        alto = ocup;

        buscar_participante_bin_by_id(vec, bajo, alto, id, i); //buscamos la posicion del participante buscado por id (busq binaria)

        encontrado = (i > -1 && i <= ocup); //si existe el participante nos devuelve la posicion dentro del rango

        if(encontrado == true)
        {
            cout << "\nSe eliminó el participante: \n" << endl;
            imprimirParticipante(vec[i]); //mostramos que se eliminara el participante dicho

            while(i < ocup)
            {
                vec[i] = vec[i + 1];
                i++;
            }
            ocup--;
        }
        else
            cout << "\nEl participante con ID: " << id << " no existe....\n" << endl;
    }
}


void buscar_participante_bin_by_id(v_participantes parts, int bajo, int alto, int id_buscado, int &posicion) //busqueda binaria
{
    int central;

    if (bajo > alto)
    {
        posicion = -1; // No se encontró el elemento
        return;
    }

    central = (bajo + alto) / 2;
    if (id_buscado == parts[central].id)
    {
        posicion = central; // Se encontró el elemento
    }
    else if (id_buscado < parts[central].id)     // Orden creciente
    {
        buscar_participante_bin_by_id(parts, bajo, central - 1, id_buscado, posicion);
    }
    else
    {
        buscar_participante_bin_by_id(parts, central + 1, alto, id_buscado, posicion);
    }
}

void consultar_participante(v_participantes v, int ocup, int id, int tipo_consulta)
{
    int i, alto, bajo;
    bool encontrado = false;

    if(ocup == -1)
        cout << "\nNo existe ningún participante.\n" << endl;
    else
    {
        v_participantes vec;
        copiar_participantes(v, vec, ocup);
        i = -1;
        bajo = 0;
        alto = ocup;
        orden_sacudida_participante_ID(vec, ocup); //primero ordenamos la lista de participantes por id y con orden sacudida
        buscar_participante_bin_by_id(vec, bajo, alto, id, i); //despues realizamos la busqueda binaria para obtener la posicion del participante

        encontrado = (i > -1 && i <= ocup); //si la posicion (i) existe nos devuelve V.

        if(encontrado == true)
        {
            switch(tipo_consulta)  //0 consulta dato basico - 1 consulta 1er etapa - 2 consulta segunda etapa
            {
            case 0:
                imprimirParticipante(vec[i]); //Segun el tipo de consulta mostraremos distintos datos del mismo participante
                break;
            case 1:
                mostrar_Participante_etapa1(vec[i]);
                break;
            case 2:
                mostrar_Participante_etapa2(vec[i]);
                break;
            }
        }
        else
            cout << "\nEl participante con ID: " << id << " no existe....\n" << endl;
    }
}

void modificar_participante(v_participantes &vec, int ocup_parts, int id, v_continentes conts, int ocup_conts)
{
    int i, alto, bajo;
    bool encontrado = false;
    t_participante aux_participante;

    if(ocup_parts == -1)
        cout << "\nNo existe ningún participante.\n" << endl; //acá validamos que al momento de modificar exista minimo un participante
    else
    {
        i = -1;
        bajo = 0;
        alto = ocup_parts;

        buscar_participante_bin_by_id(vec, bajo, alto, id, i); //verificamos que exista el participante y obtenemos la posicion (i)
        encontrado = (i > -1 && i <= ocup_parts);

        if(encontrado == true)
        {
            aux_participante = vec[i]; //guardamos el participante en un registro auxiliar

            cargar_participante_manual(aux_participante, conts, ocup_conts); //procedemos a modificar los campos manualmente (excepto el ID)

            vec[i] = aux_participante; //Finalmente guardamos el registro auxiliar en la posicion del registro original

            cout << "\nSe modificó el participante: \n" << endl;
            imprimirParticipante(vec[i]); //mostramos el nuevo registro modificado

        }
        else
            cout << "\nEl participante con ID: " << id << " no existe....\n" << endl;
    }
}

//ESTE MODULO SE ENCARGA DE CONTAR LAS PARTIPANTES DE CADA CONTINENTE, VALIDA QUE EXISTA 30 PERSONAS EN TOTAL Y QUE SEAN 4 POR CADA CONTINENTE
void control_continentes(v_participantes parts, v_continentes continentes, int ocup_parts, int &vAfrica, int &vAmerica, int &vAsia, int &vEuropa, int &vOceania, bool &control_participante)
{
    int i;
    vAfrica = 0, vAmerica = 0, vAsia = 0, vEuropa = 0, vOceania = 0;
    int cont = 0;
    for(i = 0; i <= ocup_parts; i++)
    {

        cont++;

        //{"AFRICA", "AMÉRICA", "ASIA", "EUROPA", "OCEANIA"};
        if(strcmp(parts[i].continente, continentes[0]) == 0) //{"Africa"};
            vAfrica++;
        if(strcmp(parts[i].continente, continentes[1]) == 0) //{"América"};
            vAmerica++;
        if(strcmp(parts[i].continente, continentes[2]) == 0) //{"Asia"};
            vAsia++;
        if(strcmp(parts[i].continente, continentes[3]) == 0) //{"Europa"};
            vEuropa++;
        if(strcmp(parts[i].continente, continentes[4]) == 0) //{"Oceanía"};
            vOceania++;
    }
    control_participante = cont >= 30; //acá validamos que existan 30 personas como minimo independiente de si son 4 de cada continente (se validara en etapa 1 si existen
    //esos 4 de cada continente)
}

//--------------------------------------------------------------------->>>MODULOS PARA JURADOS<<<---------------------------------------------------------------------------
//modulo_carga manual
void Cargar_Jurados(v_jurados v, int ocup, t_jurado &jurado)
{
    bool b;

    tcad apell, nombre;

    int minimoCaracteres = 3;

    bool valido = false;

    do
    {
        do
        {
            cout << "Ingrese apellido: ";
            fflush(stdin);
            gets(apell);
            valido = strlen(apell) >= minimoCaracteres;

            if (!valido || !verificacion_cadena(apell))
            {
                cout << "Ingresó apellido inválido" << endl;
                system("pause");
            }
        }
        while (!valido || !verificacion_cadena(apell));

        do
        {
            cout << "Ingrese nombre: ";
            fflush(stdin);
            gets(nombre);
            valido = strlen(nombre) >= minimoCaracteres;

            if (!valido || !verificacion_cadena(nombre))
            {
                cout << "Ingresó nombre inválido" << endl;
                system("pause");
            }
        }
        while (!valido || !verificacion_cadena(nombre));

        b = existe_apellido_nombre_jurado(v, ocup, apell, nombre); //verificacion de apellido y nombre no repetido

        if(b == true)
        {
            cout << "El jurado: " << apell << ", " << nombre << " ya existe." << endl;
        }
    }
    while(b == true);
    // una vez se verifica que no este repetido, se asignan los valores al registro
    strcpy(jurado.apellido, apell);
    strcpy(jurado.nombre, nombre);

    do
    {
        cout << "Ingrese empresa: ";
        fflush(stdin);
        gets(jurado.empresa);
        valido = strlen(jurado.empresa) >= minimoCaracteres;

        if (!valido)
        {
            cout << "Ingresó empresa inválido" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {

        cout << "Ingrese cargo: ";
        fflush(stdin);
        gets(jurado.cargo);
        valido = strlen(jurado.cargo) >= minimoCaracteres;

        if (!valido)
        {
            cout << "Ingresó cargo inválido" << endl;
            system("pause");
        }
    }
    while (!valido);

    do
    {
        cout << "Ingrese años en la industria: ";
        cin >> jurado.anios_indst;

        valido = jurado.anios_indst >= 1;
        if (!valido)
        {
            cout << "Ingresó años invalidos" << endl;
            system("pause");
        }
    }
    while (!valido);
}

bool existe_apellido_nombre_jurado(v_jurados v, int ocup, tcad apell, tcad nombre)
{
    bool band = false;
    int i;

    tcad auxNombre; //creamos las variables auxiliares para validar que no exista el usuario sin alterar los datos cargados
    tcad auxApell;
    tcad auxVectAp;
    tcad auxVectNom;

    strcpy(auxNombre, nombre);
    mayuscula(auxNombre); //se llevan los valores consultados a mayusculas

    strcpy(auxApell, apell);
    mayuscula(auxApell);

    if(ocup == -1)
    {
        return band = false;
    }
    else
    {
        for(i = 0; i <= ocup && band == false; i++)
        {
            strcpy(auxVectAp, v[i].apellido); //acá guardamos los valores cargados en auxiliares y procedemos a comparar el resultado de los campos auxiliares
            mayuscula(auxVectAp);

            strcpy(auxVectNom, v[i].nombre);
            mayuscula(auxVectNom);

            band = (strcmp(auxVectAp, auxApell) == 0 && strcmp(auxVectNom, auxNombre) == 0); //si el jurado existe devolvemos el valor por la bandera
        }
    }
    return band;
}

void Agregar_Jurados(v_jurados &v, int &ocup)
{
    t_jurado nuevo;

    if(ocup == MAX_Jurados - 1)
    {
        cout << "NO HAY ESPACIO.." << endl;
    }
    else
    {
        Cargar_Jurados(v, ocup, nuevo);
        ocup++;
        v[ocup] = nuevo;
    }
}

void Mostrar_Jurados(v_jurados vec, int ocup)
{
    cout << "------------------------------------------------" << endl;
    cout << "ID: " << vec[ocup].ID_jurado << endl;
    cout << "Apellido y nombre: " << vec[ocup].apellido << ", " << vec[ocup].nombre << endl;
    cout << "Empresa: " << vec[ocup].empresa << endl;
    cout << "Cargo: " << vec[ocup].cargo << endl;
    cout << "Años en la industria: " << vec[ocup].anios_indst << endl;
    cout << "------------------------------------------------" << endl;
}

void Lista_recursivo(v_jurados vec, int ocup) //orden creciente.<<<<<<
{
    if(ocup < 0)
    {
        cout << "\nLista de jurados vacía." << endl;
        cout << "\n-------------------\n" << endl;
    }
    else
    {
        if(ocup == 0)
        {
            Mostrar_Jurados(vec, ocup);
        }
        else
        {
            if(ocup >= 0)
            {
                Lista_recursivo(vec, ocup - 1);
                Mostrar_Jurados(vec, ocup);
            }
        }
    }
}

void Borrar(v_jurados &vec, int &ocup, tcad borrar) //borrar un jurado por su apellido
{
    int i;
    bool enco;
    tcad borrado;  //creamos variables auxiliares para realizar la comparacion de apellidos de los jurados
    tcad auxApellido;
    if(ocup == -1)
    {
        cout << "\nNo existe ningún jurado.\n" << endl; //validamos que exista al menos un jurado en el vector
    }
    else
    {
        enco = false;
        i = 0;
        strcpy(borrado, borrar); //llevamos a mayusculas el apellido ingresado
        mayuscula(borrado);
        while((i <= ocup) && !enco)
        {
            strcpy(auxApellido, vec[i].apellido); //aqui llevamos a mayusc. el apellido del jurado del vector y procedemos a comparar
            mayuscula(auxApellido);
            if(strcmp(borrado, auxApellido) == 0)
            {
                cout << "Se eliminó al jurado: " << endl;
                Mostrar_Jurados(vec, i); //si el jurado existe mostramos el jurado que se eliminará en la posicion de (i)
                enco = true;
            }
            else
            {
                i++;
            }
        }
        if(enco == true)
        {
            while(i < ocup)
            {
                vec[i] = vec[i + 1];
                i++;
            }
            ocup--;
        }
        else
        {
            cout << "\nNo existe jurado con ID:  " << borrar << endl;
        }
    }
    system("pause");
}

void cambio_Jurados(t_jurado  &x, t_jurado &y)
{
    t_jurado aux;

    aux = x;
    x = y;
    y = aux;
}

int Busqueda_Binaria_Recursiva_JURADO(v_jurados vec, int bajo, int alto, int buscado)//BUSQUEDA DE JURADO POR ID
{
    int central;

    if (bajo > alto)
    {
        return -1; // No se encontró el elemento por que salio del rango
    }
    central = (bajo + alto) / 2;
    if(buscado == vec[central].ID_jurado)
    {
        return central; // Se encontró el elemento
    }
    else if (buscado < vec[central].ID_jurado)
    {
        return Busqueda_Binaria_Recursiva_JURADO(vec, bajo, central - 1, buscado);
    }
    else
    {
        return Busqueda_Binaria_Recursiva_JURADO(vec, central + 1, alto, buscado);
    }
}

void modificar_jurado(v_jurados  &vec, int ocup, int id_buscado) //MODIFICA UN REGISTRO COMPLETO, MENOS EL ID
{
    int posicion, alto, bajo;
    t_jurado aux;

    if(ocup == -1)
        cout << "\nNo existe ningún jurado.\n" << endl; //se valida que exista un jurado en el vector como minimo
    else
    {
        posicion = -1;
        bajo = 0;
        alto = ocup;

        posicion = Busqueda_Binaria_Recursiva_JURADO(vec, bajo, alto, id_buscado); //procedemos a consultar la posicion del jurado

        if(posicion >= 0 && posicion <= ocup) //si la posicion esta dentro del rango el jurado existe y se asigna a un registro auxiliar
        {
            aux = vec[posicion];
            Cargar_Jurados(vec, ocup, aux); //llamamos al modulo de carga de jurados y al finalizar asignamos el registro auxiliar a la posicion
            vec[posicion] = aux;
            cout << "\nSe modifico el jurado: \n" << endl;
            Mostrar_Jurados(vec, posicion); //finalizando imprimimos el jurado modificado
        }
        else
        {
            cout << "\nEl jurado con el ID: " << id_buscado << " no existe\n" << endl;
        }
    }
}

void administracion_jurados(v_jurados &jurados, int &ocupado_ju, bool &control_jurados, int &id_jurado_base)
{

    tcad apellido;
    int id, posicion, bajo, alto; //ocupado_ju=-1,
    int op;
    char res;

    do
    {
        system("cls");
        menu_gestion_jurados(op);
        switch(op)
        {
        case 1:
            do
            {
                system("cls");
                cout << "--Agregar Jurado--" << endl;

                Agregar_Jurados(jurados, ocupado_ju);

                jurados[ocupado_ju].ID_jurado = id_jurado_base;

                id_jurado_base++;
                cout << "\nDesea seguir agregando jurados? s/n: ";
                cin >> res;

            }
            while(res != 'n' && res != 'N');

            control_jurados = ocupado_ju >= 2;

            if(!control_jurados)
            {
                cout << "\nSe necesita como minimo 3 jurados" << endl;
                system("pause");
            }

            break;
        case 2:
            system("cls");
            cout << "--Consultar Jurado--" << endl;

            cout << "Ingrese el ID a consultar: ";
            cin >> id;
            if(ocupado_ju == -1)
                cout << "\nNo existe ningún jurado.\n" << endl;
            else
            {
                bajo = 0;
                alto = ocupado_ju;
                posicion = Busqueda_Binaria_Recursiva_JURADO(jurados, bajo, alto, id); //validamos que exista el jurado para mostrarlo

                if(posicion > -1 && posicion <= ocupado_ju)
                {
                    Mostrar_Jurados(jurados, posicion);
                }
                else
                {
                    cout << "\nNo existe jurado con ID " << id << endl;
                }
            }
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "--Modificar Jurado--" << endl;
            cout << "Ingrese el ID a modificar: ";
            cin >> id;
            modificar_jurado(jurados, ocupado_ju, id);

            system("pause");
            break;

        case 4:
            system("cls");
            cout << "--Eliminar Jurado--" << endl;
            cout << "Ingrese el apellido a eliminar: ";
            fflush(stdin);
            gets(apellido);
            Borrar(jurados, ocupado_ju, apellido);
            control_jurados = ocupado_ju >= 2;
            break;
        case 5:
            system("cls");
            cout << "---Lista de Jurados---" << endl;
            Lista_recursivo(jurados, ocupado_ju);
            system("pause");
            break;
        case 6:
            break;
        default:
            cout << "Opcion invalida..." << endl;
            system("pause");
            break;
        }
    }
    while(op != 6);
}

//------------------------------------------>>>ETAPAS<<<---------------------------------------------------------------------------------------------------

//ETAPA 1:
void mostrar_Participante_etapa1(t_participante p)
{
    cout << "---" << endl;
    cout << "Continente: " << p.continente << endl;
    cout << "ID Participante: " << p.id << endl;
    cout << "Participante: " << p.apellido << ", " << p.primer_nombre << ", " << p.segundo_nombre << endl;
    cout << "Suma de notas de vestuario: " << p.etapa1.suma_nota_vestuario << endl;
    cout << "Suma de notas de elegancia: " << p.etapa1.suma_nota_elegancia << endl;
    cout << "Suma de notas de elocuencia: " << p.etapa1.suma_nota_elocuencia << endl;
    cout << "Suma de notas de idiomas: " << p.etapa1.suma_nota_idiomas << endl;

    cout << "\nPuntaje total en Etapa 1: " << p.etapa1.puntaje_total << endl;
    cout << "---" << endl;
}

void administracion_etapa_1(v_continentes continentes, v_participantes &participantes, int ocup_participantes, int vAfrica,
                            int vAmerica, int vAsia, int vEuropa, int vOceania, v_jurados jurados,
                            int ocup_jurados, bool control_jurados, bool control_participante,
                            v_participantes &seleccionadas, int &ocup_seleccionadas, bool &control_etapa1)
{
    int op, valor;
    do
    {
        system("cls");
        menu_primera_etapa(op);
        switch (op)
        {
        case 1:
            system("cls");
            //validar todos los campos y luego mostrar clasificacion 1er etapa

            if(!control_participante)
                cout << "\nSe requiere 30 participante como minimo para ingresar a la primer etapa\n" << endl;
            else if(!control_jurados)
                cout << "\nSe requiere 3 jurados minimos para ingresar a la primer etapa\n" << endl;

            else if (vAfrica >= 4 && vAmerica >= 4 && vAsia >= 4 && vEuropa >= 4 && vOceania >= 4)   //validar q existan minimo 4 participante de cada continentes
            {

                control_etapa1 = true;
                cout << "--Clasificacion 1er Etapa--" << endl;
                clasificar_participantes(continentes, participantes, ocup_participantes, jurados, ocup_jurados, seleccionadas, ocup_seleccionadas);
            }

            else //aca los contadores nos indican si existen 4 participantes como minimo por cada continente esto se necesita validar para poder hacer la clasificacion
            {
                if (vAfrica < 4)
                {
                    cout << "Faltan " << 4 - vAfrica << " participantes de AFRICA" << endl;
                }
                if (vAmerica < 4)
                {
                    cout << "Faltan " << 4 - vAmerica << " participantes de AMERICA" << endl;
                }
                if (vAsia < 4)
                {
                    cout << "Faltan " << 4 - vAsia << " participantes de ASIA" << endl;
                }
                if (vEuropa < 4)
                {
                    cout << "Faltan " << 4 - vEuropa << " participantes de EUROPA" << endl;
                }
                if (vOceania < 4)
                {
                    cout << "Faltan " << 4 - vOceania << " participantes de OCEANIA" << endl;
                }
            }
            system("pause");
            break;
        case 2:
            system("cls");
            if(control_etapa1 == true)
            {
                cout << "--Consultar Puntaje Participante--" << endl;
                cout << "Ingrese ID de participante a consultar: ";
                cin >> valor;
                consultar_participante(participantes, ocup_participantes, valor, 1);
            }
            else
            {
                cout << "\nPrimero debe realizar clasificacion de 20 mejores candidatas.\n" << endl;
            }
            system("pause");
            break;
        case 3:
            break;

        default:
            cout << "Opción inválida" << endl;
            system("pause");
            break;
        }
    }
    while (op != 3);
}

//Evaluacion de cada participante
void clasificar_participantes(v_continentes continentes, v_participantes &participantes,
                              int ocup_participantes, v_jurados jurados,
                              int ocup_jurados, v_participantes &seleccionadas, int &ocup_seleccionadas)
{
    ocup_seleccionadas = -1; //inicializa -1 para clasificar las 20 de acuerdo al ptj obtenido
    int i, j;
    int cantidad_jurados = ocup_jurados + 1; //se suma +1  para calcular el promedio correcatamente

    v_participantes aux_continente; //temporal asia, europa...
    int ocup_aux;

    //notas individuales de cada uno de los jurados (con su id nombre y notas correspondientes) registrados para cada participante.
    for(i = 0; i <= ocup_participantes; i++) //Recorrido de toda la lista de participantes.
    {
        //antes de calcular las sumas debemos iniciar los acumuladores en 0
        participantes[i].etapa1.suma_nota_vestuario = 0;
        participantes[i].etapa1.suma_nota_elegancia = 0;
        participantes[i].etapa1.suma_nota_elocuencia = 0;
        participantes[i].etapa1.suma_nota_idiomas = 0;

        for(j = 0; j <= ocup_jurados; j++) //Recorrido de la lista de jurados
        {
            //copiar datos del jurado
            participantes[i].etapa1.notas_jurado[j].ID_jurado = jurados[j].ID_jurado;  //copiamos el id del jurado
            strcpy(participantes[i].etapa1.notas_jurado[j].apellido_jurado, jurados[j].apellido); //copiamos el apellido del jurado
            strcpy(participantes[i].etapa1.notas_jurado[j].nombre_jurado, jurados[j].nombre); //copiamos el nombre

            //generamso valores aleatorios como puntajes individuales
            participantes[i].etapa1.notas_jurado[j].nota_vestuario = aleatorio(0, 100);
            participantes[i].etapa1.notas_jurado[j].nota_elegancia = aleatorio(0, 100);
            participantes[i].etapa1.notas_jurado[j].nota_elocuencia = aleatorio(0, 100);
            participantes[i].etapa1.notas_jurado[j].nota_idiomas = (participantes[i].cant_idiomas / 6.0 * 100); //la formula solicitada en el final

            //sumar las notas de cada categoría
            participantes[i].etapa1.suma_nota_vestuario += participantes[i].etapa1.notas_jurado[j].nota_vestuario;
            participantes[i].etapa1.suma_nota_elegancia += participantes[i].etapa1.notas_jurado[j].nota_elegancia;
            participantes[i].etapa1.suma_nota_elocuencia += participantes[i].etapa1.notas_jurado[j].nota_elocuencia;
            participantes[i].etapa1.suma_nota_idiomas += participantes[i].etapa1.notas_jurado[j].nota_idiomas;
        }

        // promediamos las notas parciales
        participantes[i].etapa1.suma_nota_vestuario = participantes[i].etapa1.suma_nota_vestuario / cantidad_jurados;
        participantes[i].etapa1.suma_nota_elegancia = participantes[i].etapa1.suma_nota_elegancia / cantidad_jurados;
        participantes[i].etapa1.suma_nota_elocuencia = participantes[i].etapa1.suma_nota_elocuencia / cantidad_jurados;
        participantes[i].etapa1.suma_nota_idiomas = participantes[i].etapa1.suma_nota_idiomas / cantidad_jurados;

        //al finalizar sumamos las notas promediadas para obtener un puntaje total de la participante
        participantes[i].etapa1.puntaje_total =
            participantes[i].etapa1.suma_nota_vestuario +
            participantes[i].etapa1.suma_nota_elegancia +
            participantes[i].etapa1.suma_nota_elocuencia +
            participantes[i].etapa1.suma_nota_idiomas;

    }

    for (i = 0; i <= 4; i++) //5 continentes
    {
        pertenece_continente(participantes, ocup_participantes, aux_continente, ocup_aux, continentes[i]);
        Ordenacion_Continentes(aux_continente, ocup_aux, seleccionadas, ocup_seleccionadas);
    }

    cout << "\n---* Se guardaron las: " << ocup_seleccionadas + 1 << " mejores del certamen!... *---" << endl;

    Insercion_primera(seleccionadas, ocup_seleccionadas);	//ordenamos las 20 mejores

    for (i = 0; i <= ocup_seleccionadas; i++)
    {
        mostrar_Participante_etapa1(seleccionadas[i]);
    }

}

//SUMA CUANTOS HAY POR CADA CONTINENTE Y LO ASIGNA A UN VECTOR AUXILIAR
void pertenece_continente(v_participantes list_part, int ocup_part, v_participantes &vconti, int &ocup_conti, tcad c)
{
    ocup_conti = -1;
    int i;
    for(i = 0; i <= ocup_part; i++) //recorre todo el vec de participantes
    {
        if(strcmp(list_part[i].continente, c) == 0)
        {
            ocup_conti++;
            vconti[ocup_conti] = list_part[i]; //asigono una participante a su respectivo continente
        }
    }
}

void Ordenacion_Continentes(v_participantes &lista_auxiliar, int ocup_auxiliar, v_participantes &seleccionadas, int &ocup_seleccionadas)
{
    int i;
    //ordena los participantes por puntaje total
    Insercion_primera(lista_auxiliar, ocup_auxiliar);
    //me quedo con las primeras cuatro participantes
    for(i = 0; i <= 3; i++)
    {
        ocup_seleccionadas++;
        seleccionadas[ocup_seleccionadas] = lista_auxiliar[i]; //EJ:africa, Seleccionadas se va qedando con las 4 de africa.
    }
}

void Insercion_primera(v_participantes &vconti, int ocup)// ordena por puntaje total de la etapa 1.
{
    int i, j;
    t_participante aux; //registro

    for(i = 1; i <= ocup; i++)
    {
        aux = vconti[i];
        j = i - 1;

        while((j >= 0) && (vconti[j].etapa1.puntaje_total < aux.etapa1.puntaje_total)) //decreciente (vec[j]<aux).
        {
            vconti[j + 1] = vconti[j];
            j--;
        }
        vconti[j + 1] = aux;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//ETAPA 2:
void mostrar_Participante_etapa2(t_participante p )
{
    cout << "---" << endl;
    cout << "Continente: " << p.continente << endl;
    cout << "ID Participante: " << p.id << endl;
    cout << "Nombres: " << p.apellido << ", " << p.primer_nombre << ", " << p.segundo_nombre << endl;
    cout << "Suma de lenguajes programacion: " <<  p.etapa2.lenguajes_pro << endl;
    cout << "Suma de experiencia: " <<  p.etapa2.experiencia << endl;
    cout << "Suma de proyectos finalizados: " << p.etapa2.proyectos_finalizados << endl;
    cout << "Suma de proyectos en ejecucion: " << p.etapa2.proyectos_en_ejecucion << endl;
    cout << "Suma de proyectos liderados: " <<  p.etapa2.proyectos_liderados << endl;

    cout << "\nPuntaje Total en Etapa 2: " <<  p.etapa2.suma_total << endl;
    cout << "---" << endl;
}

void administracion_etapa_2(v_participantes &participantes, int ocup_participantes, bool ctr_1erEtapa, bool &ctr_2daEtapa)
{

    int op, valor;

    do
    {
        system("cls");
        menu_segunda_etapa(op);
        switch (op)
        {
        case 1:
            system("cls");
            //validar todos los campos y luego mostrar clasificacion 1er etapa

            if(!ctr_1erEtapa)
                cout << "\nDebe ejecutar la primera etapa...\n" << endl;
            else
            {
                ctr_2daEtapa = true;
                cout << "--Clasificacion 2da Etapa--" << endl;
                Evaluacion_2da_ETAPA(participantes, ocup_participantes);
            }
            system("pause");
            break;
        case 2:
            system("cls");
            if(ctr_1erEtapa == true && ctr_2daEtapa == true)
            {
                cout << "--Consultar Puntaje Participante--" << endl;
                cout << "Ingrese ID de participante a consultar: ";
                cin >> valor;
                consultar_participante(participantes, ocup_participantes, valor, 2);
            }
            else
            {
                cout << "\nPrimero debe realizar la primer etapa clasificar las 20 mejores de 2da etapa.\n" << endl;
            }
            system("pause");
            break;
        case 3:
            break;

        default:
            cout << "Opción inválida" << endl;
            system("pause");
            break;
        }
    }
    while (op != 3);
}

void Evaluacion_2da_ETAPA(v_participantes &listaPriEtapa, int ocup_selec)
{

    // v_proyectos-->> |0: finalizados| 1: ejecucion | 2: liderados (finalizados + ejecucion)|

    int i;

    for(i = 0; i <= ocup_selec; i++) //recorrer la lista de participantes de la 1er etapa (las 20 mejores).
    {
        if(listaPriEtapa[i].proyectos[2] > 0) //controla que tenga liderados para poder aplicar la formula.
        {
            listaPriEtapa[i].etapa2.proyectos_liderados = listaPriEtapa[i].proyectos[2]  / (listaPriEtapa[i].proyectos[0] + (listaPriEtapa[i].proyectos[1] * 1.0)) *  100;
        }
        else
        {
            listaPriEtapa[i].etapa2.proyectos_liderados = 0;
        }

        //clasificacion por la cantidad de lenguajes de programacion que conoce
        if(listaPriEtapa[i].cant_lenguajes_prog == 0)  //0
        {
            listaPriEtapa[i].etapa2.lenguajes_pro = 0;

        }
        else if((listaPriEtapa[i].cant_lenguajes_prog >= 1) && (listaPriEtapa[i].cant_lenguajes_prog <= 3)) //[1..3]
        {
            listaPriEtapa[i].etapa2.lenguajes_pro = 25;

        }
        else if((listaPriEtapa[i].cant_lenguajes_prog == 4) || (listaPriEtapa[i].cant_lenguajes_prog == 5)) //[4..5]
        {
            listaPriEtapa[i].etapa2.lenguajes_pro = 50;

        }
        else if((listaPriEtapa[i].cant_lenguajes_prog >= 6) && (listaPriEtapa[i].cant_lenguajes_prog <= 8)) //[6..8]
        {
            listaPriEtapa[i].etapa2.lenguajes_pro = 75;

        }
        else if((listaPriEtapa[i].cant_lenguajes_prog == 9) || (listaPriEtapa[i].cant_lenguajes_prog == 10)) //[9..10]
        {
            listaPriEtapa[i].etapa2.lenguajes_pro = 100;
        }

        //clasificacion por años de experiencia
        if(listaPriEtapa[i].anios_experiencia == 0) //0
        {
            listaPriEtapa[i].etapa2.experiencia = 0;

        }
        else if(listaPriEtapa[i].anios_experiencia >= 1 && listaPriEtapa[i].anios_experiencia <= 5) //[1..5]
        {
            listaPriEtapa[i].etapa2.experiencia = 25;

        }
        else if(listaPriEtapa[i].anios_experiencia >= 6 && listaPriEtapa[i].anios_experiencia <= 10) //[6..10]
        {
            listaPriEtapa[i].etapa2.experiencia = 50;

        }
        else if(listaPriEtapa[i].anios_experiencia >= 11 && listaPriEtapa[i].anios_experiencia <= 15) //[11..15]
        {
            listaPriEtapa[i].etapa2.experiencia = 75;

        }
        else if(listaPriEtapa[i].anios_experiencia >= 16 && listaPriEtapa[i].anios_experiencia <= 20) //[16..20]
        {
            listaPriEtapa[i].etapa2.experiencia = 100;
        }

        //clasificacion por cantidad de Proyectos finalizados
        if(listaPriEtapa[i].proyectos[0] == 0) //0
        {
            listaPriEtapa[i].etapa2.proyectos_finalizados = 0;

        }
        else if(listaPriEtapa[i].proyectos[0] >= 1 && listaPriEtapa[i].proyectos[0] <= 6) //[1..6]
        {
            listaPriEtapa[i].etapa2.proyectos_finalizados = 25;

        }
        else if(listaPriEtapa[i].proyectos[0] >= 7 && listaPriEtapa[i].proyectos[0] <= 12) //[7..12]
        {
            listaPriEtapa[i].etapa2.proyectos_finalizados = 50;

        }
        else if(listaPriEtapa[i].proyectos[0] >= 13 && listaPriEtapa[i].proyectos[0] <= 20) //[13..20]
        {
            listaPriEtapa[i].etapa2.proyectos_finalizados = 75;

        }
        else if(listaPriEtapa[i].proyectos[0] >= 21 && listaPriEtapa[i].proyectos[0] <= 25) //[21..25]
        {
            listaPriEtapa[i].etapa2.proyectos_finalizados = 100;
        }

        //clasificacion por cantidad de Proyectos en ejecucion
        if(listaPriEtapa[i].proyectos[1] == 0) 	//0
        {
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion = 0;

        }
        else if(listaPriEtapa[i].proyectos[1] == 1) //1
        {
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion = 25;

        }
        else if(listaPriEtapa[i].proyectos[1] == 2) //2
        {
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion = 50;

        }
        else if(listaPriEtapa[i].proyectos[1] == 3) //3
        {
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion = 75;

        }
        else if(listaPriEtapa[i].proyectos[1] == 4) //4
        {
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion = 100;
        }

        //Al finalizar se realiza la suma total del puntaje de cada categoria.
        listaPriEtapa[i].etapa2.suma_total =
            listaPriEtapa[i].etapa2.proyectos_liderados +
            listaPriEtapa[i].etapa2.lenguajes_pro +
            listaPriEtapa[i].etapa2.experiencia +
            listaPriEtapa[i].etapa2.proyectos_finalizados +
            listaPriEtapa[i].etapa2.proyectos_en_ejecucion;
    }

    Insercion_segunda(listaPriEtapa, ocup_selec); //ordenacion por suma total.

    for (i = 0; i <= ocup_selec; i++)
    {
        mostrar_Participante_etapa2(listaPriEtapa[i]); //muestra las 20 mejores con orden decreciente.
    }
}

void Insercion_segunda(v_participantes &v, int ocup)
{
    int i, j;
    t_participante aux; //registro

    for(i = 1; i <= ocup; i++)
    {
        aux = v[i];
        j = i - 1;

        while((j >= 0) && (v[j].etapa2.suma_total < aux.etapa2.suma_total)) //decreciente (vec[j]<aux).
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

//------------------------------------------>>>CORONACION<<<---------------------------------------------------------------------------------------------------
void mostrar_Participante_Coronacion(t_participante p )
{
    cout << "Continente: " << p.continente << endl;
    cout << "ID Participante: " << p.id << endl;
    cout << "Nombres: " << p.apellido << ", " << p.primer_nombre << ", " << p.segundo_nombre << endl;
    cout << "Puntaje total primer etapa: " << p.etapa1.puntaje_total << endl;
    cout << "Puntaje total segunda etapa: " << p.etapa2.suma_total << endl;

    cout << "\nPuntaje Total Coronacion: " <<  p.puntaje_Coronacion << endl;
}

void administracion_coronacion(v_participantes &participantes, int ocup_participantes, v_finalistas &finalistas, int &ocup_finalistas, bool ctrCoronacion)
{
    bool coronar = false;
    int op;
    do
    {
        system("cls");
        menu_coronacion(op);
        switch (op)
        {
        case 1:
            system("cls");
            if(!ctrCoronacion)
                cout << "\nDebe ejecutar la segunda etapa...\n" << endl;
            else
            {
                evaluacion_Coronacion(participantes, ocup_participantes, finalistas, ocup_finalistas);
                coronar = true;
            }
            system("pause");
            break;
        case 2:
            system("cls");
            if(coronar)
            {
                mostrar_finalistas(finalistas, ocup_finalistas);
            }
            else
            {
                cout << "\nDebe realizar coronacion..\n" << endl;
            }
            system("pause");
            break;
        case 3:
            break;
        default:
            cout << "Opción inválida" << endl;
            system("pause");
            break;
        }
    }
    while (op != 3);
}

//Evalua las 20 participantes de la 2da Etapa y aplica la formula de puntaje de la coronacion
void evaluacion_Coronacion(v_participantes &listaPriEtapa, int ocup_selec, v_finalistas &listaFinalistas, int &ocup_Finalistas)
{

    int i;

    for(i = 0; i <= ocup_selec; i++)
    {
        listaPriEtapa[i].puntaje_Coronacion = 0;
        listaPriEtapa[i].puntaje_Coronacion = (listaPriEtapa[i].etapa1.puntaje_total * 0.33) + (listaPriEtapa[i].etapa2.suma_total * 0.67);
    }
    guardar_finalistas(listaPriEtapa, ocup_selec, listaFinalistas, ocup_Finalistas); //se obtiene las 5 mejores y se guarda en la lista de finalistas.
    mostrar_finalistas(listaFinalistas, ocup_Finalistas);
}

void Insercion_coronacion(v_participantes &v, int ocup)
{
    int i, j;
    t_participante aux; //registro

    for(i = 1; i <= ocup; i++)
    {
        aux = v[i];
        j = i - 1;

        while((j >= 0) && (v[j].puntaje_Coronacion < aux.puntaje_Coronacion)) //decreciente (vec[j]<aux).
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void guardar_finalistas(v_participantes &lista_2da_etapa, int ocup_2da_etapa, v_finalistas &finalistas, int &ocup_finalistas)
{
    int i;
    //ordena los participantes por resultado final
    Insercion_coronacion(lista_2da_etapa, ocup_2da_etapa);
    for(i = 0; i <= 5; i++)
    {
        ocup_finalistas++;
        finalistas[ocup_finalistas] = lista_2da_etapa[i];
    }
}

void mostrar_finalistas(v_finalistas finalistas, int &ocup_finalistas)
{
    int i;

    cout << "\n**************************\n";
    cout << "*    LA GANADORA ES...      *" << endl;;
    mostrar_Participante_Coronacion(finalistas[0]);
    cout << "\n**************************\n" << endl;


    cout << "\n**************************\n";
    cout << "*   LAS FINALISTAS SON...   *" << endl;;
    for(i = 1; i <= 4; i++)
    {

        cout << i << ") LUGAR" << endl;
        mostrar_Participante_Coronacion(finalistas[i]);
        cout << "\n**************************\n" << endl;
    }
}

//Fin del programa...... :)
