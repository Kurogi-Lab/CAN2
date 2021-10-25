/*********** random generator ***************/
unsigned _myrandn = 1.0;
double myrandom() /* between 0 to 1 */
{
  _myrandn *= 78125;
  return(_myrandn/4294967295.0);
  /*	_randn = (_randn*3125)%8388608;
	return(_randn/8388608.0);
	*/
}
