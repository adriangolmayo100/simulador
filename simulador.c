// Juego de instrucciones. código de operación
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARCHIVO_INSTRUCCIONES "file.txt"

#define MAX_BUFF 32
#define add 1
#define sub 2
#define ld 3
#define sd 4
#define mult 5

// Capacidad de las estructuras de almacenamiento es ilimitada pero se pone un máximo
#define REG 16 /* Número de registros */
#define DAT 32 /* Tamaño de memoria de datos */
#define INS 32 /* Tamaño de memoria de instrucciones */

/*Códigos para las UF */
#define TOTAL_UF 3 /* total de UF simuladas */
#define ALU 0      /* código para una UF de suma/resta */
#define MEM 1      /* código para UF de carga/almacenamiento */
#define MULT 2     /* código para UF de multiplicación */

/*Ciclos de ejecución de UF */
#define CICLOS_MEM 3  /* Carga y almacenamiento */
#define CICLOS_ALU 2  /* Suma y Resta */
#define CICLOS_MULT 5 /* Multiplicación */

/*Etapas de procesamiento de las instrucciones en ROB*/
#define ISS 1 /* Instruccion emitida*/
#define EX 2  /* Instruccion en ejecucion EX*/
#define WB 3  /* Fase WB realizada */

/* Estructuras de datos */ // Instrucción
typedef struct
{                  /* Codificación Instrucción */
    int cod;       /* operación a realizar */
    int rd;        /* registro destino */
    int rs;        /* registro fuente op1 */
    int rt;        /* registro fuente op2 */
    int inmediato; /* Dato inmediato */
} instruccion_t;

typedef struct
{                    /*Registro del banco de registros */
    int contenido;   /* contenido */
    int ok;          /* contenido valido (1) o no (0)*/
    int clk_tick_ok; /* ciclo de reloj cuando se valida ok. */
    int TAG_ROB;     /* Si ok es 0, etiqueta de la línea de ROB donde está almacenada la instrucción que lo actualizará. */
    /* Almacena la última */
} reg_t;

typedef struct
{                      /* Línea de una estación de reserva*/
    int busy;          /* contenido de la línea válido (1) o no (0) */
    int operacion;     /* operación a realizar en UF (suma,resta,mult,lw,sw) */
    int opa;           /* valor Vj*/
    int opa_Q;         /* Qj, 0 es dato válido, otro número es la línea de ROB dónde se obtiene el dato */
    int clk_tick_ok_a; /* ciclo de reloj donde se valida opa_Q */
    int opb;           /* Valor Vk */
    int opb_Q;         /* Qk, 0 es dato válido, otro número es la línea de ROB dónde se obtiene el dato */
    int clk_tick_ok_b; /* ciclo de reloj se valida donde opb_Q */
    int inmediato;     /*utilizado para las instrucciones lw/sw */
    int TAG_ROB;       /* etiqueta de la línea del ROB donde se ha almacenado esta instrucción */
} ER_t;

typedef struct
{                    /* Línea de ROB */
    int TAG_ROB;     /* Etiqueta que identifica la línea de ROB */
    int instruccion; /* tipo de instrucción */
    int busy;        /* Indica si el contenido de la línea es válido (1) o no (0) */
    int destino;     /* identificador registro destino (rd) */
    int valor;       /* resultado tras finalizar la etapa EX */
    int valor_ok;    /* indica si valor es válido (1) o no (0) */
    int clk_tick_ok; /* ciclo de reloj cuando se valida valor_ok */
    int etapa;       /* Etapa de procesamiento de la instrucción ISS, EX, WB */
} ROB_t;

typedef struct
{                    /* Simula el funcionamiento de una UF */
    int uso;         /* Indica si UF está utilizada (1) o no (0) */
    int cont_ciclos; /* indica ciclos consumidos por la UF */
    int TAG_ROB;     /* Línea del ROB donde se tiene que almacenar el resultado tras EX */
    int opa;         /* valor opa (en sd contiene dato a escribir en memoria */
    int opb;         /* valor opb (en ld y sd contiene dirección de memoria de datos ) */
    int operacion;   /* se utiliza para indicar operacion a realizar add/sub y lw/sw o mult */
    int res;         /* resultado */
    int res_ok;
    /* resultado valido(1) */
    int clk_tick_ok; /* ciclo de reloj cuando se valida res_ok */
} UF_t;

// Declaración de las variables que simulan la memoria de datos, de instrucciones y banco de registros.
// Serán vectores
int p_rob_cabeza = 1, p_rob_cola = 1; /* puntero a las posiciones de rob para introducir (cola) o retirar instrucciones (cabeza) */
int PC = 0;                           /* puntero a memoria de instrucciones, siguiente instrucción a IF */

int p_er_cola[TOTAL_UF] = {0, 0, 0};      // vector de punteros que apuntan a la cola de cada una de las UF (
int ciclo = 1;                            // ciclo de ejecución actual
reg_t banco_registros[REG];               /* Banco de registros */
int memoria_datos[DAT];                   /* Memoria de datos */
instruccion_t memoria_instrucciones[INS]; /* Memoria de instrucciones */
UF_t UF[TOTAL_UF];                        /* 3 UF: UF[0] simula la ALU, UF[1] carga/almacenamiento y UF[2] multiplicación */
ER_t ER[TOTAL_UF][INS];                   /* Vector de estaciones de reserva ER[0] para ALU, ER[1] para MEM y ER[2] para MULT */
                                          /* INS indica el total de instrucciones que puede almacenar cada ER_t */
ROB_t ROB[INS + 1];                       /* Bufer de reordenamiento */
int inst_restantes = 0;                   /* instrucciones restante para acabar el programa */
int inst_prog = 0;                        /* total de instrucciones programas*/
int inst_rob = 0;                         /* instrucciones en rob */

