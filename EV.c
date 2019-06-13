/*******************************************************************************
 * Copyright 2019 Ramzi Maalouf. All rights reserved.
 *
 * File Name : EV.c
 *
 * Description :
 *
 * Version : 0.1.0
 *
 * Created Date : 06/15/2019
 *
 * Modification History :
 *    0.1    RSM             -- Initial Release
 *
 ******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdint.h>
#include "globals.h"
#include "RamziTime.h"
#include "states.h"

/* version number.  Note: the bug release is a normally a date code */
#define MAJOR_REVISION 0
#define MINOR_REVISION 1
#if !defined(BUG_RELEASE_REVISION)
#define BUG_RELEASE_REVISION "0000000"
#endif

int g_iVerboseFlag;

static struct option long_options[] =
  {
    /* These options set a flag. */
    {"verbose", no_argument, 0, 'v'},
    /* These options don't set a flag.
       We distinguish them by their indices. */
    {"debug_level",   required_argument, 0, 'd'}, 
    {"help",       no_argument,             0 ,'H'},
    {0, 0, 0, 0}
  };
/* prototypes */
void Usage (char *Name);
void Version (char *Name);
unsigned int NumberOfElectoralVotes (uint64_t States_In, char PreDisposition);
void PrintStates(uint64_t States_In);

int main(int argc, char *argv[])
{
  int  c = -1;
  int option_index = 0;
  int t_iError = 0;
  int t_uiCount = 0;
  unsigned int t_uiElectoralVotes = 0;
  uint64_t t_ulStates = 0;
  uint64_t t_ulNumberOfCombinations = 0;
  g_iVerboseFlag = DEFAULT_VERBOSE_FLAG;

  if (argc == 1) {
    fprintf(stdout,"%s: No passed Parameters using defaults!\n",argv[0]);
  } 
  
  while ((c = getopt_long (argc, argv, "Hd:v",
			     long_options, 
			     &option_index)) != -1) {
    switch (c)
      {
      case 'd':
	g_iVerboseFlag = strtoul(optarg,(char **)NULL,10);
        t_iError = 1;
	break; 
      case 'H':
	Usage(argv[0]);
        t_iError = 1;
	/* getopt_long already printed an error message. */
	break;
      case 'V':
        Version(argv[0]);
        t_iError = 1;
        break;
      case 'v':
        g_iVerboseFlag +=DEFAULT_VERBOSE_FLAG;
        break;

      } 
  }
  if (t_iError == 0) {
	if (g_iVerboseFlag > 0) { Version(argv[0]); }
  }
  for (t_ulStates = ((uint64_t) 1<<STATES_N)  ;
                    t_ulStates > 0;
                    --t_ulStates) {
  if ((t_uiElectoralVotes = NumberOfElectoralVotes (t_ulStates,'r'))
      >= MINIMUM_EV_TO_WIN) {
   /* fprintf(stdout,"\n\nPattern 0x%lx: %d\n",t_ulStates,t_uiElectoralVotes) ;
    PrintStates(t_ulStates); */
    t_ulNumberOfCombinations ++;
  }
  }
  fprintf(stdout,"Number of Combinations %lu",t_ulNumberOfCombinations);
  return t_iError;
}

unsigned int NumberOfElectoralVotes (uint64_t States_In, char PreDisposition)
{
  unsigned int t_uiReturn = 0;
  unsigned int t_uiCount = 0;
  
  for (t_uiCount = 0; t_uiCount < STATES_N ; t_uiCount ++) {
    t_uiReturn += ((States_In >> t_uiCount) & 0x01) * c_USA[t_uiCount].EV ;
  }
  return t_uiReturn;
}

void PrintStates(uint64_t States_In)
{
  unsigned int t_uiCount = 0;

  for (t_uiCount = 0; t_uiCount < STATES_N ; t_uiCount ++) {
    if ((States_In >> t_uiCount) & 0x01) {
      fprintf(stdout,"\n%s",c_USA[t_uiCount].State);
  }
  }
  fprintf(stdout,"\n");
  return ;
}

void Usage (char *Name) 
{
  Version(Name);
  fprintf(stdout,"%s Usage\n",Name);
  fprintf(stdout, "--verbose:\t\t (default on) prints information to stdout\n");
  fprintf(stdout, "--brief:\t\t (default off) runs quiet\n");
  fprintf(stdout, "-d, --debug_level:\t debug level\n"); 
  fprintf(stdout, "-h, --help: \t\t this menu\n");
  return ;
}

void Version(char *Name)
{
  fprintf(stdout, "%s: Compiled on %s %s\n",Name,
          CompileDate,CompileTime);
  fprintf(stdout, "%s: Release %d.%d.%s\n",Name,
          MAJOR_REVISION,
          MINOR_REVISION,
          BUG_RELEASE_REVISION);

  return;
}

