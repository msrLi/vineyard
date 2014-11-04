#include"exchangeData.h"
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
/* 
function :
can:
--------number :  浮点型数据
--------ndigit :   小数点后保留几位数据
--------*buf   :  字符串接受首地址
*/
char *my_ftoa(double number,int ndigit,char *buf)    // 将 浮点型转换成 字符串行
{  
    long int_part;  
    double float_part;  
	int i;
    char str_int[32];  
    char str_float[32];  
    memset(str_int,0,32);  
    memset(str_float,0,32);  
    int_part = (long)number;  
    float_part = number - int_part;  
    // 整数部分处理  
    myitoa(int_part,str_int,10);  
    // 小数部分处理  
    if(ndigit>0)  
    {  
        float_part = fabs( pow(10,ndigit)*float_part);  
        myitoa((long)float_part,str_float,10);  
    }  
    i = strlen(str_int);  
    str_int[i] = '.';  
    strcat(str_int,str_float);  
    strcpy(buf,str_int);  
    return buf;  
} 
/* 整行转换成  其他形式 */
char* myitoa(int num,char*str,int radix)
{/*索引表*/
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;/*中间变量*/
	int i=0,j,k;
	char temp;
	/*确定unum的值*/
	if(radix==10&&num<0)/*十进制负数*/
	{
		unum=(unsigned)-num;
		str[i++]='-';
	}
	else unum=(unsigned)num;/*其他情况*/
	/*转换*/
	do{
		str[i++]=index[unum%(unsigned)radix];
		unum/=radix;
	}while(unum);
	str[i]='\0';
	/*逆序*/
	if(str[0]=='-') k=1;/*十进制负数*/
	else k=0;
	
	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}
	return str;
}
int my_atoi(const char * str)
{
	int res=0,begin=0;
	bool minus=FALSE;
	while( *str!= '\0')
	{
		if(begin==0&&(('0'<*str&&*str<'9')|| *str=='-') )         //从第一个数字或者'-'号开始
		{
			begin=1;
			if(*str == '-')
			{
				minus=TRUE;
				str++;
			}
		}else if( begin==1&&(*str<'0'||*str>'9') )           //遇到第一个非数字，退出
			break;
		if(begin==1)
		res=res*10+(*str-'0');                       //计算
		str++;
	}
	return minus? -res : res;
}
static int is_digit(char ch)  
{  
    if(ch>='0'&&ch<='9')  
        return 1;  
    else  
        return 0;  
}  
static int is_space(char ch)  
{  
    if(ch==' ')  
        return 1;  
    else  
        return 0;  
}  
double myatof(char *s)  
{  
    double power,value;  
    int i,sign;  
    // assert(s!=NULL);//判断字符串是否为空  
	if(s[0]==0 || s[0]=='\0') 
		return 0;
    for(i=0;is_space(s[i]);i++);//除去字符串前的空格  
    sign=(s[i]=='-')?-1:1;  
    if(s[i]=='-'||s[i]=='+')//要是有符号位就前进一位  
        i++;  
    for(value=0.0;is_digit(s[i]);i++)//计算小数点钱的数字  
        value=value*10.0+(s[i]-'0');  
    if(s[i]=='.')  
        i++;  
    for(power=1.0;is_digit(s[i]);i++)//计算小数点后的数字  
    {  
        value=value*10.0+(s[i]-'0');  
        power*=10.0;  
    }  
    return sign*value/power;  
}  