void Inicializar_ER(ER_t ER[][INS])
{
    int i = 0, j = 0;
    for (i = 0; i < TOTAL_UF; i++)
    {
        for (j = 0; j < INS; j++)
        {
            ER[i][j].busy = 0;          /* contenido de la línea válido (1) o no (0) */
            ER[i][j].operacion = 0;     /* operación a realizar en UF (suma,resta,mult,lw,sw) */
            ER[i][j].opa = 0;           /* valor Vj*/
            ER[i][j].opa_Q = 0;         /* Qj, 0 es dato válido, otro número es la línea de ROB dónde se obtiene el dato */
            ER[i][j].clk_tick_ok_a = 0; /* ciclo de reloj donde se valida opa_Q */
            ER[i][j].opb = 0;           /* Valor Vk */
            ER[i][j].opb_Q = 0;         /* Qk, 0 es dato válido, otro número es la línea de ROB dónde se obtiene el dato */
            ER[i][j].clk_tick_ok_b = 0; /* ciclo de reloj se valida donde opb_Q */
            ER[i][j].inmediato = 0;     /*utilizado para las instrucciones lw/sw */
            ER[i][j].TAG_ROB = 0;
        }
    }
}
void Inicializar_ROB(ROB_t ROB[])
{
    int i;
    for (i = 1; i < INS + 1; i++)
    {
        ROB[i].TAG_ROB = i;
        ROB[i].instruccion = 0;
        ROB[i].busy = 0;
        ROB[i].destino = 0;
        ROB[i].valor = 0;
        ROB[i].valor_ok = 0;
        ROB[i].clk_tick_ok = 0;
        ROB[i].etapa = 0;
    }
}
void Inicializar_Banco_registros(reg_t banco_registros[])
{
    int i;
    for (i = 0; i < REG; i++)
    {
        banco_registros[i].TAG_ROB = 0;
        banco_registros[i].ok = 1;
        banco_registros[i].clk_tick_ok = 0;
        banco_registros[i].contenido = i * 10;
    }
}
void Inicializar_memoria_datos(int memoria_datos[])
{
    int i;
    for (i = 0; i < DAT; i++)
    {
        memoria_datos[i] = (i + 1) * 2;
    }
}
void Etapa_commit()
{
    ROB_t rob_, nuevo_rob;

    rob_ = ROB[p_rob_cabeza]; // instrucción a eliminar de ROB
    if ((rob_.busy == 1) && (rob_.etapa == WB) && (rob_.valor_ok == 1) && (rob_.clk_tick_ok < ciclo))
    {
        // instrucción preparada para retirar
        // Actualizar el registro rob_.destino con rob_.valor, si rob_.TAG_ROB coincide con la etiqueta almacenada en ese registro destino.
        // Si rob_.operacion es store, escribir en memoria en la dirección rob_.destino el valor de rob_.valor
        // Retirar instrucción de ROB: Actualizar puntero de cabecera y número de instrucciones en rob (en store solo hace esto)
        // Limpiar línea ROB. Poner línea todo a 0

        // Actualización de los registros.
        if (rob_.instruccion == sd)
        {
            memoria_datos[rob_.destino] = rob_.valor;
        }
        else if (rob_.TAG_ROB == banco_registros[rob_.destino].TAG_ROB)
        {
            banco_registros[rob_.destino].contenido = rob_.valor;
            banco_registros[rob_.destino].ok = 1;
            banco_registros[rob_.destino].TAG_ROB = 0;
            banco_registros[rob_.destino].clk_tick_ok = 0;
        }

        // Borrado de la línea del ROB
        nuevo_rob.TAG_ROB = 0;
        nuevo_rob.instruccion = 0;
        nuevo_rob.busy = 0;
        nuevo_rob.destino = 0;
        nuevo_rob.valor = 0;
        nuevo_rob.valor_ok = 0;
        nuevo_rob.clk_tick_ok = 0;
        nuevo_rob.etapa = 0;

        ROB[p_rob_cabeza++] = nuevo_rob;
        inst_rob--;
    }
}

