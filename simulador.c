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
#define ISS 1              /* Instruccion emitida*/
#define EX 2               /* Instruccion en ejecucion EX*/
#define WB 3               /* Fase WB realizada */
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
    int opa_ok;        /* Qj, (1) opa válido o no (0)*/
    int clk_tick_ok_a; /* ciclo de reloj donde se valida opa_ok */
    int opb;           /* Valor Vk */
    int opb_ok;        /* Qk, (1) válido o (0) no válido */
    int clk_tick_ok_b; /* ciclo de reloj se valida donde opb_ok */
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
int p_rob_cabeza, p_rob_cola = 0; /* puntero a las posiciones de rob para introducir (cola) o retirar instrucciones (cabeza) */
int PC = 0;                       /* puntero a memoria de instrucciones, siguiente instrucción a IF */

int p_er_cola[TOTAL_UF] = {0, 0, 0};      // vector de punteros que apuntan a la cola de cada una de las UF (
int ciclo = 1;                            // ciclo de ejecución actual
reg_t banco_registros[REG];               /* Banco de registros */
int memoria_datos[DAT];                   /* Memoria de datos */
instruccion_t memoria_instrucciones[INS]; /* Memoria de instrucciones */
UF_t UF[TOTAL_UF];                        /* 3 UF: UF[0] simula la ALU, UF[1] carga/almacenamiento y UF[2] multiplicación */
ER_t ER[TOTAL_UF][INS];                   /* Vector de estaciones de reserva ER[0] para ALU, ER[1] para MEM y ER[2] para MULT */
                                          /* INS indica el total de instrucciones que puede almacenar cada ER_t */
