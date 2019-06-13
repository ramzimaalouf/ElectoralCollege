
#if !defined(STATES_H_)
#define STATES_H_

#define STATES_NAME_LEN_N 24
#define STATES_N 51
#define MINIMUM_EV_TO_WIN 270
#define MINIMUM_NUMBER_OF_STATES_REQUIRED 11  /* -- This is the minimum 
                                                -- number of states required
                                                -- to get to EV.  Just grabbed
                                                -- the biggest states and
                                                -- summed until EV Min is 
                                                -- achieved. */
                                                

typedef struct _EV_Distribution { 
  char State[STATES_NAME_LEN_N];
  unsigned char EV;
  char PreDisposition;
} s_EV_Distribution;

const s_EV_Distribution c_USA[STATES_N]=
{
{"Alabama",	9,'r'},
{"Alaska",	3},
{"Arizona",	11,'r'},
{"Arkansas",	6,'r'},
{"California",	55,'d'},
{"Colorado",	9},
{"Connecticut",	7,'d'},
{"Delaware",	3,'d'},
{"District of Columbia",	3,'d'},
{"Florida",	29},
{"Georgia",	16,'r'},
{"Hawaii",4,'d'},
{"Idaho",	4,'r'},
{"Illinois",	20,'d'},
{"Indiana",	11},
{"Iowa",	6},
{"Kansas",	6,'r'},
{"Kentucky",	8,'r'},
{"Louisiana",	8,'r'},
{"Maine",	4},
{"Maryland",	10,'d'},
{"Massachusetts	",11,'d'},
{"Michigan",	16},
{"Minnesota",	10},
{"Mississippi",	6,'r'},
{"Missouri",	10,'r'},
{"Montana",	3,'r'},
{"Nebraska",	5,'r'},
{"Nevada",	6},
{"New Hampshire",	4},
{"New Jersey",	14,'d'},
{"New Mexico",	5},
{"New York",	29,'d'},
{"North Carolina",15},
{"North Dakota",	3,'r'},
{"Ohio",	18},
{"Oklahoma",	7,'r'},
{"Oregon",7,'d'},
{"Pennsylvania",	20},
{"Rhode Island",	4,'d'},
{"South Carolina",	9,'r'},
{"South Dakota",	3,'r'},
{"Tennessee",	11,'r'},
{"Texas",38,'r'},
{"Utah",6,'r'},
{"Vermont",	3,'d'},
{"Virginia",	13},
{"Washington",12,'d'},
{"West Virginia",5,'r'},
{"Wisconsin",10},
{"Wyoming",	3,'r'},
};
#endif