void Etapa_WB()
{
    // Objetivo:
    // 1. Se busca el primer resultado válido en una unidad funcional y se escribe en ROB.
    // Un resultado es válido si el campo de la UF, UF[i].res_ok está a 1 y UF[i].clk_tick_ok
    // contiene un valor inferior al ciclo actual.
    // Si esas condiciones se cumplen se puede ejecutar la etapa WB que conlleva
    // * La línea de ROB que se tiene que actualizar está en el campo de la UF, UF[i].TAG_ROB :
    // ROB[UF[i].TAG_ROB].valor = UF[i].res
    // ROB[UF[i].TAG_ROB].valor_ok = 1
    // ROB[UF[i].TAG_ROB].destino = UF[i].op_a (solo en store)
    // ROB[UF[i].TAG_ROB].clk_tick_ok = ciclo (este operando se podrá utilizar en el ciclo siguiente en el que nos encontramos
    // ROB[id].etapa = WB
    // * Se deja libre UF. Se pone todo a 0
    // La ventaja de ejecutar WB antes que EX es que si la etapa WB escribe un resultado, libera la UF que estaba ocupando y así la etapa EX en este mismo
    // ciclo puede iniciar otra operación del mismo tipo.
    // 2. Se actualizan todas las líneas de las ER que esperen ese dato.
    // Se tienen que recorrer todas las líneas válidas de todas las estaciones de reserva y aquellos operandos que dependan
    // de ese resultado se tienen que actualizar.
    // *Estos son los operandos cuyos campos opa_Q y opb_Q estén a 0 y en los campos opa y opb tiene un valor igual al de
    // UF[i].TAG_ROB:
    // *en el campo opa/opb se pone UF[i].res y en opa_Q/opb_Q se pone un 1
    // *en el campo clk_tick_ok_a y clk_tick_ok_b se actualiza ciclo
    // Si no hay ninguno resultado disponible, no se hace nada
    int i = 0, j = 0;   // contador de unidades funcionales
    int fin, bucle = 0; // controla salir del bucle cuando encuentra un resultado valido. Solo WB un resultado

    // Estructuras nuevas:
    ROB_t n_ROB;
    UF_t n_UF;
    ER_t n_ER;

    while (!bucle && i < TOTAL_UF)
    {
        n_UF = UF[i];
        // busca resultado valido en todas las UF. El primero que encuentra lo escribe en ROB y actualiza ER
        if (n_UF.uso == 1 && n_UF.res_ok == 1 && n_UF.clk_tick_ok < ciclo)
        {
            n_ROB = ROB[n_UF.TAG_ROB];
            /*          Modificado Antonio:
                        ROB[UF[i].TAG_ROB].valor = UF[i].res;
                        ROB[UF[i].TAG_ROB].valor_ok = 1;
                        ROB[UF[i].TAG_ROB].clk_tick_ok = ciclo;
            */
            n_ROB.valor = UF[i].res;
            n_ROB.valor_ok = 1;
            n_ROB.clk_tick_ok = ciclo;
            n_ROB.etapa = WB;

            if (n_ROB.instruccion == sd)
            {
                n_ROB.valor = UF[i].opa;   // El valor a almacenar en memoria esta en OpB
                n_ROB.destino = UF[i].res; // La dirección calculada se almacena en destino
            }

            // Actualiza linea ROB, x=ROB.UF[i].TAG_ROB con
            // ALU, ld: ROB[x].valor = UF[i].res y se valida con el resto de campos de ROB
            // sd: ROB.destino =UF[i].opb y ROB[x].valor = opb y se valida en el resto de campos de ROB
            //  Dejar libre UF. Poner todo a 0s
            ROB[n_UF.TAG_ROB] = n_ROB;

            // se ha escrito un dato. No se pueden escribir más.
            bucle = 1; // no habrá más iteraciones del bucle
                       // actualizar estaciones de reserva donde hay líneas que esperan ese resultado.
                       // bucle para recorrer todas las ER

            int h;
            for (h = 0; h < TOTAL_UF; h++) // Hay que recorrer todas las ER buscando posibles dependencias
            {
                fin = p_er_cola[h]; // puntero al final de la ER
                for (j = 0; j < fin; j++)
                {
                    // una iteración por línea de ER ocupada de ER[k]. Siempre empieza en 0 (posibilidad de que no sea así)
                    // Si operando depende de ese resultado
                    n_ER = ER[h][j];
                    if (n_ER.busy)
                    {
                        // si la línea está ocupada.

                        if ((n_ER.opa_Q == UF[i].TAG_ROB))
                        {
                            n_ER.opa = ROB[UF[i].TAG_ROB].valor;
                            n_ER.opa_Q = 0;
                            /*
                                                    ER[i][j].opa = ROB[UF[i].TAG_ROB].valor;
                                                    ER[i][j].opa_Q == 1;
                            */

                            UF[i] = n_UF;
                            ER[h][j] = n_ER;
                        }
                        if (n_ER.opb_Q == UF[i].TAG_ROB)
                        {
                            n_ER.opb = ROB[UF[i].TAG_ROB].valor;
                            n_ER.opb_Q = 0;
                            /*
                                                    ER[i][j].opb = ROB[UF[i].TAG_ROB].valor;
                                                    ER[i][j].opb_Q == 1;
                            */
                            UF[i] = n_UF;
                            ER[h][j] = n_ER;
                        } // opb

                    } // fin for líneas ER
                }     // end for todas ER
            }         // end for todas UF
            n_UF.uso = 0;
            n_UF.cont_ciclos = 0;
            n_UF.opa = 0;
            n_UF.opb = 0;
            n_UF.operacion = 0;
            n_UF.res = 0;
            n_UF.res_ok = 0;
            n_UF.clk_tick_ok = 0;
            n_UF.TAG_ROB = 0;
            // Actualización de los structs
            UF[i] = n_UF;
        }
        i++;
    } // while todas UFs
}

