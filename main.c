#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265
int N;
typedef double complex cplx;

void _fft(cplx input[], cplx temp2[], int N, int step)
{
	if (step < N)
    {
		_fft(temp2, input, N, step * 2);
		_fft(temp2 + step, input + step, N, step * 2);

		for (int i = 0; i < N; i += 2 * step)
        {
			cplx t = cexp(-I * PI * i / N) * temp2[i + step];     /*twiddle matrix value * complex number*/
			input[i / 2]     = temp2[i] + t;                        /*add*/
			input[(i + N)/2] = temp2[i] - t;                        /*sub*/
		}
	}
}

void fft(cplx input[], int N)
{
	cplx temp2[N];
	for (int i = 0; i < N; i++)
        temp2[i] = input[i];

	_fft(input, temp2, N, 1);
}

void show(const char * s, cplx input[]) {
	printf("%s\n", s);
	for (int i = 0; i < N; i++)
		if (!cimag(input[i]))
			printf("(%g , J0)\n", creal(input[i]));
		else
			printf("(%g , J%g)\n", creal(input[i]), cimag(input[i]));
}

void calculate(cplx input[]) {
    printf("\n(Magnitude&Phase) : \n\n");
	for (int i = 0; i < N; i++)
        printf("(%g , %g)\n", cabsf(input[i]), cargf(input[i]));
}

int isPowerOfTwo (int N)
{
    int x = N;
    while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
        x /= 2;
    return (x == 1);
}

int main()
{
    int n , i;

    printf("\nEnter the number samples in the sequence X(n) (N)= ");
    scanf("%d",&N);

    cplx input[N];
	float temp [N];

    if (isPowerOfTwo(N))
    {
        printf("\nEnter the number samples in the sequence X(n) (n)= ");
        scanf("%d",&n);

        if (n <= N)
        {
           printf("\nEnter the number samples of sequence X(n)\n");
           for( i = 0 ; i < n ; i++)
            {
                printf("\n X(%d)= ",i);
                scanf("%f",&temp[i]);
                input[i] = temp[i];
            }
            for(int j = i ; j < N ; j++)
            {
                input[j] = 0;
            }
            show("\nData: \n", input);
            fft(input, N);
            show("\nFFT : \n", input);
            calculate(input);
        }
        else
        {
            printf("\nN must be greater than n\n");
            return 0;
        }
    }
    else
    {
        printf("\nN must be Base of 2\n");
    }

	return 0;
}
