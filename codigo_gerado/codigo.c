#define max 100
int quantidade;
float altura, largura;
int main(void)
{
	float area;
	int cont;
	scanf( altura, largura);
	area = (altura * largura );
	if( (quantidade + 1 )>= 30 )
	{
		float teste;
		if( cont == 0 )
		{
			for(cont = 0 ; cont < max ; cont++)
			{
				quantidade = area * cont ;
				printf(quantidade);
				cont = cont + 1 ;
			}
		}
		else
		{
			printf(quantidade);
		}
	}
	return 0;
}
