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
typedef struct{                    /* Línea de ROB */
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

void Etapa_EX(){
  int i = 0;      // contador unidades funcionales
  int enviar; // no se ha enviado ninguna instrucción a ejecutar
  int max;
  int j, fin;

  UF_t unidad;
  ER_t *estacionR;

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
        unidad.res_ok = 1;
        unidad.clk_tick_ok = ciclo;

        if(i == 2)
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
  while( (! enviar) && (j < fin) ) {
    if( estacionR[j].busy ){
      if(   estacionR[j].opa_ok && estacionR[j].clk_tick_ok_a < ciclo
        && estacionR[j].opb_ok && estacionR[j].clk_tick_ok_b < ciclo){ // Operandos disponibles

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
    }else
      j++;
  }

  //Buscar en ER MULT
  estacionR = ER[2];
  fin = p_er_cola[2];
  j=0;
  while( (! enviar) && (j < fin) ) {
    if( estacionR[j].busy ){
      if(   estacionR[j].opa_ok && estacionR[j].clk_tick_ok_a < ciclo
        && estacionR[j].opb_ok && estacionR[j].clk_tick_ok_b < ciclo){ // Operandos disponibles

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
    }else
      j++;
  }

  // Buscar en ER MEM
  if ( ( !enviar ) && (i == 1) ){ // store
    estacionR = ER[1]; 
    if ( ((estacionR[0].operacion == sd)) 
        && ( (estacionR[0].opa_ok) && (estacionR[0]. clk_tick_ok_a < ciclo)) 
        &&(estacionR[0].opb_ok) && (estacionR[0]. clk_tick_ok_b < ciclo) ) { //operandos disponibles para store
      
      int dirmem = estacionR[0].opa + estacionR[0].inmediato;
      UF[i].res = estacionR[0].opb;
      UF[i].cont_ciclos = max;
      UF[i].uso = 1;
      UF[i].TAG_ROB = estacionR[0].TAG_ROB;
      ROB[estacionR[0].TAG_ROB].etapa = EX;
      enviar = 1;
      estacionR[0].busy=0;
    }
  }

  if ( ( !enviar ) && (i == 1) ){ // load
    estacionR = ER[1]; 
    if ( ((estacionR[0].operacion == ld)) 
    && ( (estacionR[0].opa_ok) && (estacionR[0]. clk_tick_ok_a < ciclo)) ) { //operandos disponibles para store      
      int dirmem = estacionR[0].opa + estacionR[0].inmediato;
      int sd_en_rob = 0;
      int x;

      for(x = 0; x < INS; x++)
        if (ROB[x].instruccion == sd){
          sd_en_rob++;
        }
      
      if (sd_en_rob){
        UF[i].res = ROB[x].valor;
        UF[i].cont_ciclos = max;
      }else{
        UF[i].cont_ciclos = 1;        
      }
      UF[i].uso = 1;
      UF[i].TAG_ROB = estacionR[0].TAG_ROB;
      ROB[estacionR[0].TAG_ROB].etapa = EX;
      enviar = 1;
      estacionR[0].busy=0;
    }
  }
}