void Etapa_EX()
{
    // En todas las UF:
    // 1. En todas las UF que están en uso:
    // * Incremento un ciclo de operación.
    // * Si es el último: generar resultado y almacenarlo en UF[i].res, validarlo y actualizar ciclo
    // 2. Si alguna está libre: Enviar una nueva instrucción a ejecutar si hay instrucción disponible de ese tipo
    // * Se busca una instrucción que tenga los operandos disponibles en su ER
    // * Solo se puede enviar una instrucción
    // Instrucción ALU y ld: inicializa la UF, carga operandos.
    // Instrucción sd: Actualiza UF, calculando la dirección destino en opa y genera el resultado que es el opb. Cont_ciclos lo pone a max.
    // Dato se escribe en memoria en etapa Commit.
    // *Se libera la línea de la ER de la instrucción enviada a ejecutar.
    // Consideración: en esta plantilla no se tiene en cuenta las líneas libres de las ERs no ocupadas.

    int contador_unidad_funcional = 0; // contador unidades funcionales
    int enviar = 0;                    // no se ha enviado ninguna instrucción a ejecutar
    int max;
    int j, fin;
    UF_t unidad;
    ER_t *estacionR;
    // ALU 0, MEN 1, MULT 2
    while (contador_unidad_funcional < TOTAL_UF)
    {
        // revisa todas las UFs. Si está en uso, Incrementa ciclo.
        // Si es el último, generar resultado y validarlo. si no envía una instrucción a ejecutar (si la hay de ese tipo).
        unidad = UF[contador_unidad_funcional];

        // Establecer ciclos máximos para cada UF
        if (contador_unidad_funcional == 0)
            max = CICLOS_ALU;
        else if (contador_unidad_funcional == 1)
            max = CICLOS_MEM;
        else if (contador_unidad_funcional == 2)
            max = CICLOS_MULT;

        if (unidad.uso)
        {                         // si está en uso, se incrementa el ciclo y no se pueden enviar otra instrucción.
            unidad.cont_ciclos++; // Se incrementa siempre el contador de ciclos porque la última instrucción cuenta también
            if (unidad.cont_ciclos >= max)
            {
                unidad.res_ok = 1;
                if (contador_unidad_funcional == MULT)
                    unidad.res = unidad.opa * unidad.opb;
                else if (contador_unidad_funcional == ALU)
                    if (unidad.operacion == add)
                        unidad.res = unidad.opa + unidad.opb;
                    else
                        unidad.res = unidad.opa - unidad.opb;
                else if (unidad.operacion == ld)
                {
                    unidad.res = memoria_datos[unidad.opa];
                }
                else                         // sd
                    unidad.res = unidad.opb; // Opb contiene la suma del valor de registro más inmediato, en OpB contiene el dato a almacenar
            }
            UF[contador_unidad_funcional] = unidad;
        }
        contador_unidad_funcional++;
    }
    // Buscar en ER MEM
    estacionR = ER[1];
    unidad = UF[1];
    fin = p_er_cola[1];
    j = 0;
    max = CICLOS_MEM;
    UF_t uf_nueva = UF[1];
    while ((!enviar) && (j < fin) && !uf_nueva.uso)
    {
        if (estacionR[j].busy)
        {
            if (((estacionR[j].operacion == sd)) && ((!estacionR[j].opa_Q) && (estacionR[j].clk_tick_ok_a < ciclo)) && (!estacionR[j].opb_Q) && (estacionR[j].clk_tick_ok_b < ciclo))
            {
                unidad.cont_ciclos = 1;
                unidad.res = 0;
                unidad.uso = 1;
                estacionR[j].inmediato = estacionR[j].opb + estacionR[j].inmediato; // Algoritmo de Tomasuno dice que dicho campo se hace: RS[r].A RS[r].Vj + RS[r].A;
                unidad.opb = estacionR[j].inmediato;
                unidad.opa = estacionR[j].opa;
                unidad.TAG_ROB = estacionR[j].TAG_ROB;
                unidad.operacion = estacionR[j].operacion;
                unidad.clk_tick_ok = ciclo + max - 1;
                ROB[estacionR[j].TAG_ROB].clk_tick_ok = unidad.clk_tick_ok;
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                enviar = 1;
                estacionR[j].busy = 0;
                estacionR[j].clk_tick_ok_a = 0;
                estacionR[j].clk_tick_ok_b = 0;
                estacionR[j].inmediato = 0;
                estacionR[j].opa = 0;
                estacionR[j].opa_Q = 0;
                estacionR[j].opb = 0;
                estacionR[j].opb_Q = 0;
                estacionR[j].operacion = 0;
                estacionR[j].TAG_ROB = 0;
            }
            else if (((estacionR[j].operacion == ld)) && ((!estacionR[j].opa_Q) && (estacionR[j].clk_tick_ok_a < ciclo)))
            {

                // int sd_en_rob = 0;
                // int x;
                // while (x < INS && !sd_en_rob)
                //     if (ROB[x++].instruccion == sd)
                //         sd_en_rob++;

                // if (sd_en_rob)
                // {
                //     unidad.res = ROB[x].valor;
                //     unidad.cont_ciclos = max;
                // }
                unidad.cont_ciclos = 1;
                unidad.res = 0;
                unidad.uso = 1;
                unidad.TAG_ROB = estacionR[j].TAG_ROB;
                unidad.operacion = estacionR[j].operacion;
                estacionR[j].inmediato = estacionR[j].opa + estacionR[j].inmediato; // Algoritmo de Tomasuno dice que dicho campo se hace: RS[r].A RS[r].Vj + RS[r].A;
                unidad.opa = estacionR[j].inmediato;
                unidad.clk_tick_ok = ciclo + max - 1; // Ciclo actual + coste en ciclos - 1. El -1 es porque el propio ciclo que se manda a ejecución cuenta.
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                ROB[estacionR[j].TAG_ROB].clk_tick_ok = unidad.clk_tick_ok;
                unidad.opb = estacionR[j].opb;
                banco_registros[ROB[estacionR[j].TAG_ROB].destino].clk_tick_ok = unidad.clk_tick_ok;
                enviar = 1;
                estacionR[j].busy = 0;
                estacionR[j].clk_tick_ok_a = 0;
                estacionR[j].clk_tick_ok_b = 0;
                estacionR[j].inmediato = 0;
                estacionR[j].opa = 0;
                estacionR[j].opa_Q = 0;
                estacionR[j].opb = 0;
                estacionR[j].opb_Q = 0;
                estacionR[j].operacion = 0;
                estacionR[j].TAG_ROB = 0;
                unidad.cont_ciclos = 1;
            }
            UF[1] = unidad;
        }
        j++;
    }
    // Buscamos la ER de ALU:
    estacionR = ER[0];
    fin = p_er_cola[0];
    j = 0;
    max = CICLOS_ALU;
    uf_nueva = UF[0];
    while ((!enviar) && (j < fin) && !uf_nueva.uso)
    {
        if (estacionR[j].busy)
        {
            if (!estacionR[j].opa_Q && estacionR[j].clk_tick_ok_a < ciclo && !estacionR[j].opb_Q && estacionR[j].clk_tick_ok_b < ciclo)
            { // Operandos disponibles
                // Mandamos la instrucción a ejecutar, actualizando la UF
                uf_nueva.cont_ciclos = 1;
                uf_nueva.opa = estacionR[j].opa;
                uf_nueva.opb = estacionR[j].opb;
                uf_nueva.res_ok = 0;
                uf_nueva.res = 0;
                uf_nueva.uso = 1;
                uf_nueva.TAG_ROB = estacionR[j].TAG_ROB;
                uf_nueva.operacion = estacionR[j].operacion;
                uf_nueva.clk_tick_ok = ciclo + max - 1; // Ciclo actual + coste en ciclos - 1. El -1 es porque el propio ciclo que se manda a ejecución debe tenerse en cuenta.
                banco_registros[ROB[estacionR[j].TAG_ROB].destino].clk_tick_ok = uf_nueva.clk_tick_ok;
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                ROB[estacionR[j].TAG_ROB].clk_tick_ok = uf_nueva.clk_tick_ok;
                enviar = 1;
                estacionR[j].busy = 0;
                estacionR[j].clk_tick_ok_a = 0;
                estacionR[j].clk_tick_ok_b = 0;
                estacionR[j].inmediato = 0;
                estacionR[j].opa = 0;
                estacionR[j].opa_Q = 0;
                estacionR[j].opb = 0;
                estacionR[j].opb_Q = 0;
                estacionR[j].operacion = 0;
                estacionR[j].TAG_ROB = 0;
                UF[0] = uf_nueva;
            }
        }
        j++;
    }

    // Buscar en ER MULT
    estacionR = ER[2];
    fin = p_er_cola[2];
    j = 0;
    max = CICLOS_MULT;
    uf_nueva = UF[2];
    while ((!enviar) && (j < fin) && !uf_nueva.uso)
    {
        if (estacionR[j].busy)
        {
            if (!estacionR[j].opa_Q && estacionR[j].clk_tick_ok_a < ciclo && !estacionR[j].opb_Q && estacionR[j].clk_tick_ok_b < ciclo)
            { // Operandos disponibles
                UF_t uf_nueva;
                uf_nueva.cont_ciclos = 1;
                uf_nueva.opa = estacionR[j].opa;
                uf_nueva.opb = estacionR[j].opb;
                uf_nueva.res_ok = 0;
                uf_nueva.res = -1;
                uf_nueva.uso = 1;
                uf_nueva.TAG_ROB = estacionR[j].TAG_ROB;
                uf_nueva.operacion = estacionR[j].operacion;
                uf_nueva.clk_tick_ok = ciclo + max - 1; // Ciclo actual + coste en ciclos - 1. El -1 es porque el propio ciclo que se manda a ejecución cuenta.
                banco_registros[ROB[estacionR[j].TAG_ROB].destino].clk_tick_ok = uf_nueva.clk_tick_ok;
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                ROB[estacionR[j].TAG_ROB].clk_tick_ok = uf_nueva.clk_tick_ok;
                enviar = 1;
                estacionR[j].busy = 0;
                estacionR[j].clk_tick_ok_a = 0;
                estacionR[j].clk_tick_ok_b = 0;
                estacionR[j].inmediato = 0;
                estacionR[j].opa = 0;
                estacionR[j].opa_Q = 0;
                estacionR[j].opb = 0;
                estacionR[j].opb_Q = 0;
                estacionR[j].operacion = 0;
                estacionR[j].TAG_ROB = 0;
                UF[2] = uf_nueva;
            }
        }
        j++;
    }
}
void Etapa_ID_ISS()
{
    // 1.- Lee una instrucción de la directamente de la memoria de instrucciones y la inserta en la ER correspondiente.
    //  instrucción apuntada por PC: inst = memoria_instrucciones[PC]
    //  2.- Identifica el tipo de instrucción y selecciona la ER para insertarla. Será función del código de operación de la instrucción
    //  Si inst.cod == 1 o 2 → tipo =ALU
    //  Si inst.cod == 3 o 4 → tipo = MEM
    //  SI inst.cod == 4 → tipo = MULT
    //
    // 3.- Añadir instrucción en ROB en la posición indicada en p_rob_cola. Actualiza todos sus campos
    //  Actualiza p_rob_cola + 1
    //  4.- Utiliza el puntero p_er_cola(tipo) que apunta a la cola de ER[tipo] para almacenarla en esa posición.
    //  Actualiza todos sus campos:
    //  * opa y opb. Busca en registros rs y rt
    //  * Si el campo ok de esos registros está a 1 y clk_tick_ok es menor que el ciclo actual,
    //  se carga su contenido en los campos opa y opb de la ER, se validan y se actualiza el ciclo (operandos válidos)
    //  * En caso contrario se carga en opa y/o opb el campo TAG_ROB de esos registros, y no se validan (operandos no válidos)
    //  *Etiqueta de la línea de ROB donde ha almacenado la instrucción.
    //  *Actualizar p_er_cola[tipo] + 1
    // 4.- Invalidar contenido del registro destino poniendo campo ok a 0 y en TAG_ROB la línea de ROB donde se ha almacenado dicha instrucción.
    // 5. Actualiza PC + 1 y inst_restantes - 1
    if (inst_restantes > 0)
    {
        // leer la instrucción apuntada por PC y almacenarla en ER y ROB
        instruccion_t inst = memoria_instrucciones[PC++];
        ROB_t linea_Rob = ROB[p_rob_cola];
        linea_Rob.TAG_ROB = p_rob_cola;
        linea_Rob.instruccion = inst.cod;
        linea_Rob.busy = 1;
        if (inst.cod == sd)
            linea_Rob.destino = -1; // -1, hasta que le demos valor, dado que es la dir de menmoria
        else
            linea_Rob.destino = inst.rd;
        linea_Rob.valor = 0;
        linea_Rob.valor_ok = 0;
        linea_Rob.etapa = ISS;
        // Añadir instrucción en ROB[p_rob_cola] y actualizar todos sus campos.
        // actualizar p_rob_cola + 1
        // Actualizar línea de la ER correspondiente según tipo de instrucción, ER[p_er_cola[tipo]], donde tipo se obtiene a partir del código de operación.
        int uf;
        int coste;
        switch (inst.cod)
        {
        case add:
        case sub:
            uf = ALU;
            coste = CICLOS_ALU;
            break;

        case mult:
            uf = MULT;
            coste = CICLOS_MULT;
            break;

        default:
            uf = MEM;
            coste = CICLOS_MEM;
            break;
        }
        linea_Rob.clk_tick_ok = -1;
        int index_RS = p_er_cola[uf]++;
        ER_t linea_ER = ER[uf][index_RS];
        linea_ER.busy = 1;
        linea_ER.operacion = inst.cod;
        linea_ER.opa = 0;
        linea_ER.opa_Q = 0;
        linea_ER.clk_tick_ok_a = 0;
        linea_ER.opb = 0;
        linea_ER.opb_Q = 0;
        linea_ER.clk_tick_ok_b = 0;
        linea_ER.inmediato = inst.inmediato;
        linea_ER.TAG_ROB = linea_Rob.TAG_ROB;

        //  p_er_cola[tipo] es el puntero que apunta a la línea donde se tiene que insertar la instrucción
        //  Todas las instrucciones excepto ld: buscar operandos a y b en registros y/o ROB. Load solo busca operando a
        int rob_rs = banco_registros[inst.rs].TAG_ROB;
        if (inst.cod == ld)
        {
            if (banco_registros[inst.rs].ok)
            {
                linea_ER.opa = banco_registros[inst.rs].contenido;
                linea_ER.opa_Q = 0; //
            }
            else
            {
                if (ROB[rob_rs].valor_ok)
                {
                    linea_ER.opa = ROB[rob_rs].valor;
                    linea_ER.opa_Q = 0;
                }
                else
                {
                    linea_ER.opa_Q = rob_rs;
                    linea_ER.clk_tick_ok_a = ROB[rob_rs].clk_tick_ok;
                }
            }
            linea_Rob.destino = inst.rt;
            banco_registros[inst.rt].ok = 0;
            banco_registros[inst.rt].clk_tick_ok = -1;
            banco_registros[inst.rt].TAG_ROB = p_rob_cola;
        }
        else
        {
            // Comprobar disponibilidad de operando RT
            int rob_rt = banco_registros[inst.rt].TAG_ROB;
            if (banco_registros[inst.rt].ok)
            {
                linea_ER.opa = banco_registros[inst.rt].contenido;
                linea_ER.opa_Q = 0;
            }
            else
            {
                if (ROB[rob_rt].valor_ok)
                {
                    linea_ER.opa = ROB[rob_rt].valor;
                    linea_ER.opa_Q = 0;
                }
                else
                {
                    linea_ER.opa_Q = rob_rt; // Almacenamos la línea que se encuentra el operando en ROB
                    linea_ER.clk_tick_ok_a = ROB[rob_rt].clk_tick_ok;
                }
            }

            // Comprobar disponibilidad de operando RS

            if (banco_registros[inst.rs].ok)
            {
                linea_ER.opb = banco_registros[inst.rs].contenido;
                linea_ER.opb_Q = 0;
            }
            else
            {
                if (ROB[rob_rs].valor_ok)
                {
                    linea_ER.opb = ROB[rob_rs].valor;
                    linea_ER.opb_Q = 0;
                }
                else
                {
                    linea_ER.opb_Q = ROB[rob_rs].TAG_ROB;
                    linea_ER.clk_tick_ok_b = ROB[rob_rs].clk_tick_ok;
                }
            }
            if (inst.cod != sd)
            {
                linea_Rob.destino = inst.rd;
                banco_registros[inst.rd].ok = 0;
                banco_registros[inst.rd].clk_tick_ok = -1;
                banco_registros[inst.rd].TAG_ROB = p_rob_cola;
            }
        }

        ER[uf][index_RS] = linea_ER;
        inst_restantes--;
        inst_rob++;
        ROB[p_rob_cola++] = linea_Rob;
        //  Si es válido, cargarlo en ER sino poner línea de ROB que proporcionará su valor cuando se ejecute la instrucción de quien dependey poner
        // operando no válido
        // Actualizamos registro destino (inst.rd) como no válido y línea de ROB donde está la instrucción que lo genera
        //  Actualizar PC para que apunte siguiente instrucción PC + 1 y el número de instrucciones leídas inst_restantes - 1
    }
}

