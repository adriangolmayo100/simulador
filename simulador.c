// Juego de instrucciones. código de operación
#define add 1
#define sub 2
#define ld 3
#define sd 4
#define mult 5
//Capacidad de las estructuras de almacenamiento es ilimitada pero se pone un máximo
#define REG 16 /* Número de registros */
#define DAT 32 /* Tamaño de memoria de datos */
#define INS 32 /* Tamaño de memoria de instrucciones */
/*Códigos para las UF */
#define TOTAL_UF 3 /* total de UF simuladas */
#define ALU 0 /* código para una UF de suma/resta */
#define MEM 1 /* código para UF de carga/almacenamiento */
#define MULT 2 /* código para UF de multiplicación */
/*Ciclos de ejecución de UF */
#define CICLOS_MEM 3 /* Carga y almacenamiento */
#define CICLOS_ALU 2 /* Suma y Resta */
#define CICLOS_MULT 5 /* Multiplicación */
/*Etapas de procesamiento de las instrucciones en ROB*/
#define ISS 1 /* Instruccion emitida*/
#define EX 2 /* Instruccion en ejecucion EX*/
#define WB 3 /* Fase WB realizada */

/* Estructuras de datos */ //Instrucción
typedef struct { /* Codificación Instrucción */
int cod; /* operación a realizar */
int rd; /* registro destino */
int rs; /* registro fuente op1 */
int rt; /* registro fuente op2 */
int inmediato; /* Dato inmediato */
} instruccion_t;
typedef struct { /*Registro del banco de registros */
int contenido; /* contenido */
int ok; /* contenido valido (1) o no (0)*/
int clk_tick_ok; /* ciclo de reloj cuando se valida ok. */
int TAG_ROB; /* Si ok es 0, etiqueta de la línea de ROB donde está almacenada la instrucción que lo actualizará. */
/* Almacena la última */
} reg_t;
typedef struct { /* Línea de una estación de reserva*/
int busy; /* contenido de la línea válido (1) o no (0) */
int operacion; /* operación a realizar en UF (suma,resta,mult,lw,sw) */
Int opa; /* valor Vj*/
Int opa_ok /* Qj, (1) opa válido o no (0)*/
Int clk_tick_ok_a /* ciclo de reloj donde se valida opa_ok */
Int opb; /* Valor Vk */
int opb_ok; /* Qk, (1) válido o (0) no válido */
Int clk_tick_ok_b /* ciclo de reloj se valida donde opb_ok */
int inmediato; /*utilizado para las instrucciones lw/sw */int TAG_ROB; /* etiqueta de la línea del ROB donde se ha almacenado esta instrucción */
} ER_t;
typedef struct { /* Línea de ROB */
int TAG_ROB; /* Etiqueta que identifica la línea de ROB */
int instrucción /* tipo de instrucción */
int busy ; /* Indica si el contenido de la línea es válido (1) o no (0) */
int destino; /* identificador registro destino (rd) */
int valor; /* resultado tras finalizar la etapa EX */
int valor_ok; /* indica si valor es válido (1) o no (0) */
Int clk_tick_ok /* ciclo de reloj cuando se valida valor_ok */
int etapa; /* Etapa de procesamiento de la instrucción ISS, EX, WB */
} ROB_t;
typedef struct { /* Simula el funcionamiento de una UF */
int uso; /* Indica si UF está utilizada (1) o no (0) */
int cont_ciclos; /* indica ciclos consumidos por la UF */
int TAG_ROB; /* Línea del ROB donde se tiene que almacenar el resultado tras EX */
int opa; /* valor opa (en almacenamiento contiene dato a escribir en memoria */
int opb; /* valor opb (en lw y sw contiene dirección de memoria de datos ) */
int operacion; /* se utiliza para indicar operacion a realizar add/sub y lw/sw o mult */
int res; /* resultado */
int res_ok; /resultado valido (1) */
Int clk_tick_ok /* ciclo de reloj cuando se valida res_ok */
} UF_t;
nt main(int argc, char *argv[]) {
// Declaración de las variables que simulan la memoria de datos, de instrucciones y banco de registros.
//Serán vectores
reg_t banco_registros[REG]; /* Banco de registros */
int memoria_datos[DAT]; /* Memoria de datos */
instruccion_t memoria_instrucciones[INS]; /* Memoria de instrucciones */
UF_t UF[TOTAL_UF] /* 3 UF: UF[0] simula la ALU, UF[1] carga/almacenamiento y UF[2] multiplicación */
ER_t ER[TOTAL_UF][INS]; /* Vector de estaciones de reserva ER[0] para ALU, ER[1] para MEM y ER[2] para MULT */
/* INS indica el total de instrucciones que puede almacenar cada ER_t */
ROB_t ROB[INS]; /* Bufer de reordenamiento */
int inst_prog; /* total instrucciones programa */
int inst_rob = 0; /* instrucciones en rob */
int p_rob_cabeza, p_rob_cola = 0; /* puntero a las posiciones de rob para introducir (cola) o retirar instrucciones (cabeza) */
int PC = 0; /* puntero a memoria de instrucciones, siguiente instrucción a IF */
int p_er_cola[TOTAL_UF] = [0,0,0] //vector de punteros que apuntan a la cola de cada una de las UF (
// Inicialización del simulador
Carga_programa (inst_prog, memoria_instrucciones)
Inicializar_ER (ER);
Inicializar_ROB (ROB):
Inicializar_Banco_registros (banco_registros);
Inicializar_memoria_datos(memoria_datos);
int ciclo = 1; //ciclo de ejecución actual
//Simulación. Bucle que se ejecuta mientras haya instrucciones en el ROB e instrucciones en la memoria de instrucciones
while (inst_rob > 0 ) || (inst_prog > 0)) { // En un ciclo de reloj se ejecutan las 5 etapas de procesamiento de una instrucción
//Ejecutar cada una de las etapas.
//Omitimos IF. La instrucción es leída directamente desde la memoria_instrucciones y se inserta en la ER correspondiente
//Cada iteración del bucle simula las diferentes etapas de ejecución de la instrucción que se ejecutan en paralelo
//Ejectuar las etapas en ese orden.
Etapa_commit()
Etapa_WB();
Etapa_EX();
Etapa_ID_ISS();
ciclo = ciclo + 1; /incrementamos contador de ciclo
//Mostrar el contenido de las distintas estructuras para ver cómo evoluciona la simulación
Mostrar_ER(ER);
Mostrar_ROB(ROB);
Mostrar_Banco_Registros(banco_registros);
} //while
}//main
void Etapa_commit() {
// Objetivo: Retirar la instrucción contenida en ROB y apuntada por p_rob_cabeza si se ha ejecutado su etapa WB en un ciclo anterior.
// En otro caso no hace nada
// Se retiran en el mismo orden como se introducen. Solo se pueden retirar una instrucción por ciclo
//Acciones
// * Actualiza el registro destino con el contenido y validarlo, si coinciden las etiquetas
// Para todos los casos: Validar un resultado o un operandosignifica poner el campo ok a 1 y actualizar el campo clk_tick_ok con el
// el ciclo de reloj donde se ha realizado la validación.
// *Elimina la instrucción de instrucción de ROB
ROB_t rob_;
Rob_ = ROB[p_rob_cabeza]; //instrucción a eliminar de ROB
if ((rob_.busy == 1) && (rob_.etapa == WB) && (rob_. valor_ok == 1) && (rob_. clk_tick_ok < ciclo) ) { //instrucción preparada para retirar
// si la etiqueta de la línea ROB coincide con la almacenada en el campo TAG_ROB del registro destino (rd o rt), actualizar rd o rt
//(contenido, ok y clk_tick_ok)
//Retirar instrucción de ROB: Actualizar puntero de cabecera y número de instrucciones en rob (en store solo hace esto)
// Limpiar línea ROB. Poner línea todo a 0
}
void Etapa_WB() {
// Objetivo:
//1. Se busca el primer resultado válido en una unidad funcional y se escribe en ROB.
// Un resultado es válido si el campo de la UF, UF[i].res_ok está a 1 y UF[i].clk_tick_ok
// contiene un valor inferior al ciclo actual.
// Si esas condiciones se cumplen se puede ejecutar la etapa WB que conlleva
// * La línea de ROB que se tiene que actualizar está en el campo de la UF, UF[i].TAG_ROB :
// ROB[UF[i].TAG_ROB].valor = UF[i].res (no lo hace sd)
// ROB[UF[i].TAG_ROB].valor_ok = 1
// ROB[UF[i].TAG_ROB].clk_tick_ok = ciclo (este operando se podrá utilizar en el ciclo siguiente en el que nos encontramos
// ROB[id].etapa = WB
// * Se deja libre UF. Se pone todo a 0
// La ventaja de ejecutar WB antes que EX es que si la etapa WB escribe un resultado, libera la UF que estaba ocupando y así la etapa EX en este mismo
// ciclo puede iniciar otra operación del mismo tipo.
//2. Se actualizan todas las líneas de las ER que esperen ese dato.
// Se tienen que recorrer todas las líneas válidas de todas las estaciones de reserva y aquellos operandos que dependan
// de ese resultado se tienen que actualizar.
// *Estos son los operandos cuyos campos opa_ok y opb_ok estén a 0 y en los campos opa y opb tiene un valor igual al de UF[i].TAG_ROB:
// *en el campo opa/opb se pone UF[i].res y en opa_ok/opb_ok se pone un 1
// *en el campo clk_tick_ok_a y clk_tick_ok_b se actualiza ciclo
// Si no hay ninguno resultado disponible, no se hace nada
i = 0; //contador de unidades funcionales
bucle = 0; //controla salir del bucle cuando encuentra un resultado valido. Solo WB un resultado
While (bucle == 0 && i < TOTAL_UF) { // busca resultado valido en todas las UF. El primero que encuentra lo escribe en ROB y actualiza ER
If (UF[i].uso == 1 && UF[i].res_ok == 1 && UF[i]. clk_tick_ok < ciclo) {
//Actualiza ROB con resultado. línea a actualizar UF[i].TAG_ROB (en store no almacena resultado)
// Dejar libre UF. Poner todo a 0s
/* se ha escrito un dato. No se pueden escribir más. */
bucle = 1; //no habrá más iteraciones del bucle
//actualizar estaciones de reserva donde hay líneas que esperan ese resultado.
for (k=0; k< TOTAL_UF; k++) { //bucle para recorrer todas las ER
fin = p_er_cola[k] //puntero al final de la ER
for (j = 0; j < fin; j++) { //una iteración por línea de ER ocupada de ER[k]
/*Si operando depende de ese resultado */
If (ER[k][j].busy == 1) {// si la línea está ocupada.
If ((ER[k][j].opa_ok == 0) && (ER[k][j].opa == UF[i].TAG_ROB)) {//si opa no disponible y depende de TAG_ROB
//Actualizar operando a (valor, ok y ciclo)
} //opa
If (ER[k][j].opb_ok == 0 && ER[k][j].opb == id) { //Si operando b depende de ese resultado
//Actualizar operando b (valor, ok y ciclo)
} //opb
}
}// fin for líneas ER
} // end for todas ER
} else //if principal
i = i + 1; // siguiente UF
} //while todas UFs
}
Etapa_EX()
// En todas las UF:
// 1. En todas las UF que están en uso:
// * Incremento un ciclo de operación.
// *Si es el último: generar resultado y almacenarlo en UF[i].res, validarlo y actualizar ciclo
// 2. Si alguna está libre: Enviar una nueva instrucción a ejecutar si hay instrucción disponible de ese tipo
// * Se busca una instrucción que tenga los operandos disponibles en su ER
// * Solo se puede enviar una instrucción
i = 0; //contador unidades funcionales
enviar = 0 // no se ha enviado ninguna instrucción a ejecutar
While (i<TOTAL_UF) { // revisa todas las UFs. Si está en uso, Incrementa ciclo.
//Si es el último, generar resultado y validarlo. si no envía una instrucción a ejecutar (si la hay de ese tipo).
uf_ = UF[i]
// Establecer ciclos máximos para cada UF
if i == 0 max = CICLOS_ALU
else if i == 1 max = CICLOS_MEM
else if i == 2 max = CICLOS_MULT;
If ((uf_.uso == 1)) { // si está en uso, se incrementa el ciclo y no se pueden enviar otra instrucción.
If (uf_.cont_ciclos < max) {
uf_.cont_ciclos = uf_.cont_ciclos + 1 // incrementar el ciclo
If ( uf_.cont_ciclos == max) {
//si se ha finalizado la operación generar resultado, validarlo, actualizar ciclo
}
}
} else if (enviar == 0){ // no está en uso y todavía no se ha enviado ninguna instrucción, se comprueba si se puede enviar alguna de este tipo
er_ = ER[i]
fin = p_er_cola[i] //última línea insertada
j = 0 //contador de líneas de ER[i] desde 0 hasta fin
while ( (enviar == 0) &&( j < fin) { // búsqueda de instrucción a ejecutar en todas las líneas validas de er_
If (er_[j].busy == 1) { // comprueba si los operandos están disponibles
If ((er_ [j].opa_ok == 1) && (er_[j]. clk_tick_ok_a < ciclo) &&
(er_[j].opb_ok == 1) && (er_[j]. clk_tick_ok_b < ciclo) { // operandos disponibles. load solo busca operando a.
// Enviar operación a ejecutar a UF actualizando UF[i]
//Actualizar etapa a EX en ROB.
// enviar = 1 indicando que ya no se pueden enviar a ejecutar más instrucciones
}
else {//buscar otra instrucción en esa ER
j = j + 1;
}
} //while er_
} // if principal uf
i = i + 1; //siguiente UF aunque se haya enviado una instrucción hay que comprobar las que están en uso para incrementar ciclo
} //while UF
}
Etapa_ID_ISS ()
//1.- Lee una instrucción de la directamente de la memoria de instrucciones y la inserta en la ER correspondiente.
// instrucción apuntada por PC: inst = memoria_instrucciones[PC]
// 2.- Identifica el tipo de instrucción y selecciona la ER para insertarla. Será función del código de operación de la instrucción
// Si inst.cod == 1 o 2 → tipo =ALU
// Si inst.cod == 3 o 4 → tipo = MEM
// SI inst.cod == 4 → tipo = MULT
//
//3.- Añadir instrucción en ROB en la posición indicada en p_rob_cola. Actualiza todos sus campos
// Actualiza p_rob_cola + 1
// 4.- Utiliza el puntero p_er_cola(tipo) que apunta a la cola de ER[tipo] para almacenarla en esa posición.
// Actualiza todos sus campos:
// * opa y opb. Busca en registros rs y rt
// * Si el campo ok de esos registros está a 1 y clk_tick_ok es menor que el ciclo actual,
// se carga su contenido en los campos opa y opb de la ER, se validan y se actualiza el ciclo (operandos válidos)
// * En caso contrario se carga en opa y/o opb lo que hay en el campo TAG_ROB de esos registros, y no se validan (operandos no válidos)
// *Etiqueta de la línea de ROB donde almacena la instrucción.
// *Actualizar p_er_cola[tipo] + 1
//4.- Invalidar contenido del registro destino poniendo campo ok a 0 y en TAG_ROB la línea de ROB donde se ha almacenado dicha instrucción.
//5. Actualiza PC + 1 y inst_prog - 1
If (inst_prog > 0) { //leer la instrucción apuntada por PC y almacenarla en ER y ROB
inst = memoria_instrucciones[PC]
//Añadir instrucción en ROB[p_rob_cola] y actualizar todos sus campos.
//actualizar p_rob_cola + 1
//Actualizar línea de la ER correspondiente según tipo de instrucción, ER[p_er_cola[tipo]], donde tipo se obtiene a partir del código de operación.
// p_er_cola[tipo] es el puntero que apunta a la línea donde se tiene que insertar la instrucción
// Todas las instrucciones excepto load: buscar operandos a y b en registros y/o ROB. Load solo busca operando a
// Si es válido, cargarlo en ER sino poner línea de ROB que proporcionará su valor cuando se ejecute la instrucción de quien depende.
//Actualizamos registro destino (inst.rd) como no válido y línea de ROB donde está la instrucción que lo genera
// Actualizar PC para que apunte siguiente instrucción PC + 1 y el número de instrucciones leídas inst_prog - 1
}
