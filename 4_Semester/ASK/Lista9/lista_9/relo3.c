int relo3(int val) {
  switch (val) {
    case 100:
      return val;
    case 101:
      return val + 1;
    case 103:
    case 104:
      return val + 3;
    case 105:
      return val + 5;
    case 106:
      return val + 10;
    default:
      return val + 6;
  }
}