int Carga_programa()
{
    /* strtok es utilizado como splitter para strings */
    // El formato del fichero no debe contener espacio entre los operandos
    FILE *archivo = fopen(ARCHIVO_INSTRUCCIONES, "r");
    char buff[MAX_BUFF];
    int instrucciones = 0;

    while (fgets(buff, MAX_BUFF, archivo))
    {                                          // Para cada linea de fichero
        char *linea = strtok(buff, "\n");      // Obtiene la linea de fichero
        char *tipo_s = strtok(linea, " ");     // Separamos el tipo de instruccion
        char *operandos_s = strtok(NULL, " "); // de los operandos
        int tipo = -1;                         // tipo de instruccion para anadir al struct

        instruccion_t instruccion;
        int isLoad; // variable para evitar una llamada a strcmp

        // instruccion del tipo carga o escritura
        if (!(isLoad = strcmp(tipo_s, "ld")) || !strcmp(tipo_s, "sd"))
        {
            if (!isLoad)
                tipo = ld;
            else
                tipo = sd;

            char *rt = strtok(operandos_s, ",");
            char *inm_y_rs = strtok(NULL, ",");

            char *inm = strtok(inm_y_rs, "(");
            char *rs = strtok(NULL, "(");

            int rt_int = atoi(&rt[1]);
            int rs_int = atoi(&rs[1]);
            int inm_int = atoi(inm);

            instruccion.rd = -1;
            instruccion.rs = rs_int;
            instruccion.rt = rt_int;
            instruccion.inmediato = inm_int;
        }
        else
        { // instruccion aritmetica
            //* No lleva f delante (fadd) porque son instrucciones de enteros
            if (!strcmp(tipo_s, "add"))
                tipo = add; // instruccion add
            else if (!strcmp(tipo_s, "sub"))
                tipo = sub; // instruccion sub
            else if (!strcmp(tipo_s, "mult"))
                tipo = mult; // instruccion mult

            char *rd = strtok(operandos_s, ",");
            char *rs = strtok(NULL, ",");
            char *rt = strtok(NULL, ",");

            int rd_int = atoi(&rd[1]);
            int rs_int = atoi(&rs[1]);
            int rt_int = atoi(&rt[1]);

            instruccion.rd = rd_int;
            instruccion.rs = rs_int;
            instruccion.rt = rt_int;
            instruccion.inmediato = 0;
        }

        instruccion.cod = tipo;
        memoria_instrucciones[instrucciones++] = instruccion;

        if (instrucciones == INS)
            break; // Descartamos las demas instrucciones
    }

    return instrucciones;
}

