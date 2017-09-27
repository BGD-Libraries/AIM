#include "GP2Y0.h"

static double median(double value_buf[],const unsigned char n)
{
	double temp;
	for (unsigned char j=0;j<n-1;j++) {
		for (unsigned char i=0;i<n-j-1;i++) {
			if ( value_buf[i]>value_buf[i+1] ) {
				temp = value_buf[i];
				value_buf[i] = value_buf[i+1];
				value_buf[i+1] = temp;   
			}   
		}   
	} 
	if(n%2==0)
		return (value_buf[n/2] + value_buf[n/2-1])/2;
	else
		return value_buf[(n-1)/2];
}

double GP2Y0A02(uint8_t pinA)  //长红外测距
{
  double data[11];
  for(int cnt=0;cnt<11;cnt++){
    data[cnt]=analogRead(pinA);
    data[cnt]=constrain(14779.0*pow(data[cnt],-1.03),0,150);
  }
  return median(data,11);
}

double GP2Y0A21(uint8_t pinA) { //中红外测距
  double data[11];
  for(int cnt=0;cnt<11;cnt++){
    data[cnt]=analogRead(pinA);
    data[cnt]=constrain( ((67870.0/(data[cnt]-3.0))-40.0)/10.0 ,10,80);
  }
  return median(data,11);
}


double GP2Y0A41SK(uint8_t pinA)   //短红外测距
{
  double data[11];
  for(int cnt=0;cnt<11;cnt++){
    data[cnt]=analogRead(pinA);
    data[cnt]=data[cnt]*4.0/1024;   //4为VREF基准：实际值
    data[cnt]=constrain(8.7328*pow(data[cnt],-0.912)+0.25,0,30);    //0.25是调整值，根据测距情况自行添加相应的值
  }
  return median(data,11);
}
