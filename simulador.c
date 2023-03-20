// Juego de instrucciones. código de operación
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

void Inicializar_ER(ER_t **ER)
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
    int i = 0, j = 0; // contador de unidades funcionales
    int bucle = 0;    // controla salir del bucle cuando encuentra un resultado valido. Solo WB un resultado
    while (bucle == 0 && i < TOTAL_UF)
    { // busca resultado valido en todas las UF. El primero que encuentra lo escribe en ROB y actualiza ER
        if (UF[i].uso == 1 && UF[i].res_ok == 1 && UF[i].clk_tick_ok < ciclo)
        {
            ROB[UF[i].TAG_ROB].valor = UF[i].res;
            ROB[UF[i].TAG_ROB].valor_ok = 1;
            ROB[UF[i].TAG_ROB].clk_tick_ok = ciclo;
            if (ROB[UF[i].TAG_ROB].instruccion == sd)
            {
                ROB[UF[i].TAG_ROB].destino = UF[i].op_a;
            }
            // Actualiza linea ROB, x=ROB.UF[i].TAG_ROB con
            // ALU, ld: ROB[x].valor = UF[i].res y se valida con el resto de campos de ROB
            // sd: ROB.destino =UF[i].opb y ROB[x].valor = opb y se valida en el resto de campos de ROB
            //  Dejar libre UF. Poner todo a 0s
            ROB[UF[i].TAG_ROB].uso = 0;
            ROB[UF[i].TAG_ROB].cont_ciclos = 0;
            ROB[UF[i].TAG_ROB].TAG_ROB = 0;
            ROB[UF[i].TAG_ROB].opa = 0;
            ROB[UF[i].TAG_ROB].opb = 0;
            ROB[UF[i].TAG_ROB].operacion = 0;
            ROB[UF[i].TAG_ROB].res = 0;
            ROB[UF[i].TAG_ROB].res_ok = 0;
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
                        if (ER[i][j].opb_ok == 0 && ER[k][j].opb == id)
                        {
                            ER[i][j].opb = ROB[UF[i].TAG_ROB].valor;
                            ER[i][j].opb_ok == 1;
                        } // opb
                    }
                    break;
                } // fin for líneas ER
            }     // end for todas ER
        }
        else           // if principal
            i = i + 1; // siguiente UF
    }                  // while todas UFs
}
void Etapa_EX(){
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
    int i = 0;      // contador unidades funcionales
    int enviar = 0; // no se ha enviado ninguna instrucción a ejecutar
    int max;
    int j, fin;

    UF_t unidad;
    ER_t estacionR;

    while (i < TOTAL_UF){ 
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

        if(unidad.uso){ // si está en uso, se incrementa el ciclo y no se pueden enviar otra instrucción.
            
            if(unidad.cont_ciclos < max){
                unidad.cont_ciclos++;
            
            }else{
                unidad.res = unidad.opa + unidad.opb;
                unidad.res_ok = 1;
                unidad.clk_tick_ok = ciclo;
                /*
                unidad.uso = 0; // WB
                unidad.cont_ciclos = 0; //WB
                */

            }
            
        }else if (! enviar){ // no está en uso y todavía no se ha enviado ninguna instrucción, se comprueba si se puede enviar alguna de este tipo
            
            estacionR = ER[i];
            fin = p_er_cola[i];
            j = 0;

            while ( (! enviar) && ( j < fin ) ){
                
            }
            
            /*
            er_ = ER[i];
            fin = p_er_cola[i]; // última línea insertada
            j = 0;              // contador de líneas de ER[i] desde 0 hasta fin
            while ((enviar == 0) && (j < fin))
            { // búsqueda de instrucción a ejecutar en todas las líneas validas de er_
                if (er_[j].busy == 1)
                { // comprueba si los operandos están disponibles para operación ALU
                    if ((er_[j].operacion == ALU) && (er_[j].opa_ok == 1) && (er_[j].clk_tick_ok_a < ciclo) &&
                        (er_[j].opb_ok == 1) && (er_[j].clk_tick_ok_b < ciclo))
                    { // operandos disponibles
                      // Enviar operación a ejecutar a UF actualizando UF[i] correspondiente;
                      // enviar = 1 indicando que ya no se pueden enviar a ejecutar más instrucciones
                        else if ((er_[j].operacion == store) && (er_[j].opa_ok == 1) && (er_[j].clk_tick_ok_a < ciclo) &&
                                 (er_[j].opb_ok == 1) && (er_[j].clk_tick_ok_b < ciclo))
                        { // operandos disponibles para store
                          //  uf_.opa = er_ [j].opa + er_ [j].inmediato)
                          //   uf_.res = er_ [j].opb, se valida
                          //  uf_. cont_ciclos = max (no ocupa más ciclos), uf_.uso=1
                          //  enviar = 1 indicando que ya no se pueden enviar a ejecutar más instrucciones
                        }
                        else if ((er_[j].operacion == load) && (er_[j].opa_ok == 1) && (er_[j].clk_tick_ok_a < ciclo))
                        { // load
                          // uf_.opa = er_ [j].opa + er_ [j].inmediato)
                          // Hay que verificar que no hay en ninguna línea de ROB (sea x) almacenada una instrucción de tipo sd
                          // donde el campo ROB[x].destino sea igual a esa dirección uf_.opa
                          // Si eso ocurre : UF[i].res = ROB[x].valor y se valida. Además Uf[i].cont_ciclos = max y UF[i].uso=1
                          //  En caso contrario; se inicia operación de lectura en memoria inicializando UF (no hay resultado):
                          //  UF[i]cont_ciclos=1, uf[i].uso=1
                          //  enviar = 1 indicando que ya no se pueden enviar a ejecutar más instrucciones
                        }
                        else
                        { // buscar otra instrucción en esa ER
                            j = j + 1;
                        }
                        if enviar
                        {
                            // Actualizar en ROB[er_.TAG_ROB].etapa=EX
                            // limpiarlínea er_.[i]
                        }
                    }      // while er_
                }  
                        // if principal uf
                i++; // siguiente UF aunque se haya enviado una instrucción hay que comprobar las que están en uso para incrementar ciclo
            
            }              // while UF
        }*/
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
        instruct_t inst = memoria_instrucciones[PC];
        ROB[p_rob_cola].TAG_ROB=p_rob_cola;
        ROB[p_rob_cola].instruccion=inst.cd;
        ROB[p_rob_cola].busy=0;
        ROB[p_rob_cola].destino=inst.rd;
        ROB[p_rob_cola].valor=0;
        ROB[p_rob_cola].valor_ok=0;
        ROB[p_rob_cola].clk_tick_ok=0;
        ROB[p_rob_cola].etapa=0;
        // Añadir instrucción en ROB[p_rob_cola] y actualizar todos sus campos.
        // actualizar p_rob_cola + 1
        // Actualizar línea de la ER correspondiente según tipo de instrucción, ER[p_er_cola[tipo]], donde tipo se obtiene a partir del código de operación.
        int index_RS = p_er_cola[inst.cod]++;
        ER[inst.cod][p_er_cola[inst.cod]].busy=0;
        ER[inst.cod][p_er_cola[inst.cod]].operacion=0;
        ER[inst.cod][p_er_cola[inst.cod]].opa=0;
        ER[inst.cod][p_er_cola[inst.cod]].opa_ok=0;
        ER[inst.cod][p_er_cola[inst.cod]].clk_tick_ok_a=0;
        ER[inst.cod][p_er_cola[inst.cod]].opb=0;
        ER[inst.cod][p_er_cola[inst.cod]].opb_ok=0;
        ER[inst.cod][p_er_cola[inst.cod]].clk_tick_ok_b=0;
        ER[inst.cod][p_er_cola[inst.cod]].inmediato=inst.inmediato;
        ER[inst.cod][p_er_cola[inst.cod]].TAG_ROB=p_rob_cola;
        //  p_er_cola[tipo] es el puntero que apunta a la línea donde se tiene que insertar la instrucción
        //  Todas las instrucciones excepto ld: buscar operandos a y b en registros y/o ROB. Load solo busca operando a
        if (inst.cod==3){
            ROB[p_rob_cola].destino=inst.rt;
            if (banco_registros[inst.rs].ok==1) ER[inst.cod][index_RS].opa=0;
            else {
                ER[inst.cod][index_RS].opa_ok=ROB[banco_registros[inst.rs].TAG_ROB];
                ER[inst.cod][index_RS].clk_tick_ok_a=ROB[banco_registros[inst.rs].clk_tick_ok];

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
            instruct_t inst = memoria_instrucciones[PC];
            ROB[p_rob_cola].TAG_ROB = p_rob_cola;
            ROB[p_rob_cola].instruccion = inst.cd;
            ROB[p_rob_cola].busy = 0;
            ROB[p_rob_cola].destino = inst.rd;
            ROB[p_rob_cola].valor = 0;
            ROB[p_rob_cola].valor_ok = 0;
            ROB[p_rob_cola].clk_tick_ok = 0;
            ROB[p_rob_cola].etapa = 0;
            // Añadir instrucción en ROB[p_rob_cola] y actualizar todos sus campos.
            // actualizar p_rob_cola + 1
            // Actualizar línea de la ER correspondiente según tipo de instrucción, ER[p_er_cola[tipo]], donde tipo se obtiene a partir del código de operación.
            int index_RS = p_er_cola[inst.cod]++;
            ER[inst.cod][p_er_cola[inst.cod]].busy = 0;
            ER[inst.cod][p_er_cola[inst.cod]].operacion = 0;
            ER[inst.cod][p_er_cola[inst.cod]].opa = 0;
            ER[inst.cod][p_er_cola[inst.cod]].opa_ok = 0;
            ER[inst.cod][p_er_cola[inst.cod]].clk_tick_ok_a = 0;
            ER[inst.cod][p_er_cola[inst.cod]].opb = 0;
            ER[inst.cod][p_er_cola[inst.cod]].opb_ok = 0;
            ER[inst.cod][p_er_cola[inst.cod]].clk_tick_ok_b = 0;
            ER[inst.cod][p_er_cola[inst.cod]].inmediato = inst.inmediato;
            ER[inst.cod][p_er_cola[inst.cod]].TAG_ROB = p_rob_cola;
            //  p_er_cola[tipo] es el puntero que apunta a la línea donde se tiene que insertar la instrucción
            //  Todas las instrucciones excepto ld: buscar operandos a y b en registros y/o ROB. Load solo busca operando a
            if (inst.cod == 3)
            {
                ROB[p_rob_cola].destino = inst.rt;
                if (banco_registros[inst.rs].ok == 1)
                    ER[inst.cod][index_RS].opa = 0;
                else
                {
                    ER[inst.cod][index_RS].opa_ok = ROB[banco_registros[inst.rs].TAG_ROB];
                }
            }
            else
            {
                ROB[p_rob_cola].destino = inst.rd;
                if (banco_registros[inst.rs].ok == 1)
                    ER[inst.cod][index_RS].opa = 0;
                else
                {
                    ER[inst.cod][index_RS].opa_ok = ROB[banco_registros[inst.rs].TAG_ROB];
                }
                if (banco_registros[inst.rt].ok == 1)
                    ER[inst.cod][index_RS].opb = 0;
                else
                {
                    ER[inst.cod][index_RS].opb_ok = ROB[banco_registros[inst.rt].TAG_ROB];
                }
            }
            ROB[p_rob_cola].valor_ok = 0;
            p_rob_cola++;
            //  Si es válido, cargarlo en ER sino poner línea de ROB que proporcionará su valor cuando se ejecute la instrucción de quien dependey poner
            // operando no válido
            banco_registros[inst.rd].ok = 0;
            PC++;
            // Actualizamos registro destino (inst.rd) como no válido y línea de ROB donde está la instrucción que lo genera
            //  Actualizar PC para que apunte siguiente instrucción PC + 1 y el número de instrucciones leídas inst_prog - 1
        }
    }

    int Carga_programa(instruccion_t * memoria_instrucciones)
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

    void imprime_memoria_inst(int n_instrucciones, *instruccion_t mem_instrucciones)
    {
        int i;
        puts("************");
        for (i = 0; i < n_instrucciones; i++)
        {
            printf("Instrucción %d\n", i + 1);

            printf("Cod: %d\n", mem_instrucciones[i].cod);
            printf("Rd: %d\n", mem_instrucciones[i].rd);
            printf("Rs: %d\n", mem_instrucciones[i].rs);
            printf("Rt: %d\n", mem_instrucciones[i].rt);
            printf("Inmediato: %d\n", mem_instrucciones[i].inmediato);

            puts("************");
        }
    }
    int main(int argc, char *argv[])
    {
        // Inicialización del simulador
        Carga_programa(inst_prog, memoria_instrucciones);
        Inicializar_ER(ER);
        Inicializar_ROB(ROB);
        Inicializar_Banco_registros(banco_registros);
        Inicializar_memoria_datos(memoria_datos);
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
            ciclo = ciclo + 1;
            // incrementamos contador de ciclo

            // Mostrar el contenido de las distintas estructuras para ver cómo evoluciona la simulación
            Mostrar_ER(ER);
            Mostrar_ROB(ROB);
            Mostrar_Banco_Registros(banco_registros);
        } // while
    }     // main