void imprime_memoria_inst()
{
    int i;
    printf("+------+-----+----+----+----+-------+\n");
    printf("| INST | COD | RT | RS | RD |  INM  |\n");
    printf("+------+-----+----+----+----+-------+\n");
    for (i = 0; i < inst_prog; i++) // cambio de mem_instrucciones por 6 (se come instrucciones por detras)
    {
        printf("| %4d | %3s | %2d | %2d | %2d | %5d |\n", i + 1,
               ((memoria_instrucciones[i].cod) == add ? "add" : (memoria_instrucciones[i].cod) == sub ? "sub"
                                                            : (memoria_instrucciones[i].cod) == ld    ? "ld"
                                                            : (memoria_instrucciones[i].cod) == sd    ? "sd"
                                                            : (memoria_instrucciones[i].cod) == mult  ? "mul"
                                                                                                      : "0"),
               memoria_instrucciones[i].rt, memoria_instrucciones[i].rs, memoria_instrucciones[i].rd, memoria_instrucciones[i].inmediato);
    }
    printf("+------+-----+----+----+----+-------+\n");

    // printf("INST\tCOD\tRT\tRS\tRD\tINM\n");
    // for (i = 0; i < INS; i++)
    // {
    //     printf("%d\t", i + 1);
    //     printf("%d\t", memoria_instrucciones[i].cod);
    //     printf("%d\t", memoria_instrucciones[i].rt);
    //     printf("%d\t", memoria_instrucciones[i].rs);
    //     printf("%d\t", memoria_instrucciones[i].rd);
    //     printf("%d\n", memoria_instrucciones[i].inmediato);
    // }
    // puts("***********************");
}
void imprime_memoria_datos()
{
    int i;
    printf("+------------------+\n");
    printf("| MEMORIA DE DATOS |\n");
    printf("+------------------+\n");
    for (i = 0; i < DAT; i++)
    {
        printf("| [%2d]  |  %7d |\n", i, memoria_datos[i]);
    }
    printf("+------------------+\n");

    //     for (i = 0; i < DAT; i++)
    //         printf("Memoria datos [%d]: %d\n", i, memoria_datos[i]);
    //     puts("***********************");
}

