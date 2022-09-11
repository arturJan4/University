unsigned int fun(unsigned int a,unsigned int b)
{
	return (a >> b) | ( a << 32 - b);
}
