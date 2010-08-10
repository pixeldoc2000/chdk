// Use correct start address for your ROM file
//#define ROM_START   0xFFC00000   // A-series
#define ROM_START   0xFF810000   // S-, SD-, and G- series

static getString(addr)
{
  auto origa, stringRead;

  stringRead = "";
  origa = addr;

  while(1)
  {
      if (Byte(addr) == 0) break;
      if (addr-origa > 40) return "";
      
      stringRead = form("%s%c", stringRead, Byte(addr));

      addr = addr + 1;
  }

  return stringRead;
}

static replace(str, src, dest)
{
  auto idx;

  while(1)
  {
      idx = strstr(str,src);
      if (idx == -1) break;

      str = substr(str, 0, idx) + dest + substr(str, idx+strlen(src), strlen(str));

  }

  return str;
}