void imprime_rob()
{
    int i;
    printf("+-----+------+-------------+---------+-------+-------------+-------+----------+\n");
    printf("| TAG | BUSY | CLK_TICK_OK | DESTINO | ETAPA | INSTRUCCION | VALOR | VALOR_OK |\n");
    printf("+-----+------+-------------+---------+-------+-------------+-------+----------+\n");
    for (i = 1; i < inst_prog + 1; i++)
    {
        printf("| %3d | %4d | %11d | %7d | %5s | %11s | %5d | %8d |\n", ROB[i].TAG_ROB, ROB[i].busy, ROB[i].clk_tick_ok, ROB[i].destino,
               ((ROB[i].etapa) == ISS ? "ISS" : (ROB[i].etapa) == EX ? "EX"
                                            : (ROB[i].etapa) == WB   ? "WB"
                                                                     : "-1"),
               ((ROB[i].instruccion) == add ? "add" : (ROB[i].instruccion) == sub ? "sub"
                                                  : (ROB[i].instruccion) == ld    ? "ld"
                                                  : (ROB[i].instruccion) == sd    ? "sd"
                                                  : (ROB[i].instruccion) == mult  ? "mult"
                                                                                  : "0"),
               ROB[i].valor, ROB[i].valor_ok);
    }
    printf("+-----+------+-------------+---------+-------+-------------+-------+----------+\n");

    // printf("TAG\tBUSY\tCLK_TICK_OK\tDESTINO\tETAPA\tINSTRUCCION\tVALOR\tVALOR_OK\n");
    // for (i = 0; i < inst_restantes; i++)
    //     printf("%d\t%d\t%d\t\t%d\t%d\t%d\t\t%d\t%d\n", ROB[i].TAG_ROB, ROB[i].busy, ROB[i].clk_tick_ok, ROB[i].destino, ROB[i].etapa,
    //            ROB[i].instruccion, ROB[i].valor, ROB[i].valor_ok);

    // puts("***********************");
}
void imprime_ER()
{
    int i, j;
    for (i = 0; i < TOTAL_UF; i++)
    {
        printf("+-----------------------------------------------------------------+\n");
        printf("|Estacion %4s                                                    |\n", (i) == ALU ? "ALU" : (i) == MEM ? "MEM"
                                                                                                        : (i) == MULT  ? "MULT"
                                                                                                                       : "-1");
        printf("+---------+------+------+-------+-------+--------+--------+-------+\n");
        printf("| TAG_ROB |  OP  | BUSY |  OpA  |  OpB  | OpA_Qj | OpB_Qk |  INM  |\n");
        printf("+---------+------+------+-------+-------+--------+--------+-------+\n");
        for (j = 0; j < inst_prog; j++)
        {
            printf("| %7d | %4s | %4d | %5d | %5d | %6d | %6d | %5d |\n", ER[i][j].TAG_ROB,
                   ((ER[i][j].operacion) == add ? "add" : (ER[i][j].operacion) == sub ? "sub"
                                                      : (ER[i][j].operacion) == ld    ? "ld"
                                                      : (ER[i][j].operacion) == sd    ? "sd"
                                                      : (ER[i][j].operacion) == mult  ? "mult"
                                                                                      : "0"),
                   ER[i][j].busy, ER[i][j].opa, ER[i][j].opb, ER[i][j].opa_Q, ER[i][j].opb_Q, ER[i][j].inmediato);
        }
        printf("+---------+----+------+-------+-------+--------+----------+-------+\n");

        // for (j = 0; j < INS; j++)
        // {
        //     printf("TAG_ROB\tOP\tBUSY\tOpA\tCLK_OpA\tOpB\tCLK_OpB\topb_Q\topb_Q\tINM\n");
        //     printf("%d\t", ER[i][j].TAG_ROB);
        //     printf("%d\t", ER[i][j].operacion);
        //     printf("%d\t", ER[i][j].busy);
        //     printf("%d\t", ER[i][j].opa);
        //     printf("%d\t", ER[i][j].clk_tick_ok_a);
        //     printf("%d\t", ER[i][j].opb);
        //     printf("%d\t", ER[i][j].clk_tick_ok_b);
        //     printf("%d\t", ER[i][j].opa_Q);
        //     printf("%d\t", ER[i][j].opb_Q);
        //     printf("%d\n", ER[i][j].inmediato);
        // }
    }
}

