#include<stdio.h>
#include<math.h>
#define PI 3.1415926
int main()
{
    double r,h;
    printf("Please input r and \n");
    scanf("%lf %lf",&r,&h);
    printf("圆面积：%lf,圆周长：%lf,圆球表面积：%lf,圆球体积：%lf,圆住体积%lf",PI*pow(r,2.0),2*PI*r,4*PI*pow(r,2.0),PI*pow(r,3.0),h*PI*pow(r,2.0));

}
