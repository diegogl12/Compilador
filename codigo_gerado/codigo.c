#define max 3
int quantidade;
float altura, largura;
int main(void)
{
	float area;
	int cont;
	scanf("%f %f",&altura, &largura);
	area = (altura * largura );
	if( (area + 0 )<= 100 )
	{
		for(cont = 0 ; cont < max ;)
		{
			quantidade = area * cont ;
			printf("%i\n",quantidade);
			cont = cont + 1 ;
		}
	}
	else
	{
		printf("%i\n",quantidade);
	}
	return 0;
}
