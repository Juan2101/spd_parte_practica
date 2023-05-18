// C++ code
//
#define led_rojo 15
#define led_verde 14
#define subir 4
#define bajar 6
#define parar 5
#define A 10
#define B 11
#define C 16
#define D 17
#define E 18
#define F 9
#define G 8

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(led_rojo, OUTPUT);
    pinMode(led_verde, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(subir, INPUT_PULLUP);
    pinMode(bajar, INPUT_PULLUP);
    pinMode(parar, INPUT_PULLUP);
    Serial.begin(9600);
}

void display_off()
{
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
}

void display(int num)
{
    switch (num)
    {
    case 0:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        break;
    case 1:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
    case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 4:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 5:
        digitalWrite(A, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 6:
        digitalWrite(A, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
    case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    }
}

void comprobar_arranque(bool &encendido)
{
    if (!encendido)
    {
        while (digitalRead(parar) != 0)
        {
            delay(100);
        }
        encendido = true;
    }
}

void actualizar_led(bool estado)
{
    if (estado)
    {
        digitalWrite(led_rojo, LOW);
        digitalWrite(led_verde, HIGH);
    }
    else
    {
        digitalWrite(led_rojo, HIGH);
        digitalWrite(led_verde, LOW);
    }
}

void montacarga(int piso)
{
    actualizar_led(true);
    for (int i = 0; i < 3000; i++)
    {
        if (digitalRead(parar) == 0)
        {
            boton_emergencia(true);
        }
        delay(1);
    }
    display_off();
  	Serial.print("Se encuentra en el piso ");
  	Serial.println(piso);
  	delay(100);
}

void boton_emergencia(bool emergencia)
{
    actualizar_led(false);
    delay(200);
    while (emergencia)
    {
        if (digitalRead(parar) == 0)
        {
            emergencia = false;
            actualizar_led(true);
            delay(200);
        }
        delay(200);
    }
}

void subir_bajar(int &piso)
{
    if (digitalRead(subir) == 0)
    {
        if (piso < 9)
        {
            piso++;
            montacarga(piso);
        }
    }
    else if (digitalRead(bajar) == 0)
    {
        if (piso > 0)
        {
            piso--;
            montacarga(piso);
        }
    }
}

int piso = 0;
bool encendido = false;

void loop()
{
    comprobar_arranque(encendido);
    if (encendido)
    {
        actualizar_led(false);
        display(piso);
        subir_bajar(piso);
    }
}