void imprime_UF()
{
    int i;
    printf("+---------+-----+-----------+-------------+-------+-------+-------+-----------------+\n");
    printf("| TAG_ROB | USO | OPERACION | CONT_CICLOS |  OpA  |  OpB  |  RES  | RES_OK | CLK_OK |\n");
    printf("+---------+-----+-----------+-------------+-------+-------+-------+-----------------+\n");
    for (i = 0; i < TOTAL_UF; i++)
    {
        printf("| %7d | %3d | %9s | %11d | %5d | %5d | %5d | %6d | %6d |\n", UF[i].TAG_ROB, UF[i].uso,
               ((UF[i].operacion) == add ? "add" : (UF[i].operacion) == sub ? "sub"
                                               : (UF[i].operacion) == ld    ? "ld"
                                               : (UF[i].operacion) == sd    ? "sd"
                                               : (UF[i].operacion) == mult  ? "mult"
                                                                            : "0"),
               UF[i].cont_ciclos, UF[i].opa, UF[i].opb, UF[i].res, UF[i].res_ok, UF[i].clk_tick_ok);
    }
    printf("+---------+-----+-----------+-------------+-------+-------+-------+---------+-------+\n");

    // printf("TAG_ROB\tUSO\tOPERACION\tCONT_CICLOS\tOpA\tOpB\tRES\tRES_OK\n");
    // for (i = 0; i < TOTAL_UF; i++)
    // {
    //     printf("%d\t", UF[i].TAG_ROB);
    //     printf("%d\t", UF[i].uso);
    //     printf("%d\t", UF[i].operacion);
    //     printf("%d\t", UF[i].cont_ciclos);
    //     printf("%d\t", UF[i].opa);
    //     printf("%d\t", UF[i].opb);
    //     printf("%d\t", UF[i].res);
    //     printf("%d\n", UF[i].res_ok);
    // }
}

void imprime_Banco_registros()
{
    int i;
    printf("+-----+---------+-----+-----------+\n");
    printf("| Reg | TAG_ROB | OK  | CONTENIDO |\n");
    printf("+-----+---------+-----+-----------+\n");
    for (i = 0; i < REG; i++)
    {
        printf("| %3d | %7d | %3d | %9d |\n", i, banco_registros[i].TAG_ROB, banco_registros[i].ok, banco_registros[i].contenido);
    }
    printf("+-----+---------+-----+-----------+\n");

    // printf("TAG_ROB\tOK\tCLK_OK\tCONTENIDO\n");
    // for (i = 0; i < REG; i++)
    // {
    //     printf("%d\t", banco_registros[i].TAG_ROB);
    //     printf("%d\t", banco_registros[i].ok);
    //     printf("%d\t", banco_registros[i].clk_tick_ok);
    //     printf("%d\n", banco_registros[i].contenido);
    // }
}

void imprimeCPU()
{
    printf("Ciclo%d>\n", ciclo);
    printf("Memoria Instrucciones\n");
    imprime_memoria_inst();
    printf("Memoria Datos\n");
    imprime_memoria_datos();
    printf("Buffer de reordenamiento\n");
    imprime_rob();
    printf("Estaciones de reserva\n");
    imprime_ER();
    printf("Unidades funcionales\n");
    imprime_UF();
    printf("Banco de registros\n");
    imprime_Banco_registros();
    printf("Final ciclo %d: Instrucciones restantes en ROB: %d, Instucciones restantes del programa: %d\n", ciclo, inst_rob, inst_restantes);
    puts("\n\n");
}

int main(int argc, char *argv[])
{

    // Inicialización del simulador
    inst_restantes = inst_prog = Carga_programa();
    Inicializar_ER(ER);
    Inicializar_ROB(ROB);
    Inicializar_Banco_registros(banco_registros);
    Inicializar_memoria_datos(memoria_datos);

    while ((inst_rob > 0) || (inst_restantes > 0))
    {
        Etapa_commit();
        Etapa_WB();
        Etapa_EX();
        Etapa_ID_ISS();

        imprimeCPU();
        ciclo++;

    } // while
} // main

// MODIFICADO
/*

ETAPA ID_ISS:
  añadidos opa_Q y opb_Q
  cambiado los structs para que sí se actualicen.

ETAPA COMMIT y WB:
  cambiado la asignación de structs

*/