ROB_t ROB[INS];                           /* Bufer de reordenamiento */
int inst_prog;                            /* total instrucciones programa */
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
            ER[i][j].opa_ok = 0;        /* Qj, (1) opa válido o no (0)*/
            ER[i][j].clk_tick_ok_a = 0; /* ciclo de reloj donde se valida opa_ok */
            ER[i][j].opb = 0;           /* Valor Vk */
            ER[i][j].opb_ok = 0;        /* Qk, (1) válido o (0) no válido */
            ER[i][j].clk_tick_ok_b = 0; /* ciclo de reloj se valida donde opb_ok */
            ER[i][j].inmediato = 0;     /*utilizado para las instrucciones lw/sw */
            ER[i][j].TAG_ROB = 0;
        }
    }
}
void Inicializar_ROB(ROB_t ROB[])
{
    int i;
    for (i = 0; i < INS; i++)
    {
        ROB[i].TAG_ROB = 0;
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
        banco_registros[i].contenido = 0;
    }
}
void Inicializar_memoria_datos(int memoria_datos[])
{
    int i;
    for (i = 0; i < DAT; i++)
    {
        memoria_datos[i] = 0;
    }
}
void Etapa_commit()
{
    // Objetivo: Retirar la instrucción contenida en ROB y apuntada por p_rob_cabeza si se ha ejecutado su etapa WB en un ciclo anterior.
    // En otro caso no hace nada
    // Se retiran en el mismo orden como se introducen. Solo se pueden retirar una instrucción por ciclo
    // Acciones. SI x es la línea de ROB a retirar
    // * instrucciones ALU y ld: Actualizar el registro ROB[x]. destino con el resultado almacenado en ROB[x].valor,
    // si registro.TAG_ROB = ROB[x]:TA_ROB etiquetas y validarlo
    // * Instrucciones sd: escribir en memoria en dirección ROB[x].destino el dato ROB[x].valor
    // *Elimina la instrucción de instrucción de ROB
    //
    // Para todos los casos: Validar un resultado o un operando significa poner el campo ok a 1 y actualizar el campo clk_tick_ok con el
    // el ciclo de reloj donde se ha realizado la validación.
    ROB_t rob_;
    rob_ = ROB[p_rob_cabeza]; // instrucción a eliminar de ROB
    if ((rob_.busy == 1) && (rob_.etapa == WB) && (rob_.valor_ok == 1) && (rob_.clk_tick_ok < ciclo))
    { // instrucción preparada para retirar
        // Actualizar el registro rob_.destino con rob_.valor, si rob_.TAG_ROB coincide con la etiqueta almacenada en ese registro destino.
        // Si rob_.operacion es store, escribir en memoria en la dirección rob_.destino el valor de rob_.valor
        // Retirar instrucción de ROB: Actualizar puntero de cabecera y número de instrucciones en rob (en store solo hace esto)
        // Limpiar línea ROB. Poner línea todo a 0
        if (rob_.instruccion == sd)
        {
            memoria_datos[rob_.destino] = rob_.valor;
        }
        else if (rob_.TAG_ROB == banco_registros[rob_.destino].TAG_ROB)
        {
            banco_registros[rob_.destino].contenido = rob_.valor;
        }
        p_rob_cabeza++;
        inst_rob--;
        rob_.TAG_ROB = 0;
        rob_.instruccion = 0;
        rob_.busy = 0;
        rob_.destino = 0;
        rob_.valor = 0;
        rob_.valor_ok = 0;
        rob_.clk_tick_ok = 0;
        rob_.etapa = 0;
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
    // *Estos son los operandos cuyos campos opa_ok y opb_ok estén a 0 y en los campos opa y opb tiene un valor igual al de
    // UF[i].TAG_ROB:
    // *en el campo opa/opb se pone UF[i].res y en opa_ok/opb_ok se pone un 1
    // *en el campo clk_tick_ok_a y clk_tick_ok_b se actualiza ciclo
    // Si no hay ninguno resultado disponible, no se hace nada
    int i = 0, j = 0;   // contador de unidades funcionales
    int bucle = 0, fin; // controla salir del bucle cuando encuentra un resultado valido. Solo WB un resultado
    while (bucle == 0 && i < TOTAL_UF)
    { // busca resultado valido en todas las UF. El primero que encuentra lo escribe en ROB y actualiza ER
        if (UF[i].uso == 1 && UF[i].res_ok == 1 && UF[i].clk_tick_ok < ciclo)
        {
            ROB[UF[i].TAG_ROB].valor = UF[i].res;
            ROB[UF[i].TAG_ROB].valor_ok = 1;
            ROB[UF[i].TAG_ROB].clk_tick_ok = ciclo;
            if (ROB[UF[i].TAG_ROB].instruccion == sd)
            {
                ROB[UF[i].TAG_ROB].destino = UF[i].opa;
            }
            // Actualiza linea ROB, x=ROB.UF[i].TAG_ROB con
            // ALU, ld: ROB[x].valor = UF[i].res y se valida con el resto de campos de ROB
            // sd: ROB.destino =UF[i].opb y ROB[x].valor = opb y se valida en el resto de campos de ROB
            //  Dejar libre UF. Poner todo a 0s
            UF[i].uso = 0;
            UF[i].cont_ciclos = 0;
            UF[i].TAG_ROB = 0;
            UF[i].opa = 0;
            UF[i].opb = 0;
            UF[i].operacion = 0;
            UF[i].res = 0;
            UF[i].res_ok = 0;
            /* resultado
            /* se ha escrito un dato. No se pueden escribir más. */
            bucle = 1;          // no habrá más iteraciones del bucle
                                // actualizar estaciones de reserva donde hay líneas que esperan ese resultado.
                                // bucle para recorrer todas las ER
            fin = p_er_cola[i]; // puntero al final de la ER
            for (j = 0; j < fin; j++)
            { // una iteración por línea de ER ocupada de ER[k]. Siempre empieza en 0 (posibilidad de que no sea así)
                /*Si operando depende de ese resultado */
                if (ER[i][j].busy)
                { // si la línea está ocupada.
                    if ((ER[i][j].opa_ok == 0) && (ER[i][j].opa == UF[i].TAG_ROB))
                    {
                        ER[i][j].opa = ROB[UF[i].TAG_ROB].valor;
                        ER[i][j].opa_ok == 1;
                        break;
                    }
                    if (ER[i][j].opb_ok == 0 && ER[i][j].opb == UF[i].TAG_ROB)
                    {
                        ER[i][j].opb = ROB[UF[i].TAG_ROB].valor;
                        ER[i][j].opb_ok == 1;
                        break;
                    } // opb

                } // fin for líneas ER
            }     // end for todas ER
        }
        else           // if principal
            i = i + 1; // siguiente UF
    }                  // while todas UFs
}
void Etapa_EX()
{
    // En todas las UF:
    // 1. En todas las UF que están en uso:
    // * Incremento un ciclo de operación.
    // *Si es el último: generar resultado y almacenarlo en UF[i].res, validarlo y actualizar ciclo
    // 2. Si alguna está libre: Enviar una nueva instrucción a ejecutar si hay instrucción disponible de ese tipo
    // * Se busca una instrucción que tenga los operandos disponibles en su ER
    // * Solo se puede enviar una instrucción
    // Instrucción ALU y ld: inicializa la UF, carga operandos.
    // Instrucción sd: Actualiza UF, calculando la dirección destino en opa y genera el resultado que es el opb. Cont_ciclos lo pone a max.
    // Dato se escribe en memoria en etapa Commit.
    // *Se libera la línea de la ER de la instrucción enviada a ejecutar.
    // Consideración: en esta plantilla no se tiene en cuenta las líneas libres de las ERs no ocupadas.
    int i = 0;  // contador unidades funcionales
    int enviar; // no se ha enviado ninguna instrucción a ejecutar
    int max;
    int j, fin;
    UF_t unidad;
    ER_t *estacionR;

    while (i < TOTAL_UF)
    {
        // revisa todas las UFs. Si está en uso, Incrementa ciclo.
        // Si es el último, generar resultado y validarlo. si no envía una instrucción a ejecutar (si la hay de ese tipo).
        unidad = UF[i];

        // Establecer ciclos máximos para cada UF
        if (i == 0)
            max = CICLOS_ALU;
        else if (i == 1)
            max = CICLOS_MEM;
        else if (i == 2)
            max = CICLOS_MULT;

        if (unidad.uso)
        { // si está en uso, se incrementa el ciclo y no se pueden enviar otra instrucción.

            if (unidad.cont_ciclos < max)
            {
                unidad.cont_ciclos++;
            }
            else
            {
                unidad.res_ok = 1;
                unidad.clk_tick_ok = ciclo;

                if (i == 2)
                    unidad.res = unidad.opa * unidad.opb;
                else // COMPROBAR
                    unidad.res = unidad.opa + unidad.opb;
            }
        }
        i++;
    }

    // Buscamos la ER de ADD:
    enviar = 0;
    estacionR = ER[0];
    fin = p_er_cola[0];
    j = 0;
    while ((!enviar) && (j < fin))
    {
        if (estacionR[j].busy)
        {
            if (estacionR[j].opa_ok && estacionR[j].clk_tick_ok_a < ciclo && estacionR[j].opb_ok && estacionR[j].clk_tick_ok_b < ciclo)
            { // Operandos disponibles

                // Mandamos la instrucción a ejecutar, actualizando la UF
                UF[i].cont_ciclos = 1;
                UF[i].opa = estacionR[j].opa;
                UF[i].opb = estacionR[j].opb;
                UF[i].res_ok = 0;
                UF[i].res = -1;
                UF[i].uso = 1;
                UF[i].TAG_ROB = estacionR[j].TAG_ROB;
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                enviar = 1;
                estacionR[j].busy = 0;
            }
        }
        else
            j++;
    }

    // Buscar en ER MULT
    estacionR = ER[2];
    fin = p_er_cola[2];
    j = 0;
    while ((!enviar) && (j < fin))
    {
        if (estacionR[j].busy)
        {
            if (estacionR[j].opa_ok && estacionR[j].clk_tick_ok_a < ciclo && estacionR[j].opb_ok && estacionR[j].clk_tick_ok_b < ciclo)
            { // Operandos disponibles

                // Mandamos la instrucción a ejecutar, actualizando la UF
                UF[i].cont_ciclos = 1;
                UF[i].opa = estacionR[j].opa;
                UF[i].opb = estacionR[j].opb;
                UF[i].res_ok = 0;
                UF[i].res = -1;
                UF[i].uso = 1;
                UF[i].TAG_ROB = estacionR[j].TAG_ROB;
                ROB[estacionR[j].TAG_ROB].etapa = EX;
                enviar = 1;
                estacionR[j].busy = 0;
            }
        }
        else
            j++;
    }

    // Buscar en ER MEM
    if ((!enviar) && (i == 1))
    { // store
        estacionR = ER[1];
        if (((estacionR[0].operacion == sd)) && ((estacionR[0].opa_ok) && (estacionR[0].clk_tick_ok_a < ciclo)) && (estacionR[0].opb_ok) && (estacionR[0].clk_tick_ok_b < ciclo))
        { // operandos disponibles para store

            int dirmem = estacionR[0].opa + estacionR[0].inmediato;
            UF[i].res = estacionR[0].opb;
            UF[i].cont_ciclos = max;
            UF[i].uso = 1;
            UF[i].TAG_ROB = estacionR[0].TAG_ROB;
            ROB[estacionR[0].TAG_ROB].etapa = EX;
            enviar = 1;
            estacionR[0].busy = 0;
        }
    }

    if ((!enviar) && (i == 1))
    { // load
        estacionR = ER[1];
        if (((estacionR[0].operacion == ld)) && ((estacionR[0].opa_ok) && (estacionR[0].clk_tick_ok_a < ciclo)))
        { // operandos disponibles para store
            int dirmem = estacionR[0].opa + estacionR[0].inmediato;
            int sd_en_rob = 0;
            int x;

            for (x = 0; x < INS; x++)
                if (ROB[x].instruccion == sd)
                {
                    sd_en_rob++;
                }

            if (sd_en_rob)
            {
                UF[i].res = ROB[x].valor;
                UF[i].cont_ciclos = max;
            }
            else
            {
                UF[i].cont_ciclos = 1;
            }
            UF[i].uso = 1;
            UF[i].TAG_ROB = estacionR[0].TAG_ROB;
            ROB[estacionR[0].TAG_ROB].etapa = EX;
            enviar = 1;
            estacionR[0].busy = 0;
        }
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
    // 5. Actualiza PC + 1 y inst_prog - 1
    if (inst_prog > 0)
    { // leer la instrucción apuntada por PC y almacenarla en ER y ROB
        instruccion_t inst = memoria_instrucciones[PC++];
        ROB_t linea; 
        linea.TAG_ROB = p_rob_cola;
        linea.instruccion = inst.cod;
        linea.busy = 1;
        linea.destino = inst.rd;
        linea.valor = 0;
        linea.valor_ok = 0;
        linea.clk_tick_ok = 0;
        linea.etapa = 0;
        ROB[p_rob_cola++]=linea;
        inst_rob++;
        // Añadir instrucción en ROB[p_rob_cola] y actualizar todos sus campos.
        // actualizar p_rob_cola + 1
        // Actualizar línea de la ER correspondiente según tipo de instrucción, ER[p_er_cola[tipo]], donde tipo se obtiene a partir del código de operación.
        int uf;
        if (inst.cod ==1 || inst.cod==2)
            uf=ALU;
        else if(inst.cod==5)
            uf=MULT;
        else
            uf=MEM;
        int index_RS = p_er_cola[uf]++;
        ER_t linea_ER;
        linea_ER.busy = 1;
        linea_ER.operacion = 0;
        linea_ER.opa = 0;
        linea_ER.opa_ok = 0;
        linea_ER.clk_tick_ok_a = 0;
        linea_ER.opb = 0;
        linea_ER.opb_ok = 0;
        linea_ER.clk_tick_ok_b = 0;
        linea_ER.inmediato = inst.inmediato;
        linea_ER.TAG_ROB = p_rob_cola;
        //  p_er_cola[tipo] es el puntero que apunta a la línea donde se tiene que insertar la instrucción
        //  Todas las instrucciones excepto ld: buscar operandos a y b en registros y/o ROB. Load solo busca operando a
        if (inst.cod == 3)
        {
            linea.destino = inst.rt;
            if (banco_registros[inst.rs].ok == 1)
                ER[inst.cod][index_RS].opa = banco_registros[inst.rs].contenido;
            else
            {
                int rob_rt = banco_registros[inst.rt].TAG_ROB;
                if (ROB[rob_rt].valor_ok == 1)
                    ER[inst.cod][index_RS].opa = ROB[rob_rt].valor;
                else
                {
                    ER[inst.cod][index_RS].opa_ok = ROB[rob_rt].TAG_ROB;
                    ER[inst.cod][index_RS].clk_tick_ok_a = ROB[rob_rt].clk_tick_ok;
                }
            }
        }
        else
        {
            if (inst.cod = !4)
                linea.destino = inst.rd;

            if (banco_registros[inst.rs].ok == 1)
                ER[inst.cod][index_RS].opa = banco_registros[inst.rs].contenido;
            else
            {
                int rob_rt = banco_registros[inst.rt].TAG_ROB;
                if (ROB[rob_rt].valor_ok == 1)
                    ER[inst.cod][index_RS].opa = ROB[rob_rt].valor;
                else
                {
                    ER[inst.cod][index_RS].opa_ok = ROB[rob_rt].TAG_ROB;
                    ER[inst.cod][index_RS].clk_tick_ok_a = ROB[rob_rt].clk_tick_ok;
                }
            }
            if (banco_registros[inst.rs].ok == 1)
                ER[inst.cod][index_RS].opa = banco_registros[inst.rs].contenido;
            else
            {
                int rob_rs = banco_registros[inst.rs].TAG_ROB;
                if (ROB[rob_rs].valor_ok == 1)
                    ER[inst.cod][index_RS].opb = ROB[rob_rs].valor;
                else
                {
                    ER[inst.cod][index_RS].opb_ok = ROB[rob_rs].TAG_ROB;
                    ER[inst.cod][index_RS].clk_tick_ok_b = ROB[rob_rs].clk_tick_ok;
                }
            }
        }
        ER[inst.cod][index_RS]=linea_ER;
        inst_prog--;
        //  Si es válido, cargarlo en ER sino poner línea de ROB que proporcionará su valor cuando se ejecute la instrucción de quien dependey poner
        // operando no válido
        // Actualizamos registro destino (inst.rd) como no válido y línea de ROB donde está la instrucción que lo genera
        //  Actualizar PC para que apunte siguiente instrucción PC + 1 y el número de instrucciones leídas inst_prog - 1
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
            if (!strcmp(tipo_s, "fadd"))
                tipo = add; // instruccion add
            else if (!strcmp(tipo_s, "fsub"))
                tipo = sub; // instruccion sub
            else if (!strcmp(tipo_s, "fmult"))
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
    printf("INST\tCOD\tRT\tRS\tRD\tINM\n");
    for (i = 0; i < INS; i++)
    {
        printf("%d\t", i + 1);
        printf("%d\t", memoria_instrucciones[i].cod);
        printf("%d\t", memoria_instrucciones[i].rt);
        printf("%d\t", memoria_instrucciones[i].rs);
        printf("%d\t", memoria_instrucciones[i].rd);
        printf("%d\n", memoria_instrucciones[i].inmediato);
    }
    puts("***********************");
}
void imprime_memoria_datos()
{
    int i;
    for (i = 0; i < DAT; i++)
        printf("Memoria datos [%d]: %d\n", i, memoria_datos[i]);
    puts("***********************");
}

void imprime_rob()
{
    int i;
    printf("TAG\tBUSY\tCLK_TICK_OK\tDESTINO\tETAPA\tINSTRUCCION\tVALOR\tVALOR_OK\n");
    for (i = 0; i < INS; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\t\t%d\t%d\n", ROB[i].TAG_ROB, ROB[i].busy, ROB[i].clk_tick_ok, ROB[i].destino, ROB[i].etapa,
               ROB[i].instruccion, ROB[i].valor, ROB[i].valor_ok);

    puts("***********************");
}
void imprime_ER()
{
    int i, j;
    for (i = 0; i < TOTAL_UF; i++)
    {
        printf("Estacion %d\n", i);
        for (j = 0; j < INS; j++)
        {
            printf("TAG_ROB\tOP\tBUSY\tOpA\tCLK_OpA\tOpB\tCLK_OpB\tOpB_OK\tOpB_OK\tINM\n");
            printf("%d\t", ER[i][j].TAG_ROB);
            printf("%d\t", ER[i][j].operacion);
            printf("%d\t", ER[i][j].busy);
            printf("%d\t", ER[i][j].opa);
            printf("%d\t", ER[i][j].clk_tick_ok_a);
            printf("%d\t", ER[i][j].opb);
            printf("%d\t", ER[i][j].clk_tick_ok_b);
            printf("%d\t", ER[i][j].opa_ok);
            printf("%d\t", ER[i][j].opb_ok);
            printf("%d\n", ER[i][j].inmediato);
        }
    }
}

void imprime_UF()
{
    int i;
    printf("TAG_ROB\tUSO\tOPERACION\tCONT_CICLOS\tOpA\tOpB\tRES\tRES_OK\n");
    for (i = 0; i < TOTAL_UF; i++)
    {
        printf("%d\t", UF[i].TAG_ROB);
        printf("%d\t", UF[i].uso);
        printf("%d\t", UF[i].operacion);
        printf("%d\t", UF[i].cont_ciclos);
        printf("%d\t", UF[i].opa);
        printf("%d\t", UF[i].opb);
        printf("%d\t", UF[i].res);
        printf("%d\n", UF[i].res_ok);
    }
}

void imprime_Banco_registros()
{
    int i;
    printf("TAG_ROB\tOK\tCLK_OK\tCONTENIDO\n");
    for (i = 0; i < REG; i++)
    {
        printf("%d\t", banco_registros[i].TAG_ROB);
        printf("%d\t", banco_registros[i].ok);
        printf("%d\t", banco_registros[i].clk_tick_ok);
        printf("%d\n", banco_registros[i].contenido);
    }
}

void imprimeCPU()
{
    printf("Ciclo%d>\n", ciclo);
    printf("Memoria Instrucciones\n");
    imprime_memoria_inst();
    printf("Memoria Datos\n");
    imprime_memoria_datos();
    printf("ROB\n");
    imprime_rob();
    printf("ER\n");
    imprime_ER();
    printf("UF\n");
    imprime_UF();
    printf("Banco de registros\n");
    imprime_Banco_registros();
}

int main(int argc, char *argv[])
{
    // Inicialización del simulador
    inst_prog = Carga_programa();
    Inicializar_ER(ER);
    Inicializar_ROB(ROB);
    Inicializar_Banco_registros(banco_registros);
    Inicializar_memoria_datos(memoria_datos);
    printf("%d y %d\n", inst_rob, inst_prog);
    // Simulación. Bucle que se ejecuta mientras haya instrucciones en el ROB e instrucciones en la memoria de instrucciones
    while ((inst_rob > 0) || (inst_prog > 0))
    { // En un ciclo de reloj se ejecutan las 5 etapas de procesamiento de una instrucción
        // Ejecutar cada una de las etapas.
        // Omitimos IF. La instrucción es leída directamente desde la memoria_instrucciones y se inserta en la ER correspondiente
        // Cada iteración del bucle simula las diferentes etapas de ejecución de la instrucción que se ejecutan en paralelo
        // Ejectuar las etapas en ese orden.
        Etapa_commit();
        Etapa_WB();
        Etapa_EX();
        Etapa_ID_ISS();

        imprimeCPU();
        ciclo++;

    } // while
} // main