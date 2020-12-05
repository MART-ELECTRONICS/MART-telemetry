int vx;
int vy;
int mapX;
int mapY;

void setup()
{
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	Serial.begin(9600);
}

void loop()
{
	vx = analogRead(A0);
	vy = analogRead(A1);

	vx = map(vx, 0, 1023, -512, 512);
	vy = map(vy, 0, 1023, -512, 512);

	Serial.print("X: ");
	Serial.print(vx);
	Serial.print(" | Y: ");
	Serial.print(vy);
	Serial.print("\n");

	delay(100);
}
